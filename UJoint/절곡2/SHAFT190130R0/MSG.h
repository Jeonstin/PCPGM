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

#define  COMCONFIG1                       1
#define  COMCONFIG1_COMPORT               2       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_TEXTMSG_10            3       /* control type: textMsg, callback function: (none) */
#define  COMCONFIG1_CTSMODE               4       /* control type: binary, callback function: PortSetup1 */
#define  COMCONFIG1_XMODE                 5       /* control type: binary, callback function: PortSetup1 */
#define  COMCONFIG1_BAUDRATE              6       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_PARITY                7       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_DATABITS              8       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_STOPBITS              9       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_DECORATION            10      /* control type: deco, callback function: (none) */
#define  COMCONFIG1_INPUTQ                11      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_OUTPUTQ               12      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_TIMEOUT               13      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_CLOSE                 14      /* control type: command, callback function: Close */
#define  COMCONFIG1_TIMEOUT_MSG1          15      /* control type: textMsg, callback function: (none) */
#define  COMCONFIG1_SPLITTER_3            16      /* control type: splitter, callback function: (none) */
#define  COMCONFIG1_SPLITTER_2            17      /* control type: splitter, callback function: (none) */
#define  COMCONFIG1_SPLITTER              18      /* control type: splitter, callback function: (none) */

#define  COMM_SET                         2       /* callback function: Comm_Set */
#define  COMM_SET_AUX2PORT                2       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX1PORT                3       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PLCPORT                 4       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PORTPAR                 5       /* control type: command, callback function: PortPar1 */
#define  COMM_SET_AMPPORT                 6       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_CLOSE                   7       /* control type: command, callback function: Close */
#define  COMM_SET_AMPMODEL                8       /* control type: ring, callback function: SysSetup2 */
#define  COMM_SET_AMPCABLE                9       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_DECORATION              10      /* control type: deco, callback function: (none) */
#define  COMM_SET_TEXTMSG_3               11      /* control type: textMsg, callback function: (none) */
#define  COMM_SET_TABLE                   12      /* control type: table, callback function: (none) */

#define  ERR_SET                          3       /* callback function: Err_Set */
#define  ERR_SET_EMSG                     2       /* control type: table, callback function: (none) */
#define  ERR_SET_CLOSE                    3       /* control type: command, callback function: Close */

#define  ERRPANEL                         4       /* callback function: ErrMsgCallback */
#define  ERRPANEL_LISTBOX                 2       /* control type: listBox, callback function: (none) */
#define  ERRPANEL_TIMER                   3       /* control type: timer, callback function: ErrChkTimerCallback */

#define  INTPANEL                         5       /* callback function: IntPanelEvent */
#define  INTPANEL_SPCSIGMA2               2       /* control type: numeric, callback function: SpcSigma2 */
#define  INTPANEL_SPCDATANO2              3       /* control type: numeric, callback function: SpcDataNo2 */
#define  INTPANEL_CWSTYLE                 4       /* control type: ring, callback function: CwStyle */
#define  INTPANEL_COLOR1                  5       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR2                  6       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_STOREVALIDDAY1          7       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SETCONTNG1              8       /* control type: numeric, callback function: SetContNg */
#define  INTPANEL_COLOR3                  9       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR4                  10      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_ZEROSETHOUR             11      /* control type: numeric, callback function: ZeroSetHour */
#define  INTPANEL_ZEROSETINTERVAL         12      /* control type: numeric, callback function: ZeroSetInterval */
#define  INTPANEL_NG_CHK_FLAG1            13      /* control type: radioButton, callback function: ContNgChkFlagCallback2 */
#define  INTPANEL_COLOR5                  14      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_BYPASS6                 15      /* control type: textButton, callback function: ByPass6 */
#define  INTPANEL_BYPASS5                 16      /* control type: textButton, callback function: ByPass2_5 */
#define  INTPANEL_CLOSE                   17      /* control type: command, callback function: Close */
#define  INTPANEL_BYPASS3                 18      /* control type: textButton, callback function: ByPass2_3 */
#define  INTPANEL_STRING_6                19      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_5                20      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_4                21      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_3                22      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_2                23      /* control type: string, callback function: (none) */
#define  INTPANEL_TEXTMSG_11              24      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SEPFILE                 25      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_STRING                  26      /* control type: string, callback function: (none) */
#define  INTPANEL_ZSET_HOUR               27      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_ZSET_CNT                28      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_NIGHTWORKSTART2         29      /* control type: string, callback function: (none) */
#define  INTPANEL_NIGHTWORKSTART          30      /* control type: string, callback function: (none) */
#define  INTPANEL_DAYWORKSTART            31      /* control type: string, callback function: (none) */
#define  INTPANEL_MASTER_RPT              32      /* control type: numeric, callback function: Master_Rpt */
#define  INTPANEL_CWSURFACE               33      /* control type: radioButton, callback function: SurfaceCallback */
#define  INTPANEL_INTONG_3                34      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTONG_2                35      /* control type: ring, callback function: (none) */
#define  INTPANEL_SPCONOFF2               36      /* control type: textButton, callback function: SpcOnOff3 */
#define  INTPANEL_INTONG_1                37      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_3                38      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_2                39      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_1                40      /* control type: ring, callback function: (none) */
#define  INTPANEL_CUSTOM_COLOR_LABEL      41      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_3                42      /* control type: ring, callback function: (none) */
#define  INTPANEL_A_RETRY                 43      /* control type: binary, callback function: AUTO_Retry2 */
#define  INTPANEL_INTPNG_2                44      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_12              45      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_1                46      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNOK_3                47      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_29           48      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_22           49      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_24           50      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_28           51      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_27           52      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_25           53      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_23           54      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_19           55      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_2                56      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_13              57      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTNOK_1                58      /* control type: ring, callback function: (none) */
#define  INTPANEL_LANGUAGE                59      /* control type: slide, callback function: setLanguage2 */
#define  INTPANEL_INTOK_3                 60      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_2                 61      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_1                 62      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_3                63      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_2                64      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_1                65      /* control type: ring, callback function: (none) */
#define  INTPANEL_M_POPUP                 66      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH4             67      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH3             68      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH2             69      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_ANGLE_DATA              70      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH1             71      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_SEL_GRAPH               72      /* control type: radioButton, callback function: Sel_Graph */
#define  INTPANEL_MEAS_FOLD               73      /* control type: string, callback function: (none) */
#define  INTPANEL_DECORATION_6            74      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_3            75      /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_2               76      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG                 77      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_3               78      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_POS_4             79      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_3             80      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_2             81      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_1             82      /* control type: numeric, callback function: (none) */
#define  INTPANEL_TEXTMSG_9               83      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_7               84      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_ALL_SAVE          85      /* control type: command, callback function: Servo_All_Save */
#define  INTPANEL_ENC_CHANNEL             86      /* control type: numeric, callback function: Enc_Channel */
#define  INTPANEL_ENC_PLS_NUM             87      /* control type: numeric, callback function: Enc_Pls_Num */
#define  INTPANEL_NICK_COMP_4             88      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_3             89      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_2             90      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP               91      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ROLLER_DIA              92      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_WORK_DIA                93      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ENC_DIR                 94      /* control type: ring, callback function: Enc_Dir2 */
#define  INTPANEL_NICK_CUT                95      /* control type: numeric, callback function: Nick_Cut_Set */
#define  INTPANEL_NICK_VALUE_3            96      /* control type: numeric, callback function: Nick_Value_Set3 */
#define  INTPANEL_NICK_VALUE_2            97      /* control type: numeric, callback function: Nick_Value_Set2 */
#define  INTPANEL_NICK_VALUE              98      /* control type: numeric, callback function: Nick_Value_Set */
#define  INTPANEL_TEXTMSG_4               99      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_Z_PHASE_USE             100     /* control type: radioButton, callback function: Z_Phase_Set */
#define  INTPANEL_DECORATION              101     /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_10              102     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_DECORATION_10           103     /* control type: deco, callback function: (none) */
#define  INTPANEL_ROT_CIRCLE              104     /* control type: numeric, callback function: (none) */
#define  INTPANEL_DECORATION_11           105     /* control type: deco, callback function: (none) */
#define  INTPANEL_DTV_2D                  106     /* control type: command, callback function: (none) */
#define  INTPANEL_RUNOUT_2D               107     /* control type: command, callback function: (none) */
#define  INTPANEL_PROFILE_3D              108     /* control type: command, callback function: Profile_3d */
#define  INTPANEL_ORDER_LIMIT             109     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CUT              110     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CNT              111     /* control type: numeric, callback function: (none) */
#define  INTPANEL_DOOR_ONOFF              112     /* control type: binary, callback function: (none) */
#define  INTPANEL_FILTER_ONOFF            113     /* control type: binary, callback function: (none) */
#define  INTPANEL_ORDER_PER               114     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_L                115     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_H                116     /* control type: numeric, callback function: (none) */
#define  INTPANEL_LINE_NAME               117     /* control type: numeric, callback function: (none) */
#define  INTPANEL_LOWLOG                  118     /* control type: binary, callback function: (none) */
#define  INTPANEL_DATA_WEIGHT             119     /* control type: numeric, callback function: Keypad */
#define  INTPANEL_TOGGLEBUTTON            120     /* control type: textButton, callback function: (none) */

#define  LAN_SET                          6       /* callback function: Lan_Set */
#define  LAN_SET_CLOSE                    2       /* control type: command, callback function: Close */
#define  LAN_SET_TEXTMSG_10               3       /* control type: textMsg, callback function: (none) */
#define  LAN_SET_SERVERIP_2               4       /* control type: string, callback function: (none) */
#define  LAN_SET_SERVERIP                 5       /* control type: string, callback function: (none) */
#define  LAN_SET_PORTNO                   6       /* control type: numeric, callback function: (none) */
#define  LAN_SET_CYCLEDATATIME            7       /* control type: numeric, callback function: (none) */
#define  LAN_SET_SWITCH_LANUSE            8       /* control type: binary, callback function: Switch_LanUse1 */
#define  LAN_SET_CYCLEDATASTR             9       /* control type: string, callback function: (none) */
#define  LAN_SET_DECORATION               10      /* control type: deco, callback function: (none) */
#define  LAN_SET_KEYBOARD                 11      /* control type: command, callback function: Keyboard */
#define  LAN_SET_CONNECT_MARK             12      /* control type: command, callback function: Connect_Mark */

#define  LOGPANEL                         7       /* callback function: logpanelCallback */
#define  LOGPANEL_LISTBOX                 2       /* control type: listBox, callback function: (none) */

#define  MARK_SET                         8       /* callback function: Mark_Set */
#define  MARK_SET_TEXTMSG_12              2       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_20              3       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_CLOSE                   4       /* control type: command, callback function: Close */
#define  MARK_SET_TEXTMSG_9               5       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_MARKRESET               6       /* control type: command, callback function: MarkResetCallback */
#define  MARK_SET_MARKPOSY                7       /* control type: numeric, callback function: MarkPosYCallback */
#define  MARK_SET_MARKSTOP                8       /* control type: command, callback function: MarkStopCallback */
#define  MARK_SET_MARKPOSX                9       /* control type: numeric, callback function: MarkPosXCallback */
#define  MARK_SET_MARKSETCHK              10      /* control type: command, callback function: MarkStrSetChkCallback */
#define  MARK_SET_MARKTRANS               11      /* control type: command, callback function: MarkTestStrSend */
#define  MARK_SET_MARKWDLIMIT             12      /* control type: numeric, callback function: MarkWidthLimitCallback */
#define  MARK_SET_DECORATION_16           13      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKDIR                 14      /* control type: ring, callback function: MarkDirCallback */
#define  MARK_SET_MARKPITCH               15      /* control type: numeric, callback function: MarkPitchCallback */
#define  MARK_SET_MARKSTART               16      /* control type: command, callback function: MarkStartCallback */
#define  MARK_SET_DECORATION              17      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKFONT                18      /* control type: ring, callback function: MarkFontCallback */
#define  MARK_SET_MARKHEIGHT              19      /* control type: numeric, callback function: MarkHeightCallback */
#define  MARK_SET_MARKTESTSTR             20      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_8            21      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_8              22      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_8             23      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_8                24      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_8                25      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_8                26      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_7            27      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_7              28      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_7             29      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_7                30      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_7                31      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_7                32      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_6            33      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_6              34      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_6             35      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_6                36      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_6                37      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_6                38      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_5            39      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_5              40      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_5             41      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_5                42      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_5                43      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_5                44      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_4            45      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_4              46      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_4             47      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_4                48      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_4                49      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_4                50      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_3            51      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_3              52      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_3             53      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_3                54      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_3                55      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_3                56      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_2            57      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_2              58      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_2             59      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_2                60      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_2                61      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_2                62      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_1            63      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_1              64      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_8             65      /* control type: ring, callback function: Mark_Type_Func_8 */
#define  MARK_SET_MARK_TYPE_7             66      /* control type: ring, callback function: Mark_Type_Func_7 */
#define  MARK_SET_MARK_TYPE_6             67      /* control type: ring, callback function: Mark_Type_Func_6 */
#define  MARK_SET_MARK_TYPE_5             68      /* control type: ring, callback function: Mark_Type_Func_5 */
#define  MARK_SET_MARK_TYPE_4             69      /* control type: ring, callback function: Mark_Type_Func_4 */
#define  MARK_SET_MARK_TYPE_3             70      /* control type: ring, callback function: Mark_Type_Func_3 */
#define  MARK_SET_MARK_TYPE_2             71      /* control type: ring, callback function: Mark_Type_Func_2 */
#define  MARK_SET_MARK_TYPE_1             72      /* control type: ring, callback function: Mark_Type_Func */
#define  MARK_SET_MARK_TEXT_1             73      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_1                74      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_1                75      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_1                76      /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION_2            77      /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG                 78      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_21              79      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_22              80      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_23              81      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_24              82      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_25              83      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER                84      /* control type: splitter, callback function: (none) */
#define  MARK_SET_TEXTMSG_26              85      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_5              86      /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_4              87      /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_3              88      /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_2              89      /* control type: splitter, callback function: (none) */

#define  MSGPANEL                         9       /* callback function: msgpanelcallback */
#define  MSGPANEL_COMMANDBUTTON           2       /* control type: command, callback function: msgclose */
#define  MSGPANEL_TEXTMSG                 3       /* control type: textMsg, callback function: (none) */
#define  MSGPANEL_TIMER                   4       /* control type: timer, callback function: msgtimercallback */

#define  OPT_SET                          10      /* callback function: Opt_Set */
#define  OPT_SET_SPCSIGMA1                2       /* control type: numeric, callback function: (none) */
#define  OPT_SET_SPCDATANO1               3       /* control type: numeric, callback function: (none) */
#define  OPT_SET_CLOSE                    4       /* control type: command, callback function: Close */
#define  OPT_SET_AIRUSECH_2               5       /* control type: numeric, callback function: (none) */
#define  OPT_SET_AIRUSECH                 6       /* control type: numeric, callback function: (none) */
#define  OPT_SET_STOREVALIDDAY1           7       /* control type: numeric, callback function: (none) */
#define  OPT_SET_SETCONTNG1               8       /* control type: numeric, callback function: (none) */
#define  OPT_SET_PRT_DIR1                 9       /* control type: binary, callback function: (none) */
#define  OPT_SET_DECORATION_6             10      /* control type: deco, callback function: (none) */
#define  OPT_SET_ZEROSETHOUR              11      /* control type: numeric, callback function: (none) */
#define  OPT_SET_ZEROSETINTERVAL          12      /* control type: numeric, callback function: (none) */
#define  OPT_SET_NG_CHK_FLAG1             13      /* control type: radioButton, callback function: ContNgChkFlagCallback1 */
#define  OPT_SET_DECORATION_5             14      /* control type: deco, callback function: (none) */
#define  OPT_SET_BYPASS5                  15      /* control type: textButton, callback function: ByPass5 */
#define  OPT_SET_BYPASS4                  16      /* control type: textButton, callback function: ByPass4 */
#define  OPT_SET_BYPASS3                  17      /* control type: textButton, callback function: ByPass3 */
#define  OPT_SET_BYPASS2                  18      /* control type: textButton, callback function: ByPass2 */
#define  OPT_SET_BYPASS                   19      /* control type: textButton, callback function: ByPass1 */
#define  OPT_SET_SPCONOFF1                20      /* control type: textButton, callback function: SpcOnOff1 */
#define  OPT_SET_DECORATION_7             21      /* control type: deco, callback function: (none) */
#define  OPT_SET_KEYBOARD                 22      /* control type: command, callback function: Keyboard */
#define  OPT_SET_TEXTMSG_7                23      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_SEPFILE                  24      /* control type: radioButton, callback function: (none) */
#define  OPT_SET_MEAS_METHOD              25      /* control type: binary, callback function: (none) */
#define  OPT_SET_ZSET_HOUR                26      /* control type: radioButton, callback function: ZeroSetMode */
#define  OPT_SET_ZSET_CNT                 27      /* control type: radioButton, callback function: ZeroSetMode */
#define  OPT_SET_NIGHTWORKSTART2          28      /* control type: string, callback function: (none) */
#define  OPT_SET_NIGHTWORKSTART           29      /* control type: string, callback function: (none) */
#define  OPT_SET_DAYWORKSTART             30      /* control type: string, callback function: (none) */
#define  OPT_SET_MASTER_RPT               31      /* control type: numeric, callback function: (none) */
#define  OPT_SET_RE_TRY                   32      /* control type: binary, callback function: Master_Retry */
#define  OPT_SET_MAX_COMP                 33      /* control type: numeric, callback function: (none) */
#define  OPT_SET_TEXTMSG_8                34      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_10            35      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_REVERSE                36      /* control type: binary, callback function: A_Reverse */
#define  OPT_SET_TEXTMSG_12               37      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_21            38      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_MEAS_MODE              39      /* control type: binary, callback function: A_Meas_Mode */
#define  OPT_SET_TEXTMSG_13               40      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_22            41      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_RETRY                  42      /* control type: binary, callback function: AUTO_Retry */
#define  OPT_SET_DECORATION_23            43      /* control type: deco, callback function: (none) */
#define  OPT_SET_TEXTMSG_9                44      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_18            45      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_17            46      /* control type: deco, callback function: (none) */
#define  OPT_SET_LASER_TYPE               47      /* control type: string, callback function: (none) */
#define  OPT_SET_DECORATION_16            48      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_12            49      /* control type: deco, callback function: (none) */
#define  OPT_SET_TEXTMSG_11               50      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_TEXTMSG_10               51      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_13            52      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_14            53      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_20            54      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_19            55      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_15            56      /* control type: deco, callback function: (none) */
#define  OPT_SET_MUL_NO                   57      /* control type: numeric, callback function: (none) */
#define  OPT_SET_LANGUAGE                 58      /* control type: slide, callback function: setLanguage */
#define  OPT_SET_NICK_STEP                59      /* control type: numeric, callback function: (none) */
#define  OPT_SET_DRYTIME                  60      /* control type: numeric, callback function: (none) */
#define  OPT_SET_WASHTIME                 61      /* control type: numeric, callback function: (none) */

#define  POS_SET                          11      /* callback function: Pos_Set */
#define  POS_SET_CLOSE                    2       /* control type: command, callback function: Close */
#define  POS_SET_TABLE1                   3       /* control type: table, callback function: (none) */
#define  POS_SET_KEYBOARD                 4       /* control type: command, callback function: Keyboard */

#define  WORK_SET                         12      /* callback function: Work_Set */
#define  WORK_SET_CLOSE                   2       /* control type: command, callback function: Close */
#define  WORK_SET_MODEL1                  3       /* control type: ring, callback function: WorkSetup10 */
#define  WORK_SET_WORKER1                 4       /* control type: ring, callback function: WorkerSetup10 */
#define  WORK_SET_DECORATION_2            5       /* control type: deco, callback function: (none) */
#define  WORK_SET_DECORATION              6       /* control type: deco, callback function: (none) */
#define  WORK_SET_ADDWORKER1              7       /* control type: command, callback function: Add_worker */
#define  WORK_SET_RENAMEWORKER            8       /* control type: command, callback function: Rename0 */
#define  WORK_SET_REMOVEWORKER            9       /* control type: command, callback function: Remove0 */
#define  WORK_SET_REMOVEMODEL             10      /* control type: command, callback function: Remove0 */
#define  WORK_SET_RENAMEWORK              11      /* control type: command, callback function: Rename0 */
#define  WORK_SET_ADDMODEL                12      /* control type: command, callback function: Add0 */
#define  WORK_SET_KEYBOARD                13      /* control type: command, callback function: Keyboard */

#define  WORKREF                          13
#define  WORKREF_CLOSE                    2       /* control type: command, callback function: Close */
#define  WORKREF_SERVO_POS_21             3       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_20             4       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_19             5       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_18             6       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_17             7       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_16             8       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_15             9       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_14             10      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_13             11      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_12             12      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_11             13      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_10             14      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_9              15      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_8              16      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_7              17      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_6              18      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_5              19      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_4              20      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_3              21      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_2              22      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_1              23      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_ALL_SAVE           24      /* control type: command, callback function: Servo_All_Save1 */
#define  WORKREF_DECORATION_11            25      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_10            26      /* control type: deco, callback function: (none) */
#define  WORKREF_TUBE2_HIGH               27      /* control type: numeric, callback function: Tube2_Hdata */
#define  WORKREF_TUBE2_LOW                28      /* control type: numeric, callback function: Tube2_Ldata */
#define  WORKREF_TUBE_HIGH                29      /* control type: numeric, callback function: Tube_Hdata */
#define  WORKREF_TUBE_LOW                 30      /* control type: numeric, callback function: Tube_Ldata */
#define  WORKREF_SHAFT2_HIGH              31      /* control type: numeric, callback function: Shaft2_Hdata */
#define  WORKREF_SHAFT2_LOW               32      /* control type: numeric, callback function: Shaft2_Ldata */
#define  WORKREF_SHAFT_HIGH               33      /* control type: numeric, callback function: Shaft_Hdata */
#define  WORKREF_YAXIS_LOW                34      /* control type: numeric, callback function: Yaxis_Low */
#define  WORKREF_SHAFT_LOW                35      /* control type: numeric, callback function: Shaft_Ldata */
#define  WORKREF_YAXIS_HIGH               36      /* control type: numeric, callback function: Yaxis_High */
#define  WORKREF_TEXTMSG                  37      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_2                38      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_12            39      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION               40      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_3                41      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_4                42      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_5                43      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_7                44      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_6                45      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_8                46      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_9                47      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_13            48      /* control type: deco, callback function: (none) */
#define  WORKREF_M_DATA_WEIGHT_5          49      /* control type: numeric, callback function: M_Data_Weight5 */
#define  WORKREF_M_DATA_WEIGHT_4          50      /* control type: numeric, callback function: M_Data_Weight4 */
#define  WORKREF_M_DATA_WEIGHT_3          51      /* control type: numeric, callback function: M_Data_Weight3 */
#define  WORKREF_M_DATA_WEIGHT            52      /* control type: numeric, callback function: M_Data_Weight */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Meas_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Reverse(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Add0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Add_worker(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_Retry(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_Retry2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ColorCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Comm_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Connect_Mark(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CwStyle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Channel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Pls_Num(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EncRatioset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Err_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrChkTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrMsgCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IntPanelEvent(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keypad(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lan_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK logpanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Data_Weight(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Data_Weight3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Data_Weight4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Data_Weight5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkDirCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkFontCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkHeightCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPitchCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPosXCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPosYCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkResetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStrSetChkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkTestStrSend(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkWidthLimitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Master_Retry(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Master_Rpt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgclose(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgpanelcallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgtimercallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Cut_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Opt_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PortPar1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PortSetup1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Profile_3d(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rename0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sel_Graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetContNg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Shaft2_Hdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Shaft2_Ldata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Shaft_Hdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Shaft_Ldata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcDataNo2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcSigma2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SurfaceCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Switch_LanUse1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tube2_Hdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tube2_Ldata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tube_Hdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tube_Ldata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Work_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkerSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Yaxis_High(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Yaxis_Low(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Z_Phase_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetHour(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetInterval(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
