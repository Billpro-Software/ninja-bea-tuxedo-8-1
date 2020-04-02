/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1991 USL
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF USL
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/ws/BANKAPP.C	$Revision: 1.5 $" */
#include <atmi.h>
#include <userlog.h>

/*
 * FORMS PACKAGE:  the first part of this file is a small, some-what
 *	general purpose forms/menu handling set of software.  It works
 *	with both Microsoft and Borland C on DOS, and Microsoft C on OS2.
 *
 *	For Microsoft C on DOS, it is expected that HELVB.FON is in the
 *	current directory (copied from \C600\SRC\SAMPLES or \C700\LIB.
 *
 *	For Borland C, the BGI files for EGAVGA, ATT, and CGA are needed.
 */
#ifdef _TM_OS2
#define INCL_BASE
#define INCL_KBD
#define INCL_VIO
#include <os2.h>
#undef ADDRESS
#else
#include <dos.h>
#endif

#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#if !defined(__32BIT__) && !defined(_WIN32)
#include <bios.h>
#endif
#include <time.h>

#ifndef _TM_OS2
/*
 * Map graphics function names between MSC and BC
 */
#ifdef __TURBOC__
#include <graphics.h>
#define	setfill(a)			setfillstyle(SOLID_FILL, a)
#else
#include <graph.h>
#define bioskey(a)			_bios_keybrd(a)
#define outtextxy(x, y, t)		_moveto(x, y); _outgtext(t)
#define setviewport(x1, y1, x2, y2, z) _setviewport(x1, y1, x2, y2); (z) ? _setcliprgn(x1, y1, x2, y2), 1 : 1
#define cleardevice()			_clearscreen(_GCLEARSCREEN)
#define setfill(a)			_setcolor(a)
#define setcolor(a)			_setcolor(a)
#define bar(x1, y1, x2, y2)		_rectangle(_GFILLINTERIOR, x1, y1, x2, y2)
#define closegraph()			_unregisterfonts(); _setvideomode( _DEFAULTMODE );
#define textwidth(a)			_getgtextextent(a)
#endif

static int	MaxX, MaxY;	/* The maximum resolution of the screen */
static int	ErrorCode;	/* Reports any graphics errors		*/
static int	Height;		/* height of letters */
static int	Width;		/* width of letters */
static int	FontColor;	/* Color of font */
static int	BackColor;	/* Color of background */
static int	highlight;	/* Color of highlighted keyletter */
static int	white;		/* Index for White */
static int	egaflag;	/* EGA/VGA mode */
static int	CurrentFont;	/* current font index */
static int viewx1, viewx2, viewy1, viewy2;	/* current viewport */
static void	changefontsize(int size);	/* change font size/index */
#else
#define BKGRND(a)	(a<<4)
#define BLACK		0x00
#define BLUE		0x01
#define GREEN		0x02
#define RED		0x04
#define WHITE		0x07
#define HIYELLOW	0x0e
#define HIWHITE		0x0f
#define closegraph()
#define cleardevice()
#endif

static int	Initialized = 0;/* graphics initialized? */

/* alt characters a-z  - as returned by getkey() */
static int alt[] = {286, 304, 302, 288, 274, 289, 290, 291, 279, 292, 293, 294,
	306, 305, 280, 281, 272, 275, 287, 276, 278, 303, 273, 301, 277, 300};

#define BACKSPACE	8	/* next field */
#define CR		13	/* carriage return */
#define ESC		27	/* return from form */
#define UPKEY		328	/* previous tab stop */
#define DOWNKEY		336	/* next tab stop */
#define DELKEY		339	/* erase field value */

/* FORM structure */
struct frm_t {
	int lines;				/* lines for form */
	int cols;				/* columns for form */
	struct fld_t *flds;			/* array of fields */
	int pos;				/* current field on form */
	int font;				/* font size */
	};


/* Structure for individual fields on a form */
struct fld_t {
	int type;				/* field identifier */
	int x;					/* position on form: x */
	int y;					/* position on form: y */
	int width;				/* field width */
	int flags;				/* field types - see below */
	long lval;				/* field value - optional */
	char *sval;				/* string value of field */
	int (*input) (int, struct frm_t *);	/* input function */
	int (*rtn) (struct frm_t *);		/* handle CR on field */
 	};

/* field types */
#define F_LB	001		/* label */
#define F_TS	002		/* tab stop */
#define F_KS	004		/* keystroke */

/* Return values for the "return function" - the default is to do nothing */
#define LEAVE_IMMED	1	/* leave the current form immediately */
#define LEAVE_KEY	2	/* leave the current form after a keystroke */
#define REPAINT		3	/* repaint the current form */

/*
 * HOT KEYS:
 *	If a field is marked F_KS, then the first letter is highlighted.
 *	The user can enter Alt-x where x is the first letter of the field
 *	to move to the field.
 * 	This structure is generated to keep track of hot-key values and
 *	the associated field.
 */
struct hotkey_t {
	int c;
	int pos;
	};

#ifndef _TM_OS2
/*
 *	getkey -  Uses the BIOS to read the next keyboard character
 */
int
getkey()
{
	int key, lo, hi;

	key = bioskey(0);		/* get/wait for keystoke */
	lo = key & 0X00FF;		/* if lo is set, a normal ascii key */
	hi = (key & 0XFF00) >> 8;	/* alternate character set */
	return((lo == 0) ? hi + 256 : lo);
}
#else
int
getkey()
{
	KBDKEYINFO kbdkeyinfo;

	KbdCharIn(&kbdkeyinfo, IO_WAIT, 0);
	return((kbdkeyinfo.chChar == 0) ? kbdkeyinfo.chScan + 256 : 
		kbdkeyinfo.chChar);	
}
#endif


/* Function prototypes */
void Initialize(void);			/* initilize graphics */
void StatusLine(char *, char *);	/* print messages to status area */
int DoForm(struct frm_t *);		/* handle a form */
void DrawField(struct frm_t *, int);	/* draw a field on a form */

/*
 * Initialize: Initializes the graphics system and reports
 *	any errors which occurred.
 */

#ifndef _TM_OS2
void
#ifdef __TURBOC__
Initialize()
{
/* Borland graphics */
	int g_driver, g_mode;

	directvideo  = 0;

	detectgraph(&g_driver, &g_mode);
	if (g_driver < 0) {
		printf("No graphics hardware detected!\n");
		exit(1);
	}
	switch(g_driver) {
	case CGA:	g_mode = CGAC1;		egaflag = 0; break;
	case MCGA:	g_mode = MCGAC1;	egaflag = 0; break;
	case EGA:	g_mode = EGAHI;		egaflag = 1; break;
	case EGA64:	g_mode = EGA64LO;	egaflag = 1; break;

	case EGAMONO:	printf("EGAMONO not supported\n"); exit(1);
	case IBM8514:	printf("IBM8514 not supported\n"); exit(1);
	case HERCMONO:	printf("HERCMONO not supported\n"); exit(1);

	case ATT400:	g_mode = ATT400C1;	egaflag = 0; break;
	case VGA:	g_mode = VGAMED;	egaflag = 1; break;

	case PC3270:	printf("PC2370 not supported\n"); exit(1);
	default:	printf("Monitor not supported\n"); exit(1);
	}

#ifdef fake_cga
	egaflag = 0;
	g_mode = CGAC1;
	g_driver = CGA;
#endif
	if (g_driver == ATT400) {
		if (registerbgidriver(ATT_driver) < 0)
			exit(1);
	}
	else if (egaflag == 1) {		/* EGA, VGA, EGA64 */
		if (registerbgidriver(EGAVGA_driver) < 0)
			exit(1);
	}
	else {	/* CGA, MCGA */
		if (registerbgidriver(CGA_driver) < 0)
			exit(1);
	}
	initgraph(&g_driver, &g_mode, "");
	ErrorCode = graphresult();	/* Read result of initialization*/
	if (ErrorCode != grOk) {	/* Error occured during init	*/
		printf("Graphics System Error: %s\n", grapherrormsg(ErrorCode));
		exit(1);
	}

	MaxX = getmaxx();	/* screen size - x pixels */
	MaxY = getmaxy();	/* screen size - y pixels */

	if (egaflag) {	/* 16-color palette */
		FontColor = EGA_LIGHTBLUE;
		highlight = EGA_LIGHTGRAY;
		white = EGA_WHITE;
	}
	else {		/* 4-color pallete - number 1 */
		FontColor = CGA_LIGHTMAGENTA;
		highlight = CGA_LIGHTCYAN;
		white = CGA_WHITE;
	}
	BackColor = white;	/* color for the viewport */

	Initialized = 1;
	return;
}
#else
/* Microsoft graphics */
Initialize()
{
	struct videoconfig config;
	int egaflag = 0, i;
	struct _fontinfo f;

#ifdef fake_cga
	i = _setvideomode(_MRES4COLOR);
#else
	if ((i=_setvideomode(_ERESCOLOR)) == 0)
		i=_setvideomode(_MRES4COLOR);
	else
		egaflag = 1;
#endif
	if (i == 0) {
		printf("Error: Failed to set the video mode!\n");
		exit(1);
	}
	_getvideoconfig(&config);

	MaxX = config.numxpixels;	/* screen size - x pixels */
	MaxY = config.numypixels;	/* screen size - y pixels */

	/* Read header info from .FON files in current - expect HELVB.FON */
	if( _registerfonts( ".\\HELVB.FON" ) <= 0 ) {
		_setvideomode(_DEFAULTMODE);
		printf("Error: can't register HELVB.FON\n");
		exit(1);
	}

	_clearscreen(_GCLEARSCREEN);

	if (egaflag) {	/* 16-color palette */
		FontColor = 9;	/* BLUE */
		highlight = 7;	/* GRAY */
		white = 15;
	}
	else {		/* 4-color pallete */
		FontColor = 1;	/* light blue */
		highlight = 2;	/* magenta */
		white = 3;
	}
	BackColor = white;
	Initialized = 1;
	return;
}
#endif

#else
	/* OS2 */
static void
cls()
{
	BYTE cell[2];

	cell[0] = ' ';
	cell[1] = BKGRND(GREEN) | GREEN;
	VioWrtNCell(cell, 80*5, 0, 0, 0);
	cell[0] = 0xdc;
	cell[1] = BKGRND(GREEN) | HIWHITE;
	VioWrtNCell(cell, 80, 4, 0, 0);
	cell[1] = BKGRND(WHITE) | WHITE;
	VioWrtNCell(cell, 80*20, 5, 0, 0);
}

static void
clsscreen()
{
	BYTE cell[2];

	cell[0] = ' ';
	cell[1] = BLACK;
	VioWrtNCell(cell, 80*25, 0, 0, 0);
}

#ifndef VIO_CONFIG_CURRENT
#define VIO_CONFIG_CURRENT 0
#endif

void
Initialize()
{
	VIOCONFIGINFO vioin;

	vioin.cb = sizeof(vioin);
	VioGetConfig(VIO_CONFIG_CURRENT, &vioin, 0);
	cls();
	Initialized = 1;
	return;
}
#endif

/*
 *	badkey - beep at console when invalid key entered
 */
void
badkey()
{
	printf("");
}

/*
 * defaultinput:	default keystroke input function if application
 *	doesn't specify one.  It appends to the string value for
 *	the field as long as the field width is not exceeded.
 */
defaultinput(int c, struct frm_t *frm)
{
	int i;
	char *p;
	struct fld_t *f = &frm->flds[frm->pos];

	p = f->sval;
	for (i=0; *p != '\0'; p++, i++)
		/* EMPTY */;
	if (i >= f->width)
		return(-1);
	*p++ = c;
	*p = '\0';
	return(0);
}

#ifndef _TM_OS2
/*
 *	Drawfield - draw a single field on a form without changing
 *		the current input position.
 */
void
Drawfield(struct frm_t *frm, int pos)
{
	int x, y;
	char *s, a[2];
	struct fld_t *f = &frm->flds[pos];

	y = f->y * (Height + 4);
	x = f->x * Width;
	if (frm->pos == pos)
		setfill(FontColor);
	else
		setfill(BackColor);
	bar(x-1, y - 2, x + (Width * f->width),
		y + Height + 2);

	s = f->sval;
	if (f->flags&F_KS) {
		setcolor(highlight);
		a[0] = *s++; a[1] = '\0';
		outtextxy(x, y, a);
		x += textwidth(a);
	}

	if (frm->pos == pos)
		setcolor(BackColor);
	else
		setcolor(FontColor);
	outtextxy(x, y, s);
	return;
}
#else
void
Drawfield(struct frm_t *frm, int pos)
{
	int x, y;
	char *s, a[2];
	struct fld_t *f = &frm->flds[pos];
	BYTE attr;

	/* the coordinates in the tables are graphics coordinates
	 * for DOS - convert them so they will look nice on the OS2
	 * text screen.
	 */
	y = (f->y - 1) * 3 + 1;
	x = f->x + 15;

	if (frm->pos == pos)
		attr = BKGRND(BLUE) | HIWHITE;
	else
		attr = BKGRND(BLACK) | HIYELLOW;

	s = f->sval;
	if (f->flags&F_KS) {
		attr = BKGRND(RED) | HIWHITE;
		a[0] = *s++; a[1] = '\0';
		VioWrtCharStrAtt(a,strlen(a),y, x, &attr, 0);
		x += 1;
	}

	if (frm->pos == pos)
		attr = BKGRND(BLACK) | HIYELLOW;
	else
		attr= BKGRND(BLUE) | HIWHITE;

	if ((f->flags & F_LB) && (!(f->flags & F_KS)) &&
		(!(f->flags & F_TS)))
		attr = BKGRND(RED) | HIWHITE;
	VioWrtCharStrAtt(s,strlen(s),y, x, &attr, 0);
	return;
}
#endif

/*
 *	DoForm - display a form and handle input for the form
 */
DoForm(struct frm_t *frm)
{
	int i, j, cont, x, y, didinit = 0;
	int pos, c, newpos, redraw;
	char a[2], *s;
	struct hotkey_t hot[27];	/* at most 27 hot keys */
	struct fld_t *curflds = frm->flds;

	if (!Initialized) {
		Initialize();		/* initialized graphics */
		didinit = 1;		/* keep track so graphics can be
					 * uninitialized before returning
					 */
	}

	/* initialized field values; find first open tab stop; set up hot keys*/
	pos = -1;
	for (j = i = 0; curflds[i].type; i++) {
		if (!(curflds[i].flags&F_LB)) {	/* initialize field */
			if (curflds[i].input != NULL) {
				/* call application function with input
				 * value 0 to initialize the field
				 */
				frm->pos = i;
				(void) (*curflds[frm->pos].input)(0, frm);
			}
			else {	/* default - set to null string */
				curflds[i].lval = 0;
				*curflds[i].sval = '\0';
			}
		}
		if(curflds[i].flags&F_TS) {	/* set up hot-key */
			if (pos == -1)
				pos = i;
			if(curflds[i].flags&F_KS) {
				c = *curflds[i].sval;
				if (!isalpha(c))
					continue;
				c = toupper(c);
				hot[j].c = alt[c - 'A'];
				hot[j++].pos = i;
			}
		}
	}
	if (pos == -1) {		/* no tabstop field */
		if (didinit) {
			closegraph();	/* Return the system to text mode */
			Initialized = 0;
		}
		return(-1);
	}
	frm->pos = pos;		/* current input position is first tabstop */
	hot[j].c = 0;		/* sentinel on hot keys */

	for(;;) {
#ifndef _TM_OS2
		cleardevice();		/* clear graphics screen */
		changefontsize(1);	/* change to smallest font size */
		j = 2 * (Height + 2);	/* height of the status area */

		/* now determine largest font size that can be used
		 * for the form and still fit on the screen, leaving enough
		 * room for the status area at the bottom
		 */
		for(i=1;;i++) {
			changefontsize(i);
			if (frm->cols * Width > MaxX ||
			    frm->lines * Height + j > MaxY)
				break;	/* too big */
		}
		if (i > 1)
			i--;
		frm->font = i;		/* save the font size */
		changefontsize(i);	/* change to the font size */

		/* set up the viewport based on the font size, trying
		 * to center it on both the x and y axis
		 */
		viewx1 = (MaxX - (frm->cols * Width)) / 2;
		if (viewx1 < 0)
			viewx1 = 0;
		viewx2 = MaxX - viewx1;

		viewy1 = (MaxY - (frm->lines * (Height + 4)) - j) / 2;
		if (viewy1 < 0) {
			viewy1 = 0;
			viewy2 = MaxY - j;
		}
		else
			viewy2 = viewy1 + (frm->lines * (Height + 4));
		setviewport(viewx1, viewy1, viewx2, viewy2, 1);

		/* fill the viewport */
		setfill(BackColor);
		bar(0, 0, frm->cols * Width, frm->lines * (Height + 4));
#else
		cls();		/* clear graphics screen */
		StatusLine(NULL,NULL);
#endif

		for (i=0; curflds[i].type; i++) {	/* draw all fields */
			Drawfield(frm, i);
		}

		cont = 1;
		while(cont) {
			redraw = 0;
			newpos = -1;
			c=getkey();			/* get next keystroke */
			StatusLine(NULL, NULL);		/* clear status area */
			switch(c) {
			case CR:
				if (curflds[frm->pos].rtn == NULL) {
					badkey(); /* CR not allowed for field */
					break;
				}
				/* call application return function */
				i = (*curflds[frm->pos].rtn)(frm);
				if (i == LEAVE_KEY) {
					getkey();	/* wait for keystroke */
					if (didinit) {
						closegraph();
						Initialized = 0;
					}
					return(0);
				}
				if (i == LEAVE_IMMED) {
					if (didinit) {
						closegraph();
						Initialized = 0;
					}
					return(0);
				}
				if (i == REPAINT) {
					cont = 0;
					break;
				}
				break;
			case ESC:	/* leave form immediately */
				if (didinit) {
					closegraph();
					Initialized = 0;
				}
				return(0);
			case DOWNKEY:
			case '\t' :
				/* find the next tab stop */
				for (newpos = frm->pos;;) {
					newpos++;
					if (curflds[newpos].type == 0)
						newpos = 0;
					if (curflds[newpos].flags & F_TS)
						break;
				}
				break;
			case UPKEY:
			case BACKSPACE:
				/* find the previous tab stop */
				for(newpos = frm->pos;;) {
					newpos--;
					if (newpos < 0) {
						/* find last entry */
						for (i=0;curflds[i].type;i++)
							/* EMPTY */;
						newpos = i - 1;
					}
					if (curflds[newpos].flags&F_TS)
						break;
				}
				break;
			default:
				/* first check for hot-key */
				for (i=0; hot[i].c; i++) {
					if (hot[i].c == c)
						break;
				}
				if (hot[i].c == c) {
					newpos = hot[i].pos;
					break;
				}
				if (curflds[frm->pos].flags&F_LB) {
					badkey(); /* no input on label */
					break;
				}
				if (c == DELKEY) {/* re-init field value */
					redraw = 1;	/* redraw field */
					if (curflds[frm->pos].input != NULL) {
						(void)(*curflds[frm->pos].input)
							(0, frm);
					}
					else {
						curflds[frm->pos].lval = 0;
						*curflds[frm->pos].sval = '\0';
					}
					break;
				}
				if (c != (c&0177) || !isprint(c)) {
					badkey(); /* not a printable char */
					break;
				}
				if (curflds[frm->pos].input != NULL)
					i = (*curflds[frm->pos].input)(c,
						frm); /* app input func */
				else
					i = defaultinput(c, frm);
				if (i < 0) {
					badkey();
				}
				else
					redraw = 1;	/* redraw field */
				break;
			}
			if (newpos != -1) {
				/* normal-video the current frm->position */
				pos = frm->pos;
				frm->pos = newpos;
				Drawfield(frm, pos);
				redraw = 1;
			}
			if (redraw) {	/* redraw the field - reverse video */
				Drawfield(frm, frm->pos);
			}
		}
	}
}

/*
 *	StatusLine: Display two status lines at the bottom of the screen.
 */
#ifndef _TM_OS2
void
StatusLine(char *msg, char *msg2)
{
	int save;

	save = CurrentFont;			/* save the current font size */
	changefontsize(1);			/* change to smallest size */
	setviewport(0, 0, MaxX, MaxY, 1);	/* Open vp to full screen */

	if (msg == NULL) {			/* clear the status lines */
		setfill(0);
		bar(0, MaxY- 2*(Height+2), MaxX, MaxY);
		/* reset viewport and font size */
		setviewport(viewx1, viewy1, viewx2, viewy2, 1);
		changefontsize(save);
		return;
	}

	setfill(BackColor);
	bar(0, MaxY- 2* (Height+2), MaxX, MaxY);

	setcolor(FontColor);
	outtextxy((MaxX - textwidth(msg))/2,
		MaxY - (2 * (Height+2)) + 1, msg);
	outtextxy((MaxX - textwidth(msg2))/2,
		MaxY - (Height+2) + 1, msg2);

	/* reset viewport and font size */
	setviewport(viewx1, viewy1, viewx2, viewy2, 1);
	changefontsize(save);
}

static void
#ifdef __TURBOC__
changefontsize(int size) 
{
	int ErrorCode;

	graphresult();			/* clear error code */
	settextstyle(DEFAULT_FONT, HORIZ_DIR, size);
	ErrorCode = graphresult();	/* check result */
	if (ErrorCode != grOk) {	/* if error occured */
#ifndef noatmi
		(void) tpterm();
#else
#undef tran
#endif
		closegraph();
		printf("Graphics System Error: %s\n", grapherrormsg(ErrorCode));
		exit(1);
	}
	Height = textheight("W");
	Width = textwidth("W");
	CurrentFont = size;
}
#else
changefontsize(int size) 
{
	char font[10];
	struct _fontinfo f;

	switch(size) {	/* this code uses known sizes for HELVB.FON */
	case 1: strcpy(font, "t'helv'h10b"); break;
	case 2: strcpy(font, "t'helv'h12b"); break;
	case 3: strcpy(font, "t'helv'h15b"); break;
	case 4: strcpy(font, "t'helv'h18b"); break;
	case 5: strcpy(font, "t'helv'h22b"); break;
	default: strcpy(font, "t'helv'h28b"); break;
	}
	if (_setfont(font) < 0) {
		_setvideomode(_DEFAULTMODE);
#ifndef noatmi
		(void) tpterm();
#endif
		printf("Error: can't set font");
		exit(1);
	}
	_getfontinfo(&f);
	Height = f.pixheight;
	Width = _getgtextextent("W");
	CurrentFont = size;
}
#endif
#else
/* OS2 */
void
StatusLine(char *msg, char *msg2)
{
	BYTE attr;
	BYTE attr1[2];

	attr1[0] = 0xdc;
	attr1[1] = BKGRND(WHITE) | HIWHITE;
	VioWrtNCell(attr1, 80, 23, 0, 0);
	attr1[0] = ' ';
	attr1[1] = BKGRND(GREEN) | GREEN;
	VioWrtNCell(attr1, 80, 24, 0 , 0);
        if (msg != NULL) {
		attr = BKGRND(GREEN) | BLACK;
		VioWrtCharStrAtt(msg, strlen(msg), 24, 0 , &attr, 0);
	}
        if (msg2 != NULL) {
		attr = BKGRND(GREEN) | HIYELLOW;
		VioWrtCharStrAtt(msg2, strlen(msg2), 24, 0, &attr, 0);
	}
}

#endif
/* END OF THE FORM/MENU HANDLER */


/*
 * APPLICATION
 */
#include <atmi.h>
#include <tmtypes.h>
#ifdef FML32
#include <Usysfl32.h>
#include <fml32.h>
#include <fml1632.h>
#else
#include <Usysflds.h>
#include <fml.h>
#endif
#include "bankflds.h"

/* application form fields */
#define APP_HEADER		1
#define APP_DEPOSIT		2
#define APP_WITHDRAW		3
#define APP_TRANSFER		4
#define APP_QUIT		5
#define APP_AMOUNT		6
#define APP_ACCOUNT1		7
#define APP_ACCOUNT2		8
#define APP_BALANCE1		9
#define APP_BALANCE2		10
#define APP_CANCEL		11
#define APP_RETURN		12
#define APP_INQUIRY		13

static int input_amt(int, struct frm_t *);	/* input func for $ amounts */
static int input_acc(int, struct frm_t *);	/* input func for acount #'s */
static int rtn_func(struct frm_t *);		/* return function */

/* form field values */
#define AMOUNTLEN 10
static char amount[AMOUNTLEN];
static char balance1[AMOUNTLEN];
static char balance2[AMOUNTLEN];
#define ACCTLEN 10
static char account1[ACCTLEN];
static char account2[ACCTLEN];

/* SELECT MENU */
struct fld_t selectflds[] = {
/* name, 	x, y, wid, flags, 		lval, sval, fmt, rtn */
 {APP_HEADER, 	1, 1, 25, F_LB, 			0, "SELECT TRANSACTION", NULL, NULL},
 {APP_INQUIRY, 	1, 3, 25, F_LB|F_TS|F_KS, 	0, "INQUIRY ACCOUNT BALANCE", NULL, rtn_func},
 {APP_DEPOSIT, 	1, 4, 25, F_LB|F_TS|F_KS, 	0, "DEPOSIT INTO ACCOUNT", NULL, rtn_func},
 {APP_WITHDRAW, 	1, 5, 25, F_LB|F_TS|F_KS, 	0, "WITHDRAWAL FROM ACCOUNT", NULL, rtn_func},
 {APP_TRANSFER, 	1, 6, 25, F_LB|F_TS|F_KS, 	0, "TRANSFER BETWEEN ACCOUNTS", NULL, rtn_func},
 {APP_QUIT, 	1, 7, 25, F_LB|F_TS|F_KS, 	0, "QUIT", NULL, rtn_func},
 {0, 	0, 0, 0, 0, 	0, 0, NULL, NULL},
 };
struct frm_t selectform[] = { 11, 35, selectflds };

/* WITHDRAWAL FORM */
struct fld_t withdrawflds[] = {
/* name, 	x, y, wid, flags, 		lval, sval, fmt, rtn */
 {APP_HEADER, 	10, 1, 25, F_LB, 		0, "WITHDRAWAL", NULL, NULL},
 {APP_HEADER, 	1, 3, 20, F_LB, 			0, "ACCOUNT NUMBER:", NULL, NULL},
 {APP_ACCOUNT1, 	20, 3, 10, F_TS, 		0, account1, input_acc, rtn_func},
 {APP_HEADER, 	1, 4, 20, F_LB, 			0, "WITHDRAWAL AMOUNT:", NULL, NULL},
 {APP_AMOUNT, 	20, 4, 10, F_TS, 		0, amount, input_amt, rtn_func},
 {APP_HEADER, 	1, 5, 20, F_LB, 			0, "BALANCE AMOUNT:", NULL, NULL},
 {APP_BALANCE1, 	20, 5, 10, 0, 			0, balance1, NULL, NULL},
 {APP_RETURN, 	1, 7, 9, F_LB|F_TS|F_KS, 	0, "ENTER", NULL, rtn_func},
 {APP_CANCEL, 	10, 7, 10, F_LB|F_TS|F_KS, 	0, "CANCEL", NULL, rtn_func},
 {0, 	0, 0, 0, 0, 	0, 0, NULL, NULL},
 };
struct frm_t withdrawform[] = { 11, 35, withdrawflds };

/* DEPOSIT FORM */
struct fld_t depositflds[] = {
/* name, 	x, y, wid, flags, 		lval, sval, fmt, rtn */
 {APP_HEADER, 	10, 1, 25, F_LB, 		0, "DEPOSIT", NULL, NULL},
 {APP_HEADER, 	1, 3, 20, F_LB, 			0, "ACCOUNT NUMBER:", NULL, NULL},
 {APP_ACCOUNT1, 	20, 3, 10, F_TS, 		0, account1, input_acc, rtn_func},
 {APP_HEADER, 	1, 4, 20, F_LB, 			0, "DEPOSIT AMOUNT:", NULL, NULL},
 {APP_AMOUNT, 	20, 4, 10, F_TS, 		0, amount, input_amt, rtn_func},
 {APP_HEADER, 	1, 5, 20, F_LB, 			0, "BALANCE AMOUNT:", NULL, NULL},
 {APP_BALANCE1, 	20, 5, 10, 0, 			0, balance1, NULL, NULL},
 {APP_RETURN, 	1, 7, 9, F_LB|F_TS|F_KS, 	0, "ENTER", NULL, rtn_func},
 {APP_CANCEL, 	10, 7, 10, F_LB|F_TS|F_KS, 	0, "CANCEL", NULL, rtn_func},
 {0, 	0, 0, 0, 0, 	0, 0, NULL, NULL},
 };
struct frm_t depositform[] = { 11, 35, depositflds };

/* INQUIRY FORM */
struct fld_t inquiryflds[] = {
/* name, 	x, y, wid, flags, 		lval, sval, fmt, rtn */
 {APP_HEADER, 	10, 1, 25, F_LB, 		0, "INQUIRY", NULL, NULL},
 {APP_HEADER, 	1, 3, 20, F_LB, 			0, "ACCOUNT NUMBER:", NULL, NULL},
 {APP_ACCOUNT1, 	20, 3, 10, F_TS, 		0, account1, input_acc, rtn_func},
 {APP_HEADER, 	1, 4, 20, F_LB, 			0, "BALANCE AMOUNT:", NULL, NULL},
 {APP_BALANCE1, 	20, 4, 10, 0, 			0, balance1, NULL, NULL},
 {APP_RETURN, 	1, 6, 9, F_LB|F_TS|F_KS, 	0, "ENTER", NULL, rtn_func},
 {APP_CANCEL, 	10, 6, 10, F_LB|F_TS|F_KS, 	0, "CANCEL", NULL, rtn_func},
 {0, 	0, 0, 0, 0, 	0, 0, NULL, NULL},
 };
struct frm_t inquiryform[] = { 11, 35, inquiryflds };

/* TRANSFER FORM */
struct fld_t transferflds[] = {
/* name, 	x, y, wid, flags, 		lval, sval, fmt, rtn */
 {APP_HEADER, 	10, 1, 25, F_LB, 		0, "TRANSFER", NULL, NULL},
 {APP_HEADER, 	1, 3, 20, F_LB, 			0, "FROM ACCOUNT NUMBER:", NULL, NULL},
 {APP_ACCOUNT1, 	21, 3, 10, F_TS, 		0, account1, input_acc, rtn_func},
 {APP_HEADER, 	1, 4, 20, F_LB, 			0, "TO ACCOUNT NUMBER:", NULL, NULL},
 {APP_ACCOUNT2, 	21, 4, 10, F_TS, 		0, account2, input_acc, rtn_func},
 {APP_HEADER, 	1, 5, 20, F_LB, 			0, "TRANSFER AMOUNT:", NULL, NULL},
 {APP_AMOUNT, 	21, 5, 10, F_TS, 		0, amount, input_amt, rtn_func},
 {APP_HEADER, 	1, 6, 20, F_LB, 			0, "FROM BALANCE:", NULL, NULL},
 {APP_BALANCE1, 	21, 6, 10, 0, 			0, balance1, NULL, NULL},
 {APP_HEADER, 	1, 7, 20, F_LB, 			0, "TO BALANCE:", NULL, NULL},
 {APP_BALANCE2, 	21, 7, 10, 0, 			0, balance2, NULL, NULL},
 {APP_RETURN, 	1, 9, 9, F_LB|F_TS|F_KS, 	0, "ENTER", NULL, rtn_func},
 {APP_CANCEL, 	10, 9, 10, F_LB|F_TS|F_KS, 	0, "CANCEL", NULL, rtn_func},
 {0, 	0, 0, 0, 0, 	0, 0, NULL, NULL},
 };
struct frm_t transferform[] = { 11, 35, transferflds };

static FBFR *fbfr;	/* FML buffer for service calls */

int
main(int argc, char *argv[])
{
	TPINIT *tpinfop;
	argc = argc;			/* unused */
	argv = argv;			/* unused */


#ifndef noatmi
	if ((tpinfop = (TPINIT *)tpalloc("TPINIT", NULL,
		sizeof(struct tpinfo_t))) == (TPINIT *)NULL) {
		userlog("unable to get init buf\n");
		return(0);
	}
	strcpy(tpinfop->usrname, "Smith");
	strcpy(tpinfop->cltname, "bankapp");
	strcpy(tpinfop->passwd, "mypasswd");
	tpinfop->flags = TPU_IGN;
	tpinfop->datalen = 0;
	tpinfop->data = 0;

	if (tpinit(tpinfop) == -1) {
		userlog("tpinit failed");
		return(0);
	}
	fbfr = (FBFR *)tpalloc(FMLTYPE, NULL, 1024);
	if (fbfr == NULL) {
		userlog("Failed to allocated fielded buffer");
		return(0);
	}
#endif

	(void) DoForm(selectform);

#ifndef noatmi
	(void) tpterm();
#endif
#ifdef _TM_OS2
	clsscreen();
#endif
	return(0);
}

/*
 * input_amt - handle input characters to $ amount fields
 */
static int
input_amt(int c, struct frm_t *frm)
{
	char *samt;
	struct fld_t *f = &frm->flds[frm->pos];
	int i, j, decimal;
	long amt;

	if (c == 0)	/* initialize */
		amt = 0;
	else {
		if (!isdigit(c))
			return(-1);	/* invalid character */
		amt = f->lval;
		amt = amt * 10 + (c - '0');
		if (amt > 10000000) {	/* $100000.00 */
			return(-1);	/* amount too big */
		}
	}
	f->lval = amt;
	samt = f->sval;
	j = AMOUNTLEN - 1;		/* format from the right */
	samt[j--] = '\0';

	for(decimal = 0; amt > 0;) {
		samt[j--] = (amt % 10) + '0';
		amt /= 10;
		decimal++;	/* keep track of decimal point */
		if (j == AMOUNTLEN - 4)
			samt[j--] = '.';
	}
	if (decimal < 2) {	/* if not at least 2 digits */
		for (; decimal < 2; decimal++)
			samt[j--] = '0';
		samt[j--] = '.';
	}
	j++;
	if (samt[j] == '.')
		samt[--j] = '0';

	/* shift it to the beginning */
	for (i=0; samt[j] != '\0'; )
		samt[i++] = samt[j++];
	samt[i] = '\0';
	return(0);
}

/*
 * input_acc	- input function for account numbers
 */
static int
input_acc(int c, struct frm_t *frm)
{
	char *sacc;
	int i, j;
	long acc;
	struct fld_t *f = &frm->flds[frm->pos];

	if (c == 0)		/* initialize */
		acc = 0;
	else {
		if(!isdigit(c))
			return(-1);	/* not a digit */
		acc = f->lval;
		acc = acc * 10 + (c - '0');
		if (acc > 130000)
			return(-1);	/* account number too big */
	}
	f->lval = acc;
	sacc = f->sval;
	j = ACCTLEN - 1;
	sacc[j--] = '\0';

	for(i=0; i < 6 && acc > 0; i++) {
		sacc[j--] = (acc % 10) + '0';
		acc /= 10;
	}
	for (; i < 6; i++)
		sacc[j--] = '0';
	j++;
	/* shift it to the beginning */
	for (i=0; sacc[j] != '\0'; )
		sacc[i++] = sacc[j++];
	sacc[i] = '\0';
	return(0);
}

/*
 * rtn_function - handle CR from any field on all forms
 */
rtn_func(struct frm_t *frm)
{
	char statlin[100], bal[20], bal2[20], *s;
	int i, found, pos;
	long len;

	switch(frm->flds[frm->pos].type) {
	case  APP_DEPOSIT:	/* DEPOSIT FORM */
		DoForm(depositform); return(REPAINT);
	case  APP_INQUIRY:	/* INQUIRY FORM */
		DoForm(inquiryform); return(REPAINT);
	case  APP_WITHDRAW:	/* WITHDRAWAL FORM */
		DoForm(withdrawform); return(REPAINT);
	case  APP_TRANSFER:	/* TRANSFER FORM */
		DoForm(transferform); return(REPAINT);
	case  APP_CANCEL: /* WITHDRAWAL, INQUIRY, DEPOSIT, or TRANSFER FORM */
		return(LEAVE_IMMED);
	case  APP_QUIT:		/* SELECT FORM */
		return(LEAVE_IMMED);
	}
	/* must be an input field or APP_RETURN - send the service request */
#ifndef noatmi
	Finit(fbfr, Fsizeof(fbfr));
#endif
	/* populate the fielded buffer */
	for (found = i = 0; frm->flds[i].type; i++) {
		if (frm->flds[i].type == APP_ACCOUNT1) {
			if (frm->flds[i].lval < 10000 ||
			    frm->flds[i].lval > 120000) {
				StatusLine("Invalid Account Number",
				"Must be between 10000 and 120000");
				if (frm->pos != i) {
					/* reset current field to APP_ACCOUNT1*/
					pos = frm->pos;
					frm->pos = i;
					Drawfield(frm, pos);
					Drawfield(frm, frm->pos);
				}
				return(0);	/* no action */
			}
#ifndef noatmi
			(void) Fchg(fbfr, ACCOUNT_ID, 0,
				(char *)&frm->flds[i].lval, 0);
#endif
			found++;
		}
		if (frm->flds[i].type == APP_ACCOUNT2) {
			if (frm->flds[i].lval < 10000 ||
			    frm->flds[i].lval > 120000) {
				StatusLine("Invalid Account Number",
				"Must be between 10000 and 120000");
				if (frm->pos != i) {
					/* reset current field to APP_ACCOUNT2*/
					pos = frm->pos;
					frm->pos = i;
					Drawfield(frm, pos);
					Drawfield(frm, frm->pos);
				}
				return(0);	/* no action */
			}
#ifndef noatmi
			(void) Fchg(fbfr, ACCOUNT_ID, 1,
				(char *)&frm->flds[i].lval, 0);
#endif
			found++;
		}
		if (frm->flds[i].type == APP_AMOUNT) {
			if (frm->flds[i].lval < 1000 ||
			    frm->flds[i].lval > 10000000) {
				StatusLine("Invalid Amount",
				"Must be between $10.00 and $100000.00");
				if (frm->pos != i) {
					/* reset current field to APP_AMOUNT*/
					pos = frm->pos;
					frm->pos = i;
					Drawfield(frm, pos);
					Drawfield(frm, frm->pos);
				}
				return(0);	/* no action */
			}
#ifndef noatmi
			(void) Fchg(fbfr, SAMOUNT, 0, frm->flds[i].sval, 0);
#endif
			found++;
		}
	}
	/* sanity check that all necessary fields were populated */
	if (frm == transferform) {
		if (found < 3)
			return(0);
	}
	else if (frm == inquiryform) {
		if (found < 1)
			return(0);
	}
	else {
		if (found < 2)
			return(0);
	}
#ifndef noatmi
#ifdef tran
	if (tpbegin(30, 0) == -1) {
		(void) userlog("failed to begin transaction\n");
		strcpy(statlin, "Transaction failed");
	}
	else
#endif
	if (frm == withdrawform)
		s = "WITHDRAWAL";
	else if (frm == transferform)
		s = "TRANSFER";
	else if (frm == inquiryform)
		s = "INQUIRY";
	else
		s = "DEPOSIT";
	strcpy(bal, "FAILED");	/* default value printed for balance */
	bal2[0] = '\0';		/* default value printed */
	if (tpcall(s, (char *)fbfr, 0, (char **)&fbfr,
		&len, 0) == -1) {
		if (tperrno== TPESVCFAIL && fbfr != NULL &&
		    (s=Ffind(fbfr, STATLIN, 0, 0)) != 0) {
			strcpy(statlin, s);
		}
		else {
			if (frm == withdrawform)
				strcpy(statlin, "Withdrawal failed");
			else if (frm == transferform)
				strcpy(statlin, "Transfer failed");
			else if (frm == inquiryform)
				strcpy(statlin, "Inquiry failed");
			else
				strcpy(statlin, "Deposit failed");
		}
#ifdef tran
		(void) tpabort(0);
#endif
	}
	else {
#ifdef tran
		if (tpcommit(0) < 0) {
			if (frm == withdrawform)
				strcpy(statlin, "Withdrawal failed");
			else if (frm == transferform)
				strcpy(statlin, "Transfer failed");
			else if (frm == inquiryform)
				strcpy(statlin, "Inquiry failed");
			else
				strcpy(statlin, "Deposit failed");
		}
		else
#endif
		{
			s = Ffind(fbfr, SBALANCE, 0, 0);
			if (s != NULL)
				strcpy(bal, s);
			else
				bal[0] = '\0';

			s = Ffind(fbfr, SBALANCE, 1, 0);
			if (s != NULL)
				strcpy(bal2, s);
			else
				bal2[0] = '\0';
			strcpy(statlin, "Transaction Completed");
		}
	}
#else
	strcpy(bal, "$5555");
	strcpy(bal2, "$4444");
	strcpy(statlin, "Transaction Completed");
#endif
	/* populate form fields */
	for (i = 0; frm->flds[i].type; i++) {
		if (frm->flds[i].type == APP_BALANCE1) {
			strcpy(frm->flds[i].sval, bal);
			Drawfield(frm, i);
		}
		if (frm->flds[i].type == APP_BALANCE2) {
			strcpy(frm->flds[i].sval, bal2);
			Drawfield(frm, i);
		}
	}
	StatusLine(statlin, "HIT ANY KEY TO CONTINUE");
	return(LEAVE_KEY);	/* leave form after receiving a keystroke */
}

struct tmtype_sw_t tm_typesw[] = {
{
#ifdef FML32
"FML32",	"",		1024,		_finit32, 	_freinit32,
_funinit32,	_fpresend32,	_fpostsend32,	_fpostrecv32,	_fencdec32,
_froute32
#else
"FML",		"",		1024,		_finit, 	_freinit,
_funinit,	_fpresend,	_fpostsend,	_fpostrecv,	_fencdec,
_froute
#endif
},
{
""
}
};
