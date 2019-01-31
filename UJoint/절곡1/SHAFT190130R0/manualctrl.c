#include "MSG.h"

//#include "manualctrl.h"
#include "manual.h"
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <analysis.h>
#include <userint.h>
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "manualctrl1.h"
#include "keycode.h"


extern		int		resultview;
extern		int		CalcTestMode;

int			TestRunSet;
int			ManuRepeatMeasNo; // �������� �ݺ� ������ display NO.
int			ByPassFlag, ByPassFlag2, ByPassFlag3, ByPassFlag4, ByPassFlag5;

int			ManualTest;
int			ManualTestAvgNo;
//			double		ManualTestTime;
// 1 Cycle �����Ϸ� ���� (Ƚ��/�ð�/PLC����)
int			ManualTestStop;

//	���� ��������� ��������, R&R�������� ����ϱ����� �������� ������
int			ManualCycleNoSet_1;
//  1ȸ, �ݺ� ������
int			ManualCycleMode_1;
//	����ȸ�� Reset : ���ο� ���� ���� ���۶����� Reset
int			ManualOneTimeNo_1, ManualOneTimeNo_2;

//	�������� Data���� ���۽� Set, Data���� �Ϸ�� Reset
//int			ManualDataAcqFlag;
//	�������� ���۽� Set, ���� �Ϸ�� Reset
//int			DoingManualTestFlag;

int SensorCtrl[MAX_CH] = {	MANUALCTRL_CH1,  MANUALCTRL_CH2,  MANUALCTRL_CH3,  MANUALCTRL_CH4, MANUALCTRL_CH5,
							MANUALCTRL_CH6,  MANUALCTRL_CH7,  MANUALCTRL_CH8,  MANUALCTRL_CH9,  MANUALCTRL_CH10,
							MANUALCTRL_CH11, MANUALCTRL_CH12, MANUALCTRL_CH13,  MANUALCTRL_CH14, MANUALCTRL_CH15,
							MANUALCTRL_CH16, MANUALCTRL_CH17, MANUALCTRL_CH18, MANUALCTRL_CH19, MANUALCTRL_CH20,
							MANUALCTRL_CH21, MANUALCTRL_CH22, MANUALCTRL_CH23, MANUALCTRL_CH24,
						 MANUALCTRL_CH25,
							MANUALCTRL_CH26, MANUALCTRL_CH27, MANUALCTRL_CH28};//, MANUALCTRL_CH29, MANUALCTRL_CH30,
//							MANUALCTRL_CH31, MANUALCTRL_CH32, MANUALCTRL_CH33, MANUALCTRL_CH34, MANUALCTRL_CH35,
//							MANUALCTRL_CH36, MANUALCTRL_CH37, MANUALCTRL_CH38, MANUALCTRL_CH39, MANUALCTRL_CH40,
//							MANUALCTRL_CH41, MANUALCTRL_CH42, MANUALCTRL_CH43, MANUALCTRL_CH44, MANUALCTRL_CH45,
//							MANUALCTRL_CH46, MANUALCTRL_CH47, MANUALCTRL_CH48,
//						};

int MenuSwCtrl[MAX_MANU_SW] = {	MANUALCTRL_SOL1_2,  MANUALCTRL_SOL2_2,  MANUALCTRL_SOL3_2,  MANUALCTRL_SOL4_2, MANUALCTRL_SOL5_2,
								MANUALCTRL_SOL6_2,  MANUALCTRL_SOL7_2,  MANUALCTRL_SOL8_2,  MANUALCTRL_SOL9_2,  MANUALCTRL_SOL10_2,
								MANUALCTRL_SOL11_2, MANUALCTRL_SOL12_2, MANUALCTRL_SOL13_2,  MANUALCTRL_SOL14_2, MANUALCTRL_SOL15_2,
								MANUALCTRL_SOL16_2,  MANUALCTRL_SOL17_2,  MANUALCTRL_SOL18_2,  MANUALCTRL_SOL19_2,
								MANUALCTRL_SOL20_2, MANUALCTRL_SOL21_2, MANUALCTRL_SOL22_2, MANUALCTRL_SOL23_2,  MANUALCTRL_SOL24_2,MANUALCTRL_SOL25_2,
								MANUALCTRL_SOL26_2,  MANUALCTRL_SOL27_2,  MANUALCTRL_SOL28_2,  MANUALCTRL_SOL29_2,  MANUALCTRL_SOL30_2,
								MANUALCTRL_SOL31_2, MANUALCTRL_SOL32_2, MANUALCTRL_SOL33_2,  MANUALCTRL_SOL34_2,MANUALCTRL_SOL35_2,
								MANUALCTRL_SOL36_2,  MANUALCTRL_SOL37_2,  MANUALCTRL_SOL38_2,  MANUALCTRL_SOL39_2,  MANUALCTRL_SOL40_2,
								MANUALCTRL_SOL41_2, MANUALCTRL_SOL42_2, MANUALCTRL_SOL43_2,  MANUALCTRL_SOL44_2,MANUALCTRL_SOL45_2
							};

int MenuSwLampCtrl[MAX_MANU_SW] = {	MANUALCTRL_SOL1_L_2,  MANUALCTRL_SOL2_L_2,  MANUALCTRL_SOL3_L_2,  MANUALCTRL_SOL4_L_2, MANUALCTRL_SOL5_L_2,
								MANUALCTRL_SOL6_L_2,  MANUALCTRL_SOL7_L_2,  MANUALCTRL_SOL8_L_2,  MANUALCTRL_SOL9_L_2,  MANUALCTRL_SOL10_L_2,
								MANUALCTRL_SOL11_L_2, MANUALCTRL_SOL12_L_2, MANUALCTRL_SOL13_L_2,  MANUALCTRL_SOL14_L_2, MANUALCTRL_SOL15_L_2,
								MANUALCTRL_SOL16_L_2,  MANUALCTRL_SOL17_L_2,  MANUALCTRL_SOL18_L_2,  MANUALCTRL_SOL19_L_2,  MANUALCTRL_SOL20_L_2,
								MANUALCTRL_SOL21_L_2, MANUALCTRL_SOL22_L_2, MANUALCTRL_SOL23_L_2,  MANUALCTRL_SOL24_L_2, MANUALCTRL_SOL25_L_2,
								MANUALCTRL_SOL26_L_2,  MANUALCTRL_SOL27_L_2,  MANUALCTRL_SOL28_L_2,  MANUALCTRL_SOL29_L_2 ,  MANUALCTRL_SOL30_L_2,
								MANUALCTRL_SOL31_L_2, MANUALCTRL_SOL32_L_2, MANUALCTRL_SOL33_L_2,  MANUALCTRL_SOL34_L_2, MANUALCTRL_SOL35_L_2,
								MANUALCTRL_SOL36_L_2,  MANUALCTRL_SOL37_L_2,  MANUALCTRL_SOL38_L_2,  MANUALCTRL_SOL39_L_2 ,  MANUALCTRL_SOL40_L_2,
								MANUALCTRL_SOL41_L_2, MANUALCTRL_SOL42_L_2, MANUALCTRL_SOL43_L_2,  MANUALCTRL_SOL44_L_2, MANUALCTRL_SOL45_L_2
							};


int MenuSwCtrl2[MAX_MANU_SW2] = {	
								MANUALCTRL_SERVO1_JOG,  MANUALCTRL_SERVO2_JOG,  MANUALCTRL_SERVO1_1,  MANUALCTRL_SERVO1_2, MANUALCTRL_SERVO1_3,
								MANUALCTRL_SERVO2_1,  MANUALCTRL_SERVO2_2,  MANUALCTRL_SERVO2_3
							};


			

void	M_SetGraphTol(void);

int CVICALLBACK ResultView1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	ResultView11 (panel, control, event,  callbackData, eventData1, eventData2);
//	return 0;
	switch (event)
		{
		case EVENT_COMMIT:
			FileOpenFlag = MANU_DATA;
//			FileOpenFlag = AUTO_DATA;
		    SetActivePanel(dataview);
			break;
		}
	return 0;
}

int CVICALLBACK Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Save1( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int Save1(int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40] = {NULL}, FileBuff[2048] = {NULL};
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID;
	
	switch (event)
		{
		case EVENT_COMMIT:

			GetCtrlVal(panel, MANUALCTRL_C_MODE, &ModeID);

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			DateStamp[10] = '-';
			DateStamp[11] = NULL;
	
		// �ð� Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			TimeStamp[5]=NULL;
			
			strcat(TimeStamp, ".MAN");

			strcat(DateStamp, TimeStamp);
	
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
			strcpy(ManualTestDataDir, CurrModelDirectory);
			strcat(ManualTestDataDir, "\\DATA");
			if( SetDir(ManualTestDataDir) )				//	Directory�� �������� ������
			{
				MakeDir (ManualTestDataDir);			//	Directory����
				SetDir (ManualTestDataDir);				// �������� ����Ÿ ����  Directory�̵�
			}

			Status = FileSelectPopup (ManualTestDataDir, DateStamp, "*.MAN",
									  "Save Manual Test Data",
									  VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  ChangedManualTestDataDir);

			//	1  VAL_EXISTING_FILE_SELECTED
			//	2  VAL_NEW_FILE_SELECTED
       		if( Status == 1 || Status == 2 ) // file selected
       		{
				FileHandle = OpenFile (ChangedManualTestDataDir, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

                 // ���� ��¥ �� �ð� ���� ����
                 strcpy (timeStr,TimeStr());

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);

				//  Write �𵨸�
				sprintf(FileBuff,"Model   %s", ModelName[ModelID]);
				WriteLine (FileHandle, FileBuff,-1);
	
		       // ���� Point��  Write
		        sprintf(FileBuff,"Point_Num   %i", MeasPoints);   
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "NAME");  // 8
                
	        	// ���� �̸� ����
			    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
		        {
					if( strlen(Model[i].Name) > 14 )
					{
						strncpy(ctemp, Model[i].Name, 14);
						ctemp[14] = 0;
					}
					else
						strcpy(ctemp, Model[i].Name);
						
					sprintf(TimeStamp, fmt, ctemp);
			        strcat(FileBuff, TimeStamp);
		        }
 
			    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
				sprintf(TimeStamp, fmt, "Time");
				strcat(FileBuff, TimeStamp);
				
			    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
				sprintf(TimeStamp, fmt, "Operator");
				strcat(FileBuff, TimeStamp);
				
				   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "TUBE BARCODE        ");
    strcat(FileBuff, DateStamp);	// marking data

   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DateStamp, fmt, "SHAFT BARCODE       ");
    strcat(FileBuff, DateStamp);	// marking data

    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
	sprintf(DateStamp, fmt, "OK/NG");
	strcat(FileBuff, DateStamp); // 12, �ð�
				
		        WriteLine (FileHandle, FileBuff, -1); 

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "UNIT");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].Unit);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "K.TOL");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].KindOfTol);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "USL");  // 8
                
		        // Point�� USL�� ���� 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].PTol);
					strcat(FileBuff, TimeStamp);
		        } 
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "LSL");  // 8
		        // Point�� LSL�� ���� 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].NTol);
					strcat(FileBuff, TimeStamp);
		        }
		        WriteLine (FileHandle, FileBuff, -1); 

				// �ð� Data
	            sprintf(TimeStamp, "%s", timeStr);
	            CopyBytes(TimeStamp, 2, "-", 0, 1);
	            CopyBytes(TimeStamp, 5, "-", 0, 1);
	            // �۾��� �̸� 
	            GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);
	            
				// ���� ��� Data �� Information ����
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				itemp = 1;
				for(j = Mc[McID].Mode[modeid].StDataNum; j <= Mc[McID].Mode[modeid].CycleIndex; j++) // StDataNum �� 1base �̱� ������
				{
					if( j == Mc[McID].Mode[modeid].EdDataNum )
						break;
					if( j >= MAX_DATA_KEEP_CYCLE )
						j = 1; // data�� ����Ǵ� ù��° ��ġ

				    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
					sprintf(FileBuff, fmt, itemp++ );
			        for( i = 0; i < MeasPoints; i++)
					{
						    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
						sprintf(Temp, fmt, Mc[McID].Mode[modeid].FinalResult[i][j]);
						strcat(FileBuff, Temp);
					}
					
				    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
					sprintf(DataStamp,fmt, TimeStamp);
					strcat(FileBuff, DataStamp);
					
				    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DataStamp,fmt, WorkerName[WorkerID]);
					strcat(FileBuff, DataStamp);
					
					 sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DateStamp, fmt, "       ");
 				   strcat(FileBuff, DateStamp);	// marking data

				   sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DateStamp, fmt, "       ");
				    strcat(FileBuff, DateStamp);	// marking data

 				   sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
					sprintf(DateStamp, fmt, " ");
					strcat(FileBuff, DateStamp); // 12, �ð�
					
					
					WriteLine (FileHandle, FileBuff,-1);
				}
				
				CloseFile(FileHandle);
			}
// Project Directory�� ȯ��
			SetDir (PrjDirectory);
			break;
		}

	return 0;
}

int CVICALLBACK Clr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i = 0;
	
	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID); 

			i = ConfirmPopup ("RESET RESULT", "WANT TO RESET RESULT ?");
				
			if(i)								//	������� ����
			{
				Mc[0].Mode[1].CycleIndex = 0;
				Mc[0].Mode[1].StDataNum = 1;
				Mc[0].Mode[1].EdDataNum = 1;
				
				ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // �ݺ� ������ ǥ�� ����

				SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, 0);
				// Data�� ��� Clear ��, Save �Ұ���
//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
				SetManuCtrlTableMeasData( (double *)NULL); // ������ ����
			}
			break;
		}
		
	return 0;
}



// Key Board������ ���� �������� (Shift+Ctrl F6)
int CVICALLBACK ManualTestKey (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

		// MANUALCTRL_MANUALTEST_1, MANUALCTRL_MANUALTEST_2
/*
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(manualctrl, MANUALCTRL_MANUALTEST, &ManualTest);
			if(	ManualTest &&								//	�������� ���۹�ư ����
				!AmpPortOpenErr &&							//	Amp Port Open�� �����̰�
				!AmpCommErr &&							// 	Amp. ����� �����̰�
//				!PlcXY[plcSTOP_REQ] &&						//	���������� �ƴϰ�
				!DoingManualTestFlag &&						//	�������������� �ʰ�
				!DoingZeroFlag &&							//	�������� ������ �ʰ�
				!DoingTestFlag )							//	�ڵ� ���������� �ʾ�����
			{												//	��ư��� �� Ȱ��ȭ
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTESTKEY, ATTR_DIMMED, TRUE);
				ManualTestStart();							//	������������
			}
			else											//	����Ŭ ���������� �������� �ʾ�����
															//	������������ ��ư Off
			{
				SetCtrlVal(manualctrl, MANUALCTRL_MANUALTESTKEY, FALSE);
			}
				
			break;
		}
*/		
	return 0;
}
	
//	�������� ��� ���� �� ����
void	ManualTestFinish( void )
{
	int		mcid = McID;
	int		i,j,Dis_Count=0;
	double	data[MAX_POINT];
	char	ctemp[30];
	char	fmt[10];
	int		no;

//	if( GSt1Sig > Work_Sig ) 
//		return;
	
	
	GetCtrlVal(manualctrl, MANUALCTRL_RINGSLIDE, &no);
	ModeID = no+1;
	if( RealTimeFlag )
	{
		CalculateFinalResult_Real(); // ������ ���  
		M_MakeGraphData();

		M_GraphPlot();
		goto JUMP; 
	}
//	if(GSt1Sig ==4)
//	{
//		Calc_Order(1,2,1);
//		Calc_Order_L(1,2,1);
//	}

//	CalculateFinalResult_Manual(); // ������ ���
	CalculateFinalResult(); // ������ ���
	
/*	
	if(Angle_Data_Flag)
	{
		
		JSenValSave1();		
		
	}

*/	
//	if(GSt1Sig ==4)
//	{

		for(i=0;i<MAX_ACQ_CH_PER_CYCLE;i++)
		{
			for(j=0;j<ProbeIndex+1;j++)
				RepeatChVal_Sig3[i][j] = RepeatChVal[i][j];
		}
	   		 Graph_Index = RepeatChIndex;
/*
		GetCtrlIndex(manualctrl, MANUALCTRL_RING_2,&Model_LR) ;
		TurnDataGraphPlot1(GSt1Sig-1,Graph_Index, mainpanel);
		
		TurnDataGraphPlot2(GSt1Sig-1,Graph_Index, mainpanel);	
*/
		//	}
	
 
	if( GSt1Sig < Work_Sig ) 
	{

		for(j = 0; j < MAX_EQU; j++)
		{
			if(	 Pgm[j].Disp==1)
				Dis_Count++;
			if((Pgm[j].Sig ==GSt1Sig) && (Pgm[j].Disp==1) )			//	���� �������� Display�� Yes, Calc�ε� ���� ȣ��
			{
				data[0] = Mc[mcid].Mode[ModeID].FinalResult[Dis_Count-1][Mc[mcid].Mode[ModeID].EdDataNum]; // ���� EdDataNum�� �������� �ʾҴ�.
				SetTableCellVal(manualctrl, MANUALCTRL_M_MEAS_TABLE, MakePoint(MANU_MEAS_COL, Dis_Count), data[0]);
				SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, " 1stage Finish");
			}

		}
		
		return;
	}
	
	
JUMP: 
	for(i = 0; i < MeasPoints; i++ )
		data[i] = Mc[mcid].Mode[ModeID].FinalResult[i][Mc[mcid].Mode[ModeID].EdDataNum - 1];
	
	SetManuCtrlTableMeasData( data ); // data

	if( !RealTimeFlag ) // �ǽð� ������ ����
	{
				sprintf(fmt,"%%%d.%df",9,Model[ManuRepeatMeasNo].Unit);
				sprintf(ctemp, fmt , data[ManuRepeatMeasNo]);

//				sprintf(ctemp, "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, data[ManuRepeatMeasNo]);
//		sprintf(ctemp, "%9.3f",data[ManuRepeatMeasNo]);

		InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, ctemp, 0);
	
		GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
		SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);
	
		ManualOneTimeNo_1++;		//	����ȸ�� ���� : ���ο� ���� ���� ���۶����� Reset

			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
		
		//	����ȸ�� ȭ�� ǥ��
		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, Mc[mcid].Mode[ModeID].CycleIndex );

		if( !ManualCycleMode_1 ||										//	1 Cycle�����̰ų�
			ManualOneTimeNo_1 >= ManualCycleNoSet_1 )					//	����ȸ������ ���� ����������
		{																//	�����Ϸ�
				calc_out_data(pc73, 0); // �ݺ� ���� ��ȣ
//			else if(GSt1Sig==4)
//				calc_out_data(pc76, 0); // �ݺ� ���� ��ȣ

			ManualCtrlSt1Dimmed(0); // Dimmed ����
			ManualOneTimeNo_1 = 0;										//	����ȸ�� Reset : ���ο� ���� ���� ���۶����� Reset
			if(language==0)
			{
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "��������");
			}
			
			else if(language==1)
			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "MEAS. START");
			else
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "�������");
		}
		else															//	���ο� ��������Ŭ ����
			ManualTestStart(); // �ٽ� ��������: ST1

		
		if( MasterFlag ==1 && M_Gng ==1)
		{
			Zero_Master_Flag = 1;
			SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_3, 1);				//	��ȭ�鿡 �հ�ǥ��
		}
		
		if( MasterFlag ==2 && M_Gng ==1)
		{
			Check_Master_Flag = 1;
			SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_4, 1);				//	��ȭ�鿡 �հ�ǥ��
			calc_out_data(pc115, 1);
		
		}
		
		
//		if(Zero_Master_Flag && Check_Master_Flag)
		if( Check_Master_Flag)
		{
		
			SetCtrlVal( mainpanel, MAINPANEL_GNG_2, 1);				//	��ȭ�鿡 �հ�ǥ��
			SetCtrlVal( manualctrl, MANUALCTRL_M_GNG_2, 1);				//	��ȭ�鿡 �հ�ǥ��

		}		
		
		
	// ������ ���� via TCP/IP		

/*
			if(LanUseEnable)
			{
				if(SendData2TCP(McID, ModeID, Mc[McID].Mode[ModeID].EdDataNum))
					SendData2TCP2(McID, ModeID, Mc[McID].Mode[ModeID].EdDataNum);
			}

*/

		IdelStateTCP = 0;
		ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 

	}
}
	
// �������� �Ϸ��� ȭ����ȯ �� �ڵ�,����,���� �������� Control View Reset
void	ManualCtrlSt1Dimmed(char	flag)
{
	if( flag ) // Dimmed
	{
//		SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_RESULTVIEW_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLR_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL1, ATTR_DIMMED, TRUE);
///		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL2, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL3, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL4, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL5, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL6, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL7, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL8, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL9, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL10, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL11, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL12, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL13, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL14, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL15, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL16, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL17, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL18, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL19, ATTR_DIMMED, TRUE);		
		
		
		
		
		SetCtrlAttribute(manualctrl, MANUALCTRL_TOG_RUN, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, TRUE);
	}
	else
	{
//		if( !OldAmpErr )
//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_DIMMED, FALSE);
//		SetCtrlVal(manualctrl, MANUALCTRL_MANUALTEST_1, 0); // command ��ư���� ����
//		SetCtrlAttribute(manualctrl, MANUALCTRL_RESULTVIEW_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLR_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL2, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL3, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL4, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL5, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL6, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL7, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL8, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL9, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL10, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL11, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL12, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL13, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL14, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL15, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL16, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL17, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL18, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL19, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_TOG_RUN, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, FALSE);

//		if( !St1MeasIng )
//		{
//			SetCtrlAttribute(manualctrl, MANUALCTRL_POINT_RING, ATTR_DIMMED, FALSE);
//		}
	}
}

int CVICALLBACK ManualCtrl (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			ManualCtrl1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}

	return 0;
}
int ManualCtrl1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch(control)
	{
		case MANUALCTRL_CYCLENOSET_1:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualCycleNoSet_1, 0);
			break;
				
				
/*		case MANUALCTRL_ACQTIME:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualTestTime, 0);
			break;
					
		case MANUALCTRL_ACQNO:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualTestAvgNo, 0);
			break;
*/			
	}
	return 0;
}

int CVICALLBACK ManualCtrlCall (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
//	char	title[200], message[200];
//	int		keydata;
	int		i;
//	char	*title[100]; 
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;
			AmpStart(1);
			GetCtrlVal(panel, MANUALCTRL_POINT_RING, &ManuRepeatMeasNo); //	�ݺ� �������� �����ֱ� ���� ���õ� �����׸� ����.
			
			SetCtrlVal(manualctrl, MANUALCTRL_RINGSLIDE, 0);
			
			for( i = 0; i < MAX_MANU_SW; i++ )
			{
				def_in[i * 2 + plc40] = -1;
				def_in[i * 2 + 1 + plc40] = -1;
			}
			
			DispCylStatus();
/*			
			GetTableCellRangeVals(zerosetup,ZEROSETUP_DATA_JNL, MakeRect (1, SEN_NO, DISP_CH, 1), title, VAL_COLUMN_MAJOR);
			for(i = 0; i < DISP_CH ; i++)
			{ 
				SetCtrlAttribute (panel, SensorCtrl[i], ATTR_LABEL_TEXT, title[i]); 
		 	}
*/			
			break;
		case EVENT_LOST_FOCUS:
#ifndef _CVI_DEBUG_
			if( !St1MeasIng )
			{
				ActivePanel = mainpanel;
	//			AmpStart(0);
				ManualCtrlSt1Dimmed(0);
			}
#endif
			break;
		case EVENT_CLOSE:

			break;
		case EVENT_KEYPRESS:
			switch( eventData1 )
			{
				case _CF9: // ^F9, test
//					if( TestRunSet )
//						MessagePopup("Test", "�׽�Ʈ ��� ��");
//					else
//						MessagePopup("Test", "�׽�Ʈ ��� ����");
//				
//					TestRunSet = !TestRunSet;
					break;
				case _C_S: // ^S  // ST1
					SetManuCtrlTableMeasData((double	*)NULL);

					GSt1Sig = 1;


//					GSt1Sig = 1;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 1000; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	��������� ���� ��������Ÿ ����
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							if(i==2 )
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex/10.0-30);//
							else if(i==3 )
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex/10.0-30);//
							else if(i==0 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex *2.0);
							else if(i==1 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex *1.5);
//							RepeatChVal[RepeatChIndex][i] = ((double)rand() / 3000.0);
							
						}
					}
			
				JSenValSave(); // Ȯ�ο�, test
					
					RepeatChIndex = 1000;
						
						ModeID = 1;
						ManualTestFinish();
					break;
				case _C_A:
					CalcTestMode = 1;
					GSt1Sig = 2;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 1000; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	��������� ���� ��������Ÿ ����
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							if(i==2 )
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex)/10.0-30);// shaft ����
							else if(i==3 )
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex)/10.0-30);// tube ����
							else if(i==0 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex) *1.5);
							else if(i==1 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex) *1.0);
						}
					}
			
					RepeatChIndex = 1000;
				JSenValSave(); // Ȯ�ο�, test
						
						ModeID = 0;
						ManualTestFinish();

					break;					
				case	_C_Q:  // Up
		  		 	IdelStateTCP = 1; 
					LogDataFunc("REQUEST MEAS. ON", 0);
					RepeatChIndex = 0;
//						calc_out_data(pc12, 0); // ������
						calc_out_data(pc17, 0); // ������� O.K
						calc_out_data(pc18, 0); // ������� N.G

					  			EncMeasEnd = 0;	

					SetCtrlVal(manualctrl, MANUALCTRL_LED_3,TRUE);
					SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
					St1ReadIng = 1;
					MeasStart(1, 1); // Start: ON,  Sig: 1
					
				break;
				case	_C_W:  // Up

					GSt1Sig = 3;


//					GSt1Sig = 1;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 1000; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	��������� ���� ��������Ÿ ����
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							if(i==2 )
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex/10.0-30);//
							else if(i==3 )
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex/10.0-30);//
							else if(i==0 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex *2.0);
							else if(i==1 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)RepeatChIndex *1.5);
//							RepeatChVal[RepeatChIndex][i] = ((double)rand() / 3000.0);
							
						}
					}
			
				JSenValSave(); // Ȯ�ο�, test
					
					RepeatChIndex = 1000;
						
						ModeID = 1;
						ManualTestFinish();

					
				break;
	
				case	_C_D:  // ^D
				
  		 	IdelStateTCP = 1; 
			LogDataFunc("REQUEST MEAS. ON", 0);
			RepeatChIndex = 0;
	//			calc_out_data(pc12, 0); // ������
				calc_out_data(pc17, 0); // ������� O.K
				calc_out_data(pc18, 0); // ������� N.G

			  			EncMeasEnd = 0;	

			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 2); // Start: ON,  Sig: 1
				break;

				case	_C_Z:  // ^Z
 			LogDataFunc("REQUEST MEAS. OFF", 0);
			MeasStart(0, 2); // Start: OFF,  Sig: 1
			St1ReadIng = 0;

				break;
					
				
				case	_C_E:  // ^Z
//				Save_Master();
					CalcTestMode = 1;
					GSt1Sig = 4;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 1000; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	��������� ���� ��������Ÿ ����
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							if(i==2 )
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex)/10.0-30);// shaft ����
							else if(i==3 )
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex)/10.0-30);// tube ����
							else if(i==0 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex) *1.5);
							else if(i==1 )  //shaft ��
							RepeatChVal[RepeatChIndex][i] = ((double)(1000-RepeatChIndex) *1.0);
						}
					}
			
					RepeatChIndex = 1000;
				JSenValSave(); // Ȯ�ο�, test
						
						ModeID = 0;
						ManualTestFinish();
					
				
					
				break;
				
				
				case	_C_I:  // ^Z
					if(!Work_Check1)
					{
						Work_Check1 = TRUE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK1, 1);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK1, 1);
					}						
					else
					{
						Work_Check1 = FALSE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK1, 0);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK1, 0);
					}						
						
					
				break;
				case	_C_O:  // ^Z
					if(!Work_Check2)
					{
						Work_Check2 = TRUE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK2, 1);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK2, 1);
					}						
					else
					{
						Work_Check2 = FALSE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK2, 0);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK2, 0);
					}						
				break;
					
			}
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	char	ctemp[256];
//	sprintf(ctemp, "event=%d", event);
//	LogDataFunc(ctemp, 1);
	
	
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			
//			SetManuCtrlTableData();
//			MasterFlag = 0;
			
			
			calc_out_data(pc69, 1); // ���� �����䱸 ST1
//			calc_out_data(pc15, 1); // ���� �����䱸 ���ӽ�ȣ
			ManualOneTimeNo_1 = 0; // �ݺ� ����ȸ�� Ȯ�ο�
			//	������忡�� ������ �������� ȸ�� ����
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	������忡�� ������ ������� ����. 1ȸ �Ǵ� �ݺ�
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);

			ManualCtrlSt1Dimmed(1); // Dimmed ����
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc69, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}


int CVICALLBACK RepeatSel (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		modeid, i;
	char	tempStr[30];
	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &ManuRepeatMeasNo); //	�ݺ� �������� �����ֱ� ���� ���õ� �����׸� ����.

			ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2);

			modeid = Model[ManuRepeatMeasNo].ST;
			if(Mc[0].Mode[modeid].CycleIndex <= 0)
				return  0 ;	

			for( i = Mc[0].Mode[modeid].StDataNum ; i <= Mc[0].Mode[modeid].CycleIndex ; i++)
			{
				if( i == Mc[0].Mode[modeid].EdDataNum )
					break;
				if( i >= MAX_DATA_KEEP_CYCLE )
					i = 1; // data�� ����Ǵ� ù��° ��ġ

					sprintf(tempStr,  "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, Mc[0].Mode[modeid].FinalResult[ManuRepeatMeasNo][i] );		  

				InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, tempStr, 0); 
			} 

			GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
			SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);

			break;
		}
	return 0;
}

void	SetManuCtrlTableData(void)
{
	int		i, TotalRows;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/
	if( MeasPoints < 1 )	MeasPoints = 1;
	
	GetNumTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, &TotalRows);
	if( TotalRows < MeasPoints )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, TotalRows, MeasPoints - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > MeasPoints )
		DeleteTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, MeasPoints + 1, TotalRows - MeasPoints);

	for( i = 0; i < MeasPoints; i++ )
		ctemp[i] = Model[i].Name;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect (1, MANU_NAME_COL, MeasPoints, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
/*	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].Comp;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, M_I_VALUE, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
*/	
	
	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
		MakeRect(1, MANU_NTOL_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
	
							
	/*
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
							
	*/
	for( i = 0; i < MeasPoints; i++ )
	{
			SetTableCellRangeAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
	}
	
/////////////// CH VALUE DISPLAY
	GetNumTableRows (manualctrl, MANUALCTRL_M_CHVALUE, &TotalRows);
	if( TotalRows < ProbeIndex )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_CHVALUE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_CHVALUE, TotalRows, ProbeIndex - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > ProbeIndex )
		DeleteTableRows (manualctrl, MANUALCTRL_M_CHVALUE, ProbeIndex + 1, TotalRows - ProbeIndex);


	for( i = 0; i < ProbeIndex; i++ )
	{
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_USE_LABEL_TEXT, TRUE);
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_LABEL_TEXT, ctemp);
        SetTableCellVal (manualctrl, MANUALCTRL_M_CHVALUE, MakePoint(1, i + 1), ChNo[i].Name);//ctemp );
/*
		if( ChNo[idx].no == (i + 1) )
        {
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ChNo[idx].Name );
        	idx++;
        }
        else
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ctemp );
*/
	}
	
	
	
	

}
void	SetManuCtrlTableData2(void)
{
	int		i, TotalRows;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/
	if( MeasPoints < 1 )	MeasPoints = 1;
	
	GetNumTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, &TotalRows);
	if( TotalRows < MeasPoints )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, TotalRows, MeasPoints - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > MeasPoints )
		DeleteTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, MeasPoints + 1, TotalRows - MeasPoints);

	for( i = 0; i < MeasPoints; i++ )
		ctemp[i] = Model[i].Name;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect (1, MANU_NAME_COL, MeasPoints, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NMTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PMTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
		MakeRect(1, MANU_NTOL_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
	
							
	/*
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
							
	*/
	for( i = 0; i < MeasPoints; i++ )
	{
			SetTableCellRangeAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
	}

}

void	SetManuCtrlTableData3(void)
{
	int		i, TotalRows;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/
	if( MeasPoints < 1 )	MeasPoints = 1;
	
	GetNumTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, &TotalRows);
	if( TotalRows < MeasPoints )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, TotalRows, MeasPoints - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > MeasPoints )
		DeleteTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, MeasPoints + 1, TotalRows - MeasPoints);

	for( i = 0; i < MeasPoints; i++ )
		ctemp[i] = Model[i].Name;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect (1, MANU_NAME_COL, MeasPoints, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NM2Tol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PM2Tol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
		MakeRect(1, MANU_NTOL_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
	
							
	/*
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
							
	*/
	for( i = 0; i < MeasPoints; i++ )
	{
			SetTableCellRangeAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
	}

}


void	SetManuCtrlTableMeasData(double	*data)
{
	int		i;
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/

	/////// Rect MakeRect (int top, int left, int height, int width);

	if( data == NULL )
	{
		for( i = 0; i < MeasPoints; i++)
			dtemp[i] = 0.0;
		SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
								MakeRect(1, MANU_MEAS_COL, MeasPoints, 1),
								dtemp, VAL_COLUMN_MAJOR);
		SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
						MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_COLOR, VAL_BLACK);
	}
	else
	{
		if( RealTimeFlag )
		{
			SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_COLOR, VAL_BLACK);
			SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
		}
		
			SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1),
							data, VAL_COLUMN_MAJOR);

		if( !RealTimeFlag )
		{

			M_Gng = 1;		 	

			for( i = 0; i < MeasPoints; i++)
			{
				if(!MasterFlag)
				{
					if( data[i] > Model[i].PTol || data[i] < Model[i].NTol )
					{
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_RED);
						M_Gng = 0;		 	

					}
					else
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_BLACK);
				}
				else  if(MasterFlag==1)
				{
					if( data[i] > Model[i].PMTol || data[i] < Model[i].NMTol )
					{
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_RED);
						M_Gng = 0;		 	

					}
					else
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_BLACK);
					
					
				}
				else  if(MasterFlag==2)
				{
					if( data[i] > Model[i].PM2Tol || data[i] < Model[i].NM2Tol )
					{
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_RED);
						M_Gng = 0;		 	

					}
					else
						SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
										MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_BLACK);
					
					
				}
			
			
			}
				
		}		
	}





/*
	if(Mc[0].Mode[0].FinalResult[i][TestDataIndex] < Model[i].NTol)
	{
		GFlag[i] = FALSE;	// ���հ�
		TotalGFlag = FALSE;	// ��� ���� Point�� ���Ͽ� �� Point�� �ҷ��̸� Reset
		return;
	}
	else if(Mc[0].Mode[0].FinalResult[i][TestDataIndex] > Model[i].PTol)

	for(i = 0; i < DISP_CH; i++)
	{
//	�������� ��� �˻�(Zero Setup Panel�� ������)
		if( ZeroDiff1[i] < ZeroNTol1[i] )
		{
			ZeroNLimitErrFlag = TRUE;
			ZeroNLimitErrCounter++;
		}
		else	ZeroNLimitErrFlag = FALSE ;

		if( ZeroDiff1[i] > ZeroPTol1[i])
		{
			ZeroPLimitErrFlag = TRUE;
			ZeroPLimitErrCounter++;
		}
		else	ZeroPLimitErrFlag=FALSE ;
		
//	�������� ������  �����, ���Ŀ� ���� ������ ȭ�鿡 ǥ��
		if( ZeroNLimitErrFlag || ZeroPLimitErrFlag )
			SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
							MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_RED);
		else
			SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
							MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_BLUE);
	}
*/


}

//	�������� ����
void	ManualTestStart( void )
{
	ManualCtrlSt1Dimmed(1);

	RepeatChIndex = 0;
		
	// �����ð� ����
//	GetCtrlVal(syssetup, SYSSETUP_STARTDELAY, &StartDelay);
//	SleepFunc( StartDelay * 1000 ); // Delay(StartDelay);

	//	���� ������ Read
//	GetCtrlVal(manualctrl, MANUALCTRL_ACQNO, &ManualTestAvgNo);
//	GetCtrlVal(manualctrl, MANUALCTRL_ACQTIME, &ManualTestTime);
	//	������ �������� �������� ����			
//	GetStopMode();
}


int CVICALLBACK ManuSwCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, flag;


	switch (event)
		{
		case EVENT_COMMIT:
//			MessagePopup("test", "event test"); // test
			ServoBtnAllOff();
			
			GetCtrlVal(manualctrl, control, &flag);
			
			for( i = 0; i < MAX_MANU_SW; i++ )
			{
			
//				if((i==4)&& (MenuSwCtrl[4] == control))
//				{
//					SetCtrlVal (manualctrl, MANUALCTRL_MSG_TEST, "0");
//					
//					calc_out_data(pc15, 0); // pc20 + i
//				
//				}
				if( MenuSwCtrl[i] == control )
					calc_out_data(MENU_SW_ST + i, flag); // pc20 + i
				else
				{
					calc_out_data(MENU_SW_ST + i, 0);
					SetCtrlVal(manualctrl, MenuSwCtrl[i], 0);
				}
			 
			
			
			}
			break;
		}
	return 0;
}

int CVICALLBACK MeasTabelCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	int			top, left, leftbtn, rightbtn, key;
	int			modeid, i;
	char		tempStr[20], fmt[10];

	modeid = ModeID;
	
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			if( St1MeasIng )
				return 0;

			GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

			if( (cell.y - 1) == ManuRepeatMeasNo )
				return 0; // ���� ǥ�õǰ� �ִ� �����׸�
			if( (cell.y - 1) < 0 ) // ������ �߸��Ȱ�.
				return 0;
				
			ManuRepeatMeasNo = cell.y - 1;
//			GetCtrlVal(panel, MANUALCTRL_POINT_RING, &ManuRepeatMeasNo); //	�ݺ� �������� �����ֱ� ���� ���õ� �����׸� ����.
			SetCtrlVal(manualctrl, MANUALCTRL_POINT_RING, ManuRepeatMeasNo); //	�ݺ� �������� �����ֱ� ���� ���õ� �����׸� ����.

			ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2);

			if(Mc[McID].Mode[modeid].CycleIndex <= 0)
				return  0 ;	

			for( i = Mc[McID].Mode[modeid].StDataNum ; i <= Mc[McID].Mode[modeid].CycleIndex ; i++)
			{
				if( i == Mc[McID].Mode[modeid].EdDataNum )
					break;
				if( i >= MAX_DATA_KEEP_CYCLE )
					i = 1; // data�� ����Ǵ� ù��° ��ġ

				sprintf(fmt,"%%%d.%df",9,Model[ManuRepeatMeasNo].Unit);
				sprintf(tempStr, fmt , Mc[McID].Mode[modeid].FinalResult[ManuRepeatMeasNo][i]);

//				sprintf(tempStr, "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, Mc[0].Mode[modeid].FinalResult[ManuRepeatMeasNo][i] );		  

				InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, tempStr, 0); 
			} 

			GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
			if(i> 0)
				SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);
			M_SetGraphTol();

			
			break;
		case EVENT_COMMIT:
			break;
		}
	return 0;
}

int test_count=0;

int CVICALLBACK ManuSwCallback1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
				
			
			break;
		}
	return 0;
}

int CVICALLBACK Tog_Run (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		Tog;
	
	switch (event)
		{
		case EVENT_COMMIT:
			 	GetCtrlVal (manualctrl, MANUALCTRL_TOG_RUN, &Tog);

			/*	if(Tog)
					calc_out_data(pc99, 1); 
				else	
					calc_out_data(pc99, 0); */
					
			break;
		}
	return 0;
}

int CVICALLBACK Mode_Select (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int		index_count;
	
	switch (event)
		{
		case EVENT_VAL_CHANGED:
		    
		    GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID);
//			GetCtrlIndex(manualctrl,MANUALCTRL_LISTBOX_2,&index_count);
		    
		    if(ModeID==1)
		    {
				calc_out_data(pc45,1);			// PLC�� �������� ��� ����
				calc_out_data(pc46,0);		    // PLC�� R&R ���� ��� Reset
				calc_out_data(pc47,0);			// PLC�� ������ ��� Reset
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, DISABLE);
		    	
	//	    	if(index_count)
   	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		    }
		    else if(ModeID==2)
		    {
				calc_out_data(pc45,0);			// PLC�� �������� ��� ����
				calc_out_data(pc46,1);		    // PLC�� R&R ���� ��� Reset
				calc_out_data(pc47,0);			// PLC�� ������ ��� Reset
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, 4);    	
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, ENABLE);
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, 1);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, ENABLE);
		    	
//		    	if(index_count)
  // 					SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		
		    }
		    else if(ModeID==3)
		    {
				calc_out_data(pc45,0);			// PLC�� �������� ��� ����
				calc_out_data(pc46,0);		    // PLC�� R&R ���� ��� Reset
				calc_out_data(pc47,1);			// PLC�� ������ ��� Reset
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, 1); 
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, ENABLE);
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, 0); 
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, ENABLE);

	//	    	if(index_count)
   	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		
		    }

			break;
		}
	return 0;
}

int CVICALLBACK M_Meas_Mode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK M_Select_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i, j;
	
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlVal(panel, control, &i);
		   if(i==1)
		   {
				SetCtrlAttribute(panel, MANUALCTRL_DECO_1, ATTR_TOP, 60);
				SetCtrlAttribute(panel, MANUALCTRL_GRAPH1, ATTR_TOP, 70); //MenuSwCtrl  MenuSwLampCtrl
				
				for(j=0;j<MAX_MANU_SW;j++)
				{
			  		SetCtrlAttribute (panel, MenuSwCtrl[j], ATTR_VISIBLE, 0);
			  		SetCtrlAttribute (panel, MenuSwLampCtrl[j], ATTR_VISIBLE, 0);
				}
		   }
		   else
		   {
				SetCtrlAttribute(panel, MANUALCTRL_DECO_1, ATTR_TOP, 800);
				SetCtrlAttribute(panel, MANUALCTRL_GRAPH1, ATTR_TOP, 800);

				for(j=0;j<MAX_MANU_SW;j++)
				{
			  		SetCtrlAttribute (panel, MenuSwCtrl[j], ATTR_VISIBLE, 1);
			  		SetCtrlAttribute (panel, MenuSwLampCtrl[j], ATTR_VISIBLE, 1);
				}
		   }
			   
	
			break;
	}
	return 0;
}

int CVICALLBACK RealTimeMeas (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(manualctrl, MANUALCTRL_REALTIMEMEAS, &RealTimeFlag);
			if( RealTimeFlag ) // ���������̸�
			{
				ManualCtrlSt1Dimmed(1);
				SetCtrlVal(panel, MANUALCTRL_CYCLEMODE_1, 0);
			}
			else
			{
				ManualCtrlSt1Dimmed(0);
				Mc[0].Mode[1].CycleIndex = 0;
				Mc[0].Mode[1].StDataNum = 1;
				Mc[0].Mode[1].EdDataNum = 1;
				
//				MeasValueCls();
				ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // �ݺ� ������ ǥ�� ����
				SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, 0);
			}			break;
		}
	return 0;
}
  void		M_MakeGraphData(void)
{
	int	i;


		if( GraphData4.DataNum >= MAX_PLOT_NUM ) // Data full
		{
			GraphData4.DataNum = MAX_PLOT_NUM;
			for(i = 0; i < MeasPoints; i++ )
			{
	//			for(j = 0; j < (MAX_PLOT_NUM - 1); j++ )
	//				GraphData.Data[i][j] = GraphData.Data[i][j + 1];
				memmove(&GraphData4.Data[i][0], &GraphData4.Data[i][1], (GraphData4.DataNum - 1) * sizeof(double) );
				GraphData4.Data[i][MAX_PLOT_NUM - 1] = Mc[McID].Mode[1].FinalResult[i][Mc[McID].Mode[1].EdDataNum - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData4.Data[i][GraphData4.DataNum] = Mc[McID].Mode[1].FinalResult[i][Mc[McID].Mode[1].EdDataNum - 1];
	//		GraphData.DataNum = Mc[0].Mode[0].CycleIndex;
			GraphData4.DataNum++;
		}
	

}

//	�׷����� �׸� �׸���
void		M_GraphPlot(void)
{
	int		OldHandleData = 0;
	int		i,j;
	//double	N20;//, P20;
	double	Cen;

	
	if( GraphData4.HandleData != 0 )
		OldHandleData = GraphData4.HandleData;
	else
	{
			DeleteGraphPlot(manualctrl, MANUALCTRL_GRAPH1, -1, VAL_IMMEDIATE_DRAW);
			
			GraphData4.HandleNTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.NTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

			GraphData4.HandlePTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.PTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
										
										
			GraphData4.HandleNCTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.NCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
										
			GraphData4.HandlePCTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.PCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);										


	//	N20 = (*GraphData.PTol-*GraphData.NTol)*UclLcl/100.;
		Cen = (*GraphData4.PTol-*GraphData4.NTol)*50./100.;

//		N20 = MC_Grade[SPCDisplayPointNo][1];
//		P20 = MC_Grade[SPCDisplayPointNo][2];
	
	
		for(j=0;j<MAX_PLOT_NUM ;j++)
		{
		//	PTol20[j] = *GraphData.PTol-N20;
		//	NTol20[j] = *GraphData.NTol+N20;
			Center_Point[j] = *GraphData4.NTol+Cen;
		}	
	
	//	sprintf(temp,"%f %f",PTol20,NTol20);
	//	MessagePopup("",temp);
			/*
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, PTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			i = PlotY(mainpanel, MAINPANEL_GRAPH1, NTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			*/
			i = PlotY(manualctrl, MANUALCTRL_GRAPH1, Center_Point, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_CYAN);

	}


//		SetCtrlVal(mainpanel, MAINPANEL_UCL, *GraphData4.PCTol);
//		SetCtrlVal(mainpanel, MAINPANEL_LCL, *GraphData4.NCTol);
		
//		SetCtrlVal(mainpanel, MAINPANEL_USL, *GraphData4.PTol);
//		SetCtrlVal(mainpanel, MAINPANEL_LSL, *GraphData4.NTol);
//		SetCtrlVal(mainpanel, MAINPANEL_MEAS_POINT, Model[SPCDisplayPointNo].Name);

		
		for(i = 0; i < MeasPoints; i++ )
			GraphData4.Data[i][0] = Center_Point[i];

	if( GraphData4.DataNum < 1 )		GraphData4.DataNum = 1;
	GraphData4.HandleData = PlotY(manualctrl, MANUALCTRL_GRAPH1, &GraphData4.Data[ManuRepeatMeasNo], GraphData4.DataNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
	
	if( OldHandleData != 0 ) // AutoScale ������ ���ߴ� ���� ����
		DeleteGraphPlot(manualctrl, MANUALCTRL_GRAPH1, OldHandleData, VAL_IMMEDIATE_DRAW); // ������ ���ΰ� �����͸� ����

//	}
//	else if(McID == 1)
//	{
	

}
 void	M_SetGraphTol(void)
{
	int		i;
	

	GraphData4.HandleData = 0;
	GraphData4.HandleNTol = 0;
	GraphData4.HandlePTol = 0;

 	GraphData4.HandleNCTol = 0;
	GraphData4.HandlePCTol = 0;
	
	for(i = 0; i < MAX_PLOT_NUM; i++ )
	{

		GraphData4.NTol[i] = Model[ManuRepeatMeasNo].NTol;
		GraphData4.PTol[i] = Model[ManuRepeatMeasNo].PTol;
		GraphData4.NCTol[i] = Model[ManuRepeatMeasNo].NCTol;
		GraphData4.PCTol[i] = Model[ManuRepeatMeasNo].PCTol;
		
	}
	
}

int CVICALLBACK TestTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int i;
	int		i, j;//, j, l, CH_count; //, EventPanel, EventCtrl;
	double	dtemp[MAX_POINT];
	
	switch (event)
	{
		case EVENT_TIMER_TICK:

		if( (ActivePanel == manualctrl) && AmpRunFlag )// && !St1CalcIng ) // �������� ȭ���̰� �������� �ƴϸ�
		{
	
			for( i = 0; i < ProbeIndex; i++ )
				dtemp[i] = ChData[ChNo[i].no - 1];
			SetTableCellRangeVals(manualctrl, MANUALCTRL_M_CHVALUE,
									MakeRect(1, 2, ProbeIndex, 1),
									dtemp, VAL_COLUMN_MAJOR);
			
		}

			break;
	}
	return 0;
}

int CVICALLBACK ManualMeasSw1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			
/*
			SetCtrlAttribute (manualctrl, MANUALCTRL_M_VIEW, ATTR_ZPLANE_POSITION,0 );

			SetCtrlAttribute (manualctrl, MANUALCTRL_MANUALTEST_M, ATTR_ZPLANE_POSITION,0 );
			SetCtrlAttribute (manualctrl, MANUALCTRL_MANUALTEST_M_2, ATTR_ZPLANE_POSITION,0 );
			SetCtrlAttribute (manualctrl, MANUALCTRL_M_GNG_3, ATTR_ZPLANE_POSITION,0 );
			SetCtrlAttribute (manualctrl, MANUALCTRL_M_GNG_4, ATTR_ZPLANE_POSITION,0 );
			SetCtrlAttribute (manualctrl, MANUALCTRL_WORK_NAME2, ATTR_ZPLANE_POSITION,0 );

*/			
			 			SetManuCtrlTableData2();
			MasterFlag = 1;

			calc_out_data(pc79, 1); // ���� �����䱸 ST1

/*			
			ManualOneTimeNo_1 = 0; // �ݺ� ����ȸ�� Ȯ�ο�
			//	������忡�� ������ �������� ȸ�� ����
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	������忡�� ������ ������� ����. 1ȸ �Ǵ� �ݺ�
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed ����
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc79, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			

			SetManuCtrlTableData3();
			MasterFlag = 2;

			calc_out_data(pc70, 1); // ���� �����䱸 ST1

/*			
			ManualOneTimeNo_1 = 0; // �ݺ� ����ȸ�� Ȯ�ο�
			//	������忡�� ������ �������� ȸ�� ����
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	������忡�� ������ ������� ����. 1ȸ �Ǵ� �ݺ�
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed ����
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc70, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int ActionBtnAllOff(void)  
{
	int i;
	
	for( i = 0; i < MAX_MANU_SW; i++ )
	{
		calc_out_data(MENU_SW_ST + i, 0);
		SetCtrlAttribute(manualctrl, MenuSwCtrl[i], ATTR_CTRL_VAL, 0);
	}
	return 0;
}
int ServoBtnAllOff(void)  
{
	int i;
	
	for( i = 0; i < MAX_MANU_SW2; i++ )
	{
		calc_out_data(MENU_SW_ST2 + i, 0);
		SetCtrlAttribute(manualctrl, MenuSwCtrl2[i], ATTR_CTRL_VAL, 0);
	}
	return 0;
}

int CVICALLBACK ServoSwCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, flag;

	switch (event)
		{
		case EVENT_COMMIT:

			
			 ActionBtnAllOff();
		 
	
			GetCtrlVal(manualctrl, control, &flag);
			
			for( i = 0; i < MAX_MANU_SW2; i++ )
			{
			
				if( MenuSwCtrl2[i] == control )
					calc_out_data(MENU_SW_ST2 + i, flag); 
				else
				{
					calc_out_data(MENU_SW_ST2 + i, 0);
					SetCtrlVal(manualctrl, MenuSwCtrl2[i], 0);
				}
			 
			
			
			}
			break;
		}
	return 0;
	
	
}

int CVICALLBACK Servo_Home (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
//			calc_out_data(pc67, 1); // ���� �����䱸 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc67, 0); // ���� �����䱸 ST1
			break;
		}
	return 0;
}

int CVICALLBACK Action_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 73);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 85);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 436);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 315);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 187);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 316);
			
			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 1102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 1131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 1171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 1129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 1280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 1280);

			break;
	}
	return 0;
}

int CVICALLBACK Action_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 1100);

			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 1102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 1131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 1171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 1129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 1280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 1280);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK Action_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 73);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 1100);
			
			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 280);
			
			
			

			break;
	}
	return 0;
}

int CVICALLBACK CycleMode_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int	no;
	
	switch (event)
	{
		case EVENT_COMMIT:
				
			
			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  char	mark_data[100];

  switch (event)
	{
		case EVENT_COMMIT:
//            GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);

			   sprintf(mark_data,"[)>%%030A06%%029A");
			   MessagePopup("test",mark_data);
//		SendDataAUX2(1,mark_data);

			   
//			   TestData2TCP(0,0, mark_data);

			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  char	mark_data[100];

  switch (event)
	{
		case EVENT_COMMIT:
			

			BarCode_Printing_M( (char *)NULL ); // �հ��� ���� ���ڵ带 ������ �Ѵ�.

           GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, BAR_DATA);
           SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);

		   GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_5, BAR_DATA);
           SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_7, BAR_DATA);
 //          SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);

			   sprintf(mark_data,"C2,000%d,001,%s",ModelID+1,BAR_DATA);
		   
			   TestData2TCP(0,0, mark_data);
//		   SendDataAUX1(0, mark_data);
			break;
	}
	return 0;
}

int CVICALLBACK Pos_Select2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT2, &i);
		calc_out_data(pc82, 0); 
		calc_out_data(pc83, 0); 
		calc_out_data(pc84, 0); 
		calc_out_data(pc85, 0); 
		if(i==0)
			calc_out_data(pc82, 1); 
		else if(i==1)
			calc_out_data(pc83, 1); 
		else if(i==2)
			calc_out_data(pc84, 1); 
		else if(i==3)
			calc_out_data(pc85, 1); 

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc86, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc86, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			i = ConfirmPopup ("���� ����", "��ġ DATA�� �����ϰڽ��ϱ�?");

			if(i)								//	����
			{
				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT2, &j);
				GetCtrlVal(manualctrl, MANUALCTRL_TRANS_SERVO, &data);
				if(j==0)
					Servo_Position[0] = data;
				else
					Servo_Position[1] = data;
				calc_out_data(pc85, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc85, 0); // ���� �����䱸 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK Servo_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			i = ConfirmPopup ("DATA ����", "��ġ DATA�� �����ϰڽ��ϱ�?");

			if(i)								//	����
			{
//				calc_out_data(pc86, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc86, 0); // ���� �����䱸 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Jog_Vel2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	JogVel;
	
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(manualctrl, MANUALCTRL_JOG_VEL2, &JogVel);


			break;
	}
	return 0;
}

int CVICALLBACK Act_Bt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc78, 1); // ���� �����䱸 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc78, 0); // ���� �����䱸 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Home_Bt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
//			calc_out_data(pc79, 1); // ���� �����䱸 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc79, 0); // ���� �����䱸 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Pos_Select3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

		for(i=0;i<7;i++)
			calc_out_data(pc88+i, 0); 

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT3, &i);
			calc_out_data(pc88+i, 1); 
		

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc95, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc95, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i,j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 

				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT3, &j);
				if(j==0)
					break;
				

			i = ConfirmPopup ("���� ����", "��ġ DATA�� �����ϰڽ��ϱ�?");

			if(i)								//	����
			{
				
				GetCtrlVal(manualctrl, MANUALCTRL_MARK_SERVO, &data);
					Servo_Position[2] = data;
				
				calc_out_data(pc89, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc89, 0); // ���� �����䱸 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK Pos_Select4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

		for(i=0;i<14;i++)
			calc_out_data(pc97+i, 0); 

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT4, &i);

			calc_out_data(pc97+i, 1); 

			

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc111, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc111, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT4, &j);
				if(j==0)
					break;

			i = ConfirmPopup ("���� ����", "��ġ DATA�� �����ϰڽ��ϱ�?");

			if(i)								//	����
			{
				GetCtrlVal(manualctrl, MANUALCTRL_MEAS_SERVO, &data);
					Servo_Position[3] = data;

					calc_out_data(pc93, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc93, 0); // ���� �����䱸 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK ManualMeasSw3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc71, 1); // ���� �����䱸 ST1

/*			
			ManualOneTimeNo_1 = 0; // �ݺ� ����ȸ�� Ȯ�ο�
			//	������忡�� ������ �������� ȸ�� ����
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	������忡�� ������ ������� ����. 1ȸ �Ǵ� �ݺ�
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed ����
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc71, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc72, 1); // ���� �����䱸 ST1

/*			
			ManualOneTimeNo_1 = 0; // �ݺ� ����ȸ�� Ȯ�ο�
			//	������忡�� ������ �������� ȸ�� ����
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	������忡�� ������ ������� ����. 1ȸ �Ǵ� �ݺ�
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed ����
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc72, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}


void  ServoDataRead(void)
{
	int		i, j;
	unsigned	long bPos;
unsigned  long	Angle;
	char    temp[10], temp1[100], temp2[10], temp3[10];
	
	Angle = 0;
	
	bPos = 1;
	for( i = 0; i < 16; i++ )
	{
		if( d_in[plc200 + i] )
			Angle |= bPos;
		bPos <<= 1;
	}
	
	ChData[2] =  50.0-(double)Angle/100.0;
	
	Angle = 0;
	
	bPos = 1;
	for( i = 0; i < 16; i++ )
	{
		if( d_in[plc216 + i] )
			Angle |= bPos;
		bPos <<= 1;
	}
	
	ChData[3] =   50.0-(double)Angle/100.0;

	if(!Auto_1cycleFlag)
	{
	
		temp1[0]=0;
		sprintf(temp2,"%c", 0x0D);
		sprintf(temp3,"%c", 0x0A);
	
		for(j=0;j<20;j++)
		{
			Angle = 0;
	
			bPos = 1;

			for( i = 0; i < 8; i++ )
			{
				if( d_in[plc320+j*8 + i] )
					Angle |= bPos;
				bPos <<= 1;
			}
			sprintf(temp,"%c", Angle);
		
			if(strcmp(temp,temp2))
			{
				if(strcmp(temp,temp3))
					strcat(temp1,temp);
			}
		}	
	
	
	
		SetCtrlVal(mainpanel, MAINPANEL_B1,temp1);
	

		temp1[0]=0;
		for(j=0;j<20;j++)
		{
			Angle = 0;
	
			bPos = 1;

			for( i = 0; i < 8; i++ )
			{
				if( d_in[plc480+j*8 + i] )
					Angle |= bPos;
				bPos <<= 1;
			}
			sprintf(temp,"%c", Angle);

			if(strcmp(temp,temp2))
			{
				if(strcmp(temp,temp3))
					strcat(temp1,temp);
			}
		}	
			SetCtrlVal(mainpanel, MAINPANEL_B2,temp1);
	}	
	
}



void  ServoDataSend(int no)
{
	int		i;
	unsigned	long bPos;
	unsigned	long data;
/*
		data = Servo_Position[no];;
		
		
		bPos = 1;
		for( i = 0; i < 32; i++ )
		{
			if( data & bPos )
				calc_out_data(pc120 + i, SET);
			else
				calc_out_data(pc120 + i, RESET);
			bPos <<= 1;
		}

		calc_out_data(pc95+no, 1);
*/	
}


int CVICALLBACK ByPass5 (int panel, int control, int event,
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

int CVICALLBACK Servo_All_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double pos;
	switch (event)
	{
		case EVENT_COMMIT:

//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_1,&Servo_Position[0]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_2,&Servo_Position[1]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_3,&Servo_Position[2]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_4,&Servo_Position[3]);

//				calc_out_data(pc94, 1); // ���� data �о��

			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	mark_data[100];
	switch (event)
	{
		case EVENT_COMMIT:

			sprintf(mark_data,"CO,0,3000");  	
 			   TestData2TCP(0,0, mark_data);

// 		   SendDataAUX1(1, "TEST");

			break;
	}
	return 0;
}
void	Save_Master(void)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40] = {NULL}, FileBuff[2048] = {NULL};
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID;
	
			GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID);

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			DateStamp[10] = '-';
			DateStamp[11] = NULL;
	
		// �ð� Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			TimeStamp[5]=NULL;
			
			strcat(TimeStamp, ".LMT");

			strcat(DateStamp, TimeStamp);
	
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
			strcpy(ManualTestDataDir, CurrModelDirectory);
			strcat(ManualTestDataDir, "\\DATA");
		
			
			if( SetDir(ManualTestDataDir) )				//	Directory�� �������� ������
			{
				MakeDir (ManualTestDataDir);			//	Directory����
				SetDir (ManualTestDataDir);				// �������� ����Ÿ ����  Directory�̵�
			}

			strcat(ManualTestDataDir, "\\");
 			strcat(ManualTestDataDir, DateStamp);

			strcpy(ChangedManualTestDataDir, ManualTestDataDir);
			FileHandle = OpenFile (ChangedManualTestDataDir, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

                 // ���� ��¥ �� �ð� ���� ����
                 strcpy (timeStr,TimeStr());

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);

				//  Write �𵨸�
				sprintf(FileBuff,"Model   %s", ModelName[ModelID]);
				WriteLine (FileHandle, FileBuff,-1);
	
		       // ���� Point��  Write
		        sprintf(FileBuff,"Point_Num   %i", MeasPoints);   
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "NAME");  // 8
                
	        	// ���� �̸� ����
			    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
		        {
					if( strlen(Model[i].Name) > 14 )
					{
						strncpy(ctemp, Model[i].Name, 14);
						ctemp[14] = 0;
					}
					else
						strcpy(ctemp, Model[i].Name);
						
					sprintf(TimeStamp, fmt, ctemp);
			        strcat(FileBuff, TimeStamp);
		        }
 
			    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
				sprintf(TimeStamp, fmt, "Time");
				strcat(FileBuff, TimeStamp);
				
			    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
				sprintf(TimeStamp, fmt, "Operator");
				strcat(FileBuff, TimeStamp);
				
		        WriteLine (FileHandle, FileBuff, -1); 

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "UNIT");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].Unit);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "K.TOL");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].KindOfTol);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "USL");  // 8
                
		        // Point�� USL�� ���� 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].PTol);
					strcat(FileBuff, TimeStamp);
		        } 
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "LSL");  // 8
		        // Point�� LSL�� ���� 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].NTol);
					strcat(FileBuff, TimeStamp);
		        }
		        WriteLine (FileHandle, FileBuff, -1); 

				// �ð� Data
	            sprintf(TimeStamp, "%s", timeStr);
	            CopyBytes(TimeStamp, 2, "-", 0, 1);
	            CopyBytes(TimeStamp, 5, "-", 0, 1);
	            // �۾��� �̸� 
	            GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);
	            
				// ���� ��� Data �� Information ����
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				itemp = 1;
				for(j = Mc[McID].Mode[modeid].StDataNum; j <= Mc[McID].Mode[modeid].CycleIndex; j++) // StDataNum �� 1base �̱� ������
				{
					if( j == Mc[McID].Mode[modeid].EdDataNum )
						break;
					if( j >= MAX_DATA_KEEP_CYCLE )
						j = 1; // data�� ����Ǵ� ù��° ��ġ

				    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
					sprintf(FileBuff, fmt, itemp++ );
			        for( i = 0; i < MeasPoints; i++)
					{
						    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
						sprintf(Temp, fmt, Mc[McID].Mode[modeid].FinalResult[i][j]);
						strcat(FileBuff, Temp);
					}
					
				    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
					sprintf(DataStamp,fmt, TimeStamp);
					strcat(FileBuff, DataStamp);
					
				    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DataStamp,fmt, WorkerName[WorkerID]);
					strcat(FileBuff, DataStamp);
					
					WriteLine (FileHandle, FileBuff,-1);
				}
				
				CloseFile(FileHandle);
			SetDir (PrjDirectory);
			
				Mc[0].Mode[1].CycleIndex = 0;
				Mc[0].Mode[1].StDataNum = 1;
				Mc[0].Mode[1].EdDataNum = 1;
				
				ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // �ݺ� ������ ǥ�� ����

				SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, 0);
				// Data�� ��� Clear ��, Save �Ұ���
//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
				SetManuCtrlTableMeasData( (double *)NULL); // ������ ����
			
			
			

}

int CVICALLBACK Manual_Printing4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  char	mark_data[100];

  switch (event)
	{
		case EVENT_COMMIT:
//            GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);

			   sprintf(mark_data,"C2,000%d,003,%s",ModelID+1,Model_Char[1]);
		   
				   TestData2TCP(0,0, mark_data);
//	   SendDataAUX1(0, mark_data);

			
//			GetCtrlVal(panel, MANUALCTRL_MANU_BARCODE_DATA, BAR_DATA);

	//		SendDataAUX1(0, BAR_DATA);	

			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  char	mark_data[100];

  switch (event)
	{
		case EVENT_COMMIT:
//            GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, BAR_DATA);

			   sprintf(mark_data,"C2,000%d,003,%08d",ModelID+1,Ok_cnt);
			   TestData2TCP(0,0, mark_data);
		   
//		   SendDataAUX1(0, mark_data);

			
//			GetCtrlVal(panel, MANUALCTRL_MANU_BARCODE_DATA, BAR_DATA);

	//		SendDataAUX1(0, BAR_DATA);	

			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	 char	mark_data[100];

	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			
//			SetManuCtrlTableData();
//			MasterFlag = 0;

			
			
			
			calc_out_data(pc71, 1); // ���� �����䱸 ST1
//			calc_out_data(pc15, 1); // ���� �����䱸 ���ӽ�ȣ
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc71, 0); // ���� �����䱸 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}
