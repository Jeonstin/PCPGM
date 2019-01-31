#include <userint.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <utility.h>
/********************************************************************************************/
/********************************************************************************************/
/* File:    InstallCommCallback.c                                                           */
/* Purpose: This example illustrates the use of the RS232 Library's InstallComCallback      */
/*          function to respond to the LWRS_RXFLAG event. The user will be asked to enter   */
/*          an event character. Whenever this event character is detected on the COM port,  */
/*          a callback function will be executed.                                           */
/* Notes:   To run this example you need to do a Loopback Test, i.e. connect pin 2 to       */
/*          pin 3 on the serial port.                                                       */
/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/* Include files                                                                            */
/********************************************************************************************/
#include <ansi_c.h>
#include <rs232.h>
#include "UserDefinedConst.h"
//#include "UserDefinedFlag.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"  
#include "PLC_IODefinedConst.h"
//#include "McControl.h"


/********************************************************************************************/
/* Globals                                                                                  */
/********************************************************************************************/
#define AUX1EVENTCHAR 0x0D
#define AUX2EVENTCHAR 0x0A  

int AUX1PortOpenErr,    // AUX1 포트 OPEN Err 		
    AUX1PortSendErr;	  // AUX1 포트 DATA 전송 Err
    AUX2PortAnswerErr;  
    
int AUX2PortOpenErr,
    AUX2PortSendErr,
    AUX2PortAnswerErr;

int AUX1CallbackRunFlg,   // AUX1 Callback 함수 실행중임을 나타내는 Flag
    AUX2CallbackRunFlg;  // AUX2 Callback 함수 실행중임을 나타내는 Flag

int AUX1MonFlg,           // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송 
    AUX2MonFlg;			  // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송       

char CheckSum[3];
char CheckSum1[4];
BYTE Sum = 0;

int	ReceiveEnd = 0;
int	S_d = 0, R_d = 0;
char	Check_Data[3];
char	Last_Data[512];
int		NGT_Cnt, Resend_Data = 0;
//int   MarkingType=0;	        	// 마킹할 타입
//int   MarkingType2=0;	        	// 마킹할 타입	  
//int   WeightType=0;	        		// 마킹할 타입	  

char  MarkingString[50]="NOTHING";  // 마킹할 데이터 저장
char  MarkingData[512]="NOTHING";   // 마킹할 일련번호 저장

char	MarkInBuffLabel[80]; // 마킹기의 응답문자 버퍼
int		MarkInBuffIdxLabel;  // 마킹기 버퍼의 기록할 위치 버퍼

char	R_Data[30];

int Mark_OnCtrl[8] = {	MARK_SET_MARK_ONOFF_1,MARK_SET_MARK_ONOFF_2,MARK_SET_MARK_ONOFF_3,MARK_SET_MARK_ONOFF_4,
						MARK_SET_MARK_ONOFF_5,MARK_SET_MARK_ONOFF_6,MARK_SET_MARK_ONOFF_7,MARK_SET_MARK_ONOFF_8};
int Mark_TypeCtrl[8] = {	MARK_SET_MARK_TYPE_1,MARK_SET_MARK_TYPE_2,MARK_SET_MARK_TYPE_3,MARK_SET_MARK_TYPE_4,
						MARK_SET_MARK_TYPE_5,MARK_SET_MARK_TYPE_6,MARK_SET_MARK_TYPE_7,MARK_SET_MARK_TYPE_8};
int Mark_TextCtrl[8] = {	MARK_SET_MARK_TEXT_1,MARK_SET_MARK_TEXT_2,MARK_SET_MARK_TEXT_3,MARK_SET_MARK_TEXT_4,
						MARK_SET_MARK_TEXT_5,MARK_SET_MARK_TEXT_6,MARK_SET_MARK_TEXT_7,MARK_SET_MARK_TEXT_8};
int Mark_XCtrl[8] = {	MARK_SET_MARK_X_1,MARK_SET_MARK_X_2,MARK_SET_MARK_X_3,MARK_SET_MARK_X_4,
						MARK_SET_MARK_X_5,MARK_SET_MARK_X_6,MARK_SET_MARK_X_7,MARK_SET_MARK_X_8};
int Mark_YCtrl[8] = {	MARK_SET_MARK_Y_1,MARK_SET_MARK_Y_2,MARK_SET_MARK_Y_3,MARK_SET_MARK_Y_4,
						MARK_SET_MARK_Y_5,MARK_SET_MARK_Y_6,MARK_SET_MARK_Y_7,MARK_SET_MARK_Y_8};
int Mark_ZCtrl[8] = {	MARK_SET_MARK_Z_1,MARK_SET_MARK_Z_2,MARK_SET_MARK_Z_3,MARK_SET_MARK_Z_4,
						MARK_SET_MARK_Z_5,MARK_SET_MARK_Z_6,MARK_SET_MARK_Z_7,MARK_SET_MARK_Z_8};
int Mark_RotCtrl[8] = {	MARK_SET_MARK_ROT_1,MARK_SET_MARK_ROT_2,MARK_SET_MARK_ROT_3,MARK_SET_MARK_ROT_4,
						MARK_SET_MARK_ROT_5,MARK_SET_MARK_ROT_6,MARK_SET_MARK_ROT_7,MARK_SET_MARK_ROT_8};



/********************************************************************************************/
/* Prototypes                                                                               */
/********************************************************************************************/
void CVICALLBACK AUX1_Callback_Func (int portNo,int eventMask,void *callbackData);
void CVICALLBACK AUX2_Callback_Func (int portNo,int eventMask,void *callbackData); 


//Marking Characters Queue 변수및 함수 선언
#define  QUEUECHARNUM     20
typedef struct _dnode
{
    char grade[QUEUECHARNUM];
    char string[QUEUECHARNUM];
    struct _dnode *prev;
    struct _dnode *next;
} dnode;

dnode *head, *tail;	   

void clear_queue(void);
int get(char* grade, char* str);
int put (char* grade, char* str);
void init_queue(void);
void end_queue(void);


/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int OpenAUX1 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX1PortOpenErr = OpenComConfig (MarkPortNo, ComPar[MarkPortNo].DeviceName,
						 	        ComPar[MarkPortNo].BaudRate, ComPar[MarkPortNo].Parity,
									ComPar[MarkPortNo].Data, ComPar[MarkPortNo].Stop,
									ComPar[MarkPortNo].InQ, ComPar[MarkPortNo].OutQ );
    if(AUX1PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (MarkPortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (MarkPortNo);
    FlushOutQ (MarkPortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (MarkPortNo, LWRS_RXFLAG, 0, AUX1EVENTCHAR , AUX1_Callback_Func, 0);
 //   InstallComCallback (MarkPortNo, LWRS_RECEIVE, 16, AUX1EVENTCHAR , AUX1_Callback_Func, 0);		   //

exit:
    return AUX1PortOpenErr;
}

int CloseAUX1(void)
{
/*  Close the open COM port before exiting */
    if( !AUX1PortOpenErr )
    {
 //   	do{
      	InstallComCallback (MarkPortNo, 0, 0, 0, 0, 0);
 //   	}while(AUX1CallbackRunFlg);  
    
    	CloseCom (MarkPortNo); 
    }
    return 0;
} 

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX1 (int type, char* data)
{                  
   char command[512];//, data1[100];
    int no,  count; 
	int i, x, cs=0;
	
    switch(type)
    {				  
     case 0:
			sprintf(command,"%s%c",data, 0x0D);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
//			MarkSend_No++;
          break;
      case 1:
		  
//	   		if(d_in[plc23])
//				sprintf(command,"CO,1,-1.4,5,-6.6%c",0x0D);  	
//	   		if(d_in[plc24])
				sprintf(command,"CO,0,3000%c",0x0D);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
//			MarkSend_No++;
          break;
      case 2:
//			sprintf(command,"%c%c%c%s%c%c",0x01,0x31,0x02,data,0x03,0x0D);  	
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No++;
          break;
      case 3:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No =0;
          break;
      default:
           return FALSE;
    }   

    
       AUX1PortSendErr=RESET;
       AUX1MonFlg = SET;  // 데이터 전송 flag Set : 전송함
 	
/*    
    strcpy(Last_Data, command);
    if( count< 0 )
    {
       AUX1PortSendErr=SET;
    }   
    else 
    {
       AUX1PortSendErr=RESET;
       AUX1MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }   
    
	S_d ++;
   */
	//	SetCtrlVal(mainpanel, MAINPANEL_S_D, S_d);
    return AUX1PortSendErr;

}
void Calc_Check(char* data)   // telesis marking 통신 BCC
{

	int no, i;
	
	//	int	radix = 16;
//	char buff[10];
	
	Sum = 0;
	
	no = strlen(data);
	
//	Sum =(BYTE)0x31;
	Sum =0x31;
	
	for(i=1;i<no;i++)
	{
		Sum +=(BYTE)data[i];
	}
//	itoa(cnt,buff, radix);
//	sprintf(CheckSum,"%02X",Sum);
	sprintf(CheckSum1,"%d",Sum);

	return;
}



void Calc_Check_Sum(char* data) // 막사 레이져 마킹기check sum
{

	int no, i;
	
	//	int	radix = 16;
//	char buff[10];
	
	Sum = 0;
	
	no = strlen(data);
	
//	Sum =(BYTE)data[1];
	
	for(i=1;i<no;i++)
	{
		Sum +=(BYTE)data[i];
	}
//	itoa(cnt,buff, radix);
	sprintf(CheckSum,"%02X",Sum);
//	sprintf(CheckSum1,"%d",Sum);

//	MessagePopup(CheckSum, CheckSum);
	
	return;
}


/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX1_Callback_Func (int portNo,int eventMask,void *callbackData)
{
  #define    ACK	 0x06
   #define    NAK	 0x15

	char buffer[256];
    int  Count,i;
	char *flagChar;
	char	temp[10], ctemp[100];
	char temp0[128], temp1[10]; 
	
//	double  data;
	
	AUX1CallbackRunFlg=1;
	
    Count=GetInQLen (MarkPortNo);
	
    ComRd(MarkPortNo, buffer, Count);
	
	
	AUX1MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  

	LogDataFunc(buffer, 1);

	
	sprintf(temp1,"%c%c",buffer[0],buffer[1]);
	sprintf(temp0,"C2");
	
//	flagChar=strcmp( temp1, temp0);
	if(!strcmp( temp1, temp0))
	{
		AUX1PortSendErr=FALSE; 
		AUX1CallbackRunFlg=0;  

//		LogDataFunc(temp0, 1);
		AUX1CallbackRunFlg=0;  

		

		sprintf(temp1,"%c",buffer[3]);

		if(!strcmp( temp1, "0"))
		{
			calc_out_data(pc120, 1); // 마킹기 전송 불량
		LogDataFunc("문자 전송 ok", 1);
		}
		else
		{
			calc_out_data(pc119, 1); // 마킹기 전송 불량
		LogDataFunc("문자 전송 ng", 1);
			
			
		}
		
//		calc_out_data(pc74, 1); // 마킹기 전송 불량
//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		return;
	}
	
	
	sprintf(temp1,"%c%c",buffer[0],buffer[1]);
	sprintf(temp0,"CO");
	
	if(!strcmp( temp1, temp0))
	{
		AUX1PortSendErr=FALSE; 
		AUX1CallbackRunFlg=0;  

//		LogDataFunc(temp0, 1);
		AUX1CallbackRunFlg=0;  

		

		sprintf(temp1,"%c",buffer[3]);

		if(!strcmp( temp1,"0"))
		{
			calc_out_data(pc121, 1); // 마킹기 전송 불량
			calc_out_data(pc122, 0); // 마킹기 전송 불량

			
			ctemp[0] = 0;
			for(i=7;i<Count-1;i++)
			{
				sprintf(temp,"%c",buffer[i]);
				if(strcmp(temp," ") )
					strcat(ctemp,temp);
			}	
		
			SetCtrlVal(mainpanel, MAINPANEL_SCAN_DATA, ctemp);
			SetCtrlVal(manualctrl, MANUALCTRL_SCAN_DATA, ctemp);
			if(!strcmp( ctemp, QR_A_Data))
			{
				calc_out_data(pc121, 1); // 마킹기 전송 불량
				calc_out_data(pc122, 0); // 마킹기 전송 불량
				LogDataFunc("문자 SCAN OK", 1);

			}
			else
			{
				calc_out_data(pc121, 0); // 마킹기 전송 불량
				calc_out_data(pc122, 1); // 마킹기 전송 불량
				LogDataFunc("문자 비교 불량", 1);
			}
				
				
			
		
		}
		else
		{
			calc_out_data(pc121, 0); // 마킹기 전송 불량
			calc_out_data(pc122, 1); // 마킹기 전송 불량
			LogDataFunc("문자 SCAN NG", 1);
			
			
		}
		
		
		return;
	}
	
	
}   


/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int OpenAUX2 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX2PortOpenErr = OpenComConfig (AUX2PortNo, ComPar[AUX2PortNo].DeviceName,
						 	        ComPar[AUX2PortNo].BaudRate, ComPar[AUX2PortNo].Parity,
									ComPar[AUX2PortNo].Data, ComPar[AUX2PortNo].Stop,
									ComPar[AUX2PortNo].InQ, ComPar[AUX2PortNo].OutQ );
    if(AUX2PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (AUX2PortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (AUX2PortNo);
    FlushOutQ (AUX2PortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (AUX2PortNo, LWRS_RXFLAG, 4, AUX2EVENTCHAR , AUX2_Callback_Func, 0);
//    InstallComCallback (AUX2PortNo, LWRS_RECEIVE, 2, AUX2EVENTCHAR , AUX2_Callback_Func, 0);

exit:
    return AUX2PortOpenErr;
}

int CloseAUX2(void)
{
/*  Close the open COM port before exiting */
    if( !AUX2PortOpenErr )
    {
    	do{
      	InstallComCallback (AUX2PortNo, 0, 0, 0, 0, 0);
    	}while(AUX2CallbackRunFlg);  
    
    	CloseCom (AUX2PortNo); 
    }	  
    
    return 0;
} 

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX2 (int type, char* data)
{ 

    char command[512];
    int  count; 

    switch(type)
    {				  
      case 1:
		  sprintf(command,"%s",data);//,0x03);  	  한번 측정
          break;
      case 2:
		  sprintf(command,"%c%cMZ%c%c", 0x30,0x30,0X0D,0X0A);//,0x03);  	  한번 측정
          break;
      case 3:
		  sprintf(command,"RLF%c%c", 0X0D,0X0A);//,0x03);  	 연속측정 end
          break;
      default:
           return FALSE;
    }   
    

    FlushInQ (AUX2PortNo);
    FlushOutQ (AUX2PortNo);
    
    count=ComWrt(AUX2PortNo, command, strlen(command));  
    
    if( count< 0 )
    {
       AUX2PortSendErr=SET;
    }   
    else 
    {
       AUX2PortSendErr=RESET;
       AUX2MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }   
  	ResetTimer(mainpanel, MAINPANEL_TESTTIME);
   
    return AUX2PortSendErr;

//	return 0;
	
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX2_Callback_Func (int portNo,int eventMask,void *callbackData)
{
	char buffer[256];
    int  i, Count;
	char	ctemp[500]=" ";
	char	temp[10];
//	char *stop;
//	unsigned char  ChkByte = 1;
//	double  data;
//	unsigned char temp1;
	
	AUX2CallbackRunFlg=1;
	
    Count=GetInQLen (AUX2PortNo);

    ComRd(AUX2PortNo, buffer, Count);

	if(Count <9)
	{
		
		LogDataFunc(buffer, 1);
	
	  FlushInQ (AUX2PortNo);
	  FlushOutQ (AUX2PortNo);
		AUX2CallbackRunFlg=0;
		
//		SendDataAUX2(1,"test");

		return;
		
		
		
	}



  
	
	AUX2MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  

	
		ctemp[0] = 0;
		for(i=0;i<Count-2;i++)
		{
			sprintf(temp,"%c",buffer[i]);
//			if(strcmp(temp," ") )
				strcat(ctemp,temp);
		}	

//		Torque_Value[0] = atof(ctemp)*1000;

//		ctemp[0] = 0;
/*		
		for(i=6;i<(Count-2);i++)
		{
			sprintf(temp,"%c",buffer[i]);
			strcat(ctemp,temp);
		}	
		Rpm_Velue = atoi(ctemp);

*/		
		
		if(Bar_Select==0)
			SetCtrlVal(mainpanel, MAINPANEL_B1,ctemp);
		else
			SetCtrlVal(mainpanel, MAINPANEL_B2,ctemp);
		
		
		//		strlen(R_Data);
//		ctemp[0] = 0;
		
	GetCtrlVal(mainpanel,MAINPANEL_A_WORK2, &i);
	if(i==0)
		SetCtrlVal(mainpanel,MAINPANEL_A_WORK2, 1);
	else
		SetCtrlVal(mainpanel,MAINPANEL_A_WORK2, 0);
		
		
		AUX2PortSendErr=FALSE; 
		AUX2CallbackRunFlg=0;  
	
  FlushInQ (AUX2PortNo);
    FlushOutQ (AUX2PortNo);

//			SendDataAUX2(1,"test");
		
  return;
  
}


void MarkInit_Label(void)
{
	int		i, quNum, itempanel;
	char	ctemp[20];
	
	if( !MarkPortNo || AUX1PortOpenErr )	return;
	
	FlushInQ(MarkPortNo);
	FlushOutQ(MarkPortNo);
	
	AllTimerStart(0);
	
	ActivePanel = itempanel = GetActivePanel();

	UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", SET, MODELESS);
	
	MarkInBuffIdxLabel = 0;
	
	sprintf(ctemp, "%c?P%c", 0x1b, 0x0d); // 마킹방향 물음.(통신에러 검사용 으로 그냥사용)
	
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	
	for( i = 0; i < 100; i++ ) // Max 1.0 sec 이내에 응답이 없으면 통신에러
	{
		SleepFunc(10); // 10 ms delay
		quNum = GetInQLen(MarkPortNo);
		
		if( quNum > 0 )
		{
           	ComRd( MarkPortNo, &MarkInBuffLabel[MarkInBuffIdxLabel], quNum );
           	MarkInBuffIdxLabel += quNum;
           	if( MarkInBuffLabel[MarkInBuffIdxLabel - 1] == ';' )
           		break;
		}
	}							 
	
	if( i >= 100 ) // MarkCommErr
	{
		AUX1PortSendErr = 1;
		InErrNum[6] = 1;
		AllTimerStart(1);
		UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", RESET, MODELESS);
		UserMessageBox(itempanel, 2000, VAL_WHITE, VAL_RED, "마킹기 초기화 실패..", SET, MODELESS);
		return;
	}
	AUX1PortSendErr = 0;
	InErrNum[6] = 0;
	
	sprintf(ctemp, "%c@%c", 0x1b, 0x0d); // 메모리 클리어(블럭 00로 클리어)
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cG1%c", 0x1b, 0x0d); // 직선 배열 마킹 선택
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cH%d%c", 0x1b, MarkFont[0], 0x0d); // 선택된 폰트정보 전송
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cO%d%c", 0x1b, MarkHeight[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));					   
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cM%d%c", 0x1b, MarkPitch[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cP%d%c", 0x1b, MarkDir[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cI%d%c", 0x1b, MarkPosX[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cJ%d%c", 0x1b, MarkPosY[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cU%s%c", 0x1b, CurrMarkStr0, 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	AllTimerStart(1);
	UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", RESET, MODELESS);
}
