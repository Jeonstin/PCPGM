/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2011. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  KEY                              1       /* callback function: keypanelfun */
#define  KEY_BS                           2       /* callback function: fbs */
#define  KEY_CLR                          3       /* callback function: fclr */
#define  KEY_ESC                          4       /* callback function: fesc */
#define  KEY_DOT                          5       /* callback function: fdot */
#define  KEY_ENTER                        6       /* callback function: fenter */
#define  KEY_BLANK                        7       /* callback function: fblank */
#define  KEY_KEY0                         8       /* callback function: fzero */
#define  KEY_YY                           9       /* callback function: fyy */
#define  KEY_ZZ                           10      /* callback function: fzz */
#define  KEY_WW                           11      /* callback function: fww */
#define  KEY_VV                           12      /* callback function: fvv */
#define  KEY_UU                           13      /* callback function: fuu */
#define  KEY_TT                           14      /* callback function: ftt */
#define  KEY_SS                           15      /* callback function: fss */
#define  KEY_XX                           16      /* callback function: fxx */
#define  KEY_RR                           17      /* callback function: frr */
#define  KEY_SPARE                        18
#define  KEY_OO                           19      /* callback function: foo */
#define  KEY_QQ                           20      /* callback function: fqq */
#define  KEY_PP                           21      /* callback function: fpp */
#define  KEY_NN                           22      /* callback function: fnn */
#define  KEY_MM                           23      /* callback function: fmm */
#define  KEY_LL                           24      /* callback function: fll */
#define  KEY_KK                           25      /* callback function: fkk */
#define  KEY_JJ                           26      /* callback function: fjj */
#define  KEY_II                           27      /* callback function: fii */
#define  KEY_FF                           28      /* callback function: fff */
#define  KEY_HH                           29      /* callback function: fhh */
#define  KEY_GG                           30      /* callback function: fgg */
#define  KEY_EE                           31      /* callback function: fee */
#define  KEY_DD                           32      /* callback function: fdd */
#define  KEY_CC                           33      /* callback function: fcc */
#define  KEY_BB                           34      /* callback function: fbb */
#define  KEY_AA                           35      /* callback function: faa */
#define  KEY_KEY3                         36      /* callback function: fthree */
#define  KEY_KEY2                         37      /* callback function: ftwo */
#define  KEY_KEY1                         38      /* callback function: fone */
#define  KEY_KEY6                         39      /* callback function: fsix */
#define  KEY_KEY5                         40      /* callback function: ffive */
#define  KEY_KEY4                         41      /* callback function: ffour */
#define  KEY_KEY9                         42      /* callback function: fnine */
#define  KEY_KEY8                         43      /* callback function: feight */
#define  KEY_KEY7                         44      /* callback function: fseven */
#define  KEY_COMMANDBUTTON                45      /* callback function: minus */
#define  KEY_COMMANDBUTTON_2              46      /* callback function: plus */
#define  KEY_STRING                       47
#define  KEY_PADSORT                      48      /* callback function: fpadsort */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK faa(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fbb(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fblank(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fbs(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fcc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fclr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fdd(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fdot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fee(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK feight(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fenter(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fesc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ffive(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ffour(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fgg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fhh(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fii(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fjj(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fkk(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fll(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fmm(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fnine(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fnn(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fone(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK foo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fpadsort(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fpp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fqq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK frr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fseven(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fsix(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fss(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fthree(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ftt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ftwo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fuu(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fvv(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fww(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fxx(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fyy(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fzero(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fzz(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK keypanelfun(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK minus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK plus(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
