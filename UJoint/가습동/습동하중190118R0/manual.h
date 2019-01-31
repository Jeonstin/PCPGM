/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2019. All Rights Reserved.          */
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
#define  MANUALCTRL_SOL45_2               32      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_2               33      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_2               34      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL42_2               35      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_2               36      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL40_2               37      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL39_2               38      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL38_2               39      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_2               40      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL36_2               41      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL35_2               42      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL34_2               43      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL33_2               44      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL32_2               45      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL31_2               46      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL30_2               47      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL29_2               48      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL28_2               49      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL27_2               50      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL25_2               51      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_L_2             52      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_2               53      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_L_2             54      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_2               55      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_L_2             56      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL42_L_2             57      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_2               58      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL22_2               59      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_L_2             60      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_2               61      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL40_L_2             62      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_2               63      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL39_L_2             64      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_2               65      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL38_L_2             66      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_2               67      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_L_2             68      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_2               69      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL36_L_2             70      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_2               71      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL35_L_2             72      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL13_2               73      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL34_L_2             74      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_2               75      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL33_L_2             76      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_2               77      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL32_L_2             78      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_L_2             79      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_L_2             80      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_L_2             81      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_L_2             82      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_L_2             83      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_43         84      /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SOL28_L_2             85      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_M_GNG_4               86      /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_M_GNG_3               87      /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_M_GNG_2               88      /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_SOL27_L_2             89      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_L_2             90      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_L_2             91      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_L_2             92      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_L_2             93      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_L_2             94      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_L_2             95      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_L_2             96      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_L_2             97      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_L_2             98      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_L_2             99      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_L_2             100     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_MANUAL_PRINTING_3     101     /* control type: command, callback function: Manual_Printing3 */
#define  MANUALCTRL_MANUAL_PRINTING_2     102     /* control type: command, callback function: Manual_Printing2 */
#define  MANUALCTRL_MANUAL_PRINTING_5     103     /* control type: command, callback function: Manual_Printing5 */
#define  MANUALCTRL_MANUAL_PRINTING_4     104     /* control type: command, callback function: Manual_Printing4 */
#define  MANUALCTRL_MANUAL_PRINTING_6     105     /* control type: command, callback function: Manual_Printing6 */
#define  MANUALCTRL_MANUAL_PRINTING       106     /* control type: command, callback function: Manual_Printing */
#define  MANUALCTRL_MANU_BARCODE_DATA     107     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL13_L_2             108     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_L_2             109     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_2               110     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL11_L_2             111     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_2               112     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_2               113     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL9_2                114     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_L_2             115     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL9_L_2              116     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL8_2                117     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL8_L_2              118     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_50         119     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_57            120     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_56            121     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_58            122     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_55            123     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_54            124     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_49         125     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_70         126     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_36            127     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_69         128     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_GRAPH6                129     /* control type: graph, callback function: Graph1 */
#define  MANUALCTRL_GRAPH5                130     /* control type: graph, callback function: Graph1 */
#define  MANUALCTRL_GRAPH4                131     /* control type: graph, callback function: Graph1 */
#define  MANUALCTRL_GRAPH3                132     /* control type: graph, callback function: Graph1 */
#define  MANUALCTRL_DECORATION_71         133     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_52         134     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_68         135     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_39            136     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_67         137     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_62         138     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_49            139     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_46            140     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SCAN_DATA             141     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CLR_1                 142     /* control type: command, callback function: Clr */
#define  MANUALCTRL_M_CHVALUE             143     /* control type: table, callback function: (none) */
#define  MANUALCTRL_M_MEAS_TABLE          144     /* control type: table, callback function: MeasTabelCallback */
#define  MANUALCTRL_SAVE_1                145     /* control type: command, callback function: Save */
#define  MANUALCTRL_RESULTVIEW_1          146     /* control type: command, callback function: ResultView1 */
#define  MANUALCTRL_CLOSE                 147     /* control type: command, callback function: Close */
#define  MANUALCTRL_CH21                  148     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH22                  149     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH23                  150     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH24                  151     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH25                  152     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH4                   153     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH3                   154     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH2                   155     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH1                   156     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH26                  157     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH27                  158     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH28                  159     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_WORK_NAME2            160     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH29                  161     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_STRING_3              162     /* control type: string, callback function: (none) */
#define  MANUALCTRL_STRING                163     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH30                  164     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH31                  165     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH40                  166     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH39                  167     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH38                  168     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH37                  169     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH36                  170     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH35                  171     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH34                  172     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH33                  173     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH32                  174     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_STRING_2              175     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH5                   176     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CYCLENOSET_1          177     /* control type: numeric, callback function: ManualCtrl */
#define  MANUALCTRL_MCYCLEINDEX_1         178     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH6                   179     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH7                   180     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH8                   181     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH9                   182     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH10                  183     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH11                  184     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH48                  185     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH47                  186     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH46                  187     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH45                  188     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH44                  189     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_SAVE            190     /* control type: command, callback function: Servo_Save */
#define  MANUALCTRL_SERVO_SEND_3          191     /* control type: command, callback function: Servo_Send_3 */
#define  MANUALCTRL_SERVO_MOVE_3          192     /* control type: command, callback function: Servo_Move_3 */
#define  MANUALCTRL_SERVO_SEND_2          193     /* control type: command, callback function: Servo_Send_2 */
#define  MANUALCTRL_SERVO_MOVE_2          194     /* control type: command, callback function: Servo_Move_2 */
#define  MANUALCTRL_SERVO_SEND            195     /* control type: command, callback function: Servo_Send */
#define  MANUALCTRL_SERVO_MOVE            196     /* control type: command, callback function: Servo_Move */
#define  MANUALCTRL_CH43                  197     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH42                  198     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH41                  199     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH20                  200     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH19                  201     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH18                  202     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH17                  203     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_M_WORK2               204     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_M_WORK1               205     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_CH16                  206     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH15                  207     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH14                  208     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH13                  209     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_RING_2                210     /* control type: ring, callback function: View_Chdata */
#define  MANUALCTRL_CH12                  211     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_14         212     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_15         213     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_27         214     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_26         215     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_25         216     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_24         217     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_21            218     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_20            219     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_19            220     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_18            221     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_LED_4                 222     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_2                 223     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED                   224     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_10            225     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_5             226     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_POINT_RING            227     /* control type: ring, callback function: RepeatSel */
#define  MANUALCTRL_LED_3                 228     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LISTBOX_2             229     /* control type: listBox, callback function: (none) */
#define  MANUALCTRL_MANUALTEST_2          230     /* control type: command, callback function: ManualMeasSw2 */
#define  MANUALCTRL_MANUALTEST_4          231     /* control type: command, callback function: ManualMeasSw4 */
#define  MANUALCTRL_MANUALTEST_M_2        232     /* control type: command, callback function: ManualMeasSw2 */
#define  MANUALCTRL_MANUALTEST_M          233     /* control type: command, callback function: ManualMeasSw1 */
#define  MANUALCTRL_MANUALTEST_3          234     /* control type: command, callback function: ManualMeasSw3 */
#define  MANUALCTRL_MANUALTEST_1          235     /* control type: command, callback function: ManualMeasSw */
#define  MANUALCTRL_VEL_SLIDE             236     /* control type: slide, callback function: (none) */
#define  MANUALCTRL_TOG_RUN               237     /* control type: toggle, callback function: Tog_Run */
#define  MANUALCTRL_MSG_TEST              238     /* control type: string, callback function: (none) */
#define  MANUALCTRL_GRAPH2                239     /* control type: graph, callback function: (none) */
#define  MANUALCTRL_GRAPH1                240     /* control type: graph, callback function: (none) */
#define  MANUALCTRL_MEAS_CNT              241     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_4             242     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_3             243     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_C_MODE                244     /* control type: slide, callback function: Mode_Select */
#define  MANUALCTRL_PICTURE               245     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_2             246     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_MODEL_TL              247     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_EPB             248     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_WD              249     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_LR              250     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_23            251     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_RINGSLIDE             252     /* control type: slide, callback function: M_Meas_Mode */
#define  MANUALCTRL_MMDDYY                253     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_HHMMSS                254     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_37         255     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_HOME_BT               256     /* control type: command, callback function: Home_Bt */
#define  MANUALCTRL_ACT_BT                257     /* control type: command, callback function: Act_Bt */
#define  MANUALCTRL_DECORATION_20         258     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_65         259     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_63         260     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_SELECT_VIEW         261     /* control type: textButton, callback function: M_Select_View */
#define  MANUALCTRL_DECO_1                262     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_CYCLEMODE_2           263     /* control type: binary, callback function: CycleMode_2 */
#define  MANUALCTRL_CYCLEMODE_1           264     /* control type: binary, callback function: (none) */
#define  MANUALCTRL_REALTIMEMEAS          265     /* control type: binary, callback function: RealTimeMeas */
#define  MANUALCTRL_TIMER                 266     /* control type: timer, callback function: TestTimer */
#define  MANUALCTRL_DECORATION_2          267     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_3          268     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_4          269     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_MARKDATA            270     /* control type: string, callback function: (none) */
#define  MANUALCTRL_POS_SELECT4           271     /* control type: ring, callback function: Pos_Select4 */
#define  MANUALCTRL_DATA_SAVE             272     /* control type: textBox, callback function: (none) */
#define  MANUALCTRL_POS_SELECT3           273     /* control type: ring, callback function: Pos_Select3 */
#define  MANUALCTRL_POS_SELECT2           274     /* control type: ring, callback function: Pos_Select2 */
#define  MANUALCTRL_JOG_VEL2              275     /* control type: slide, callback function: Jog_Vel2 */
#define  MANUALCTRL_RING                  276     /* control type: ring, callback function: (none) */
#define  MANUALCTRL_ACTION_3              277     /* control type: command, callback function: Action_3 */
#define  MANUALCTRL_ACTION_2              278     /* control type: command, callback function: Action_2 */
#define  MANUALCTRL_ACTION_1              279     /* control type: command, callback function: Action_1 */
#define  MANUALCTRL_DECO_5                280     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_H_LED_4               281     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_3               282     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_2               283     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_5          284     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_H_LED_1               285     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECO_6                286     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_MEAS_SERVO            287     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_TRANS_SERVO           288     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_MARK_SERVO            289     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_7          290     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_VIEW_2              291     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_ORIGIN_PIC            292     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_M_VIEW                293     /* control type: deco, callback function: (none) */


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
int  CVICALLBACK Graph1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Home_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Jog_Vel2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Meas_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Select_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrlCall(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManuSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTabelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mode_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RealTimeMeas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RepeatSel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResultView1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
