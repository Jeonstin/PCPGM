#include "MSG.h"
#include <formatio.h>
#include "main.h"
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include <userint.h>
#include "manual.h"
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "keycode.h"

int		MarkFont[3], MarkHeight[3], MarkPitch[3], MarkPosX[3], MarkPosY[3], MarkDir[3], MarkWidthLimit[3];
int		MarkUseFlag[3], MarkInitRunFlag[3];
char	MarkDataSetStr0[30]; // 기호로 저장되어 있다.
char	MarkDataSetStr1[30]; // 기호로 저장되어 있다.
char	MarkDataSetStr2[30]; // 기호로 저장되어 있다.


//char	CurrMarkStr[4][40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr0[40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr1[40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr2[40]; // 기호를 변환하여 만든 마킹 문자열

//int		MarkOrgStat; // 마킹헤더 원점 상태
//int		MarkRdyStat; // 마킹헤더 준비 상태(마킹위치에서 정지 상태)
//int		MarkEndStat; // 마킹헤더 완료 상태(마킹후 정지 상태)
char	MarkInBuff[80]; // 마킹기의 응답문자 버퍼
int		MarkInBuffIdx;  // 마킹기 버퍼의 기록할 위치 버퍼

 int		SendMarkingLabel;
	char YY_end1[10];
	char  Bar_Month1[10]; 
	char  Bar_Date1[10];
	int	Mark_End_Flag=0;
	

void	ReadMarkData(void)
{
	int 	h_file, fileSize;
	int 	i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\marker.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
		for(i = 0; i < 3; i++)
		{
			ReadFile(h_file, (char *)&MarkFont[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkHeight[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPitch[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPosX[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPosY[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkDir[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkWidthLimit[i], sizeof(int));
			
		}
		ReadFile(h_file, MarkDataSetStr0, 25); 
		ReadFile(h_file, MarkDataSetStr1, 25); 
		MarkDataSetStr0[25] = 0; 
		MarkDataSetStr1[25] = 0; 
		CloseFile( h_file );
		
		SetCtrlIndex(markpanel, MARK_SET_MARKFONT, MarkFont[0]);
		//SetCtrlIndex(markpanel, MARKPANEL_MARKDIR, MarkDir[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKDIR, MarkDir[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKHEIGHT, MarkHeight[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPITCH, MarkPitch[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPOSX, MarkPosX[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPOSY, MarkPosY[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKWDLIMIT, MarkWidthLimit[0]);
		
		
    	MarkPosX[1] = MarkPosY[1] = 10; 
    	MarkPosX[2] = MarkPosY[2] = 10; 
    	
    	
		MarkHeight[1] = MarkPitch[1] = 10;
		MarkHeight[2] = MarkPitch[2] = 10;
    	
    	MarkWidthLimit[1] = 150;
    	MarkWidthLimit[2] = 150;
    	
    	MarkDataSetStr1[0] = 0;
    	MarkDataSetStr2[0] = 0;
    	
    	MarkDir[1] = 0;
    	MarkDir[2] = 270;
    	
    	MarkFont[1] = 0;
    	MarkFont[2] = 0;
				
		
	}
    else
    {
    	MarkPosX[0] = MarkPosY[0] = 10;
    	MarkPosX[1] = MarkPosY[1] = 10; 
    	MarkPosX[2] = MarkPosY[2] = 10; 
    	
    	
    	MarkHeight[0] = MarkPitch[0] = 10;
		MarkHeight[1] = MarkPitch[1] = 10;
		MarkHeight[2] = MarkPitch[2] = 10;
    	
    	MarkWidthLimit[0] = 150;
    	MarkWidthLimit[1] = 150;
    	MarkWidthLimit[2] = 150;
    	
    	MarkDataSetStr0[0] = 0; 
    	MarkDataSetStr1[0] = 0;
    	MarkDataSetStr2[0] = 0;
    	
    	MarkDir[0] = 270;
    	MarkDir[1] = 0;
    	MarkDir[2] = 270;
    	
    	MarkFont[0] = 0;
    	MarkFont[1] = 0;
    	MarkFont[2] = 0;
    	
    }
}

void	SaveMarkData(void)
{
	int 	h_file;
	int 	i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\marker.dat");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);

	for(i = 0; i < 3; i++)
	{
		WriteFile(h_file, (char *)&MarkFont[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkHeight[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPitch[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPosX[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPosY[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkDir[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkWidthLimit[i], sizeof(int));
	 }
	 WriteFile(h_file, MarkDataSetStr0, 25); 
	 WriteFile(h_file, MarkDataSetStr1, 25); 
	CloseFile( h_file );
}


void  RereadMarkData(void)
{
	
	GetCtrlVal(markpanel, MARK_SET_MARKHEIGHT, &MarkHeight[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPITCH, &MarkPitch[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPOSX, &MarkPosX[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPOSY, &MarkPosY[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKWDLIMIT, &MarkWidthLimit[0]);

	
	
	
	
}



int CVICALLBACK MarkFontCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlIndex(panel, control, &MarkFont[0]);

			break;
	}
	return 0;
}

int CVICALLBACK MarkHeightCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPitchCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPosXCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPosYCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkDirCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &MarkDir[0]);

			break;
	}
	return 0;
}

int CVICALLBACK MarkTestStrSend (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
		for(i=0;i<8;i++)
		{
			if(Mark_OnOff[i])
				Mark_Rot_No = i;
		
		}

			 SendMarkingDataLabel();
					Start_Mark = 0;
					MarkSend_No = 0;
			 	Bar_Send_Flag = 1; 
			break;
	}
	return 0;
}

int CVICALLBACK MarkWidthLimitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkStrSetChkCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				SetCtrlVal(panel, MARK_SET_MARKTESTSTR, CurrMarkStr0);

			break;
	}
	return 0;
}

int CVICALLBACK MarkStartCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc134, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc134, 0); // 
			break;
	}
	return 0;
}

void	MarkStartFunc(void)
{
	char	temp[50], ctemp[50];
	
	if(SendMarkingLabel && (MarkPortNo !=0) )  
	{
		if( AUX1PortOpenErr )
			return;
		else
		{
			FlushOutQ(MarkPortNo);  

		 }
	}
			//각인 start
			sprintf(temp, "%cU", 0x02); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02x%c", temp,Sum, 0x03); 
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));


//	if(SendMarkingLabel && (MarkPortNo !=0) )    
//		ComWrt(MarkPortNo, ctemp, strlen(ctemp));
		
}

int CVICALLBACK MarkStopCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	ctemp[20];
	
	
	switch (event)
		{
		case EVENT_COMMIT:
		if( AUX1PortOpenErr ) break;
			FlushOutQ(MarkPortNo);
			sprintf(ctemp, "%c", 0x18); // 선택된 폰트정보 전송
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));
			break;
		}
	return 0;
}

int CVICALLBACK MarkResetCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	ctemp[20];
	
	switch (event)
		{
		case EVENT_COMMIT:
		if( AUX1PortOpenErr ) break;
			FlushOutQ(MarkPortNo);
			sprintf(ctemp, "%c%%%c", 0x1b, 0x0d); // MARKING START
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));
			break;
		}
	return 0;
}

void	On_Marking(void)
{

//		calc_out_data(pc54, 0); // 마킹 전송 완료 clear
 //			SendMarkingLabel = 1; //마킹 시작
//		calc_out_data(pc53, 1); // 마킹중
//		SetCtrlVal(mainpanel, MAINPANEL_MARKLED,1);
		

}


void Make_YYMMDD(void)
{
  //  char BarCode_Command[1024];
//	char Command_data[512];
	int  iTemp;
	char temp[20], DateStamp[20];
	
		sprintf(temp, "%s", DateStr());
		MakeDateStr(DateStamp, temp);
	
//		if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
//			GetBeforeDay( DateStamp );
	
		DateStamp[4] = 0;
		iTemp = atoi(DateStamp) - 2013;
		sprintf(YY_end1,"%c", ((iTemp) + 'A')); // 년: 2020:A, 2021:B, ~

		strcpy(temp, &DateStamp[5]);
		temp[2] = 0;
		iTemp = atoi(temp) ;
		sprintf(Bar_Month1,"%c", (iTemp-1 + 'A')); // 년: 2020:A, 2021:B, ~

		strcpy(temp, &DateStamp[8]);
		temp[2] = 0;
		iTemp = atoi(temp);
		if( iTemp <27 )
			sprintf(Bar_Date1,"%c", (iTemp-1 + 'A')); // 년: 2020:A, 2021:B, ~
		else
			sprintf(Bar_Date1,"%d",iTemp-26 ); 

}


void	SendMarkingDataLabel(void)   //AUX02
{

	char	temp[50], ctemp[50], data[50];
	int i = 0,j,  x,y,z;
	int PortNo = MarkPortNo;
	

		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);
	
     AUX1PortSendErr=RESET;
	
//	FlushOutQ(PortNo);

	Read_MarkSet();
	Make_YYMMDD();
	
	for(i=0;i<8;i++)
	{

			
			//각인 동작 유무
			sprintf(temp, "%cS%d%d", 0x02,i+1,Mark_OnOff[i]); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][0], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
			//시작점
		
			x = (int)(Mark_X[i]*10.0);
			y = (int)(Mark_Y[i]*10.0);
			z = (int)(Mark_Z[i]*10.0);
			
			sprintf(temp, "%cO%d%0004d%0004d%0004d", 0x02,i+1, x,y,z); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][1], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//			SleepFunc(200); // 10 ms delay

		
			// 회전각도
			sprintf(temp, "%cQ%d%003d", 0x02,i+1, Mark_Rot[i]*90); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][2], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay

			sprintf(data,"");
			if(Mark_Type1[i] == 0)
			{
				sprintf(data,"%%1@");	
			}
			else if(Mark_Type1[i] == 1)
			{
				sprintf(data,"%%2@");	
			}
			else if(Mark_Type1[i] == 2)
			{
					sprintf(data,"%s%s%s",YY_end1,Bar_Month1, Bar_Date1);
//					sprintf(data,"%s%s%s%d",YY_end1,Bar_Month1, Bar_Date1,Line_Name);
					
			}
			else if(Mark_Type1[i] == 3)
			{
				sprintf(data,"%00005d",Mark_Cnt_No);	
			}
			else if(Mark_Type1[i] == 4)
			{
				sprintf(data,"%s",Mark_Text[i]);	
			}
			else if(Mark_Type1[i] == 5)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"A");
				else
					sprintf(data,"B");
					
			}
			else if(Mark_Type1[i] == 6)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s A %00005d",YY_end1,Bar_Month1, Bar_Date1,Mark_Cnt_No);
				else
					sprintf(data,"%s%s%s B %00005d",YY_end1,Bar_Month1, Bar_Date1,Mark_Cnt_No);
					
			}
			else if(Mark_Type1[i] == 7)//년월일 조별
			{
//				if(DayOrNightWork==0)//주간
//					sprintf(data,"%s%s%s A",YY_end1,Bar_Month1, Bar_Date1);
//				else
//					sprintf(data,"%s%s%s B",YY_end1,Bar_Month1, Bar_Date1);
					sprintf(data,"%s%s%s%d",YY_end1,Bar_Month1, Bar_Date1,Line_Name);
					
			}

			
			j = strlen(data);
			
			sprintf(temp, "%c%c%c%02d%s%c", 0x01, 0x31, 0x02,i*2+1, data, 0x03); 
			
			Calc_Check_Sum(temp);
//			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(ctemp, "%s%c", temp, 0x0D); 
//			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%c", temp, 0x0D); 

			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);

	
}

void	A_MarkingDataLabel(void)   //AUX02
{

	char	temp[50], ctemp[50], data[50];
	int i = 0,j,  x,y,z;
	int PortNo = MarkPortNo;
	
	SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);

//	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	
	Make_YYMMDD();
	sprintf(Bar_Data," ");
	for(i=0;i<8;i++)
	{
			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i] == 0)
			{
				sprintf(data,"%%1@");	
			}
			else if(Mark_Type1[i] == 1)
			{
				sprintf(data,"%%2@");	
			}
			else if(Mark_Type1[i] == 2)
			{
//					sprintf(data,"%s%s%s%d",YY_end1,Bar_Month1, Bar_Date1,Line_Name);
					sprintf(data,"%s%s%s",YY_end1,Bar_Month1, Bar_Date1);
					
			}
			else if(Mark_Type1[i] == 3)
			{
				sprintf(data,"%00005d",Mark_Cnt_No);	
			}
			else if(Mark_Type1[i] == 4)
			{
				sprintf(data,"%s",Mark_Text[i]);	
			}
			else if(Mark_Type1[i] == 5)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"A");
				else
					sprintf(data,"B");
					
			}
			else if(Mark_Type1[i] == 6)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s A %00005d",YY_end1,Bar_Month1, Bar_Date1,Mark_Cnt_No);
				else
					sprintf(data,"%s%s%s B %00005d",YY_end1,Bar_Month1, Bar_Date1,Mark_Cnt_No);
					
			}
			else if(Mark_Type1[i] == 7)
			{
					sprintf(data,"%s%s%s%d",YY_end1,Bar_Month1, Bar_Date1,Line_Name);
					
			}
					
			j = strlen(data);
			
			if(Mark_OnOff[i] !=0)
				strcat(Bar_Data, data);
			

			
			
			sprintf(temp, "%c%c%c%02d%s%c", 0x01, 0x31, 0x02,i*2+1, data, 0x03); 
			
			Calc_Check_Sum(temp);
//			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(ctemp, "%s%c", temp, 0x0D); 
//			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%c", temp, 0x0D); 
			if(i==7)
				Mark_End_Flag = TRUE;
			
			
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Bar_Data);
	
	
}
void	SaveMarkData2(void)
{
	int 	h_file, i;
	char    lineBuff[200];
	
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\SYS");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

	h_file = OpenFile (".\\SYS\\SaveMarkData.txt",
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA, lineBuff);
		WriteLine(h_file,  lineBuff, -1);
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_2, lineBuff);
		WriteLine(h_file,  lineBuff, -1);
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_3, lineBuff);
		WriteLine(h_file,  lineBuff, -1);
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_5, lineBuff);
		WriteLine(h_file,  lineBuff, -1);
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_6, lineBuff);
		WriteLine(h_file,  lineBuff, -1);
	GetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_7, lineBuff);
		WriteLine(h_file,  lineBuff, -1);

	CloseFile( h_file );
}

void		ReadMarkData2(void)
{
//	int		NumofWorker;
	int 	ModelFileHandle, i;
	char	ModelFileBuff[1000], temp[500];//, Dummy[15];
	
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\SYS");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

	ModelFileHandle = OpenFile (".\\SYS\\SaveMarkData.txt",
								VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII);

//  Read 모델 수
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA, ModelFileBuff);
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_2, ModelFileBuff);
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_3, ModelFileBuff);

	
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_5, ModelFileBuff);
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_6, ModelFileBuff);
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	SetCtrlVal(mainpanel,MAINPANEL_BAR_DATA_7, ModelFileBuff);
	
	
	
	CloseFile (ModelFileHandle);
}
