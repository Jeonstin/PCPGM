#include	"windows.h"
#include <rs232.h>
#include <ansi_c.h>
#include 	<utility.h>
#include	"stdio.h"
#include 	<userint.h>
#include 	"UserDefinedConst.h"
#include 	"PLC_IODefinedConst.h"
#include 	"UIRDefinedHeader.h"					  
#include 	"UserDefinedGlobal.h"
 

void  check_iomon(void);  				// PLC.C 에 사용됨.
void  calc_out_data(int bit, int set); 	// PLC.C 에 사용됨.

char		OldAmpErr; // 에러 발생 상태
int		nick_no1=0,nick_no2=0,nick_no3=0,nick_no4=0;// nick를 순서적으로 값 비교하기 위해 순차적으로 정가함.
 int		Finish_Meas=0;

int CVICALLBACK ThreadFunction(void *functionData)
{
	int		i, j;//, j, l, CH_count; //, EventPanel, EventCtrl;
	char	temp[50], ctemp[50];
	double	dtemp[MAX_POINT];
//	double  value;
	
	while( MainLoopFlag ) // 1초에 약 80 ~ 100번 실행된다.(아무것도 안할때???), Sleep() 땜시
	{

//	if( ActivePanel == mainpanel ) // test
//	{
//		sg_cnt++;  // 테스트용, test
//		if( sg_cnt > 10000000 )	sg_cnt = 0;
//	}

		// 2 ms delay와 비슷하지만 CPU를 점유하지 않는 DELAY
		Sleep(2); // 이것은 지우지 말것. 지우면 CPU를 너무 많이 점유해서 전체적으로 느려질수 있슴.
  		if( (ActivePanel == manualctrl) && RealTimeFlag )
		{
			if( RepeatChIndex >= 2 )  // RepeatMpiChIndex
			{
				ManualTestFinish();
				AmpStart(1); // 센서값을 다시 화면에 표시
				RepeatChIndex = 0;
				Sleep(50); // 이것은 지우지 말것. 지우면 CPU를 너무 많이 점유해서 전체적으로 느려질수 있슴.
			}
		}

		if( AmpRdEndFlag )
		{
			St1CalcIng = 1;
			if( GSt1Sig ==2 ) 
				Finish_Meas = 0;
			
			JSenValSave(); // 확인용, test
			
			if( ActivePanel == zerosetup )
			{
				ZeroSetupFinish();
				Meas_Start_On_Flag = 0;
			}
			else if( d_in[plc4]==0 )
			{
				ModeID = 1;
				ManualTestFinish();
				Meas_Start_On_Flag = 0;
				AmpStart(1); // 센서값을 다시 화면에 표시
			}
			else if( d_in[plc4]==1  ) 
			{
				ModeID = 0;
				nick_no1 =nick_no2 =nick_no3 =nick_no4 = 0;
				TestFinish();
				Finish_Meas = 1;
				Meas_Start_On_Flag = 0;
				AmpStart(1); // 센서값을 다시 화면에 표시
			}
			
			calc_out_data(pc11, 0); // ST1 측정중
			St1CalcIng = St1EndPtFlag = 0;
			St1MeasIng = 0; // 측정중 종료
			AmpRdEndFlag = 0; // ST1에서 측정값을 구하기 위한 센서값을 다 읽었슴.
		}

		if( (AmpCommErr || AmpPortOpenErr || !AmpParaReadFlag ) )
		{
			if( !OldAmpErr )
			{
				OldAmpErr = 1;
				ManualCtrlSt1Dimmed(1);
				ZeroSetCtrlSt1Dimmed(1);
			}
		}
		else if( OldAmpErr )
		{
			OldAmpErr = 0;
			if( !St1MeasIng )
			{
				ManualCtrlSt1Dimmed(0);
				ZeroSetCtrlSt1Dimmed(0);
			}
		}
		
		
		
		if( ActivePanel == manualctrl) // 수동측정 화면이고 측정중이 아니면
		{
					ServoDataRead();
		}
//		if( (ActivePanel == manualctrl) && AmpRunFlag && !St1MeasIng && !St1CalcIng ) // 수동측정 화면이고 측정중이 아니면
		if( (ActivePanel == manualctrl) && AmpRunFlag  && !St1CalcIng ) // 수동측정 화면이고 측정중이 아니면
		{
			for(i = 0; i < ProbeIndex; i++)
//			for(i = 0; i < 9; i++)
				SetCtrlVal(manualctrl, SensorCtrl[i], ChData[ChNo[i].no - 1] );
		}
			
		
		if( !St1MeasIng && LogDataSaveRdy )
		{
			LogDataSaveRdy = 0;
			AllTimerStart(0);
			LogDataSave();
			ClearListCtrl(logpanel, LOGPANEL_LISTBOX); // 내용 삭제
			AllTimerStart(1);
		}
		
		if(Bar_Send_Flag)
		{
/////////////////
				j = Start_Mark; 
			if(!J_Flag && MarkEndFlag) //간격 전송	  Mark_Space
			{
						MarkEndFlag = 0;
						SendDataAUX1(5, Mark_Data[0][5]);
						J_Flag = 1;
				
			}
			//	j = Start_Mark;
			if(Start_Mark <8 && J_Flag)
			{
				if(MarkSend_No == 0&& MarkEndFlag)
				{
						MarkEndFlag = 0;
						SendDataAUX1(0, Mark_Data[j][0]);
				}
				else if(MarkSend_No == 1 && MarkEndFlag)
				{
					MarkEndFlag = 0;
					SendDataAUX1(1, Mark_Data[j][1]);
				}
				else if(MarkSend_No == 2 && MarkEndFlag)
				{
					MarkEndFlag = 0;
					SendDataAUX1(2, Mark_Data[j][2]);
				}
				else if(MarkSend_No == 3 && MarkEndFlag)
				{
					MarkEndFlag=0;
					SendDataAUX1(3, Mark_Data[j][3]);
				}
				else if(MarkSend_No == 4 && MarkEndFlag)
				{
					MarkEndFlag=0;
					SendDataAUX1(4, Mark_Data[j][4]);
					Start_Mark++;
					MarkSend_No = 0;

				}
			}
/////////					

/*
				if(Start_Mark==8 && MarkEndFlag)
				{
					MarkEndFlag=0;
					Start_Mark++;

					MarkSend_No = 0;

					sprintf(temp, "%cI%03d00%03d00%03d", 0x02, M_1_Vel, M_2_Vel, M_3_Vel); 
					Calc_Check_Sum(temp);
					sprintf(ctemp, "%s%02x%c", temp,Sum, 0x03); 
					ComWrt(MarkPortNo, ctemp, strlen(ctemp));
					
				}
*/
			if(Start_Mark==8 && MarkEndFlag)
				{
					Start_Mark = 0;
					MarkSend_No = 0;
					Bar_Send_Flag=0;
				 	calc_out_data(pc122 , 1);

					LogDataFunc("마킹 전송 완료", 1);
	
/*
					sprintf(temp, "%cV", 0x02); 
					Calc_Check_Sum(temp);
					sprintf(ctemp, "%s%02x%c", temp,Sum, 0x03); 
					ComWrt(MarkPortNo, ctemp, strlen(ctemp));
*/					
				}
				

			
		}
	
		if(A_Bar_Send_Flag)
		{
/////////////////
				j = Start_Mark;
			if(Start_Mark <8)
			{
				if( MarkEndFlag)
				{
					MarkEndFlag=0;
					SendDataAUX1(3, Mark_Data_Shift[j][3]);
					Start_Mark++;
//					MarkSend_No = 0;
				}
			}
/////////					

			
				if(Start_Mark==8 && MarkEndFlag)
				{
					Start_Mark = 0;
					MarkSend_No = 0;
					A_Bar_Send_Flag=0;
				 	calc_out_data(pc122 , 1);
					LogDataFunc("auto 마킹 전송 완료", 1);
				}
				

			
		}
		
		
		
	}	
 		
		
	return 0;
}

int CVICALLBACK ThreadFunction_IO(void *functionData)
{
	
	while( MainLoopFlag ) // 1초에 약 80 ~ 100번 실행된다.(아무것도 안할때???), Sleep() 땜시
	{

//		return 0;//TEST용
		// 2 ms delay와 비슷하지만 CPU를 점유하지 않는 DELAY
		if(	!AmpError_DGT && AmpRunFlag && AmpModelID==2 )//&& !First_Read)
			Digit_Probe_Read();

		
		
	//	PlcInCommSend();
		
	}
	
	return 0;
}


void	SleepFunc(int	msec)
{
	Sleep(msec);
}

//// int rename( const char *oldname, const char *newname ); // file or directory
//// return   0: success;
int	DirRenameFunc(const char *oldname, const char *newname )
{
	return	rename(oldname, newname);
}

int DelTreeFunc( const char *oldname )
{
	char	ctemp[256]; // MAX_PATH_LENGTH
	
	sprintf(ctemp, "%s\\DATA", oldname);
	if( !SetDir(ctemp) ) // 성공
	{
		DeleteFile ("*.*");
		SetDir(oldname);
		DeleteDir(ctemp);
	}
	
	DeleteFile ("*.*");
	sprintf(ctemp, "%s\\PRODUCT", PrjDirectory);
	SetDir(ctemp);
	DeleteDir(oldname);
	SetDir(PrjDirectory);
	
	return 0; // 성공
}

int	CtrlKeyStat(void)
{
	if( GetKeyState(VK_CONTROL) & 0x8000 )
		return 1;
	else
		return 0;
}

