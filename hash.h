#ifndef _SYS_HASH_H_
#define _SYS_HASH_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <pthread.h>
#include "list.h"
typedef dl_node_s	hash_node_s;
typedef dl_head_s	hash_list_s;
#define HASH_ENTRY( ptr, type, member ) (conrainer_of( ptr, type, member ) )
#define HASH_TBL_FOREACH( ptbl, index ) \
	for ( (index) = 0UL; (index) < (ptbl)->size; (index)++ )
#define HASH_GET_INDEX( ptbl, pkey )		( (ptbl)->pfhash( pkey ) )
#define HASH_IS_VALID_INDEX( ptbl, index )	( (index) < (ptbl)->size)
#define HASH_GET_LIST( ptbl, index )	(&(ptbl)->pbckt[index])
#define HASH_IS_HASHED( pnode )		(NULL != (pnode)->ppstpre)
typedef struct tagHASH_TABLE
{
    unsigned long size;
    unsigned long (*pfhash)( const void * );
    hash_list_s *pbckt;
} hash_table_s;
#define HASH_BCKT_FOREACH( plist, pnode ) \
	DL_FOREACH( plist, pnode )
#define HASH_BCKT_FOREACH_SAFE( plist, pnode, next ) \
	DL_FOREACH_SAFE( plist, pnode, next )
#define HASH_SCAN_BCKT( ptbl, index, pnode ) \
	HASH_BCKT_FOREACH( &(ptbl)->pbckt[index], pnode )
#define HASH_SCAN_BCKT_SAFE( ptbl, index, pnode, next ) \
	HASH_BCKT_FOREACH_SAFE( &(ptbl)->pbckt[index], pnode, next )
#define HASH_SCAN_TBL( ptbl, index, pnode ) \
	HASH_TBL_FOREACH( ptbl, index ) \
	HASH_SCAN_BCKT( ptbl, index, pnode )
#define HASH_SCAN_TBL_SAFE( ptbl, index, pnode, next )	\
	HASH_TBL_FOREACH( ptbl, index ) \
	HASH_SCAN_BCKT_SAFE( ptbl, index, pnode, next )


/*************************************************************************
* func name   :  api_hash_init
* author      :  haungzhonglei hash doubly-linked list head
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_init( IN hash_table_s *phashtbl )
{
    unsigned long index = 0;
    HASH_TBL_FOREACH( phashtbl, index )
    {
        api_dl_init( &(phashtbl->pbckt[index]) );
    }
    return;
}


/*************************************************************************
* func name   :  api_hash_list_first
* author      :  Trail
* description :  get the first node of conflict list
* date        :  2015/08/11
* input       :  IN hash_list_s *plist
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
static inline hash_node_s *api_hash_list_first( IN const hash_list_s *plist )
{
    return(api_dl_first( plist ) );
}


/*************************************************************************
* func name   :  api_hash_list_next
* author      :  Trail
* description :  Get the next node
* date        :  2015/08/11
* input       :  IN hash_node_s *pnode
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
static inline hash_node_s *api_hash_list_next( IN const hash_node_s *pnode )
{
    return(api_dl_next( pnode ) );
}


/*************************************************************************
* func name   :  api_hash_list_prev
* author      :  Trail
* description :  get the previous node
* date        :  2015/08/11
* input       :  IN hash_node_s *pnode
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
static inline hash_node_s *api_hash_list_prev( IN const hash_node_s *pnode )
{
    return(api_dl_prev( pnode ) );
}


/*************************************************************************
* func name   :  api_hash_list_add
* author      :  Trail
* description :  add node to head of conflict list
* date        :  2015/08/11
* input       :  IN hash_list_s *plist
*                IN hash_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_list_add( IN hash_list_s *plist, IN hash_node_s *pnode )
{
    api_dl_add_head( plist, pnode );
    return;
}


/*************************************************************************
* func name  :  api_hash_list_add_after
* author      :  Trail
* description :  add node after another one
* date        :  2015/08/11
* input       :  IN hash_list_s *plist
*                IN hash_node_s *prev
*                IN hash_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_list_add_after( IN hash_list_s *plist,
                                      IN hash_node_s *prev,
                                      IN hash_node_s *pinst )
{
    if ( NULL == prev )
    {
        api_dl_add_head( (dl_head_s *) plist, (dl_node_s *) pinst );
    }
    else
    {
        api_dl_add_after( (dl_node_s *) prev, (dl_node_s *) pinst );
    }
    return;
}


/*************************************************************************
* func name   :  api_hash_list_del
* author      :  Trail
* description :  delete node from confilict list
* date        :  2015/08/11
* input       :  IN hash_node_s pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_list_del( IN hash_node_s *pnode )
{
    api_dl_del( pnode );
    return;
}


/*************************************************************************
* func name  :  api_hash_add
* author      :  Trail
* description :  Add node to hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
*                IN hash_node_s *pnode
*                IN void *pkey
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_add( IN hash_table_s *ptbl,
                             IN hash_node_s *pnode,
                             IN void *pkey )
{
    hash_list_s	*plist;
    unsigned long	index;
    index = HASH_GET_INDEX( ptbl, pkey );
    plist = HASH_GET_LIST( ptbl, index );
    api_hash_list_add( plist, pnode );
    return;
}


/*************************************************************************
* func name   :  api_hash_add_order
* author      :  Trail
* description :  add node to hash table by order
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
*                IN hash_node_s *pnode
*                IN long (*pfkeycmp)(IN hash_node_s *, IN void *)
*                IN void *pkey
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_add_order( IN hash_table_s *ptbl,
                                  IN hash_node_s *pnode,
                                  IN long (*pfkeycmp)( IN hash_node_s *, IN void * ),
                                  IN void *pkey )
{
    hash_list_s	*plist;
    hash_node_s	*prenode = (hash_node_s *) NULL;
    hash_node_s	*pscannode;
    unsigned long	index;
    index = HASH_GET_INDEX( ptbl, pkey );
    plist = HASH_GET_LIST( ptbl, index );
    HASH_SCAN_BCKT( ptbl, index, pscannode )
    {
        if ( pfkeycmp( pscannode, pkey ) > 0 )
        {
            break;
        }
        prenode = pscannode;
    }
    api_hash_list_add_after( plist, prenode, pnode );
    return;
}


/*************************************************************************
* func name  :  api_hash_del
* author      :  Trail
* description :  delete node from hash table
* date        :  2015/08/11
* input       :  IN hash_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_del( IN hash_node_s *pnode )
{
    api_hash_list_del( pnode );
    return;
}


/*************************************************************************
* func name   :  api_hash_create
* author      :  Trail
* description :  create hash table
* date        :  2015/08/11
* input       :  IN unsigned long size
*                IN unsigned long (*pfhash)(void *)
* output      :
* return      :  hash_table_s *
* modify      :
*************************************************************************/
#ifdef __KERNEL__
hash_table_s *api_hash_create( IN unsigned long size, IN unsigned long (*pfhash)( void * ), IN unsigned int uiTag );


#else
hash_table_s *api_hash_create( IN unsigned long size, IN unsigned long (*pfhash)( const void * ) );


#endif


/*************************************************************************
* func name   :  api_hash_large_create
* author      :  Trail
* description :  create hash table
* date        :  2015/08/11
* input       :  IN unsigned long size
*                IN unsigned long (*pfhash)(void *)
* output      :
* return      :  hash_table_s *
* modify      :
*************************************************************************/
hash_table_s *api_hash_large_create( IN unsigned long size, IN unsigned long (*pfhash)( void * ) );


/*************************************************************************
* func name   :  HASH_destroy
* author      :  Trail
* description :  destroy hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
*                IN void  (*pfFree)(hash_node_s *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
void api_hash_destory( IN hash_table_s *phashtbl, IN void (*pfFree)( hash_node_s * ) );


/*************************************************************************
* func name   :  api_hash_large_destory
* author      :  Trail
* description :  destroy hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
*                IN void  (*pfFree)(hash_node_s *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
void api_hash_large_destory( IN hash_table_s *phashtbl, IN void (*pfFree)( hash_node_s * ) );


/*************************************************************************
* func name   :  api_hash_find
* author      :  Trail
* description :  find node with key
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
*                IN void *pkey
*                IN long(*pfkeycmp)(IN hash_node_s *,IN void *)
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
hash_node_s *api_hash_find( IN hash_table_s *ptbl,
                        IN void *pkey,
                        IN long (*pfkeycmp)( IN hash_node_s *, IN void * ) );


/* List lock */
typedef struct taghash_rwlock_list_s
{
    hash_list_s		stList;
    pthread_rwlock_t	rwlock;
} hash_rwlock_list_s;
typedef struct tagHASH_RWLOCK_LIST_TABLE
{
    unsigned long size;
    unsigned long (*pfhash)( const void * );
    hash_rwlock_list_s *pbckt;
} hash_rwlock_list_table_s;


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListReadLock
* author      :  Trail
* description :  lock the conflict list with read lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListReadLock( IN hash_rwlock_list_s *plist )
{
    (void) pthread_rwlock_rdlock( &plist->rwlock );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListReadTryLock
* author      :  Trail
* description :  try lock the conflict list with lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :  BOOL_FALSE BOOL_TRUE
* modify      :
*************************************************************************/
static inline BOOL_T apt_hash_rwbkt_ListReadTryLock( IN hash_rwlock_list_s *plist )
{
    return(0 == pthread_rwlock_tryrdlock( &plist->rwlock ) );
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListReadUnLock
* author      :  Trail
* description :  unlock the conflict list
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListReadUnLock( IN hash_rwlock_list_s *plist )
{
    (void) pthread_rwlock_unlock( &plist->rwlock );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListWriteLock
* author      :  Trail
* description :  lock the conflict list with write lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListWriteLock( IN hash_rwlock_list_s *plist )
{
    (void) pthread_rwlock_wrlock( &plist->rwlock );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListWriteTryLock
* author      :  Trail
* description :  try lock the conflict list with lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :  BOOL_FALSE BOOL_TRUE
* modify      :
*************************************************************************/
static inline BOOL_T apt_hash_rwbkt_ListWriteTryLock( IN hash_rwlock_list_s *plist )
{
    return(0 == pthread_rwlock_trywrlock( &plist->rwlock ) );
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListWriteUnLock
* author      :  Trail
* description :  unlock the conflict list
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListWriteUnLock( IN hash_rwlock_list_s *plist )
{
    (void) pthread_rwlock_unlock( &plist->rwlock );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListAdd
* author      :  Trail
* description :  add node to hash table
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
*                IN hash_node_s *pnode
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListAdd( IN hash_rwlock_list_s *plist, IN hash_node_s *pnode )
{
    apt_hash_rwbkt_ListWriteLock( plist );
    api_hash_list_add( &(plist->stList), pnode );
    apt_hash_rwbkt_ListWriteUnLock( plist );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_ListDel
* author      :  Trail
* description :  delte node from conflicnt list
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_s *plist
*                IN hash_node_s *pnode
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_ListDel( IN hash_rwlock_list_s *plist,
                                       IN hash_node_s *pnode )
{
    apt_hash_rwbkt_ListWriteLock( plist );
    api_hash_list_del( pnode );
    apt_hash_rwbkt_ListWriteUnLock( plist );
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_Add
* author      :  Trail
* description :  add node to hash table
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_table_s *ptbl,
*                IN hash_node_s *pnode,
*                IN const void *pkey,
*                IN BOOL_T bLock
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_Add( IN hash_rwlock_list_table_s *ptbl,
                                   IN hash_node_s *pnode,
                                   IN const void *pkey,
                                   IN BOOL_T bLock )
{
    hash_rwlock_list_s	*plist;
    unsigned long		index;
    index = HASH_GET_INDEX( ptbl, pkey );
    plist = HASH_GET_LIST( ptbl, index );
    if ( BOOL_TRUE == bLock )
    {
        apt_hash_rwbkt_ListAdd( plist, pnode );
    }
    else
    {
        api_hash_list_add( &plist->stList, pnode );
    }
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_del
* author      :  Trail
* description :  delete node from hash table
* date        :  2015/08/11
* input       :
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void apt_hash_rwbkt_del( IN hash_rwlock_list_table_s *ptbl,
                                   IN hash_node_s *pnode,
                                   IN const void *pkey,
                                   IN BOOL_T bLock )
{
    hash_rwlock_list_s	*plist;
    unsigned long		index;
    if ( BOOL_TRUE == bLock )
    {
        index = HASH_GET_INDEX( ptbl, pkey );
        plist = HASH_GET_LIST( ptbl, index );
        apt_hash_rwbkt_ListDel( plist, pnode );
    }
    else
    {
        api_hash_list_del( pnode );
    }
    return;
}


/*************************************************************************
* func name   :  apt_hash_rwbkt_create
* author      :  Trail
* description :  create hash table
* date        :  2015/08/11
* input       :  IN unsigned long size
*                IN unsigned long (*pfhash)(void *)
* output      :
* return      :  hash_table_s *
* modify      :
*************************************************************************/
hash_table_s *apt_hash_rwbkt_create( IN unsigned long size, IN unsigned long (*pfhash)( void * ) );


/*************************************************************************
* func name   :  apt_hash_rwbkt_destroy
* author      :  Trail
* description :  destroy hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
*                IN void  (*pfFree)(hash_node_s *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
void apt_hash_rwbkt_destroy( IN hash_table_s *phashtbl, IN void (*pfFree)( hash_node_s * ) );


/*************************************************************************
* func name   :  apt_hash_rwbkt_find
* author      :  Trail
* description :  find node with key
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
*                IN void *pkey
*                IN long(*pfkeycmp)(IN hash_node_s *,IN void *)
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
hash_node_s *apt_hash_rwbkt_find( IN hash_table_s *ptbl,
                              IN void *pkey,
                              IN long (*pfkeycmp)( IN hash_node_s *, IN void * ),
                              IN BOOL_T bLock );


/* table lock */
typedef struct tagHASH_RWLOCK_TABLE
{
    unsigned long size;
    unsigned long (*pfhash)( const void * );
    hash_list_s		*pbckt;
    pthread_rwlock_t	rwlock;
} hash_rwlock_table_s;


/*************************************************************************
* func name   :  api_hash_rwtbl_ReadLock
* author      :  Trail
* description :  lock the conflict list with read lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_ReadLock( IN hash_rwlock_table_s *ptbl )
{
    (void) pthread_rwlock_rdlock( &ptbl->rwlock );
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_ReadTryLock
* author      :  Trail
* description :  try lock the conflict list with lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :  BOOL_FALSE BOOL_TRUE
* modify      :
*************************************************************************/
static inline BOOL_T api_hash_rwtbl_ReadTryLock( IN hash_rwlock_table_s *ptbl )
{
    return(0 == pthread_rwlock_tryrdlock( &ptbl->rwlock ) );
}


/*************************************************************************
* func name   :  api_hash_rwtbl_ReadUnLock
* author      :  Trail
* description :  unlock the conflict list
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_ReadUnLock( IN hash_rwlock_table_s *ptbl )
{
    (void) pthread_rwlock_unlock( &ptbl->rwlock );
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_WriteLock
* author      :  Trail
* description :  lock the conflict list with write lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_WriteLock( IN hash_rwlock_table_s *ptbl )
{
    (void) pthread_rwlock_wrlock( &ptbl->rwlock );
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_WriteTryLock
* author      :  Trail
* description :  try lock the conflict list with lock
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :  BOOL_FALSE BOOL_TRUE
* modify      :
*************************************************************************/
static inline BOOL_T api_hash_rwtbl_WriteTryLock( IN hash_rwlock_table_s *ptbl )
{
    return(0 == pthread_rwlock_trywrlock( &ptbl->rwlock ) );
}


/*************************************************************************
* func name   :  api_hash_rwtbl_ListWriteUnLock
* author      :  Trail
* description :  unlock the conflict list
* date        :  2015/08/11
* input       :  IN hash_rwlock_table_s *ptbl
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_WriteUnLock( IN hash_rwlock_table_s *ptbl )
{
    (void) pthread_rwlock_unlock( &ptbl->rwlock );
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_Add
* author      :  Trail
* description :  add node to hash table
* date        :  2015/08/11
* input       :  IN hash_rwlock_list_table_s *ptbl,
*                IN hash_node_s *pnode,
*                IN const void *pkey,
*                IN BOOL_T bLock
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_Add( IN hash_rwlock_table_s *ptbl,
                                   IN hash_node_s *pnode,
                                   IN const void *pkey,
                                   IN BOOL_T bLock )
{
    hash_list_s	*plist;
    unsigned long	index;
    index = HASH_GET_INDEX( ptbl, pkey );
    plist = HASH_GET_LIST( ptbl, index );
    if ( BOOL_TRUE == bLock )
    {
        api_hash_rwtbl_WriteLock( ptbl );
        api_hash_list_add( plist, pnode );
        api_hash_rwtbl_WriteUnLock( ptbl );
    }
    else
    {
        api_hash_list_add( plist, pnode );
    }
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_del
* author      :  Trail
* description :  delete node from hash table
* date        :  2015/08/11
* input       :
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void api_hash_rwtbl_del( IN hash_rwlock_table_s *ptbl,
                                   IN hash_node_s *pnode,
                                   IN BOOL_T bLock )
{
    if ( BOOL_TRUE == bLock )
    {
        api_hash_rwtbl_WriteLock( ptbl );
        api_hash_list_del( pnode );
        api_hash_rwtbl_WriteUnLock( ptbl );
    }
    else
    {
        api_hash_list_del( pnode );
    }
    return;
}


/*************************************************************************
* func name   :  api_hash_rwtbl_create
* author      :  Trail
* description :  create hash table
* date        :  2015/08/11
* input       :  IN unsigned long size
*                IN unsigned long (*pfhash)(void *)
* output      :
* return      :  hash_table_s *
* modify      :
*************************************************************************/
hash_table_s *api_hash_rwtbl_create( IN unsigned long size, IN unsigned long (*pfhash)( void * ) );


/*************************************************************************
* func name   :  api_hash_rwtbl_destroy
* author      :  Trail
* description :  destroy hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
*                IN void  (*pfFree)(hash_node_s *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
void api_hash_rwtbl_destroy( IN hash_table_s *phashtbl, IN void (*pfFree)( hash_node_s * ) );


/*************************************************************************
* func name   :  api_hash_rwtbl_find
* author      :  Trail
* description :  find node with key
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
*                IN void *pkey
*                IN long(*pfkeycmp)(IN hash_node_s *,IN void *)
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
hash_node_s *api_hash_rwtbl_find( IN hash_table_s *ptbl,
                              IN void *pkey,
                              IN long (*pfkeycmp)( IN hash_node_s *, IN void * ),
                              IN BOOL_T bLock );


static inline int  HASH_ShowCnt( hash_table_s *phashtbl )
{
    unsigned int	uiIndex		= 0;
    hash_node_s	*pstCurrNode	= NULL;
    hash_node_s	*nextnode	= NULL;
    int		cnt		= 0;
    HASH_SCAN_TBL_SAFE( phashtbl, uiIndex, pstCurrNode, nextnode );
    {
        cnt++;
    }
    return(cnt);
}


#ifdef __cplusplus
}
#endif
#endif

