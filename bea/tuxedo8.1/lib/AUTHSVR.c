/*	Copyright (c) 1997 BEA Systems, Inc.
  	All rights reserved

  	THIS IS UNPUBLISHED PROPRIETARY
  	SOURCE CODE OF BEA Systems, Inc.
  	The copyright notice above does not
  	evidence any actual or intended
  	publication of such source code.
*/

/*	Copyright (c) 1995 Novell, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Novell, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) tuxedo/cmdtux/SAUTHSVR.c	$Revision: 1.5 $" */
#include <tmenv.h>
#ifndef NOWHAT
static	char	sccsid[] = "@(#) tuxedo/cmdtux/SAUTHSVR.c	$Revision: 1.5 $";
#endif

/*
	Server to perform user authentication.

	Build using:
	TUXDIR=<path> buildserver -f AUTHSVR.c -o AUTHSVR

	This is a sample for an application building their own
	authentication server.  This is not the code that generates
	$TUXDIR/bin/AUTHSVR. DO NOT CLOBBER THAT PROGRAM.  INSTALL
	YOUR APPLICATION AUTHSVR IN $APPDIR.
 */
#include <stdio.h>
#include <sys/types.h>
#include <Uunix.h>
#include <sys/stat.h>
#include <atmi.h>
#include <tpadm.h>
#include <userlog.h>

/*
 * crypt() is an interface to an OS encryption function.
 * WARNING: on many systems, crypt() may only work on up to 8
 * character passwords.
 * key is the user's typed password; salt
 * is a two-character string chosen from the set [a-zA-Z0-9./]
 * that is used to perturb the DES algorithm.  It returns a pointer
 * to the encrypted password, or NULL on error.
 */

#define HASHSIZE 100
#define HASHTBL	 (HASHSIZE+1)
#define WILDCARD(NM) (((NM)[0]=='*')&&((NM)[1]=='\0'))

static	char	*passfile = "/etc/passwd";
static	int	nocache;

struct namelist  {
	char  pw_name[MAXTIDENT+1];
	char  pw_cname[MAXTIDENT+1];
	char  pw_passwd[MAXTIDENT+1];
	int   uid;
	struct namelist *next;
};

static struct namelist *hashtab[HASHTBL];
static	struct	stat	statbuf;

static	void	freecache _((void));
static	int	initcache _((void));
static	int	hash _((char *s));
static	struct	namelist *lookup _((char *, char *, int));
static	struct	namelist *install _((struct namelist *info));
static	struct	namelist *getpwinfo _((char *, char *));
static	int	myfgetpwent _((FILE *, struct namelist *));

/*
 * mystrtok is very similar to strtok with the exception that it does not
 * evaluate consecutive delimiter characters as one delimiter but rather as
 * individual delimeters separating empty fields.
 */

static	char *
#ifdef _TMPROTOTYPES
mystrtok(char *s, char *del)
#else
mystrtok(s,del)
char	*s;
char	*del;
#endif
{
	static	char *p = NULL;
	char	*r;

	if (s != NULL) {
		p = s;
	}
	if ((p == NULL) || (*p == '\0')) {
		return(NULL);
	}
	r = p;
	while (strchr(del,*p) == NULL) {
		p++;
	}
	if (*p != '\0') {
		*p++ = '\0';
	}
	return(r);
}

int
#ifdef _TMPROTOTYPES
tpsvrinit(int argc, char **argv)
#else
tpsvrinit(argc,argv)
int argc;
char *argv[];
#endif
{
	int c;

	while((c = getopt(argc,argv,"f:n")) != EOF) {
		switch(c) {
		case 'f':
			passfile = optarg;
			break;
		case 'n':
			nocache = 1;
			break;
		default:
			break;
		}
	}
	if(stat(passfile, &statbuf) == -1) {
		userlog("Cannot get status of password file");
		return(-1);
	}
	/* Prime the cache */
	if(!nocache) {
		if(initcache() == -1) {
			return(-1);
		}
	}
	return(1);
}

void
#ifdef _TMPROTOTYPES
tpsvrdone(void)
#else
tpsvrdone()
#endif
{
	(void)userlog("AUTHSVR terminating");
	return;
}

#ifdef __cplusplus
extern "C"
#endif
void
#ifdef _TMPROTOTYPES
AUTHSVC(TPSVCINFO *tpsvcinfo)
#else
AUTHSVC(tpsvcinfo)
TPSVCINFO *tpsvcinfo;
#endif
{

	char	*pass;
	long	appkey;
	struct	namelist	*np;
	struct	stat	newbuf;
	TPINIT	*tpinfo;

	tpinfo = (TPINIT *) tpsvcinfo->data;

	/* NULL terminate passwd if it is not already so */
	pass = (char *)&tpinfo->data;
	if(pass[tpinfo->datalen-1] != '\0') {
		pass[tpinfo->datalen-1] = '\0';
	}
	if(nocache)
		np = getpwinfo(tpinfo->usrname, tpinfo->cltname);
	else {
		if(stat(passfile, &newbuf) == -1) {
			userlog("Cannot get status of password file");
			tpreturn(TPFAIL, -1, (char *)NULL, 0, 0);
		}
		if(newbuf.st_mtime != statbuf.st_mtime) {
			freecache();
			if(initcache() == 0)
				statbuf = newbuf;
			else {
				tpreturn(TPFAIL, -1, (char *)NULL, 0, 0);
			}
		}
		np = lookup(tpinfo->usrname, tpinfo->cltname, 0);
	}

	if(np != NULL) {
		pass=(char *)crypt((char *)&(tpinfo->data), np->pw_passwd);
		if(pass && strcmp(pass,(char *)np->pw_passwd) == 0) {
			/* 
			 * If this user is the system administrator or operator
			 * then a special key is assigned; otherwise, just use
			 * the user id of this user once they pass auth.
			 */
			if (strcmp(tpinfo->cltname, "tpsysadm") == 0)
				appkey = (long)0x80000000;
			else if (strcmp(tpinfo->cltname, "tpsysop") == 0)
				appkey = (long)0xC0000000;
			else
				appkey = (long)np->uid;
			tpreturn(TPSUCCESS, appkey, (char *)NULL, 0, 0);
		}
	}
	(void)userlog("Authentication failed for user %s/%s",
		tpinfo->usrname, tpinfo->cltname);
	tpreturn(TPFAIL, -1, (char *)NULL, 0, 0);
}


static	int
#ifdef _TMPROTOTYPES
hash(char *s)
#else
hash(s)
char *s;
#endif
{
	int hashval;

	if (WILDCARD(s))
		return(HASHSIZE);
	for (hashval = 0 ; *s != '\0'; )
		hashval += *s++;
	return(hashval % HASHSIZE);
}

static struct namelist *
#ifdef _TMPROTOTYPES
lookup(char *un, char *cn, int exact)
#else
lookup(un, cn, exact)
char  *un;
char  *cn;
int	exact;
#endif
{
	struct namelist *p, *wc = NULL;

	/*
	 * Find a match for the username and client name provided by the user.
	 * Note that there are four types of entries in the password file/cache.
	 * They are listed below in order of matching precedence when validating
	 * a user against the file.
	 *	1. Exact username/exact clientname
	 *	2. Wildcard username (*)/exact clientname
	 *	3. Exact username/wildcard clientname (*)
	 *	4. Wildcard username (*)/wildcard clientname (*)
	 * Note that the reserved client names tpsysadm and tpsysop are
	 * special cases and are not allowed to match wildcard clientnames
	 * in the password file.
	 */

	if (!exact && (WILDCARD(un) || WILDCARD(cn))) {
		(void)userlog("Wildcard username and/or clientname presented");
	}

	/*
	 * First look for exact match on user name AND client name, remember
	 * if we see a match on user name with a wildcard client name.
	 */
	for (p = hashtab[hash(un)] ; p != NULL ; p = p->next) {
		if (strcmp(un, p->pw_name) != 0) {
			continue;
		}
		if (strcmp(cn, p->pw_cname) == 0) {
			return(p);
		}
		if (!exact && (WILDCARD(p->pw_cname)) &&
		    (strcmp(cn,"tpsysadm")!=0) && (strcmp(cn,"tpsysop")!=0)) {
			wc = p;	/* Save client wildcard match */
		}
	}
	if (exact) {
		return(NULL);
	}
	/*
	 * Now look in wildcard user name list and see if we find either
	 * a match on client name or a double wildcard entry.  Only match
	 * a double wildcard if we haven't found another wildcard yet.
	 */
	for (p = hashtab[HASHSIZE] ; p != NULL ; p = p->next) {
		if ((wc == NULL) && WILDCARD(p->pw_cname) &&
		    (strcmp(cn,"tpsysadm")!=0) && (strcmp(cn,"tpsysop")!=0)) {
			/* Double wildcard is last on list so we can return */
			return(p);
		}
		/*
		 * Exact match on client name, this is highest precedence 
		 * wildcard match and should be returned immediately.
		 */
		if (strcmp(cn, p->pw_cname) == 0) {
			return(p);
		}
	}
	/*
	 * No match in wildcard usrname field so return wildcard client name
	 * entry in exact usrname list if found, otherwise NULL.
	 */
	return(wc);
}

static struct namelist *
#ifdef _TMPROTOTYPES
install(struct namelist *info)
#else
install(info)
struct namelist *info;
#endif
{
	struct namelist  *np, *ep;
	int hashval;

	np = lookup(info->pw_name,info->pw_cname,1);
	if (np == (struct namelist *)NULL) {
		np = (struct namelist *)malloc(sizeof(struct namelist));
		if (np == (struct namelist *)NULL) {
			return(NULL);
		}
		*np = *info;
		hashval = hash(np->pw_name);
		if (WILDCARD(info->pw_cname) &&
		    (hashtab[hashval] != (struct namelist *)NULL)) {
			/* Need to put at end of list so it's found last */
			for (ep=hashtab[hashval];
			     ep->next != (struct namelist *)NULL;
			     ep = ep->next) {
				continue;
			}
			ep->next = np;
		} else {
			np->next = hashtab[hashval];
			hashtab[hashval] = np;
		}
	} else {
		/* warning:  already in cache */
		userlog("Duplicate id [%s/%s] in password file",
		info->pw_name, info->pw_cname);
	}
	return(np);
}

static int
#ifdef _TMPROTOTYPES
myfgetpwent(FILE *fp, struct namelist *node)
#else
myfgetpwent(fp, node)
FILE *fp;
struct namelist *node;
#endif
{
	char	line[BUFSIZ+1];
	char	*val;

	/*
	 * this code assumes that:
	 * 1.  the password or password-like file is readable
	 * 2.  the format is
	 *	login_name:password:uid:gid:comment:other stuff
	 * 3.  we cannot use fgetpwent since it is not POSIX-compliant
	 *
	 * If comment begins with "TPCLTNM,", then we take the stuff after
	 * the comma as the client name.  This allows for a particular user
	 * to have different passwords for different client names.  * is
	 * allowed as the client name which acts as a wildcard.  Likewise,
	 * for the user name.  Wildcard user and client names are sorted
	 * to the end of the list by tpaddusr(1) so they will be the last
	 * thing matched.
	 */
	for(;;) {
		if (fgets(line, BUFSIZ, fp) == NULL) {
			/* valid entry not found */
			return(-1);
		}
		/* Get pointer to login name value */
		if ((val = mystrtok(line, ":\n")) == NULL) {
			continue;
		}
		(void)strncpy(node->pw_name, val, sizeof(node->pw_name));
		node->pw_name[sizeof(node->pw_name)-1] = '\0';

		/* Get pointer to password value */
		if ((val = mystrtok(NULL, ":\n")) == NULL) {
			continue;
		}
		(void)strncpy(node->pw_passwd, val, sizeof(node->pw_passwd));
		node->pw_passwd[sizeof(node->pw_passwd)-1] = '\0';

		/* Get pointer to uid value */
		if (((val = mystrtok(NULL, ":\n")) == NULL) ||
		    (val[0] == '\0') ||
		    (((strcmp(val,"-1") != 0)) &&
		     (strspn(val,"0123456789") != strlen(val)))) {
			/* uid is null or non-numeric */
			continue;
		}
		node->uid = atoi(val);
		/*
		 * Get pointer to gid value so we can skip it.  It's ok if
		 * it's missing, that just means we shouldn't look for a
		 * clientname set by tpaddusr(1) in the following comment.
		 */
		(void)strcpy(node->pw_cname,"*");	/* default value */
		if ((val = mystrtok(NULL, ":\n")) != NULL) {
			/* Now get the comment and see if it's the right form */
			if (((val = mystrtok(NULL, ":\n")) != NULL) &&
			    (strncmp(val, "TPCLTNM,", 8) == 0)) {
				(void)strncpy(node->pw_cname, val+8,
						sizeof(node->pw_cname));
				node->pw_cname[sizeof(node->pw_cname)-1] = '\0';
			}
		}
		node->next = (struct namelist *)NULL;
		break;
	}
	return(1);
}

static	int
#ifdef _TMPROTOTYPES
initcache(void)
#else
initcache()
#endif
{
	FILE	*fp;
	struct	namelist	node;


	/* Open the password file */
	if((fp=fopen(passfile, "r")) == (FILE *)NULL) {
		(void)userlog("Cannot open password file %s", passfile);
		return(-1);
	}

	for(;;) {
		if (myfgetpwent(fp, &node) < 0)
			break;

		if(install(&node) == NULL) {
			(void)fclose(fp);
			return(-1);
		}
	}

	/* Done with the file */
	(void)fclose(fp);
	return(0);
}

#ifdef	DEBUG
#ifdef __cplusplus
extern "C"
#endif
void
#ifdef _TMPROTOTYPES
_PRT_CACHE(TPSVCINFO *tpsvcinfo)
#else
_PRT_CACHE(tpsvcinfo)
TPSVCINFO *tpsvcinfo;
#endif
{
	int	i;
	struct namelist *p;

	if(nocache)
		(void)fprintf(stdout, "Cache is disabled\n");
	else {
		(void)fprintf(stdout, "Contents of cache\n");
		for(i=0; i<HASHTBL; i++) {
			for (p = hashtab[i]; p != NULL ; p = p->next)
				(void)fprintf(stdout,"%s:%s:%d:%s\n",
						p->pw_name,
						p->pw_passwd,
						p->uid,
						p->pw_cname);
		}
	}
	(void)fflush(stdout);
	tpreturn(TPSUCCESS, 0, tpsvcinfo->data, tpsvcinfo->len, 0);
}
#endif

static	void
#ifdef _TMPROTOTYPES
freecache(void)
#else
freecache()
#endif
{
	int	i;
	struct	namelist	*p, *prev;

	for(i=0; i<HASHTBL; i++) {
		p = hashtab[i];
		while(p != NULL) {
			prev = p;
			p = p->next;
			prev->next = NULL;
			free(prev);
		}
		hashtab[i] = (struct namelist *)NULL;
	}
	return;
}

static struct namelist *
#ifdef _TMPROTOTYPES
getpwinfo(char *un, char *cn)
#else
getpwinfo(un, cn)
char  *un;
char  *cn;
#endif
{
#define WUSR	1
#define WCLT	2
#define WUNC	3

	FILE	*fp;
	static	struct	namelist	node;
	struct	namelist wildcard;
	int	found = 0;

	(void)memset((char *)&wildcard, 0, sizeof(wildcard));
	if (WILDCARD(un) || WILDCARD(cn)) {
		(void)userlog("Wildcard username and/or clientname presented");
		return(NULL);
	}
	/* Open the password file */
	if((fp=fopen(passfile, "r")) == (FILE *)NULL) {
		(void)userlog("Cannot open password file");
		return(NULL);
	}

	for(;;) {
		if (myfgetpwent(fp, &node) < 0) {
			/* entry not found */
			(void) fclose(fp);
			if (found) {
				node = wildcard;
				return(&node);
			}
			return(NULL);
		}
		if ((strcmp(un, node.pw_name) == 0) &&
		     (strcmp(cn, node.pw_cname) == 0)) {
			/* Exact match on both user name and client name */
			break;
		}
		/*
		 * Check for exact client name match with a wildcard user name
		 * this has highest precedence.  If we've already found a
		 * match of this type then no need to examine wildcard info.
		 */
		if (found == WUSR)
			continue;
		if (strcmp(cn, node.pw_cname) == 0) {
			if (WILDCARD(node.pw_name)) {
				/* USRNAME wildcard match */
				found = WUSR;
				wildcard = node;
			}
			continue;
		}
		if (found == WCLT)
			continue;
		if (strcmp(un, node.pw_name) == 0) {
			if (WILDCARD(node.pw_cname) &&
			    (strcmp(cn,"tpsysadm") != 0) &&
			    (strcmp(cn,"tpsysop")  != 0)) {
				/* CLTNAME wildcard match */
				found = WCLT;
				wildcard = node;
			}
			continue;
		}
		if (found == WUNC)
			continue;
		if (WILDCARD(node.pw_name) && WILDCARD(node.pw_cname) &&
		    (strcmp(cn,"tpsysadm")!=0) && (strcmp(cn,"tpsysop")!=0)) {
			/* Double wildcard match */
			found = WUNC;
			wildcard = node;
		}
	}
	
	/* Done with the file */
	(void)fclose(fp);
	return(&node);
}
