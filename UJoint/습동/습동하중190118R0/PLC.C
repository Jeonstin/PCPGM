#include "main.h"

// include 화일 
#include <formatio.h>
#include <userint.h>
#include <rs232.h>
#include <utility.h>
#include <ansi_c.h> 
#include <string.h>

#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "plc.h"
#include "keycode.h"

char	PlcErrMsg[MAX_PLC_ERR][MAX_PLC_ERR_COL];
char	*InErrMsg[MAX_IN_ERR] = {
		"CAN NOT OPEN AMP PORT.",  // 0
		"AMP COM ERROR.",
		"CAN NOT READ AMP PARAMETER.",
		"CAN NOT OPEN PLC COMM PORT.",
		"PLC COMM ERROR.",
		"....", // 5
		"....",
		"....",
		"CONTINOUS NG.",
		" ",
		" ", // 10
		" ",
		" ",
		" ",
		" ",
		};

int					PlcErrNum[MAX_PLC_ERR], OldPlcErrNum[MAX_PLC_ERR], InErrNum[MAX_IN_ERR], OldInErrNum[MAX_IN_ERR]; // error 발생여부.
unsigned 	short	PlcOutWord[PLCWordWriteNo], OldPlcOutWord[PLCWordWriteNo];
unsigned	short	PlcInWord[PLCWordReadNo];
char				OutRes, check_iomon_Flag;
char				PlcTimerRunFlag;
int		Bar_Send_Flag=0,A_Bar_Send_Flag = 0;

char	d_in[PLC_IN_NO], def_in[PLC_IN_NO], d_out[PLC_OUT_NO], def_out[PLC_OUT_NO];

char	St1MeasIng;
int		PlcPcOff;
int		PlcCallBackIng, PlcFirstRunFlag;
double Torque_Data;
int		Model_LR=0;

char	St1ReadIng, St1CalcIng; // 저널부의 센서값 읽는중, 계산중,
// char	St2ReadIng, St2CalcIng; // 캠부의 센서값 읽는중, 계산중

void  check_iomon(void);

void  calc_out_data(int bit, int set)
{
	div_t 	x;
	unsigned short 	mask_bit;
	int 	port_no, bit_no;

	x = div(bit, 16);
	port_no = x.quot;
	bit_no = x.rem;

	mask_bit = 0x01;
	mask_bit <<= bit_no;

//unsigned 	short	PlcOutWord[PLCWordWriteNo];
//unsigned	short	PlcInWord[PLCWordReadNo];

	if(set)	PlcOutWord[port_no] |= mask_bit;
	else   	PlcOutWord[port_no] &= (~mask_bit);
}

void	PlcOutCommSend(void)
{
	int		i;
	char	temp[30];
	
	UnderPLCReadFlag = FALSE;
	UnderPLCWriteFlag = TRUE;
						
//////////////////////////  DDC-II
//	PLCPortOutBuff[0] = 'W';
//	PLCPortOutBuff[1] = OutByte[1]; // HighO
//	PLCPortOutBuff[2] = OutByte[0]; // LowO
//	PLCPortOutBuff[3] = (unsigned char)(PLCPortOutBuff[0] + PLCPortOutBuff[1] + PLCPortOutBuff[2]);
//	PLCPortOutBuff[4] = 0;
//	PLCSendBytesNo = 4;

//////////////////////////  MK-200S
	strcpy(	PLCPortOutBuff, PLCWriteReqCMDHeader );
	for( i = 0; i < PLCWordWriteNo; i ++ )
	{
		sprintf(temp, "%04X", PlcOutWord[i]);
		strcat( PLCPortOutBuff, temp );
	}
	
#if	PLC_SELECTION==MELSEC					//	MELSEC PLC가 선택되면 컴파일됨
	sprintf(temp, "%c%c", Comm_CR,Comm_LF);
#elif	PLC_SELECTION==MASTER_K200S			//	MASTER K200S가 선택되면 컴파일됨
	sprintf(temp, "%c", Comm_EOT);
#endif

	strcat( PLCPortOutBuff, temp );
			
	PLCPortSend();
}

void	PlcInCommSend(void)
{
	UnderPLCReadFlag = TRUE;
	UnderPLCWriteFlag = FALSE;

//////////////////////////  DDC-II
//	PLCPortOutBuff[0] = 'R';  // ddc-II board
//	PLCPortOutBuff[1] = 0;
//	PLCSendBytesNo = 1;

	strcpy(	PLCPortOutBuff, PLCReadReqCMD );
	PLCPortSend();
}					

void PlcGetInFromBuff(void)
{
	int	i, j, st, ed;
	unsigned short 	ChkWord;
	char	temp[30];

///////////////  PLCPortInBuff

	for(i = 0; i < PLCWordReadNo; i++)
	{
		strncpy(temp, &PLCPortInBuff[i * 4 + PLCReadCMDReturnDataPosition], 4);
		temp[4] = 0;
		sscanf(temp, "%x", (int *)&PlcInWord[i] );
		
		ChkWord = 1;
		for( j = 0; j < 16; j++ )
		{
			if( PlcInWord[i] & ChkWord )
				d_in[i * 16 + j] = 1;
			else
				d_in[i * 16 + j] = 0;
			ChkWord <<= 1;
		}
	}
	
	for(i = 0; i < PLCWordWriteNo; i++)
		OldPlcOutWord[i] = PlcInWord[i + PLCWordWriteStNo];
	
	st = PLCWordWriteStNo * 16;
	ed = PLCWordWriteStNo * 16+PLCWordWriteNo * 16;
	
	
	for( i = st; i < ed; i++ ) // plc에서 읽을때 출력까지 같이 읽어온다.
		d_out[i - st] = d_in[i];
	
	///  WORD DATA 추가(320BIT)	
	for( j = 0; j < 320; j++ )
	{
//		d_in[j+320] =d_in[j+320+160+160]; 
		d_in[j+320] =d_in[j+320+160]; 
		
		
	}
	
	
}


/*
void PlcGetInFromBuff(void)
{
	int	i, j, st, ed;
	unsigned short 	ChkWord;
	char	temp[30];

///////////////  PLCPortInBuff

	for(i = 0; i < PLCWordReadNo; i++)
	{
		strncpy(temp, &PLCPortInBuff[i * 4 + 10], 4);
		temp[4] = 0;
		sscanf(temp, "%x", (int *)&PlcInWord[i] );
		
		ChkWord = 1;
		for( j = 0; j < 16; j++ )
		{
			if( PlcInWord[i] & ChkWord )
				d_in[i * 16 + j] = 1;
			else
				d_in[i * 16 + j] = 0;
			ChkWord <<= 1;
		}
	}
	
	for(i = 0; i < PLCWordWriteNo; i++)
		OldPlcOutWord[i] = PlcInWord[i + PLCWordWriteStNo];
	
	st = PLCWordWriteStNo * 16;
	ed = PLCWordReadNo * 16;
	
	for( i = st; i < ed; i++ ) // plc에서 읽을때 출력까지 같이 읽어온다.
		d_out[i - st] = d_in[i];
}
*/

/********************************************************************************************/
/* EventCharDetectFunc ():  Fuction called when the event character is detected.         */
/********************************************************************************************/

int		PlcCommRetryNum; // plc error check
void CVICALLBACK PLC_IO_Function (int portNo,int eventMask,void *callbackData)
{
	int		i, j;

	PlcCallBackIng = 1;
//	if( !MainLoopFlag ) // check_iomon() 에서 처리 할 것이 남아 있다.
//		return;																						
	
	if( PlcTimerRunFlag ) // Plc Error Timer
	{
//		ComRdTerm (PlcPortNo, PLCPortInBuff, PLCIOByteMax, Comm_ETX);
		PlcCallBackIng = 0;
		return;
	}
	
	SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
	
//	if( ActivePanel == manualctrl ) // test, sg_cnt
//	{
//		sg_cnt1++;  // 테스트용, test
//		if( sg_cnt1 > 10000000 )	sg_cnt1 = 0;
//	}

	
	 // Comm_ETX를 이벤트 문자로 등록 했지만 혹시 엉뚱한 문자가 입력된다면...
	j = GetInQLen(PlcPortNo);
	if( j < 1 )
	{
		PlcCallBackIng = 0;
		return; // 에러발생의 소지
	}
	
	ComRd(PlcPortNo, PLCPortInBuff, j);
	
	if( UnderPLCReadFlag)		// Return Data From PLC (30 word) by Read Command
	{
#if	PLC_SELECTION==MELSEC					//	MELSEC PLC가 선택되면 컴파일됨
		if( (PLCPortInBuff[0] == Comm_STX) && ( j >=  PLCReadCMDReturnDataPosition + 4 * PLCWordReadNo) )	// PLC or RS-232C Error가 아니면 PLC Data Decode
#elif	PLC_SELECTION==MASTER_K200S			//	MASTER K200S가 선택되면 컴파일됨
		if( (PLCPortInBuff[0] == Comm_ACK) && ( j >=  PLCReadCMDReturnDataPosition + 4 * PLCWordReadNo) )	// PLC or RS-232C Error가 아니면 PLC Data Decode
#endif
		{
   			PlcGetInFromBuff();
   			
			check_iomon();
//			check_iomon_Flag = 1; // 쓰레드에서 check_iomon() 실행=>위에서 바로 실행해보지 뭐..^^;

			for( i = 0; i < PLCWordWriteNo; i++ )
			{
				if( PlcOutWord[i] != OldPlcOutWord[i] )
				{
					OutRes = SET;
					break;
				}
			}
   			
   			if( OutRes )						   
   			{
   				OutRes = 0;
   				PlcOutCommSend();
   			}
   			else
	   			PlcInCommSend();
   			
			PlcCommRetryNum = 0;
			PlcCommErr = FALSE;
			InErrNum[4] = 0;
		}
		else
		{
       		SleepFunc(100); // Delay(0.1);
   			PlcInCommSend();
   			
   			PlcCommRetryNum++;
   			if( PlcCommRetryNum > 6 )
   			{
//				PlcCommErr = TRUE;
//				InErrNum[4] = 1;
//				if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
//					SetActivePanel(errpanel);
   			}
   		}
   	}
   	else  // UnderPLCWriteFlag
   	{
//		ComRdTerm (PlcPortNo, PLCPortInBuff, PLCIOByteMax, Comm_ETX);
		if(PLCPortInBuff[0] != Comm_ACK)	// PLC or RS-232C Error가 아니면 PLC Data Decode
		{
       		SleepFunc(100); // Delay(0.1);
   			PlcOutCommSend();
   			
   			PlcCommRetryNum++;
   			if( PlcCommRetryNum > 4 )
   			{
//				PlcCommErr = TRUE;
//				InErrNum[4] = 1;
//				if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
//					SetActivePanel(errpanel);
   			}
   		}
   		else
   		{
   			PlcInCommSend();
   			
   			PlcCommRetryNum = 0;
			PlcCommErr = FALSE;
			InErrNum[4] = 0;
   		}
   	}
   	
//	SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_INTERVAL, 1.0);
   	ResetTimer(mainpanel, MAINPANEL_PLCTIMER);
	SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
	 
	PlcCallBackIng = 0;
	return;
}

int		PLCOpen(void)
{   
	int		ret;

	if(PlcPortNo == 0)
	{
//		MessagePopup ("PLC Port Error", "PLC. Port 번호가 선택되지 않았습니다.(Not Selected)");
//		PlcPortOpenErr = 1;
//		InErrNum[3] = 1;
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
		if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
			SetActivePanel(errpanel);
		return -1;  // not open
	}
	
    /*  Open and Configure Com port */
    ret = OpenComConfig (PlcPortNo, ComPar[PlcPortNo].DeviceName,
							ComPar[PlcPortNo].BaudRate, ComPar[PlcPortNo].Parity,
							ComPar[PlcPortNo].Data, ComPar[PlcPortNo].Stop,
							ComPar[PlcPortNo].InQ, ComPar[PlcPortNo].OutQ);
    if(ret) goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
	ret = SetCTSMode (PlcPortNo, ComPar[PlcPortNo].CTSMode);
	if(ret) goto exit;
	
	ret = SetXMode(PlcPortNo, ComPar[PlcPortNo].XMode);
	if(ret) goto exit;

	ret = FlushInQ(PlcPortNo);
	if(ret) goto exit;
	
	ret = FlushOutQ(PlcPortNo);
	
exit:
	if(ret)
	{
		MessagePopup ("Plc. Port Error", "PLC Port Not Opened.");
		PlcPortOpenErr = 1;
		InErrNum[3] = 1;
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
		if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
			SetActivePanel(errpanel);
	}
	else
	{
#if	PLC_SELECTION==MELSEC					//	MELSEC PLC가 선택되면 컴파일됨
///////////////////  a2sh plc comm  //////////////////////////////////////////////
		InstallComCallback (PlcPortNo, LWRS_RXFLAG, 0, Comm_LF, PLC_IO_Function, NULL);  // melsec a2sh
//////////////////////////////////////////////////////////////////////////////////////////
#elif	PLC_SELECTION==MASTER_K200S			//	MASTER K200S가 선택되면 컴파일됨
		InstallComCallback (PlcPortNo, LWRS_RXFLAG, 0, Comm_ETX, PLC_IO_Function, NULL); // mk-200s
#endif
		PlcInCommSend();
		ResetTimer(mainpanel, MAINPANEL_PLCTIMER);
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
		PlcPortOpenErr = 0;
		InErrNum[3] = 0;
	}
	
	return ret;  						   
}

void PLCClose(void)
{
//  	InstallComCallback (PlcPortNo, 0, 0, 0, 0, 0);
//  removePLCTimer(); 
//  CmtWaitForThreadPoolFunctionCompletion (DEFAULT_THREAD_POOL_HANDLE,
//										  PLCThreadID,
//  										  OPT_TP_PROCESS_EVENTS_WHILE_WAITING);
  	CloseCom (PlcPortNo);
//  CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, PLCThreadID);
}

void initPLC(void)
{
#if	PLC_SELECTION==MELSEC					//	MELSEC PLC가 선택되면 컴파일됨
///////////////////  a2sh plc comm  //////////////////////////////////////////////
//	sprintf(PLCReadReqCMD, "%c%s%s%s%x%s%2X%c%c", Comm_ENQ, StationNo, PLCNo,WordReadCMD,
//				PLCReturnDelay, PLCReadAddr, PLCWordReadNo, Comm_CR, Comm_LF); 
//	sprintf(PLCWriteReqCMDHeader, "%c%s%s%s%X%s%2X", Comm_ENQ, StationNo, PLCNo,
//				WordWriteCMD, PLCReturnDelay, PLCWriteAddr, PLCWordWriteNo);
	
////Q CPU
	sprintf(PLCReadReqCMD, "%cF90000FF00%s%s%4X%c%c", Comm_ENQ,WordReadCMD, PLCReadAddr, PLCWordReadNo,Comm_CR, Comm_LF);
//		%s%s%s%x%s%2X%c%c", Comm_ENQ, StationNo, PLCNo,WordReadCMD,
//				PLCReturnDelay, PLCReadAddr, PLCWordReadNo, Comm_CR, Comm_LF); 
	sprintf(PLCWriteReqCMDHeader, "%cF90000FF00%s%s%4X", Comm_ENQ, WordWriteCMD, PLCWriteAddr, PLCWordWriteNo);//
//				%s%s%s%X%s%2X", Comm_ENQ, StationNo, PLCNo,
//				WordWriteCMD, PLCReturnDelay, PLCWriteAddr, PLCWordWriteNo);
	
//////////////////////////////////////////////////////////////////////////////////////////
#elif	PLC_SELECTION==MASTER_K200S			//	MASTER K200S가 선택되면 컴파일됨
	sprintf(PLCReadReqCMD, "%c00RSB06%s%02X%c", Comm_ENQ, PLCReadAddr, PLCWordReadNo, Comm_EOT); // k-200s, 4byte=>2card
	sprintf(PLCWriteReqCMDHeader, "%c00WSB06%s%02X", Comm_ENQ, PLCWriteAddr, PLCWordWriteNo); // k-200s
#endif
	return;
}



void	PLCPortSend(void)
{
	ComWrt(PlcPortNo, PLCPortOutBuff, strlen(PLCPortOutBuff));
	return;
}

// 자동/수동모드에서 Control View Set ( OnOff=1 : Enable, OnOff=0 : Disable)
void	MainCtrlSet(char	OnOff)
{
	// 화면에 자동/수동 표시
	if( OnOff )										// 자동이면
	{
		SetCtrlAttribute(mainpanel, MAINPANEL_MANUALCTRL1, ATTR_DIMMED, TRUE);	// 수동측정 흐리게
//		SetCtrlAttribute(mainpanel, MAINPANEL_ZEROSETUP1, ATTR_DIMMED, TRUE);	// 영점조정 흐리게
		SetCtrlAttribute(mainpanel, MAINPANEL_MODELSETUP1, ATTR_DIMMED, TRUE);	// 제품설정 흐리게
//		SetCtrlAttribute(mainpanel, MAINPANEL_RESULTVIEW1, ATTR_DIMMED, TRUE);	// 결과보기 흐리게
//		SetCtrlAttribute(mainpanel, MAINPANEL_MENU_BT1, ATTR_DIMMED, TRUE);	// 결과보기 흐리게
//		SetCtrlAttribute(mainpanel, MAINPANEL_SYSSETUP0, ATTR_DIMMED, TRUE);	// 시스템 설정
//		SetCtrlAttribute(mainpanel, MAINPANEL_TEXT_CTRL, ATTR_DIMMED, TRUE);	// 박스 위치 지정
//		SetCtrlAttribute(mainpanel, MAINPANEL_CLOSE, ATTR_DIMMED, TRUE);		// 종료  흐리게, 프로그램 종료는 가능해야함.
	}
	else										// 수동이면
	{
		SetCtrlAttribute(mainpanel, MAINPANEL_MANUALCTRL1, ATTR_DIMMED, FALSE);	// 수동측정 선명하게
		SetCtrlAttribute(mainpanel, MAINPANEL_ZEROSETUP1, ATTR_DIMMED, FALSE);	// 영점조정 선명하게
		SetCtrlAttribute(mainpanel, MAINPANEL_MODELSETUP1, ATTR_DIMMED, FALSE);	// 제품설정 선명하게
		SetCtrlAttribute(mainpanel, MAINPANEL_RESULTVIEW1, ATTR_DIMMED, FALSE);	// 결과보기 선명하게
		SetCtrlAttribute(mainpanel, MAINPANEL_MENU_BT1, ATTR_DIMMED, FALSE);	// 결과보기 선명하게
//		SetCtrlAttribute(mainpanel, MAINPANEL_SYSSETUP0, ATTR_DIMMED, FALSE);	// 시스템 설정
//		SetCtrlAttribute(mainpanel, MAINPANEL_TEXT_CTRL, ATTR_DIMMED, FALSE);	// 박스 위치 지정
//		SetCtrlAttribute(mainpanel, MAINPANEL_CLOSE, ATTR_DIMMED, FALSE);		// 종료  선명하게
	}
	return;
}

int CVICALLBACK PlcTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		ret;
//	sg_cnt++;  // 테스트용, test
//	if( sg_cnt > 10000000 )	sg_cnt = 0;
	LogDataFunc("Plc Error Timer", 1);
	
	if( PlcPortOpenErr )
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
		return 0;
	}

	if( PlcCallBackIng ) 	
	{
		ResetTimer (panel, control);
		return 0;
	}
	
	switch (event)
		{
		case EVENT_TIMER_TICK:
			PlcTimerRunFlag = 1;
//			PlcCommErr = TRUE;
//			InErrNum[4] = 1;
//			if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
//				SetActivePanel(errpanel);
			
			ret = FlushInQ (PlcPortNo);  
			if( ret == -2 || ret == -3 )
			{
//				PlcPortOpenErr = 1;
//				InErrNum[3] = 1;
				SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
				return 0;
			}
			
			FlushOutQ (PlcPortNo);
			
			SleepFunc(100); // 0.1초 지연
			PlcInCommSend();
			ResetTimer (panel, control);
			PlcTimerRunFlag = 0;
			break;
		}
	return 0;
}

void	MeasValueCls(void)
{
	int	i;
	
	if( ActivePanel == manualctrl ) // 수동 측정
		SetManuCtrlTableMeasData((double	*)NULL); // data clear
	else if( ActivePanel == mainpanel ) // 메인 화면
	{
		for(i = 0; i < MeasPoints; i++ )
		{
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
			SetCtrlVal( mainpanel, PointCtrl[i], 0.0);
		}
	}
}
void	MeasValueCls2(void)
{
	int	i;
	
	if( ActivePanel == manualctrl ) // 수동 측정
		SetManuCtrlTableMeasData((double	*)NULL); // data clear
	else if( ActivePanel == mainpanel ) // 메인 화면
	{
		for(i = 0; i < MeasPoints; i++ )
		{
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
		}
	}
}

void	MeasStart(char flag, char Sig)
{
	
	
	if( flag ) // MeasStart
	{
		St1MeasIng = 1;
		if( ActivePanel == zerosetup ) // 영점조정
		{
			if( d_out[pc9] )
				calc_out_data(pc9, 0); // ST1 ZsetReq
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0); // 자동영점 신호
		}
//		else if( ActivePanel == mainpanel ) // 메인 화면
//		{
//			SetCtrlAttribute(mainpanel, MAINPANEL_SPCLEFT, ATTR_DIMMED, TRUE);
//		}
		else if( ActivePanel == manualctrl ) // 수동 측정
		{
			if( d_out[pc69] )
				calc_out_data(pc69, 0); // 수동 측정요구 ST1
		//	if( d_out[pc10] )
		//		calc_out_data(pc12, 0); // 수동 측정요구 ST1
		}

//		SetCtrlAttribute(mainpanel, MAINPANEL_DATETIME, ATTR_ENABLED, FALSE);
//		GetCtrlVal(syssetup, SYSSETUP_STARTDELAY, &StartDelay);
//		RepeatChIndex = 0;
//		GetCtrlVal(syssetup, SYSSETUP_TESTAVGNO, &TestAvgNo);

		calc_out_data(pc11, 1); // ST1 측정중
		GSt1Sig = Sig;
		
		AmpStart(1);
	}
	else
	{
//		AmpStart(0);

		if( St1MeasIng )
		{
			AmpRdEndFlag = 1;                      // 측정중에 측정취소를 했다면 측정결과를 계산하지 않는다.
		}
			
//		if( ActivePanel == zerosetup ) // 영점조정
//			calc_out_data(pc8, 0); // ST1 ZsetReq
//		else if( ActivePanel == manualctrl ) // 수동 측정
//			calc_out_data(pc6, 0); // 수동 측정요구 ST1
//		else if( ActivePanel == mainpanel ) // 메인 화면

//		if( ActivePanel == mainpanel ) // 메인 화면
//			SetCtrlAttribute(mainpanel, MAINPANEL_SPCLEFT, ATTR_DIMMED, FALSE);
	}
}

void  MeasEscFunc(void)
{
	int		i;
	
//	if( AmpRunFlag || St1MeasIng )
//		AmpStart(0); // amp read cancel.

	ManualCtrlSt1Dimmed(0);
			if(language==0)
			{
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "LEFT측정시작");
			}
			else if(language==1)
			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "MEAS. START");
			else
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "測定始作");
	ZeroSetCtrlSt1Dimmed(0);
	
	St1EndPtFlag = 0;
	St1MeasIng = 0;
	St1ReadIng = St1CalcIng = 0; // 저널부의 센서값 읽는중, 계산중,
			Gono_Gng = 0;	
	
	if( ActivePanel == manualctrl )
		AmpStart(1); // 센서값이 보이도록 다시 시작
	
	calc_out_data(pc8, 0); // ST1 ZsetReq
	calc_out_data(pc9, 0); // ST1 ZsetReq
	calc_out_data(pc10, 0); //ST2 ZsetReq 
	calc_out_data(pc69, 0); // 
	calc_out_data(pc12, 0); // 

	calc_out_data(pc11, 0); // ST1 측정중
	calc_out_data(pc14, 0); // 자동영점 신호
	calc_out_data(pc15, 0);
//	calc_out_data(pc16, 0);
	
	calc_out_data(pc73, 0); // 반복측정 MODE
	calc_out_data(pc74, 0); // 반복측정 MODE
	calc_out_data(pc75, 0); // 반복측정 MODE
//	calc_out_data(pc76, 0); // 반복측정 MODE

	InErrNum[8] = 0; // 연속 불량
	calc_out_data(pc19, 0);
	calc_out_data(pc17, 0); // 측정결과 O.K
	calc_out_data(pc18, 1); // 측정결과 N.G
	
	calc_out_data(pc73, 0); // 마킹기 전송중
//	calc_out_data(pc74, 0); // 마킹기 전송 불량
	Mark_End_Flag = 0;

  		calc_out_data(pc80, 0); //
  		calc_out_data(pc81, 1); //
 	
		NGFlag_Retest = FALSE ; //재측정 안
			SendMarkingLabel = 0;
	
	RepeatChIndex = 0;
	
	for( i = 0; i < MAX_MANU_SW; i++)
	{
		if( d_out[MENU_SW_ST + i] )
		{
			calc_out_data(MENU_SW_ST + i, 0);
			SetCtrlVal(manualctrl, MenuSwCtrl[i], 0);
		}
	}

}

/*
int MenuSwLampCtrl[MAX_MANU_SW] = {	MANUALCTRL_SOL1_L,  MANUALCTRL_SOL2_L,  MANUALCTRL_SOL3_L,  MANUALCTRL_SOL4_L, MANUALCTRL_SOL5_L,
								MANUALCTRL_SOL6_L,  MANUALCTRL_SOL7_L,  MANUALCTRL_SOL8_L,  MANUALCTRL_SOL9_L,  MANUALCTRL_SOL10_L,
								MANUALCTRL_SOL11_L, MANUALCTRL_SOL12_L, MANUALCTRL_SOL13_L,  MANUALCTRL_SOL14_L,
							};
*/
void	DispCylStatus(void)
{
	int		i;

 // GetPanelHandleFromTabPage(manualctrl, MANUALCTRL_TAB, PAGE_TWO, &manualpanel);

			
	for( i = 0; i < MAX_MANU_SW; i++ )
	{
		if( (d_in[i * 2 + plc40] != def_in[i * 2 + plc40]) || ( d_in[i * 2 + 1 + plc40] != def_in[i * 2 + 1 + plc40]) ) // home, act중 하나라도 변화가 있으면
		{
			if( d_in[i * 2 + plc40] == d_in[i * 2 + 1 + plc40] ) // error
			{
				SetCtrlAttribute(manualctrl, MenuSwLampCtrl[i], ATTR_DIMMED, TRUE);
			}
			else
			{
				SetCtrlAttribute(manualctrl, MenuSwLampCtrl[i], ATTR_DIMMED, FALSE);
				if( d_in[i * 2 + plc40] ) // act
				{
					SetCtrlVal(manualctrl, MenuSwLampCtrl[i], 1);
				}
				else
				{
					SetCtrlVal(manualctrl, MenuSwLampCtrl[i], 0);
				}
			}
		}
	}
}

void  TimeDataSend(void)
{
	int		i;
	unsigned	long bPos;
	unsigned	long data;
	int		WashTime, DryTime;
	



//마킹 회전 수		
		data = Mark_Rot_No;
		bPos = 1;
		for( i = 0; i < 4; i++ )
		{
			if( data & bPos )
				calc_out_data(pc126 + i, SET);
			else
				calc_out_data(pc126 + i, RESET);
			bPos <<= 1;
		}
		
//auto mastering count		
			data = MasterRepeatChkNum;
		bPos = 1;
		for( i = 0; i < 4; i++ )
		{
			if( data & bPos )
				calc_out_data(pc130 + i, SET);
			else
				calc_out_data(pc130 + i, RESET);
			bPos <<= 1;
		}
		
//// servo data send
		
		
}

void  ServoDataSend_Total(void)
{
	int		i, j;
	unsigned	long bPos;
	unsigned	long data;
	int		data_10, data_1;
	

	for(j=0;j<7;j++)
	{
		data = Servo_Position[j];
		
		
		bPos = 1;
		for( i = 0; i < 32; i++ )
		{
			if( data & bPos )
				calc_out_data(pc160+j*32 + i, SET);
			else
				calc_out_data(pc160+j*32 + i, RESET);
			bPos <<= 1;
		}
	
		
	}

	
	
	
}


void	AlarmDataFunc(char *str, char flag)
{
	char	cTemp[256];
	int		linenum;
	

	sprintf(cTemp, "[%s] : %s", CurrTime, str); //
	InsertListItem (mainpanel,MAINPANEL_ALARM_LIST, -1, cTemp, 0);
	
	
		GetNumListItems (mainpanel,MAINPANEL_ALARM_LIST, &linenum);
	    if(linenum > 100)
			DeleteListItem ( mainpanel,MAINPANEL_ALARM_LIST, 0, 1);
	
		
		GetNumListItems (mainpanel,MAINPANEL_ALARM_LIST, &linenum);
		SetCtrlIndex (mainpanel,MAINPANEL_ALARM_LIST, linenum-1);

}



void  check_iomon(void)
{
	int		i, j;
	char	ctemp[256], temp[100];
	char	mark_data[100];
	char	Mark_Bar_Data[200];
	
//	int		Sol5_value;
//	int		Sol6_value;
	
//	sg_cnt++;  // 테스트용, test
//	if( sg_cnt > 10000000 )	sg_cnt = 0;
	
//	OperateIo();
//			GaugeStatusDisplay();

//	TimeDataSend();
//	ServoDataSend_Total();
	
	GetPanelHandleFromTabPage(mainpanel, MAINPANEL_TAB, PAGE_ONE, &tabpanel);

  	
	if(d_in[plc0]) SetCtrlVal(mainpanel, MAINPANEL_LED,TRUE);
	else SetCtrlVal(mainpanel, MAINPANEL_LED,FALSE);

	if(d_in[plc0]) SetCtrlVal(manualctrl, MANUALCTRL_LED,TRUE);
	else SetCtrlVal(manualctrl, MANUALCTRL_LED,FALSE);
	

	if( !d_out[pc0] && MainLoopFlag )
		calc_out_data(pc0, 1); // pc 정상
	
	if( d_out[pc0] && !MainLoopFlag )
		calc_out_data(pc0, 0); // pc 정상 이상

	if( (ActivePanel == mainpanel) && (!d_out[pc1] || d_out[pc2] || d_out[pc3]))// && !OldAmpErr )
	{
		calc_out_data(pc1, 1); // 주화면
		calc_out_data(pc2, 0); // 수동 측정화면
		calc_out_data(pc3, 0); // 영점 조정화면
	}
//	else if( (ActivePanel == manualctrl) && (d_out[pc1] || !d_out[pc2] || d_out[pc3]) && !OldAmpErr )
	else if( (ActivePanel == manualctrl) && (d_out[pc1] || !d_out[pc2] || d_out[pc3]) ) // 수동 조작은 해야 하므로 살려줌.
	{
		calc_out_data(pc1, 0); // 주화면
		calc_out_data(pc2, 1); // 수동 측정화면
		calc_out_data(pc3, 0); // 영점 조정화면
	}
	else if( (ActivePanel == zerosetup) && (d_out[pc1] || d_out[pc2] || !d_out[pc3]))// && !OldAmpErr )
	{
		calc_out_data(pc1, 0); // 주화면
		calc_out_data(pc2, 0); // 수동 측정화면
		calc_out_data(pc3, 1); // 영점 조정화면
	}
//	else if( ActivePanel == NULL && !OldAmpErr )
//	{
//		calc_out_data(pc1, 1); // 주화면
//		calc_out_data(pc2, 0); // 수동 측정화면
//		calc_out_data(pc3, 0); // 영점 조정화면
//	}
	
//	if( (d_out[pc1] || d_out[pc2] || d_out[pc3]) && OldAmpErr ) // amp 통신에러
/*
	if( (d_out[pc1] || d_out[pc3]) && OldAmpErr ) // amp 통신에러
	{
		calc_out_data(pc1, 0); // 주화면
//		calc_out_data(pc2, 0); // 수동 측정화면
		calc_out_data(pc3, 0); // 영점 조정화면
	}
*/	
	if( (d_in[plc6] != def_in[plc6]) ) // 측정 취소
	{
		if( d_in[plc6] )
		{
			LogDataFunc("MEAS ESC ON", 1);
			Bar_Send_Flag=A_Bar_Send_Flag =0;
			MarkEndFlag = 1;

			MeasEscFunc();
		 	IdelStateTCP = 0; 
			calc_out_data(pc15, 0); // 반복측정 MODE
//			calc_out_data(pc16, 0); // 반복측정 MODE
			calc_out_data(pc54, 0); // 마킹 전송 완료 clear
			
			
		calc_out_data(pc116, 0); // 마킹기 lan alarm
			
		 	calc_out_data(pc119 , 0);
		 	calc_out_data(pc120 , 0);
			
			calc_out_data(pc121, 0); // SCAN OK
			calc_out_data(pc122, 0); // SCAN NG
			

	calc_out_data(pc73, 0); // 반복측정 MODE
	calc_out_data(pc74, 0); // 반복측정 MODE
	calc_out_data(pc75, 0); // 반복측정 MODE
//	calc_out_data(pc76, 0); // 반복측정 MODE

	//		calc_out_data(pc13, 0); // 마킹 전송 완료 clear
			calc_out_data(pc72, 0); // 마킹 전송 완료 clear
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
		 	ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 
		 	
		}
		else
			LogDataFunc("MEAS ESC OFF", 0);
	
	}
	


	if( d_in[plc1] && (d_in[plc1] != def_in[plc1]) ) // 자동측정 화면 전환
		SetActivePanel(mainpanel);
	if( d_in[plc2] && (d_in[plc2] != def_in[plc2]) ) // 수동측정 화면 전환
		SetActivePanel(manualctrl);
	if( d_in[plc3] && (d_in[plc3] != def_in[plc3]) ) // 영점측정 화면 전환
		SetActivePanel(zerosetup);
			

/*	
	 if(Meas_Method)
	 {
		 calc_out_data(pc40, 0);
		 calc_out_data(pc41, 1);
	 }
	 else
	 {
		 calc_out_data(pc40, 1);
		 calc_out_data(pc41, 0);
	 }
*/		 
	
	if(  (d_in[plc4] != def_in[plc4])  ) // 자동 기동중
	{
		if( d_in[plc4] )
		{
			LogDataFunc("AUTO RUNNING ON", 1);
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_1,TRUE);
			
				SetMenuBarAttribute (menu_item, MENUBAR_MAINMENU, ATTR_DIMMED, 1);	
				SetMenuBarAttribute (menu_item, MENUBAR_SYSMENU, ATTR_DIMMED, 1);	
				SetMenuBarAttribute (menu_item, MENUBAR_INTERFACE, ATTR_DIMMED, 1);	
			

		}
		
		if( PointMoveSet ) // 측정 박스 이동중
			MainPanelEvent (mainpanel, EVENT_KEYPRESS, (void *)0, _CF8, 0); // ^F8 을 보냄.
	
		
		MainCtrlSet( d_in[plc4] );
		if( !d_in[plc4] )	
		{
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_1,FALSE);
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			LogDataFunc("AUTO RUNNING OFF", 1);
			InErrNum[8] = 0; // 연속 불량

				SetMenuBarAttribute (menu_item, MENUBAR_MAINMENU, ATTR_DIMMED, 0);	
				SetMenuBarAttribute (menu_item, MENUBAR_SYSMENU, ATTR_DIMMED, 0);	
				SetMenuBarAttribute (menu_item, MENUBAR_INTERFACE, ATTR_DIMMED, 0);	
			
			calc_out_data(pc19, 0);
		}
	}

	if( (d_in[plc5] != def_in[plc5]) ) // Cycle start
	{
		if( d_in[plc5] )
		{
		 	IdelStateTCP = 1; 
			LogDataFunc("Cycle start ON", 1);
			calc_out_data(pc17, 0); // 측정결과 O.K
			calc_out_data(pc18, 0); // 측정결과 N.G
  		calc_out_data(pc51, 0); // 네트웍 data 읽기 완료 reset
  		calc_out_data(pc80, 0); //
  		calc_out_data(pc81, 0); //
		
			calc_out_data(pc22, 0); // NG
			calc_out_data(pc85, 0); // NG
		
 		
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
	
			MeasValueCls();
			RepeatChIndex = 0;
		}
		else
		{
			LogDataFunc("Cycle start OFF", 0);
		 	//IdelStateTCP = 0; 
			
		}
			
	}

	if( (d_in[plc7] != def_in[plc7]) ) 
	{
		if( d_in[plc7] )
		{
			LogDataFunc("RESET ON", 1);

			InErrNum[8] = 0; // 연속 불량
			CurrContNG = 0;							
   //			calc_out_data(pc74, 0); // 마킹기 전송 불량
			
				calc_out_data(pc14, 0); // 청소시간이 ON되면 RESET누르면 끝난다.

			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			calc_out_data(pc19, 0);
           P_Chk = 0;
            N_Chk = 0; // 상한, 하한 관리 over count
			
		}
//		else
//			LogDataFunc("RESET 신호", 0);
	}

	if( (d_in[plc8] != def_in[plc8]) ) 
	{
		if( d_in[plc8] )
		{
			calc_out_data(pc8, 0);
			calc_out_data(pc9, 0);
			calc_out_data(pc69, 0);
			calc_out_data(pc71, 0);
			
  			
   
		}
		else
		{
		}
	}


	if( d_in[plc10] != def_in[plc10] ) // 측정요구 sig1
	{
		if( d_in[plc10] )
		{
		 	IdelStateTCP = 1; 
			LogDataFunc("REQUEST MEAS. ON", 1);
			RepeatChIndex = 0;
				calc_out_data(pc17, 0); // 측정결과 O.K
				calc_out_data(pc18, 0); // 측정결과 N.G
				calc_out_data(pc12, 0); // 
			MeasValueCls();

			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다
			
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			
			EncMeasEnd = 0;	
			if( ActivePanel == manualctrl )
			{
				ManualCtrlSt1Dimmed(1); // Dimmed 설정
	//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "측 정 중");
				if( ManualCycleMode_1 ) // 반복측정 MODE
					calc_out_data(pc73, 1); // 반복측정 MODE
			}
			 MeasCnt=0;
			SetCtrlVal(manualctrl, MANUALCTRL_LED_3,TRUE);
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_2,TRUE);
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
		}
		else
		{
		
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_2,FALSE);
				SetCtrlVal(manualctrl, MANUALCTRL_LED_3,FALSE);
			
			LogDataFunc("REQUEST MEAS. OFF", 1);
			MeasStart(0, 1); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
		}
	}
	if( d_in[plc11] != def_in[plc11] ) // 측정요구 sig2
	{
		if( d_in[plc11] )
		{
		 	IdelStateTCP = 1; 
			LogDataFunc("측정요구 ON 2", 0);
			RepeatChIndex = 0;
  	//			calc_out_data(pc12, 0); // 재측정
				calc_out_data(pc17, 0); // 측정결과 O.K
				calc_out_data(pc18, 0); // 측정결과 N.G
				calc_out_data(pc12, 0); // 
    			calc_out_data(pc22, 0); // NG

			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다

			EncMeasEnd = 0;	
			if( ActivePanel == manualctrl )
			{
				ManualCtrlSt1Dimmed(1); // Dimmed 설정
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_2, ATTR_LABEL_TEXT, "측 정 중");
				if( ManualCycleMode_1 ) // 반복측정 MODE
					calc_out_data(pc73, 1); // 반복측정 MODE
			}
			
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 2); // Start: ON,  Sig: 1
		}
		else
		{
			LogDataFunc("측정요구 2OFF", 0);
			MeasStart(0, 2); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
		}
	}
	if( d_in[plc12] != def_in[plc12] ) // 측정요구 sig3
	{
		if( d_in[plc12] )
		{
		 	IdelStateTCP = 1; 
			LogDataFunc("측정요구3 ON", 0);
			RepeatChIndex = 0;
 				calc_out_data(pc80, 0); // 측정결과 O.K
				calc_out_data(pc81, 0); // 측정결과 N.G
			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다

			if( ActivePanel == manualctrl )
			{
				ManualCtrlSt1Dimmed(1); // Dimmed 설정
	//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "측 정 중");
				if( ManualCycleMode_1 ) // 반복측정 MODE
					calc_out_data(pc74, 1); // 반복측정 MODE
			}
			
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 3); // Start: ON,  Sig: 1
		}
		else
		{
			LogDataFunc("측정요구3 OFF", 0);
			MeasStart(0, 3); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
		}
	}

	if( d_in[plc13] != def_in[plc13] ) // 영점측정 요구
	{
		if( d_in[plc13] )
		{
	 		IdelStateTCP = 1; 		
			LogDataFunc("REQUEST ZEROSET ON", 1);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
					  			EncMeasEnd = 0;	
			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다
			
	//		if(AutoZeroHourUseFlag || AutoZeroCntUseFlag)
	//			calc_out_data(pc16, 1);
			if( ActivePanel == manualctrl )
			{
				ManualCtrlSt1Dimmed(1); // Dimmed 설정
	//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "측 정 중");
				if( ManualCycleMode_1 ) // 반복측정 MODE
					calc_out_data(pc74, 1); // 반복측정 MODE
			}
			
				
			if( d_out[pc14] )
				calc_out_data(pc14, 0);

				
			calc_out_data(pc8, 0);
			calc_out_data(pc9, 0);
//			if( d_out[pc72] )
//			calc_out_data(pc72, 0);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
		}
		else
		{
			LogDataFunc("REQUEST ZEROSET OFF", 1);
			MeasStart(0, 1); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
		}
	}

	if( d_in[plc14] != def_in[plc14] ) // 영점측정 요구
	{
		if( d_in[plc14] )
		{
	 		IdelStateTCP = 1; 		
			LogDataFunc("REQUEST ZEROSET2 ON", 1);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			calc_out_data(pc9, 0); // ST2 ZsetReq
				calc_out_data(pc10, 0); // ST2 ZsetReq
	
					  			EncMeasEnd = 0;	
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다
			
//			if(AutoZeroHourUseFlag || AutoZeroCntUseFlag)
//				calc_out_data(pc16, 1);
				
			if( d_out[pc14] )
				calc_out_data(pc14, 0);

	//		if( d_out[pc13] )
	//		calc_out_data(pc13, 0);
//			if( d_out[pc72] )
//			calc_out_data(pc72, 0);
  					SetCtrlVal(zerosetup, ZEROSETUP_LED_3,TRUE);

			St1ReadIng = 1;
			MeasStart(1, 4); // Start: ON,  Sig: 1
		}
		else
		{
			LogDataFunc("REQUEST ZEROSET OFF", 1);
			MeasStart(0, 4); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
			SetCtrlVal(zerosetup, ZEROSETUP_LED_3,FALSE);
		}
	}
	
 	if( d_in[plc15] != def_in[plc15] ) // 측정요구 sig4
	{
		if( d_in[plc15] )
		{
		 	IdelStateTCP = 1; 
			LogDataFunc("측정요구4 ON", 0);
			RepeatChIndex = 0;
 				calc_out_data(pc80, 0); // 측정결과 O.K
				calc_out_data(pc81, 0); // 측정결과 N.G
			calc_out_data(pc15, 0); // 한바뀌 읽었다
//			calc_out_data(pc16, 0); // 한바뀌 읽었다
 			calc_out_data(pc85, 0); // NG

			if( ActivePanel == manualctrl )
			{
				ManualCtrlSt1Dimmed(1); // Dimmed 설정
	//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "측 정 중");
//				if( ManualCycleMode_1 ) // 반복측정 MODE
//					calc_out_data(pc76, 1); // 반복측정 MODE
			}
			
			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 4); // Start: ON,  Sig: 1
		}
		else
		{
			LogDataFunc("측정요구4 OFF", 0);
			MeasStart(0, 4); // Start: OFF,  Sig: 1
			St1ReadIng = 0;
		}
	}
	
	if( (d_in[plc16] != def_in[plc16]) ) 
	{
		if( d_in[plc16] )
		{
//				McIDTestFlag = TRUE;	
				McID = 1;
				SetCtrlVal( mainpanel, MAINPANEL_RINGCH, "2 선반");
				SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_ZPLANE_POSITION,0 );
		  		SetCtrlIndex ( mainpanel, MAINPANEL_MCID_VIEW, McID);			
			}
		else
			LogDataFunc("제 2 기", 0);
	}
	if( (d_in[plc17] != def_in[plc17]) ) 
	{
		if( d_in[plc17] )
		{
//				McIDTestFlag = TRUE;	
				McID = 2;
				SetCtrlVal( mainpanel, MAINPANEL_RINGCH, "3 선반");
			}
		else
			LogDataFunc("제 B 기", 0);
	}

  	if( (d_in[plc18] != def_in[plc18]) ) 
	{
		if( d_in[plc18] )
		{
				SetCtrlVal(mainpanel, MAINPANEL_LED_IN_1,TRUE);
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_1,TRUE);
		}
		else
		{
			SetCtrlVal(mainpanel, MAINPANEL_LED_IN_1,FALSE);
			SetCtrlVal(tabpanel, TABPANEL_LED_IN_1,FALSE);
			
		}
	}
	if( (d_in[plc19] != def_in[plc19]) ) 
	{
		if( d_in[plc19] )
		{
				SetCtrlVal(mainpanel, MAINPANEL_LED_IN_2,TRUE);
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_2,TRUE);
		}
		else
		{
			SetCtrlVal(mainpanel, MAINPANEL_LED_IN_2,FALSE);
			SetCtrlVal(tabpanel, TABPANEL_LED_IN_2,FALSE);
			
		}
	}
	if( (d_in[plc20] != def_in[plc20]) ) 
	{
		if( d_in[plc20] )
		{
				SetCtrlVal(mainpanel, MAINPANEL_LED_OUT_1,TRUE);
				SetCtrlVal(tabpanel, TABPANEL_LED_OUT_1,TRUE);
		}
		else
		{
			SetCtrlVal(mainpanel, MAINPANEL_LED_OUT_1,FALSE);
			SetCtrlVal(tabpanel, TABPANEL_LED_OUT_1,FALSE);
			
		}
	}
	if( (d_in[plc21] != def_in[plc21]) ) 
	{
		if( d_in[plc21] )
		{
				SetCtrlVal(mainpanel, MAINPANEL_LED_OUT_2,TRUE);
				SetCtrlVal(tabpanel, TABPANEL_LED_OUT_2,TRUE);
		}
		else
		{
			SetCtrlVal(mainpanel, MAINPANEL_LED_OUT_2,FALSE);
			SetCtrlVal(tabpanel, TABPANEL_LED_OUT_2,FALSE);
			
		}
	}
	if( (d_in[plc22] != def_in[plc22]) )  // 서보 1 data 보내라
	{
		if( d_in[plc22] )
		{
			
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_3,TRUE);
		}
		else
		{
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_3,FALSE);
		
		}
	}
	if( (d_in[plc23] != def_in[plc23]) ) 
	{
		if( d_in[plc23] )
		{
			
				SetCtrlVal(tabpanel, TABPANEL_LED_OUT_3,TRUE);
		}
		else
		{
				SetCtrlVal(tabpanel, TABPANEL_LED_OUT_3,FALSE);
		
		}
	}
	if( (d_in[plc24] != def_in[plc24]) ) 
	{
		if( d_in[plc24] )
		{
			
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_4,TRUE);
		}
		else
		{
				SetCtrlVal(tabpanel, TABPANEL_LED_IN_4,FALSE);
		
		}
	}
	if( (d_in[plc25] != def_in[plc25]) ) 
	{
		if( d_in[plc25] )
		{
			
				SetCtrlVal(tabpanel, TABPANEL_LED_DATA_11,TRUE);
		}
		else
		{
				SetCtrlVal(tabpanel, TABPANEL_LED_DATA_11,FALSE);
		
		}
	}
	if( (d_in[plc26] != def_in[plc26]) ) 		//마킹 문자 전송
	{
		if( d_in[plc26] )
		{
			Auto_1cycleFlag = 1;
			
//				A_MarkingDataLabel();	
//				A_Bar_Send_Flag=1;
//			 	calc_out_data(pc120 , 0);
				
//				SetCtrlVal(mainpanel, MAINPANEL_LED_DATA_5,TRUE);
//				SetCtrlVal(tabpanel, TABPANEL_LED_DATA_5,TRUE);
		}
		else
		{
			Auto_1cycleFlag = 0;
//			calc_out_data(pc73, 0); //마킹 문자 전송중

			//			SetCtrlVal(mainpanel, MAINPANEL_LED_DATA_5,FALSE);
//			SetCtrlVal(tabpanel, TABPANEL_LED_DATA_5,FALSE);
		
		}
	}
	if( (d_in[plc27] != def_in[plc27]) ) 
	{
		if( d_in[plc27] )
		{
		   A_Model_Change(1);

 //  			SendMarkingLabel = 1; //MarkStartFunc();
		}
		else
		{
			
		}
	}
	if( (d_in[plc28] != def_in[plc28]) ) 
	{
		if( d_in[plc28] )
		{
		   A_Model_Change(2);
		}
		else
		{
		
		}
	}
	if( (d_in[plc29] != def_in[plc29]) ) 
	{
		if( d_in[plc29] )
		{
		   A_Model_Change(3);
		   
		
		}
		else
		{

			
		}
	}
	if( (d_in[plc30] != def_in[plc30]) ) 	   //text1 send 
	{
		if( d_in[plc30] )
		{
		   A_Model_Change(4);
			
//			   TestData2TCP(0,0, mark_data);
			   

		}
		else
		{

			
		}
	}
	if( (d_in[plc31] != def_in[plc31]) ) 	  //text2 send 
	{
		if( d_in[plc31] )
		{
		   A_Model_Change(5);
			
//			   TestData2TCP(0,0, mark_data);
		}
		else
		{
	
		}
	}
	if( (d_in[plc32] != def_in[plc32]) ) 	   //text3 send
	{
		if( d_in[plc32] )
		{
		   A_Model_Change(6);
			
//			   TestData2TCP(0,0, mark_data);
		}
		else
		{
			
		}
	}
	if( (d_in[plc33] != def_in[plc33]) ) 	  //QR SEND
	{
		if( d_in[plc33] )
		{
			
		   A_Model_Change(7);
			   
			   
			   
		}
		else
		{
			
		}
	}
	if( (d_in[plc34] != def_in[plc34]) ) 
	{
		if( d_in[plc34] )
		{
		   A_Model_Change(8);
		}
		else
		{
//			SetManuCtrlTableData();

//			MasterFlag = 0;
			
		}
	}
	if( (d_in[plc35] != def_in[plc35]) ) 
	{
		if( d_in[plc35] )
		{
		   A_Model_Change(9);
		}
		else
		{
			
		}
	}
	
	if( (d_in[plc36] != def_in[plc36]) )  //6 +OK
	{
		if( d_in[plc36] )
		{
		   A_Model_Change(10);
			
//			SendDataAUX1(1, "TEST");
		}
		else
		{
		
		}
	}
	if( (d_in[plc37] != def_in[plc37]) ) //6 -OK
	{
		if( d_in[plc37] )
		{
			for(i=0;i<20;i++)
				Meas_Data[i] = 0.0;

			ReadMeasData();
			
		}
		else
		{
		
		}
	}
	
 	if( (d_in[plc38] != def_in[plc38]) ) 
	{
		if( d_in[plc38] )
		{

			for(i = 0; i < MAX_EQU; i++)							//추가
			{														//추가
				if(Pgm[i].Disp == 1 && Pgm[i].Sig==1)				//추가
				{
					EquResult3_Temp[i]=EquResult2_Temp[i];					//추가
				}//추가
			}		

		
		}
		else
	  	{
		}
	}
	
	if( (d_in[plc39] != def_in[plc39]) ) 
	{
		if( d_in[plc39] )
		{

			
/*			
			for(i = 0; i < MAX_EQU; i++)							//추가
			{														//추가
				if(Pgm[i].Disp == 1 && Pgm[i].Sig==3)				//추가
				{
					EquResult1_Temp[i]=EquResult4_Temp[i];					//추가
				}//추가

				if(Pgm[i].Disp == 1 && Pgm[i].Sig==2)				//추가
				{
					EquResult4_Temp[i]=EquResult3_Temp[i];					//추가
				}//추가
			}		
			
			
			for(i=0;i<8; i++)
			{
				for(j=0;j<4 ; j++)
				{
					strcpy(Mark_Data_Shift[i][j], Mark_Data[i][j]);	
					
				}
				
			}
			
			sprintf(Mark_Bar_Data," - ");
			
			for(i=0;i<8; i++)
			{
				if(Mark_OnOff[i] !=0)
					strcat(Mark_Bar_Data, Mark_Data_Shift[i][3]); 
			}
*/
           GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, temp_barcode);
            SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, temp_barcode);
			
           GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, temp_barcode);
            SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, temp_barcode);
			

//실제 전송 문자
           GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_6, temp_barcode);
            SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_7, temp_barcode);
			
           GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_5, temp_barcode);
            SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_6, temp_barcode);
			
			
			
			
			GetCtrlVal(mainpanel, MAINPANEL_TEXT_DATA_2, mark_data);
			SetCtrlVal(mainpanel, MAINPANEL_TEXT_DATA_3, mark_data);

			GetCtrlVal(mainpanel, MAINPANEL_TEXT_DATA_1, mark_data);
			SetCtrlVal(mainpanel, MAINPANEL_TEXT_DATA_2, mark_data);
			
			strcpy(Ex_Data[2],Ex_Data[1]);
			strcpy(Ex_Data[1],Ex_Data[0]);
			
			
			

		}
		else
	  	{

		  // 마킹 문자 shift 필요함
		
		}
	}

	
	if( d_in[plc40] != def_in[plc40] ) // DATA SHIFT
	{
		if( d_in[plc40] )
		{
			SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_2,"L");
//    		calc_out_data(pc80, 0); //
  //		calc_out_data(pc81, 0); //
/*		
  
			Marking_OnFlag = 0;
/////  수정 1219		
			if(Work_Sig == 1)
			{
		  		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, ctemp);
		  		SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, ctemp);
		 		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);
			}
			GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, ctemp);
  			SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, ctemp);
	
			if(Work_Sig == 2)
				GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, BAR_DATA);
	
*/		
 		
		}
						else
		{
			  //SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_2,"-");   
		}
	}

		
	if( d_in[plc41] != def_in[plc41] ) //문자 전송1
	{
		if( d_in[plc41] )
		{
			SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_2,"R");	
				
		}
		else
		{
			 //SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_2,"-"); 
		}
			
//			Marking_OnFlag = 1;
			
//			SendMarkingDataLabel();
		
	}

	if( d_in[plc42] != def_in[plc42] ) //마킹 시작
	{
		if( d_in[plc42] )
		{
			SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_3,"L");
			//SetCtrlVal(mainpanel, MAINPANEL_MODEL_LR, 1);//RH
		}
		else
		{
			//SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_3,"-"); 
			//SetCtrlVal(mainpanel, MAINPANEL_MODEL_LR, 0);//LH
		}
	}
	if( d_in[plc43] != def_in[plc43] ) //마킹 END
	{
		if( d_in[plc43] )
		{
			SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_3,"R");
			//SetCtrlVal(mainpanel, MAINPANEL_MODEL_WD, 1);
  
		}
		else
		{
			//SetCtrlVal(mainpanel,MAINPANEL_RETAIN_L_3,"-"); 
			//SetCtrlVal(mainpanel, MAINPANEL_MODEL_WD, 0);
		}
	}
	if( d_in[plc44] != def_in[plc44] ) //마킹 END
	{
		if( d_in[plc44] )
		{
		
  			
   
		}
		else
		{
		}
	}

	if( d_in[plc45] != def_in[plc45] ) //마킹 END
	{
		if( d_in[plc45] )
		{
			SetCtrlVal(mainpanel, MAINPANEL_MODEL_EPB, 1);
  
		}
		else
		{
			SetCtrlVal(mainpanel, MAINPANEL_MODEL_EPB, 0);
		}
	}
	
	
	if( d_in[plc46] != def_in[plc46] ) //마킹 END
	{
		if( d_in[plc46] )
		{
			////제품 카운터
//				Inworkcount ++;
//				SetCtrlVal(mainpanel, MAINPANEL_INWORK_COUNT, Inworkcount);
			
		}
		else
		{
//				LogDataFunc("마킹 끝 ", LogUseFlag);
		}
	}

	if( d_in[plc47] != def_in[plc47] )
	{
		if( d_in[plc47] )
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_1,TRUE);
		}
		else
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_1,FALSE);
		}
	}
	if( d_in[plc48] != def_in[plc48] )
	{
		if( d_in[plc48] )
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_2,TRUE);
		}
		else
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_2,FALSE);
		}
	}
	if( d_in[plc49] != def_in[plc49] ) 
	{
		if( d_in[plc49] )
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_3,TRUE);
		}
		else
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_3,FALSE);
		}
	}
	if( d_in[plc50] != def_in[plc50] )
	{
		if( d_in[plc50] )
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_4,TRUE);
		}
		else
		{
				SetCtrlVal(manualctrl, MANUALCTRL_H_LED_4,FALSE);
		}
	}


	if( (d_in[plc54] != def_in[plc54]) ) 
	{
		if( d_in[plc54] )
		{
		}
	}

	if( (d_in[plc55] != def_in[plc55]) ) 
	{
		if( d_in[plc55] )
		{
		}
	}
	
	if( (d_in[plc77] != def_in[plc77]) )  //마킹기 전송 요구
	{
		if( d_in[plc77] )
		{
//			LogDataFunc("마킹기 전송 신호", 1);
//			calc_out_data(pc77, 0); // 마킹기 전송 불량
//			calc_out_data(pc79, 0); // 마킹기 전송 완료

//			Bar_Send_Flag = 1;
			
		}
	}
	if( (d_in[plc78] != def_in[plc78]) )    //마킹기 마킹 완료
	{
		if( d_in[plc78] )
		{
//			calc_out_data(pc77, 0); // 마킹기 전송 불량
//			calc_out_data(pc79, 0); // 마킹기 전송 완료
			
		}
	}
	if( (d_in[plc79] != def_in[plc79]) )  //마킹기 전송 요구
	{
		if( d_in[plc79] )
		{
//			LogDataFunc("마킹기 재전송 신호", 1);
//			calc_out_data(pc77, 0); // 마킹기 전송 불량
//			calc_out_data(pc79, 0); // 마킹기 전송 불량
	
//			AUX1MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  
//			AUX1PortSendErr=FALSE; 
//			AUX1CallbackRunFlg=0;  

//			Bar_Send_Flag = 1;
			
		}
	}
	
	if( (ByPassFlag && !d_out[pc4]) || (!ByPassFlag && d_out[pc4]) )
		calc_out_data(pc4, ByPassFlag);
	if( (ByPassFlag2 && !d_out[pc5]) || (!ByPassFlag2 && d_out[pc5]) )
		calc_out_data(pc5, ByPassFlag2);
	if( (ByPassFlag3 && !d_out[pc6]) || (!ByPassFlag3 && d_out[pc6]) )
		calc_out_data(pc6, ByPassFlag3);

	if( (ByPassFlag4 && !d_out[pc7]) || (!ByPassFlag4 && d_out[pc7]) )
		calc_out_data(pc7, ByPassFlag4);
	if( (ByPassFlag5 && !d_out[pc13]) || (!ByPassFlag5 && d_out[pc13]) )
		calc_out_data(pc13, ByPassFlag5);


	if( (Zero_Master_Flag && !d_out[pc114]) || (!Zero_Master_Flag && d_out[pc114]) )
		calc_out_data(pc114, Zero_Master_Flag);
	if( (Check_Master_Flag && !d_out[pc115]) || (!Check_Master_Flag && d_out[pc115]) )
		calc_out_data(pc115, Check_Master_Flag);
	
	
//	if( (AMeasMode && !d_out[pc10]) || (!AMeasMode && d_out[pc10]) )
//		calc_out_data(pc10, AMeasMode);
  	
	if( ActivePanel == manualctrl )
	{
		DispCylStatus();
	}

	
	for(i = 0; i < MAX_PLC_ERR; i++ ) // error 발생여부 확인
	{
		if( d_in[plc240 + i] ) // plc error check
		{
			PlcErrNum[i] = 1;
			if( !def_in[plc240 + i] )
			{
				sprintf(ctemp, "%s ON", PlcErrMsg[i]);
	//			AlarmDataFunc(ctemp, 1);

				LogDataFunc(ctemp, 1);
				if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
					SetActivePanel(errpanel);
			}
		}
		else
		{
			PlcErrNum[i] = 0;
			if( def_in[plc240 + i] )
			{
				sprintf(ctemp, "%s OFF", PlcErrMsg[i]);
				LogDataFunc(ctemp, 0);
			}
		}
	}

	////// 이전의 d_in 상태를 저장 def_in 으로
	for( i = 0; i < PLC_IN_NO; i++ )
	{
		if( d_in[i] != def_in[i] )
			def_in[i] = d_in[i];
		
		if( i < PLC_OUT_NO )
		{
			if( d_out[i] != def_out[i])
				def_out[i] = d_out[i];
		}
	}
	
	PlcFirstRunFlag = 1;
}

