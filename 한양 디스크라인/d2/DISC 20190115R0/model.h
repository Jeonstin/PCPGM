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

#define  EQUSETUP                         1       /* callback function: callEqusetup */
#define  EQUSETUP_CLOSE                   2       /* control type: command, callback function: Close */
#define  EQUSETUP_EQUATION                3       /* control type: table, callback function: EquationDataSetup */
#define  EQUSETUP_VIEW_2                  4       /* control type: ring, callback function: (none) */
#define  EQUSETUP_VIEW                    5       /* control type: ring, callback function: (none) */
#define  EQUSETUP_MODE                    6       /* control type: ring, callback function: (none) */
#define  EQUSETUP_UNIT                    7       /* control type: ring, callback function: (none) */
#define  EQUSETUP_TEXTMSG                 8       /* control type: textMsg, callback function: (none) */
#define  EQUSETUP_TEXTBOX                 9       /* control type: textBox, callback function: (none) */
#define  EQUSETUP_TEXTMSG_2               10      /* control type: textMsg, callback function: (none) */

#define  MODELSETUP                       2       /* callback function: callModelsetup */
#define  MODELSETUP_REMOVEWORKER          2       /* control type: command, callback function: Remove */
#define  MODELSETUP_RENAMEWORKER          3       /* control type: command, callback function: Rename */
#define  MODELSETUP_ADDWORKER             4       /* control type: command, callback function: Add */
#define  MODELSETUP_RENAMEMODEL           5       /* control type: command, callback function: Rename */
#define  MODELSETUP_REMOVEMODEL           6       /* control type: command, callback function: Remove */
#define  MODELSETUP_CHANGEMODEL           7       /* control type: command, callback function: ChangeOn */
#define  MODELSETUP_ADDMODEL              8       /* control type: command, callback function: Add */
#define  MODELSETUP_DATA                  9       /* control type: table, callback function: ModelDataSetup */
#define  MODELSETUP_MODEL                 10      /* control type: ring, callback function: ModelSetup */
#define  MODELSETUP_WORKER                11      /* control type: ring, callback function: WorkerSetup */
#define  MODELSETUP_TEXTMSG_2             12      /* control type: textMsg, callback function: (none) */
#define  MODELSETUP_TEXTMSG               13      /* control type: textMsg, callback function: (none) */
#define  MODELSETUP_DECORATION_2          14      /* control type: deco, callback function: (none) */
#define  MODELSETUP_MODEL_CHAR_5          15      /* control type: string, callback function: (none) */
#define  MODELSETUP_MODEL_CHAR_4          16      /* control type: string, callback function: (none) */
#define  MODELSETUP_MODEL_CHAR_3          17      /* control type: string, callback function: (none) */
#define  MODELSETUP_MODEL_CHAR_2          18      /* control type: string, callback function: (none) */
#define  MODELSETUP_MODEL_CHAR_1          19      /* control type: string, callback function: (none) */
#define  MODELSETUP_CLOSE                 20      /* control type: command, callback function: Close */
#define  MODELSETUP_DECORATION_4          21      /* control type: deco, callback function: (none) */
#define  MODELSETUP_SERVO_POS_7           22      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_6           23      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_5           24      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_4           25      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_3           26      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_2           27      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_SERVO_POS_1           28      /* control type: numeric, callback function: (none) */
#define  MODELSETUP_DECORATION_3          29      /* control type: deco, callback function: (none) */
#define  MODELSETUP_STRING                30      /* control type: string, callback function: (none) */
#define  MODELSETUP_MODELLIST2            31      /* control type: listBox, callback function: (none) */
#define  MODELSETUP_MODELLIST             32      /* control type: listBox, callback function: Modellist */
#define  MODELSETUP_DECORATION            33      /* control type: deco, callback function: (none) */
#define  MODELSETUP_CHANGEFINISH          34      /* control type: command, callback function: ChangeFinish */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callEqusetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callModelsetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChangeFinish(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChangeOn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EquationDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Modellist(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rename(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkerSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
