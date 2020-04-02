/* $Id: e_qs.h,v 1.2 2000/05/24 18:33:37 gtong Exp $
*****************************************************************************
** Copyright (c) 1999, BEA Systems, Inc.
** All Rights Reserved.
*/

#ifndef _E_QS_H
#define _E_QS_H 1

#include "gpsys.h"
#include "e_engine.h"

/* TODO - remove these */

typedef TM32I ET_TRANSACTION;
#define ED_TRANSACTION_NONE     -1
#define ED_TRANSACTION_IMPLICIT -2


/* the QS_API definition must match definition in  qs_tcm.h */

#ifndef QS_API
#ifdef WIN32
#ifdef QS_EXPORTS
#define QS_EXPORT __declspec(dllexport)
#else
#define QS_EXPORT __declspec(dllimport)
#endif
#define QS_API __stdcall
#define QS_IMPORT extern QS_EXPORT
#else
#define QS_EXPORT
#define QS_IMPORT extern
#define QS_API
#endif
#endif

/******************************* qs constants *******************************/

#define ED_QS_CORRELATION_ID_SIZE            32
#define ED_QS_MESSAGE_ID_SIZE                32

#define ED_QS_TIMEOUT_NONE                  -1
#define ED_QS_TIMEOUT_INFINITE              -2

/************************** qs specific error codes *************************/

/*	codes are relative to EE_QS_BASE defined in  e_engine.h */

#define EE_QS_NOTFOUND    (EE_QS_BASE - 1)
#define EE_QS_INVCONTROL  (EE_QS_BASE - 2)
#define EE_QS_INVTRANS    (EE_QS_BASE - 3)
#define EE_QS_INVQUEUE    (EE_QS_BASE - 4)
#define EE_QS_INVCURSOR   (EE_QS_BASE - 5)
#define EE_QS_INVFILTER   (EE_QS_BASE - 6)
#define EE_QS_INVLIST     (EE_QS_BASE - 7)
#define EE_QS_INVPROPERTY (EE_QS_BASE - 8)
#define EE_QS_NOMESSAGE   (EE_QS_BASE - 9)

/********************************** handle types ****************************/

/*	the ET_QS_HANDLE structure is  for  internal  use  only.
	consumers of the queuing services  should  not  use  it */

typedef struct {
	void   * pObject;
	TM32I    nGeneration;
} ET_QS_HANDLE;


/*	all of these are really the same thing,  but we do  the
	typedef thing to provide the illusion  of  type  safety */

typedef ET_QS_HANDLE ET_QS_FILTER;
typedef ET_QS_HANDLE ET_QS_CURSOR;
typedef ET_QS_HANDLE ET_QS_PROPERTY_LIST;
typedef ET_QS_HANDLE ET_QS_QUEUE;


/******************************* cursor control *****************************/

typedef struct {
	TM32U               nFlags;          /* flags to define fields       */
	TM32U               nOperation;      /* the cursor operation         */
	ET_QS_FILTER        hFilter;         /* filter for matching messages */
	ET_QS_PROPERTY_LIST hProperties;     /* handle to the properties     */
	ET_QS_PROPERTY_LIST hDeliveryInfo;   /* handle to the delivery info  */
} ET_QS_CURSOR_CONTROL;

/* flags for  the  nFlags  field  of  the  ET_QS_CURSOR_CONTROL  structure  */

#define EF_QS_CURSOR_OPERATION              (1 <<  0)
#define EF_QS_CURSOR_FILTER                 (1 <<  1)
#define EF_QS_CURSOR_PROPERTIES             (1 <<  2)
#define EF_QS_CURSOR_DELIVERY_INFO          (1 <<  3)

/* flags for the nOperation field  of  the  ET_QS_CURSOR_CONTROL  structure */

#define EF_QS_OPERATION_FIRST               (1 <<  0)
#define EF_QS_OPERATION_FORWARD             (1 <<  1)
#define EF_QS_OPERATION_BACKWARD            (1 <<  2)
#define EF_QS_OPERATION_LAST                (1 <<  3)
#define EF_QS_OPERATION_STICKY              (1 <<  4)
#define EF_QS_OPERATION_LOCK                (1 <<  5)
#define EF_QS_OPERATION_CURRENT             (1 <<  6)




/****************************** close control *******************************/

typedef struct {
	TM32U          nFlags;               /* flags to define fields       */
	TM32I          nPolicy;              /* close policy                 */
	TM32I          nAction;              /* close action                 */
	TM32I          nTimeout;             /* timeout for blocking policy  */
} ET_QS_CLOSE_CONTROL;

/* flags for use in the nFlags field of the ET_QS_CLOSE_CONTROL structure   */

#define EF_QS_CLOSE_POLICY                   (1 << 0)
#define EF_QS_CLOSE_ACTION                   (1 << 1)
#define EF_QS_CLOSE_TIMEOUT                  (1 << 2)

#define ED_QS_CLOSE_POLICY_DEFER             1
#define ED_QS_CLOSE_POLICY_BLOCK             2
#define ED_QS_CLOSE_POLICY_FORCE             3
#define ED_QS_CLOSE_POLICY_FAIL              4

#define ED_QS_CLOSE_ACTION_PURGE             1




/***************************** dequeue control ******************************/

typedef struct {
	TM32U               nFlags;          /* flags to define valid fields */
	TM32I               nTimeout;        /* timeout for the dequeue      */
	ET_QS_FILTER        hFilter;         /* filter for matching messages */
	ET_QS_CURSOR        hCursor;         /* dequeue through this cursor  */
	TM32I               hAsynchronous;   /* handle to use in tpgetreply  */
	ET_QS_PROPERTY_LIST hProperties;     /* handle to user properties    */
	ET_QS_PROPERTY_LIST hDeliveryInfo;   /* handle to delivery info      */
} ET_QS_DEQUEUE_CONTROL;

/* flags for use in the nFlags field of the ET_QS_DEQUEUE_CONTROL structure */

#define EF_QS_DEQUEUE_ASYNCHRONOUS          (1 << 0)
#define EF_QS_DEQUEUE_CURSOR                (1 << 1)
#define EF_QS_DEQUEUE_FILTER                (1 << 2)
#define EF_QS_DEQUEUE_TIMEOUT_ABSOLUTE      (1 << 3)
#define EF_QS_DEQUEUE_TIMEOUT_RELATIVE      (1 << 4)
#define EF_QS_DEQUEUE_DATA                  (1 << 5)
#define EF_QS_DEQUEUE_PROPERTIES            (1 << 6)
#define EF_QS_DEQUEUE_DELIVERY_INFO         (1 << 7)






/***************************** enqueue control ******************************/


typedef struct {
	TM32U               nFlags;          /* flags to define valid fields */
	ET_QS_PROPERTY_LIST hProperties;     /* handle to user properties    */
	ET_QS_PROPERTY_LIST hDeliveryInfo;   /* handle to delivery info      */
} ET_QS_ENQUEUE_CONTROL;

/* flags for use in the nFlags field of the ET_QS_ENQUEUE_CONTROL structure */

#define EF_QS_ENQUEUE_PROPERTIES            0x00000001
#define EF_QS_ENQUEUE_DELIVERY_INFO         0x00000002

#define ED_QS_QOS_PERSISTENT                1
#define ED_QS_QOS_NON_PERSISTENT            2

/******************************* open control *******************************/

typedef struct {
	TM32U              nFlags;           /* flags to define valid fields */
	TM32U              nCreate;          /* bitmask for create options   */
	TM32U              nAccess;          /* bitmask defining access mode */
	TM32U              nSharing;         /* bitmask for sharing options  */
} ET_QS_OPEN_CONTROL;

/* flags for use in the nFlags field of the ET_QS_OPEN_CONTROL structure    */

#define EF_QS_OPEN_CREATE                   0x00000001
#define EF_QS_OPEN_ACCESS                   0x00000002
#define EF_QS_OPEN_SHARING                  0x00000004

/* flags for use in the nCreate field of the ET_QS_OPEN_CONTROL structure   */

#define EF_QS_CREATE_TEMPORARY              0x00000001
#define EF_QS_CREATE_EXCLUSIVE              0x00000002

/* flags for use in the nAccess field of the ET_QS_OPEN_CONTROL structure   */

#define EF_QS_ACCESS_ENQUEUE                0x00000001
#define EF_QS_ACCESS_DEQUEUE                0x00000002
#define EF_QS_ACCESS_PEEK                   0x00000004

/* flags for use in the nSharing field of the ET_QS_OPEN_CONTROL structure  */

#define EF_QS_SHARING_ENQUEUE               0x00000001
#define EF_QS_SHARING_DEQUEUE               0x00000002
#define EF_QS_SHARING_PEEK                  0x00000004





/******************************** property types ****************************/

#define ED_QS_PROPERTY_TYPE_INT8            1
#define ED_QS_PROPERTY_TYPE_INT16           2
#define ED_QS_PROPERTY_TYPE_INT32           3
#define ED_QS_PROPERTY_TYPE_INT64           4
#define ED_QS_PROPERTY_TYPE_FLOAT           5
#define ED_QS_PROPERTY_TYPE_DOUBLE          6
#define ED_QS_PROPERTY_TYPE_STRING          7
#define ED_QS_PROPERTY_TYPE_BLOB            8
#define ED_QS_PROPERTY_TYPE_BOOLEAN         9

#define ED_QS_PROPERTY_LENGTH_DEFAULT       -1





/********************************* prototypes *******************************/

#ifdef _cplusplus
extern "C" {
#endif

/****************************** in e_qs_cursor.c ****************************/

QS_IMPORT TM32I QS_API _e_qs_cursor_control(
	_TCADEF,
	ET_QS_CURSOR              hCursor,
	ET_QS_CURSOR_CONTROL    * pControl,
	char                   ** ppMessage,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_cursor_create(
	_TCADEF,
	ET_QS_QUEUE               hQueue,
	ET_QS_CURSOR            * phCursor,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_cursor_destroy(
	_TCADEF,
	ET_QS_CURSOR              hCursor,
	TM32U                     nFlags
);


/****************************** in e_qs_filter.c ****************************/

QS_IMPORT TM32I QS_API _e_qs_filter_create (
	_TCADEF,
	ET_QS_FILTER            * phFilter,
	const char              * pGrammar,
	const char              * pExpression,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_filter_destroy(
	_TCADEF,
	ET_QS_FILTER              hFilter,
	TM32U                     nFlags
);


/***************************** in e_qs_properties.c *************************/

QS_IMPORT TM32I QS_API _e_qs_property_list_clear(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_create(
	_TCADEF,
	ET_QS_PROPERTY_LIST     * phPropertyList,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_destroy(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_properties_first(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	char                    * pName,
	TM32I                   * pLength,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_get(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	const char              * pName,
	TM32I                   * pType,
	void                    * pValue,
	TM32I                   * pLength,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_next(
	_TCADEF,
	ET_QS_PROPERTY_LIST   hPropertyList,
	char                * pName,
	TM32I               * pLength,
	TM32U                 nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_remove(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	const char              * pName,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_property_list_set(
	_TCADEF,
	ET_QS_PROPERTY_LIST       hPropertyList,
	const char              * pName,
	TM32I                     nType,
	const void              * pValue,
	TM32I                     nLength,
	TM32U                     nFlags
);


/******************************** in e_qs_queue.c ***************************/


QS_IMPORT TM32I QS_API _e_qs_queue_close(
	_TCADEF,
	ET_QS_QUEUE               hQueue,
	ET_QS_CLOSE_CONTROL     * pControl,
	ET_TRANSACTION            hTransaction,
	TM32U                     nFlags
);

QS_IMPORT TM32I QS_API _e_qs_queue_dequeue (
	_TCADEF,
	ET_QS_QUEUE               hQueue,
	ET_QS_DEQUEUE_CONTROL   * pControl,
	char                   ** ppMessage,
	TM32I                   * pLength,
	ET_TRANSACTION            hTransaction,
	TM32U                     nFlags
);


QS_IMPORT TM32I QS_API _e_qs_queue_enqueue (
	_TCADEF,
	ET_QS_QUEUE               hQueue,
	ET_QS_ENQUEUE_CONTROL   * pControl,
	char                    * pMessage,
	TM32I                     nLength,
	ET_TRANSACTION            hTransaction,
	TM32U                     nFlags
);


QS_IMPORT TM32I QS_API _e_qs_queue_open(
	_TCADEF,
	const char              * pName, 
	ET_QS_OPEN_CONTROL      * pControl,
	ET_QS_QUEUE             * phQueue,
	TM32U                     nFlags
);


#ifdef _cplusplus
}
#endif
#endif /* #ifndef _E_QS_H */

