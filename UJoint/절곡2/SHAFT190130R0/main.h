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

#define  CALPANEL                         1       /* callback function: Calib_Event */
#define  CALPANEL_CLOSE                   2       /* control type: command, callback function: Close */
#define  CALPANEL_AMP_NO                  3       /* control type: ring, callback function: Amp_No */
#define  CALPANEL_AMP_ON                  4       /* control type: textButton, callback function: Amp_On */
#define  CALPANEL_AMP_LED                 5       /* control type: LED, callback function: (none) */
#define  CALPANEL_MASTER1_8               6       /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_7               7       /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_6               8       /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_5               9       /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_4               10      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_3               11      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_2               12      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_8               13      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_7               14      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_6               15      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_5               16      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_4               17      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_3               18      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_2               19      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_8              20      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_7              21      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_6              22      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_5              23      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_4              24      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_3              25      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_2              26      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_8              27      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_7              28      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_6              29      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_5              30      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_4              31      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_3              32      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_2              33      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_PARA_1              34      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_8            35      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_7            36      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_6            37      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_5            38      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_4            39      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_3            40      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_2            41      /* control type: numeric, callback function: (none) */
#define  CALPANEL_OPSET_DATA_1            42      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_8              43      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_7              44      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_6              45      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_5              46      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_4              47      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_3              48      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_2              49      /* control type: numeric, callback function: (none) */
#define  CALPANEL_LOW_DATA_1              50      /* control type: numeric, callback function: (none) */
#define  CALPANEL_CAL_DATA_1              51      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER2_1               52      /* control type: numeric, callback function: (none) */
#define  CALPANEL_MASTER1_1               53      /* control type: numeric, callback function: (none) */
#define  CALPANEL_TEXTMSG                 54      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_2               55      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_3               56      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_4               57      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_5               58      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_6               59      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_7               60      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_8               61      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_9               62      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_10              63      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_CAL8_2                  64      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL8_1                  65      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL7_2                  66      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL7_1                  67      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL6_2                  68      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL6_1                  69      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL5_2                  70      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL5_1                  71      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL4_2                  72      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL4_1                  73      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL3_2                  74      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL3_1                  75      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_CAL2_2                  76      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL2_1                  77      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_UPDATE_8                78      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_7                79      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_6                80      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_5                81      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_4                82      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_3                83      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_2                84      /* control type: command, callback function: Update1 */
#define  CALPANEL_UPDATE_1                85      /* control type: command, callback function: Update1 */
#define  CALPANEL_CAL1_2                  86      /* control type: command, callback function: Calibration_Master2 */
#define  CALPANEL_CAL1_1                  87      /* control type: command, callback function: Calibration_Master1 */
#define  CALPANEL_TEXTMSG_14              88      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_13              89      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_15              90      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_12              91      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_16              92      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_11              93      /* control type: textMsg, callback function: (none) */
#define  CALPANEL_DECORATION_23           94      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_22           95      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_21           96      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_20           97      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_19           98      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_18           99      /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_17           100     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION              101     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_14           102     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_15           103     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_13           104     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_16           105     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_12           106     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_11           107     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_10           108     /* control type: deco, callback function: (none) */
#define  CALPANEL_DECORATION_9            109     /* control type: deco, callback function: (none) */

#define  DATAPANEL                        2       /* callback function: DatapanelCall */
#define  DATAPANEL_CLOSE                  2       /* control type: command, callback function: Close */
#define  DATAPANEL_WORK_NAME              3       /* control type: string, callback function: (none) */
#define  DATAPANEL_MMDDYY                 4       /* control type: textMsg, callback function: (none) */
#define  DATAPANEL_HHMMSS                 5       /* control type: textMsg, callback function: (none) */
#define  DATAPANEL_DECORATION             6       /* control type: deco, callback function: (none) */
#define  DATAPANEL_PICTURE_2              7       /* control type: picture, callback function: (none) */
#define  DATAPANEL_TEXTMSG_18             8       /* control type: textMsg, callback function: (none) */
#define  DATAPANEL_GRAPH1                 9       /* control type: graph, callback function: (none) */
#define  DATAPANEL_DATA_TABLE             10      /* control type: table, callback function: (none) */
#define  DATAPANEL_RING_2                 11      /* control type: ring, callback function: View_garph */

#define  MAINPANEL                        3       /* callback function: MainPanelEvent */
#define  MAINPANEL_LED_OUT_4              2       /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_OUT_3              3       /* control type: LED, callback function: (none) */
#define  MAINPANEL_SPLITTER_6             4       /* control type: splitter, callback function: (none) */
#define  MAINPANEL_MAINCTRL0              5       /* control type: pictButton, callback function: MainCtrl0 */
#define  MAINPANEL_LED_IN_5               6       /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_IN_3               7       /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_IN_4               8       /* control type: LED, callback function: (none) */
#define  MAINPANEL_LSTDDIV                9       /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LMIN                   10      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_CWGRAPH                11      /* control type: activeX, callback function: (none) */
#define  MAINPANEL_LMAX                   12      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LR                     13      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LCP                    14      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LXBAR                  15      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LCPK                   16      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_MARK_CNT_NO            17      /* control type: numeric, callback function: TotalTestNo */
#define  MAINPANEL_TOTALTESTNO            18      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_P10                    19      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P9                     20      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P8                     21      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P7                     22      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P6                     23      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P5                     24      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P4                     25      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P3                     26      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P2                     27      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P1                     28      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P63                    29      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_GRAPH_HIS              30      /* control type: graph, callback function: (none) */
#define  MAINPANEL_P62                    31      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P61                    32      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P60                    33      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P59                    34      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P58                    35      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P57                    36      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P56                    37      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P55                    38      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P54                    39      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_TEXTMSG_2              40      /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_P53                    41      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P52                    42      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P51                    43      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P50                    44      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P49                    45      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P48                    46      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P47                    47      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P46                    48      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P45                    49      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P44                    50      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P43                    51      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P42                    52      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P41                    53      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P40                    54      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P39                    55      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P38                    56      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P37                    57      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P36                    58      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P35                    59      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P34                    60      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P33                    61      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P32                    62      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P31                    63      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P30                    64      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P29                    65      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P28                    66      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P27                    67      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P26                    68      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P25                    69      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P24                    70      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P23                    71      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P22                    72      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P21                    73      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P20                    74      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P19                    75      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P18                    76      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P17                    77      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P16                    78      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P15                    79      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P14                    80      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P13                    81      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P12                    82      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_P11                    83      /* control type: numeric, callback function: MeasPointEvent */
#define  MAINPANEL_LNG                    84      /* control type: numeric, callback function: TotalTestNo */
#define  MAINPANEL_LG_3                   85      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LG_2                   86      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LG                     87      /* control type: numeric, callback function: (none) */
#define  MAINPANEL_GNG_3                  88      /* control type: textButton, callback function: (none) */
#define  MAINPANEL_GNG_2                  89      /* control type: textButton, callback function: (none) */
#define  MAINPANEL_GNG                    90      /* control type: textButton, callback function: (none) */
#define  MAINPANEL_DATETIME               91      /* control type: timer, callback function: cbDateTime */
#define  MAINPANEL_PLCTIMER               92      /* control type: timer, callback function: PlcTimer */
#define  MAINPANEL_AMPTIMER               93      /* control type: timer, callback function: AmpTimer */
#define  MAINPANEL_TESTTIME               94      /* control type: timer, callback function: TestTime */
#define  MAINPANEL_SPCLEFT                95      /* control type: ring, callback function: SPCSelect */
#define  MAINPANEL_TEXTMSG                96      /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_STATUSMSG_5            97      /* control type: string, callback function: (none) */
#define  MAINPANEL_STATUSMSG_4            98      /* control type: string, callback function: (none) */
#define  MAINPANEL_STATUSMSG_3            99      /* control type: string, callback function: (none) */
#define  MAINPANEL_STATUSMSG_2            100     /* control type: string, callback function: (none) */
#define  MAINPANEL_STATUSMSG              101     /* control type: string, callback function: (none) */
#define  MAINPANEL_MEASDATATABLE          102     /* control type: table, callback function: (none) */
#define  MAINPANEL_LED_OUT_2              103     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_OUT_1              104     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_IN_2               105     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_10            106     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_9             107     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_8             108     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_7             109     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_6             110     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_5             111     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_4             112     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_3             113     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_2             114     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_DATA_1             115     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_IN_1               116     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_4                  117     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LSL                    118     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LCL                    119     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_UCL                    120     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_DECORATION_2           121     /* control type: deco, callback function: (none) */
#define  MAINPANEL_USL                    122     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_CH_S2                  123     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_WORK_MODEL_CHAR        124     /* control type: string, callback function: (none) */
#define  MAINPANEL_WORK_NAME              125     /* control type: string, callback function: (none) */
#define  MAINPANEL_STRING_3               126     /* control type: string, callback function: (none) */
#define  MAINPANEL_STRING                 127     /* control type: string, callback function: (none) */
#define  MAINPANEL_CH_S1                  128     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_LAN_TIMER              129     /* control type: timer, callback function: LanTimer */
#define  MAINPANEL_SPLITTER_5             130     /* control type: splitter, callback function: (none) */
#define  MAINPANEL_GRAPH6                 131     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_GRAPH5                 132     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_GRAPH4                 133     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_GRAPH3                 134     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_GRAPH2                 135     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_GRAPH1                 136     /* control type: graph, callback function: Graph1 */
#define  MAINPANEL_ERRVIEW                137     /* control type: command, callback function: ErrView */
#define  MAINPANEL_A_START                138     /* control type: command, callback function: A_Start */
#define  MAINPANEL_KEYBOARD               139     /* control type: command, callback function: Keyboard */
#define  MAINPANEL_LISTBOX                140     /* control type: listBox, callback function: (none) */
#define  MAINPANEL_A_TABLE_3              141     /* control type: table, callback function: (none) */
#define  MAINPANEL_SCAN_DATA              142     /* control type: string, callback function: (none) */
#define  MAINPANEL_TEXT_DATA_3            143     /* control type: string, callback function: (none) */
#define  MAINPANEL_TEXT_DATA_2            144     /* control type: string, callback function: (none) */
#define  MAINPANEL_TEXT_DATA_1            145     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_7             146     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_6             147     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_5             148     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_3             149     /* control type: string, callback function: (none) */
#define  MAINPANEL_STRING_2               150     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_2             151     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA_4             152     /* control type: string, callback function: (none) */
#define  MAINPANEL_BAR_DATA               153     /* control type: string, callback function: (none) */
#define  MAINPANEL_A_TABLE_2              154     /* control type: table, callback function: (none) */
#define  MAINPANEL_A_TABLE                155     /* control type: table, callback function: A_Table */
#define  MAINPANEL_SPLITTER_15            156     /* control type: splitter, callback function: (none) */
#define  MAINPANEL_SPLITTER               157     /* control type: splitter, callback function: (none) */
#define  MAINPANEL_IMAGE_CAP              158     /* control type: command, callback function: Image_Cap */
#define  MAINPANEL_LAN_TRANS              159     /* control type: command, callback function: Lan_Trans */
#define  MAINPANEL_COMP_VALUE             160     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_RINGCH                 161     /* control type: string, callback function: (none) */
#define  MAINPANEL_TEXTMSG_4              162     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_3              163     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_DECORATION_3           164     /* control type: deco, callback function: (none) */
#define  MAINPANEL_TAB                    165     /* control type: tab, callback function: (none) */
#define  MAINPANEL_DECO_2                 166     /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECO_1                 167     /* control type: deco, callback function: (none) */
#define  MAINPANEL_A_WORK3                168     /* control type: LED, callback function: (none) */
#define  MAINPANEL_A_WORK2                169     /* control type: LED, callback function: (none) */
#define  MAINPANEL_A_WORK1                170     /* control type: LED, callback function: (none) */
#define  MAINPANEL_SELECT_MEAS            171     /* control type: textButton, callback function: Select_Meas */
#define  MAINPANEL_SELECT_NG_INT          172     /* control type: textButton, callback function: Sw_Int */
#define  MAINPANEL_LED_MC_3               173     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED                    174     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_MC_4               175     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_MC_2               176     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_2                  177     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_MC_1               178     /* control type: LED, callback function: (none) */
#define  MAINPANEL_DECORATION_5           179     /* control type: deco, callback function: (none) */
#define  MAINPANEL_MARKLED                180     /* control type: LED, callback function: (none) */
#define  MAINPANEL_MENU_BT                181     /* control type: command, callback function: Menu_Bt */
#define  MAINPANEL_RESULTVIEW0            182     /* control type: command, callback function: ResultView0 */
#define  MAINPANEL_MODELSETUP0            183     /* control type: command, callback function: ModelSetup0 */
#define  MAINPANEL_ZEROSETUP0             184     /* control type: command, callback function: ZeroSetup0 */
#define  MAINPANEL_MANUALCTRL0            185     /* control type: command, callback function: ManualCtrl0 */
#define  MAINPANEL_MARKING_CHAR           186     /* control type: string, callback function: (none) */
#define  MAINPANEL_BF_MARKING             187     /* control type: string, callback function: (none) */
#define  MAINPANEL_DECORATION_7           188     /* control type: deco, callback function: (none) */
#define  MAINPANEL_TEXTMSG_5              189     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_9              190     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_MENU_BT1               191     /* control type: command, callback function: Menu_Bt */
#define  MAINPANEL_A_DATAVIEW             192     /* control type: command, callback function: A_Dataview */
#define  MAINPANEL_LIST_STATUS            193     /* control type: command, callback function: List_Status */
#define  MAINPANEL_RESULTVIEW1            194     /* control type: command, callback function: ResultView0 */
#define  MAINPANEL_MODELSETUP1            195     /* control type: command, callback function: ModelSetup0 */
#define  MAINPANEL_ZEROSETUP1             196     /* control type: command, callback function: ZeroSetup0 */
#define  MAINPANEL_MANUALCTRL_2           197     /* control type: command, callback function: ManualCtrl_2 */
#define  MAINPANEL_CLOSE                  198     /* control type: command, callback function: Close */
#define  MAINPANEL_MANUALCTRL1            199     /* control type: command, callback function: ManualCtrl0 */
#define  MAINPANEL_RING                   200     /* control type: ring, callback function: (none) */
#define  MAINPANEL_DECORATION_8           201     /* control type: deco, callback function: (none) */
#define  MAINPANEL_ENC                    202     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_NICK_LED               203     /* control type: LED, callback function: (none) */
#define  MAINPANEL_DATA_TABLE             204     /* control type: table, callback function: (none) */
#define  MAINPANEL_INWORK_COUNT           205     /* control type: numeric, callback function: Inwork_Count */
#define  MAINPANEL_MCID_VIEW              206     /* control type: ring, callback function: Mcid_View */
#define  MAINPANEL_DECORATION_9           207     /* control type: deco, callback function: (none) */
#define  MAINPANEL_CWSCR                  208     /* control type: binary, callback function: Cwscr */
#define  MAINPANEL_NG_VIEW                209     /* control type: binary, callback function: Ng_View */
#define  MAINPANEL_PICTURE_2              210     /* control type: picture, callback function: (none) */
#define  MAINPANEL_MODEL_TL               211     /* control type: textButton, callback function: (none) */
#define  MAINPANEL_MODEL_EPB              212     /* control type: textButton, callback function: (none) */
#define  MAINPANEL_MODEL_WD               213     /* control type: textButton, callback function: (none) */
#define  MAINPANEL_MODEL_LR               214     /* control type: textButton, callback function: (none) */
#define  MAINPANEL_NET_DATA               215     /* control type: string, callback function: (none) */
#define  MAINPANEL_LED_3                  216     /* control type: LED, callback function: (none) */
#define  MAINPANEL_RING_2                 217     /* control type: ring, callback function: View_DTV */
#define  MAINPANEL_FAIL_CNT               218     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_ALARM_DELETE           219     /* control type: command, callback function: Alarm_Delete */
#define  MAINPANEL_ALARM_LIST             220     /* control type: textBox, callback function: (none) */
#define  MAINPANEL_STATUS_BOX             221     /* control type: listBox, callback function: (none) */
#define  MAINPANEL_DECORATION             222     /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECORATION_10          223     /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECORATION_12          224     /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECORATION_11          225     /* control type: deco, callback function: (none) */
#define  MAINPANEL_DECORATION_4           226     /* control type: deco, callback function: (none) */
#define  MAINPANEL_OPERATE_NO             227     /* control type: ring, callback function: Operate_No */
#define  MAINPANEL_RESET_MC               228     /* control type: command, callback function: Reset_Mc */
#define  MAINPANEL_LED_6                  229     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_5                  230     /* control type: LED, callback function: (none) */
#define  MAINPANEL_LED_7                  231     /* control type: LED, callback function: (none) */
#define  MAINPANEL_HHMMSS_3               232     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_HHMMSS_4               233     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_MMDDYY                 234     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_HHMMSS                 235     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_18             236     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_LED_8                  237     /* control type: LED, callback function: (none) */
#define  MAINPANEL_ZERO_NOW               238     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_TEXTMSG_7              239     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_TEXTMSG_6              240     /* control type: textMsg, callback function: (none) */
#define  MAINPANEL_ZERO_CNT               241     /* control type: numeric, callback function: (none) */
#define  MAINPANEL_PICTURE                242     /* control type: picture, callback function: MeasPointEvent */
#define  MAINPANEL_DECORATION_6           243     /* control type: deco, callback function: (none) */
#define  MAINPANEL_B2                     244     /* control type: string, callback function: B2_Select */
#define  MAINPANEL_B1                     245     /* control type: string, callback function: B1_Select */

#define  MENUPANEL                        4
#define  MENUPANEL_STRING                 2       /* control type: string, callback function: (none) */
#define  MENUPANEL_CLOSE_MENU             3       /* control type: command, callback function: Close_Menu */
#define  MENUPANEL_MENU_7                 4       /* control type: command, callback function: Menu_7 */
#define  MENUPANEL_MENU_6                 5       /* control type: command, callback function: Menu_6 */
#define  MENUPANEL_MENU_5                 6       /* control type: command, callback function: Menu_5 */
#define  MENUPANEL_MENU_4                 7       /* control type: command, callback function: Menu_4 */
#define  MENUPANEL_MENU_3                 8       /* control type: command, callback function: Menu_3 */
#define  MENUPANEL_MENU_2                 9       /* control type: command, callback function: Menu_2 */
#define  MENUPANEL_MENU_1                 10      /* control type: command, callback function: Menu_1 */

#define  PW                               5       /* callback function: cbPW */
#define  PW_PW_2                          2       /* control type: string, callback function: Pw2 */
#define  PW_MAXLENGTH                     3       /* control type: numeric, callback function: (none) */
#define  PW_MASK                          4       /* control type: string, callback function: (none) */
#define  PW_PWVALUE                       5       /* control type: string, callback function: (none) */
#define  PW_PW                            6       /* control type: string, callback function: Pw */
#define  PW_DECORATION_4                  7       /* control type: deco, callback function: (none) */
#define  PW_COMMANDBUTTON                 8       /* control type: command, callback function: Pw */
#define  PW_DECORATION                    9       /* control type: deco, callback function: (none) */
#define  PW_CANCEL                        10      /* control type: command, callback function: Pw */
#define  PW_PWCHANGE1                     11      /* control type: string, callback function: Pw */
#define  PW_PWCHANGE2                     12      /* control type: string, callback function: Pw */
#define  PW_DECORATION_3                  13      /* control type: deco, callback function: (none) */
#define  PW_PWCHANGE_OLD                  14      /* control type: textButton, callback function: (none) */
#define  PW_PWVIEWS                       15      /* control type: command, callback function: Pw */
#define  PW_PWVIEWU                       16      /* control type: command, callback function: Pw */
#define  PW_PWCHANGE                      17      /* control type: textButton, callback function: Pw */

     /* tab page panel controls */
#define  TABPANEL_SPLITTER_6              2       /* control type: splitter, callback function: (none) */
#define  TABPANEL_LED_OUT_3               3       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_OUT_2               4       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_OUT_1               5       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_IN_4                6       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_IN_3                7       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_IN_2                8       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_11             9       /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_10             10      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_13             11      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_12             12      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_9              13      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_8              14      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_7              15      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_6              16      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_5              17      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_4              18      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_3              19      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_2              20      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_DATA_1              21      /* control type: LED, callback function: (none) */
#define  TABPANEL_LED_IN_1                22      /* control type: LED, callback function: (none) */
#define  TABPANEL_SPLITTER                23      /* control type: splitter, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_2_LISTBOX               2       /* control type: listBox, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MAINMENU                 2
#define  MENUBAR_MAINMENU_AUTOMENU        3       /* callback function: MENU_Main */
#define  MENUBAR_MAINMENU_MANUMENU        4       /* callback function: MENU_Manual */
#define  MENUBAR_MAINMENU_ZEROMENU        5       /* callback function: MENU_Zeroset */
#define  MENUBAR_MAINMENU_W_MENU          6
#define  MENUBAR_MAINMENU_W_MENU_SUBMENU  7
#define  MENUBAR_MAINMENU_W_MENU_WORKSEL  8       /* callback function: MENU_Worksel */
#define  MENUBAR_MAINMENU_W_MENU_EQUMENU  9       /* callback function: Menu_Equ */
#define  MENUBAR_MAINMENU_EXITMENU        10      /* callback function: Exit_Menu */
#define  MENUBAR_SYSMENU                  11
#define  MENUBAR_SYSMENU_MARKMENU         12      /* callback function: Mark_Menu */
#define  MENUBAR_SYSMENU_CALMENU          13      /* callback function: Calib_Menu */
#define  MENUBAR_SYSMENU_COMMENU          14      /* callback function: Comm_Menu */
#define  MENUBAR_SYSMENU_LANMENU          15      /* callback function: Lan_Menu */
#define  MENUBAR_SYSMENU_POSIMENU         16      /* callback function: Posi_Menu */
#define  MENUBAR_SYSMENU_ERRMENU          17      /* callback function: Err_Menu */
#define  MENUBAR_SYSMENU_NG_CLEAR         18      /* callback function: Ng_Clear */
#define  MENUBAR_INTERFACE                19
#define  MENUBAR_INTERFACE_WORK_DATA      20      /* callback function: Work_Data */
#define  MENUBAR_INTERFACE_INTER_DATA     21      /* callback function: Inter_Data */
#define  MENUBAR_HELPMMENU                22

#define  MENUBAR_2                        2
#define  MENUBAR_2_FILE                   2
#define  MENUBAR_2_FILE_SAVE_MC           3       /* callback function: Save_Mc */
#define  MENUBAR_2_FILE_LOAD_MC           4       /* callback function: Load_Mc */
#define  MENUBAR_2_TOOLS                  5
#define  MENUBAR_2_TOOLS_ITEM1            6       /* callback function: Clear_Cmt */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Table(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Alarm_Delete(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Amp_No(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Amp_On(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AmpTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK B1_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK B2_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Calib_Event(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Calib_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Calibration_Master1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Calibration_Master2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbDateTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cbPW(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Clear_Cmt(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close_Menu(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Comm_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Cwscr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DatapanelCall(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Err_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ErrView(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Exit_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Graph1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Image_Cap(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Inter_Data(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Inwork_Count(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Lan_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Lan_Trans(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LanTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK List_Status(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Load_Mc(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK MainCtrl0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MainPanelEvent(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Mark_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Mcid_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasPointEvent(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Menu_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Menu_Equ(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK MENU_Main(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK MENU_Manual(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK MENU_Worksel(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK MENU_Zeroset(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ModelSetup0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Ng_Clear(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Ng_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Operate_No(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PlcTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Posi_Menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Pw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pw2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Reset_Mc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResultView0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Save_Mc(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Select_Meas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SPCSelect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sw_Int(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TestTime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TotalTestNo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Update1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK View_DTV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK View_garph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Work_Data(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK ZeroSetup0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
