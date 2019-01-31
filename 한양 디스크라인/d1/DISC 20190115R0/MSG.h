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
#define  COMM_SET_AUX4PORT                2       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX3PORT                3       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX2PORT                4       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX1PORT                5       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PLCPORT                 6       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PORTPAR                 7       /* control type: command, callback function: PortPar1 */
#define  COMM_SET_AMPPORT                 8       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_CLOSE                   9       /* control type: command, callback function: Close */
#define  COMM_SET_AMPMODEL                10      /* control type: ring, callback function: SysSetup2 */
#define  COMM_SET_AMPCABLE                11      /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_DECORATION              12      /* control type: deco, callback function: (none) */
#define  COMM_SET_TEXTMSG_3               13      /* control type: textMsg, callback function: (none) */
#define  COMM_SET_TABLE                   14      /* control type: table, callback function: (none) */

#define  ERR_SET                          3       /* callback function: Err_Set */
#define  ERR_SET_EMSG                     2       /* control type: table, callback function: (none) */
#define  ERR_SET_CLOSE                    3       /* control type: command, callback function: Close */

#define  ERRPANEL                         4       /* callback function: ErrMsgCallback */
#define  ERRPANEL_LISTBOX                 2       /* control type: listBox, callback function: (none) */
#define  ERRPANEL_TIMER                   3       /* control type: timer, callback function: ErrChkTimerCallback */

#define  INTPANEL                         5       /* callback function: IntPanelEvent */
#define  INTPANEL_SPCSIGMA2               2       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SPCDATANO2              3       /* control type: numeric, callback function: (none) */
#define  INTPANEL_CWSTYLE                 4       /* control type: ring, callback function: CwStyle */
#define  INTPANEL_COLOR1                  5       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR2                  6       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_STOREVALIDDAY1          7       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SETCONTNG1              8       /* control type: numeric, callback function: (none) */
#define  INTPANEL_COLOR3                  9       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR4                  10      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_ZEROSETHOUR             11      /* control type: numeric, callback function: (none) */
#define  INTPANEL_ZEROSETINTERVAL         12      /* control type: numeric, callback function: (none) */
#define  INTPANEL_NG_CHK_FLAG1            13      /* control type: radioButton, callback function: ContNgChkFlagCallback2 */
#define  INTPANEL_COLOR5                  14      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_BYPASS4                 15      /* control type: textButton, callback function: ByPass2_4 */
#define  INTPANEL_BYPASS2                 16      /* control type: textButton, callback function: ByPass2_2 */
#define  INTPANEL_BYPASS6                 17      /* control type: textButton, callback function: ByPass2_6 */
#define  INTPANEL_BYPASS5                 18      /* control type: textButton, callback function: ByPass2_5 */
#define  INTPANEL_CLOSE                   19      /* control type: command, callback function: Close */
#define  INTPANEL_BYPASS3                 20      /* control type: textButton, callback function: ByPass2_3 */
#define  INTPANEL_STRING_6                21      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_5                22      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_4                23      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_3                24      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_2                25      /* control type: string, callback function: (none) */
#define  INTPANEL_TEXTMSG_11              26      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SEPFILE                 27      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_STRING                  28      /* control type: string, callback function: (none) */
#define  INTPANEL_ZSET_HOUR               29      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_ZSET_CNT                30      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_NIGHTWORKSTART2         31      /* control type: string, callback function: (none) */
#define  INTPANEL_NIGHTWORKSTART          32      /* control type: string, callback function: (none) */
#define  INTPANEL_DAYWORKSTART            33      /* control type: string, callback function: (none) */
#define  INTPANEL_MASTER_RPT              34      /* control type: numeric, callback function: (none) */
#define  INTPANEL_CWSURFACE               35      /* control type: radioButton, callback function: SurfaceCallback */
#define  INTPANEL_INTONG_3                36      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTONG_2                37      /* control type: ring, callback function: (none) */
#define  INTPANEL_COUNTONOFF              38      /* control type: textButton, callback function: CountOnOff */
#define  INTPANEL_SPCONOFF2               39      /* control type: textButton, callback function: SpcOnOff3 */
#define  INTPANEL_INTONG_1                40      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_3                41      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_2                42      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_1                43      /* control type: ring, callback function: (none) */
#define  INTPANEL_CUSTOM_COLOR_LABEL      44      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_3                45      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_15              46      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_2                47      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_14              48      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_12              49      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_1                50      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_33           51      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_32           52      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_3                53      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_31           54      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_30           55      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_22           56      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_24           57      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_28           58      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_26           59      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_27           60      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_25           61      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_23           62      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_19           63      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_2                64      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_13              65      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTNOK_1                66      /* control type: ring, callback function: (none) */
#define  INTPANEL_LANGUAGE                67      /* control type: slide, callback function: setLanguage2 */
#define  INTPANEL_INTOK_3                 68      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_2                 69      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_1                 70      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_3                71      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_2                72      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_1                73      /* control type: ring, callback function: (none) */
#define  INTPANEL_M_POPUP                 74      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH4             75      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH3             76      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH2             77      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_ANGLE_DATA              78      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH1             79      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_SEL_GRAPH               80      /* control type: radioButton, callback function: Sel_Graph */
#define  INTPANEL_MEAS_FOLD               81      /* control type: string, callback function: (none) */
#define  INTPANEL_DECORATION_6            82      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_3            83      /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_2               84      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG                 85      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_3               86      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_POS_4             87      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_3             88      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_2             89      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_1             90      /* control type: numeric, callback function: (none) */
#define  INTPANEL_TEXTMSG_9               91      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_7               92      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_ALL_SAVE          93      /* control type: command, callback function: Servo_All_Save */
#define  INTPANEL_ENC_CHANNEL             94      /* control type: numeric, callback function: Enc_Channel */
#define  INTPANEL_ENC_PLS_NUM             95      /* control type: numeric, callback function: Enc_Pls_Num */
#define  INTPANEL_NICK_COMP_4             96      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_3             97      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_2             98      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP               99      /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ROLLER_DIA              100     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_WORK_DIA                101     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ENC_DIR                 102     /* control type: ring, callback function: Enc_Dir2 */
#define  INTPANEL_NICK_CUT                103     /* control type: numeric, callback function: Nick_Cut_Set */
#define  INTPANEL_NICK_VALUE_3            104     /* control type: numeric, callback function: Nick_Value_Set3 */
#define  INTPANEL_NICK_VALUE_2            105     /* control type: numeric, callback function: Nick_Value_Set2 */
#define  INTPANEL_NICK_VALUE              106     /* control type: numeric, callback function: Nick_Value_Set */
#define  INTPANEL_TEXTMSG_4               107     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_Z_PHASE_USE             108     /* control type: radioButton, callback function: Z_Phase_Set */
#define  INTPANEL_DECORATION              109     /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_10              110     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_DECORATION_10           111     /* control type: deco, callback function: (none) */
#define  INTPANEL_ROT_CIRCLE              112     /* control type: numeric, callback function: (none) */
#define  INTPANEL_DECORATION_11           113     /* control type: deco, callback function: (none) */
#define  INTPANEL_DTV_2D                  114     /* control type: command, callback function: (none) */
#define  INTPANEL_RUNOUT_2D               115     /* control type: command, callback function: (none) */
#define  INTPANEL_PROFILE_3D              116     /* control type: command, callback function: Profile_3d */
#define  INTPANEL_ORDER_LIMIT             117     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CUT              118     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CNT              119     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_ONOFF            120     /* control type: binary, callback function: (none) */
#define  INTPANEL_ORDER_PER               121     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_L                122     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_H                123     /* control type: numeric, callback function: (none) */
#define  INTPANEL_LINE_NAME               124     /* control type: numeric, callback function: (none) */
#define  INTPANEL_RESET_MC                125     /* control type: command, callback function: Reset_Mc2 */
#define  INTPANEL_MODEL_CHANGE_SET        126     /* control type: radioButton, callback function: (none) */
#define  INTPANEL_CYCLE_DELAY             127     /* control type: numeric, callback function: (none) */
#define  INTPANEL_WORKMODE                128     /* control type: textButton, callback function: (none) */
#define  INTPANEL_INSPECT                 129     /* control type: textButton, callback function: Inspect */
#define  INTPANEL_A_RETRY                 130     /* control type: textButton, callback function: AUTO_Retry2 */
#define  INTPANEL_DOOR_ONOFF              131     /* control type: textButton, callback function: (none) */
#define  INTPANEL_NIGHT_CHAR              132     /* control type: string, callback function: (none) */
#define  INTPANEL_DAY_CHAR                133     /* control type: string, callback function: (none) */

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
#define  MARK_SET_MARKPOSZ                9       /* control type: numeric, callback function: MarkPosXCallback */
#define  MARK_SET_MARKPOSX                10      /* control type: numeric, callback function: MarkPosXCallback */
#define  MARK_SET_MARKSETCHK              11      /* control type: command, callback function: MarkStrSetChkCallback */
#define  MARK_SET_MARKTRANS_2             12      /* control type: command, callback function: MarkTestStrSend2 */
#define  MARK_SET_MARKTRANS               13      /* control type: command, callback function: MarkTestStrSend */
#define  MARK_SET_MARKWDLIMIT             14      /* control type: numeric, callback function: MarkWidthLimitCallback */
#define  MARK_SET_DECORATION_16           15      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKDIR                 16      /* control type: ring, callback function: MarkDirCallback */
#define  MARK_SET_MARKSTART_2             17      /* control type: command, callback function: Dot_Start */
#define  MARK_SET_MARKPITCH               18      /* control type: numeric, callback function: MarkPitchCallback */
#define  MARK_SET_MARKSTART               19      /* control type: command, callback function: MarkStartCallback */
#define  MARK_SET_DECORATION              20      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKFONT                21      /* control type: ring, callback function: MarkFontCallback */
#define  MARK_SET_MARKHEIGHT              22      /* control type: numeric, callback function: MarkHeightCallback */
#define  MARK_SET_MARKTESTSTR             23      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_8            24      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_8              25      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_24            26      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_23            27      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_22            28      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_21            29      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_20            30      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_19            31      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_18            32      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_17            33      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_16            34      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_15            35      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_14            36      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_13            37      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_12            38      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_11            39      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_10            40      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_9             41      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_8             42      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_8                43      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_8                44      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_8                45      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_7            46      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_7              47      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_7             48      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_7                49      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_7                50      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_7                51      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_6            52      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_6              53      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_6             54      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_6                55      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_6                56      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_6                57      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_5            58      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_5              59      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_5             60      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_5                61      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_5                62      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_5                63      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_9            64      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_4            65      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_4              66      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TEXT_4             67      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_4                68      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_4                69      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_24           70      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_10           71      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_24            72      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_23           73      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_4                74      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_23            75      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_22           76      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_3            77      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_22            78      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_21           79      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_3              80      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_21            81      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_20           82      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_3             83      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_20            84      /* control type: ring, callback function: Mark_Type_Func_20 */
#define  MARK_SET_MARK_ONOFF_19           85      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Z_3                86      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_19            87      /* control type: ring, callback function: Mark_Type_Func_19 */
#define  MARK_SET_MARK_ONOFF_18           88      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_11           89      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_18            90      /* control type: ring, callback function: Mark_Type_Func_18 */
#define  MARK_SET_MARK_ONOFF_17           91      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Y_3                92      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_17            93      /* control type: ring, callback function: Mark_Type_Func_17 */
#define  MARK_SET_MARK_ONOFF_16           94      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_3                95      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_16            96      /* control type: ring, callback function: Mark_Type_Func_16 */
#define  MARK_SET_MARK_ONOFF_15           97      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_2            98      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_15            99      /* control type: ring, callback function: Mark_Type_Func_15 */
#define  MARK_SET_MARK_ONOFF_14           100     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_2              101     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_14            102     /* control type: ring, callback function: Mark_Type_Func_14 */
#define  MARK_SET_MARK_ONOFF_13           103     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_2             104     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_13            105     /* control type: ring, callback function: Mark_Type_Func_13 */
#define  MARK_SET_MARK_ONOFF_12           106     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Z_2                107     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_12            108     /* control type: ring, callback function: Mark_Type_Func_12 */
#define  MARK_SET_MARK_Y_2                109     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_11            110     /* control type: ring, callback function: Mark_Type_Func_11 */
#define  MARK_SET_MARK_X_2                111     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_10            112     /* control type: ring, callback function: Mark_Type_Func_10 */
#define  MARK_SET_MARK_ONOFF_1            113     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_9             114     /* control type: ring, callback function: Mark_Type_Func_9 */
#define  MARK_SET_MARK_ROT_1              115     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_8             116     /* control type: ring, callback function: Mark_Type_Func_8 */
#define  MARK_SET_MARK_TYPE_7             117     /* control type: ring, callback function: Mark_Type_Func_7 */
#define  MARK_SET_MARK_TYPE_6             118     /* control type: ring, callback function: Mark_Type_Func_6 */
#define  MARK_SET_MARK_TYPE_5             119     /* control type: ring, callback function: Mark_Type_Func_5 */
#define  MARK_SET_MARK_TYPE_4             120     /* control type: ring, callback function: Mark_Type_Func_4 */
#define  MARK_SET_MARK_TYPE_3             121     /* control type: ring, callback function: Mark_Type_Func_3 */
#define  MARK_SET_MARK_TYPE_2             122     /* control type: ring, callback function: Mark_Type_Func_2 */
#define  MARK_SET_MARK_TYPE_1             123     /* control type: ring, callback function: Mark_Type_Func */
#define  MARK_SET_MARK_TEXT_1             124     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_1                125     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_1                126     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_1                127     /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION_2            128     /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG_30              129     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_31              130     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_27              131     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_28              132     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_29              133     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG                 134     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_21              135     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_22              136     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_23              137     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_12             138     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_13             139     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_14             140     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_15             141     /* control type: splitter, callback function: (none) */
#define  MARK_SET_TEXTMSG_24              142     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_25              143     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_11             144     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_10             145     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_8              146     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_9              147     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER                148     /* control type: splitter, callback function: (none) */
#define  MARK_SET_TEXTMSG_26              149     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_5              150     /* control type: splitter, callback function: (none) */
#define  MARK_SET_STRING_3                151     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING_4                152     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING_2                153     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING                  154     /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_22           155     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_17           156     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_18           157     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_19           158     /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG_32              159     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_DECORATION_20           160     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_4            161     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_21           162     /* control type: deco, callback function: (none) */

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
#define  WORKREF_WORK_NAME                17      /* control type: string, callback function: (none) */
#define  WORKREF_MODELS_10                18      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_9                 19      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_8                 20      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_7                 21      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_6                 22      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_5                 23      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_4                 24      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_3                 25      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_2                 26      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_1                 27      /* control type: radioButton, callback function: (none) */
#define  WORKREF_LED_L_10                 28      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_9                  29      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_8                  30      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_7                  31      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_6                  32      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_5                  33      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_4                  34      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_3                  35      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_2                  36      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_1                  37      /* control type: LED, callback function: (none) */
#define  WORKREF_SCALE_NO                 38      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_7              39      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_6              40      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_5              41      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_4              42      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_3              43      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_2              44      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_1              45      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_ALL_SAVE           46      /* control type: command, callback function: Servo_All_Save1 */
#define  WORKREF_STRING_4                 47      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_5                 48      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_3                 49      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_2                 50      /* control type: string, callback function: (none) */
#define  WORKREF_DECORATION_14            51      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_2             52      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_13            53      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_25            54      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_3             55      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_10               56      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_12            57      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG                  58      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_18            59      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_23            60      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_24            61      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_22            62      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_20            63      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_21            64      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_15            65      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_16            66      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_2                67      /* control type: textMsg, callback function: (none) */
#define  WORKREF_ZERO_CHECK               68      /* control type: ring, callback function: Zero_Check */
#define  WORKREF_LR_CHECK_2               69      /* control type: ring, callback function: Lr_Check2 */
#define  WORKREF_BARCODE_CHECK            70      /* control type: ring, callback function: Barcode_Check */
#define  WORKREF_LR_CHECK                 71      /* control type: ring, callback function: Lr_Check */
#define  WORKREF_ENC_DIR4                 72      /* control type: ring, callback function: Enc_Dir4 */
#define  WORKREF_ENC_DIR2                 73      /* control type: ring, callback function: Enc_Dir3 */
#define  WORKREF_TEXTMSG_11               74      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_3                75      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_8                76      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_9                77      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_6                78      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_4                79      /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_5                80      /* control type: textMsg, callback function: (none) */
#define  WORKREF_PICTURE                  81      /* control type: picture, callback function: (none) */


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
int  CVICALLBACK Barcode_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ColorCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Comm_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CountOnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CwStyle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Dot_Start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Channel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Pls_Num(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EncRatioset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Err_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrChkTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrMsgCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Inspect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IntPanelEvent(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lan_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK logpanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_12(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_13(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_14(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_15(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_16(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_17(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_18(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_19(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_20(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK MarkTestStrSend2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkWidthLimitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Master_Retry(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK Reset_Mc2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sel_Graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SurfaceCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Switch_LanUse1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Work_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkerSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Z_Phase_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
