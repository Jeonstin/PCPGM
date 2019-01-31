#include "3DGraphCtrl.h"
#include "MSG.h"
#include <userint.h>
#include "resultview.h"
#include 	<analysis.h>
#include 	"spc.h"
#include 	<formatio.h>
#include 	<ansi_c.h>
#include 	<utility.h>
#include 	"main.h"
#include 	"UserDefinedConst.h"
#include 	"PLC_IODefinedConst.h"
#include 	"UIRDefinedHeader.h"					  
#include 	"UserDefinedGlobal.h"

#define hrChk(f)            if (hr = (f), FAILED(hr)) goto Error; else
#define SIZE               180
#define SIZE1               10
#define NUM_CUSTOM_COLORS   (sizeof(gColorCtrls) / sizeof(gColorCtrls[0]))
static int          gColorCtrls[5] = {   INTPANEL_COLOR1, INTPANEL_COLOR2, 
                                        INTPANEL_COLOR3, INTPANEL_COLOR4, 
                                        INTPANEL_COLOR5
                                    };

int		UserModalFlag; // 사용자 메세지 박스의 모달여부
int		AutoRetry, ReverseFlag, AMeasMode;
 int	language;
double	A_Low[3],A_High[3],M_Low[3],M_High[3]; 
static HRESULT RefreshControls(void);
static CAObjHandle  gGraph;
static HRESULT GetPlot(CAObjHandle *plot);
static void RefreshCustomColorControls(void);
static int IsColorMapCustom(void);
static HRESULT SetCustomColorMap(void);

 void	GetBeforeDay( char	*date ) // 하루전의 날짜를 얻어옴.
{
	int	month, day, year;

	GetSystemDate(&month, &day, &year);
	if( day > 1 )
	{
		sprintf(date, "%d-%02d-%02d", year, month, day - 1);
	}
	else
	{
		month--;
	    switch( month )                                      
	    {
	        case 0:
	        	year--;
	        	month = 12;
	        	day = 31;
	        	break;
	        case 1:
	        case 3:                                             
	        case 5:                                             
	        case 7:                                             
	        case 8:                                             
	        case 10:                                            
	        case 12:
	        	day = 31;
	        	break;
	        case 4:                                             
	        case 6:                                             
	        case 9:                                             
	        case 11: 
	        	day = 30;
	        	break;
	        case 2:                                             
	             if( year % 4 )
	             	day = 28;
	             else
	             	day = 29;
	    }
		sprintf(date, "%d-%02d-%02d", year, month, day);
	}
}

void GetDataFileName(char *datestr)
{
	char	Temp[30], DateStamp[30];
	
	if( datestr == NULL ) // 새로 생성
	{
		sprintf(Temp, "%s", DateStr());
		MakeDateStr(DateStamp, Temp);
		
		if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
		GetBeforeDay( DateStamp );

		if( DayOrNightWork == 0 ) // 주간
		{
			if( SepFileFlag )  // 주야간 파일 분리
				strcat(DateStamp, "_DAY");
		}
		else
		{
			if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
				GetBeforeDay( DateStamp );
				
			if( SepFileFlag )
				strcat(DateStamp, "_NIGHT");
		}
	}
	else
		strcpy(DateStamp, datestr);

	strcpy(DataFileNameOk, PrjDirectory);
	strcat(DataFileNameOk, "\\Product\\");
	sprintf(Temp, "%s\\", ModelName[ModelID]);
	strcat(DataFileNameOk, Temp);
	strcat(DataFileNameOk, "data");
	
	if( SetDir(DataFileNameOk) )			//	Directory가 존재하지 않으면
		MakeDir(DataFileNameOk);				//	Directory생성

// Project Directory로 환원 Mc
	SetDir (PrjDirectory);
	strcat(DataFileNameOk, "\\");
	strcat(DataFileNameOk, DateStamp);
	
	strcpy(DataFileNameNg, DataFileNameOk);
	strcpy(DataFileNameAll, DataFileNameOk);
	strcpy(DataFileNameLFT,DataFileNameAll);
	strcpy(DataFileNameRGT,DataFileNameAll);
	
	
	strcat(DataFileNameOk, ".OK");
	strcat(DataFileNameNg, ".NG");
	strcat(DataFileNameAll, ".ALL");
	strcat(DataFileNameLFT, ".LFT");
	strcat(DataFileNameRGT, ".RGT");
}

void GetAutoSaveDataNum(void) // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
{
	int		fileHandle, i;
	long	fileSize, buffSize, currFilePtr;
	char	lineBuff[MAX_POINT * 17];
	

	Mc[0].Mode[0].CycleIndex = 0;
	McSPC[0].NG = McSPC[0].G = 0; // 합격, 불량 수량
	
	if( !GetFileInfo (DataFileNameAll, &fileSize) ) // file 이 존재하는지 확인
	{
		DataFileCreate();
		return ; // All file이 존재하지 않으면 다른것도 있을 수 없다.
	}

	fileHandle = OpenFile(DataFileNameAll,
								VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);

	for( i = 0; i < 7; i++ ) // head line num
	{
		ReadLine (fileHandle, lineBuff,-1);
	}

	ReadLine (fileHandle, lineBuff,-1);

	buffSize = strlen(lineBuff);
	if( buffSize > 10 ) // 적어도 10 이상은 되어야 데이터가 있다고 본다.
	{
		currFilePtr = SetFilePtr(fileHandle, 0L, 1); // 현재 포인터에서 0의 옵셋위치.
	
		currFilePtr = currFilePtr - (buffSize + 2); // 1라인을 읽었으므로 1라인 뒤로

		Mc[0].Mode[0].CycleIndex = (fileSize - currFilePtr) / (buffSize + 2); // 저장되어 있는 데이터의 수량.
	
		if( GetFileInfo (DataFileNameNg, &fileSize) ) // file 이 존재하는지 확인
		{
			if( fileSize > currFilePtr )
			{
				McSPC[0].NG = (fileSize - currFilePtr) / (buffSize + 2);
			}
		}

		if( GetFileInfo (DataFileNameOk, &fileSize) ) // file 이 존재하는지 확인
		{
			if( fileSize > currFilePtr )
			{
				McSPC[0].G = (fileSize - currFilePtr) / (buffSize + 2);
			}
		}
	}
	else
	{
		Mc[0].Mode[0].CycleIndex = 0;
		McSPC[0].G = McSPC[0].NG = 0;
	}
	
	CloseFile(fileHandle);
//	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Mc[0].Mode[0].CycleIndex );	// 전체 측정회수 표시
//  SetCtrlVal( mainpanel, MAINPANEL_LG, McSPC[0].G );
//	SetCtrlVal( mainpanel, MAINPANEL_LNG, McSPC[0].NG);
	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Total_cnt );	// 전체 측정회수 표시
	SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt );
	SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt);

}

void DataFileCreate(void)
{
	int		fileHandleAll, fileHandleOk, fileHandleNg, i, fileHandleLFT, fileHandleRGT;
	char	lineBuff[MAX_POINT * 17], ctemp[40], DateStamp[60];
	char	fmt[10];
	

	fileHandleAll = OpenFile(DataFileNameAll,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	fileHandleOk = OpenFile(DataFileNameOk,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	fileHandleNg = OpenFile(DataFileNameNg,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	fileHandleLFT = OpenFile(DataFileNameLFT,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	fileHandleRGT = OpenFile(DataFileNameRGT,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	

//	fileHandle = OpenFile(DataFile,
//								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	sprintf(ctemp, "%s", DateStr());
	MakeDateStr(DateStamp, ctemp);

	///////// 마약 아래부분을 수정한다면 GetAutoSaveDataNum() 함수에서 데이터 수량을 읽어오는 부분을
	///////// 수정해야할 수도 있슴.
/*
	sprintf(lineBuff, "Auto Measurement(%s) 전체 Data           ", DateStamp);
	WriteLine(fileHandleAll, lineBuff, -1);
	sprintf(lineBuff, "Auto Measurement(%s)  O.K Data           ", DateStamp);
	WriteLine(fileHandleOk, lineBuff, -1);
	sprintf(lineBuff, "Auto Measurement(%s)  N.G Data           ", DateStamp);
	WriteLine(fileHandleNg, lineBuff, -1);
*/
	sprintf(lineBuff,"Model  %s", ModelName[ModelID]);
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
	WriteLine (fileHandleLFT, lineBuff, -1);
	WriteLine (fileHandleRGT, lineBuff, -1);
	
//	WriteLine (fileHandle, lineBuff, -1);
	
	// 측정 Point수  Write
	sprintf(lineBuff,"Point_Num   %i", MeasPoints);   
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);

	sprintf(lineBuff,"Point_Num   %i", MeasPoints/2);   

	WriteLine (fileHandleLFT, lineBuff, -1);
	WriteLine (fileHandleRGT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    // 명칭
    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "NAME");
//    strcat(lineBuff, "    NAME"); // 8

    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
	// 계산식 이름 저장
	for( i = 0; i < MeasPoints; i++)
	{
		if( strlen(Model[i].Name) > 14 )
		{
			strncpy(ctemp, Model[i].Name, 14);
			ctemp[14] = 0;
		}
		else
			strcpy(ctemp, Model[i].Name);
		
		sprintf(DateStamp, fmt, ctemp);
		strcat(lineBuff, DateStamp);
	}
	
    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
	sprintf(DateStamp, fmt, "Time   ");
	strcat(lineBuff, DateStamp); // 12, 시간

    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "Operator    ");
    strcat(lineBuff, DateStamp);;	// 14, 작업자

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "TUBE BARCODE        ");
    strcat(lineBuff, DateStamp);;	// marking data

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "SHAFT BARCODE       ");
    strcat(lineBuff, DateStamp);;	// marking data

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
	sprintf(DateStamp, fmt, "OK/NG");
	strcat(lineBuff, DateStamp); // 12, 시간
	
	
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
//	WriteLine (fileHandleLFT, lineBuff, -1);
//	WriteLine (fileHandleRGT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "UNIT");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].Unit);
		strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "K.TOL");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].KindOfTol);
		strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "USL");
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W,  Model[i].Unit);
			
		sprintf(DateStamp, fmt, Model[i].PTol);
		strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "LSL");
	// Point별 LSL값 저장 
	for( i = 0; i < MeasPoints; i++)
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
		    
		sprintf(DateStamp, fmt, Model[i].NTol);
		strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleAll, lineBuff, -1);
	WriteLine (fileHandleOk, lineBuff, -1);
	WriteLine (fileHandleNg, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);
	
	
	
	
	////////////left data file
    // 명칭
    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "NAME");
//    strcat(lineBuff, "    NAME"); // 8

    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
	// 계산식 이름 저장
	for( i = 0; i < MeasPoints; i++)
	{
		
		if( strlen(Model[i].Name) > 14 )
		{
			strncpy(ctemp, Model[i].Name, 14);
			ctemp[14] = 0;
		}
		else
			strcpy(ctemp, Model[i].Name);
		
		sprintf(DateStamp, fmt, ctemp);
		
		if(Model[i].Sig==1 || Model[i].Sig==2)
			strcat(lineBuff, DateStamp);
	}
	
    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
	sprintf(DateStamp, fmt, "Time   ");
	strcat(lineBuff, DateStamp); // 12, 시간

    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "Operator    ");
    strcat(lineBuff, DateStamp);;	// 14, 작업자

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "TUBE BARCODE        ");
    strcat(lineBuff, DateStamp);;	// marking data

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "SHAFT BARCODE       ");
    strcat(lineBuff, DateStamp);;	// marking data

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
	sprintf(DateStamp, fmt, "OK/NG");
	strcat(lineBuff, DateStamp); // 12, 시간
	
	
	WriteLine (fileHandleLFT, lineBuff, -1);
	
    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "UNIT");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].Unit);
		if(Model[i].Sig==1 || Model[i].Sig==2)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleLFT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "K.TOL");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].KindOfTol);
		if(Model[i].Sig==1 || Model[i].Sig==2)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleLFT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "USL");
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W,  Model[i].Unit);
			
		sprintf(DateStamp, fmt, Model[i].PTol);
		if(Model[i].Sig==1 || Model[i].Sig==2)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleLFT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "LSL");
	// Point별 LSL값 저장 
	for( i = 0; i < MeasPoints; i++)
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
		    
		sprintf(DateStamp, fmt, Model[i].NTol);
		if(Model[i].Sig==1 || Model[i].Sig==2)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleLFT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);
	
	
	

	////////////////
	////////////right data file
    // 명칭
    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "NAME");
//    strcat(lineBuff, "    NAME"); // 8

    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
	// 계산식 이름 저장
	for( i = 0; i < MeasPoints; i++)
	{
		
		if( strlen(Model[i].Name) > 14 )
		{
			strncpy(ctemp, Model[i].Name, 14);
			ctemp[14] = 0;
		}
		else
			strcpy(ctemp, Model[i].Name);
		
		sprintf(DateStamp, fmt, ctemp);
		
		if(Model[i].Sig==3 || Model[i].Sig==4)
			strcat(lineBuff, DateStamp);
	}
	
    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
	sprintf(DateStamp, fmt, "Time   ");
	strcat(lineBuff, DateStamp); // 12, 시간

    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "Operator    ");
    strcat(lineBuff, DateStamp);;	// 14, 작업자

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "TUBE BARCODE        ");
    strcat(lineBuff, DateStamp);;	// marking data

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "SHAFT BARCODE       ");
    strcat(lineBuff, DateStamp);;	// marking data

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
	sprintf(DateStamp, fmt, "OK/NG");
	strcat(lineBuff, DateStamp); // 12, 시간
	
	
	WriteLine (fileHandleRGT, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "UNIT");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].Unit);
		if(Model[i].Sig==3 || Model[i].Sig==4)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleRGT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "K.TOL");
    
    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		sprintf(DateStamp, fmt, Model[i].KindOfTol);
		if(Model[i].Sig==3 || Model[i].Sig==4)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleRGT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "USL");
	for( i = 0; i < MeasPoints; i++)								// Point별 USL값 저장 
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W,  Model[i].Unit);
			
		sprintf(DateStamp, fmt, Model[i].PTol);
		if(Model[i].Sig==3 || Model[i].Sig==4)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleRGT, lineBuff, -1);
//	WriteLine (fileHandle, lineBuff, -1);

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
    sprintf(lineBuff, fmt, "LSL");
	// Point별 LSL값 저장 
	for( i = 0; i < MeasPoints; i++)
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
		    
		sprintf(DateStamp, fmt, Model[i].NTol);
		if(Model[i].Sig==3 || Model[i].Sig==4)
			strcat(lineBuff, DateStamp);
	}
	
	WriteLine (fileHandleRGT, lineBuff, -1);

	////////////////

	
	
	
	

	CloseFile(fileHandleAll);
	CloseFile(fileHandleOk);
	CloseFile(fileHandleNg);
	CloseFile(fileHandleLFT);
	CloseFile(fileHandleRGT);
//	CloseFile(fileHandle);
	Total_cnt=Ok_cnt=Ng_cnt = 0;
	
	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LG, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LNG, 0);
		
	L_TotalNo = L_Ok = L_Ng = R_TotalNo = R_Ok = R_Ng = 0;
	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO_2, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LG_2, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LNG_2, 0);

	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO_3, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LG_3, 0);
	SetCtrlVal( mainpanel, MAINPANEL_LNG_3, 0);
		
	Zero_Master_Flag = 0;
//	Check_Master_Flag = 0;
}

void	MakeDateStr(char *Dstr, const char *Sstr)
{
	CopyBytes(Dstr, 0, Sstr, 6, 4);				//	년
	CopyBytes(Dstr, 5, Sstr, 0, 2);				//	월
	CopyBytes(Dstr, 8, Sstr, 3, 2);				//	일
	CopyBytes(Dstr, 4, "-", 0, 1);
	CopyBytes(Dstr, 7, "-", 0, 1);
	Dstr[10] = 0x00;
}

void 	delOldFile(void)
{
    char File_Name[512];
    int  FileMonth, FileDay, FileYear;
    char dateStr[30],DateStamp[30];
    int  Month, Day, Year, StoreValidDay;
    double FileTotalDay, TotalDay;
    								 
	AllTimerStart(0);
    GetCtrlVal(interdata, INTPANEL_STOREVALIDDAY1, &StoreValidDay);
    
// 현재 날짜 및 시간 가져 오기   
    strcpy (dateStr,DateStr());
								 
//  현제 날짜 계산 
   	CopyBytes(DateStamp, 0, dateStr, 6, 4);  // Year
   	DateStamp[4]=0x00;
   	Scan(DateStamp,"%s>%i",&Year);
   	
	CopyBytes(DateStamp, 0, dateStr, 0, 2);  // Month
	DateStamp[2]=0x00;
	Scan(DateStamp,"%s>%i",&Month);
	
	CopyBytes(DateStamp, 0, dateStr, 3, 2);  // Day
	DateStamp[2]=0x00;
	Scan(DateStamp,"%s>%i",&Day);
	
	TotalDay= (double)(Year*365 + ((Month-1)*30) + Day);  

	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\HISTORY");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
	}
	else
	{
		if( GetFirstFile ("*.*", 1, 0, 0, 0, 0, 0, File_Name) == 0 )
		{	    
		    do{
		        if(GetFileDate (File_Name, &FileMonth, &FileDay,&FileYear) == 0)
		        {
		           FileTotalDay =(double)( FileYear*365 + ((FileMonth-1)*30) + FileDay );
		           if(FileTotalDay < TotalDay-StoreValidDay)
		           {
		              DeleteFile (File_Name);
		           }   
		        }
		    } while(GetNextFile (File_Name)==0);
		}
	}
    
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		AllTimerStart(1);
		return ;								//	Data Recall 취소
	}

	if( GetFirstFile ("*.*", 1, 0, 0, 0, 0, 0, File_Name) != 0)
	{
		AllTimerStart(1);
	    return ;
	}
	    
    do{
        if(GetFileDate (File_Name, &FileMonth, &FileDay,&FileYear)==0)
        {
           FileTotalDay =(double)( FileYear*365 + ((FileMonth-1)*30) + FileDay );
           if(FileTotalDay < TotalDay-StoreValidDay)
           {
              DeleteFile (File_Name);
           }   
        }
    }while(GetNextFile (File_Name)==0); 
    
	SetDir (PrjDirectory);
	AllTimerStart(1);
    return;
}

// 측정값 저장   NewFileName : 새로저장할 파일 Name,    typeFlag :  결과저장 유무 0-측정값만,  1-통계값포함 
void saveAsFile( int startPos, int measNum, char* NewFileName, int typeFlag )
{												    
  char lineBuffer[MAX_POINT * 14], tempBuffer[512];
  int  i, j, SpcMode;
  int  hFile;
	char	fmt[15];
  
  double maxValue, minValue, tirValue, meanValue, sigmaValue;
  int		maxIndex, minIndex;
  double	UpperNPL, LowerNPL, CpU, CpL, Cp, Cpk, Cpkm, FNC, UpperFNC, LowerFNC;
//int     SpcMode;

  if(startPos <= 1)
      startPos = 1;
 
  
  //calculating the number of rows and columns in DATA table
  if( startPos+measNum-1 > dataObj.measNum)
        measNum = dataObj.measNum-startPos+1;
  
   
  if( measNum <= 0 || dataObj.measPointNum <= 0 )
  {
       MessagePopup ("DATA VIEW ERROR!",
					  "No data is found or \n out of the range of measure data");
	   return;	   
  }				   
  
  if((hFile = OpenFile (NewFileName, VAL_READ_WRITE, VAL_TRUNCATE,
						VAL_ASCII)) == -1)
  {
	  sprintf(tempBuffer," FILE OPEN ERROR CODE : %d",GetFmtIOError);
	  ConfirmPopup ("FILE OPEN ERROR !", tempBuffer);
	  return ;
  }
			
  //	1  VAL_EXISTING_FILE_SELECTED
  //	2  VAL_NEW_FILE_SELECTED	
	
  	//Printing Data
  	if(typeFlag)
  	{
  	   sprintf(lineBuffer,"FILE : %s",dataObj.fileName);  // File
  	   WriteLine (hFile, lineBuffer, -1);
//  	   sprintf(lineBuffer,"TITLE : %s",dataObj.title);  // Title
  //	   WriteLine (hFile, lineBuffer, -1);
  	   sprintf(lineBuffer,"MODEL :  %s",dataObj.model);  // Model
  	   WriteLine (hFile, lineBuffer, -1);
  	   sprintf(lineBuffer,"POINT_NUM :  %d",dataObj.measPointNum);  // Point Numle
  	   WriteLine (hFile, lineBuffer, -1);
  	}
  	else
  	{
  	   sprintf(lineBuffer,"%s",dataObj.fileName);  // Title
  	   WriteLine (hFile, lineBuffer, -1);
  	   sprintf(lineBuffer,"MODEL  %s",dataObj.model);  // Model
  	   WriteLine (hFile, lineBuffer, -1);
  	   sprintf(lineBuffer,"POINT_NUM  %d",dataObj.measPointNum);  // Point Numle
  	   WriteLine (hFile, lineBuffer, -1); 
  	}
  
  	lineBuffer[0]=0;
  	strcat(lineBuffer, "        NAME"); 
  	// 계산식 이름 저장
	for( i=0; i< dataObj.measPointNum + 2;i++)
 	{   
  	    sprintf(tempBuffer,"%12s", dataObj.pointName[i]);
	 	strcat(lineBuffer, tempBuffer);
  	}
    WriteLine (hFile, lineBuffer, -1); 

    lineBuffer[0]=0;
  	// UPPER 이름 Print
  	strcat(lineBuffer, "       UPPER");
  	// Point별 UPPER값 Print

	for( i=0; i< dataObj.measPointNum;i++) 
  	{
//		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
		sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);

		sprintf(tempBuffer, fmt , dataObj.tolValue[0][i]);

	
//	sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], dataObj.tolValue[0][i]);
 		strcat(lineBuffer, tempBuffer);
  	}
  	WriteLine (hFile, lineBuffer, -1);  
  
    lineBuffer[0]=0;
  	// DOWNER 이름 Print
  	strcat(lineBuffer, "       LOWER");
  	// Point별 DOWNER값 Print 
	for( i=0; i< dataObj.measPointNum;i++)  
  	{
 
		sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
		sprintf(tempBuffer, fmt , dataObj.tolValue[1][i]);

//	sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], dataObj.tolValue[1][i]);
 		strcat(lineBuffer, tempBuffer);
  	}
  	WriteLine (hFile, lineBuffer, -1);  
  
  	for( j=startPos ; j<startPos+measNum ; j++)
  	{
     	lineBuffer[0]=0;
  	 	sprintf(lineBuffer,"%12d", j);

			for( i=0; i< dataObj.measPointNum + 2;i++) 
  	 	{
  	 		if( i < dataObj.measPointNum )
  	 		{
				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , dataObj.measVal[i][j-1]);

//		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], dataObj.measVal[i][j-1]);
       		}
       		else if( i == dataObj.measPointNum )
       			sprintf(tempBuffer,"%12s", dataObj.Time[j-1]);
       		else
       			sprintf(tempBuffer,"%12s", dataObj.Operater[j-1]);
       		strcat(lineBuffer, tempBuffer);
     	}
    	WriteLine (hFile, lineBuffer, -1);
  	} 

  	if( typeFlag == 0)
  	{
  	    CloseFile (hFile); 
  	    return;
  	}
  	
// To print results 

	WriteLine (hFile,"   ",-1);   //New Line
	
    lineBuffer[0]=0;
    // MAX 이름 print
  	strcat(lineBuffer, "         MAX");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
   		//최대및 최소 , Range계산
   		MaxMin1D (&dataObj.measVal[i][startPos-1],
             		measNum, &maxValue, &maxIndex, &minValue,
			 		&minIndex);

				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , maxValue);


//		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], maxValue);
   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1); 

    lineBuffer[0]=0;
    //MIN 이름 print
  	strcat(lineBuffer, "         MIN");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
   		//최대및 최소 , Range계산
   		MaxMin1D (&dataObj.measVal[i][startPos-1],
             		measNum, &maxValue, &maxIndex, &minValue,
			 		&minIndex);

				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , minValue);

//		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], minValue);
   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);
	
	lineBuffer[0]=0;
    //TIR 이름 print
  	strcat(lineBuffer, "         TIR");   
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
   		//최대및 최소 , Range계산
   		MaxMin1D (&dataObj.measVal[i][startPos-1],
             		measNum, &maxValue, &maxIndex, &minValue,
			 		&minIndex);
		tirValue = maxValue - minValue;	 		
		
				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , tirValue);

//		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i],tirValue);
   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);
	
	lineBuffer[0]=0;
    //AVR 이름 print
  	strcat(lineBuffer, "     AVERAGE");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
   		//평균, 표준편차계산
        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
						  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
						  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		
 
				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , tirValue);

//		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], meanValue);
   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);
	
	lineBuffer[0]=0;
    //SIGMA 이름 print
  	strcat(lineBuffer, "       SIGMA");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
   		//평균, 표준편차계산
        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
						  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
						  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		

				sprintf(fmt,"%%%d.%df",12,dataObj.Unit[i]);
				sprintf(tempBuffer, fmt , sigmaValue);
		
//	   		sprintf(tempBuffer,"%%%d.%df",12,dataObj.Unit[i], sigmaValue);
   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);
	
	lineBuffer[0]=0;
    //Cp 이름 print
  	strcat(lineBuffer, "          Cp");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);

	      SpcSigma = 6;
		  if( dataObj.KindOfTol[i] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
	      
	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][i],
									   dataObj.tolValue[1][i], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;

   		    sprintf(tempBuffer,"%12.2f",Cp);
	   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);

	lineBuffer[0]=0;
    //Ckp 이름 print
  	strcat(lineBuffer, "         Cpk");
	for( i=0; i< dataObj.measPointNum;i++) 
    { 
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);

	      SpcSigma = 6;
		  if( dataObj.KindOfTol[i] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
	      
	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][i],
									   dataObj.tolValue[1][i], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;

   		    sprintf(tempBuffer,"%12.2f",Cpk);
	   		strcat(lineBuffer,tempBuffer);
	}
	WriteLine (hFile, lineBuffer, -1);

  	CloseFile (hFile); 

  return;
  
}

void	UserMessageBox(int panel, int time, int fore, int back, char *str, int	reset, int modalStat)
{
	int	textSize = 40;
	int	panelh, panelw, MessageStrLen;
//	int	itemp;
		
	if( !reset )
	{
		if( UserModalFlag )
			RemovePopup(0); // modal => modeless
		HidePanel(msgpanel);
		UserModalFlag = 0;
		return;
	}

	MessageStrLen = strlen(str);
	GetPanelAttribute(panel, ATTR_HEIGHT, &panelh);
	GetPanelAttribute(panel, ATTR_WIDTH, &panelw);
	
	if( panelw < (MessageStrLen * textSize / 2) )
		textSize = panelw * 2 / MessageStrLen;
		
	SetPanelAttribute (msgpanel, ATTR_HEIGHT, textSize);
	if( modalStat )
		SetPanelAttribute (msgpanel, ATTR_WIDTH, (MessageStrLen + 1) * textSize / 2);
	else
		SetPanelAttribute (msgpanel, ATTR_WIDTH, MessageStrLen * textSize / 2);
	SetPanelAttribute(msgpanel, ATTR_TOP, VAL_AUTO_CENTER);
	SetPanelAttribute(msgpanel, ATTR_LEFT, VAL_AUTO_CENTER);
	SetPanelAttribute(msgpanel, ATTR_TITLEBAR_VISIBLE, 0);
	
	if( modalStat ) // modal
	{
		InstallPopup( msgpanel );
		UserModalFlag = 1;
	}
	
	GetPanelAttribute (msgpanel, ATTR_HEIGHT, &panelh);
	GetPanelAttribute (msgpanel, ATTR_WIDTH, &panelw);
	
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TOP, 0);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_LEFT, 0);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_HEIGHT, panelh);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_WIDTH, panelw);
	
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TEXT_BOLD, 1);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TEXT_POINT_SIZE, textSize);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TEXT_COLOR, fore);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TEXT_BGCOLOR, back);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_TEXT_RAISED, 1);
	SetCtrlAttribute(msgpanel, MSGPANEL_TEXTMSG, ATTR_VISIBLE,1 ); 
	
	SetCtrlVal (msgpanel, MSGPANEL_TEXTMSG , str );
	
	DisplayPanel (msgpanel);
	
	if( time != 0 ) // ON/OFF
	{
		ResetTimer(msgpanel, MSGPANEL_TIMER);
		SetCtrlAttribute(msgpanel, MSGPANEL_TIMER, ATTR_INTERVAL, time / 1000.);
		SetCtrlAttribute(msgpanel, MSGPANEL_TIMER, ATTR_ENABLED, TRUE);
	}
}

/*
int		UserMessageCtrlID = 0, UserMessagePanelID = 0;
void	UserMessageBox(int panel, int time, int fore, int back, char *str, int	reset, int modalStat)
{
	int	textSize = 40;
	int	panelh, panelw, MessageStrLen;
//	int	itemp;
		
	if( !reset && UserMessagePanelID == 0 )
		return;

	if( UserMessagePanelID != 0 )
	{
		if( UserModalFlag )
		{
			RemovePopup(0); // modal => modeless
			UserModalFlag = 0;
		}
		
//		DiscardCtrl( OldPanel, UserMessageCtrlID );
		DiscardPanel( UserMessagePanelID );
		UserMessagePanelID = UserMessageCtrlID = 0;
		return;
	}

	MessageStrLen = strlen(str);
	GetPanelAttribute (panel, ATTR_HEIGHT, &panelh);
	GetPanelAttribute (panel, ATTR_WIDTH, &panelw);
	
	if( panelw < (MessageStrLen * textSize / 2) )
		textSize = panelw * 2 / MessageStrLen;
		
	UserMessagePanelID = NewPanel(0, "", VAL_AUTO_CENTER, VAL_AUTO_CENTER, textSize, MessageStrLen * textSize / 2);
//	SetPanelAttribute (UserMessagePanelID, ATTR_TITLEBAR_VISIBLE, 0);
//	SetPanelAttribute (UserMessagePanelID, ATTR_TITLEBAR_VISIBLE, 0);
	
	if( modalStat ) // modal
	{
		InstallPopup( UserMessagePanelID );
		UserModalFlag = 1;
	}
	
	UserMessageCtrlID = NewCtrl(UserMessagePanelID, CTRL_TEXT_MSG, "ONCALULATION", 0, 0); 
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_TEXT_BOLD, 1);
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_TEXT_POINT_SIZE, textSize);
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_TEXT_COLOR, fore);
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_TEXT_BGCOLOR, back);
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_TEXT_RAISED, 1);
	SetCtrlAttribute(UserMessagePanelID, UserMessageCtrlID, ATTR_VISIBLE,1 ); 
	
	SetCtrlVal (UserMessagePanelID, UserMessageCtrlID , str );
//	SetCtrlAttribute (panel, UserMessageCtrlID, ATTR_TOP, ctrlT);
//	SetCtrlAttribute (panel, UserMessageCtrlID, ATTR_LEFT, ctrlL);
//	GetCtrlAttribute (panel, UserMessageCtrlID, ATTR_HEIGHT, &itemp);
//	GetCtrlAttribute (panel, UserMessageCtrlID, ATTR_WIDTH, &itemp);
	
	if( time != 0 ) // ON/OFF
	{
		AllTimerStart(0); // amp, plc timer error cancel
		SleepFunc(time);
		if( UserModalFlag )
		{
			RemovePopup(0); // modal => modeless
			UserModalFlag = 0;
		}
//		DiscardCtrl( OldPanel, UserMessageCtrlID );
		DiscardPanel( UserMessagePanelID );
		UserMessagePanelID = UserMessageCtrlID = 0;
		AllTimerStart(1);
	}
}

void	UserMessageBox(int panel, int time, int fore, int back, char *str, int	reset, int modalStat)
{
	int	textSize = 40, ctrlL, ctrlT;
	int	panelh, panelw, MessageStrLen;
//	int	itemp;
		
	if( !reset && UserMessageCtrlID == 0 )
		return;

	if( UserMessageCtrlID != 0 )
	{
		if( UserModalFlag )
		{
			RemovePopup(0); // modal => modeless
			UserModalFlag = 0;
		}
		
		DiscardCtrl( OldPanel, UserMessageCtrlID );
//		int DiscardPanel (int panelHandle);
		UserMessageCtrlID = 0;
		return;
	}

	MessageStrLen = strlen(str);
	GetPanelAttribute (panel, ATTR_HEIGHT, &panelh);
	GetPanelAttribute (panel, ATTR_WIDTH, &panelw);
	
	if( panelw < (MessageStrLen * textSize / 2) )
		textSize = panelw * 2 / MessageStrLen;
		
	ctrlL = (panelw - MessageStrLen * textSize / 2) / 2;
	ctrlT = (panelh - textSize) / 2;
	
	if( modalStat ) // modal
	{
		InstallPopup( panel );
		UserModalFlag = 1;
	}
//	int NewPanel (int parentPanelHandle, char panelTitle[], int panelTop, int panelLeft, int panelHeight, int panelWidth);
	UserMessageCtrlID = NewCtrl(panel, CTRL_TEXT_MSG, "ONCALULATION", ctrlT, ctrlL); 
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_TEXT_BOLD, 1);
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_TEXT_POINT_SIZE, textSize);
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_TEXT_COLOR, fore);
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_TEXT_BGCOLOR, back);
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_TEXT_RAISED, 1);
	SetCtrlAttribute(panel, UserMessageCtrlID, ATTR_VISIBLE,1 ); 
	OldPanel = panel;
	
	SetCtrlVal (panel, UserMessageCtrlID , str );
//	SetCtrlAttribute (panel, UserMessageCtrlID, ATTR_TOP, ctrlT);
//	SetCtrlAttribute (panel, UserMessageCtrlID, ATTR_LEFT, ctrlL);
//	GetCtrlAttribute (panel, UserMessageCtrlID, ATTR_HEIGHT, &itemp);
//	GetCtrlAttribute (panel, UserMessageCtrlID, ATTR_WIDTH, &itemp);
	
	if( time != 0 ) // ON/OFF
	{
		AllTimerStart(0); // amp, plc timer error cancel
		SleepFunc(time);
		if( UserModalFlag )
		{
			RemovePopup(0); // modal => modeless
			UserModalFlag = 0;
		}
		DiscardCtrl( OldPanel, UserMessageCtrlID );
		UserMessageCtrlID = 0;
		AllTimerStart(1);
	}
}
*/
void	DataFileChange(void) // 계산식에서 측정항목 수량이 변경됨.
{
	int		i;
	char	ctemp[256]; // maxpathlength
	long	fileSize;

	GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.

	if( Mc[0].Mode[0].CycleIndex != 0 ) // 기존에 있던 파일을 다른 이름으로 변경
	{
		strcpy(WorkingDirectory, DataFileNameAll);
		WorkingDirectory[strlen(WorkingDirectory) - 4] = 0; // ".ALL"을 삭제
		
		for( i = 0; i < 10; i++ )
		{
			sprintf(ctemp, "%s-%02d.ALL", WorkingDirectory, i);
			if( !GetFileInfo(ctemp, &fileSize) ) // file이 존재하지 않으면
				break;
		}
		
		if( i < 10 )
		{
			DirRenameFunc(DataFileNameAll, ctemp );
			ctemp[strlen(ctemp) - 3] = 0;
			strcat(ctemp, "OK");
			DirRenameFunc(DataFileNameOk, ctemp );
			ctemp[strlen(ctemp) - 2] = 0;
			strcat(ctemp, "NG");
			DirRenameFunc(DataFileNameNg, ctemp );
		}
	}
/*
	if( Mc[0].Mode[0].CycleIndex != 0 ) // 기존에 있던 파일을 다른 이름으로 변경
	{
		strcpy(WorkingDirectory, DataFile);
		WorkingDirectory[strlen(WorkingDirectory) - 4] = 0; // ".ALL"을 삭제
		
		for( i = 0; i < 10; i++ )
		{
			sprintf(ctemp, "%s-%02d.ALL", WorkingDirectory, i);
			if( !GetFileInfo(ctemp, &fileSize) ) // file이 존재하지 않으면
				break;
		}
		
		if( i < 10 )
		{
			DirRenameFunc(DataFile, ctemp );
		}

	
	}
*/	
	DataFileCreate(); // 다시 파일을 만듦.
}

void	FR_SpaceDelFunc(char *str)
{
	int		index, length, i;
	char	ctemp[256];
	
	length = strlen(str);
	if( length < 1 )	return;
	
	index = length - 1;
	while( str[index] == ' ' )
	{
		str[index--] = 0; // 뒤의 공백을 제거
		if( index < 0 ) return;
	}
		
	for(i = 0; i < length; i++)
	{
		if( str[i] != ' ' ) // 앞의 공백을 제거하기 위한
		{
			index = i;
			break;
		}
	}
	
	strcpy(ctemp, &str[index]);
	strcpy(str, ctemp);
}

void  FileReName( void )
{
	char	TempStr1[256], TempStr2[256];
	int		i;

	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA\\senval.");

	sprintf(TempStr1, "%sDA9", WorkingDirectory );
	DeleteFile(TempStr1);

	for( i = 9; i > 0; i-- )
	{
		sprintf(TempStr1, "%sDA%d", WorkingDirectory, (i - 1));
		sprintf(TempStr2, "%sDA%d", WorkingDirectory, i);
		DirRenameFunc(TempStr1, TempStr2 );
	}
}

//double		RepeatChVal[MAX_ACQ_CH_PER_CYCLE][MAX_CH_SIG][MAX_CH];
//double		(*ChVal)[MAX_CH];
//int			RepeatChIndex;
void JSenValSave(void)
{
	int		i, j, k, no;
	int		fileHandle;
	char	lineBuff[MAX_CH * 13], ctemp[30], ctemp1[30];
	double	data[50], Sort_data[50], sep;
	double		Max, Min,Mean;
	int			MaxIndex, MinIndex;
	double		ChVal_720[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
	FileReName(); // 
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA\\senval.da0");
	fileHandle = OpenFile(WorkingDirectory,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	strcpy(lineBuff, "**** 측정용 센서값 저장 ****");
	WriteLine(fileHandle, lineBuff, -1);

	// 센서값 읽음 횟수 저장
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", "센서읽은 수량:");
	strcat(lineBuff, ctemp1);
	
	sprintf(ctemp, "Sig1: %d", RepeatChIndex);
	sprintf(ctemp1, "%12s", ctemp);
	strcat(lineBuff, ctemp1);
	WriteLine(fileHandle, lineBuff, -1);
	
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", " ");
	strcat(lineBuff, ctemp1);
	
	for( j = 0; j < DISP_CH;j++ )
	{
		sprintf(ctemp, "CH%d", j + 1);
		sprintf(ctemp1, "%12s", ctemp);
		strcat(lineBuff, ctemp1);
	}
	
	WriteLine(fileHandle, lineBuff, -1);
		
		for(k = 0; k < 2; k++)
		{		
			for( i = 0; i < RepeatChIndex; i++ ) // 
			{
				if(RepeatChVal[i][k] >20.0)
					RepeatChVal[i][k] = RepeatChVal[i-1][k];
				else if(RepeatChVal[i][k] <-20.0)
					RepeatChVal[i][k] = RepeatChVal[i-1][k];
		
			}
		}
		
		

/////filter
	if(Filter_Flag)
	{
		for(k = 0; k < 2; k++)
		{		
			for( i = 0; i < RepeatChIndex-Filter_Cnt; i++ ) // 
			{
				for( j = 0; j < Filter_Cnt; j++ ) // 
					data[j] = RepeatChVal[i+j][k];

				
				Sort(data, Filter_Cnt, 0, Sort_data);

//				MaxMin1D(data,Filter_Cnt , &Max, &MaxIndex, &Min, &MinIndex);
				Mean = 0.0;
			
				for( j = Filter_L; j < (Filter_Cnt-Filter_H); j++ ) // 
				{
						Mean = Mean+Sort_data[j];  
				}
//					Mean = Mean-Max-Min;
					RepeatChVal[i][k] = Mean/(Filter_Cnt-(Filter_H+Filter_L)) ;
		
			}
		}
	
//	RepeatChIndex = RepeatChIndex-Filter_Cnt;	
	
	}		
/////filter
	if(Filter_Flag)
	{
		for(k = 0; k < 2; k++)
		{		
			for( i = 0; i < RepeatChIndex-Filter_Cnt; i++ ) // 
			{
				for( j = 0; j < Filter_Cnt; j++ ) // 
					data[j] = RepeatChVal[i+j][k];

				
				Sort(data, Filter_Cnt, 0, Sort_data);

//				MaxMin1D(data,Filter_Cnt , &Max, &MaxIndex, &Min, &MinIndex);
				Mean = 0.0;
			
				for( j = Filter_L; j < (Filter_Cnt-Filter_H); j++ ) // 
				{
						Mean = Mean+Sort_data[j];  
				}
//					Mean = Mean-Max-Min;
					RepeatChVal[i][k] = Mean/(Filter_Cnt-(Filter_H+Filter_L)) ;
		
			}
		}
	
//	RepeatChIndex = RepeatChIndex-Filter_Cnt;	
	
	}		

	
	
	
	

	/*
Enc_Init = RepeatChVal[0][4];

		for( i = 1; i < RepeatChIndex; i++ ) // 
		{
			if(RepeatChVal[i][4] >= (Enc_Init+360.0))
			{
				RepeatChIndex = i;	
				break;
			}
		
		}
*/	
/*	
	if(GSt1Sig == 1 || GSt1Sig == 2)
	{
	
	//0.5도 단위로 연산	
		sep = (double)RepeatChIndex/720.0;

	
		for( i = 0; i < 720; i++ ) // 
		{
		
			for(k = 0; k < DISP_CH; k++)
			{
				no = (int)(i*sep);
				ChVal_720[i][k] = RepeatChVal[no][k];
			}
		}
	
		for( i = 0; i < 720; i++ ) // 
		{
		
			for(k = 0; k < DISP_CH; k++)
			{
				RepeatChVal[i][k] = ChVal_720[i][k];
			}
		}
 	
		RepeatChIndex= 720;
	}

	RepeatChIndex= 720;
*/	
		if(GSt1Sig==1 || GSt1Sig ==3)
		{
			sep = (51.0-0.0)/(double)RepeatChIndex;
			for(i=0;i< RepeatChIndex;i++)
				RepeatChVal[i][2] = 0.0 +(sep*i);
			
			sep = (51.0-0.0)/(double)RepeatChIndex;
			for(i=0;i< RepeatChIndex;i++)
				RepeatChVal[i][3] = 0.0 +(sep*i);
		}
		else
		{
			sep = (0.0-51.0)/(double)RepeatChIndex;
			for(i=0;i< RepeatChIndex;i++)
				RepeatChVal[i][2] = 51.0 +(sep*i);
			sep = (0.0-51.0)/(double)RepeatChIndex;
			for(i=0;i< RepeatChIndex;i++)
				RepeatChVal[i][3] = 51.0 +(sep*i);
			
			
		}
		
		
	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		
		
		for(k = 0; k < 4; k++)
		{
			RepeatChValBase[i][k]=RepeatChVal[i][k];
		}
	}
			
	RepeatChIndexBase = RepeatChIndex;
	
	
	for( i = 0; i < RepeatChIndexBase; i++ ) // 
		{
			lineBuff[0] = 0;
			sprintf(ctemp1, "%12d", i + 1);
			strcat(lineBuff, ctemp1);
		
			for(k = 0; k < DISP_CH; k++)
			{
				sprintf(ctemp1, "%12.2f", RepeatChVal[i][k]);
				strcat(lineBuff, ctemp1);
			}
			WriteLine(fileHandle, lineBuff, -1);
		}


	CloseFile(fileHandle);

}

void	AllTimerStart(char flag)
{
	if( flag )
	{
	//	날짜시간 Update Timer Enable, 현재 타이머 카운터 리셋
		ResetTimer(mainpanel, MAINPANEL_DATETIME); 
		ResetTimer(mainpanel, MAINPANEL_PLCTIMER);
		ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
//		ResetTimer(mainpanel, MAINPANEL_ERRDISPTIMER);
		
		SetCtrlAttribute(mainpanel, MAINPANEL_DATETIME, ATTR_ENABLED, TRUE);
		SetCtrlAttribute(mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
		if( AmpRunFlag )
			SetCtrlAttribute(mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, TRUE);
//		SetCtrlAttribute(mainpanel, MAINPANEL_ERRDISPTIMER, ATTR_ENABLED, TRUE);
//		SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);
	}
	else
	{
	//	날짜시간 Update Timer Enable
//		SetCtrlAttribute(mainpanel, MAINPANEL_DATETIME, ATTR_ENABLED, FALSE);
//		SetCtrlAttribute(mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
		SetCtrlAttribute(mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
//		SetCtrlAttribute (mainpanel, MAINPANEL_LAN_TIMER, ATTR_ENABLED, FALSE); 
		
//		SetCtrlAttribute(mainpanel, MAINPANEL_ERRDISPTIMER, ATTR_ENABLED, FALSE);
//		SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, FALSE);
	}
}

void	ReadCalcData(void)
{
	int 	i, h_file, fileSize;

	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\Calc.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
		for( i = 0; i < MAX_EQU; i++ )
			ReadFile(h_file, (char *)&Pgm[i], sizeof(PGM));
	
		CloseFile( h_file );
    }
    else
    {
    	for( i = 0; i < MAX_EQU; i++ )
    	{
    		Pgm[i].Name[0] = 0;
    		Pgm[i].Equ[0] = 0;
    		Pgm[i].Unit = 0;
    		Pgm[i].Mode = 0;
    		Pgm[i].Disp = 0;
    		Pgm[i].Grp1 = 0;
    		Pgm[i].ST = 0;
    		Pgm[i].Gap = 0;
    		Pgm[i].Sig = 0;
    		Pgm[i].KindOfTol = 0;
    		Pgm[i].Comp = 0;
    		Pgm[i].NTol = 0;
    		Pgm[i].PTol = 0;
    		Pgm[i].Comp1 = 0;
    		Pgm[i].NCTol = 0;
    		Pgm[i].PCTol = 0;
    	}
    }
}
void 		View_MarkSet(void)
{
	
//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_1, Mark_OnOff[0]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_1, Mark_Type1[0]);

		if((Mark_Type1[0] != 4))//&& (Mark_Type1[0] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_1, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_1, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_1, Mark_Text[0]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_1, Mark_X[0]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_1, Mark_Y[0]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_1, Mark_Z[0]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_1, Mark_Rot[0]);
			
//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_2, Mark_OnOff[1]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_2, Mark_Type1[1]);

		if((Mark_Type1[1] != 4))// && (Mark_Type1[1] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_2, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_2, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_2, Mark_Text[1]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_2, Mark_X[1]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_2, Mark_Y[1]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_2, Mark_Z[1]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_2, Mark_Rot[1]);
			
//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_3, Mark_OnOff[2]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_3, Mark_Type1[2]);

		if((Mark_Type1[2] != 4))// && (Mark_Type1[2] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_3, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_3, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_3, Mark_Text[2]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_3, Mark_X[2]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_3, Mark_Y[2]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_3, Mark_Z[2]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_3, Mark_Rot[2]);
			
			
//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_4, Mark_OnOff[3]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_4, Mark_Type1[3]);

		if((Mark_Type1[3] != 4))// && (Mark_Type1[3] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_4, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_4, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_4, Mark_Text[3]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_4, Mark_X[3]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_4, Mark_Y[3]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_4, Mark_Z[3]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_4, Mark_Rot[3]);

//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_5, Mark_OnOff[4]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_5, Mark_Type1[4]);

		if((Mark_Type1[4] != 4))// && (Mark_Type1[4] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_5, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_5, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_5, Mark_Text[4]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_5, Mark_X[4]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_5, Mark_Y[4]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_5, Mark_Z[4]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_5, Mark_Rot[4]);

//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_6, Mark_OnOff[5]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_6, Mark_Type1[5]);

		if((Mark_Type1[5] != 4))// && (Mark_Type1[5] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_6, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_6, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_6, Mark_Text[5]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_6, Mark_X[5]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_6, Mark_Y[5]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_6, Mark_Z[5]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_6, Mark_Rot[5]);

//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_7, Mark_OnOff[6]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_7, Mark_Type1[6]);

		if((Mark_Type1[6] != 4))// && (Mark_Type1[6] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_7, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_7, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_7, Mark_Text[6]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_7, Mark_X[6]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_7, Mark_Y[6]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_7, Mark_Z[6]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_7, Mark_Rot[6]);

//////
		SetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_8, Mark_OnOff[7]) ;

		SetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_8, Mark_Type1[7]);

		if((Mark_Type1[7] != 4))// && (Mark_Type1[7] != 6))
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_8, ATTR_VISIBLE, 0);
		else
			SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_8, ATTR_VISIBLE, 1);
			
		
		SetCtrlVal(markpanel, MARK_SET_MARK_TEXT_8, Mark_Text[7]) ;
			
		SetCtrlVal(markpanel, MARK_SET_MARK_X_8, Mark_X[7]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Y_8, Mark_Y[7]) ;
		SetCtrlVal(markpanel, MARK_SET_MARK_Z_8, Mark_Z[7]) ;
		
		SetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_8, Mark_Rot[7]);

			
	
	
}

void 		Read_MarkSet(void)
{
	
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_1, &Mark_OnOff[0]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_2, &Mark_OnOff[1]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_3, &Mark_OnOff[2]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_4, &Mark_OnOff[3]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_5, &Mark_OnOff[4]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_6, &Mark_OnOff[5]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_7, &Mark_OnOff[6]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_ONOFF_8, &Mark_OnOff[7]) ;
	

		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_1, &Mark_Type1[0]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_2, &Mark_Type1[1]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_3, &Mark_Type1[2]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_4, &Mark_Type1[3]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_5, &Mark_Type1[4]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_6, &Mark_Type1[5]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_7, &Mark_Type1[6]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_8, &Mark_Type1[7]);
		

		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_1, Mark_Text[0]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_2, Mark_Text[1]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_3, Mark_Text[2]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_4, Mark_Text[3]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_5, Mark_Text[4]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_6, Mark_Text[5]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_7, Mark_Text[6]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_TEXT_8, Mark_Text[7]) ;
		
		GetCtrlVal(markpanel, MARK_SET_MARK_X_1, &Mark_X[0]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_1, &Mark_Y[0]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_1, &Mark_Z[0]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_2, &Mark_X[1]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_2, &Mark_Y[1]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_2, &Mark_Z[1]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_3, &Mark_X[2]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_3, &Mark_Y[2]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_3, &Mark_Z[2]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_4, &Mark_X[3]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_4, &Mark_Y[3]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_4, &Mark_Z[3]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_5, &Mark_X[4]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_5, &Mark_Y[4]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_5, &Mark_Z[4]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_6, &Mark_X[5]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_6, &Mark_Y[5]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_6, &Mark_Z[5]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_7, &Mark_X[6]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_7, &Mark_Y[6]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_7, &Mark_Z[6]) ;

		GetCtrlVal(markpanel, MARK_SET_MARK_X_8, &Mark_X[7]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Y_8, &Mark_Y[7]) ;
		GetCtrlVal(markpanel, MARK_SET_MARK_Z_8, &Mark_Z[7]) ;

		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_1, &Mark_Rot[0]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_2, &Mark_Rot[1]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_3, &Mark_Rot[2]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_4, &Mark_Rot[3]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_5, &Mark_Rot[4]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_6, &Mark_Rot[5]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_7, &Mark_Rot[6]);
		GetCtrlIndex ( markpanel, MARK_SET_MARK_ROT_8, &Mark_Rot[7]);
		

}

void	ReadModelVarData(void)
{
	int 	h_file, fileSize, i;
	char	lineBuff[200];
	char 	data[8][512];
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ModelVar.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE,VAL_ASCII);
	
			
		ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%i%i%i%i%i",&Total_cnt,&Ok_cnt,&Ng_cnt, &Mark_Cnt_No, &Line_Name);
		
		ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i",&Servo_Position[0],&Servo_Position[1],&Servo_Position[2],&Servo_Position[3],
						&Servo_Position[4],&Servo_Position[5],&Servo_Position[6],&Servo_Position[7],&Servo_Position[8],&Servo_Position[9],
						&Servo_Position[10],&Servo_Position[11],&Servo_Position[12],&Servo_Position[13],
						&Servo_Position[14],&Servo_Position[15],&Servo_Position[16],&Servo_Position[17],&Servo_Position[18],&Servo_Position[19],&Servo_Position[20]);

		for(i=0;i<8;i++)
		{
			ReadLine (h_file, lineBuff, -1); 
			Scan(lineBuff,"%s>%i%i%f%f%f%i",&Mark_OnOff[i],&Mark_Type1[i], &Mark_X[i], &Mark_Y[i], &Mark_Z[i], &Mark_Rot[i]);
		
			if(Mark_OnOff[i])
				Mark_Rot_No = i;
		
		}
		for(i=0;i<8;i++)
		{
			ReadLine (h_file, lineBuff, -1); 
			strcpy(Mark_Text[i],lineBuff);
			
//			Scan(lineBuff,"%s>%30s",Mark_Text[i]);
		}

		
		ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%i%i",&Zero_Master_Flag,&Check_Master_Flag);

				ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%f%f%f%f%f",&Shaft_Low,&Shaft_High,&Tube_Low,&Tube_High,&Retry_Data);

		ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%i%i%i%i%i%i",&L_TotalNo, &L_Ok, &L_Ng,&R_TotalNo, &R_Ok, &R_Ng);
			
					ReadLine (h_file, lineBuff, -1); 
		Scan(lineBuff,"%s>%f%f",&YaxisLow,&YaxisHigh);
		
		CloseFile( h_file );
		
		View_MarkSet();
/*		
		 if(MarkPortNo > 0)
		 {
			 SendMarkingDataLabel();
		 	Start_Mark = 0;
					MarkSend_No = 0;
//			Bar_Send_Flag = 1; 
		 }
*/		 
		 
		 
/*		 
		SetCtrlVal( interdata, INTPANEL_ROLLER_DIA, Roller_Dia);
		SetCtrlVal( interdata, INTPANEL_WORK_DIA, Work_Dia);
		SetCtrlVal( interdata, INTPANEL_NICK_COMP, Nick_Comp1[0] );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_2, Nick_Comp1[1] );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_3, Nick_Comp1[2] );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_4, Nick_Comp1[3] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE, Nick_Value[0] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE_2, Nick_Value[1] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE_3, Nick_Value[2] );
		SetCtrlVal( interdata, INTPANEL_NICK_CUT, Nick_Cut );
		SetCtrlVal( mainpanel, MAINPANEL_INWORK_COUNT, Inworkcount );
	SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_1, A_Low[0]);
	SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_2, A_Low[1]);
	SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_3, A_Low[2]);
	SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_1, A_High[0]);
	SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_2, A_High[1]);
	SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_3, A_High[2]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_LOW_1, M_Low[0]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_LOW_2, M_Low[1]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_LOW_3, M_Low[2]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_1, M_High[0]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_2, M_High[1]);
	SetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_3, M_High[2]);
*/	
//	SetCtrlVal(mainpanel, MAINPANEL_WORK_MODEL_CHAR, Model_Char);
	SetCtrlVal(mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);
//	SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR, Model_Char);

	SetCtrlIndex ( mainpanel, MAINPANEL_OPERATE_NO, Line_Name-1);
/*	
		if(!ByPassFlag3)
		{

			
			if(Check_Master_Flag)
			{
				SetCtrlVal( mainpanel, MAINPANEL_GNG_2, 1);				//	주화면에 합격표시
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_2, 1);				//	주화면에 합격표시
			}
			else
			{
				SetCtrlVal( mainpanel, MAINPANEL_GNG_2, 0);				//	주화면에 합격표시
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_2, 0);				//	주화면에 합격표시
			}
				
			
			if(Zero_Master_Flag)
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_3, 1);				//	주화면에 합격표시
			else
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_3, 0);				//	주화면에 합격표시
			if(Check_Master_Flag)
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_4, 1);				//	주화면에 합격표시
			else
				SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_4, 0);				//	주화면에 합격표시

		}
*/	
		SetCtrlVal(workref, WORKREF_SERVO_POS_1, Servo_Position[0]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_2, Servo_Position[1]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_3, Servo_Position[2]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_4, Servo_Position[3]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_5, Servo_Position[4]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_6, Servo_Position[5]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_7, Servo_Position[6]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_8, Servo_Position[7]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_9, Servo_Position[8]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_10, Servo_Position[9]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_11, Servo_Position[10]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_12, Servo_Position[11]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_13, Servo_Position[12]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_14, Servo_Position[13]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_15, Servo_Position[14]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_16, Servo_Position[15]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_17, Servo_Position[16]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_18, Servo_Position[17]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_19, Servo_Position[18]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_20, Servo_Position[19]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_21, Servo_Position[20]);
	
		SetCtrlVal(workref, WORKREF_SHAFT_LOW, Shaft_Low);
		SetCtrlVal(workref, WORKREF_SHAFT_HIGH, Shaft_High);
		SetCtrlVal(workref, WORKREF_TUBE_LOW, Tube_Low);
		SetCtrlVal(workref, WORKREF_TUBE_HIGH, Tube_High);

		SetCtrlVal(workref, WORKREF_YAXIS_LOW, YaxisLow);
		SetCtrlVal(workref, WORKREF_YAXIS_HIGH, YaxisHigh);

		SetCtrlVal(workref, WORKREF_RETRY_SET_VALUE, Retry_Data);
		
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_1, Servo_Position[0]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_2, Servo_Position[1]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_3, Servo_Position[2]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_4, Servo_Position[3]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_5, Servo_Position[4]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_6, Servo_Position[5]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_7, Servo_Position[6]);
		
		SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO_2, L_TotalNo);
	SetCtrlVal( mainpanel, MAINPANEL_LG_2, L_Ok);
	SetCtrlVal( mainpanel, MAINPANEL_LNG_2, L_Ng);

		SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO_3, R_TotalNo);
	SetCtrlVal( mainpanel, MAINPANEL_LG_3, R_Ok);
	SetCtrlVal( mainpanel, MAINPANEL_LNG_3, R_Ng);
		
    }
	 else
	 {
		Roller_Dia = 90.0;
		Work_Dia = 60.0;
		Nick_Comp1[0] =Nick_Comp1[1] =Nick_Comp1[2] =Nick_Comp1[3] = 0.0;
		Nick_Value[0] =Nick_Value[1] =Nick_Value[2] = 100.0;
		Nick_Cut = 100;
/*		
		SetCtrlVal( interdata, INTPANEL_ROLLER_DIA, Roller_Dia);
		SetCtrlVal( interdata, INTPANEL_WORK_DIA, Work_Dia);
		SetCtrlVal( interdata, INTPANEL_NICK_COMP, Nick_Comp );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_2, Nick_Comp1[1] );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_3, Nick_Comp1[2] );
		SetCtrlVal( interdata, INTPANEL_NICK_COMP_4, Nick_Comp1[3] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE, Nick_Value[0] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE_2, Nick_Value[1] );
		SetCtrlVal( interdata, INTPANEL_NICK_VALUE_3, Nick_Value[2] );
		SetCtrlVal( interdata, INTPANEL_NICK_CUT, Nick_Cut );
*/
	 
	 }
//		Enc_Ratio = ( Roller_Dia / Work_Dia ) ;
	
}

void	ReadBoxPosData(void)
{
	int 	i, h_file, fileSize;

	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\BoxPos.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
		for( i = 0; i < MAX_EQU; i++ )
			ReadFile(h_file, (char *)&BoxPos[i], sizeof(BOXPOS));
	
		CloseFile( h_file );
    }
}

void	ReadZsetData(void)
{
	int 	i, h_file, fileSize;

	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ZeroSet1.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
		for( i = 0; i < MAX_CH; i++ )
		{
			ReadFile(h_file, (char *)&ZeroOldest1[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroOld1[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroLatest1[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroDiff1[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroNTol1[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroPTol1[i], sizeof(double));
		}
		CloseFile( h_file );
    }
    
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\ZeroSet2.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
		for( i = 0; i < MAX_AX; i++ )
		{
			ReadFile(h_file, (char *)&ZeroOldest2[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroOld2[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroLatest2[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroDiff2[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroNTol2[i], sizeof(double));
			ReadFile(h_file, (char *)&ZeroPTol2[i], sizeof(double));
		}
		CloseFile( h_file );
    }
}

void	SaveCalcData(void)
{
	int 	h_file, i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\Calc.DAT");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);
	 							 
//  Write 계산식 데이타
	for(i = 0; i < MAX_EQU; i++)
		WriteFile(h_file, (char *)&Pgm[i], sizeof(PGM));
		
	CloseFile( h_file );
}

void	SaveModelVarData(void)
{
	int 	h_file, i;
	char    lineBuff[200];
	
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ModelVar.DAT");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	 							 
	sprintf(lineBuff,"%d	%d	%d	%d	%d",Total_cnt,Ok_cnt,Ng_cnt, Mark_Cnt_No, Line_Name);
	WriteLine(h_file,  lineBuff, -1);

	sprintf(lineBuff,"%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d",
			Servo_Position[0],Servo_Position[1],Servo_Position[2],Servo_Position[3],Servo_Position[4],
			Servo_Position[5],Servo_Position[6],Servo_Position[7],Servo_Position[8],Servo_Position[9],
			Servo_Position[10],Servo_Position[11],Servo_Position[12],Servo_Position[13],Servo_Position[14],
			Servo_Position[15],Servo_Position[16],Servo_Position[17],Servo_Position[18],Servo_Position[19],Servo_Position[20]);
	WriteLine(h_file,  lineBuff, -1);

	for(i=0;i<8;i++)
	{
		sprintf(lineBuff,"%d	%d	%3.2f	%3.2f	%3.2f	%d",Mark_OnOff[i],Mark_Type1[i],Mark_X[i],Mark_Y[i],Mark_Z[i],Mark_Rot[i]);
		WriteLine(h_file,  lineBuff, -1);
	}
	for(i=0;i<8;i++)
	{
		sprintf(lineBuff,"%s",Mark_Text[i]);
		WriteLine(h_file,  lineBuff, -1);
	}

	
	sprintf(lineBuff,"%d	%d",Zero_Master_Flag, Check_Master_Flag);
	WriteLine(h_file,  lineBuff, -1);

	sprintf(lineBuff,"%f	%f	%f	%f	%f",Shaft_Low, Shaft_High, Tube_Low, Tube_High, Retry_Data);
	WriteLine(h_file,  lineBuff, -1);
	
	sprintf(lineBuff,"%d	%d	%d	%d	%d	%d",L_TotalNo,L_Ok,L_Ng,R_TotalNo,R_Ok,R_Ng);
	WriteLine(h_file,  lineBuff, -1);

	sprintf(lineBuff,"%f	%f",YaxisLow, YaxisHigh);
	WriteLine(h_file,  lineBuff, -1);
	
	CloseFile( h_file );
}

void	SaveBoxPosData(void)
{
	int 	h_file, i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\BoxPos.dat");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);

	for(i = 0; i < MAX_EQU; i++)
		WriteFile(h_file, (char *)&BoxPos[i], sizeof(BOXPOS));
		
	CloseFile( h_file );
}

void	SaveZsetData(void)
{
	int 	h_file, i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ZeroSet1.dat");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);

	for(i = 0; i < MAX_CH; i++)
	{
		WriteFile(h_file, (char *)&ZeroOldest1[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroOld1[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroLatest1[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroDiff1[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroNTol1[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroPTol1[i], sizeof(double));
	}
	CloseFile( h_file );

	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\ZeroSet2.dat");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);

	for(i = 0; i < MAX_AX; i++)
	{
		WriteFile(h_file, (char *)&ZeroOldest2[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroOld2[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroLatest2[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroDiff2[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroNTol2[i], sizeof(double));
		WriteFile(h_file, (char *)&ZeroPTol2[i], sizeof(double));
	}
	CloseFile( h_file );
}

void	ReadModelData(void)
{
	ReadCalcData();
	ReadBoxPosData();
	ReadZsetData();
	ReadModelVarData();
	ReadMarkData();
	ReadModelVarData2();
	

}

void	WriteModelData(void)
{
	SaveCalcData();
	SaveBoxPosData();
	SaveZsetData();
	SaveModelVarData();
	SaveMarkData();
	SaveModelVarData2();
	
		

}

void	LogDataFunc(char *str, char flag)
{
	char	cTemp[1024],temp[200];
	int		linenum;
	
	if( ((!LogUseFlag || !PlcFirstRunFlag) && !flag )   ||End_PGM)
		return;

	
	
 		
		
		
	sprintf(cTemp, "[%s] : %s", CurrTime, str); //
	InsertListItem (logpanel, LOGPANEL_LISTBOX, -1, cTemp, 0);
	
	
//		sprintf(temp,"[%s] [%s] :%s",DateStr(),TimeStr(), str);
//		InsertListItem(mainpanel, MAINPANEL_STATUS_BOX, -1, temp,0);

//		GetNumListItems (mainpanel, MAINPANEL_STATUS_BOX, &linenum);
//		SetCtrlIndex (mainpanel, MAINPANEL_STATUS_BOX, linenum-1);
	
//		if(linenum >100)
//		DeleteListItem (mainpanel, MAINPANEL_STATUS_BOX, 0, 1);
}
/*
	ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // 반복 측정값 표시 삭제
	InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, ctemp, 0);
	
	GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
	SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);
*/

void	LogDataSave(void)
{
	char	DateStamp[30];
	int		fileHandle, i, listnum;
	long	fileSize;
	char	lineBuff[1024], Temp[30];
	
	sprintf(Temp, "%s", DateStr());
	MakeDateStr(DateStamp, Temp);

	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\HISTORY");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, DateStamp);
	
	strcat(WorkingDirectory, ".LOG");

	if( !GetFileInfo (WorkingDirectory, &fileSize) ) // file 이 존재하는지 확인
	{
		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	}
	else
	{
		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
	}

	GetNumListItems (logpanel, LOGPANEL_LISTBOX, &listnum);

	for( i = 0; i < listnum; i++ )
	{
		GetLabelFromIndex (logpanel, LOGPANEL_LISTBOX, i, lineBuff);
		WriteLine(fileHandle, lineBuff, -1);
	}
	
	WriteLine(fileHandle, " ", -1);
	
	CloseFile(fileHandle);
}


void	ReadPlcErrMsg(void)
{
	int 	i, h_file, fileSize;

//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\sys");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
//char	PlcErrMsg[MAX_PLC_ERR][256];
		for( i = 0; i < MAX_PLC_ERR; i++ )
			sprintf(PlcErrMsg[i], "Err%d", i + 1);
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);									   

	if( !GetFileInfo (".\\sys\\PlcErrMsg.txt", &fileSize) ) // file 이 존재하는지 확인
	{
		for( i = 0; i < MAX_PLC_ERR; i++ )
			sprintf(PlcErrMsg[i], "Err%d", i + 1);
	    return ; 
    }
    
    h_file = OpenFile (".\\sys\\PlcErrMsg.txt",
	 							 VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII);
	
	for( i = 0; i < MAX_PLC_ERR; i++ )
		ReadLine(h_file, PlcErrMsg[i], MAX_PLC_ERR_COL - 2);
	
	CloseFile( h_file );
}

int CVICALLBACK printing (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

// 통신 설정
int CVICALLBACK Menu_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		if(PointMoveSet || St1MeasIng )
			return 0;
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE); // PORT 를 닫기 전에 에러감지용 타이머 죽임.
		SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
		SleepFunc(150);
//		commPWCtrlFlag = TRUE;
//		SetActivePanel(pw);
	
		//	Amp. 통신 중지
		AmpRunFlag = FALSE;
		//	Amp. 통신용 Thread 제거	
		if(!AmpPortOpenErr)
		{
			AmpPortOpenErr = 1;
			AmpPortClose();
		}

		//	PLC. 통신용 Thread 제거	
		if(!PlcPortOpenErr)
		{
			PlcPortOpenErr = 1;
			PLCClose();
		}

		// communicatin setting
//		if ((commpanel = LoadPanel (0, "msg.uir", COMM_SET)) < 0)
//			return ;

		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(commpanel);
		InstallPopup(commpanel);
//			SetActivePanel(commpanel);

			break;
		}
	return 0;
}

// lan 설정
int CVICALLBACK Menu_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
			DisplayPanel(lanpanel);
			InstallPopup(lanpanel);
			break;
		}
	return 0;
}

// work, operator 설정
int CVICALLBACK Menu_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
			DisplayPanel(workpanel);
			InstallPopup(workpanel);

			break;
		}
	return 0;
}

// 포지션 설정

int CVICALLBACK Menu_4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(pospanel);
		InstallPopup(pospanel);

			break;
		}
	return 0;
}
// 에러 메시지 설정
int CVICALLBACK Menu_5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	char	tmpStr[10];
	char  *DataFileBuff1[1000];

	switch (event)
		{
		case EVENT_COMMIT:

			DeleteTableRows (err1panel, ERR_SET_EMSG, 1, -1);     
		   InsertTableRows (err1panel, ERR_SET_EMSG, -1, MAX_PLC_ERR, VAL_CELL_STRING);
		
		
		   for(i = 0; i < MAX_PLC_ERR ; i++)
		   {
		      // To write a row label text
		      sprintf(tmpStr,"ERR %d",i);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_USE_LABEL_TEXT, 1);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_POINT_SIZE,12);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_TEXT, tmpStr );
		   }

			for(i = 0; i < MAX_PLC_ERR ; i++)
				DataFileBuff1[i] = PlcErrMsg[i];
	
			SetTableCellRangeVals(err1panel, ERR_SET_EMSG, MakeRect(1, 1, MAX_PLC_ERR, 1),
								DataFileBuff1, VAL_ROW_MAJOR);
		   

		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(err1panel);
		InstallPopup(err1panel);
			break;
		}
	return 0;
}

// option 설정
int CVICALLBACK Menu_6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(optpanel);
		InstallPopup(optpanel);

			break;
		}
	return 0;
}

int CVICALLBACK Menu_7 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(markpanel);
		InstallPopup(markpanel);

			break;
	}
	return 0;
}


int CVICALLBACK Close_Menu (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetActivePanel(mainpanel);

			break;
		}
	return 0;
}

int CVICALLBACK Keyboard (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
		static int g_exeHandle;
		char  temp[100];
		
		switch (event)
		{
			case EVENT_COMMIT:
           sprintf(temp,"clickey.exe");
		   
 //       MessagePopup("",exeFile);
 	       if (!LaunchExecutableEx (temp, LE_SHOWNORMAL, &g_exeHandle))
				LogDataFunc("화�-키보드 시작", 1);
  
  	      else
            MessagePopup ("ERROR", "Failed to launch executable!");

	
	
	
			break;
		}
	return 0;
}

void Set_DataTable(void)
{
	int		i, TotalColumns;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];


  DeleteTableRows (mainpanel, MAINPANEL_DATA_TABLE, 1, -1);     
//  DeleteTableColumns (mainpanel, MAINPANEL_DATA_TABLE, 1, -1);
   
   //Making the new rows and colums in DATA table
//   InsertTableRows (mainpanel, MAINPANEL_DATA_TABLE, 1, 1, VAL_CELL_NUMERIC);
   
/*   
  for(i = 1; i <= MeasPoints; i++)
   {  
	     SetTableColumnAttribute (mainpanel, MAINPANEL_DATA_TABLE,i,
								   ATTR_COLUMN_WIDTH, 60);
	     SetTableColumnAttribute (mainpanel, MAINPANEL_DATA_TABLE,i,
								   ATTR_LABEL_POINT_SIZE, 10);

		 
		SetTableColumnAttribute (mainpanel, MAINPANEL_DATA_TABLE,
								   i, ATTR_USE_LABEL_TEXT, 1);
        SetTableColumnAttribute (mainpanel, MAINPANEL_DATA_TABLE, i, ATTR_LABEL_TEXT, 
									Model[i-1].Name);
   }
*/	
///////////////
  
	
	
}
void Set_DataValue(void)
{
	int		i,no;
	double	dtemp[MAX_POINT];
	char    temp[10], ctemp[20], DateStamp[50];
   char		*temp1[4][10];
	char	TimeStamp[30], DataStamp[512];
	
	
   InsertTableRows (mainpanel, MAINPANEL_DATA_TABLE, 1, 1, VAL_CELL_STRING);
   
   
//   for(i=0;i<MeasPoints;i++)
//	SetTableCellRangeAttribute (mainpanel, MAINPANEL_DATA_TABLE, MakeRect(1, i+1, 1, 1), ATTR_PRECISION, Model[i].Unit);
	

		GetCtrlVal(mainpanel,MAINPANEL_TOTALTESTNO, &i);

		sprintf(temp,"%d",i+1);
   		SetTableRowAttribute (mainpanel, MAINPANEL_DATA_TABLE,
								   1, ATTR_USE_LABEL_TEXT, 1);
        SetTableRowAttribute (mainpanel, MAINPANEL_DATA_TABLE, 1, ATTR_LABEL_TEXT, 
									temp);
   
   
/*		
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
	SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, A_M_NAME,1,  MeasPoints),
							dtemp, VAL_ROW_MAJOR);

	for( i = 0; i < MeasPoints; i++ )
	{
		if( GFlag[i] == FALSE )
		{
			SetTableCellAttribute (mainpanel, MAINPANEL_DATA_TABLE, MakePoint(i+1,1) , ATTR_TEXT_COLOR, VAL_RED);
		}
		else								//	측정값이 OK구간이면
		{
			SetTableCellAttribute (mainpanel, MAINPANEL_DATA_TABLE, MakePoint(i+1,1), ATTR_TEXT_COLOR, VAL_BLACK);
		}
	}

	

	
	

////// 	

   InsertTableRows (datapanel, DATAPANEL_DATA_TABLE, 1, 1, VAL_CELL_NUMERIC);
   
   for(i=0;i<MeasPoints;i++)
	SetTableCellRangeAttribute (datapanel, DATAPANEL_DATA_TABLE, MakeRect(1, i+1, 1, 1), ATTR_PRECISION, Model[i].Unit);
	

		GetCtrlVal(mainpanel,MAINPANEL_TOTALTESTNO, &i);

		sprintf(temp,"%d",i+1);
   		SetTableRowAttribute (datapanel, DATAPANEL_DATA_TABLE,
								   1, ATTR_USE_LABEL_TEXT, 1);
        SetTableRowAttribute (datapanel, DATAPANEL_DATA_TABLE, 1, ATTR_LABEL_TEXT, 
									temp);
   
   
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
	SetTableCellRangeVals(datapanel, DATAPANEL_DATA_TABLE,
							MakeRect(1, A_M_NAME,1,  MeasPoints),
							dtemp, VAL_ROW_MAJOR);

	for( i = 0; i < MeasPoints; i++ )
	{
		if( GFlag[i] == FALSE )
		{
			SetTableCellAttribute (datapanel, DATAPANEL_DATA_TABLE, MakePoint(i+1,1) , ATTR_TEXT_COLOR, VAL_RED);
		}
		else								//	측정값이 OK구간이면
		{
			SetTableCellAttribute (datapanel, DATAPANEL_DATA_TABLE, MakePoint(i+1,1), ATTR_TEXT_COLOR, VAL_BLACK);
		}
	}

	

	
	
	GetNumTableRows (datapanel, DATAPANEL_DATA_TABLE ,&no );
 
	if(no>400)
		DeleteTableRows (datapanel, DATAPANEL_DATA_TABLE, 401, no-400);     
*/


	  temp1[0][0] = Lan_Data_Char[0];
	  temp1[1][0] = Lan_Data_Char[1];
	  temp1[2][0] = Lan_Data_Char[2];
	  temp1[3][0] = Lan_Data_Char[3];

		SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, 1,1,  1),
							temp1[0], VAL_ROW_MAJOR);
		SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, 2,1,  1),
							temp1[1], VAL_ROW_MAJOR);
		SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, 3,1,  1),
							temp1[2], VAL_ROW_MAJOR);
		SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, 4,1,  1),
							temp1[3], VAL_ROW_MAJOR);
	  
		
	sprintf(ctemp, "%s", DateStr());
 	MakeDateStr(DateStamp, ctemp);

	
	sprintf(TimeStamp, "%s", TimeStr());
	CopyBytes(TimeStamp, 2, ":", 0, 1);
	CopyBytes(TimeStamp, 5, ":", 0, 1);
//	TimeStamp[8]=0X00;
	
	strcat(DateStamp, " / ");
	strcat(DateStamp, TimeStamp);
	temp1[0][0] = DateStamp;
	
	if(TotalGFlag)
	{
		strcpy(DataStamp,"OK");
		
	}
	else
		strcpy(DataStamp,"NG - NONE MARK WORD.");
	
	
	  temp1[1][0] = DataStamp;

		SetTableCellRangeVals(mainpanel, MAINPANEL_DATA_TABLE,
							MakeRect(1, 5,1,  1),
							temp1[0], VAL_ROW_MAJOR);


	
	
		
	GetNumTableRows (mainpanel, MAINPANEL_DATA_TABLE ,&no );
 
	if(no>400)
		DeleteTableRows (mainpanel, MAINPANEL_DATA_TABLE, 401, no-400);     
	
}


void   Set_MeasData(void)
{
	int		i, TotalRows, no=0, no2 = 0, j;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	char	*ctemp1[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];

	if( MeasPoints < 1 )	MeasPoints = 1;

	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 1)
		{
			no++;
			
		}
	}	
	L_MeasPoints  = no;
	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 2)
		{
			no2++;
			
		}
	}	
	R_MeasPoints  = no2;
	
//////////////	
	GetNumTableRows (mainpanel, MAINPANEL_A_TABLE, &TotalRows);

	if( TotalRows < no )
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_A_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (mainpanel, MAINPANEL_A_TABLE, TotalRows, no - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > no )
		DeleteTableRows (mainpanel, MAINPANEL_A_TABLE, no + 1, TotalRows - no);

////////////////
	GetNumTableRows (mainpanel, MAINPANEL_A_TABLE_2, &TotalRows);

	if( TotalRows < no2 )
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_A_TABLE_2, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (mainpanel, MAINPANEL_A_TABLE_2, TotalRows, no2 - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > no2 )
		DeleteTableRows (mainpanel, MAINPANEL_A_TABLE_2, no2 + 1, TotalRows - no2);

	
	
	j=0;
	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 1)
		{
			ctemp[j] = Model[i].Name;
			j++;
		}
	}	
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
							MakeRect (1, A_M_NAME, no, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	
	j = 0;
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 2)
		{
			ctemp[j] = Model[i].Name;
			j++;
		}
	}	
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE_2,
							MakeRect (1, A_M_NAME, no2, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	
/*
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].Comp;
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
							MakeRect(1, A_I_VALUE, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
*/	
	j=0;
	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 1)
		{
			dtemp[j] = Model[i].NTol;
		  j++;
		}
	}
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
							MakeRect(1, A_L_VALUE, no, 1),
							dtemp, VAL_COLUMN_MAJOR);

	j=0;
	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 2)
		{
			dtemp[j] = Model[i].NTol;
		  j++;
		}
	}
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE_2,
							MakeRect(1, A_L_VALUE, no2, 1),
							dtemp, VAL_COLUMN_MAJOR);
		
		
     j=0;	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 1)
		{
			dtemp[j] = Model[i].PTol;
		  j++;
		}
	}
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
							MakeRect(1, A_H_VALUE, no, 1),
							dtemp, VAL_COLUMN_MAJOR);
     j=0;	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 2)
		{
			dtemp[j] = Model[i].PTol;
		  j++;
		}
	}
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE_2,
							MakeRect(1, A_H_VALUE, no2, 1),
							dtemp, VAL_COLUMN_MAJOR);

	
	
	for( i = 0; i < no; i++ )
			SetTableCellRangeAttribute (mainpanel, MAINPANEL_A_TABLE, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);

	for( i = 0; i < no2; i++ )
			SetTableCellRangeAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i+no].Unit);
	
	j=0;	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 1)
		{
			dtemp[j] = 0.0;
		  j++;
		}
	}	
		
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
							MakeRect(1, A_M_VALUE, no, 1),
							dtemp, VAL_COLUMN_MAJOR);

	j=0;	
	for( i = 0; i < MeasPoints; i++ )
	{
		if(Model[i].ST == 2)
		{
			dtemp[j] = 0.0;
		  j++;
		}
	}	
		
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE_2,
							MakeRect(1, A_M_VALUE, no2, 1),
							dtemp, VAL_COLUMN_MAJOR);
		
		
/*	
		for( i = 0; i < MeasPoints; i++ )
		SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(5,i+1), ATTR_TEXT_COLOR, VAL_BLUE);
	
		for( i = 0; i < MeasPoints; i++ )
			ctemp[i] = "OK";
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
								MakeRect (1, 5, MeasPoints, 1),
								ctemp,	VAL_COLUMN_MAJOR);
*/
	
	
	
	for( i = 0; i < no; i++ )
	{
		SetTableRowAttribute (mainpanel, MAINPANEL_A_TABLE, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
		SetTableRowAttribute (mainpanel, MAINPANEL_A_TABLE, i+1, ATTR_ROW_HEIGHT, 40);
	}
	for( i = 0; i < no2; i++ )
	{
		SetTableRowAttribute (mainpanel, MAINPANEL_A_TABLE_2, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
		SetTableRowAttribute (mainpanel, MAINPANEL_A_TABLE_2, i+1, ATTR_ROW_HEIGHT, 40);
	}
	
	for( i = 0; i < no; i++ )
	{
			SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,i+1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,i+1), ATTR_TEXT_COLOR, VAL_BLACK);
	}
	for( i = 0; i < no2; i++ )
	{
			SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,i+1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,i+1), ATTR_TEXT_COLOR, VAL_BLACK);
	}

}

void   Set_MeasValue(void)
{
	int		i, j;
	double	dtemp[MAX_POINT];
  	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];


	if(GSt1Sig == 2)
	{
		j=0;
		for( i = 0; i < MeasPoints; i++ )
		{
			if(Model[i].ST == 1)
			{
			dtemp[j] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			  j++;
			}
			
			
			
		}
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
								MakeRect(1, A_M_VALUE, L_MeasPoints, 1),
								dtemp, VAL_COLUMN_MAJOR);
	
		j=0;
		for( i = 0; i < MeasPoints; i++ )
		{
			if(Model[i].ST == 1)
			{
			
				if( GFlag[i] == FALSE )
				{
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,j+1) , ATTR_TEXT_BGCOLOR, VAL_RED);
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_COLOR, VAL_WHITE);
		//				SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(5,i+1), ATTR_TEXT_COLOR, VAL_RED);
		
		//				ctemp[i] = "NG"; 
				}
				else								//	측정값이 OK구간이면
				{
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_BGCOLOR, VAL_BLUE);
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_COLOR, VAL_WHITE);
		//				SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(5,i+1), ATTR_TEXT_COLOR, VAL_BLUE);
		
		//				ctemp[i] = "OK"; 
				}

				j++;
			}
		}
	}

	if(GSt1Sig == 4)
	{
		j=0;
		for( i = 0; i < MeasPoints; i++ )
		{
			if(Model[i].ST == 2)
			{
			dtemp[j] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			  j++;
			}
			
			
			
		}
		SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE_2,
								MakeRect(1, A_M_VALUE, R_MeasPoints, 1),
								dtemp, VAL_COLUMN_MAJOR);
	
		j=0;
		for( i = 0; i < MeasPoints; i++ )
		{
			if(Model[i].ST == 2)
			{
			
				if( GFlag[i] == FALSE )
				{
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,j+1) , ATTR_TEXT_BGCOLOR, VAL_RED);
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_COLOR, VAL_WHITE);
		//				SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(5,i+1), ATTR_TEXT_COLOR, VAL_RED);
		
		//				ctemp[i] = "NG"; 
				}
				else								//	측정값이 OK구간이면
				{
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_BGCOLOR, VAL_BLUE);
					SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE_2, MakePoint(A_M_VALUE,j+1), ATTR_TEXT_COLOR, VAL_WHITE);
		//				SetTableCellAttribute (mainpanel, MAINPANEL_A_TABLE, MakePoint(5,i+1), ATTR_TEXT_COLOR, VAL_BLUE);
		
		//				ctemp[i] = "OK"; 
				}

				j++;
			}
		}
	}
	
	
	
	
	
	
	
	/*
	SetTableCellRangeVals(mainpanel, MAINPANEL_A_TABLE,
								MakeRect (1, 5, MeasPoints, 1),
								ctemp,	VAL_COLUMN_MAJOR);
*/
	
	
}

int CVICALLBACK Pw2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
	        case EVENT_LEFT_CLICK :
	             callKEYPAD(panel, control, event, NON_TABLE, 0, 0);
	             break;   
	}
	return 0;
}

void CVICALLBACK Ng_Clear (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	ClearListCtrl(mainpanel, MAINPANEL_LISTBOX); // 반복 측정값 표시 삭제
	
	
}

int CVICALLBACK Image_Cap (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	char Temp[100], TimeStamp[30], image_save[256];
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			
		strcpy(image_save, PrjDirectory);
		strcat(image_save, "\\Product\\");
		sprintf(Temp, "%s\\", ModelName[ModelID]);
		strcat(image_save, Temp);
		strcat(image_save, "IMAGE\\");

		if( SetDir(image_save) )			//	Directory가 존재하지 않으면
		{
			MakeDir (image_save);				//	Directory생성
		}

		strcat(image_save,ModelName[ModelID] );
		strcat(image_save, "_");
	 	sprintf(TimeStamp, "%s", TimeStr());
		CopyBytes(TimeStamp, 2, "-", 0, 1);
		CopyBytes(TimeStamp, 5, "-", 0, 1);
		TimeStamp[8]=0X00;

		strcat(image_save,TimeStamp);
		strcat(image_save,".BMP" );
		
				
		   GetPanelDisplayBitmap (mainpanel, VAL_VISIBLE_AREA, VAL_ENTIRE_OBJECT,&i );        
		   ClipboardPutBitmap (i);
		   SaveBitmapToBMPFile (i, image_save);
			break;
	}
	return 0;
}

int CVICALLBACK Lan_Trans (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:
  
			GSt1Sig = 1;
					for(i = 0; i < MeasPoints; i++)
					{
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
						SetCtrlVal( mainpanel, PointCtrl[i], 0.0);
					}

//					GSt1Sig = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 100; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 100;
						
					if( panel == mainpanel)
					{
						ModeID = 0;
						TestFinish();
					}

					break;
	}
	return 0;
}

int CVICALLBACK AUTO_Retry (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &AutoRetry);

			break;
	}
	return 0;
}

void CVICALLBACK Inter_Data (int menuBar, int menuItem, void *callbackData,
		int panel)
{
/*	
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_1,Servo_Position[0]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_2,Servo_Position[1]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_3,Servo_Position[2]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_4,Servo_Position[3]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_5,Servo_Position[4]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_6,Servo_Position[5]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_7,Servo_Position[6]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_8,Servo_Position[7]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_9,Servo_Position[8]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_10,Servo_Position[9]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_11,Servo_Position[10]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_12,Servo_Position[11]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_13,Servo_Position[12]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_14,Servo_Position[13]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_15,Servo_Position[14]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_16,Servo_Position[15]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_17,Servo_Position[16]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_18,Servo_Position[17]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_19,Servo_Position[18]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_20,Servo_Position[19]);
			SetCtrlVal(interdata, INTPANEL_SERVO_POS_21,Servo_Position[20]);
*/			
			SetActivePanel(interdata);
	
	
	
	
	
}

int CVICALLBACK Sel_Graph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			ActivePanel = markpanel;
			
			/*
			for(i = 0; i < 2 ; i++)
			{
				SetCtrlIndex(panel, MARKPANEL_MARKFONT, MarkFont[i]);
				SetCtrlIndex(panel, MARKPANEL_MARKDIR, MarkDir[i]);
				SetCtrlVal(panel, MARKPANEL_MARKHEIGHT, MarkHeight[i]);
				SetCtrlVal(panel, MARKPANEL_MARKPITCH, MarkPitch[i]);
				SetCtrlVal(panel, MARKPANEL_MARKPOSX, MarkPosX[i]);
				SetCtrlVal(panel, MARKPANEL_MARKPOSY, MarkPosY[i]);
				SetCtrlVal(panel, MARKPANEL_MARKWDLIMIT, MarkWidthLimit[i]);
			}
			*/
			if( AUX1PortSendErr && !MarkInitRunFlag[0] )
			{
				MarkInit_Label();
				MarkInitRunFlag[0] = 1;
			}
			

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
 			 SaveMarkData();

			break;
	}
	return 0;
}

int CVICALLBACK setLanguage (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
   			Change_Language();

			break;
	}
	return 0;
}


void	Change_Language(void)
{
	GetCtrlVal(interdata, INTPANEL_LANGUAGE, &language);
//	if(!language)
		return;
	switch(language)
	{
		case 0:

//			SetCtrlAttribute (optpanel, OPT_SET_LANGUAGE                 , ATTR_LABEL_TEXT,             "언어선택");   //언어선택
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    0,     "한국어",   0);   //한국어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    1,     "ENGLISH",   1);   //영  어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    2,     "中國語",   2);   //중국어

			//비밀 번호  Screen 	
			SetCtrlAttribute (pw,PW_COMMANDBUTTON, ATTR_LABEL_TEXT,               "확    인"); 
			SetCtrlAttribute (pw,PW_CANCEL, ATTR_LABEL_TEXT,              	        "취  소");
			SetCtrlAttribute (pw,PW_PW, ATTR_LABEL_TEXT,                 		"비밀 번호 "); 
			SetCtrlAttribute (pw,PW_PW_2, ATTR_LABEL_TEXT,                 		"비밀 번호 "); 
			SetCtrlAttribute (pw,PW_PWCHANGE1, ATTR_LABEL_TEXT,            "비밀 번호 변경 ");
			SetCtrlAttribute (pw,PW_PWCHANGE2, ATTR_LABEL_TEXT,             "변경번호 확인 "); 
//			SetCtrlAttribute (pw,PW_PWCHANGE, ATTR_LABEL_TEXT,               "비밀번호 변경"); 
			
			//환경 설정  

			SetCtrlAttribute (interdata, INTPANEL_STOREVALIDDAY1, ATTR_LABEL_TEXT,                   "파일유효저장일 ");   //수동측정   1
			SetCtrlAttribute (interdata, INTPANEL_SETCONTNG1, ATTR_LABEL_TEXT,                        "연속 불량");	//	1
			SetCtrlAttribute (interdata, INTPANEL_NG_CHK_FLAG1, ATTR_LABEL_TEXT,                        "사용 유무");
			SetCtrlAttribute (interdata, INTPANEL_CLOSE          , ATTR_LABEL_TEXT,                    "확 인");   //확 인 1

			SetCtrlAttribute (interdata, INTPANEL_DAYWORKSTART, ATTR_LABEL_TEXT,                        "주간 작업 시작");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART, ATTR_LABEL_TEXT,                        "주중 야간 작업 시작");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART2, ATTR_LABEL_TEXT,                        "주말 야간 작업 시작");
			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_13                ,                      "연속 NG");  //AMP통신   
			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_12                ,                      "재측정 유무");  //AMP통신   

            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,     ATTR_ON_TEXT,                   "재측정 사용");   //반복
            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,    ATTR_OFF_TEXT,                    "미사용");   //1회  
            SetCtrlAttribute (interdata, INTPANEL_SEPFILE                  , ATTR_LABEL_TEXT,"주/야간 파일 별도 저장");   //주/야간 파일 별도 저장      
			

			
			// 제품 선택 MENU 
			SetCtrlAttribute (workpanel, WORK_SET_MODEL1      , ATTR_LABEL_TEXT,                 "제품선택");   //제품선택
            SetCtrlAttribute (workpanel, WORK_SET_REMOVEMODEL, ATTR_LABEL_TEXT,                 "제품삭제");   //제품삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORK, ATTR_LABEL_TEXT,              "제품명 변경");   //제품명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDMODEL   , ATTR_LABEL_TEXT,                 "제품추가");   //제품추가

			SetCtrlAttribute (workpanel, WORK_SET_WORKER1     , ATTR_LABEL_TEXT,              "작업자 선택");   //작업자 선택
			SetCtrlAttribute (workpanel, WORK_SET_REMOVEWORKER, ATTR_LABEL_TEXT,             "작업자 삭제");   //작업자 삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORKER, ATTR_LABEL_TEXT,           "작업자명 변경");   //작업자명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDWORKER1   , ATTR_LABEL_TEXT,             "작업자 추가");   //작업자 추가
            SetCtrlAttribute (workpanel, WORK_SET_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			
			//MENU 
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_1  , ATTR_LABEL_TEXT,              "COMMUNICATION");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_2  , ATTR_LABEL_TEXT,              "LAN SETUP");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_3  , ATTR_LABEL_TEXT,              "기종, 작업자");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_4  , ATTR_LABEL_TEXT,              "POINT POSITION");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_5  , ATTR_LABEL_TEXT,              "ERROR MESSAGE");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_6  , ATTR_LABEL_TEXT,              "OPTION");   //COMMUNICATION
            SetCtrlAttribute (menupanel, MENUPANEL_CLOSE_MENU      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
	
			// MENU COMMUNICATION
			SetCtrlVal       (commpanel  , COMM_SET_TEXTMSG_3                ,                      "통신포트 설정");   //통신포트 설정
            SetCtrlAttribute (commpanel  , COMM_SET_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			SetCtrlAttribute (commpanel  , COMM_SET_PORTPAR                 , ATTR_LABEL_TEXT,           "PORT 설정");   //포트이름
  //          SetCtrlVal       (commpanel  , COMM_SET_PORTNAME                ,                     "포트 이름");   //측정시 설정값

			SetCtrlVal       (comconfig1  , COMCONFIG1_TEXTMSG_10                ,                      "RS232 통신 설정");   //통신포트 설정
            SetCtrlAttribute (comconfig1  , COMCONFIG1_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			
			// LAN MENU 
			SetCtrlAttribute (lanpanel,LAN_SET_SWITCH_LANUSE, ATTR_LABEL_TEXT,                        "Data 전송");	//	1
            SetCtrlAttribute (lanpanel,LAN_SET_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			// point pos menu
            SetCtrlAttribute (pospanel, POS_SET_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			// error message menu
            SetCtrlAttribute (err1panel, ERR_SET_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			
			//modelsetup    MODEL 	   사용 불가 문자 : \ / : * ? " < > |  TEXTMSG
            //SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG      ,                                   "SEN. VALUE [um]");
			SetCtrlAttribute (modelsetup,MODELSETUP                , ATTR_LABEL_TEXT,             "제품 설정");   //제품  설정
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 1, ATTR_LABEL_TEXT,             "측 정 명");   //측 정 명
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 2, ATTR_LABEL_TEXT,             "보 정 값");   //보 정 값
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 3, ATTR_LABEL_TEXT,             "공차하한");   //공차하한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 4, ATTR_LABEL_TEXT,            "관리 공차 하한");  //공차상한한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 5, ATTR_LABEL_TEXT,            "관리 공차 상한");  //공차상한한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 6, ATTR_LABEL_TEXT,            "공차 상한");  //공차상한한
            SetCtrlAttribute (modelsetup,MODELSETUP_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			SetCtrlAttribute (modelsetup,MODELSETUP_MODEL      , ATTR_LABEL_TEXT,                 "제품선택");   //제품선택
            SetCtrlAttribute (modelsetup,MODELSETUP_WORKER     , ATTR_LABEL_TEXT,              "작업자 선택");   //작업자 선택

            SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEMODEL, ATTR_LABEL_TEXT,                 "제품삭제");   //제품삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEMODEL, ATTR_LABEL_TEXT,              "제품명 변경");   //제품명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDMODEL   , ATTR_LABEL_TEXT,                 "제품추가");   //제품추가

			SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEWORKER, ATTR_LABEL_TEXT,             "작업자 삭제");   //작업자 삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEWORKER, ATTR_LABEL_TEXT,           "작업자명 변경");   //작업자명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDWORKER   , ATTR_LABEL_TEXT,             "작업자 추가");   //작업자 추가
			
			
			
		// MANUAL
            SetCtrlAttribute (manualctrl,MANUALCTRL_MCYCLEINDEX_1, ATTR_LABEL_TEXT,             "총측정횟수");   //총측정횟수
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLENOSET_1,  ATTR_LABEL_TEXT,            "반복수 설정");   //반복수 설정
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLEMODE_1,   ATTR_LABEL_TEXT,           "측정횟수조건");   //측정횟수조건
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,     ATTR_ON_TEXT,                   "반복");   //반복
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,    ATTR_OFF_TEXT,                    "1회");   //1회  
            SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_1 , ATTR_LABEL_TEXT,               "LEFT측정시작");   //측정시작             
 //           SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_2 , ATTR_LABEL_TEXT,               "단차 측정시작");   //측정시작             
            SetCtrlAttribute (manualctrl,MANUALCTRL_SAVE_1       , ATTR_LABEL_TEXT,             "측정값저장");   //측정값저장
            SetCtrlAttribute (manualctrl,MANUALCTRL_RESULTVIEW_1 , ATTR_LABEL_TEXT,               "결과보기");   //결괴보기 
			SetCtrlAttribute (manualctrl,MANUALCTRL_CLR_1        , ATTR_LABEL_TEXT,             "측정값삭제");   //측정값삭제
            SetCtrlAttribute (manualctrl,MANUALCTRL_CLOSE        , ATTR_LABEL_TEXT,              "메뉴 복귀");   //메뉴 복귀
//			SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG      ,          						 "센 서 값 [um]");   //센 서 값 [um] 
			SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG_4    ,         						 "반복측정값[um]");   //반복측정값[um] 
 			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_2                ,                      "AMP COM");  //AMP통신   
			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_23                ,                      "PLC COM");  //PLC통신   

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,    ATTR_ON_TEXT,                      "투입셔틀\n전진/후진");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,   ATTR_OFF_TEXT,                     "투입셔틀\n전진/후진");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,    ATTR_ON_TEXT,                      "이송#1 하상\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,   ATTR_OFF_TEXT,                     "이송#1 하상\n하강/상승");   //불합격
	
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,    ATTR_ON_TEXT,                      "이송#1 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,   ATTR_OFF_TEXT,                     "이송#1 척\nON/OFF");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,    ATTR_ON_TEXT,                      "이송#2 하상\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,   ATTR_OFF_TEXT,                     "이송#2 하상\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,    ATTR_ON_TEXT,                      "이송#2 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,   ATTR_OFF_TEXT,                     "이송#2 척\nON/OFF");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,    ATTR_ON_TEXT,                      "이송#3 하상\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,   ATTR_OFF_TEXT,                     "이송#3 하상\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,    ATTR_ON_TEXT,                      "이송#3 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,   ATTR_OFF_TEXT,                     "이송#3 척\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,    ATTR_ON_TEXT,                      "이송#4 하상\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,   ATTR_OFF_TEXT,                     "이송#4 하상\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,    ATTR_ON_TEXT,                      "이송#4 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,   ATTR_OFF_TEXT,                     "이송#4 척\nON/OFF");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,    ATTR_ON_TEXT,                      "이송#4 회전\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,   ATTR_OFF_TEXT,                     "이송#4 회전\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,    ATTR_ON_TEXT,                      "이송#5 하상\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,   ATTR_OFF_TEXT,                     "이송#5 하상\n하강/상승");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,    ATTR_ON_TEXT,                      "이송#5 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,   ATTR_OFF_TEXT,                     "이송#5 척\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,    ATTR_ON_TEXT,                      "이송#5 회전\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,   ATTR_OFF_TEXT,                     "이송#5 회전\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,    ATTR_ON_TEXT,                      "이송#5 전후\n전진/후진");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,   ATTR_OFF_TEXT,                     "이송#5 전후\n전진/후진");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL15_2        ,    ATTR_ON_TEXT,                      "측정 리프트\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL15_2        ,   ATTR_OFF_TEXT,                     "측정 리프트\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL16_2        ,    ATTR_ON_TEXT,                      "측정 파트\n전진/후진");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL16_2        ,   ATTR_OFF_TEXT,                     "측정 파트\n전진/후진");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,    ATTR_ON_TEXT,                      "측정 파트\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,   ATTR_OFF_TEXT,                     "측정 파트\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,    ATTR_ON_TEXT,                      "마스터 셔틀\n전진/후진");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,   ATTR_OFF_TEXT,                     "마스터 셔틀\n전진/후진");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,    ATTR_ON_TEXT,                      "LASER 마킹\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,   ATTR_OFF_TEXT,                     "LASER 마킹\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,    ATTR_ON_TEXT,                      "NG CONV 정\n동작/복귀");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,   ATTR_OFF_TEXT,                     "NG CONV 정\n동작/복귀");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL21_2        ,    ATTR_ON_TEXT,                      "서보 조그\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL21_2        ,   ATTR_OFF_TEXT,                     "서보 조그\n+/-");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL22_2        ,    ATTR_ON_TEXT,                      "내경 PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL22_2        ,   ATTR_OFF_TEXT,                     "내경 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL23_2        ,    ATTR_ON_TEXT,                      "평면 PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL23_2        ,   ATTR_OFF_TEXT,                     "평면 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,    ATTR_ON_TEXT,                      "NG CONV 역\n동작/복귀");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,   ATTR_OFF_TEXT,                     "NG CONV 역\n동작/복귀");   //불합격

			
			
			/*
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,    ATTR_ON_TEXT,                      "스토퍼#2\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,   ATTR_OFF_TEXT,                     "스토퍼#2\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,    ATTR_ON_TEXT,                      "배출 이송\n전진/후진");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,   ATTR_OFF_TEXT,                     "배출 이송\n전진/후진");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,    ATTR_ON_TEXT,                      "배출이송 상하\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,   ATTR_OFF_TEXT,                     "배출이송 상하\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,    ATTR_ON_TEXT,                      "배출이송 척\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,   ATTR_OFF_TEXT,                     "배출이송 척\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,    ATTR_ON_TEXT,                      "배출판별모터\n전회전/역회전");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,   ATTR_OFF_TEXT,                     "배출판별모터\n전회전/역회전");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,    ATTR_ON_TEXT,                      "OK배출모터\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,   ATTR_OFF_TEXT,                     "OK배출모터\nON/OFF");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,    ATTR_ON_TEXT,                      "AIR PROBE1\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,   ATTR_OFF_TEXT,                     "AIR PROBE1\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,    ATTR_ON_TEXT,                      "AIR PROBE2\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,   ATTR_OFF_TEXT,                     "AIR PROBE2\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,    ATTR_ON_TEXT,                      "안착 확인 솔\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,   ATTR_OFF_TEXT,                     "안착 확인 솔\nON/OFF");   //불합격
*/
			
			
			
			//M_MEAS_TABLE
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 1, ATTR_LABEL_TEXT,             "측정항목");   //측정항목
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 2, ATTR_LABEL_TEXT,             "측정값");       //하한
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 3, ATTR_LABEL_TEXT,             "하한");     //측정값 
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 4, ATTR_LABEL_TEXT,             "상한");       //상한
			
			// SERVO POSITION
//			SetCtrlVal (servoctrl,SERVOPOS_TEXTMSG      ,          						 "LEFT SERVO POSITION");   //센 서 값 [um] 
//			SetCtrlVal (servoctrl,SERVOPOS_TEXTMSG_2      ,          						 "RIGHT SERVO POSITION");   //센 서 값 [um] 
  //          SetCtrlAttribute (servoctrl,SERVOPOS_SERVO_SETTING , ATTR_LABEL_TEXT,               "SERVO DATA 입력");   //측정시작             
    //        SetCtrlAttribute (servoctrl,SERVOPOS_SERVO_SETTING_2 , ATTR_LABEL_TEXT,               "SERVO 위치 이동");   //측정시작             
      //      SetCtrlAttribute (servoctrl,SERVOPOS_SERVO_SAVE , ATTR_LABEL_TEXT,               "SERVO SAVE");   //측정시작             
        //    SetCtrlAttribute (servoctrl,SERVOPOS_CLOSE      , ATTR_LABEL_TEXT,                    "확 인");   //확 인

			//zerosetup		 
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_LABEL_TEXT,                 "센서 번호");   //센서 번호
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 2, ATTR_LABEL_TEXT,           "오래된 \n측정값");   //오래된 \n측정값
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 3, ATTR_LABEL_TEXT,                "이전측정값");   //이전측정값              
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 4, ATTR_LABEL_TEXT,             "현재 \n측정값");   //현재 \n측정값
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 5, ATTR_LABEL_TEXT,         "편차\n(이전-현재)");   //편차\n(이전-현재)
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 6, ATTR_LABEL_TEXT,                  "센서하한");   //센서하한
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 7, ATTR_LABEL_TEXT,                  "센서상한");   //센서상한
			SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL   , ATTR_LABEL_TEXT,                  "영점 조정");   //영점조정
//			SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL_3   , ATTR_LABEL_TEXT,                  "우측 영점조정");   //영점조정
            SetCtrlAttribute (zerosetup  , ZEROSETUP_CLOSE       , ATTR_LABEL_TEXT,                         "확 인");   //확인
			SetCtrlVal       (zerosetup  , ZEROSETUP_TEXTMSG_2                ,                      "단위 [um]");   //통신포트 설정

			//dataview
            SetCtrlAttribute (dataview  , DATAVIEW_TITLE          , ATTR_LABEL_TEXT,                    "제 목");   //제 목
            SetCtrlAttribute (dataview  , DATAVIEW_TOTAL_NUM      , ATTR_LABEL_TEXT,                 "전체수량");   //전체수량
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_START_NUM, ATTR_LABEL_TEXT,             "시작번호입력");   //시작번호입력
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_DATA_NUM , ATTR_LABEL_TEXT,             "데이터수입력");   //데이터수입력
//            SetCtrlAttribute (dataview  , DATAVIEW_REVIEW_COM     , ATTR_LABEL_TEXT,                 "다시보기");   //다시보기
//            SetCtrlAttribute (dataview  , DATAVIEW_SAVEDATA       , ATTR_LABEL_TEXT,                    "저 장");   //저 장
//            SetCtrlAttribute (dataview  , DATAVIEW_PRINTING       , ATTR_LABEL_TEXT,               "흑백프린트");   //흑백프린트
            SetCtrlAttribute (dataview  , DATAVIEW_START_NUM      , ATTR_LABEL_TEXT,                 "시작번호");   //시작번호
            SetCtrlAttribute (dataview  , DATAVIEW_DATA_NUM       , ATTR_LABEL_TEXT,                 "데이터수");   //데이터수
            SetCtrlAttribute (dataview  , DATAVIEW_CLOSE          , ATTR_LABEL_TEXT,                    "확 인");   //확 인
			SetCtrlVal       (dataview  , DATAVIEW_TEXTMSG_4                ,                      "단위 [um]");   //통신포트 설정
  		
			//main
			SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO, ATTR_LABEL_TEXT,                       "전체");   //전체수량
            SetCtrlAttribute (mainpanel,MAINPANEL_LG	     , ATTR_LABEL_TEXT,                       "합격");   //합격수량
            SetCtrlAttribute (mainpanel,MAINPANEL_LNG        , ATTR_LABEL_TEXT,                       "불량");   //불량수량
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,    ATTR_ON_TEXT,                      "합 격");   //합 격
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,   ATTR_OFF_TEXT,                     "불합격");   //불합격
//			SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO_3, ATTR_LABEL_TEXT,                       "전체");   //전체수량
//            SetCtrlAttribute (mainpanel,MAINPANEL_LG_3	     , ATTR_LABEL_TEXT,                       "합격");   //합격수량
 //           SetCtrlAttribute (mainpanel,MAINPANEL_LNG_3        , ATTR_LABEL_TEXT,                       "불량");   //불량수량
//			SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,    ATTR_ON_TEXT,                      "합 격");   //합 격
//			SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,   ATTR_OFF_TEXT,                     "불합격");   //불합격
			SetCtrlAttribute (mainpanel,MAINPANEL_LISTBOX    , ATTR_LABEL_TEXT,                    "NG LIST");   //NG LIST
//			SetCtrlVal       (mainpanel,MAINPANEL_STRING_4                ,                      "좌측 VANE");   //통신포트 설정
//			SetCtrlVal       (mainpanel,MAINPANEL_STRING_5                ,                      "우측 VANE");   //통신포트 설정
             SetCtrlAttribute (mainpanel,MAINPANEL_ERRVIEW, ATTR_LABEL_TEXT,                   "알람 보기");   //수동측정
 
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 1, ATTR_LABEL_TEXT,             "측정항목");   //측정항목
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 3, ATTR_LABEL_TEXT,             "공차하한");       //하한
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 2, ATTR_LABEL_TEXT,             "측정값");     //측정값 
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 4, ATTR_LABEL_TEXT,             "공차상한");       //상한
			 
			 
			 SetCtrlAttribute (mainpanel,MAINPANEL_MANUALCTRL1, ATTR_LABEL_TEXT,                   "수동측정");   //수동측정
            SetCtrlAttribute (mainpanel,MAINPANEL_ZEROSETUP1 , ATTR_LABEL_TEXT,                   "영점조정");   //영점조정
            SetCtrlAttribute (mainpanel,MAINPANEL_MODELSETUP1, ATTR_LABEL_TEXT,                   "제품설정");   //제품설정
			SetCtrlAttribute (mainpanel,MAINPANEL_MENU_BT       , ATTR_LABEL_TEXT,                  "환경 설정");   //환경 설정 
			SetCtrlAttribute (mainpanel,MAINPANEL_RESULTVIEW1, ATTR_LABEL_TEXT,                   "결과조회");   //결과조회
			SetCtrlAttribute (mainpanel,MAINPANEL_CLOSE ,      ATTR_LABEL_TEXT,                       "종료");   //종료 
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_3                ,                      "AMP 통신");  //AMP통신   
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_4                ,                      "PLC 통신");  //PLC통신   
			
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_1        , ATTR_LABEL_TEXT,                    "자동 운전");   //자동 운전
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_2        , ATTR_LABEL_TEXT,                    "제품 측정중");   //제품 측정중
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_3        , ATTR_LABEL_TEXT,                    "측정 완료");   //측정 완료

           SetCtrlAttribute (mainpanel,MAINPANEL_LXBAR      , ATTR_LABEL_TEXT,                       "평균");   //평균
            SetCtrlAttribute (mainpanel,MAINPANEL_LR         , ATTR_LABEL_TEXT,                       "범위");   //범위
			SetCtrlAttribute (mainpanel,MAINPANEL_LMAX       , ATTR_LABEL_TEXT,                     "최대값");   //최대값
			SetCtrlAttribute (mainpanel,MAINPANEL_LMIN       , ATTR_LABEL_TEXT,                     "최소값");   //최소값
			SetCtrlAttribute (mainpanel,MAINPANEL_LSTDDIV    , ATTR_LABEL_TEXT,                  "표준 편차");   //표준 편차
			SetCtrlAttribute (mainpanel,MAINPANEL_LCP        , ATTR_LABEL_TEXT,                         "CP");   //CP
			SetCtrlAttribute (mainpanel,MAINPANEL_LCPK       , ATTR_LABEL_TEXT,                        "Cpk");   //Cpk
/////
			SetCtrlAttribute (markpanel, MARK_SET_MARKTRANS       , ATTR_LABEL_TEXT,                        "문자 전송");   
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG                ,                      "마킹유무");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_21                ,                      "마킹 종류");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_22                ,                      "마킹 문자");    
			
			SetCtrlAttribute (workref, WORKREF_SERVO_ALL_SAVE       , ATTR_LABEL_TEXT,                        "위치 저장");   

			
		break;

		case 1:
//			SetCtrlAttribute (optpanel, OPT_SET_LANGUAGE                 , ATTR_LABEL_TEXT,             "LANGUAGE SELECT");   //언어선택
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    0,     "한국어",   0);   //한국어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    1,     "ENGLISH",   1);   //영  어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    2,     "中國語",   2);   //중국어

		//비밀 번호  Screen 	
			SetCtrlAttribute (pw,PW_COMMANDBUTTON, ATTR_LABEL_TEXT,               "O  K"); 
			SetCtrlAttribute (pw,PW_CANCEL, ATTR_LABEL_TEXT,              	        "CANCEL");
			SetCtrlAttribute (pw,PW_PW, ATTR_LABEL_TEXT,                 		"PASSWORD "); 
			SetCtrlAttribute (pw,PW_PW_2, ATTR_LABEL_TEXT,                 		"PASSWORD "); 
			SetCtrlAttribute (pw,PW_PWCHANGE1, ATTR_LABEL_TEXT,                "P/W CHANGE ");
			SetCtrlAttribute (pw,PW_PWCHANGE2, ATTR_LABEL_TEXT,             "P/W CONFIRM "); 
//			SetCtrlAttribute (pw,PW_PWCHANGE, ATTR_LABEL_TEXT,               "P/W CHECK"); 
			

			
			
			//환경 설정  
			SetCtrlAttribute (interdata, INTPANEL_STOREVALIDDAY1, ATTR_LABEL_TEXT,               "FILE SAVE DAYS ");   //수동측정
			SetCtrlAttribute (interdata, INTPANEL_SETCONTNG1, ATTR_LABEL_TEXT,                       "CONTINOUS NG");
			SetCtrlAttribute (interdata, INTPANEL_NG_CHK_FLAG1, ATTR_LABEL_TEXT,                        "ON/OFF");
			SetCtrlAttribute (interdata, INTPANEL_CLOSE          , ATTR_LABEL_TEXT,                    "RETURN");   //확 인 1

			SetCtrlAttribute (interdata, INTPANEL_DAYWORKSTART, ATTR_LABEL_TEXT,                        "DAY WORK START");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART, ATTR_LABEL_TEXT,                        "WEEKDAYS NIGHT WORK START");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART2, ATTR_LABEL_TEXT,                        "WEEKEND NIGHT WORK START");

			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_13                ,                      "CONT NG");  //AMP통신   
			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_12               ,                      "RE.MEAS ON/OFF");  //AMP통신   
			
            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,     ATTR_ON_TEXT,                   "RE.MEAS ON");   //반복
            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,    ATTR_OFF_TEXT,                    "RE.MEAS OFF");   //1회  
            SetCtrlAttribute (interdata, INTPANEL_SEPFILE                  , ATTR_LABEL_TEXT,"DAY/NIGHT DIFF. SAVE");   //주/야간 파일 별도 저장      
		
			// 제품 선택 MENU 
			SetCtrlAttribute (workpanel, WORK_SET_MODEL1      , ATTR_LABEL_TEXT,                 "MODEL");   //제품선택
            SetCtrlAttribute (workpanel, WORK_SET_REMOVEMODEL, ATTR_LABEL_TEXT,                 "MODEL DEL");   //제품삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORK, ATTR_LABEL_TEXT,              "NAME \n CHANGE");   //제품명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDMODEL   , ATTR_LABEL_TEXT,                 "MODEL ADD");   //제품추가

			SetCtrlAttribute (workpanel, WORK_SET_WORKER1     , ATTR_LABEL_TEXT,              "WORKER.");   //작업자 선택
			SetCtrlAttribute (workpanel, WORK_SET_REMOVEWORKER, ATTR_LABEL_TEXT,             "WORKER DEL");   //작업자 삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORKER, ATTR_LABEL_TEXT,           "NAME \n CHANGE");   //작업자명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDWORKER1   , ATTR_LABEL_TEXT,             "WORKER ADD");   //작업자 추가
            SetCtrlAttribute (workpanel, WORK_SET_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
			
			//MENU 
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_1  , ATTR_LABEL_TEXT,              "COMMUNICATION");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_2  , ATTR_LABEL_TEXT,              "LAN SETUP");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_3  , ATTR_LABEL_TEXT,              "MODEL, OPERATOR");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_4  , ATTR_LABEL_TEXT,              "POINT POSITION");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_5  , ATTR_LABEL_TEXT,              "ERROR MESSAGE");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_6  , ATTR_LABEL_TEXT,              "OPTION");   //COMMUNICATION
            SetCtrlAttribute (menupanel, MENUPANEL_CLOSE_MENU      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
 			
			// MENU COMMUNICATION
			SetCtrlVal       (commpanel  , COMM_SET_TEXTMSG_3                ,                      "COM. PORT SET");   //통신포트 설정
            SetCtrlAttribute (commpanel  , COMM_SET_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
			SetCtrlAttribute (commpanel  , COMM_SET_PORTPAR                 , ATTR_LABEL_TEXT,           "PORT \n parameter");   //포트이름
 //           SetCtrlVal       (commpanel  , COMM_SET_PORTNAME                ,                     "PORT NAME");   //측정시 설정값
			
			SetCtrlVal       (comconfig1  , COMCONFIG1_TEXTMSG_10                ,                      "RS232 COM. SET");   //통신포트 설정
            SetCtrlAttribute (comconfig1  , COMCONFIG1_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
	
			// LAN MENU 
			SetCtrlAttribute (lanpanel,LAN_SET_SWITCH_LANUSE, ATTR_LABEL_TEXT,                        "Data Trans");	//	1
            SetCtrlAttribute (lanpanel,LAN_SET_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
			// point pos menu
            SetCtrlAttribute (pospanel, POS_SET_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인

			// error message menu
            SetCtrlAttribute (err1panel, ERR_SET_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
			
		//modelsetup    MODEL 	   사용 불가 문자 : \ / : * ? " < > |
            SetCtrlAttribute (modelsetup,MODELSETUP                , ATTR_LABEL_TEXT,             "MODEL SEL.");   //제품  설정
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 1, ATTR_LABEL_TEXT,             "MEAS. NAME");   //측 정 명
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 2, ATTR_LABEL_TEXT,             "COMP. VALUE");   //보 정 값
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 3, ATTR_LABEL_TEXT,             "COMP. LOWER");   //공차하한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 4, ATTR_LABEL_TEXT,            "MIDDLE LOWER");  //공차상한한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 5, ATTR_LABEL_TEXT,            "MIDDLE UPPER");  //공차상한한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 6, ATTR_LABEL_TEXT,            "COMP. UPPER");  //공차상한한
    
            SetCtrlAttribute (modelsetup,MODELSETUP_CLOSE      , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
			SetCtrlAttribute (modelsetup,MODELSETUP_MODEL      , ATTR_LABEL_TEXT,                 "MODEL.");   //제품선택
            SetCtrlAttribute (modelsetup,MODELSETUP_WORKER     , ATTR_LABEL_TEXT,              "WORKER.");   //작업자 선택

            SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEMODEL, ATTR_LABEL_TEXT,                 "MODEL DEL");   //제품삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEMODEL, ATTR_LABEL_TEXT,              "CHANGE");   //제품명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDMODEL   , ATTR_LABEL_TEXT,                 "MODEL ADD");   //제품추가

			SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEWORKER, ATTR_LABEL_TEXT,             "WORKER DEL");   //작업자 삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEWORKER, ATTR_LABEL_TEXT,           "CHANGE");   //작업자명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDWORKER   , ATTR_LABEL_TEXT,             "WORKER ADD");   //작업자 추가
			
			
			
			//manualctrl
//			SetCtrlAttribute (manualctrl,MANUALCTRL              , ATTR_LABEL_TEXT,       "SENSOR, MANUAL MEAS.");   //센서, 수동 측정
            SetCtrlAttribute (manualctrl,MANUALCTRL_MCYCLEINDEX_1, ATTR_LABEL_TEXT,             "TOTAL MEAS.NUM");   //총측정횟수
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLENOSET_1,  ATTR_LABEL_TEXT,                "REPEAT NUM.");   //반복수 설정
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLEMODE_1,   ATTR_LABEL_TEXT,                  "MEAS.ORDER");   //측정횟수조건
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,     ATTR_ON_TEXT,                     "REPEAT");   //반복
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,    ATTR_OFF_TEXT,                     "1 TIME");   //1회  
            SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_1 , ATTR_LABEL_TEXT,                "MEAS. START");   //측정시작             
  //          SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_2 , ATTR_LABEL_TEXT,                "RIGHT MEAS. START");   //측정시작             
            SetCtrlAttribute (manualctrl,MANUALCTRL_SAVE_1       , ATTR_LABEL_TEXT,        "MEAS.VALUE SAVE");   //측정값저장
            SetCtrlAttribute (manualctrl,MANUALCTRL_RESULTVIEW_1 , ATTR_LABEL_TEXT,                "RESULT VIEW");   //결괴보기 
			SetCtrlAttribute (manualctrl,MANUALCTRL_CLR_1        , ATTR_LABEL_TEXT,                     "DELETE");   //측정값삭제
            SetCtrlAttribute (manualctrl,MANUALCTRL_CLOSE        , ATTR_LABEL_TEXT,                "RETURN");   //메뉴 복귀
//			SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG      ,                                   "SEN. VALUE [um]");   //센 서 값 [um] 
			SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG_4    ,                                  "REPEAT VALUE[um]");   //반복측정값[um] 
			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_2                ,                      "AMP COM");  //AMP통신   
			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_23                ,                      "PLC COM");  //PLC통신   

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,    ATTR_ON_TEXT,                      "IN SHUTTLE\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,   ATTR_OFF_TEXT,                     "IN SHUTTLE\nFOR/BACK");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,    ATTR_ON_TEXT,                      "MEAS LIFT\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,   ATTR_OFF_TEXT,                     "MEAS LIFT\n하강/상승");   //불합격
	
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,    ATTR_ON_TEXT,                      "UP FIXTURE\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,   ATTR_OFF_TEXT,                     "UP FIXTURE\n하강/상승");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,    ATTR_ON_TEXT,                      "NG MARK\n하강/상승");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,   ATTR_OFF_TEXT,                     "NG MARK\n하강/상승");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,    ATTR_ON_TEXT,                      "DIA SHUTTLE\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,   ATTR_OFF_TEXT,                     "DIA SHUTTLE\nFOR/BACK");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,    ATTR_ON_TEXT,                      "SIDE DIA1\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,   ATTR_OFF_TEXT,                     "SIDE DIA1\nFOR/BACK");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,    ATTR_ON_TEXT,                      "SIDE DIA2\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,   ATTR_OFF_TEXT,                     "SIDE DIA2\nFOR/BACK");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,    ATTR_ON_TEXT,                      "DIA PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,   ATTR_OFF_TEXT,                     "DIA PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,    ATTR_ON_TEXT,                      "PLATE PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,   ATTR_OFF_TEXT,                     "PLATEPROBE\nON/OFF");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,    ATTR_ON_TEXT,                      "DIA1 PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,   ATTR_OFF_TEXT,                     "DIA1 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,    ATTR_ON_TEXT,                      "DIA2PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,   ATTR_OFF_TEXT,                     "DIA2 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,    ATTR_ON_TEXT,                      "STOPPER#1\nUP/DN");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,   ATTR_OFF_TEXT,                     "STOPPER#1\nUP/DN");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,    ATTR_ON_TEXT,                      "STOPPER#2\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,   ATTR_OFF_TEXT,                     "STOPPER#2\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,    ATTR_ON_TEXT,                      "IN MOTOR\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,   ATTR_OFF_TEXT,                     "IN MOTOR\nON/OFF");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,    ATTR_ON_TEXT,                      "LIFT\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,   ATTR_OFF_TEXT,                     "LIFT\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,    ATTR_ON_TEXT,                      "MEAS PART\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,   ATTR_OFF_TEXT,                     "MEAS PART\nFOR/BACK");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,    ATTR_ON_TEXT,                      "MEAS PART\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,   ATTR_OFF_TEXT,                     "MEAS PART\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,    ATTR_ON_TEXT,                      "ROTATION\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,   ATTR_OFF_TEXT,                     "ROTATION\n+/-");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,    ATTR_ON_TEXT,                      "MARK PART\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,   ATTR_OFF_TEXT,                     "MARK PART\nFOR/BACK");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL25_2        ,    ATTR_ON_TEXT,                      "CHUCK\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL25_2        ,   ATTR_OFF_TEXT,                     "CHUCK\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL27_2        ,    ATTR_ON_TEXT,                      "ROTATION\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL27_2        ,   ATTR_OFF_TEXT,                     "ROTATION\n+/-");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL28_2        ,    ATTR_ON_TEXT,                      "LIFT\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL28_2        ,   ATTR_OFF_TEXT,                     "LIFT\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL29_2        ,    ATTR_ON_TEXT,                      "STOPPER#1\nUP/DN");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL29_2        ,   ATTR_OFF_TEXT,                     "STOPPER#1\nUP/DN");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,    ATTR_ON_TEXT,                      "STOPPER#2\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,   ATTR_OFF_TEXT,                     "STOPPER#2\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,    ATTR_ON_TEXT,                      "TRANSFER\nFOR/BACK");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,   ATTR_OFF_TEXT,                     "TRANSFER\nFOR/BACK");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,    ATTR_ON_TEXT,                      "TRANS DN/UP\nDN/UP");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,   ATTR_OFF_TEXT,                     "TRANS DN/UP\nDN/UP");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,    ATTR_ON_TEXT,                      "TRANS CHUCK\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,   ATTR_OFF_TEXT,                     "TRANS CHUCK\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,    ATTR_ON_TEXT,                      "OUT MOTOR\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,   ATTR_OFF_TEXT,                     "OUT MOTOR\n+/-");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,    ATTR_ON_TEXT,                      "OK MOTOR\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,   ATTR_OFF_TEXT,                     "OK MOTOR\nON/OFF");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,    ATTR_ON_TEXT,                      "AIR PROBE1\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,   ATTR_OFF_TEXT,                     "AIR PROBE1\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,    ATTR_ON_TEXT,                      "AIR PROBE2\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,   ATTR_OFF_TEXT,                     "AIR PROBE2\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,    ATTR_ON_TEXT,                      "SEAT CONFIRM\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,   ATTR_OFF_TEXT,                     "SEAT CONFIRM\nON/OFF");   //불합격

			

			//M_MEAS_TABLE
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 1, ATTR_LABEL_TEXT,             "MEAS. ITEM");   //측정항목
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 3, ATTR_LABEL_TEXT,             "LOWER");       //하한
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 2, ATTR_LABEL_TEXT,             "VALUE");     //측정값 
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 4, ATTR_LABEL_TEXT,             "UPPER");       //상한

	
			//zerosetup		 
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_LABEL_TEXT,                 "SENSE NUMBER");   //대과거영
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 2, ATTR_LABEL_TEXT,           "1ST VALUE");   //과거영점
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 3, ATTR_LABEL_TEXT,                "2ND VALUE");   //현재영점               
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 4, ATTR_LABEL_TEXT,                   "3RD VALUE");   //편차
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 5, ATTR_LABEL_TEXT,                  "DIFF \n(2ND-3RD)");   //-허용편차
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 6, ATTR_LABEL_TEXT,                  "LOWER");   //+허용편차
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 7, ATTR_LABEL_TEXT,                 "UPPER");   //명 칭
			SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL   , ATTR_LABEL_TEXT,                  "ZERO-SET");   //확인
//			SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL_3   , ATTR_LABEL_TEXT,                  "RIGHT ZERO-SET");   //확인
            SetCtrlAttribute (zerosetup  , ZEROSETUP_CLOSE       , ATTR_LABEL_TEXT,                         "RETURN");   //확인
			SetCtrlVal       (zerosetup  , ZEROSETUP_TEXTMSG_2                ,                      "UNIT [um]");   //통신포트 설정

			//dataview
            SetCtrlAttribute (dataview  , DATAVIEW_TITLE          , ATTR_LABEL_TEXT,                    "TITLE");   //제 목
            SetCtrlAttribute (dataview  , DATAVIEW_TOTAL_NUM      , ATTR_LABEL_TEXT,                 "TOTAL NUM");   //전체수량
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_START_NUM, ATTR_LABEL_TEXT,             "START NUM. INPUT");   //시작번호입력
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_DATA_NUM , ATTR_LABEL_TEXT,             "DATA NUM. INPUT");   //데이터수입력
//            SetCtrlAttribute (dataview  , DATAVIEW_REVIEW_COM     , ATTR_LABEL_TEXT,                 "REVIEW");   //다시보기
//            SetCtrlAttribute (dataview  , DATAVIEW_SAVEDATA       , ATTR_LABEL_TEXT,                    "SAVE");   //저 장
//            SetCtrlAttribute (dataview  , DATAVIEW_PRINTING       , ATTR_LABEL_TEXT,               "PRINT");   //흑백프린트
            SetCtrlAttribute (dataview  , DATAVIEW_START_NUM      , ATTR_LABEL_TEXT,                 "START NUM.");   //시작번호
            SetCtrlAttribute (dataview  , DATAVIEW_DATA_NUM       , ATTR_LABEL_TEXT,                 "DATA NUM.");   //데이터수
            SetCtrlAttribute (dataview  , DATAVIEW_CLOSE          , ATTR_LABEL_TEXT,                    "RETURN");   //확 인
 			SetCtrlVal       (dataview  , DATAVIEW_TEXTMSG_4                ,                      "UNIT [um]");   //통신포트 설정
    
	
			//main
			SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO, ATTR_LABEL_TEXT,                       "ALL");   //전체수량
           SetCtrlAttribute (mainpanel,MAINPANEL_LG	     , ATTR_LABEL_TEXT,                       "OK");   //합격수량
            SetCtrlAttribute (mainpanel,MAINPANEL_LNG        , ATTR_LABEL_TEXT,                       "NG");   //불량수량
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,    ATTR_ON_TEXT,                      "OK");   //합 격
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,   ATTR_OFF_TEXT,                     "NG");   //불합격
//			SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO_3, ATTR_LABEL_TEXT,                       "ALL");   //전체수량
    //        SetCtrlAttribute (mainpanel,MAINPANEL_LG_3	     , ATTR_LABEL_TEXT,                       "OK");   //합격수량
   //         SetCtrlAttribute (mainpanel,MAINPANEL_LNG_3        , ATTR_LABEL_TEXT,                       "NG");   //불량수량
	//		SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,    ATTR_ON_TEXT,                      "OK");   //합 격
	//		SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,   ATTR_OFF_TEXT,                     "NG");   //불합격
			SetCtrlAttribute (mainpanel,MAINPANEL_LISTBOX    , ATTR_LABEL_TEXT,                    "NG LIST");   //NG LIST
	//		SetCtrlVal       (mainpanel,MAINPANEL_STRING_4                ,                      "LEFT VANE");   //통신포트 설정
	//		SetCtrlVal       (mainpanel,MAINPANEL_STRING_5                ,                      "RIGHT VANE");   //통신포트 설정
             SetCtrlAttribute (mainpanel,MAINPANEL_ERRVIEW, ATTR_LABEL_TEXT,                   "ALARM VIEW");   //수동측정
          SetCtrlAttribute (mainpanel,MAINPANEL_MANUALCTRL1, ATTR_LABEL_TEXT,                  "MANUAL");   //수동측정
            SetCtrlAttribute (mainpanel,MAINPANEL_ZEROSETUP1 , ATTR_LABEL_TEXT,                      "ZERO SET");   //영점조정
            SetCtrlAttribute (mainpanel,MAINPANEL_MODELSETUP1, ATTR_LABEL_TEXT,                    "MODEL SEL.");   //제품설정
			SetCtrlAttribute (mainpanel,MAINPANEL_MENU_BT       , ATTR_LABEL_TEXT,                        "CONFIG");   //환경 설정 
			SetCtrlAttribute (mainpanel,MAINPANEL_RESULTVIEW1, ATTR_LABEL_TEXT,                        "RESULT");   //결과조회
			SetCtrlAttribute (mainpanel,MAINPANEL_CLOSE ,      ATTR_LABEL_TEXT,                       "EXIT");   //종료 
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_3                ,                      "AMP COM");  //AMP통신   
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_4                ,                      "PLC COM");  //PLC통신   
			
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 1, ATTR_LABEL_TEXT,             "MEAS.ITEM");   //측정항목
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 2, ATTR_LABEL_TEXT,             "VALUE");       //하한
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 3, ATTR_LABEL_TEXT,             "LOWER");     //측정값 
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 4, ATTR_LABEL_TEXT,             "UPPER");       //상한

			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_1        , ATTR_LABEL_TEXT,                    "AUTO RUN");   //자동 운전
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_2        , ATTR_LABEL_TEXT,                    "MEASURING");   //제품 측정중
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_3        , ATTR_LABEL_TEXT,                    "MEASURE END");   //측정 완료
            SetCtrlAttribute (mainpanel,MAINPANEL_LXBAR      , ATTR_LABEL_TEXT,                           "AVR");   //평균
            SetCtrlAttribute (mainpanel,MAINPANEL_LR         , ATTR_LABEL_TEXT,                         "RANGE");   //범위
			SetCtrlAttribute (mainpanel,MAINPANEL_LMAX       , ATTR_LABEL_TEXT,                           "MAX");   //최대값
			SetCtrlAttribute (mainpanel,MAINPANEL_LMIN       , ATTR_LABEL_TEXT,                           "MIN");   //최소값
			SetCtrlAttribute (mainpanel,MAINPANEL_LSTDDIV    , ATTR_LABEL_TEXT,                         "SIGMA");   //표준 편차
			SetCtrlAttribute (mainpanel,MAINPANEL_LCP        , ATTR_LABEL_TEXT,                            "CP");   //CP
			SetCtrlAttribute (mainpanel,MAINPANEL_LCPK       , ATTR_LABEL_TEXT,                           "Cpk");   //Cpk
			
/////
			SetCtrlAttribute (markpanel, MARK_SET_MARKTRANS       , ATTR_LABEL_TEXT,                        "SEND TEXT");   //Cpk
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG                ,                      "USE");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_21                ,                      "MARK TYPE");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_22                ,                      "MARK TEXT");    
			SetCtrlAttribute (workref, WORKREF_SERVO_ALL_SAVE       , ATTR_LABEL_TEXT,                        "POSITION SAVE");   
			
		break;

		case 2:
//			SetCtrlAttribute (optpanel, OPT_SET_LANGUAGE                 , ATTR_LABEL_TEXT,             "言語選擇");   //언어선택
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    0,     "한국어",   0);   //한국어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    1,     "ENGLISH",   1);   //영  어
            ReplaceListItem  (optpanel, OPT_SET_LANGUAGE ,    2,     "中國語",   2);   //중국어

			//비밀 번호  Screen 	
			SetCtrlAttribute (pw,PW_COMMANDBUTTON, ATTR_LABEL_TEXT,               "確認 "); 
			SetCtrlAttribute (pw,PW_CANCEL, ATTR_LABEL_TEXT,              	        "取消");
			SetCtrlAttribute (pw,PW_PW, ATTR_LABEL_TEXT,                 		"秘密 番號 "); 
			SetCtrlAttribute (pw,PW_PW_2, ATTR_LABEL_TEXT,                 		"秘密 番號 "); 
			SetCtrlAttribute (pw,PW_PWCHANGE1, ATTR_LABEL_TEXT,            "秘密 番號 變更 ");
			SetCtrlAttribute (pw,PW_PWCHANGE2, ATTR_LABEL_TEXT,             "變更番號 確認 "); 
//			SetCtrlAttribute (pw,PW_PWCHANGE, ATTR_LABEL_TEXT,               "秘密番號 變更"); 
			

			
			
			//환경 설정  
			SetCtrlAttribute (interdata, INTPANEL_STOREVALIDDAY1, ATTR_LABEL_TEXT,                   "FILE有效貯藏日 ");   //수동측정
			SetCtrlAttribute (interdata, INTPANEL_SETCONTNG1, ATTR_LABEL_TEXT,                        "連續 不良");
			SetCtrlAttribute (interdata, INTPANEL_NG_CHK_FLAG1, ATTR_LABEL_TEXT,                        "使用 設定");
			SetCtrlAttribute (interdata, INTPANEL_CLOSE          , ATTR_LABEL_TEXT,                    "確認");   //확 인 1
	
			SetCtrlAttribute (interdata, INTPANEL_DAYWORKSTART, ATTR_LABEL_TEXT,                        "晝間 作業 START");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART, ATTR_LABEL_TEXT,                        "週中 夜間 作業 START");
			SetCtrlAttribute (interdata, INTPANEL_NIGHTWORKSTART2, ATTR_LABEL_TEXT,                        "週末 夜間 作業 START");
			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_13                ,                      "連續 NG");  //AMP통신   
			SetCtrlVal       (interdata, INTPANEL_TEXTMSG_12               ,                      "再測定 有/無");  //AMP통신   
			
            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,     ATTR_ON_TEXT,                   "再測定 有");   //반복
            SetCtrlAttribute (interdata, INTPANEL_A_RETRY,    ATTR_OFF_TEXT,                    "再測定 無");   //1회  
            SetCtrlAttribute (interdata, INTPANEL_SEPFILE                  , ATTR_LABEL_TEXT,"晝/夜間 FILE 別途 貯藏");   //주/야간 파일 별도 저장      
			
			// 제품 선택 MENU 
			SetCtrlAttribute (workpanel, WORK_SET_MODEL1      , ATTR_LABEL_TEXT,                 "製品選擇");   //제품선택
            SetCtrlAttribute (workpanel, WORK_SET_REMOVEMODEL, ATTR_LABEL_TEXT,                 "製品削除");   //제품삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORK, ATTR_LABEL_TEXT,              "製品名 變更");   //제품명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDMODEL   , ATTR_LABEL_TEXT,                 "製品追加");   //제품추가
            SetCtrlAttribute (workpanel, WORK_SET_WORKER1    , ATTR_LABEL_TEXT,              "勞動者 選擇");   //작업자 선택
            SetCtrlAttribute (workpanel, WORK_SET_REMOVEWORKER, ATTR_LABEL_TEXT,             "勞動者 削除");   //작업자 삭제
            SetCtrlAttribute (workpanel, WORK_SET_RENAMEWORKER, ATTR_LABEL_TEXT,           "勞動者名 變更");   //작업자명 변경
            SetCtrlAttribute (workpanel, WORK_SET_ADDWORKER1   , ATTR_LABEL_TEXT,             "勞動者 追加");   //작업자 추가
            SetCtrlAttribute (workpanel, WORK_SET_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인

			//MENU 
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_1  , ATTR_LABEL_TEXT,              "通信 設定");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_2  , ATTR_LABEL_TEXT,              "LAN 設定");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_3  , ATTR_LABEL_TEXT,              "製品, 勞動者");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_4  , ATTR_LABEL_TEXT,              "測定項目 POSITION");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_5  , ATTR_LABEL_TEXT,              "ERROR 設定");   //COMMUNICATION
			SetCtrlAttribute (menupanel, MENUPANEL_MENU_6  , ATTR_LABEL_TEXT,              "環境 設定");   //COMMUNICATION
            SetCtrlAttribute (menupanel, MENUPANEL_CLOSE_MENU      , ATTR_LABEL_TEXT,                    "確認");   //확 인

			// MENU COMMUNICATION
			SetCtrlVal       (commpanel  , COMM_SET_TEXTMSG_3                ,                      "通信 PORT 設定");   //통신포트 설정
            SetCtrlAttribute (commpanel  , COMM_SET_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인
			SetCtrlAttribute (commpanel  , COMM_SET_PORTPAR                 , ATTR_LABEL_TEXT,           "PORT 設定");   //포트이름
   //         SetCtrlVal       (commpanel  , COMM_SET_PORTNAME                ,                     "PORT 名");   //측정시 설정값
			
			SetCtrlVal       (comconfig1  , COMCONFIG1_TEXTMSG_10                ,                      "RS232 通信 設定");   //통신포트 설정
            SetCtrlAttribute (comconfig1  , COMCONFIG1_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인

			// LAN MENU
			SetCtrlAttribute (lanpanel,LAN_SET_SWITCH_LANUSE, ATTR_LABEL_TEXT,                        "Data 傳送");	//	1
            SetCtrlAttribute (lanpanel,LAN_SET_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인
			// point pos menu
            SetCtrlAttribute (pospanel, POS_SET_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인

			// error message menu
            SetCtrlAttribute (err1panel, ERR_SET_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인
			
			//modelsetup    MODEL 	   사용 불가 문자 : \ / : * ? " < > |
            SetCtrlAttribute (modelsetup,MODELSETUP                , ATTR_LABEL_TEXT,             "製品 設定");   //제품  설정
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 1, ATTR_LABEL_TEXT,             "測定 名");   //측 정 명
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 2, ATTR_LABEL_TEXT,             "補正 値.");   //보 정 값
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 3, ATTR_LABEL_TEXT,             "公差下限");   //공차하한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 4, ATTR_LABEL_TEXT,            "官吏 下限");  //공차상한한  官吏 公差
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 5, ATTR_LABEL_TEXT,            "官吏 上限");  //공차상한한
            SetTableColumnAttribute (modelsetup, MODELSETUP_DATA, 6, ATTR_LABEL_TEXT,            "公差 上限");  //공차상한한
    
            SetCtrlAttribute (modelsetup,MODELSETUP_CLOSE      , ATTR_LABEL_TEXT,                    "確認");   //확 인
			SetCtrlAttribute (modelsetup,MODELSETUP_MODEL      , ATTR_LABEL_TEXT,                 "製品選擇");   //제품선택
            SetCtrlAttribute (modelsetup,MODELSETUP_WORKER     , ATTR_LABEL_TEXT,              "勞動者 選擇");   //작업자 선택
	
            SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEMODEL, ATTR_LABEL_TEXT,                 "製品削除");   //제품삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEMODEL, ATTR_LABEL_TEXT,              "製品名 變更");   //제품명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDMODEL   , ATTR_LABEL_TEXT,                 "製品追加");   //제품추가
            SetCtrlAttribute (modelsetup,MODELSETUP_REMOVEWORKER, ATTR_LABEL_TEXT,             "勞動者 削除");   //작업자 삭제
            SetCtrlAttribute (modelsetup,MODELSETUP_RENAMEWORKER, ATTR_LABEL_TEXT,           "勞動者名 變更");   //작업자명 변경
            SetCtrlAttribute (modelsetup,MODELSETUP_ADDWORKER   , ATTR_LABEL_TEXT,             "勞動者 追加");   //작업자 추가
			
			
			
			//manualctrl
//			SetCtrlVal (manualctrl,MANUALCTRL                                    ,        "SENSOR, 手動 測定");   //센서, 수동 측정
            SetCtrlAttribute (manualctrl,MANUALCTRL_MCYCLEINDEX_1, ATTR_LABEL_TEXT,             "銃測定回數");   //총측정횟수
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLENOSET_1,  ATTR_LABEL_TEXT,            "反復數 設定");   //반복수 설정
            SetCtrlAttribute (manualctrl,MANUALCTRL_CYCLEMODE_1,   ATTR_LABEL_TEXT,           "測定回數條件");   //측정횟수조건
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,     ATTR_ON_TEXT,                   "反復");   //반복
            SetCtrlAttribute (manualctrl, MANUALCTRL_CYCLEMODE_1,    ATTR_OFF_TEXT,                    "1回");   //1회  
            SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_1 , ATTR_LABEL_TEXT,               "測定始作");   //측정시작             
    //        SetCtrlAttribute (manualctrl,MANUALCTRL_MANUALTEST_2 , ATTR_LABEL_TEXT,               "右 測定始作");   //측정시작             
            SetCtrlAttribute (manualctrl,MANUALCTRL_SAVE_1       , ATTR_LABEL_TEXT,             "測定DATA貯藏");   //측정값저장
            SetCtrlAttribute (manualctrl,MANUALCTRL_RESULTVIEW_1 , ATTR_LABEL_TEXT,               "結果確認");   //결괴보기 
			SetCtrlAttribute (manualctrl,MANUALCTRL_CLR_1        , ATTR_LABEL_TEXT,             "測定 削除");   //측정값삭제
            SetCtrlAttribute (manualctrl,MANUALCTRL_CLOSE        , ATTR_LABEL_TEXT,              "復歸");   //메뉴 복귀
	//		SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG      ,          						 "Sensor 値 [um]");   //센 서 값 [um] 
			SetCtrlVal (manualctrl,MANUALCTRL_TEXTMSG_4    ,         						 "反復測定 [um]");   //반복측정값[um] 

			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_2                ,                      "AMP通信");  //AMP통신   
			SetCtrlVal       (manualctrl,MANUALCTRL_TEXTMSG_23                ,                      "PLC通信");  //PLC통신   

				SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,    ATTR_ON_TEXT,                      "製品 入\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL1_2        ,   ATTR_OFF_TEXT,                     "製品 入\n前進/後進");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,    ATTR_ON_TEXT,                      "製品 安着\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL2_2        ,   ATTR_OFF_TEXT,                     "製品 安着\n下降/上昇");   //불합격
	
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,    ATTR_ON_TEXT,                      "UP FIXTURE\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL3_2        ,   ATTR_OFF_TEXT,                     "UP FIXTURE\n下降/上昇");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,    ATTR_ON_TEXT,                      "NG MARK\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL4_2        ,   ATTR_OFF_TEXT,                     "NG MARK\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,    ATTR_ON_TEXT,                      "內徑 移送\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL5_2        ,   ATTR_OFF_TEXT,                     "內徑 移送\n前進/後進");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,    ATTR_ON_TEXT,                      "SIDE DIA1\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL6_2        ,   ATTR_OFF_TEXT,                     "SIDE DIA1\n前進/後進");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,    ATTR_ON_TEXT,                      "SIDE DIA2\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL7_2        ,   ATTR_OFF_TEXT,                     "SIDE DIA2\n前進/後進");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,    ATTR_ON_TEXT,                      "組立內徑PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL8_2        ,   ATTR_OFF_TEXT,                     "組立內徑PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,    ATTR_ON_TEXT,                      "PLATE PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL9_2        ,   ATTR_OFF_TEXT,                     "PLATE PROBE\nON/OFF");   //불합격

			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,    ATTR_ON_TEXT,                      "DIA1 PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL10_2        ,   ATTR_OFF_TEXT,                     "DIA1 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,    ATTR_ON_TEXT,                      "DIA2 PROBE\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL11_2        ,   ATTR_OFF_TEXT,                     "DIA2 PROBE\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,    ATTR_ON_TEXT,                      "製品 停止#1\n上昇/下降");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL12_2        ,   ATTR_OFF_TEXT,                     "製品 停止#1\n上昇/下降");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,    ATTR_ON_TEXT,                      "製品 停止#2\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL13_2        ,   ATTR_OFF_TEXT,                     "製品 停止#2\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,    ATTR_ON_TEXT,                      "投入 電動機\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL14_2        ,   ATTR_OFF_TEXT,                     "投入 電動機\nON/OFF");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,    ATTR_ON_TEXT,                      "製品安着\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL17_2        ,   ATTR_OFF_TEXT,                     "製品安着\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,    ATTR_ON_TEXT,                      "測定部\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL18_2        ,   ATTR_OFF_TEXT,                     "測定部\n前進/後進");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,    ATTR_ON_TEXT,                      "測定部\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL19_2        ,   ATTR_OFF_TEXT,                     "測定部\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,    ATTR_ON_TEXT,                      "電動機\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL20_2        ,   ATTR_OFF_TEXT,                     "電動機\n+/-");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,    ATTR_ON_TEXT,                      "刻印機\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL24_2        ,   ATTR_OFF_TEXT,                     "刻印機\n前進/後進");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL25_2        ,    ATTR_ON_TEXT,                      "製品固定\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL25_2        ,   ATTR_OFF_TEXT,                     "製品固定\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL27_2        ,    ATTR_ON_TEXT,                      "電動機\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL27_2        ,   ATTR_OFF_TEXT,                     "電動機\n+/-");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL28_2        ,    ATTR_ON_TEXT,                      "製品安着\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL28_2        ,   ATTR_OFF_TEXT,                     "製品安着\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL29_2        ,    ATTR_ON_TEXT,                      "製品 停止#1\n上昇/下降");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL29_2        ,   ATTR_OFF_TEXT,                     "製品 停止#1\n上昇/下降");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,    ATTR_ON_TEXT,                      "製品 停止#2\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL30_2        ,   ATTR_OFF_TEXT,                     "製品 停止#2\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,    ATTR_ON_TEXT,                      "移送部\n前進/後進");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL31_2        ,   ATTR_OFF_TEXT,                     "移送部\n前進/後進");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,    ATTR_ON_TEXT,                      "移送 上下\n下降/上昇");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL32_2        ,   ATTR_OFF_TEXT,                     "移送 上下\n下降/上昇");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,    ATTR_ON_TEXT,                      "製品固定\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL33_2        ,   ATTR_OFF_TEXT,                     "製品固定\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,    ATTR_ON_TEXT,                      "排出 電動機\n+/-");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL34_2        ,   ATTR_OFF_TEXT,                     "排出 電動機\n+/-");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,    ATTR_ON_TEXT,                      "OK 電動機\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL35_2        ,   ATTR_OFF_TEXT,                     "OK 電動機\nON/OFF");   //불합격
			
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,    ATTR_ON_TEXT,                      "測定器 空氣1\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL37_2        ,   ATTR_OFF_TEXT,                     "測定器 空氣1\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,    ATTR_ON_TEXT,                      "測定器 空氣2\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL38_2        ,   ATTR_OFF_TEXT,                     "測定器 空氣2\nON/OFF");   //불합격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,    ATTR_ON_TEXT,                      "安着 SOL\nON/OFF");   //합 격
			SetCtrlAttribute (manualctrl,MANUALCTRL_SOL40_2        ,   ATTR_OFF_TEXT,                     "安着 SOL\nON/OFF");   //불합격

			 //M_MEAS_TABLE
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 1, ATTR_LABEL_TEXT,             "測定項目");   //측정항목
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 3, ATTR_LABEL_TEXT,             "下限");       //하한
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 2, ATTR_LABEL_TEXT,             "測定 値.");     //측정값 
			SetTableColumnAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, 4, ATTR_LABEL_TEXT,             "上限");       //상한


			//zerosetup		 
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_LABEL_TEXT,                 "SENSOR 番號");   //센서 번호
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 2, ATTR_LABEL_TEXT,           "以前1 \n測定VAL");   //오래된 \n측정값
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 3, ATTR_LABEL_TEXT,                "以前2測定VAL");   //이전측정값              
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 4, ATTR_LABEL_TEXT,             "現在 \n測定VAL");   //현재 \n측정값
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 5, ATTR_LABEL_TEXT,         "偏差\n(以前-現在)");   //편차\n(이전-현재)
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 6, ATTR_LABEL_TEXT,                  "SENSOR下限");   //센서하한
            SetTableColumnAttribute (zerosetup, ZEROSETUP_DATA_JNL, 7, ATTR_LABEL_TEXT,                  "SENSOR上限");   //센서상한
			SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL   , ATTR_LABEL_TEXT,                  "零點調整");   //영점조정
	//		SetCtrlAttribute (zerosetup  , ZEROSETUP_DOZEROSET_JNL_3   , ATTR_LABEL_TEXT,                  "右 零點調整");   //영점조정
            SetCtrlAttribute (zerosetup  , ZEROSETUP_CLOSE       , ATTR_LABEL_TEXT,                         "確認");   //확인
			SetCtrlVal       (zerosetup  , ZEROSETUP_TEXTMSG_2                ,                      "單位 [um]");   //통신포트 설정

			//dataview
            SetCtrlAttribute (dataview  , DATAVIEW_TITLE          , ATTR_LABEL_TEXT,                    "題目");   //제 목
            SetCtrlAttribute (dataview  , DATAVIEW_TOTAL_NUM      , ATTR_LABEL_TEXT,                 "全體數量");   //전체수량
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_START_NUM, ATTR_LABEL_TEXT,             "始作番號入力");   //시작번호입력
            SetCtrlAttribute (dataview  , DATAVIEW_INPUT_DATA_NUM , ATTR_LABEL_TEXT,             "DATA數 入力");   //데이터수입력
//            SetCtrlAttribute (dataview  , DATAVIEW_REVIEW_COM     , ATTR_LABEL_TEXT,                 "REVIEW");   //다시보기
//            SetCtrlAttribute (dataview  , DATAVIEW_SAVEDATA       , ATTR_LABEL_TEXT,                    "貯 藏");   //저 장
//            SetCtrlAttribute (dataview  , DATAVIEW_PRINTING       , ATTR_LABEL_TEXT,               "PRINT");   //흑백프린트
            SetCtrlAttribute (dataview  , DATAVIEW_START_NUM      , ATTR_LABEL_TEXT,                 "始作番號");   //시작번호
            SetCtrlAttribute (dataview  , DATAVIEW_DATA_NUM       , ATTR_LABEL_TEXT,                 "DATA數");   //데이터수
            SetCtrlAttribute (dataview  , DATAVIEW_CLOSE          , ATTR_LABEL_TEXT,                    "確認");   //확 인
			SetCtrlVal       (dataview  , DATAVIEW_TEXTMSG_4                ,                      "單位 [um]");   //통신포트 설정
    
			//main
			SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO, ATTR_LABEL_TEXT,                       "全 體");   //전체수량
            SetCtrlAttribute (mainpanel,MAINPANEL_LG	     , ATTR_LABEL_TEXT,                       "合格");   //합격수량
            SetCtrlAttribute (mainpanel,MAINPANEL_LNG        , ATTR_LABEL_TEXT,                       "不良");   //불량수량
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,    ATTR_ON_TEXT,                      "合格");   //합 격
			SetCtrlAttribute (mainpanel,MAINPANEL_GNG        ,   ATTR_OFF_TEXT,                     "不良");   //불합격
	//		SetCtrlAttribute (mainpanel,MAINPANEL_TOTALTESTNO_3, ATTR_LABEL_TEXT,                       "全 體");   //전체수량
    //        SetCtrlAttribute (mainpanel,MAINPANEL_LG_3	     , ATTR_LABEL_TEXT,                       "合格");   //합격수량
   //         SetCtrlAttribute (mainpanel,MAINPANEL_LNG_3        , ATTR_LABEL_TEXT,                       "不良");   //불량수량
	//		SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,    ATTR_ON_TEXT,                      "合格");   //합 격
	//		SetCtrlAttribute (mainpanel,MAINPANEL_GNG_3        ,   ATTR_OFF_TEXT,                     "不良");   //불합격
			SetCtrlAttribute (mainpanel,MAINPANEL_LISTBOX    , ATTR_LABEL_TEXT,                    "不良 LIST");   //NG LIST
	//		SetCtrlVal       (mainpanel,MAINPANEL_STRING_4                ,                      "左 VANE");   //통신포트 설정
//			SetCtrlVal       (mainpanel,MAINPANEL_STRING_5                ,                      "右 VANE");   //통신포트 설정
             SetCtrlAttribute (mainpanel,MAINPANEL_ERRVIEW, ATTR_LABEL_TEXT,                   "ALARM");   //수동측정

			 SetCtrlAttribute (mainpanel,MAINPANEL_MANUALCTRL1, ATTR_LABEL_TEXT,                   "手動 測定");   //수동측정
            SetCtrlAttribute (mainpanel,MAINPANEL_ZEROSETUP1 , ATTR_LABEL_TEXT,                   "零點調定");   //영점조정
            SetCtrlAttribute (mainpanel,MAINPANEL_MODELSETUP1, ATTR_LABEL_TEXT,                   "製品設定");   //제품설정
			SetCtrlAttribute (mainpanel,MAINPANEL_MENU_BT       , ATTR_LABEL_TEXT,                  "環境 設定");   //환경 설정 
			SetCtrlAttribute (mainpanel,MAINPANEL_RESULTVIEW1, ATTR_LABEL_TEXT,                   "結果照會");   //결과조회
			SetCtrlAttribute (mainpanel,MAINPANEL_CLOSE ,      ATTR_LABEL_TEXT,                       "退出");   //종료 
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_3                ,                      "AMP通信");  //AMP통신   
			SetCtrlVal       (mainpanel,MAINPANEL_HHMMSS_4                ,                      "PLC通信");  //PLC통신   

			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 1, ATTR_LABEL_TEXT,             "測定項目");   //측정항목
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 2, ATTR_LABEL_TEXT,             "測定 値");       //하한
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 3, ATTR_LABEL_TEXT,             "下限.");     //측정값 
			SetTableColumnAttribute (mainpanel,MAINPANEL_A_TABLE, 4, ATTR_LABEL_TEXT,             "上限");       //상한
			
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_1        , ATTR_LABEL_TEXT,                    "自動運轉");   //자동 운전
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_2        , ATTR_LABEL_TEXT,                    "自動測定");   //제품 측정중
			SetCtrlAttribute (mainpanel,MAINPANEL_LED_MC_3        , ATTR_LABEL_TEXT,                    "測定完了");   //측정 완료

            SetCtrlAttribute (mainpanel,MAINPANEL_LXBAR      , ATTR_LABEL_TEXT,                       "平均");   //평균
            SetCtrlAttribute (mainpanel,MAINPANEL_LR         , ATTR_LABEL_TEXT,                       "範圍");   //범위
			SetCtrlAttribute (mainpanel,MAINPANEL_LMAX       , ATTR_LABEL_TEXT,                     "最大");   //최대값
			SetCtrlAttribute (mainpanel,MAINPANEL_LMIN       , ATTR_LABEL_TEXT,                     "最小");   //최소값
			SetCtrlAttribute (mainpanel,MAINPANEL_LSTDDIV    , ATTR_LABEL_TEXT,                  "標準 偏差");   //표준 편차
			SetCtrlAttribute (mainpanel,MAINPANEL_LCP        , ATTR_LABEL_TEXT,                         "CP");   //CP
			SetCtrlAttribute (mainpanel,MAINPANEL_LCPK       , ATTR_LABEL_TEXT,                        "Cpk");   //Cpk
	
/////
			SetCtrlAttribute (markpanel, MARK_SET_MARKTRANS       , ATTR_LABEL_TEXT,                        "文字 傳送");   //Cpk
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG                ,                      "USE");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_21                ,                      "MARK TYPE");    
			SetCtrlVal       (markpanel, MARK_SET_TEXTMSG_22                ,                      "MARK 文字");    
			SetCtrlAttribute (workref, WORKREF_SERVO_ALL_SAVE       , ATTR_LABEL_TEXT,                        "POSITION 貯藏");   
			
		break;
	}
}

int CVICALLBACK EncRatioset (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK:                                                    
			switch(control)                                                       
			{                                                                     
				case INTPANEL_ROLLER_DIA:		// 위상각 기구 옵셋량(도)         
					callKEYPAD(panel, control, event, NON_TABLE, &Roller_Dia,0); 
					break;                                                        
				case INTPANEL_WORK_DIA:
					callKEYPAD(panel, control, event, NON_TABLE, &Work_Dia,0);
					break;
			   case INTPANEL_NICK_COMP:
					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Comp1[0],0);
					break;
			   case INTPANEL_NICK_COMP_2:
					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Comp1[1],0);
					break;
			   case INTPANEL_NICK_COMP_3:
					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Comp1[2],0);
					break;
			   case INTPANEL_NICK_COMP_4:
					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Comp1[3],0);
					break;
			}                                                                     
			
	}
	return 0;
}

int CVICALLBACK Enc_Dir (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
 					GetCtrlVal(interdata, INTPANEL_ENC_DIR, &EncDir);

			break;
	}
	return 0;
}

int CVICALLBACK Enc_Pls_Num (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &EncPlsNum,0);

			break;
	}
	return 0;
}

int CVICALLBACK Enc_Channel (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &EncChannel,0);

			break;
	}
	return 0;
}

int CVICALLBACK Nick_Value_Set (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Value[0],0);

			break;
	}
	return 0;
}

int CVICALLBACK Nick_Cut_Set (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Cut,0);

			break;
	}
	return 0;
}

int CVICALLBACK Z_Phase_Set (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}
void	Empty_Work(int  Check)
{
	int   ST1_count=0,meas_point=0, j;
	

	if(Check==0)
	{
			//SetCtrlAttribute(mainpanel, MAINPANEL_GNG_2, ATTR_VISIBLE, FALSE);
			//SetCtrlAttribute(mainpanel, MAINPANEL_RANK_UD, ATTR_VISIBLE, FALSE);

		for(j = 0; j < MAX_EQU; j++)
		{
			if(Pgm[j].Sig ==1 && Pgm[j].Disp)			
			{
				EquResult2_Temp[j]=9999.9; 
			}

		}
		return;
	}
	
	if(Check==1)
	{
		
		for(j = 0; j < MAX_EQU; j++)
		{
			if(Pgm[j].Disp )			
			{
				// 화면 표시 0.000, 바탕 색은 흰색
				SetCtrlAttribute(mainpanel, *(PointCtrl+ST1_count+meas_point), ATTR_TEXT_BGCOLOR, VAL_WHITE);
				SetCtrlAttribute(mainpanel, *(PointCtrl+ST1_count+meas_point), ATTR_TEXT_COLOR, VAL_WHITE);
			    Mc[0].Mode[0].FinalResult[ST1_count+meas_point][Mc[0].Mode[0].EdDataNum - 1]=0.000;
				meas_point++;
			}

		}
		Mc[McID].Mode[ModeID].CycleIndex--;
		Mc[McID].Mode[ModeID].EdDataNum--;

	}

}

int CVICALLBACK Nick_Value_Set2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Value[1],0);

			break;
	}
	return 0;
}

int CVICALLBACK Nick_Value_Set3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
// 					GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
 					callKEYPAD(panel, control, event, NON_TABLE, &Nick_Value[2],0);

			break;
	}
	return 0;
}
 void	ReadSenval(void)
{
	int 	i, j,k, no, h_file, fileSize;
	char	lineBuff[1024];
	int		flag;
	char	Temp[30], DateStamp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product\\");
	sprintf(Temp, "%s\\", ModelName[ModelID]);
	strcat(WorkingDirectory, Temp);
	strcat(WorkingDirectory, "data");
	

// Project Directory로 환원
//	SetDir (WorkingDirectory);		
	strcat(WorkingDirectory, "\\senval.da0");
	

    
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);

	
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	
		for(j=0;j<4000;j++)
		{
			flag = ReadLine (h_file, lineBuff, -1); // 제품명
			if(flag == -2) // end of file
					break;

			Scan(lineBuff,"%s>%i%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
												&no,& RepeatChVal[j][0],& RepeatChVal[j][1],& RepeatChVal[j][2],& RepeatChVal[j][3],& RepeatChVal[j][4],& RepeatChVal[j][5],& RepeatChVal[j][6],& RepeatChVal[j][7],
												& RepeatChVal[j][8],& RepeatChVal[j][9],& RepeatChVal[j][10],& RepeatChVal[j][11],& RepeatChVal[j][12],& RepeatChVal[j][13],& RepeatChVal[j][14],& RepeatChVal[j][15],
												& RepeatChVal[j][16],& RepeatChVal[j][17],& RepeatChVal[j][18],& RepeatChVal[j][19],& RepeatChVal[j][20],& RepeatChVal[j][21],& RepeatChVal[j][22],& RepeatChVal[j][23]);
			
			
				RepeatEncVal[j] = RepeatChVal[j][7];
//				RepeatEncVal[0][j] = RepeatChVal[j][7];
//				RepeatEncVal[1][j] = RepeatChVal[j][15];
//				RepeatEncVal[2][j] = RepeatChVal[j][23];

		}

	
		RepeatChIndex = no-1;	
	
	CloseFile( h_file );
	
	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		
		
		for(k = 0; k < DISP_CH; k++)
		{
			RepeatChValBase[i][k]=RepeatChVal[i][k];
		}
	}
	

		
		
	RepeatChIndexBase = RepeatChIndex;
	
	
	
}

 void	ReadSenval1(void)
{
	int 	i, j,k,  no, h_file, fileSize;
	char	lineBuff[1024];
	int		flag;
	char	Temp[30], DateStamp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product\\");
	sprintf(Temp, "%s\\", ModelName[ModelID]);
	strcat(WorkingDirectory, Temp);
	strcat(WorkingDirectory, "data");
	

// Project Directory로 환원
//	SetDir (WorkingDirectory);		
	strcat(WorkingDirectory, "\\senval.da1");
	

    
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);

	
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	
		for(j=0;j<4000;j++)
		{
			flag = ReadLine (h_file, lineBuff, -1); // 제품명
			if(flag == -2) // end of file
					break;

			Scan(lineBuff,"%s>%i%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
												&no,& RepeatChVal[j][0],& RepeatChVal[j][1],& RepeatChVal[j][2],& RepeatChVal[j][3],& RepeatChVal[j][4],& RepeatChVal[j][5],& RepeatChVal[j][6],& RepeatChVal[j][7],
												& RepeatChVal[j][8],& RepeatChVal[j][9],& RepeatChVal[j][10],& RepeatChVal[j][11],& RepeatChVal[j][12],& RepeatChVal[j][13],& RepeatChVal[j][14],& RepeatChVal[j][15],
												& RepeatChVal[j][16],& RepeatChVal[j][17],& RepeatChVal[j][18],& RepeatChVal[j][19],& RepeatChVal[j][20],& RepeatChVal[j][21],& RepeatChVal[j][22],& RepeatChVal[j][23]);
			
			
//				RepeatEncVal[j] = RepeatChVal[j][7];
//				RepeatEncVal[0][j] = RepeatChVal[j][7];
//				RepeatEncVal[1][j] = RepeatChVal[j][15];
//				RepeatEncVal[2][j] = RepeatChVal[j][23];

		}

	
		RepeatChIndex = no-1;	
	
	CloseFile( h_file );

	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		
		
		for(k = 0; k < DISP_CH; k++)
		{
			RepeatChValBase[i][k]=RepeatChVal[i][k];
		}
	}
	

		
		
	RepeatChIndexBase = RepeatChIndex;


}

 void	ReadSenval2(void)
{
	int 	i, j,k,  no, h_file, fileSize;
	char	lineBuff[1024];
	int		flag;
	char	Temp[30], DateStamp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product\\");
	sprintf(Temp, "%s\\", ModelName[ModelID]);
	strcat(WorkingDirectory, Temp);
	strcat(WorkingDirectory, "data");
	

// Project Directory로 환원
//	SetDir (WorkingDirectory);		
	strcat(WorkingDirectory, "\\senval.da2");
	

    
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);

	
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	
		for(j=0;j<4000;j++)
		{
			flag = ReadLine (h_file, lineBuff, -1); // 제품명
			if(flag == -2) // end of file
					break;

			Scan(lineBuff,"%s>%i%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
												&no,& RepeatChVal[j][0],& RepeatChVal[j][1],& RepeatChVal[j][2],& RepeatChVal[j][3],& RepeatChVal[j][4],& RepeatChVal[j][5],& RepeatChVal[j][6],& RepeatChVal[j][7],
												& RepeatChVal[j][8],& RepeatChVal[j][9],& RepeatChVal[j][10],& RepeatChVal[j][11],& RepeatChVal[j][12],& RepeatChVal[j][13],& RepeatChVal[j][14],& RepeatChVal[j][15],
												& RepeatChVal[j][16],& RepeatChVal[j][17],& RepeatChVal[j][18],& RepeatChVal[j][19],& RepeatChVal[j][20],& RepeatChVal[j][21],& RepeatChVal[j][22],& RepeatChVal[j][23]);
			
			
//				RepeatEncVal[j] = RepeatChVal[j][7];
//				RepeatEncVal[0][j] = RepeatChVal[j][7];
//				RepeatEncVal[1][j] = RepeatChVal[j][15];
//				RepeatEncVal[2][j] = RepeatChVal[j][23];

		}

	
		RepeatChIndex = no-1;	
	
	CloseFile( h_file );

	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		
		
		for(k = 0; k < DISP_CH; k++)
		{
			RepeatChValBase[i][k]=RepeatChVal[i][k];
		}
	}
	

		
		
	RepeatChIndexBase = RepeatChIndex;


}
 
 void	ReadSenval3(void)
{
	int 	i, j,k,  no, h_file, fileSize;
	char	lineBuff[1024];
	int		flag;
	char	Temp[30], DateStamp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product\\");
	sprintf(Temp, "%s\\", ModelName[ModelID]);
	strcat(WorkingDirectory, Temp);
	strcat(WorkingDirectory, "data");
	

// Project Directory로 환원
//	SetDir (WorkingDirectory);		
	strcat(WorkingDirectory, "\\senval.da3");
	

    
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);

	
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	ReadLine (h_file, lineBuff, -1); // 제품명
	
		for(j=0;j<4000;j++)
		{
			flag = ReadLine (h_file, lineBuff, -1); // 제품명
			if(flag == -2) // end of file
					break;

			Scan(lineBuff,"%s>%i%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f%f",
												&no,& RepeatChVal[j][0],& RepeatChVal[j][1],& RepeatChVal[j][2],& RepeatChVal[j][3],& RepeatChVal[j][4],& RepeatChVal[j][5],& RepeatChVal[j][6],& RepeatChVal[j][7],
												& RepeatChVal[j][8],& RepeatChVal[j][9],& RepeatChVal[j][10],& RepeatChVal[j][11],& RepeatChVal[j][12],& RepeatChVal[j][13],& RepeatChVal[j][14],& RepeatChVal[j][15],
												& RepeatChVal[j][16],& RepeatChVal[j][17],& RepeatChVal[j][18],& RepeatChVal[j][19],& RepeatChVal[j][20],& RepeatChVal[j][21],& RepeatChVal[j][22],& RepeatChVal[j][23]);
			
			
//				RepeatEncVal[j] = RepeatChVal[j][7];
//				RepeatEncVal[0][j] = RepeatChVal[j][7];
//				RepeatEncVal[1][j] = RepeatChVal[j][15];
//				RepeatEncVal[2][j] = RepeatChVal[j][23];

		}

	
		RepeatChIndex = no-1;	
	
	CloseFile( h_file );

	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		
		
		for(k = 0; k < DISP_CH; k++)
		{
			RepeatChValBase[i][k]=RepeatChVal[i][k];
		}
	}
	

		
		
	RepeatChIndexBase = RepeatChIndex;


}

 void Model_Histogram(int j, int startPos,int	measNum)
{
 	int 	i;
	double	Step;
	double	OK_G[6], NG_G[6],PG_G[6];
	double	N_Center[5], P_Center[5], M_Center[5];
	double	Center_Hist[30];
	int		Y_1[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// = {5,5,6,0,0,0,0,0,0,0, 12, 13, 14, 15, 16, 17, 18 };//, 19, 11, 12,0,0,0,0,0,0,0,0,0,0};
    int		Y_Data[500];
	double 	Graph_Data1[500];// graph의 histogram 용
//    int startPos, measNum;

	
// 			GetCtrlVal (chartview, CHARTVIEW_INPUT_START_NUM, &startPos);
//			GetCtrlVal (chartview, CHARTVIEW_INPUT_DATA_NUM, &measNum);
	
	Step = (Model[j].PTol - Model[j].NTol)/5.;
	
	OK_G[0] = Model[j].NTol; // OK항목에서의 범위
	NG_G[0] = Model[j].NTol - (Model[j].PTol - Model[j].NTol); // -NG에서의 범위
	PG_G[0] = Model[j].PTol;								   // +NG에서의 범위
	
	for(i=1;i<6;i++)	 // -Ng에서의 histogram의 중간 값 표시
	{
		NG_G[i] = NG_G[0] + (i) * Step;
		N_Center[i-1] = (NG_G[i] + NG_G[i-1])/2.;
		Center_Hist[i-1] = N_Center[i-1];
	}


	for(i=1;i<6;i++)	 // ok에서의 histogram의 중간 값 표시
	{
		OK_G[i] = OK_G[0] + (i) * Step;
		M_Center[i-1] = (OK_G[i] + OK_G[i-1])/2.;
		Center_Hist[i+5-1] = M_Center[i-1];
	}

	for(i=0;i<measNum;i++)
		  Graph_Data1[i] = SpcData[j][i];

	for(i=1;i<6;i++)   // +Ng에서의 histogram의 중간 값 표시
	{
		PG_G[i] = PG_G[0] + (i) * Step;
		P_Center[i-1] = (PG_G[i] + PG_G[i-1])/2.;
		Center_Hist[i+10-1] = P_Center[i-1];
	}
	
    for(i=0;i< measNum;i++)
    {
        Y_Data[i]=(int)((Graph_Data1[i]-NG_G[0])/Step) +1;
    	if(Y_Data[i]<=1) Y_1[0] ++;
    	else if(Y_Data[i] > 15) Y_1[14] ++;
    	else Y_1[Y_Data[i]-1]++;

    }

    for(i=measNum;i< 500;i++)
    {
        Y_Data[i]=0;
    
    }

			 DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH_HIS,-1,VAL_IMMEDIATE_DRAW);
			
//		    SetAxisScalingMode (printing_image, PRINTING_GRAPH2,VAL_XAXIS  , VAL_MANUAL, 0.0,(double)31 );
//			SetAxisScalingMode (printing_image, PRINTING_GRAPH2, VAL_LEFT_YAXIS, VAL_MANUAL, 0.0,
//								(double)(15+1));
		
//			SPCDrawHistogram(printing_image, PRINTING_GRAPH2, -1, Center_Hist, Y_1, 30);//DispYesNo);

//		    SetAxisScalingMode (printing_image, PRINTING_GRAPH2,VAL_XAXIS  , VAL_MANUAL, 0.0,(double)1 );
//			SetAxisScalingMode (printing_image, PRINTING_GRAPH2, VAL_LEFT_YAXIS, VAL_MANUAL, 0.0,
//								(double)(25+1));
			
			SPCDrawHistogram(mainpanel, MAINPANEL_GRAPH_HIS, -1, Center_Hist, Y_1, 15);//DispYesNo);

}

void	Calc_Order(int ch1, int ch2, int no)
{
	
	int	i, j;
	double   DTV_temp[MAX_ACQ_CH_PER_CYCLE];
	double	T_temp = 0.0;//total sum
//	double  S_temp[50];  // 판정을 내리기 위한 차수에서의 값 
	double		Max, Min;
	int			Order_Min=7,MaxIndex, MinIndex;
	double PI=3.14159;
	
	
	
/////////////////////
      for(i=0 ; i< RepeatChIndex; i++) //dtv data 
          DTV_temp[i] = 0.0;// 각 순간의 두께값 저장

	
	// DTV값 저장
      for(i=0 ; i< RepeatChIndex; i++) //dtv data 
          DTV_temp[i] = RepeatChVal[i][ch1-1]+RepeatChVal[i][ch2-1];// 각 순간의 두께값 저장

// 정현파, 여현파 분석
	  for(i=0;i<RepeatChIndex;i++)
	  {
	  	for(j=Order_Min;j<Order_Limit;j++)
	  	{
	  		D_sin[i][j] = DTV_temp[i]*sin(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지
	  																// 각도는 0도부터 0.5증가	
	  		D_cos[i][j] = DTV_temp[i]*cos(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지	
	  	}
	  }

		T_temp = 0.0;

	 for(j=Order_Min;j<Order_Limit;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
		 	T_temp = T_temp + D_sin[i][j];
	 
	 	T_sin[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }
		T_temp = 0.0;

	 for(j=Order_Min;j<Order_Limit;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
	 	T_temp = T_temp + D_cos[i][j];
	 
	 	T_cos[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }
		T_temp = 0.0;

	for(j=Order_Min;j<Order_Limit;j++)
		S_fft[GSt1Sig-1][j-Order_Min] = 2 * sqrt(T_sin[j]*T_sin[j] + T_cos[j]*T_cos[j])*0.9;

	MaxMin1D(S_fft[GSt1Sig-1],Order_Limit-Order_Min , &Max, &MaxIndex, &Min, &MinIndex);
	
	Max_Order[no-1] = Max*((double)Order_Per/100.0);   //차 수 계산 분리
	Deg_Order[no-1] = MaxIndex+Order_Min+1;
	
	
//	sprintf(ctemp, "(max Order,%d, %f)...", Deg_Order, Max_Order );
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, ctemp);
}

void	Calc_Order_L(int ch1, int ch2, int no)
{
	
	int	i, j;
	double   DTV_temp[MAX_ACQ_CH_PER_CYCLE];
	double	T_temp = 0.0;//total sum
//	double  S_temp[50];  // 판정을 내리기 위한 차수에서의 값 
	double		Max, Min;
	int			MaxIndex, MinIndex;
	double PI=3.14159;
	
	
	
/////////////////////

	
	// DTV값 저장
      for(i=0 ; i< RepeatChIndex; i++) //dtv data 
          DTV_temp[i] = RepeatChVal[i][ch1-1]+RepeatChVal[i][ch2-1];// 각 순간의 두께값 저장

// 정현파, 여현파 분석
	  for(i=0;i<RepeatChIndex;i++)
	  {
	  	for(j=1;j<7;j++)
	  	{
	  		D_sin[i][j] = DTV_temp[i]*sin(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지
	  																// 각도는 0도부터 0.5증가	
	  		D_cos[i][j] = DTV_temp[i]*cos(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지	
	  	}
	  }

		T_temp = 0.0;

	 for(j=1;j<7;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
		 	T_temp = T_temp + D_sin[i][j];
	 
	 	T_sin[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }
		T_temp = 0.0;

	 for(j=1;j<7;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
	 	T_temp = T_temp + D_cos[i][j];
	 
	 	T_cos[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }

	for(j=1;j<7;j++)
		S_fft[GSt1Sig-1][j-1] = 2 * sqrt(T_sin[j]*T_sin[j] + T_cos[j]*T_cos[j]);

	MaxMin1D(S_fft[GSt1Sig-1],6 , &Max, &MaxIndex, &Min, &MinIndex);
	
	Max_Order_L[no-1] = Max*((double)Order_Per/100.0);   //차 수 계산 분리
	Deg_Order_L[no-1] = MaxIndex+2;
	
	
//	sprintf(ctemp, "(max Order,%d, %f)...", Deg_Order, Max_Order );
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, ctemp);
}

void	Calc_Order_Test(int ch1, int ch2, int no)
{
	
	int	i, j;
	double   DTV_temp[MAX_ACQ_CH_PER_CYCLE];
	double	T_temp = 0.0;//total sum
//	double  S_temp[50];  // 판정을 내리기 위한 차수에서의 값 
	double		Max, Min;
	int			Order_Min=0,MaxIndex, MinIndex;
	double PI=3.14159;
	char  temp[512],temp1[20];
	
	
	
/////////////////////
      for(i=0 ; i< RepeatChIndex; i++) //dtv data 
          DTV_temp[i] = 0.0;// 각 순간의 두께값 저장

	
	// DTV값 저장
      for(i=0 ; i< RepeatChIndex; i++) //dtv data 
          DTV_temp[i] = RepeatChVal[i][ch1-1]+RepeatChVal[i][ch2-1];// 각 순간의 두께값 저장

// 정현파, 여현파 분석
	  for(i=0;i<RepeatChIndex;i++)
	  {
	  	for(j=Order_Min;j<Order_Limit;j++)
	  	{
	  		D_sin[i][j] = DTV_temp[i]*sin(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지
	  																// 각도는 0도부터 0.5증가	
	  		D_cos[i][j] = DTV_temp[i]*cos(2*PI* (i*360.0/(double)RepeatChIndex) *(j+1)/(360.0)); 	// DATA *sin(2*pi/360 *각도*차수)
	  																// 차수는 1차부터 50차수까지	
	  	}
	  }

		T_temp = 0.0;

	 for(j=Order_Min;j<Order_Limit;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
		 	T_temp = T_temp + D_sin[i][j];
	 
	 	T_sin[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }
		T_temp = 0.0;

	 for(j=Order_Min;j<Order_Limit;j++)
	 {
	 	for(i=0;i<RepeatChIndex;i++)
	 	T_temp = T_temp + D_cos[i][j];
	 
	 	T_cos[j] = 2*T_temp/RepeatChIndex;
		T_temp = 0.0;
	 }
		T_temp = 0.0;

	sprintf(temp,"order");
	for(j=Order_Min;j<Order_Limit;j++)
	{
		S_fft[GSt1Sig-1][j-Order_Min] = 2 * sqrt(T_sin[j]*T_sin[j] + T_cos[j]*T_cos[j]);
		sprintf(temp1,"%f", S_fft[GSt1Sig-1][j-Order_Min]);
		strcat(temp, temp1);
	}
	
	
	LogDataFunc(temp, 1);

	MaxMin1D(S_fft[GSt1Sig-1],Order_Limit-Order_Min , &Max, &MaxIndex, &Min, &MinIndex);
	
	Max_Order[no-1] = Max*((double)Order_Per/100.0);   //차 수 계산 분리
	Deg_Order[no-1] = MaxIndex+Order_Min+1;
	
	
//	sprintf(ctemp, "(max Order,%d, %f)...", Deg_Order, Max_Order );
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, ctemp);
}



void Initial_CW3D(void)
{
   CAObjHandle     plot = 0;
	
	GetObjHandleFromActiveXCtrl(mainpanel, MAINPANEL_CWGRAPH, &gGraph);
    GetPlot(&plot);
    CW3DGraphLib_CWPlot3DSetStyle(plot, NULL, CW3DGraphLibConst_cwHiddenLine);
    CW3DGraphLib_CWPlot3DSetColorMapAutoScale(plot, NULL, VFALSE);
    CW3DGraphLib_CWPlot3DSetColorMapInterpolate(plot, NULL, VTRUE);
    CW3DGraphLib_CWPlot3DSetColorMapLog(plot, NULL, VFALSE);
    CW3DGraphLib_CWPlot3DSetColorMapStyle(plot, NULL,CW3DGraphLibConst_cwColorSpectrum);
    RefreshControls();
    	CWGraphPlot();
		

}

static HRESULT RefreshControls(void)
{
    HRESULT                                     hr;
    CAObjHandle                                 plot = 0;
    enum CW3DGraphLibEnum_CWPlot3DStyles        style;
    enum CW3DGraphLibEnum_CWColorMapStyles      colorMapStyle;
    VBOOL                                       autoscale, 
                                                interpolate, 
                                                logarithmic;
    
    hrChk (GetPlot(&plot));
    hrChk (CW3DGraphLib_CWPlot3DGetStyle(plot, NULL, &style));
    SetCtrlVal(interdata, INTPANEL_CWSURFACE, style == CW3DGraphLibConst_cwSurface);
 
	hrChk (CW3DGraphLib_CWPlot3DGetColorMapAutoScale(plot, NULL, &autoscale));
 

	hrChk (CW3DGraphLib_CWPlot3DGetColorMapStyle(plot, NULL, &colorMapStyle));
    SetCtrlIndex(interdata, INTPANEL_CWSTYLE, colorMapStyle);

	RefreshCustomColorControls();
	
Error:
    CA_DiscardObjHandle(plot);
    return hr;
}
void  CWGraphPlot(void) //초기 그림
{
  HRESULT     hr;
    VARIANT     xVt, yVt, zVt;
	double PI=3.14159;
	
    int         i, j;
    double      factor;
                double  t[SIZE], xData[SIZE][SIZE], yData[SIZE][SIZE], 
                        zData[SIZE][SIZE];
    
            CA_VariantSetEmpty(&xVt);
            CA_VariantSetEmpty(&yVt);
            CA_VariantSetEmpty(&zVt);
            

                for (i = 0; i < SIZE; ++i)
                    t[i] = PI*i*2/180;
//			   j=0;
				for (i = 0; i < SIZE; ++i)
                    for(j = 0; j < SIZE1; ++j)
                        {
//                        xData[j][i] = (cos(t[j]) + 3.0) * cos(t[i]);
//                        yData[j][i] = (cos(t[j]) + 3.0) * sin(t[i]);
//                        zData[j][i] = sin(t[j]) + 2.0;
                        xData[j][i] = (150+j*10) * cos(t[i]);
                        yData[j][i] = (150+j*10) * sin(t[i]);
                        zData[j][i] =  rand()*0.00005;//(double)j*0.2;
                        }
                hrChk (CA_VariantSet2DArray(&xVt, CAVT_DOUBLE, SIZE,10,  xData));
                hrChk (CA_VariantSet2DArray(&yVt, CAVT_DOUBLE, SIZE,10,  yData));
                hrChk (CA_VariantSet2DArray(&zVt, CAVT_DOUBLE, SIZE,10, zData));

				hrChk (CW3DGraphLib__DCWGraph3DPlot3DParametricSurface(gGraph, 
                    NULL, xVt, yVt, zVt, CA_DEFAULT_VAL));
            
            if (IsColorMapCustom())
                hrChk (SetCustomColorMap());

Error:
            if (FAILED(hr))
                CA_DisplayErrorInfo(0, "ActiveX Error", hr, NULL);
            CA_VariantClear(&xVt);
            CA_VariantClear(&yVt);
            CA_VariantClear(&zVt);

}

static HRESULT GetPlot(CAObjHandle *plot)
{
    HRESULT         hr;
    CAObjHandle     plots = 0;
    
    hrChk (CW3DGraphLib__DCWGraph3DGetPlots(gGraph, NULL, &plots));
    hrChk (CW3DGraphLib_CWPlots3DItem(plots, NULL, CA_VariantInt(1), plot));
    
Error:
    CA_DiscardObjHandle(plots);
    return hr;
}


int CVICALLBACK CwStyle (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  HRESULT         hr;
    CAObjHandle     plot = 0;
    int             style;

    switch (event)
        {
        case EVENT_COMMIT:
            hrChk (GetPlot(&plot));
            GetCtrlVal(interdata, INTPANEL_CWSTYLE, &style);
            hrChk (CW3DGraphLib_CWPlot3DSetColorMapStyle(plot, NULL, style));
            RefreshCustomColorControls();
            if (style == CW3DGraphLibConst_cwCustom)
                hrChk (SetCustomColorMap());
Error:
            if (FAILED(hr))
                CA_DisplayErrorInfo(0, "ActiveX Error", hr, NULL);
            CA_DiscardObjHandle(plot);
            break;
        }
    return 0;
}

int CVICALLBACK ColorCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
   HRESULT         hr;

    switch (event)
        {
        case EVENT_COMMIT:
            hrChk (SetCustomColorMap());
Error:
            if (FAILED(hr))
                CA_DisplayErrorInfo(0, "ActiveX Error", hr, NULL);
            break;
        }
    return 0;
}

int CVICALLBACK SurfaceCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
   HRESULT         hr;
    CAObjHandle     plot = 0;
    int             surface;
    
    switch (event)
        {
        case EVENT_COMMIT:
            hrChk (GetPlot(&plot));
            GetCtrlVal(interdata, INTPANEL_CWSURFACE, &surface);
            hrChk (CW3DGraphLib_CWPlot3DSetStyle(plot, NULL, surface 
                ? CW3DGraphLibConst_cwSurface : CW3DGraphLibConst_cwHiddenLine));
Error:
            if (FAILED(hr))
                CA_DisplayErrorInfo(0, "ActiveX Error", hr, NULL);
            CA_DiscardObjHandle(plot);
            break;
        }
    return 0;
}
static void RefreshCustomColorControls(void)
{
    int     enable;
    
    enable = IsColorMapCustom();
    SetCtrlAttribute(interdata, INTPANEL_COLOR1, ATTR_DIMMED, !enable);
    SetCtrlAttribute(interdata, INTPANEL_COLOR2, ATTR_DIMMED, !enable);
    SetCtrlAttribute(interdata, INTPANEL_COLOR3, ATTR_DIMMED, !enable);
    SetCtrlAttribute(interdata, INTPANEL_COLOR4, ATTR_DIMMED, !enable);
    SetCtrlAttribute(interdata, INTPANEL_COLOR5, ATTR_DIMMED, !enable);
}
static int IsColorMapCustom(void)
{
    HRESULT                                 hr;
    CAObjHandle                             plot = 0;
    enum CW3DGraphLibEnum_CWColorMapStyles  colorMapStyle 
                                                = CW3DGraphLibConst_cwNone;
    
    hrChk (GetPlot(&plot));
    hrChk (CW3DGraphLib_CWPlot3DGetColorMapStyle(plot, NULL, &colorMapStyle));

Error:
    CA_DiscardObjHandle(plot);
    return colorMapStyle == CW3DGraphLibConst_cwCustom;
}
 static HRESULT SetCustomColorMap(void)
{
    HRESULT         hr;
    CAObjHandle     plot = 0, zAxis = 0;
    double          max, min, interval, mapValues[NUM_CUSTOM_COLORS];
    VARIANT         maxVt, minVt, valuesVt, colorsVt;
    int             i;
    unsigned int    mapColors[NUM_CUSTOM_COLORS];
    
    CA_VariantSetEmpty(&maxVt);
    CA_VariantSetEmpty(&minVt);
    CA_VariantSetEmpty(&valuesVt);
    CA_VariantSetEmpty(&colorsVt);
    
    hrChk (GetPlot(&plot));
    hrChk (CW3DGraphLib_CWPlot3DGetZAxis(plot, NULL, &zAxis));
    
    hrChk (CW3DGraphLib_CWAxis3DGetMaximum(zAxis, NULL, &maxVt));
    hrChk (CW3DGraphLib_CWAxis3DGetMinimum(zAxis, NULL, &minVt));
    hrChk (CA_VariantGetDouble(&maxVt, &max));
    hrChk (CA_VariantGetDouble(&minVt, &min));
    interval = (max - min) / NUM_CUSTOM_COLORS;
    
    for (i = 0; i < NUM_CUSTOM_COLORS; ++i)
        {
        int color;
        mapValues[i] = min + (i * interval);
        GetCtrlVal(mainpanel, gColorCtrls[i], &color);
        mapColors[NUM_CUSTOM_COLORS - 1 - i] = ((color & 0xff) << 16) 
            | (color & 0xff00) | ((color & 0xff0000) >> 16);
        }
    
    hrChk (CA_VariantSet1DArray(&valuesVt, CAVT_DOUBLE, 
        NUM_CUSTOM_COLORS, mapValues));
    hrChk (CA_VariantSet1DArray(&colorsVt, CAVT_INT, 
        NUM_CUSTOM_COLORS, mapColors));
    
    hrChk (CW3DGraphLib_CWPlot3DSetColorMapValues(plot, NULL, valuesVt));
    hrChk (CW3DGraphLib_CWPlot3DSetColorMapColors(plot, NULL, colorsVt));
    
Error:
    CA_VariantClear(&valuesVt);
    CA_VariantClear(&colorsVt);
    CA_VariantClear(&maxVt);
    CA_VariantClear(&minVt);

    CA_DiscardObjHandle(zAxis);
    CA_DiscardObjHandle(plot);
    return hr;
}
void  CWGraphPlot_Auto2(void) //측정모드
{
  HRESULT     hr;
    VARIANT     xVt, yVt, zVt;
	double PI=3.14159;
	
    int         i, j;
    double      factor;
                double  t[SIZE], xData[SIZE][SIZE], yData[SIZE][SIZE], 
                        zData[SIZE][SIZE];
    
            CA_VariantSetEmpty(&xVt);
            CA_VariantSetEmpty(&yVt);
            CA_VariantSetEmpty(&zVt);
            

                for (i = 0; i < SIZE; ++i)
                    t[i] = PI*i*2/180;
//			   j=0;
				for (i = 0; i < SIZE; ++i)
				{
					//                        xData[j][i] = (cos(t[j]) + 3.0) * cos(t[i]);
//                        yData[j][i] = (cos(t[j]) + 3.0) * sin(t[i]);
//                        zData[j][i] = sin(t[j]) + 2.0;
                        xData[0][i] = (250) * cos(t[i]);
                        yData[0][i] = (250) * sin(t[i]);
                      
						////  2도 단위의 data를 넣어야 한다.
						zData[0][i] =  UpChVal[0][i*2]/1000 + DnChVal[0][i*2]/1000;//rand()*0.0001;//(double)j*0.2;
                }
				for (i = 0; i < SIZE; ++i)
				{//                        xData[j][i] = (cos(t[j]) + 3.0) * cos(t[i]);
//                        yData[j][i] = (cos(t[j]) + 3.0) * sin(t[i]);
//                        zData[j][i] = sin(t[j]) + 2.0;
                        xData[1][i] = (250-100) * cos(t[i]);
                        yData[1][i] = (250-100) * sin(t[i]);
                      
						////  2도 단위의 data를 넣어야 한다.
						zData[1][i] =  UpChVal[1][i*2]/1000 + DnChVal[1][i*2]/1000;//rand()*0.0001;//(double)j*0.2;
                }

				hrChk (CA_VariantSet2DArray(&xVt, CAVT_DOUBLE, 2,SIZE,  xData));
                hrChk (CA_VariantSet2DArray(&yVt, CAVT_DOUBLE, 2,SIZE, yData));
                hrChk (CA_VariantSet2DArray(&zVt, CAVT_DOUBLE, 2,SIZE,  zData));

				hrChk (CW3DGraphLib__DCWGraph3DPlot3DParametricSurface(gGraph, 
                    NULL, xVt, yVt, zVt, CA_DEFAULT_VAL));
            
			hrChk (CW3DGraphLib__DCWGraph3DPlot3DParametricSurface(gGraph, 
                    NULL, xVt, yVt, zVt, CA_DEFAULT_VAL));
            
            if (IsColorMapCustom())
                hrChk (SetCustomColorMap());

Error:
            if (FAILED(hr))
                CA_DisplayErrorInfo(0, "ActiveX Error", hr, NULL);
            CA_VariantClear(&xVt);
            CA_VariantClear(&yVt);
            CA_VariantClear(&zVt);

}

int CVICALLBACK Mark_Type_Func (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_1, &Mark_Type1[0]);
			if(Mark_Type1[0] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_1, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_1, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_2, &Mark_Type1[1]);
			if(Mark_Type1[1] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_2, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_2, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_3, &Mark_Type1[2]);
			if(Mark_Type1[2] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_3, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_3, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_4, &Mark_Type1[3]);
			if(Mark_Type1[3] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_4, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_4, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_5, &Mark_Type1[4]);
			if(Mark_Type1[4] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_5, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_5, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_6, &Mark_Type1[5]);
			if(Mark_Type1[5] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_6, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_6, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_7 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_7, &Mark_Type1[6]);
			if(Mark_Type1[6] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_7, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_7, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Type_Func_8 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:

			GetCtrlIndex ( markpanel, MARK_SET_MARK_TYPE_8, &Mark_Type1[7]);
			if(Mark_Type1[7] == 4)
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_8, ATTR_VISIBLE, 1);
			else
				SetCtrlAttribute (markpanel, MARK_SET_MARK_TEXT_8, ATTR_VISIBLE, 0);
				
				

			break;
	}
	return 0;
}
/*
void JSenValSave_1(void)	  //여기서부터 해야함. 141216
{
	int		i, j, k;
	int		fileHandle;
	char	lineBuff[MAX_CH * 13], ctemp[30], ctemp1[30];
	double	data[50];
	double		Max, Min,Mean;
	int			MaxIndex, MinIndex;
	
	FileReName(); // 
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA\\senval.da0");
	fileHandle = OpenFile(WorkingDirectory,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	strcpy(lineBuff, "**** 측정용 센서값 저장 ****");
	WriteLine(fileHandle, lineBuff, -1);

	// 센서값 읽음 횟수 저장
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", "센서읽은 수량:");
	strcat(lineBuff, ctemp1);
	
	sprintf(ctemp, "Sig1: %d", RepeatChIndex);
	sprintf(ctemp1, "%12s", ctemp);
	strcat(lineBuff, ctemp1);
	WriteLine(fileHandle, lineBuff, -1);
	
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", " ");
	strcat(lineBuff, ctemp1);
	
	for( j = 0; j < DISP_CH;j++ )
	{
		sprintf(ctemp, "CH%d", j + 1);
		sprintf(ctemp1, "%12s", ctemp);
		strcat(lineBuff, ctemp1);
	}
	
	WriteLine(fileHandle, lineBuff, -1);
	


		
	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		lineBuff[0] = 0;
		sprintf(ctemp1, "%12d", i + 1);
		strcat(lineBuff, ctemp1);
		
		for(k = 0; k < DISP_CH; k++)
		{
			sprintf(ctemp1, "%12.1f", RepeatChVal[i][k]);
			strcat(lineBuff, ctemp1);
		}
		WriteLine(fileHandle, lineBuff, -1);
	}

	CloseFile(fileHandle);
}
*/

void JSenValSave1(void)
{
	int		i, j, k, no;
	int		fileHandle;
	char	lineBuff[MAX_CH * 13], ctemp[60], ctemp1[30],TimeStamp[30];
	double	data[50], sep;
	double		Max, Min,Mean;
	int			MaxIndex, MinIndex;
	double		ChVal_720[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
//	FileReName(); // 
	
	sprintf(ctemp, "%s", DateStr());
	strcat(ctemp,"-");
	sprintf(TimeStamp, "%s", TimeStr());
	CopyBytes(TimeStamp, 2, "-", 0, 1);
	CopyBytes(TimeStamp, 5, "-", 0, 1);
	TimeStamp[8]=0X00;
	
	strcat(ctemp, TimeStamp);
	strcat(ctemp, ".ORD");
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA\\ORD\\");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성
	
	strcat(WorkingDirectory, ctemp);
	
	fileHandle = OpenFile(WorkingDirectory,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	strcpy(lineBuff, "**** 측정용 센서값 저장 ****");
	WriteLine(fileHandle, lineBuff, -1);

	// 센서값 읽음 횟수 저장
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", "센서읽은 수량:");
	strcat(lineBuff, ctemp1);
	
	sprintf(ctemp, "Sig1: %d", RepeatChIndex);
	sprintf(ctemp1, "%12s", ctemp);
	strcat(lineBuff, ctemp1);
	WriteLine(fileHandle, lineBuff, -1);
	
	lineBuff[0] = 0;
	sprintf(ctemp1, "%12s", " ");
	strcat(lineBuff, ctemp1);
	
	for( j = 0; j < 5;j++ )
	{
		sprintf(ctemp, "CH%d", j + 1);
		sprintf(ctemp1, "%12s", ctemp);
		strcat(lineBuff, ctemp1);
	}
		sprintf(ctemp, "DTV");
		sprintf(ctemp1, "%12s", ctemp);
		strcat(lineBuff, ctemp1);
	
	WriteLine(fileHandle, lineBuff, -1);
	
	
	for( i = 0; i < RepeatChIndex; i++ ) // 
	{
		lineBuff[0] = 0;
		sprintf(ctemp1, "%12d", i + 1);
		strcat(lineBuff, ctemp1);
		
		for(k = 0; k < 5; k++)
		{
			sprintf(ctemp1, "%12.1f", RepeatChVal[i][k]);
			strcat(lineBuff, ctemp1);
		}

			sprintf(ctemp1, "%12.1f", RepeatChVal[i][1]+RepeatChVal[i][3]);
			strcat(lineBuff, ctemp1);
		
		WriteLine(fileHandle, lineBuff, -1);
	}

	CloseFile(fileHandle);
}
/////////////

void	ReadMeasData(void)
{
	int 	no, flag, i, h_file, fileSize;
	char	lineBuff[512],temp[20],temp1[20];
	char	FoldName[100], GNG_FRF[10][20];

	
	GetCtrlVal(interdata, INTPANEL_MEAS_FOLD, FoldName);

	strcpy(WorkingDirectory, FoldName);
	//	저장 Directory 설정

// Project Directory로 환원
	SetDir (PrjDirectory);


	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE,VAL_ASCII);
	
		if(h_file==-1)
		{
			LogDataFunc("FRF DATA READ FILE ERROR", 1);
			return;
		}
//		fileSize = strlen(lineBuff);
		flag = ReadLine (h_file, lineBuff, -1); // 

			Scan(lineBuff,"%s>%s%d", 
				temp, &no, &FRF_PTol[i],&Meas_Data[i*2],&Meas_Data[i*2+1]);
		
		for(i=0;i<no;i++)
		{
		flag = ReadLine (h_file, lineBuff, -1); // 
			if(flag == -2) // end of file
					break;
			Scan(lineBuff,"%s>%s%f%f%f%f", 
				GNG_FRF[i], &FRF_NTol[i], &FRF_PTol[i],&Meas_Data[i*2],&Meas_Data[i*2+1]);

		}
		
		CloseFile( h_file );
	
    //        DeleteFile (FoldName);
		
		
    }
	
	
	 else
	 {
		
	 }
	
}

void CVICALLBACK Work_Data (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	
	
			SetCtrlVal(workref, WORKREF_SERVO_POS_1, Servo_Position[0]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_2, Servo_Position[1]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_3, Servo_Position[2]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_4, Servo_Position[3]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_5, Servo_Position[4]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_6, Servo_Position[5]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_7, Servo_Position[6]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_8, Servo_Position[7]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_9, Servo_Position[8]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_10, Servo_Position[9]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_11, Servo_Position[10]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_12, Servo_Position[11]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_13, Servo_Position[12]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_14, Servo_Position[13]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_15, Servo_Position[14]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_16, Servo_Position[15]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_17, Servo_Position[16]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_18, Servo_Position[17]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_19, Servo_Position[18]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_20, Servo_Position[19]);
		SetCtrlVal(workref, WORKREF_SERVO_POS_21, Servo_Position[20]);
	
		
		SetCtrlVal(workref, WORKREF_SHAFT_LOW, Shaft_Low);
		SetCtrlVal(workref, WORKREF_SHAFT_HIGH, Shaft_High);
		SetCtrlVal(workref, WORKREF_TUBE_LOW, Tube_Low);
		SetCtrlVal(workref, WORKREF_TUBE_HIGH, Tube_High);
		SetCtrlVal(workref, WORKREF_RETRY_SET_VALUE, Retry_Data);
		
		SetCtrlVal(workref, WORKREF_YAXIS_LOW, YaxisLow);
		SetCtrlVal(workref, WORKREF_YAXIS_HIGH, YaxisHigh);
			SetActivePanel(workref);

}

int CVICALLBACK Servo_All_Save1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

		GetCtrlVal(workref, WORKREF_SERVO_POS_1, &Servo_Position[0]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_2, &Servo_Position[1]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_3, &Servo_Position[2]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_4, &Servo_Position[3]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_5, &Servo_Position[4]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_6, &Servo_Position[5]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_7, &Servo_Position[6]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_8, &Servo_Position[7]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_9, &Servo_Position[8]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_10, &Servo_Position[9]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_11, &Servo_Position[10]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_12, &Servo_Position[11]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_13, &Servo_Position[12]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_14, &Servo_Position[13]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_15, &Servo_Position[14]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_16, &Servo_Position[15]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_17, &Servo_Position[16]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_18, &Servo_Position[17]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_19, &Servo_Position[18]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_20, &Servo_Position[19]);
		GetCtrlVal(workref, WORKREF_SERVO_POS_21, &Servo_Position[20]);
		
		
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_1, Servo_Position[0]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_2, Servo_Position[1]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_3, Servo_Position[2]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_4, Servo_Position[3]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_5, Servo_Position[4]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_6, Servo_Position[5]);
		SetCtrlVal(modelsetup, MODELSETUP_SERVO_POS_7, Servo_Position[6]);
		
		GetCtrlVal(workref, WORKREF_SHAFT_LOW, &Shaft_Low);
		GetCtrlVal(workref, WORKREF_SHAFT_HIGH, &Shaft_High);
		GetCtrlVal(workref, WORKREF_TUBE_LOW, &Tube_Low);
		GetCtrlVal(workref, WORKREF_TUBE_HIGH, &Tube_High);

		GetCtrlVal(workref, WORKREF_RETRY_SET_VALUE, &Retry_Data);

		GetCtrlVal(workref, WORKREF_YAXIS_LOW, &YaxisLow);
		GetCtrlVal(workref, WORKREF_YAXIS_HIGH, &YaxisHigh);
		
		
		
	
			break;
	}
	return 0;
}
void	A_Model_Change(int	no)
{
	
		int			BitMapID;
		int		i, ModelCheckNo;
		unsigned	long bPos;
		int	a[8];
		
		
		
		
	ModelCheckNo = no-1;
	
		
		if((ModelCheckNo == ModelID) ||(ModelCheckNo < 0))
			return;
	
		ModelID =  ModelCheckNo ;
		SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);			

		WriteModelData();
			ModelChanged();

					GetModelTableData();
					
					strcpy(MainPicName, PrjDirectory);
					strcat(MainPicName, "\\WorkImage\\");
					strcat(MainPicName, ModelName[ModelID]);
					strcat(MainPicName, ".bmp");

					if( !GetBitmapFromFile (MainPicName, &BitMapID))
					{
						SetCtrlBitmap (mainpanel, MAINPANEL_PICTURE, 0X00, BitMapID);
					}

					
					
					GetDataFileName( (char *)NULL); // 새로만듦
					GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
					
					SetSpcPrecision();
					SetGraphTol();
					GraphPlot();
					
					SetManuCtrlTableData(); // 공차가 변경되었을 수 있으므로
 					Set_MeasData();
					
}
void	ReadModelVarData2(void)
{
	int 	h_file, fileSize, i;
	char	lineBuff[200];
	char 	data[8][512];
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ModelVar2.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE,VAL_ASCII);
	
			

		for(i=0;i<7;i++)
		{
			ReadLine (h_file, lineBuff, -1); 
			strcpy(Model_Char[i],lineBuff);
			
//			Scan(lineBuff,"%s>%30s",Mark_Text[i]);
		}
		
		
		
		CloseFile( h_file );
		
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_1, Model_Char[0]); //업체 코드
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_2, Model_Char[1]); //품번
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_3, Model_Char[2]); //ALC
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_4, Model_Char[3]); //EO CODE
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_5, Model_Char[4]); //LINE
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_6, Model_Char[5]); //LINE
		SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_7, Model_Char[6]); //LINE
	
		
//					sprintf(ModelName2[ModelID],"%s",Model_Char[1]);
		
//		for(i=0;i<10;i++)
//			SetCtrlVal(workref, Sensor_OnCtrl[i], Sensor_OnOff[i]);
		
//		for(i=0;i<10;i++)
//			calc_out_data(pc97+i, Sensor_OnOff[i]); 
		
		
    }
	 else
	 {
	 
	 }
//		Enc_Ratio = ( Roller_Dia / Work_Dia ) ;
	
}

void	SaveModelVarData2(void)
{
	int 	h_file, i;
	char    lineBuff[200];
	
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\ModelVar2.DAT");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	 							 

	for(i=0;i<7;i++)
	{
		sprintf(lineBuff,"%s",Model_Char[i]);
		WriteLine(h_file,  lineBuff, -1);
	}

	CloseFile( h_file );
}
