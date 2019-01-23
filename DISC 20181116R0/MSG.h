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
#define  INTPANEL_CLOSE                   4       /* control type: command, callback function: Close */
#define  INTPANEL_CWSTYLE                 5       /* control type: ring, callback function: CwStyle */
#define  INTPANEL_COLOR1                  6       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR2                  7       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_STOREVALIDDAY1          8       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SETCONTNG1              9       /* control type: numeric, callback function: (none) */
#define  INTPANEL_COLOR3                  10      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR4                  11      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_ZEROSETHOUR             12      /* control type: numeric, callback function: (none) */
#define  INTPANEL_ZEROSETINTERVAL         13      /* control type: numeric, callback function: (none) */
#define  INTPANEL_NG_CHK_FLAG1            14      /* control type: radioButton, callback function: ContNgChkFlagCallback2 */
#define  INTPANEL_COLOR5                  15      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_BYPASS4                 16      /* control type: textButton, callback function: ByPass2_4 */
#define  INTPANEL_BYPASS2                 17      /* control type: textButton, callback function: ByPass2_2 */
#define  INTPANEL_BYPASS6                 18      /* control type: textButton, callback function: ByPass2_6 */
#define  INTPANEL_BYPASS5                 19      /* control type: textButton, callback function: ByPass2_5 */
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
#define  INTPANEL_A_DATAVIEW7             36      /* control type: command, callback function: A_Dataview7 */
#define  INTPANEL_ZERO_SET7               37      /* control type: command, callback function: Zero_Set7 */
#define  INTPANEL_REFER_BT5               38      /* control type: command, callback function: Refer_Bt5 */
#define  INTPANEL_MANUALCTRL7             39      /* control type: command, callback function: Manualctrl7 */
#define  INTPANEL_INTONG_3                40      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTONG_2                41      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_35           42      /* control type: deco, callback function: (none) */
#define  INTPANEL_GRAPHONOFF              43      /* control type: textButton, callback function: GraphOnOff */
#define  INTPANEL_COUNTONOFF              44      /* control type: textButton, callback function: CountOnOff */
#define  INTPANEL_SPCONOFF2               45      /* control type: textButton, callback function: SpcOnOff3 */
#define  INTPANEL_INTONG_1                46      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_3                47      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_2                48      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_1                49      /* control type: ring, callback function: (none) */
#define  INTPANEL_CUSTOM_COLOR_LABEL      50      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_3                51      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_15              52      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_2                53      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_14              54      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_12              55      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_1                56      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_33           57      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_32           58      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_3                59      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_34           60      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_31           61      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_30           62      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_22           63      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_24           64      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_28           65      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_26           66      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_27           67      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_25           68      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_23           69      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_19           70      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_2                71      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_13              72      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTNOK_1                73      /* control type: ring, callback function: (none) */
#define  INTPANEL_LANGUAGE                74      /* control type: slide, callback function: setLanguage2 */
#define  INTPANEL_INTOK_3                 75      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_2                 76      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_1                 77      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_3                78      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_2                79      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_1                80      /* control type: ring, callback function: (none) */
#define  INTPANEL_M_POPUP                 81      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH4             82      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH3             83      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH2             84      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_ANGLE_DATA              85      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH1             86      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_SEL_GRAPH               87      /* control type: radioButton, callback function: Sel_Graph */
#define  INTPANEL_MEAS_FOLD               88      /* control type: string, callback function: (none) */
#define  INTPANEL_DECORATION_6            89      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_3            90      /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_2               91      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG                 92      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_3               93      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_POS_4             94      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_3             95      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_2             96      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_1             97      /* control type: numeric, callback function: (none) */
#define  INTPANEL_TEXTMSG_9               98      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_7               99      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_ALL_SAVE          100     /* control type: command, callback function: Servo_All_Save */
#define  INTPANEL_ENC_CHANNEL             101     /* control type: numeric, callback function: Enc_Channel */
#define  INTPANEL_ENC_PLS_NUM             102     /* control type: numeric, callback function: Enc_Pls_Num */
#define  INTPANEL_NICK_COMP_4             103     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_3             104     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_2             105     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP               106     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ROLLER_DIA              107     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_WORK_DIA                108     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ENC_DIR                 109     /* control type: ring, callback function: Enc_Dir2 */
#define  INTPANEL_NICK_CUT                110     /* control type: numeric, callback function: Nick_Cut_Set */
#define  INTPANEL_NICK_VALUE_3            111     /* control type: numeric, callback function: Nick_Value_Set3 */
#define  INTPANEL_NICK_VALUE_2            112     /* control type: numeric, callback function: Nick_Value_Set2 */
#define  INTPANEL_NICK_VALUE              113     /* control type: numeric, callback function: Nick_Value_Set */
#define  INTPANEL_TEXTMSG_4               114     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_Z_PHASE_USE             115     /* control type: radioButton, callback function: Z_Phase_Set */
#define  INTPANEL_DECORATION              116     /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_10              117     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_DECORATION_10           118     /* control type: deco, callback function: (none) */
#define  INTPANEL_ROT_CIRCLE              119     /* control type: numeric, callback function: (none) */
#define  INTPANEL_DECORATION_11           120     /* control type: deco, callback function: (none) */
#define  INTPANEL_DTV_2D                  121     /* control type: command, callback function: (none) */
#define  INTPANEL_RUNOUT_2D               122     /* control type: command, callback function: (none) */
#define  INTPANEL_PROFILE_3D              123     /* control type: command, callback function: Profile_3d */
#define  INTPANEL_ORDER_LIMIT             124     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CUT              125     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CNT              126     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_ONOFF            127     /* control type: binary, callback function: (none) */
#define  INTPANEL_ORDER_PER               128     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_L                129     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_H                130     /* control type: numeric, callback function: (none) */
#define  INTPANEL_LINE_NAME               131     /* control type: numeric, callback function: (none) */
#define  INTPANEL_RESET_MC                132     /* control type: command, callback function: Reset_Mc2 */
#define  INTPANEL_MODEL_CHANGE_SET        133     /* control type: radioButton, callback function: (none) */
#define  INTPANEL_CYCLE_DELAY             134     /* control type: numeric, callback function: (none) */
#define  INTPANEL_WORKMODE                135     /* control type: textButton, callback function: (none) */
#define  INTPANEL_INSPECT                 136     /* control type: textButton, callback function: Inspect */
#define  INTPANEL_A_RETRY                 137     /* control type: textButton, callback function: AUTO_Retry2 */
#define  INTPANEL_DOOR_ONOFF              138     /* control type: textButton, callback function: (none) */
#define  INTPANEL_NIGHT_CHAR              139     /* control type: string, callback function: (none) */
#define  INTPANEL_DAY_CHAR                140     /* control type: string, callback function: (none) */

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
#define  MARK_SET_MARKPOSX                9       /* control type: numeric, callback function: MarkPosXCallback */
#define  MARK_SET_MARKSETCHK              10      /* control type: command, callback function: MarkStrSetChkCallback */
#define  MARK_SET_MARKTRANS_2             11      /* control type: command, callback function: MarkTestStrSend2 */
#define  MARK_SET_MARKTRANS               12      /* control type: command, callback function: MarkTestStrSend */
#define  MARK_SET_MARKWDLIMIT             13      /* control type: numeric, callback function: MarkWidthLimitCallback */
#define  MARK_SET_DECORATION_16           14      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKDIR                 15      /* control type: ring, callback function: MarkDirCallback */
#define  MARK_SET_MARKSTART_2             16      /* control type: command, callback function: Dot_Start */
#define  MARK_SET_WORK_NAME               17      /* control type: string, callback function: (none) */
#define  MARK_SET_MARKPITCH               18      /* control type: numeric, callback function: MarkPitchCallback */
#define  MARK_SET_MARKSTART               19      /* control type: command, callback function: MarkStartCallback */
#define  MARK_SET_MARK_VEL_3              20      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_VEL_2              21      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_VEL_1              22      /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION              23      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKFONT                24      /* control type: ring, callback function: MarkFontCallback */
#define  MARK_SET_MARKHEIGHT              25      /* control type: numeric, callback function: MarkHeightCallback */
#define  MARK_SET_MARKTESTSTR             26      /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_30           27      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_8            28      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_TEXTMSG_16              29      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_MARK_TEXT_24            30      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_23            31      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_22            32      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_21            33      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_20            34      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_19            35      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_18            36      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_17            37      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_16            38      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_15            39      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_14            40      /* control type: string, callback function: (none) */
#define  MARK_SET_A_DATAVIEW4             41      /* control type: command, callback function: A_Dataview4 */
#define  MARK_SET_ZERO_SET4               42      /* control type: command, callback function: Zero_Set4 */
#define  MARK_SET_REFER_BT4               43      /* control type: command, callback function: Refer_Bt4 */
#define  MARK_SET_MANUALCTRL4             44      /* control type: command, callback function: Manualctrl4 */
#define  MARK_SET_MARK_TEXT_13            45      /* control type: string, callback function: (none) */
#define  MARK_SET_SAVE_MARK               46      /* control type: command, callback function: (none) */
#define  MARK_SET_DECORATION_35           47      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_TEXT_12            48      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_11            49      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_10            50      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_9             51      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_8             52      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_SIZE_8             53      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_8                54      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_8                55      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_8                56      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_7            57      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_7             58      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TEXT_7             59      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_7                60      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_7                61      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_7                62      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_6             63      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_6            64      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_6             65      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_6                66      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_6                67      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_5             68      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_6                69      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_5            70      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_5             71      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_5                72      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_5                73      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_4             74      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_5                75      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_9            76      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_4            77      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_4             78      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_4                79      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_4                80      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_24           81      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_10           82      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_24            83      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_23           84      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_4                85      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_23            86      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_22           87      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_3            88      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_22            89      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_21           90      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_3             91      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_21            92      /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_20           93      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_3             94      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_20            95      /* control type: ring, callback function: Mark_Type_Func_20 */
#define  MARK_SET_MARK_ONOFF_19           96      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Z_3                97      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_19            98      /* control type: ring, callback function: Mark_Type_Func_19 */
#define  MARK_SET_MARK_ONOFF_18           99      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_11           100     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_18            101     /* control type: ring, callback function: Mark_Type_Func_18 */
#define  MARK_SET_MARK_ONOFF_17           102     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Y_3                103     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_17            104     /* control type: ring, callback function: Mark_Type_Func_17 */
#define  MARK_SET_MARK_ONOFF_16           105     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_3                106     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_16            107     /* control type: ring, callback function: Mark_Type_Func_16 */
#define  MARK_SET_MARK_ONOFF_15           108     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_2            109     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_15            110     /* control type: ring, callback function: Mark_Type_Func_15 */
#define  MARK_SET_MARK_ONOFF_14           111     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_2             112     /* control type: numeric, callback function: (none) */
#define  MARK_SET_WORK_MODEL_CHAR2        113     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_14            114     /* control type: ring, callback function: Mark_Type_Func_14 */
#define  MARK_SET_MARK_ONOFF_13           115     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_2             116     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_13            117     /* control type: ring, callback function: Mark_Type_Func_13 */
#define  MARK_SET_MARK_ONOFF_12           118     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Z_2                119     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_12            120     /* control type: ring, callback function: Mark_Type_Func_12 */
#define  MARK_SET_MARK_Y_2                121     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_11            122     /* control type: ring, callback function: Mark_Type_Func_11 */
#define  MARK_SET_MARK_X_2                123     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_10            124     /* control type: ring, callback function: Mark_Type_Func_10 */
#define  MARK_SET_MARK_ONOFF_1            125     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_9             126     /* control type: ring, callback function: Mark_Type_Func_9 */
#define  MARK_SET_MARK_ROT_8              127     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_7              128     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_6              129     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_5              130     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_4              131     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_3              132     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_2              133     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_1              134     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_8             135     /* control type: ring, callback function: Mark_Type_Func_8 */
#define  MARK_SET_MARK_TYPE_7             136     /* control type: ring, callback function: Mark_Type_Func_7 */
#define  MARK_SET_MARK_SPACE_1            137     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_1             138     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_6             139     /* control type: ring, callback function: Mark_Type_Func_6 */
#define  MARK_SET_MARK_TYPE_5             140     /* control type: ring, callback function: Mark_Type_Func_5 */
#define  MARK_SET_MARK_TYPE_4             141     /* control type: ring, callback function: Mark_Type_Func_4 */
#define  MARK_SET_MARK_TYPE_3             142     /* control type: ring, callback function: Mark_Type_Func_3 */
#define  MARK_SET_MARK_TYPE_2             143     /* control type: ring, callback function: Mark_Type_Func_2 */
#define  MARK_SET_MARK_TYPE_1             144     /* control type: ring, callback function: Mark_Type_Func */
#define  MARK_SET_MARK_TEXT_1             145     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_1                146     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_1                147     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_1                148     /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION_2            149     /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG_30              150     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_31              151     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_27              152     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_28              153     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_29              154     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_34              155     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG                 156     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_33              157     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_21              158     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_22              159     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_23              160     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_12             161     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_13             162     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_14             163     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_15             164     /* control type: splitter, callback function: (none) */
#define  MARK_SET_TEXTMSG_24              165     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_25              166     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_11             167     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_10             168     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_8              169     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER_9              170     /* control type: splitter, callback function: (none) */
#define  MARK_SET_SPLITTER                171     /* control type: splitter, callback function: (none) */
#define  MARK_SET_TEXTMSG_26              172     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_5              173     /* control type: splitter, callback function: (none) */
#define  MARK_SET_STRING_3                174     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING_4                175     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING_2                176     /* control type: string, callback function: (none) */
#define  MARK_SET_STRING                  177     /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_22           178     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_17           179     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_18           180     /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG_32              181     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_DECORATION_20           182     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_4            183     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_21           184     /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_BT_4               185     /* control type: command, callback function: Mark_Bt_4 */
#define  MARK_SET_MARK_BT_3               186     /* control type: command, callback function: Mark_Bt_3 */
#define  MARK_SET_MARK_BT_2               187     /* control type: command, callback function: Mark_Bt_2 */
#define  MARK_SET_MARK_BT_1               188     /* control type: command, callback function: Mark_Bt_1 */

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
#define  WORKREF_SERVO_POS_21             2       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_20             3       /* control type: numeric, callback function: (none) */
#define  WORKREF_CLOSE                    4       /* control type: command, callback function: Close */
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
#define  WORKREF_OIL_TIME                 20      /* control type: numeric, callback function: (none) */
#define  WORKREF_DRY_TIME                 21      /* control type: numeric, callback function: (none) */
#define  WORKREF_ORDER_SAVE_NO            22      /* control type: numeric, callback function: (none) */
#define  WORKREF_WASH_TIME                23      /* control type: numeric, callback function: (none) */
#define  WORKREF_MODELS_8                 24      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_7                 25      /* control type: radioButton, callback function: (none) */
#define  WORKREF_DECORATION_30            26      /* control type: deco, callback function: (none) */
#define  WORKREF_MODELS_6                 27      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_16               28      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_28            29      /* control type: deco, callback function: (none) */
#define  WORKREF_MODELS_5                 30      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_14               31      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_29            32      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_27            33      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_15               34      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_4                 35      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_13               36      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_3                 37      /* control type: radioButton, callback function: (none) */
#define  WORKREF_DECORATION_26            38      /* control type: deco, callback function: (none) */
#define  WORKREF_MARK_SET5                39      /* control type: command, callback function: Mark_Set5 */
#define  WORKREF_MODELS_2                 40      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_1                 41      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_12               42      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_6             43      /* control type: deco, callback function: (none) */
#define  WORKREF_A_DATAVIEW5              44      /* control type: command, callback function: A_Dataview5 */
#define  WORKREF_ZERO_SET5                45      /* control type: command, callback function: Zero_Set5 */
#define  WORKREF_REFER_BT5                46      /* control type: command, callback function: Refer_bt5 */
#define  WORKREF_MANUALCTRL5              47      /* control type: command, callback function: Manualctrl5 */
#define  WORKREF_LED_L_10                 48      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_9                  49      /* control type: LED, callback function: (none) */
#define  WORKREF_BYPASS_5                 50      /* control type: textButton, callback function: ByPass5 */
#define  WORKREF_BYPASS_4                 51      /* control type: textButton, callback function: ByPass4 */
#define  WORKREF_BYPASS_3                 52      /* control type: textButton, callback function: ByPass3 */
#define  WORKREF_SAVE_MODEL_REF           53      /* control type: command, callback function: Save_Model_Ref */
#define  WORKREF_BYPASS_2                 54      /* control type: textButton, callback function: ByPass2 */
#define  WORKREF_BYPASS_1                 55      /* control type: textButton, callback function: ByPass1 */
#define  WORKREF_LED_L_8                  56      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_7                  57      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_6                  58      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_5                  59      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_4                  60      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_3                  61      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_2                  62      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_1                  63      /* control type: LED, callback function: (none) */
#define  WORKREF_SCALE_NO                 64      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_7              65      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_6              66      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_5              67      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_4              68      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_3              69      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_2              70      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_1              71      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_ALL_SAVE           72      /* control type: command, callback function: Servo_All_Save1 */
#define  WORKREF_STRING_4                 73      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_5                 74      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_3                 75      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_2                 76      /* control type: string, callback function: (none) */
#define  WORKREF_DECORATION_14            77      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_2             78      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_13            79      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_25            80      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_3             81      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_10               82      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_12            83      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG                  84      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_18            85      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_23            86      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_24            87      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_22            88      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_20            89      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_21            90      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_15            91      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_16            92      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_2                93      /* control type: textMsg, callback function: (none) */
#define  WORKREF_ZERO_CHECK               94      /* control type: ring, callback function: Zero_Check */
#define  WORKREF_LR_CHECK_2               95      /* control type: ring, callback function: Lr_Check2 */
#define  WORKREF_BARCODE_CHECK            96      /* control type: ring, callback function: Barcode_Check */
#define  WORKREF_LR_CHECK                 97      /* control type: ring, callback function: Lr_Check */
#define  WORKREF_ENC_DIR4                 98      /* control type: ring, callback function: Enc_Dir4 */
#define  WORKREF_ENC_DIR2                 99      /* control type: ring, callback function: Enc_Dir3 */
#define  WORKREF_TEXTMSG_11               100     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_3                101     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_8                102     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_9                103     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_6                104     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_4                105     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_5                106     /* control type: textMsg, callback function: (none) */
#define  WORKREF_PICTURE                  107     /* control type: picture, callback function: (none) */
#define  WORKREF_WORK_MODEL_CHAR2         108     /* control type: string, callback function: (none) */
#define  WORKREF_ANGLE_SAVE_ON            109     /* control type: textButton, callback function: (none) */
#define  WORKREF_ORDER_SAVE_ON            110     /* control type: textButton, callback function: (none) */
#define  WORKREF_A_RO_LOW                 111     /* control type: textButton, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Dataview5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Dataview7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK GraphOnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Inspect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IntPanelEvent(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lan_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK logpanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK Refer_Bt4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_Bt5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rename0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Reset_Mc2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_Model_Ref(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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
int  CVICALLBACK Zero_Set4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Set5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Set7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif