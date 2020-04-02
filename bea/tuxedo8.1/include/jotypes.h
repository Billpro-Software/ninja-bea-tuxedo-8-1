/*
 * Copyright (c) 1997 BEA Systems, Inc.  All rights reserved
 *
 * THIS IS UNPUBLISHED PROPRIETARY SORUCE CODE OF BEA Systems, Inc.
 * The copyright notice above does not evidence any actual or intended
 * publication of such source code.
 *
 * $Id: jotypes.h,v 1.3 2002/08/05 16:35:20 bhavani Exp $
 */

#ifndef _JOTYPES_H_
#define _JOTYPES_H_

#include <tmenv.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Canonical string format
 */
#define	LATIN1_CANONICAL	0	/* canonical format is iso-8859-1 */
#define	UNICODE_CANONICAL	1	/* canonical format is Unicode */

/*
 * Local format
 */
#define	LATIN1_LOCAL		0	/* local format is iso-8859-1 */
#define	ANY8_LOCAL		1	/* local format is 8-bit non-8859-1 */
#define	ANY16_LOCAL		2	/* local format is any 16-bit */
#define	ANY24_LOCAL		3	/* local format is any 24-bit */
#define	ANY32_LOCAL		4	/* local format is any 32-bit */

struct joconversionsw_t {
	const char *name;		/* eg. en_US, ja_JP */
	const short canonicalFmt;	/* xxxx_CANONICAL */
	const short localFmt;		/* xxxx_LOCAL */
	int	(*_conversionInit) _((void));
	int	(*_conversionDone) _((void));
	int	(*_canonical2local) _((unsigned char *, long, unsigned char **,
					long *));
	int	(*_local2canonical) _((unsigned char *, long, unsigned char **,
					long *));
};

#ifndef	_TMDLLEXPORT
#define	_TMDLLEXPORT
#endif
#ifndef	_TMDLLIMPORT
#define	_TMDLLIMPORT
#endif

#ifdef	_EXPORTING
#define	_TMIJCONV	_TMDLLEXPORT
#else
#define	_TMIJCONV	_TMDLLIMPORT
#endif

_TMIJCONV extern _TM_THREADVAR struct joconversionsw_t _joconvsw;

extern int _dfltconversionInit _((void));
extern int _dfltconversionDone _((void));
extern int _dfltcanonical2local _((unsigned char *, long, unsigned char **,
				   long *));
extern int _dfltlocal2canonical _((unsigned char *, long, unsigned char **,
				   long *));

#if defined(__cplusplus)
}
#endif


#define	_localeName()		_joconvsw.name

#define	_canonicalFmt()		_joconvsw.canonicalFmt

#define	_localFmt()		_joconvsw.localFmt

#define	_canonicalcsize()	((_canonicalFmt() == LATIN1_CANONICAL) ? 1 : 2)

#define	_localcsize()		((_localFmt()==LATIN1_LOCAL) ? 1 : _localFmt())

#define	_conversionInit()	\
	((*(_joconvsw._conversionInit==NULL ?	\
	_dfltconversionInit : _joconvsw._conversionInit)) ())

#define	_conversionDone()	\
	((*(_joconvsw._conversionDone==NULL ?	\
	_dfltconversionDone : _joconvsw._conversionDone)) ())

#define	_canonical2local(u,ul,l,ll)	\
	((*(_joconvsw._canonical2local==NULL ?	\
	_dfltcanonical2local : _joconvsw._canonical2local)) ((u),(ul),(l),(ll)))

#define	_local2canonical(l,ll,u,ul)	\
	((*(_joconvsw._local2canonical==NULL ?	\
	_dfltlocal2canonical : _joconvsw._local2canonical)) ((l),(ll),(u),(ul)))

#define	JOLTI18NFALSE	0x0
#define	JOLTI18NTRUE	0x1

extern int jolti18nFlag;

#endif	/* _JOTYPES_H_ */
