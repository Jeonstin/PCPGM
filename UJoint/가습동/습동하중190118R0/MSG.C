//#include <tcpsupp.h>
#include "manual.h"
#include <ansi_c.h>
#include <utility.h>
#include <formatio.h>
#include "main.h"
#include 	<userint.h>
#include 	"MSG.h"
#include 	"UserDefinedConst.h"
#include 	"PLC_IODefinedConst.h"
#include 	"UIRDefinedHeader.h"					  
#include 	"UserDefinedGlobal.h"
#include "keycode.h"

int		ErrPanelDispFlag;
int CVICALLBACK logpanelCallback (int panel, int event, void *callbackData,
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

int CVICALLBACK msgclose (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			if( UserModalFlag )
				RemovePopup(0); // modal => modeless
			HidePanel(msgpanel);
			UserModalFlag = 0;
			break;
		}
	return 0;
}

int CVICALLBACK msgpanelcallback (int panel, int event, void *callbackData,
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

int CVICALLBACK msgtimercallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_TIMER_TICK:
			SetCtrlAttribute(msgpanel, MSGPANEL_TIMER, ATTR_ENABLED, FALSE);
			if( UserModalFlag )
				RemovePopup(0); // modal => modeless
			HidePanel(msgpanel);
			UserModalFlag = 0;
			break;
		}
	return 0;
}

void UpdateErrMessage(void)
{
	int		i, flag = 0, errflag = 0;
	
	for( i = 0; i < MAX_IN_ERR; i++)
	{
		if( InErrNum[i] != OldInErrNum[i] )
		{
			flag = 1;
			OldInErrNum[i] = InErrNum[i];
		}
		
		if( InErrNum[i] )	errflag = 1;
	}

	for( i = 0; i < MAX_PLC_ERR; i++)
	{
		if( PlcErrNum[i] != OldPlcErrNum[i] )
		{
			flag = 1;
			OldPlcErrNum[i] = PlcErrNum[i];
		}
		
		if( PlcErrNum[i] )	errflag = 1;
	}
	
	if( !errflag ) // 에러가 하나도 없다.
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_ERRVIEW, ATTR_LABEL_COLOR, VAL_WHITE);
		SetCtrlAttribute (mainpanel,MAINPANEL_ERRVIEW, ATTR_LABEL_TEXT,"ALARM");   //수동측정

		ClearListCtrl(errpanel, ERRPANEL_LISTBOX); // 내용 삭제
		SetPanelAttribute(errpanel, ATTR_WINDOW_ZOOM, VAL_MINIMIZE);
		return;
	}
	
	if( errflag )
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_ERRVIEW, ATTR_LABEL_COLOR, VAL_RED);
        SetCtrlAttribute (mainpanel,MAINPANEL_ERRVIEW, ATTR_LABEL_TEXT,"ALARM");   //수동측정

		ClearListCtrl(errpanel, ERRPANEL_LISTBOX); // 내용 삭제
		for( i = 0; i < MAX_IN_ERR; i++)
		{
			if( InErrNum[i] )
				InsertListItem(errpanel, ERRPANEL_LISTBOX, -1, InErrMsg[i], 0);
		}

		for( i = 0; i < MAX_PLC_ERR; i++)
		{
			if( PlcErrNum[i] )
				InsertListItem(errpanel, ERRPANEL_LISTBOX, -1, PlcErrMsg[i], 0);
		}
	}
}

//char	*PlcErrMsg[MAX_PLC_ERR] = {
//char	*InErrMsg[MAX_IN_ERR] = {
//int	PlcErrNum[MAX_PLC_ERR], OldPlcErrNum[MAX_PLC_ERR];
//int	InErrNum[MAX_IN_ERR], OldInErrNum[MAX_IN_ERR]; // error 발생여부.
int CVICALLBACK ErrMsgCallback (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ErrPanelDispFlag = 1;
			for( i = 0; i < MAX_IN_ERR; i++)
				OldInErrNum[i] = 0;
			for( i = 0; i < MAX_PLC_ERR; i++)
				OldPlcErrNum[i] = 0;

			UpdateErrMessage();
			SetCtrlAttribute(panel, ERRPANEL_TIMER, ATTR_ENABLED, TRUE);
			break;
		case EVENT_LOST_FOCUS:
			if(PopupFlag)
				ErrPanelDispFlag = 0;
			SetCtrlAttribute(panel, ERRPANEL_TIMER, ATTR_ENABLED, FALSE);
			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK ErrChkTimerCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_TIMER_TICK:
			UpdateErrMessage();
			break;
		}
	return 0;
}

/*
int CVICALLBACK ErrDispTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		OldErrDispCurNum, tempErr = 0, MaxChkNum;
	
	if( (ActivePanel != mainpanel) || St1ReadIng || St1CalcIng )
		return 0;

	MaxChkNum = MAX_PLC_ERR + MAX_IN_ERR;
	OldErrDispCurNum = ErrDispCurNum;
	ErrDispCurNum++;
	strcpy(StatusMsg," ");   // 상태정보창 정상
	
//	PlcErrNum[0] = PlcErrNum[1] = PlcErrNum[2]= InErrNum[0] = 1; // test
	switch (event)
		{
		case EVENT_TIMER_TICK:
		
			while(1)
			{
				if( ErrDispCurNum >= MAX_IN_ERR )
				{
					if( PlcErrNum[ErrDispCurNum - MAX_IN_ERR] )
					{
						tempErr = 1;
						break;
					}
				}
				else
				{
					if( InErrNum[ErrDispCurNum] )
					{
						tempErr = 1;
						break;
					}
				}
				
				
				if( ErrDispCurNum == OldErrDispCurNum )
					break;
				ErrDispCurNum++;
				if( ErrDispCurNum >= MaxChkNum )
					ErrDispCurNum = 0;
			}

			if( tempErr )
			{
				if( ErrDispCurNum >= MAX_IN_ERR )
				    strcpy(StatusMsg, PlcErrMsg[ErrDispCurNum - MAX_IN_ERR]);
				else
				    strcpy(StatusMsg, InErrMsg[ErrDispCurNum]);
			    
				if( ActivePanel == mainpanel )
				{
			    	SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_BGCOLOR, VAL_RED);
					SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_COLOR, VAL_WHITE);
					SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, StatusMsg);
				}
			}
			else
			{
				if( ActivePanel == mainpanel )
				{
			    	SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_BGCOLOR, VAL_WHITE);
					SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_COLOR, VAL_BLACK);
					SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, StatusMsg);
				}
			}

			break;
		}
	return 0;
}

*/

int CVICALLBACK Comm_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK Lan_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;
			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK Err_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK Pos_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK ErrView (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		 	SetActivePanel(errpanel);
			break;
		}
	return 0;
}

int CVICALLBACK Switch_LanUse1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			
			LanUse();

			break;
		}
	return 0;
}

int CVICALLBACK SysSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		Temp;

	switch (event)
		{
		case EVENT_COMMIT:

			break;

		case EVENT_VAL_CHANGED:
			switch(control)
			{
				case COMM_SET_AMPCABLE :				// 	케이블 종류 체크
					GetCtrlVal(panel, COMM_SET_AMPCABLE, &AmpCableID);
					break;
				case COMM_SET_AMPPORT:				//	Amp. Port No.
					GetCtrlVal(panel, COMM_SET_AMPPORT, &AmpPortNo);
					if( AmpPortNo &&				// Port 번호가 중복이면
						(AmpPortNo==PlcPortNo ||
						AmpPortNo==MarkPortNo ||
						AmpPortNo==AUX2PortNo )   )
					{
						MessagePopup ("Port Setup Error", "Port Duplicate.");
						AmpPortNo=0;
					}
					GetIndexFromValue(panel, COMM_SET_AMPPORT, &Temp, AmpPortNo);
					SetCtrlIndex(panel, COMM_SET_AMPPORT, Temp);
					break;

				case COMM_SET_PLCPORT:				//	Plc. Port No.
					GetCtrlVal(panel, COMM_SET_PLCPORT, &PlcPortNo);
					if( PlcPortNo &&				// Port 번호가 중복이면
						(PlcPortNo==AmpPortNo ||
						PlcPortNo==MarkPortNo ||
						PlcPortNo==AUX2PortNo )   )
					{
						MessagePopup ("Port Setup Error", "Port Duplicate.");
						PlcPortNo=0;
					}
					GetIndexFromValue(panel, COMM_SET_PLCPORT, &Temp, PlcPortNo);
					SetCtrlIndex(panel, COMM_SET_PLCPORT, Temp);
					break;

				case COMM_SET_AUX1PORT:				//	Mark. Port No.
					GetCtrlVal(panel, COMM_SET_AUX1PORT, &MarkPortNo);
					if( MarkPortNo &&				// Port 번호가 중복이면
						(MarkPortNo==AmpPortNo ||
						MarkPortNo==PlcPortNo ||
						MarkPortNo==AUX2PortNo )   )
					{
						MessagePopup ("Port Setup Error", "Port Duplicate.");
						MarkPortNo=0;
					}
					GetIndexFromValue(panel, COMM_SET_AUX1PORT, &Temp, MarkPortNo);
					SetCtrlIndex(panel, COMM_SET_AUX1PORT, Temp);
					break;

				case COMM_SET_AUX2PORT:				//	AUX2. Port No.
					GetCtrlVal(panel, COMM_SET_AUX2PORT, &AUX2PortNo);
					if( AUX2PortNo &&				// Port 번호가 중복이면
						(AUX2PortNo==AmpPortNo ||
						AUX2PortNo==PlcPortNo ||
						AUX2PortNo==MarkPortNo )   )
					{
						MessagePopup ("Port Setup Error", "Port Duplicate.");
						AUX2PortNo=0;
					}
					GetIndexFromValue(panel, COMM_SET_AUX2PORT, &Temp, AUX2PortNo);
					SetCtrlIndex(panel, COMM_SET_AUX2PORT, Temp);
					break;

			}
			break;

		}
	return 0;
}

int CVICALLBACK PortPar1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			RemovePopup(0);
			SetActivePanel(comconfig1);

			break;
		}
	return 0;
}

int CVICALLBACK PortSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		Temp;
	
	GetCtrlVal(panel, COMCONFIG1_COMPORT, &PortNo);

	switch (event)
	{
		case EVENT_VAL_CHANGED:
			switch(control)
			{
				case COMCONFIG1_COMPORT:
					SetCtrlVal(panel, COMCONFIG1_CTSMODE, ComPar[PortNo].CTSMode);
					
					SetCtrlVal(panel, COMCONFIG1_XMODE, ComPar[PortNo].XMode);
					
					GetIndexFromValue(panel, COMCONFIG1_BAUDRATE, &Temp, ComPar[PortNo].BaudRate);
					SetCtrlIndex(panel, COMCONFIG1_BAUDRATE, Temp);
					
					GetIndexFromValue(panel, COMCONFIG1_PARITY, &Temp, ComPar[PortNo].Parity);
					SetCtrlIndex(panel, COMCONFIG1_PARITY, Temp);
					
					GetIndexFromValue(panel, COMCONFIG1_DATABITS, &Temp, ComPar[PortNo].Data);
					SetCtrlIndex(panel, COMCONFIG1_DATABITS, Temp);
					
					GetIndexFromValue(panel, COMCONFIG1_STOPBITS, &Temp, ComPar[PortNo].Stop);
					SetCtrlIndex(panel, COMCONFIG1_STOPBITS, Temp);
					
					SetCtrlVal(panel, COMCONFIG1_INPUTQ, ComPar[PortNo].InQ);
					
					SetCtrlVal(panel, COMCONFIG1_OUTPUTQ, ComPar[PortNo].OutQ);
					
					SetCtrlVal(panel, COMCONFIG1_TIMEOUT, ComPar[PortNo].Timeout);
					break;
					
				case COMCONFIG1_CTSMODE:
					GetCtrlVal(panel, COMCONFIG1_CTSMODE, &ComPar[PortNo].CTSMode);
					break;
					
				case COMCONFIG1_XMODE:
					GetCtrlVal(panel, COMCONFIG1_XMODE, &ComPar[PortNo].XMode);
					break;
					
				case COMCONFIG1_BAUDRATE:
					GetCtrlVal(panel, COMCONFIG1_BAUDRATE, &ComPar[PortNo].BaudRate);
					break;
					
				case COMCONFIG1_PARITY:
					GetCtrlVal(panel, COMCONFIG1_PARITY, &ComPar[PortNo].Parity);
					break;
					
				case COMCONFIG1_DATABITS:
					GetCtrlVal(panel, COMCONFIG1_DATABITS, &ComPar[PortNo].Data);
					break;
					
				case COMCONFIG1_STOPBITS:
					GetCtrlVal(panel, COMCONFIG1_STOPBITS, &ComPar[PortNo].Stop);
					break;
			}
			break;
		case EVENT_LEFT_CLICK:
			switch(control)
			{
				case COMCONFIG1_INPUTQ:
					callKEYPAD(panel, control, event, NON_TABLE, &ComPar[PortNo].InQ, 0);
					break;
					
				case COMCONFIG1_OUTPUTQ:
					callKEYPAD(panel, control, event, NON_TABLE, &ComPar[PortNo].OutQ, 0);
					break;
					
				case COMCONFIG1_TIMEOUT:
					callKEYPAD(panel, control, event, NON_TABLE, &ComPar[PortNo].Timeout, 0);
					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK Opt_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;


			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK ContNgChkFlagCallback1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &ContNgCntUseFlag);

			break;
		}
	return 0;
}

int CVICALLBACK ByPass (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

int CVICALLBACK ByPass1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &ByPassFlag);

			break;
		}
	return 0;
}

int CVICALLBACK SpcOnOff1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SPCViewOnOff();

			break;
		}
	return 0;
}

int CVICALLBACK Cont_Module (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

void	Save_ErrMsg(void)
{
	int	hFile, j;
    char FileStamp[200];
	char	ctemp[100];
	char	*comment[1000];
//    int  Status;
    
    
            //	Project Directory
			strcpy(WorkingDirectory, PrjDirectory);
	        
			//	저장 Directory 설정
			strcat(WorkingDirectory, "\\SYS");
			
			if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
			{
			    MakeDir (WorkingDirectory);			//	Directory생성
//			    SetDir(WorkingDirectory);
			}
			SetDir (PrjDirectory);
			strcpy(FileStamp,WorkingDirectory);
			strcat(FileStamp,"\\PlcErrMsg.txt");	
    	   	
			AllTimerStart(0);

		  if((hFile = OpenFile (FileStamp, VAL_WRITE_ONLY, VAL_TRUNCATE,
								VAL_ASCII)) == -1)
		  {
			  sprintf(ctemp," FILE OPEN ERROR CODE : %d",GetFmtIOError);
			  ConfirmPopup ("FILE OPEN ERROR !", ctemp);
			  return ;
		  }
			
			for(j=0;j<MAX_PLC_ERR;j++)
			{	

				
				GetTableCellRangeVals(err1panel,ERR_SET_EMSG, MakeRect(1, 1, j+1, 1),
								comment, VAL_COLUMN_MAJOR);
		  	    WriteLine (hFile, comment[j], -1);
				sprintf(PlcErrMsg[j],"%s",comment[j]);
				
//				PlcErrMsg[j] = comment[j];
				
			}
			
			CloseFile(hFile);
}

int CVICALLBACK Work_Set (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;


			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

void CVICALLBACK Work_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
			sys3PWFlag=TRUE;
			SetActivePanel(pw);
/*
			ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
			DisplayPanel(workpanel);
			InstallPopup(workpanel);
*/	
}

int CVICALLBACK WorkSetup10 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_VAL_CHANGED:
			WriteModelData();
			ModelChanged();

			break;
		}
	return 0;
}

int CVICALLBACK WorkerSetup10 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	CtrlIndex;
	
	switch (event)
		{
		case EVENT_VAL_CHANGED:
			GetCtrlIndex (workpanel, WORK_SET_WORKER1, &CtrlIndex);			
			SetCtrlIndex (modelsetup, MODELSETUP_WORKER, CtrlIndex);			

			SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, 0);
			// 화면에 나타난 가공기 1 합격 횟수 리셋
			SetCtrlVal( mainpanel, MAINPANEL_LG, 0);
			// 화면에 나타난 가공기 2 횟수 리셋
//			SetCtrlVal( mainpanel, MAINPANEL_RG, 0);
			// 화면에 나타난 가공기 1 불합격 횟수 리셋
			SetCtrlVal( mainpanel, MAINPANEL_LNG, 0);
			// 화면에 나타난 가공기 2 불합격 횟수 리셋
//			SetCtrlVal( mainpanel, MAINPANEL_RNG, 0);

			//	주화면의 표시변수 Reset, SPC Data Display
			ResetMainWindowVariable();

			break;
		}
	return 0;
}

int CVICALLBACK Add0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Add1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int CVICALLBACK Rename0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Rename1 ( panel, control,  event, callbackData, eventData1, eventData2);


			break;
		}
	return 0;
}

int CVICALLBACK Remove0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Remove1 ( panel, control, event, callbackData, eventData1, eventData2);

			break;
		}
	return 0;
}

int CVICALLBACK SysSetup2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
 					GetCtrlVal(panel, COMM_SET_AMPMODEL, &AmpModelID);

			break;
	}
	return 0;
}

int CVICALLBACK A_Reverse (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &ReverseFlag);

			break;
	}
	return 0;
}

int CVICALLBACK A_Meas_Mode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &AMeasMode);

			break;
	}
	return 0;
}

int CVICALLBACK Add_worker (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		j, NumofWorker, Temp;
	char	cTemp[51];//, cTempDir[512];

	switch (event)
	{
		case EVENT_COMMIT:
  			Temp = GenericMessagePopup ("(Add Worker)",
										"(Add Worker Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);
			if(Temp==1)								//	추가
			{
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				InsertListItem (modelsetup, MODELSETUP_WORKER, -1, cTemp, NumofWorker);
				InsertListItem ( workpanel, WORK_SET_WORKER1, -1, cTemp, NumofWorker);
				SetCtrlIndex (modelsetup, MODELSETUP_WORKER, NumofWorker);
				SetCtrlIndex ( workpanel, WORK_SET_WORKER1, NumofWorker);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j = 0; j < NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);
			}

			break;
	}
	return 0;
}

int CVICALLBACK ByPass2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &ByPassFlag2);

			break;
	}
	return 0;
}

int CVICALLBACK ByPass3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &ByPassFlag3);

			break;
	}
	return 0;
}

int CVICALLBACK ByPass4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &ByPassFlag4);

			break;
	}
	return 0;
}

int CVICALLBACK SpcOnOff2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		  		SPCViewOnOff();

			break;
	}
	return 0;
}

int CVICALLBACK IntPanelEvent (int panel, int event, void *callbackData,
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
			
		case EVENT_KEYPRESS:
//			sprintf(temp, "%d,0x%X, ", eventData1, eventData1); // test
//			MessagePopup("key", temp);
//			return 1;
//			m_keycode = (int *)eventData2;
//			m_keycodeval = *m_keycode;
			switch(eventData1)
			{
				case	_C_Q:  // ^D

				SetCtrlAttribute (interdata, INTPANEL_FILTER_ONOFF, ATTR_VISIBLE, 1);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_CNT, ATTR_VISIBLE, 1);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_H, ATTR_VISIBLE, 1);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_L, ATTR_VISIBLE, 1);

				SetCtrlAttribute (interdata, INTPANEL_ORDER_PER, ATTR_VISIBLE, 1);
	
				break;
			
			}
			
	}
	return 0;
}

int CVICALLBACK ZeroSetMode2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &AutoZeroCntUseFlag);
			GetCtrlVal(panel, control, &AutoZeroHourUseFlag);

			break;
	}
	return 0;
}

int CVICALLBACK ContNgChkFlagCallback2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &ContNgCntUseFlag);

			break;
	}
	return 0;
}

int CVICALLBACK Enc_Dir2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
					GetCtrlVal(interdata, INTPANEL_ENC_DIR, &EncDir);

			break;
	}
	return 0;
}

int CVICALLBACK SpcOnOff3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ByPass2_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlVal(panel, control, &ByPassFlag3);

			break;
	}
	return 0;
}

int CVICALLBACK ByPass2_5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
	 			GetCtrlVal(panel, control, &ByPassFlag5);

			break;
	}
	return 0;
}

int CVICALLBACK AUTO_Retry2 (int panel, int control, int event,
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

int CVICALLBACK DatapanelCall (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_GOT_FOCUS:
  			ActivePanel = panel;

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
			
		case EVENT_KEYPRESS:
			switch( eventData1 )
			{
				case _C_S: // ^S  // ST1
					GSt1Sig = 1;
					for(i = 0; i < MeasPoints; i++)
					{
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
						SetCtrlVal( mainpanel, PointCtrl[i], 0.0);
					}

//					GSt1Sig = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 720; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()

							RepeatChVal[RepeatChIndex][i] = ((double)rand() / 1000.0);
							
						}
					}
			
					RepeatChIndex = 720;
						
						ModeID = 0;
						TestFinish();
					break;
					
			}
			break;
			
	}
	return 0;
}

int CVICALLBACK View_garph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlIndex(datapanel, DATAPANEL_RING_2,&Model_LR) ;
			TurnDataGraphPlot3(Model_LR,Graph_Index,datapanel);	

			break;
	}
	return 0;
}

int CVICALLBACK View_Chdata (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
 			GetCtrlIndex(panel, control,&Model_LR) ;
			TurnDataGraphPlot2(Model_LR,Graph_Index,manualctrl);	

			break;
	}
	return 0;
}

int CVICALLBACK setLanguage2 (int panel, int control, int event,
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

int CVICALLBACK ByPass6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 	 			GetCtrlVal(panel, control, &ByPassFlag4);

			break;
	}
	return 0;
}

int CVICALLBACK Connect_Mark (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

			Connect_Tcp();

			
			break;
	}
	return 0;
}

int CVICALLBACK Shaft_Ldata (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &Shaft_Low,0);
			break;
	}
	return 0;
}

int CVICALLBACK Shaft_Hdata (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &Shaft_High,0);
			break;
	}
	return 0;
}

int CVICALLBACK Tube_Ldata (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &Tube_Low,0);
			break;
	}
	return 0;
}

int CVICALLBACK Tube_Hdata (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &Tube_High,0);
			break;
	}
	return 0;
}

int CVICALLBACK Keypad (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &Tube_High,0);
			break;
	}
	return 0;
}

int CVICALLBACK Yaxis_Low (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &YaxisLow,0);
			break;
	}
	return 0;
}

int CVICALLBACK Yaxis_High (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &YaxisHigh,0);
			break;
	}
	return 0;
}

int CVICALLBACK SetContNg (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &ContNgChkNum,0);
			break;
	}
	return 0;
}
		 

int CVICALLBACK SpcDataNo2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &SpcDataNo,0);
			break;
	}
	return 0;
}

int CVICALLBACK SpcSigma2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &SpcSigma,0);
			break;
	}
	return 0;
}

int CVICALLBACK ZeroSetInterval (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &AutoZeroChkNum,0);
			break;
	}
	return 0;
}

int CVICALLBACK ZeroSetHour (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &AutoZeroChkHour,0);
			break;
	}
	return 0;
}

int CVICALLBACK Master_Rpt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
 					callKEYPAD(panel, control, event, NON_TABLE, &MasterRepeatChkNum,0);
			break;
	}
	return 0;
}
