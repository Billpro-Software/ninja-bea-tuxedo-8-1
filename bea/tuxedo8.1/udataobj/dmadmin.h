/*	Copyright (c) 1992 UNIX System Laboratories, Inc.
        All rights reserved

        THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF Unix System Laboratories, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
#ifndef NOWHAT
static	char h_dmadmin[] = "@(#) domain/gw/include/dmadmin	$Revision: 1.12 $";
#endif

/* #ident	"@(#) domain/gw/include/dmadmin	$Revision: 1.12 $" */

/*
	Warning: This file should not be changed in any
	way, doing so will destroy the compatibility with TUXEDO programs
	and libraries.
*/
/*	ADMIN FIELD ENTRIES */

/* operations in dmadmin translated into admin API operations in DMADM */
#define TA_FIRSTCF	1
#define TA_NEXTCF	2	
#define TA_RETRIEVECF	3
#define TA_ADDCF	4	
#define TA_UPDATECF	5	
#define TA_DELETECF	6

/* operations */
#define TA_SET		10
#define TA_GET		11
#define TA_GETNEXT	12

/* operations */
#define TA_ADVERTISE	15
#define TA_UNADVERTISE	16
#define TA_SUSPEND	17
#define TA_RESUME	18

/* states */
#define TA_NEW		20
#define TA_UPDATE	21
#define TA_INVALID	22	
#define TA_ACTIVE	23
#define TA_INACTIVE	24

/* classes */
#ifndef DM_GATEWAYS
#define DM_RESOURCES	1	
#define DM_LDOMAINS	2
#define DM_RDOMAINS	3
#define DM_TDOMAINS	4
#define DM_OSITPS	5
#define DM_LSERVICES	6
#define DM_RSERVICES	7
#define DM_ROUTINGS	8
#define DM_ACLS	9
#define DM_PASSWORDS	10
#define DM_GATEWAYS	11
#define GW_INFO	12
#define GW_TRANSACTIONS	13
#define GW_AUDIT	14
#define DM_SNADOMS	15
#define DM_RDOMSECS	16
#define DM_RDOMUSRS	17
/* SNA2 Begin - Fields added by SNA Connect Version 2 */
#define DM_SNACRMS	18
#define DM_SNASTACKS	19
#define DM_SNALINKS	20
/* SNA2 End */
#define DM_TOPEND	21
#define DM_CONNECTION	22
/* Added for OSITP V4.0 */
#define DM_OSITPX	23
#endif

/* dmconfig field values */
/*	fname	fldid            */
/*	-----	-----            */
#define	TA_STATUS	((FLDID)41060)	/* number: 100	 type: string */
#define	TA_ERROR	((FLDID)101)	/* number: 101	 type: short */
#define	TA_OPERATION	((FLDID)102)	/* number: 102	 type: short */
#define	TA_CLASS	((FLDID)103)	/* number: 103	 type: short */
#define	TA_BADFLD	((FLDID)8296)	/* number: 104	 type: long */
#define	TA_OCCURS	((FLDID)105)	/* number: 105	 type: short */
#define	TA_BADFLDNAME	((FLDID)41066)	/* number: 106	 type: string */

#ifndef REDUCE_CPP

 /* DM_SNADOM */
#define	TA_SNADOM	((FLDID)41170)	/* number: 210	 type: string */
#define	TA_LUNAME	((FLDID)41171)	/* number: 211	 type: string */
#define	TA_MODENAME	((FLDID)41172)	/* number: 212	 type: string */
#define	TA_NETID	((FLDID)41173)	/* number: 213	 type: string */
#define	TA_SECTYPE	((FLDID)41174)	/* number: 214	 type: string */
#define	TA_SYMDESTNAME	((FLDID)41175)	/* number: 215	 type: string */
#define	TA_MAXSNASESS	((FLDID)216)	/* number: 216	 type: short */
#define	TA_LCONV	((FLDID)41177)	/* number: 217	 type: string */

 /* DM_RESOURCES */
#define	TA_VERSION	((FLDID)41180)	/* number: 220	 type: string */
#define	TA_DMKEY	((FLDID)41181)	/* number: 221	 type: string */
#define	TA_ENCDMKEY	((FLDID)41182)	/* number: 222	 type: string */
#define	TA_DMMAGIC	((FLDID)41183)	/* number: 223	 type: string */
#define	TA_ENCDMMAGIC	((FLDID)41184)	/* number: 224	 type: string */

 /* DM_TDOMAIN */
#define	TA_TDOM	((FLDID)41185)	/* number: 225	 type: string */
#define	TA_NWADDR	((FLDID)41186)	/* number: 226	 type: string */
#define	TA_NWADDRLEN	((FLDID)227)	/* number: 227	 type: short */
#define	TA_NWDEVICE	((FLDID)41188)	/* number: 228	 type: string */
#define	TA_NWIDLETIME	((FLDID)8421)	/* number: 229	 type: long */

 /* DM_OSITP */
#define	TA_OSITP	((FLDID)41190)	/* number: 230	 type: string */
#define	TA_APT	((FLDID)41191)	/* number: 231	 type: string */
#define	TA_APTLEN	((FLDID)232)	/* number: 232	 type: short */
#define	TA_AEQ	((FLDID)41193)	/* number: 233	 type: string */
#define	TA_AEQLEN	((FLDID)234)	/* number: 234	 type: short */
#define	TA_AET	((FLDID)41195)	/* number: 235	 type: string */
#define	TA_ACN	((FLDID)41196)	/* number: 236	 type: string */
#define	TA_ACN2	((FLDID)237)	/* number: 237	 type: short */
#define	TA_APID	((FLDID)238)	/* number: 238	 type: short */
#define	TA_AEID	((FLDID)239)	/* number: 239	 type: short */
#define	TA_PROFILE	((FLDID)41200)	/* number: 240	 type: string */
#define	TA_PROFILE2	((FLDID)241)	/* number: 241	 type: short */
#define	TA_URCH	((FLDID)41202)	/* number: 242	 type: string */

 /* DM_LOCAL_DOMAIN */
#define	TA_LDOM	((FLDID)41203)	/* number: 243	 type: string */
#define	TA_SVRGRP	((FLDID)41204)	/* number: 244	 type: string */
#define	TA_TYPE	((FLDID)41205)	/* number: 245	 type: string */
#define	TA_DOMAINID	((FLDID)41206)	/* number: 246	 type: string */
#define	TA_DMTLOGDEV	((FLDID)41207)	/* number: 247	 type: string */
#define	TA_AUDITLOG	((FLDID)41208)	/* number: 248	 type: string */
#define	TA_BLOCKTIME	((FLDID)249)	/* number: 249	 type: short */
#define	TA_DMTLOGNAME	((FLDID)41210)	/* number: 250	 type: string */
#define	TA_DMTLOGSIZE	((FLDID)8443)	/* number: 251	 type: long */
#define	TA_MAXDATALEN	((FLDID)8444)	/* number: 252	 type: long */
#define	TA_MAXRDOM	((FLDID)8445)	/* number: 253	 type: long */
#define	TA_MAXRDTRAN	((FLDID)254)	/* number: 254	 type: short */
#define	TA_MAXTRAN	((FLDID)255)	/* number: 255	 type: short */
#define	TA_MAXSENDLEN	((FLDID)8448)	/* number: 256	 type: long */
#define	TA_SECURITY	((FLDID)41217)	/* number: 257	 type: string */
#define	TA_SECURITY2	((FLDID)258)	/* number: 258	 type: short */
#define	TA_TUXCONFIG	((FLDID)41219)	/* number: 259	 type: string */
#define	TA_TUXOFFSET	((FLDID)8452)	/* number: 260	 type: long */
#define	TA_BLOB_SHM_SIZE	((FLDID)8453)	/* number: 261	 type: long */

 /* DM_REMOTE_DOMAIN */
#define	TA_RDOM	((FLDID)41222)	/* number: 262	 type: string */
#define	TA_LOOPBACK	((FLDID)263)	/* number: 263	 type: short */

 /* DM_ACCESS_CONTROL */
#define	TA_ACLNAME	((FLDID)41224)	/* number: 264	 type: string */
#define	TA_NRDOM	((FLDID)265)	/* number: 265	 type: short */
#define	TA_ACL_RDOM	((FLDID)41226)	/* number: 266	 type: string */

 /* DM_LOCAL_SERVICES */
#define	TA_BUFTYPE	((FLDID)41227)	/* number: 267	 type: string */
#define	TA_BUFSTYPE	((FLDID)41228)	/* number: 268	 type: string */
#define	TA_INBUFTYPE	((FLDID)41229)	/* number: 269	 type: string */
#define	TA_OBUFTYPE	((FLDID)41230)	/* number: 270	 type: string */
#define	TA_OBUFSTYPE	((FLDID)41231)	/* number: 271	 type: string */
#define	TA_OUTBUFTYPE	((FLDID)41232)	/* number: 272	 type: string */
#define	TA_RNAME	((FLDID)41233)	/* number: 273	 type: string */
#define	TA_SERVICENAME	((FLDID)41234)	/* number: 274	 type: string */

 /* DM_ROUTING */
#define	TA_ROUTINGNAME	((FLDID)41235)	/* number: 275	 type: string */
#define	TA_FIELDNAME	((FLDID)41236)	/* number: 276	 type: string */
#define	TA_RANGES	((FLDID)41237)	/* number: 277	 type: string */

 /* DM_REMOTE_SERVICES */
#define	TA_AUTOTRAN	((FLDID)41238)	/* number: 278	 type: string */
#define	TA_AUTOTRAN2	((FLDID)279)	/* number: 279	 type: short */
#define	TA_CONV	((FLDID)41240)	/* number: 280	 type: string */
#define	TA_CONV2	((FLDID)281)	/* number: 281	 type: short */
#define	TA_LOAD	((FLDID)282)	/* number: 282	 type: short */
#define	TA_PRIO	((FLDID)283)	/* number: 283	 type: short */
#define	TA_TRANTIME	((FLDID)8476)	/* number: 284	 type: long */
#define	TA_SRVGRP	((FLDID)41245)	/* number: 285	 type: string */
#define	TA_SRVID	((FLDID)286)	/* number: 286	 type: short */
#define	TA_STATE	((FLDID)287)	/* number: 287	 type: short */
#define	TA_ACTIVITY	((FLDID)288)	/* number: 288	 type: short */
#define	TA_ALLSTATS	((FLDID)289)	/* number: 289	 type: short */
#define	TA_DOMSTATS	((FLDID)290)	/* number: 290	 type: short */
#define	TA_OPTION	((FLDID)291)	/* number: 291	 type: short */
#define	TA_ON	((FLDID)292)	/* number: 292	 type: short */
#define	TA_OFF	((FLDID)293)	/* number: 293	 type: short */
#define	TA_RESET	((FLDID)294)	/* number: 294	 type: short */
#define	TA_TOGGLE	((FLDID)295)	/* number: 295	 type: short */
#define	TA_STATISTICS	((FLDID)296)	/* number: 296	 type: short */
#define	TA_AUDIT	((FLDID)297)	/* number: 297	 type: short */
#define	TA_TRAN_STATE	((FLDID)8490)	/* number: 298	 type: long */
#define	TA_MTYPE	((FLDID)41260)	/* number: 300	 type: string */
#define	TA_MAX_LISTENING_EP	((FLDID)301)	/* number: 301	 type: short */
#define	TA_ENCODING_LEVEL	((FLDID)302)	/* number: 302	 type: short */
#define	TA_NUMREQLSVC	((FLDID)8492)	/* number: 300	 type: long */
#define	TA_NUMREQRSVC	((FLDID)8493)	/* number: 301	 type: long */
#define	TA_NUMREPLSVC	((FLDID)8494)	/* number: 302	 type: long */
#define	TA_NUMREPRSVC	((FLDID)8495)	/* number: 303	 type: long */
#define	TA_NUMREQACT	((FLDID)8496)	/* number: 304	 type: long */
#define	TA_NUMREQC	((FLDID)8497)	/* number: 305	 type: long */
#define	TA_NUMREQF	((FLDID)8498)	/* number: 306	 type: long */
#define	TA_NUMCONVACT	((FLDID)8499)	/* number: 307	 type: long */
#define	TA_NUMCONVLOC	((FLDID)8500)	/* number: 308	 type: long */
#define	TA_NUMCONVLSND	((FLDID)8501)	/* number: 309	 type: long */
#define	TA_NUMCONVREM	((FLDID)8502)	/* number: 310	 type: long */
#define	TA_NUMCONVRSND	((FLDID)8503)	/* number: 311	 type: long */
#define	TA_NUMEVACT	((FLDID)8504)	/* number: 312	 type: long */
#define	TA_NUMEVNSUSP	((FLDID)8505)	/* number: 313	 type: long */
#define	TA_NUMEVTSUSP	((FLDID)8506)	/* number: 314	 type: long */
#define	TA_NUMTRAN	((FLDID)8507)	/* number: 315	 type: long */
#define	TA_NUMTRANCMT	((FLDID)8508)	/* number: 316	 type: long */
#define	TA_NUMTRANHCMT	((FLDID)8509)	/* number: 317	 type: long */
#define	TA_NUMTRANHRLB	((FLDID)8510)	/* number: 318	 type: long */
#define	TA_NUMTRANRLB	((FLDID)8511)	/* number: 319	 type: long */
#define	TA_STAT_RESET_TIME	((FLDID)8512)	/* number: 320	 type: long */
#define	TA_SHM_CONTENTIONS	((FLDID)8513)	/* number: 321	 type: long */
#define	TA_LOG_CONTENTIONS	((FLDID)8514)	/* number: 322	 type: long */
#define	TA_PASSWD	((FLDID)41285)	/* number: 325	 type: string */
#define	TA_ENCPASSWD	((FLDID)41286)	/* number: 326	 type: string */
#define	TA_LPWD	((FLDID)41287)	/* number: 327	 type: string */
#define	TA_RPWD	((FLDID)41288)	/* number: 328	 type: string */
#define	TA_ENC2_LPWD	((FLDID)41289)	/* number: 329	 type: string */
#define	TA_ENC2_RPWD	((FLDID)41290)	/* number: 330	 type: string */
#define	TA_REENCRYPT_PWD	((FLDID)331)	/* number: 331	 type: short */
#define	TA_NUMPROC	((FLDID)8524)	/* number: 332	 type: long */
#define	TA_NUMRDOM	((FLDID)8525)	/* number: 333	 type: long */
#define	TA_PARENTRDOM	((FLDID)41294)	/* number: 334	 type: string */
#define	TA_TRANID	((FLDID)41295)	/* number: 335	 type: string */
#define	VENKAT_SHORT	((FLDID)336)	/* number: 336	 type: short */
#define	VENKAT_LONG	((FLDID)8529)	/* number: 337	 type: long */
#define	VENKAT_FLOAT	((FLDID)24914)	/* number: 338	 type: float */
#define	VENKAT_DOUBLE	((FLDID)33107)	/* number: 339	 type: double */
#define	VENKAT_CHAR	((FLDID)16724)	/* number: 340	 type: char */
#define	VENKAT_STRING	((FLDID)41301)	/* number: 341	 type: string */
#define	VENKAT_CARRAY	((FLDID)49494)	/* number: 342	 type: carray */
#define	TA_PRINNAME	((FLDID)41303)	/* number: 343	 type: string */
#define	TA_RPRINNAME	((FLDID)41304)	/* number: 344	 type: string */
#define	TA_RPRINPASSWD	((FLDID)41305)	/* number: 345	 type: string */
#define	TA_DIRECTION	((FLDID)41306)	/* number: 346	 type: string */
#define	TA_RDOMSEC	((FLDID)41307)	/* number: 347	 type: string */
#define	TA_RDOMUSR	((FLDID)41308)	/* number: 348	 type: string */
#define	TA_CMPLIMIT	((FLDID)8542)	/* number: 350	 type: long */
#define	TA_DMCMPLIMIT	((FLDID)8542)	/* number: 350	 type: long */
#define	TA_MINENCRYPTBITS	((FLDID)8543)	/* number: 351	 type: long */
#define	TA_MAXENCRYPTBITS	((FLDID)8544)	/* number: 352	 type: long */
/* SNA2 Begin - Fields added by SNA Connect Version 2 */
#define	TA_SNALINK	((FLDID)41313)	/* number: 353	 type: string */
#define	TA_LSYSID	((FLDID)41314)	/* number: 354	 type: string */
#define	TA_RSYSID	((FLDID)41315)	/* number: 355	 type: string */
#define	TA_MINWIN	((FLDID)356)	/* number: 356	 type: short */
#define	TA_MAXSYNCLVL	((FLDID)357)	/* number: 357	 type: short */
#define	TA_SNASTACK	((FLDID)41318)	/* number: 358	 type: string */
#define	TA_SNACRM	((FLDID)41319)	/* number: 359	 type: string */
#define	TA_STACKTYPE	((FLDID)41320)	/* number: 360	 type: string */
#define	TA_TPNAME	((FLDID)41321)	/* number: 361	 type: string */
#define	TA_STACKPARMS	((FLDID)41322)	/* number: 362	 type: string */
#define	TA_API	((FLDID)41323)	/* number: 363	 type: string */
#define	TA_FUNCTION	((FLDID)41324)	/* number: 364	 type: string */
#define	TA_CODEPAGE	((FLDID)41325)	/* number: 365	 type: string */
#define	TA_STARTTYPE	((FLDID)41326)	/* number: 366	 type: string */
/* SNA2 End */
#define	TA_CONNECTION_POLICY	((FLDID)41327)	/* number: 367	 type: string */
#define	TA_RETRY_INTERVAL	((FLDID)8560)	/* number: 368	 type: long */
#define	TA_MAXRETRY	((FLDID)8561)	/* number: 369	 type: long */
/* The following added for TOPEND gateway */
#define	TA_TP_SYSTEM	((FLDID)41330)	/* number: 370	 type: string */
#define	TA_TE_PRODUCT	((FLDID)41331)	/* number: 371	 type: string */
#define	TA_TE_FUNCTION	((FLDID)41332)	/* number: 372	 type: string */
#define	TA_TE_TARGET	((FLDID)41333)	/* number: 373	 type: string */
#define	TA_TE_QUALIFIER	((FLDID)8566)	/* number: 374	 type: long */
#define	TA_TE_RTQGROUP	((FLDID)41335)	/* number: 375	 type: string */
#define	TA_TE_RTQNAME	((FLDID)41336)	/* number: 376	 type: string */
/* DMIB additional fields */
#define	TA_BRANCHSTATE	((FLDID)8569)	/* number: 377	 type: long */
#define	TA_BRANCHNETID	((FLDID)41338)	/* number: 378	 type: string */
#define	TA_DMIB	((FLDID)8571)	/* number: 379	 type: long */
#define	TA_DMFAILOVERSEQ	((FLDID)380)	/* number: 380	 type: short */
#define	TA_DMFIELDTYPE	((FLDID)41341)	/* number: 381	 type: string */
#define	TA_CURENCRYPTBITS	((FLDID)8574)	/* number: 382	 type: long */
#define	TA_DMACLPOLICY	((FLDID)41343)	/* number: 383	 type: string */
#define	TA_DMCONNPRINCIPALNAME	((FLDID)41344)	/* number: 384	 type: string */
#define	TA_DMLOCALPRINCIPALNAME	((FLDID)41345)	/* number: 385	 type: string */
#define	TA_DMPRIORITY_TYPE	((FLDID)41346)	/* number: 386	 type: string */
#define	TA_DMINPRIORITY	((FLDID)387)	/* number: 387	 type: short */
#define	TA_DMCREDENTIALPOLICY	((FLDID)41348)	/* number: 388	 type: string */
#define	TA_DMTCPKEEPALIVE	((FLDID)41349)	/* number: 389	 type: string */
#define	TA_DMKEEPALIVE	((FLDID)8582)	/* number: 390	 type: long */
#define	TA_DMKEEPALIVEWAIT	((FLDID)8583)	/* number: 391	 type: long */
#define	TA_ABORT_THRESHOLD	((FLDID)8584)	/* number: 392	 type: long */
/* end REDUCE_CPP */
#endif

#ifndef REDUCE_CPP
#define	TA_DMTBLTYPE	((FLDID)401)	/* number: 401	 type: short */
#define	TA_DMENTRYSIZE	((FLDID)8594)	/* number: 402	 type: long */
#define	TA_DMHASH_INDX	((FLDID)8595)	/* number: 403	 type: long */
#define	TA_DMNBKTS	((FLDID)404)	/* number: 404	 type: short */
#define	TA_DMNUMENTRIES	((FLDID)405)	/* number: 405	 type: short */
#define	TA_DMSHMSIZE	((FLDID)8598)	/* number: 406	 type: long */
/* The following 2 fields have been introduced in release 6.0. These are
 * internal fields of the /Domain feature and as such liable to change.
 * The TA_DMGWOPT field sent by GWADM to DMADM indicates the release/version
 * or functionality level of the sending GWADM.   ONE AND ONLY ONE BIT SHOULD
 * BE SET ON IN THIS BITFIELD..... indicating the version/functionality level
 * of the GWADM.
 * The other field TA_DMADMOPT though sent from DMADM to GWADM starting rel 6,
 * is being implemented for future usage.
 */
#define	TA_DMADMOPT	((FLDID)49559)	/* number: 407	 type: carray */
#define	TA_DMGWOPT	((FLDID)49560)	/* number: 408	 type: carray */
/* The next field is used for conveying the GWADM advertised servicename to 
 * the DMADM.  This again has been introduced in rel 6.0.  This will hide the
 * DMADM from the GWADM servicename computations/conventions/etc.
 */
/*
 * #define	TA_DMGWASVC	((FLDID)41369)	* number: 409	 type: string *
 */
#define	TA_DMGWASVC	((FLDID)41369)	/* number: 409	 type: string */
/* 
 * Fields added for the OSITP V4.0 
 */
#define	TA_OSITPX	((FLDID)41370)	/* number: 410	 type: string */
/* TA_NWADDR string */
/* TA_AET string */
#define	TA_TSEL	((FLDID)41371)	/* number: 411	 type: string */
#define	TA_TAILORPATH	((FLDID)41372)	/* number: 412	 type: string */
#define	TA_PSEL	((FLDID)41373)	/* number: 413	 type: string */
#define	TA_SSEL	((FLDID)41374)	/* number: 414	 type: string */
#define	TA_EXTENSIONS	((FLDID)41375)	/* number: 415	 type: string */
/* TA_MINENCRYPTBITS long */
/* TA_MAXENCRYPTBITS long */
#define	TA_MULTIPLEXING	((FLDID)416)	/* number: 416	 type: short */
#define	TA_DNSRESOLUTION	((FLDID)41377)	/* number: 417	 type: string */
#define	TA_OPTIONS	((FLDID)41378)	/* number: 418	 type: string */
#define	TA_XATMIENCODING	((FLDID)41379)	/* number: 419	 type: string */
/* Local Services adds for OSITP */
#define	TA_COUPLING	((FLDID)41380)	/* number: 420	 type: string */
#define	TA_INRECTYPE	((FLDID)41381)	/* number: 421	 type: string */
#define	TA_INRECSTYPE	((FLDID)41382)	/* number: 422	 type: string */
#define	TA_OUTRECTYPE	((FLDID)41383)	/* number: 423	 type: string */
#define	TA_OUTRECSTYPE	((FLDID)41384)	/* number: 424	 type: string */
/* Remote Services adds for OSITP */
#define	TA_AUTOPREPARE	((FLDID)41385)	/* number: 425	 type: string */
#define	TA_TPSUTTYPE	((FLDID)41386)	/* number: 426	 type: string */
#define	TA_REMTPSUT	((FLDID)41387)	/* number: 427	 type: string */
/* end of OSITP V4.0 adds */
/* end REDUCE_CPP */
#endif

/* return values */
#define TAEDMTYPE	-20	/* error reading the DMTYPE file*/
#define TAEINCONSIS	-19	/* inconsistent specification */
#define TAENOSPACE	-18	/* no space in TUXCONFIG */
#define TAEBLOCK	-17	/* blocking condition */
#define TAEGOTSIG	-16	/* got a signal */
#define TAECONFIG	-15	/* error readin the TUXCONFIG */
#define TAEDUPLICATE	-14	/* tried to add a duplicate record */
#ifndef TAEINVAL
#define TAEINVAL	-13	/* invalid argument */
#endif
#define TAENOTFOUND	-12	/* record not found */
#define TAEOS		-11	/* operating system error */
#ifndef TAEPERM
#define TAEPERM	-10	/* permission error */
#endif
#define TAEPROTO	-9	/* protocol error */
#define TAERANGE	-8	/* field value out of range */
#define TAEREQUIRED	-7	/* field value required but not present */
#define TAESIZE	-6	/* string value too long */
#define TAESVCERR	-5	/* service error */
#define TAESYSTEM	-3	/* system error */
#define TAETIME	-2	/* timeout */
#define TAEUPDATE	-1	/* update not allowed */
#define TAOK		0	/* suceeded */
#define TAUPDATED	1	/* suceeded and updated a record */
#define TAPARTIAL	2	/* suceeded at master; failed elsewhere */
