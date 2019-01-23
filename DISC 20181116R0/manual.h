/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2018. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MANUALCTRL                       1       /* callback function: ManualCtrlCall */
#define  MANUALCTRL_DECO_9                2       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECO_8                3       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECO_7                4       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SERVO2_POS            5       /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO1_POS            6       /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_JOG            7       /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_T_MSG_2               8       /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SERVO2_3              9       /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO2_2              10      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LMIN                  11      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_1              12      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LMAX                  13      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_HOME            14      /* control type: command, callback function: Servo_Home */
#define  MANUALCTRL_SERVO1_JOG            15      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LXBAR                 16      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_T_MSG_1               17      /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SERVO1_3              18      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_2              19      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_1              20      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SOL7_2                21      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_2                22      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL5_2                23      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL4_2                24      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL3_2                25      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL2_2                26      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL1_2                27      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_L_2              28      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL7_L_2              29      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL4_L_2              30      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL5_L_2              31      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL3_L_2              32      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL2_L_2              33      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL1_L_2              34      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_2               35      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL60_2               36      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_2               37      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_2               38      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_2               39      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_2               40      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_MARK_SET2             41      /* control type: command, callback function: Mark_Set2 */
#define  MANUALCTRL_SOL55_2               42      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_2               43      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_2               44      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_2               45      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_2               46      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL50_2               47      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL49_2               48      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL48_2               49      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL47_2               50      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL46_2               51      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_2               52      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_2               53      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_2               54      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL42_2               55      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_2               56      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL60_L_2             57      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL40_2               58      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_L_2             59      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL39_2               60      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_L_2             61      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL38_2               62      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_L_2             63      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL37_2               64      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_L_2             65      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL36_2               66      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL55_L_2             67      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL35_2               68      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_L_2             69      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL34_2               70      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_L_2             71      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL33_2               72      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_L_2             73      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL32_2               74      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_L_2             75      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_2               76      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL50_L_2             77      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_2               78      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL49_L_2             79      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_2               80      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL48_L_2             81      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL28_2               82      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL47_L_2             83      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_2               84      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL46_L_2             85      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_2               86      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_L_2             87      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_2               88      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_L_2             89      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_2               90      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_L_2             91      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_2               92      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL42_L_2             93      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_2               94      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_L_2             95      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_2               96      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL40_L_2             97      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_2               98      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL39_L_2             99      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_2               100     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL38_L_2             101     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_2               102     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_L_2             103     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_2               104     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL36_L_2             105     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_2               106     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL35_L_2             107     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL13_2               108     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL34_L_2             109     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_2               110     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL33_L_2             111     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_2               112     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL32_L_2             113     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_L_2             114     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_L_2             115     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_L_2             116     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_L_2             117     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_L_2             118     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_43         119     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SOL28_L_2             120     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_L_2             121     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_L_2             122     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_L_2             123     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_L_2             124     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_L_2             125     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_L_2             126     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_L_2             127     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_WORK_MODEL_CHAR2      128     /* control type: string, callback function: (none) */
#define  MANUALCTRL_WORK_NAME2            129     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL20_L_2             130     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_L_2             131     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_L_2             132     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_L_2             133     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_L_2             134     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_MANUAL_PRINTING_2     135     /* control type: command, callback function: Manual_Printing2 */
#define  MANUALCTRL_MANUAL_PRINTING       136     /* control type: command, callback function: Manual_Printing */
#define  MANUALCTRL_MANU_BARCODE_DATA     137     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL13_L_2             138     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_E_STOP_BT2            139     /* control type: command, callback function: E_Stop_Bt2 */
#define  MANUALCTRL_BZ_STOP2              140     /* control type: command, callback function: BZ_Stop2 */
#define  MANUALCTRL_AL_RESET2             141     /* control type: command, callback function: AL_ReSet2 */
#define  MANUALCTRL_ORIGIN_BT2            142     /* control type: command, callback function: ORIGIN_bt2 */
#define  MANUALCTRL_ERRVIEW2              143     /* control type: command, callback function: ErrView */
#define  MANUALCTRL_SOL12_L_2             144     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_L_2             145     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_2               146     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_2               147     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL9_2                148     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_L_2             149     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL9_L_2              150     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL8_2                151     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL8_L_2              152     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_50         153     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_37            154     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_49         155     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_36            156     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_42            157     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_61         158     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_48            159     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_58         160     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_45            161     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_65         162     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_51            163     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_73         164     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_58            165     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_69         166     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_55            167     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_67         168     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_53            169     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_71         170     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_57            171     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_70         172     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_56            173     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_66         174     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_61            175     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_52            176     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_76         177     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_68         178     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_54            179     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_64         180     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_50            181     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_56         182     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_43            183     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_CLR_1                 184     /* control type: command, callback function: Clr */
#define  MANUALCTRL_M_MEAS_TABLE          185     /* control type: table, callback function: MeasTabelCallback */
#define  MANUALCTRL_SAVE_1                186     /* control type: command, callback function: Save */
#define  MANUALCTRL_RESULTVIEW_1          187     /* control type: command, callback function: ResultView1 */
#define  MANUALCTRL_CLOSE                 188     /* control type: command, callback function: Close */
#define  MANUALCTRL_CH21                  189     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH22                  190     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH23                  191     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH24                  192     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH25                  193     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH4                   194     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH3                   195     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH2                   196     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH1                   197     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH26                  198     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH27                  199     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH28                  200     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH29                  201     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_STRING                202     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH30                  203     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH31                  204     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH40                  205     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH39                  206     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH38                  207     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH37                  208     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH36                  209     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH35                  210     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH34                  211     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH33                  212     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH32                  213     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH5                   214     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CYCLENOSET_1          215     /* control type: numeric, callback function: ManualCtrl */
#define  MANUALCTRL_MCYCLEINDEX_1         216     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH6                   217     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_A_DATAVIEW2           218     /* control type: command, callback function: A_Dataview2 */
#define  MANUALCTRL_CH7                   219     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_MODELSETUP2           220     /* control type: command, callback function: Modelsetup2 */
#define  MANUALCTRL_REFER_BT2             221     /* control type: command, callback function: Refer_Bt2 */
#define  MANUALCTRL_CH8                   222     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH9                   223     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH10                  224     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH11                  225     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH48                  226     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH47                  227     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH46                  228     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH45                  229     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH44                  230     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_SAVE            231     /* control type: command, callback function: Servo_Save */
#define  MANUALCTRL_SERVO_SEND_3          232     /* control type: command, callback function: Servo_Send_3 */
#define  MANUALCTRL_SERVO_MOVE_3          233     /* control type: command, callback function: Servo_Move_3 */
#define  MANUALCTRL_SERVO_SEND_2          234     /* control type: command, callback function: Servo_Send_2 */
#define  MANUALCTRL_SERVO_MOVE_2          235     /* control type: command, callback function: Servo_Move_2 */
#define  MANUALCTRL_SERVO_SEND            236     /* control type: command, callback function: Servo_Send */
#define  MANUALCTRL_SERVO_MOVE            237     /* control type: command, callback function: Servo_Move */
#define  MANUALCTRL_CH43                  238     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH42                  239     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH41                  240     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH20                  241     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH19                  242     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH18                  243     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH17                  244     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_M_WORK2               245     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_M_WORK1               246     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_CH16                  247     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH15                  248     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH14                  249     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH13                  250     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_RING_2                251     /* control type: ring, callback function: View_Chdata */
#define  MANUALCTRL_CH12                  252     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_14         253     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_15         254     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_27         255     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_26         256     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_25         257     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_24         258     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_21            259     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_20            260     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_19            261     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_18            262     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_60            263     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_19           264     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_75         265     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_O_LED_1               266     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_59            267     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_18           268     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_74         269     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_MA_LED_1              270     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_24            271     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_17           272     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_16         273     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_LED_1               274     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_49            275     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_16           276     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_62         277     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_D_LED_1               278     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_7             279     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_2            280     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_63         281     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_W_LED_1               282     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_4                 283     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_2                 284     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED                   285     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_10            286     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_5             287     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_POINT_RING            288     /* control type: ring, callback function: RepeatSel */
#define  MANUALCTRL_LED_3                 289     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LISTBOX_2             290     /* control type: listBox, callback function: (none) */
#define  MANUALCTRL_MANUALTEST_2          291     /* control type: command, callback function: ManualMeasSw2 */
#define  MANUALCTRL_MANUALTEST_4          292     /* control type: command, callback function: ManualMeasSw4 */
#define  MANUALCTRL_MANUALTEST_M          293     /* control type: command, callback function: ManualMeasSw1 */
#define  MANUALCTRL_MANUALTEST_3          294     /* control type: command, callback function: ManualMeasSw3 */
#define  MANUALCTRL_MANUALTEST_1          295     /* control type: command, callback function: ManualMeasSw */
#define  MANUALCTRL_VEL_SLIDE             296     /* control type: slide, callback function: (none) */
#define  MANUALCTRL_TOG_RUN               297     /* control type: toggle, callback function: Tog_Run */
#define  MANUALCTRL_MSG_TEST              298     /* control type: string, callback function: (none) */
#define  MANUALCTRL_GRAPH1                299     /* control type: graph, callback function: (none) */
#define  MANUALCTRL_MEAS_CNT              300     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_4             301     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_3             302     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_C_MODE                303     /* control type: slide, callback function: Mode_Select */
#define  MANUALCTRL_PICTURE               304     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_2             305     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_MODEL_TL              306     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_EPB             307     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_WD              308     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_LR              309     /* control type: textButton, callback function: Model_LR_Func */
#define  MANUALCTRL_TEXTMSG_23            310     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_RINGSLIDE             311     /* control type: slide, callback function: M_Meas_Mode */
#define  MANUALCTRL_MMDDYY                312     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_HHMMSS                313     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_32         314     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_37         315     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_33         316     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_HOME_BT               317     /* control type: command, callback function: Home_Bt */
#define  MANUALCTRL_ACT_BT                318     /* control type: command, callback function: Act_Bt */
#define  MANUALCTRL_DECORATION_20         319     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_18         320     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_SELECT_VIEW         321     /* control type: textButton, callback function: M_Select_View */
#define  MANUALCTRL_DECO_1                322     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_CYCLEMODE_2           323     /* control type: binary, callback function: CycleMode_2 */
#define  MANUALCTRL_CYCLEMODE_1           324     /* control type: binary, callback function: (none) */
#define  MANUALCTRL_REALTIMEMEAS          325     /* control type: binary, callback function: RealTimeMeas */
#define  MANUALCTRL_TIMER                 326     /* control type: timer, callback function: TestTimer */
#define  MANUALCTRL_DECORATION_2          327     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_3          328     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_MARKDATA            329     /* control type: string, callback function: (none) */
#define  MANUALCTRL_POS_SELECT4           330     /* control type: ring, callback function: Pos_Select4 */
#define  MANUALCTRL_DATA_SAVE             331     /* control type: textBox, callback function: (none) */
#define  MANUALCTRL_POS_SELECT3           332     /* control type: ring, callback function: Pos_Select3 */
#define  MANUALCTRL_POS_SELECT2           333     /* control type: ring, callback function: Pos_Select2 */
#define  MANUALCTRL_JOG_VEL2              334     /* control type: slide, callback function: Jog_Vel2 */
#define  MANUALCTRL_RING                  335     /* control type: ring, callback function: (none) */
#define  MANUALCTRL_ACTION_3              336     /* control type: command, callback function: Action_3 */
#define  MANUALCTRL_ACTION_2              337     /* control type: command, callback function: Action_2 */
#define  MANUALCTRL_ACTION_1              338     /* control type: command, callback function: Action_1 */
#define  MANUALCTRL_DECO_5                339     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_ORIGIN_PIC            340     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_H_LED_4               341     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_3               342     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_2               343     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_5          344     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_H_LED_1               345     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECO_6                346     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SERVO12_SERVO         347     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO11_SERVO         348     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO10_SERVO         349     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO9_SERVO          350     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO8_SERVO          351     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO7_SERVO          352     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO6_SERVO          353     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO5_SERVO          354     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO4_SERVO          355     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO3_SERVO          356     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO1_SERVO          357     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_SERVO          358     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_6          359     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SCAN_ON_OFF           360     /* control type: command, callback function: Scan_OnOff */
#define  MANUALCTRL_LASER_ON_OFF          361     /* control type: command, callback function: Laser_OnOff */
#define  MANUALCTRL_DECORATION_72         362     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_4          363     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_E_STOP_BT3            364     /* control type: textButton, callback function: E_Stop_Bt3 */
#define  MANUALCTRL_DECORATION            365     /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Act_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AL_ReSet2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BZ_Stop2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CycleMode_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E_Stop_Bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E_Stop_Bt3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrView(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Home_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Jog_Vel2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Laser_OnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Meas_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Select_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrlCall(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManuSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTabelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mode_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Model_LR_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Modelsetup2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ORIGIN_bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RealTimeMeas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_Bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RepeatSel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResultView1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Scan_OnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Home(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ServoSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TestTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tog_Run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK View_Chdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
