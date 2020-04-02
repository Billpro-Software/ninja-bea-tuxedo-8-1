/*	Copyright (c) 1997 BEA Systems, Inc.
	All rights reserved

	THIS IS UNPUBLISHED PROPRIETARY
	SOURCE CODE OF BEA Systems, Inc.
	The copyright notice above does not
	evidence any actual or intended
	publication of such source code.
*/
/* #ident	"@(#) objtm/include/CosTransactions_i.h	$Revision: 1.13 $" */


/*
 * This header file contains the declarations of the local Current_Impl and
 * Control_Impl objects on the server.
 */ 

#ifndef _COSTRANSACTIONS_I_H
#define _COSTRANSACTIONS_I_H

#ifndef NOWHAT
static char h_costransactions[] = "@(#)iceberg:include/CosTransactions_i.h  $Revision: 1.13 $";
#endif

#include <ots_c.h>

#include <atmi.h>
#include <tx.h>
#include <tobj_c.h>
#include "errorinfo.hxx"
#include "iop_threads.hxx"
#include "orbimpl.hxx"

#ifdef IOP_THREAD_SAFE
#include <threadexitinterest.hxx>
#endif	/* IOP_THREAD_SAFE */

#if !defined(_AIX) && !defined(__linux__) && !defined(WIN32) && !defined(__sgi) && !defined(UNIXWARE) && !defined(__HP_aCC) && !defined(__BOOL_IS_A_RESERVED_WORD) && !defined(__sun) && !defined(_SEQUENT_)
#define bool	int
#endif

#if !defined(_AIX) && !defined(WIN32)
#define true	1
#define false	0
#endif

class Control_Impl;

class Current_Impl : public Tobj::TransactionCurrent
#ifdef	IOP_THREAD_SAFE
	,ThreadExitInterest
#endif	/* IOP_THREAD_SAFE */
	{

private:
	#define DEFAULT_BEGIN_TIMEOUT  300

	CORBA::Boolean		current_is_valid;
	ErrorInfo		m_error_info;

	CosTransactions::Control_ptr activate_control(Control_Impl*);

public:
	
	class PerThreadInfo
	{
	    public:
#ifdef	IOP_THREAD_SAFE
		PerThreadInfo(IOPTID);
#else	/* IOP_THREAD_SAFE */
		PerThreadInfo();
#endif	/* IOP_THREAD_SAFE */
		~PerThreadInfo();
		unsigned long		m_timeout;
		IOPTID			m_thread_id;
	};

private:

#ifdef	IOP_THREAD_SAFE
	PerThreadInfo * GetPerThreadInfo();
#ifdef	WIN32
#pragma warning(disable: 4251)
#endif	/* WIN32 */
	TDListPtr<PerThreadInfo>	m_per_thread_info;
#ifdef	WIN32
#pragma warning(default: 4251)
#endif	/* WIN32 */
#else	/* IOP_THREAD_SAFE */
	inline PerThreadInfo * GetPerThreadInfo() { return & m_single_thread_info; }
	PerThreadInfo			m_single_thread_info;
#endif	/* IOP_THREAD_SAFE */

public:
	Current_Impl(ORBImpl * orb);
	Current_Impl();
	void invalidate();
	void begin();
		//throw (SubtransactionsUnavailable);
	void commit(CORBA::Boolean report_heuristics);
		//throw(NoTransaction,HeuristicMixed,HeuristicHazard);
	void rollback();
		//throw(NoTransaction);
	void rollback_only();
		//throw(NoTransaction);
	CosTransactions::Status get_status();
	char* get_transaction_name();
	void set_timeout(CORBA::ULong seconds);
	CosTransactions::Control_ptr get_control();
	CosTransactions::Control_ptr suspend();
	void resume(CosTransactions::Control_ptr which);
		//throw(InvalidControl);

	void open_xa_rm();
		// throw(RMfailed)
	void close_xa_rm();
		// throw(RMfailed)

	// Thread related
#ifdef	IOP_THREAD_SAFE
	void InformThreadExit(IOPTID ThreadId);
#endif	/* IOP_THREAD_SAFE */

};

class Control_Impl : public CosTransactions::Control {
private:
	TPTRANID* cntl;

public:
	Control_Impl();
	Control_Impl(TPTRANID* my_cntl);
	~Control_Impl();
	CosTransactions::Terminator_ptr get_terminator();
		//throw(Unavailable);
	CosTransactions::Coordinator_ptr get_coordinator();
		//throw(Unavailable);
	TPTRANID* get_cntl();
};

#endif
