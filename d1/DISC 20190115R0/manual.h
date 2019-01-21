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
#define  MANUALCTRL_SERVO2_1              11      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO_HOME            12      /* control type: command, callback function: Servo_Home */
#define  MANUALCTRL_SERVO1_JOG            13      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_T_MSG_1               14      /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SERVO1_3              15      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_2              16      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_1              17      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SOL7_2                18      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_2                19      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL5_2                20      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL4_2                21      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL3_2                22      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL2_2                23      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL1_2                24      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_L_2              25      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL7_L_2              26      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL4_L_2              27      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL5_L_2              28      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL3_L_2              29      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL2_L_2              30      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL1_L_2              31      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_2               32      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL60_2               33      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_2               34      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_2               35      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_2               36      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_2               37      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL55_2               38      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_2               39      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_2               40      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_2               41      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_2               42      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL50_2               43      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL49_2               44      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL48_2               45      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL47_2               46      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL46_2               47      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_2               48      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL24_2               49      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL23_2               50      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL22_2               51      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_2               52      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_2               53      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL42_2               54      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_2               55      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL60_L_2             56      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL40_2               57      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_L_2             58      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL39_2               59      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_L_2             60      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL38_2               61      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_L_2             62      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL37_2               63      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_L_2             64      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL36_2               65      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL55_L_2             66      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL35_2               67      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_L_2             68      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL34_2               69      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_L_2             70      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL33_2               71      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_L_2             72      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL32_2               73      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_L_2             74      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_2               75      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL50_L_2             76      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_2               77      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL49_L_2             78      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_2               79      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL48_L_2             80      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL28_2               81      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL47_L_2             82      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_2               83      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL46_L_2             84      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_2               85      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_L_2             86      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_2               87      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL24_L_2             88      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_L_2             89      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_L_2             90      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL44_L_2             91      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL43_L_2             92      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL42_L_2             93      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL41_L_2             94      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_2               95      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL40_L_2             96      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_2               97      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL39_L_2             98      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_2               99      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL38_L_2             100     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_2               101     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_L_2             102     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_2               103     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL36_L_2             104     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_2               105     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL35_L_2             106     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL13_2               107     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL34_L_2             108     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_2               109     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL33_L_2             110     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_2               111     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL32_L_2             112     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_L_2             113     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_L_2             114     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_L_2             115     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_L_2             116     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_L_2             117     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_43         118     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SOL28_L_2             119     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_L_2             120     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_L_2             121     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_L_2             122     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_L_2             123     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_L_2             124     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_L_2             125     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_L_2             126     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_L_2             127     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_L_2             128     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_MANUAL_PRINTING_2     129     /* control type: command, callback function: Manual_Printing2 */
#define  MANUALCTRL_MANUAL_PRINTING       130     /* control type: command, callback function: Manual_Printing */
#define  MANUALCTRL_MANU_BARCODE_DATA     131     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL13_L_2             132     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_L_2             133     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_L_2             134     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_2               135     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_2               136     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL9_2                137     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_L_2             138     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL9_L_2              139     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL8_2                140     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL8_L_2              141     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_50         142     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_37            143     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_49         144     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_36            145     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_42            146     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_60         147     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_47            148     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_63         149     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_50            150     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_61         151     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_48            152     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_58         153     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_45            154     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_62         155     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_49            156     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_56         157     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_43            158     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_47         159     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_34            160     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_CLR_1                 161     /* control type: command, callback function: Clr */
#define  MANUALCTRL_M_MEAS_TABLE          162     /* control type: table, callback function: MeasTabelCallback */
#define  MANUALCTRL_SAVE_1                163     /* control type: command, callback function: Save */
#define  MANUALCTRL_RESULTVIEW_1          164     /* control type: command, callback function: ResultView1 */
#define  MANUALCTRL_CLOSE                 165     /* control type: command, callback function: Close */
#define  MANUALCTRL_CH21                  166     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH22                  167     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH23                  168     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH24                  169     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH25                  170     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH4                   171     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH3                   172     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH2                   173     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH1                   174     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH26                  175     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH27                  176     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH28                  177     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_WORK_NAME2            178     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH29                  179     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_STRING                180     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH30                  181     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH31                  182     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH40                  183     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH39                  184     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH38                  185     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH37                  186     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH36                  187     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH35                  188     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH34                  189     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH33                  190     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH32                  191     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH5                   192     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CYCLENOSET_1          193     /* control type: numeric, callback function: ManualCtrl */
#define  MANUALCTRL_MCYCLEINDEX_1         194     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH6                   195     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH7                   196     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH8                   197     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH9                   198     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH10                  199     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH11                  200     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH48                  201     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH47                  202     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH46                  203     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH45                  204     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH44                  205     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_SAVE            206     /* control type: command, callback function: Servo_Save */
#define  MANUALCTRL_SERVO_SEND_3          207     /* control type: command, callback function: Servo_Send_3 */
#define  MANUALCTRL_SERVO_MOVE_3          208     /* control type: command, callback function: Servo_Move_3 */
#define  MANUALCTRL_SERVO_SEND_2          209     /* control type: command, callback function: Servo_Send_2 */
#define  MANUALCTRL_SERVO_MOVE_2          210     /* control type: command, callback function: Servo_Move_2 */
#define  MANUALCTRL_SERVO_SEND            211     /* control type: command, callback function: Servo_Send */
#define  MANUALCTRL_SERVO_MOVE            212     /* control type: command, callback function: Servo_Move */
#define  MANUALCTRL_CH43                  213     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH42                  214     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH41                  215     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH20                  216     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH19                  217     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH18                  218     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH17                  219     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_M_WORK2               220     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_M_WORK1               221     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_CH16                  222     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH15                  223     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH14                  224     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH13                  225     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_RING_2                226     /* control type: ring, callback function: View_Chdata */
#define  MANUALCTRL_CH12                  227     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_14         228     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_15         229     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_27         230     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_26         231     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_25         232     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_24         233     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_21            234     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_20            235     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_19            236     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_18            237     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_LED_4                 238     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_2                 239     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED                   240     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_10            241     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_5             242     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_POINT_RING            243     /* control type: ring, callback function: RepeatSel */
#define  MANUALCTRL_LED_3                 244     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LISTBOX_2             245     /* control type: listBox, callback function: (none) */
#define  MANUALCTRL_MANUALTEST_2          246     /* control type: command, callback function: ManualMeasSw2 */
#define  MANUALCTRL_MANUALTEST_5          247     /* control type: command, callback function: ManualMeasSw6 */
#define  MANUALCTRL_MANUALTEST_4          248     /* control type: command, callback function: ManualMeasSw4 */
#define  MANUALCTRL_MANUALTEST_M          249     /* control type: command, callback function: ManualMeasSw1 */
#define  MANUALCTRL_MANUALTEST_3          250     /* control type: command, callback function: ManualMeasSw3 */
#define  MANUALCTRL_MANUALTEST_1          251     /* control type: command, callback function: ManualMeasSw */
#define  MANUALCTRL_VEL_SLIDE             252     /* control type: slide, callback function: (none) */
#define  MANUALCTRL_TOG_RUN               253     /* control type: toggle, callback function: Tog_Run */
#define  MANUALCTRL_MSG_TEST              254     /* control type: string, callback function: (none) */
#define  MANUALCTRL_GRAPH1                255     /* control type: graph, callback function: (none) */
#define  MANUALCTRL_MEAS_CNT              256     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_4             257     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_3             258     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_C_MODE                259     /* control type: slide, callback function: Mode_Select */
#define  MANUALCTRL_PICTURE               260     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_2             261     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_MODEL_TL              262     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_EPB             263     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_WD              264     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_LR              265     /* control type: textButton, callback function: Model_LR_Func */
#define  MANUALCTRL_TEXTMSG_23            266     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_RINGSLIDE             267     /* control type: slide, callback function: M_Meas_Mode */
#define  MANUALCTRL_MMDDYY                268     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_HHMMSS                269     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_32         270     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_37         271     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_33         272     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_HOME_BT               273     /* control type: command, callback function: Home_Bt */
#define  MANUALCTRL_ACT_BT                274     /* control type: command, callback function: Act_Bt */
#define  MANUALCTRL_DECORATION_20         275     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_18         276     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_SELECT_VIEW         277     /* control type: textButton, callback function: M_Select_View */
#define  MANUALCTRL_DECO_1                278     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_CYCLEMODE_2           279     /* control type: binary, callback function: CycleMode_2 */
#define  MANUALCTRL_CYCLEMODE_1           280     /* control type: binary, callback function: (none) */
#define  MANUALCTRL_REALTIMEMEAS          281     /* control type: binary, callback function: RealTimeMeas */
#define  MANUALCTRL_TIMER                 282     /* control type: timer, callback function: TestTimer */
#define  MANUALCTRL_DECORATION_2          283     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_3          284     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_MARKDATA            285     /* control type: string, callback function: (none) */
#define  MANUALCTRL_POS_SELECT4           286     /* control type: ring, callback function: Pos_Select4 */
#define  MANUALCTRL_DATA_SAVE             287     /* control type: textBox, callback function: (none) */
#define  MANUALCTRL_POS_SELECT3           288     /* control type: ring, callback function: Pos_Select3 */
#define  MANUALCTRL_POS_SELECT2           289     /* control type: ring, callback function: Pos_Select2 */
#define  MANUALCTRL_JOG_VEL2              290     /* control type: slide, callback function: Jog_Vel2 */
#define  MANUALCTRL_RING                  291     /* control type: ring, callback function: (none) */
#define  MANUALCTRL_ACTION_3              292     /* control type: command, callback function: Action_3 */
#define  MANUALCTRL_ACTION_2              293     /* control type: command, callback function: Action_2 */
#define  MANUALCTRL_ACTION_1              294     /* control type: command, callback function: Action_1 */
#define  MANUALCTRL_DECO_5                295     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_ORIGIN_PIC            296     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_H_LED_4               297     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_3               298     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_2               299     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_5          300     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_H_LED_1               301     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECO_6                302     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SERVO12_SERVO         303     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO11_SERVO         304     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO10_SERVO         305     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO9_SERVO          306     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO8_SERVO          307     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO7_SERVO          308     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO6_SERVO          309     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO5_SERVO          310     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO4_SERVO          311     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO3_SERVO          312     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO1_SERVO          313     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_SERVO          314     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_6          315     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION            316     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_7          317     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SCAN_ON_OFF           318     /* control type: command, callback function: Scan_OnOff */
#define  MANUALCTRL_LASER_ON_OFF          319     /* control type: command, callback function: Laser_OnOff */
#define  MANUALCTRL_DECORATION_4          320     /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Act_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CycleMode_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK ManualMeasSw6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManuSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTabelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mode_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Model_LR_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RealTimeMeas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
