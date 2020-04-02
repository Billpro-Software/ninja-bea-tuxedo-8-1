/*	(c) 2003 BEA Systems, Inc. All Rights Reserved. */
/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1994 Unix System Laboratories, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) samples/atmi/bankapp/TOOLS/menudriver.c	$Revision: 1.5 $" */
#ifndef NOWHAT
static	char	sccsid[] = "@(#) apps/bankapp/TOOLS/menudriver.c	$Revision: 1.5 $";
#endif
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#ifdef mips
#include <sys/utsname.h>
#ifdef T_NONSTOP
#include <stddef.h>
#endif
#endif

typedef struct choice_t {
	char	*fullname;	/* converted to all upper case */
	char	abb_name;	/* 1 character abbreviation */
	char	*helpmsg;	/* help message for this command */
	char	*priosh;	/* prioritization shell script */
	char	*preqsh;	/* prerequisites shell script */
	char	*shell;		/* command script */
	int	allowed;	/* for looping to see if allowed this time */
	int	cprio;		/* current priority for this loop */
} CHOICE;

char	shellscript[1024]="";
CHOICE	*choices = NULL;
int	choice_count = 0;
int	dflt = -1;
char	prompt[512];
char	menu_title[512] = "";
int	dbglvl = 0;

long	options = 0;
#define	OPT_SELECTION	0x01	/* Selection Menu - No help, no quit */

static	void
usage(s)
char	*s;
{
	(void) fprintf(stderr, "\nusage: %s menufile\n", s);
	return;
}

static	char *
MALLOC(howbig)
size_t	howbig;
{
	char	*rv;

	if ((rv = malloc(howbig)) == NULL) {
		(void) fprintf(stderr, "\nMemory allocation failure (%ld)\n",
			(long) howbig);
	}
	return(rv);
}

static	char *
REALLOC(oldstr, howbig)
char	*oldstr;
size_t	howbig;
{
	char	*rv;

	if ((rv = realloc(oldstr, howbig)) == NULL) {
		(void) fprintf(stderr, "\nMemory reallocation failure (%ld)\n",
			(long) howbig);
	}
	return(rv);
}

static void
setoptions(s)
char	*s;
{
	char	*ptr;

	ptr = strtok(s,"\t ");
	while ((ptr = strtok(NULL, "\t ")) != NULL) {
		if (strcmp(ptr, "SELECTION") == 0)
			options |= OPT_SELECTION;
	}
	return;
}

static	int
adddata(tostring, nd)
char	**tostring;
char	*nd;
{
	if (*tostring == NULL) {
		if ((*tostring = MALLOC(strlen(nd)+2)) == NULL)
			return(-1);
		(void) strcpy(*tostring, "");
	} else {
		*tostring=REALLOC(*tostring,strlen(*tostring)+strlen(nd)+2);
		if (*tostring == NULL)
			return(-1);
	}
	(void) sprintf(*tostring+strlen(*tostring), "%s\n", nd);
	return(0);
}

static	int
putchoice(toadd)
CHOICE	*toadd;
{
	int	i;

	for (i=0; i < choice_count ;i++) {
		if (toadd->abb_name == choices[i].abb_name) {
			(void) fprintf(stderr, "\nDuplicate key letter %c\n",
			toadd->abb_name);
			return(-1);
		}
	}
	if (choices == (CHOICE *) NULL) {
		choices = (CHOICE *) MALLOC(sizeof(CHOICE));
	} else {
		choices = (CHOICE *) REALLOC(choices,
		(choice_count + 1) * sizeof(CHOICE));
	}
	if (choices == NULL)
		return(-1);
	choices[choice_count++] = *toadd;
	return(0);
}

static	int
addquit() {
	CHOICE	tmp;

	tmp.fullname = "Quit";
	tmp.abb_name = 'Q';
	tmp.priosh = NULL;
	tmp.preqsh = NULL;
	tmp.helpmsg = "Quit this menu and return 1 level up.\n";
	tmp.shell = NULL;
	return(putchoice(&tmp));
}

static	int
addhelp() {
	CHOICE	tmp;

	tmp.fullname = "Help";
	tmp.abb_name = 'H';
	tmp.priosh = NULL;
	tmp.preqsh = NULL;
	tmp.helpmsg = "Provide help for menu choice(s).\n";
	tmp.shell = NULL;
	return(putchoice(&tmp));
}

static	int
addchoice(fd)
FILE	*fd;
{
	CHOICE	tmp;	/* fill this in, then if it's ok add to list */
	char	s[512], *tag;
	int	i, sl;
	static	int	lineno = 0;

	tmp.fullname = tmp.helpmsg = tmp.priosh = tmp.preqsh = tmp.shell = NULL;
	tmp.abb_name = '\0';
	while(fgets(s,sizeof(s),fd)) {
		lineno++;
		sl = strlen(s);
		if (s[sl-1] != '\n') {
			(void) fprintf(stderr, "\nLine %d is too long\n", lineno);
			return(-1);
		}
		s[sl-1] = '\0';
		sl--;
		if (s[0] == '\0')
			continue;
		while (s[sl-1] == '\\') {
			if (fgets(s+sl-1, sizeof(s)-sl+1, fd) == NULL)
				break;
			lineno++;
			sl = strlen(s);
			if (s[sl-1] != '\n') {
				(void) fprintf(stderr,
				"\nLine %d is too long\n", lineno);
				return(-1);
			}
			s[sl-1] = '\0';
			sl--;
		}

		if (s[0] == '#' || (s[0] == '\t' && s[1] == '#'))
			continue;

		if (s[0] != '\t') {
			if (STRNCMP(s, "TITLE	", 6) == 0) {
				(void) strcpy(menu_title, s+6);
				return(1);
			}
			if (STRNCMP(s, "OPTIONS	", 8) == 0) {
				(void) setoptions(s);
				return(1);
			}
			if (tmp.fullname != NULL) {
				(void) fprintf(stderr,
				"\nMultiple specification of tag, line %d\n",
				lineno);
				return(-1);
			}
			if ((tmp.fullname = MALLOC(strlen(s)+1)) == NULL)
				return(-1);
			if (options & OPT_SELECTION) {
				tmp.abb_name = '1' + choice_count;
			} else {
				for (i=0; s[i] != '\0' ;i++) {
					if (isupper(s[i])) {
						if (tmp.abb_name != '\0') {
							(void) fprintf(stderr,
"\nMultiple key letter specification, %s, line %d\n", s, lineno);
							return(-1);
						}
						tmp.abb_name = s[i];
					}
				}
			}
			if (tmp.abb_name == '\0') {
				(void) fprintf(stderr,
				"\nNo keyletter specified, %s, line %d\n",
				s, lineno);
				return(-1);
			}
			(void) strcpy(tmp.fullname, s);
			continue;
		}

		if (tmp.fullname == NULL) {
			(void) fprintf(stderr,"\nMissing command name, line %d\n",
				lineno);
			return(-1);
		}
		/*
		 * Else this is one of the following tagged types of lines.
		 *	HELP - part of a multi-line help message for this cmd
		 *	PRIO - Prioritization shell script for this cmd
		 *	PREQ - Prerequisite shell script for this cmd
		 *	SHEL - Command shell script
		 *	END  - End of script marker
		 */
		tag = strtok(s, "\t");
		if (strcmp(tag, "HELP") == 0) {
			if (adddata(&tmp.helpmsg, strtok(NULL, "")) == -1)
				return(-1);
			continue;
		}
		if (strcmp(tag, "PRIO") == 0) {
			if (adddata(&tmp.priosh, strtok(NULL, "")) == -1)
				return(-1);
			continue;
		}
		if (strcmp(tag, "PREQ") == 0) {
			if (adddata(&tmp.preqsh, strtok(NULL, "")) == -1)
				return(-1);
			continue;
		}
		if (strcmp(tag, "SHEL") == 0) {
			if (adddata(&tmp.shell, strtok(NULL, "")) == -1)
				return(-1);
			continue;
		}
		if (strcmp(tag, "END") == 0) {
			if (tmp.shell == NULL) {
				(void) fprintf(stderr,
				"\nScript not specified for command %s\n",
				tmp.fullname);
				return(-1);
			}
			if (putchoice(&tmp) < 0)
				return(-1);
			return(1);
		}
		(void) fprintf(stderr, "\nIllegal tag, %s\n", tag ? tag : "NULL");
		return(-1);
	}
	if (tmp.fullname != NULL) {
		(void) fprintf(stderr, "\nIncomplete specification for %s\n",
		tmp.fullname);
		return(-1);
	}
	return(0);
}

static	int
dump_and_execute(str)
char	*str;
{
	FILE	*fd;
	char	*fname, cmd[512];
	int	rv;

	if ((fname = tmpnam(NULL)) == NULL) {
		(void) fprintf(stderr, "\nFailed to generate temp file name\n");
		return(-1);
	}
	if ((fd = fopen(fname, "w")) == NULL) {
		(void) fprintf(stderr,"\nFailed to create temp file %s\n",fname);
		return(-1);
	}
	fprintf(fd, "%s", str);
	fclose(fd);
	(void) sprintf(cmd, "sh %s", fname);
	if (dbglvl >= 5)
		fprintf(stderr, ">> system(%s)\n", cmd);
	if (dbglvl >= 7) {
		char	dbgcmd[512];
		sprintf(dbgcmd, "cat %s | sed 's/^/DBG:/'", fname);
		(void) system(dbgcmd);
	}
	rv = system(cmd);
	if (dbglvl < 10)
		unlink(fname);
	if ((rv < 0) || ((rv & 0xff) != 0))
		return(-1);
	return((rv & 0xff00) >> 8);
}

static	int
present_menu() {
	int	i, rv;
	int	first = 1;

	dflt = -1;
	for (i=0; i < choice_count ;i++) {
		choices[i].allowed = 1;
		if (choices[i].preqsh) {
			rv = dump_and_execute(choices[i].preqsh);
			if (rv == -1)
				return(-1);
			choices[i].allowed = (rv == 0);
		}
		if (!choices[i].allowed)
			continue;

		if (first) {
			first = 0;
			if (choices[i].abb_name == 'Q')
				return(-1);
			fprintf(stderr,
				"\n%s%s",
				menu_title,
				menu_title[0] != '\0' ? "\n\n" : "");
		}
			
		choices[i].cprio = 0;
		if (choices[i].priosh) {
			rv = dump_and_execute(choices[i].priosh);
			if (rv == -1)
				return(-1);
			choices[i].cprio = rv;
		}
		if (options & OPT_SELECTION) {
			fprintf(stderr, "\t%c - %s\n", choices[i].abb_name,
				choices[i].fullname);
		} else {
			fprintf(stderr, "\t(%c) - %s\n", choices[i].abb_name,
				choices[i].fullname);
		}
		if (choices[i].cprio > 0 &&
		    (dflt<0 || choices[i].cprio>choices[dflt].cprio)) {
			dflt = i;
		}
	}

	if (dflt >= 0) {
		sprintf(prompt, "\n\tEnter Choice (<cr> == '%c') ? ",
			choices[dflt].abb_name);
	} else {
		sprintf(prompt, "\n\tEnter Choice ? ");
	}
	fprintf(stderr, "%s", prompt);
	return(0);
}

static	int
STRCMP(s1, s2)
char	*s1, *s2;
{
	while (*s1 != '\0' && *s2 != '\0') {
		if (toupper(*s1++) != toupper(*s2++))
			return(1);
	}
	return((*s1 == *s2) ? 0 : 1);
}

static	int
STRNCMP(s1, s2, sz)
char	*s1, *s2;
int	sz;
{
	while (sz-- && *s1 != '\0' && *s2 != '\0') {
		if (toupper(*s1++) != toupper(*s2++))
			return(1);
	}
	return(((sz < 0) || (*s1 == *s2)) ? 0 : 1);
}

static	void
give_help(str)
char	*str;
{
	char	*cmd;
	int	i;

	if (cmd = strtok(str, " "))
		cmd = strtok(NULL, "");
	for (i=0; i < choice_count ;i++) {
		if (!choices[i].allowed)
			continue;
		if (cmd != NULL) {
			if (cmd[1] == '\0') {
				if (toupper(cmd[0]) != choices[i].abb_name)
					continue;
			} else if (STRCMP(cmd, choices[i].fullname) != 0) {
				continue;
			}
		}
		fprintf(stderr, "\n(%c) - %s\n%s", choices[i].abb_name,
			choices[i].fullname, choices[i].helpmsg);
	}
	return;
}

static	int
get_choice()
{
	char	input[512];
	int	i;

	while (gets(input)) {
		if (input[0] == '\0') {
			if (dflt >= 0)
				return(dflt);
			fprintf(stderr, "\n\tNo default available, try again\n");
			if (present_menu() < 0)
				return(-1);
			continue;
		}

		if (input[0] == '!') {
			if (input[1] == '!') {
				if (shellscript[0] != '\0')
					system(shellscript);
				else
					fprintf(stderr,
						"\n\tNo saved shell script\n");
				if (present_menu() < 0)
					return(-1);
				continue;
			}
			if (input[1] != '\0') {
				strcpy(shellscript, input+1);
				system(shellscript);
			}
			if (present_menu() < 0)
				return(-1);
			continue;
		}

		if ((input[0] == '?' && strchr(" ", input[1])) ||
		    (toupper(input[0]) == 'H' && strchr(" ", input[1])) ||
		    (STRNCMP(input,"HELP",4) == 0 && strchr(" ", input[4]))) {
			give_help(input);
			if (present_menu() < 0)
				return(-1);
			continue;
		}

		for (i=0; i < choice_count ;i++) {
			if (input[1] == '\0' &&
			    toupper(input[0]) == choices[i].abb_name) {
				if (choices[i].allowed)
					return(i);
				break;
			}
			if (STRCMP(input, choices[i].fullname) == 0) {
				if (choices[i].allowed)
					return(i);
				break;
			}
		}
		fprintf(stderr, "\n\tIllegal selection (%s), try again\n", input);
		if (present_menu() < 0)
			return(-1);
	}
}

main(argc, argv)
int	argc;
char	*argv[];
{
	FILE	*fd;
	int	rv, indx, ch;
	extern	int	optind;
	extern	char	*optarg;

	while ((ch = getopt(argc, argv, "d:")) != EOF) {
		switch(ch) {
		case 'd':
			dbglvl = atoi(optarg);
			break;
		}
	}

	if ((argc-optind) != 1) {
		fprintf(stderr, "argc/%d, optind/%d, dbglvl/%d\n", argc, optind, dbglvl);
		usage(argv[0]);
		exit(1);
	}

	if ((fd = fopen(argv[optind], "r")) == NULL) {
		(void) fprintf(stderr,"\nError opening %s for reading\n",argv[optind]);
		exit(1);
	}

	while ((rv = addchoice(fd)) > 0) {
		continue;
	}
	fclose(fd);

	if (rv < 0) {
		(void) fprintf(stderr, "\nError processing menu file %s\n",
				argv[optind]);
		exit(1);
	}

	if (!(options & OPT_SELECTION) && (addquit() < 0 || addhelp() < 0))
		exit(1);

	while(1) {
		if (present_menu() < 0)
			break;
		if ((indx = get_choice()) < 0)
			break;
		if (choices[indx].abb_name == 'Q')
			break;
		(void) dump_and_execute(choices[indx].shell);
		if (options & OPT_SELECTION)
			break;
	}
	exit(0);
}
