#ifndef _SYS_LIST_H_
#define _SYS_LIST_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>
#include <linux/kernel.h>
#define IN
#define INOUT
#define OUT
#define BOOL_T   int
#define BOOL_TRUE  1
#define BOOL_FALSE 0
#ifndef __KERNEL__
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(type,member) __compiler_offsetof(type,member)
#else
#define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif

#define container_of(ptr, type, member) ({                      \
    const typeof ( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( ( char *)__mptr - offsetof(type,member) );})
#endif
typedef struct tagSL_NODE
{
    struct tagSL_NODE *next;
} sl_node_s;
#define SL_ENTRY(ptr, type, member) (container_of(ptr, type, member))
typedef struct tagSL_HEAD
{
    sl_node_s *pfirst;
} sl_head_s;
static inline void api_sl_init(IN sl_head_s *plist);
static inline void api_sl_node_init(IN sl_node_s *pnode);
static inline BOOL_T api_sl_is_empty(IN const sl_head_s *plist);
static inline sl_node_s *api_sl_first(IN const sl_head_s *plist);
static inline sl_node_s *api_sl_next(IN const sl_node_s *pnode);
static inline void api_sl_add_head(IN sl_head_s *plist, IN sl_node_s *pnode);
static inline sl_node_s *api_sl_del_head(IN sl_head_s *plist);
static inline void api_sl_add_after(IN sl_head_s *plist, IN sl_node_s *prev, IN sl_node_s *pinst);
static inline sl_node_s *api_sl_del_after(IN sl_head_s *plist, IN sl_node_s *prev);
static inline void api_sl_del(IN sl_head_s *plist, IN const sl_node_s *pnode);
static inline void api_sl_append(IN sl_head_s *pdstlist, IN sl_head_s *psrclist);
static inline void api_sl_free_all(IN sl_head_s *plist, IN void (*pfFree)(void *));
/*************************************************************************
* func name   :  api_sl_init
* author      :  haungzhonglei
* description :  initial a singly-linked list head
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_init(IN sl_head_s *plist)
{
    plist->pfirst = (sl_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_sl_node_init
* author      :  Trail
* description :  initial a singly-linked list node
* date        :  2015/08/08
* input       :  IN sl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_node_init(IN sl_node_s *pnode)
{
    pnode->next = (sl_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_sl_is_empty
* author      :  Trail
* description :  Whether the singly-linked list is empty
* date        :  2015/08/08
* input       :  IN const sl_head_s *plist
* output      :
* return      :  BOOL_TRUE 空  BOOL_FALSE  非空
* modify      :
*************************************************************************/
static inline BOOL_T api_sl_is_empty(IN const sl_head_s *plist)
{
    return (NULL == plist->pfirst);
}
/*************************************************************************
* func name   :  api_sl_first
* author      :  Trail
* description :  Get the first element of a singly-linked list
* date        :  2015/08/08
* input       :  IN const sl_head_s *plist
* output      :
* return      :  sl_node_s *     节点指针
* modify      :
*************************************************************************/
static inline sl_node_s *api_sl_first(IN const sl_head_s *plist)
{
    return (plist->pfirst);
}
/*************************************************************************
* func name   :  api_sl_next
* author      :  Trail
* description :  Get the next element of current one
* date        :  2015/08/08
* input       :  IN const sl_node_s *pnode
* output      :
* return      :  sl_node_s *   节点指针
* modify      :
*************************************************************************/
static inline sl_node_s *api_sl_next(IN const sl_node_s *pnode)
{
    return (pnode->next);
}
/*************************************************************************
* func name   :  api_sl_add_head
* author      :  Trail
* description :  Add an element to the head of the list
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
                 IN sl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_add_head(IN sl_head_s *plist, IN sl_node_s *pnode)
{
    pnode->next = plist->pfirst;
    plist->pfirst = pnode;
    return ;
}
/*************************************************************************
* func name   :  api_sl_del_head
* author      :  Trail
* description :  Delete the first element from the list
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
* output      :
* return      :  sl_node_s *
* modify      :
*************************************************************************/
static inline sl_node_s *api_sl_del_head(IN sl_head_s *plist)
{
    sl_node_s *pnode = plist->pfirst;
    if (NULL != pnode)
    {
        plist->pfirst = pnode->next;
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_sl_add_after
* author      :  Trail
* description :  Add an element after another one
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
                 IN sl_node_s *prev
                 IN sl_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_add_after(IN sl_head_s *plist, IN sl_node_s *prev, IN sl_node_s *pinst)
{
    if (NULL == prev)
    {
        api_sl_add_head(plist, pinst);
    }
    else
    {
        pinst->next = prev->next;
        prev->next = pinst;
    }
    return ;
}
/*************************************************************************
* func name   :  api_sl_del_after
* author      :  Trail
* description :  Delete the element after the specified one
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
                 IN sl_node_s *prev
* output      :
* return      :  sl_node_s *
* modify      :
*************************************************************************/
static inline sl_node_s *api_sl_del_after(IN sl_head_s *plist, IN sl_node_s *prev)
{
    sl_node_s *pnode;
    if (NULL == prev)
    {
        pnode = api_sl_del_head(plist);
    }
    else
    {
        pnode = prev->next;
        if (NULL != pnode)
        {
            prev->next = pnode->next;
        }
    }
    return pnode;
}
/************************************宏定义**********************************/
#define SL_FOREACH(plist, pnode) \
    for((pnode) = api_sl_first(plist); \
        NULL != (pnode); \
        (pnode) = api_sl_next(pnode))
#define SL_FOREACH_SAFE(plist, pnode, next) \
    for((pnode) = api_sl_first(plist); \
        (NULL != (pnode)) && ({(next) = api_sl_next(pnode); BOOL_TRUE;}); \
        (pnode) = (next))
#define SL_FOREACH_PREVPTR(plist, pnode, prev) \
    for((pnode) =  api_sl_first(plist), (prev) = (sl_node_s *)NULL; \
        NULL != (pnode); \
        (void)({(prev) = (pnode); (pnode) = api_sl_next(pnode);}))
#define SL_ENTRY_FIRST(plist, type, member) \
    (api_sl_is_empty(plist) ? NULL : SL_ENTRY(api_sl_first(plist), type, member))
#define SL_ENTRY_NEXT(pstEntry, member) \
    (NULL == (pstEntry) ? NULL: \
        (NULL == api_sl_next(&((pstEntry)->member))) ? NULL : \
            SL_ENTRY(api_sl_next(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define SL_FOREACH_ENTRY(plist, pstEntry, member) \
    for((pstEntry) = SL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        NULL != (pstEntry); \
        (pstEntry) = SL_ENTRY_NEXT(pstEntry, member))
#define SL_FOREACH_ENTRY_SAFE(plist, pstEntry, nextEntry, member) \
    for((pstEntry) = SL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        (NULL != (pstEntry)) && \
        ({(nextEntry) = SL_ENTRY_NEXT(pstEntry, member); BOOL_TRUE;}); \
        (pstEntry) = (nextEntry))
#define SL_FOREACH_ENTRY_PREVPTR(plist, pstEntry, prevEntry, member) \
    for((pstEntry) = SL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member), \
        (prevEntry) = NULL ; \
        NULL != (pstEntry); \
        (void)({(prevEntry) = (pstEntry); (pstEntry) = SL_ENTRY_NEXT(prevEntry);}))
/*************************************************************************
* func name   :  api_sl_del
* author      :  Trail
* description :  Delete an element from the list
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
                 IN const sl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_del(IN sl_head_s *plist, IN const sl_node_s *pnode)
{
    sl_node_s *pstCur, *prev;
    SL_FOREACH_PREVPTR(plist, pstCur, prev)
    {
        if (pstCur == pnode)
        {
            (void)api_sl_del_after(plist, prev);
            break;
        }
    }
    return;
}
/*************************************************************************
* func name   :  api_sl_append
* author      :  Trail
* description :  Append psrclist to pdstlist
* date        :  2015/08/08
* input       :  IN sl_head_s *pdstlist
                 IN sl_head_s *psrclist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_append(IN sl_head_s *pdstlist, IN sl_head_s *psrclist)
{
    sl_node_s *pnode, *prev;
    if (BOOL_TRUE != api_sl_is_empty(psrclist))
    {
        SL_FOREACH_PREVPTR(pdstlist, pnode, prev)
        {
            ;/* do nothing */
        }
        if (NULL == prev)
        {
            pdstlist->pfirst = api_sl_first(psrclist);
        }
        else
        {
            prev->next = api_sl_first(psrclist);
        }
        api_sl_init(psrclist);
    }
    return;
}
/*************************************************************************
* func name   :  api_sl_free_all
* author      :  Trail
* description :  Remove an free all nodes from  list
* date        :  2015/08/08
* input       :  IN sl_head_s *plist
                 IN void(*pfFree)(void *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_sl_free_all(IN sl_head_s *plist, IN void(*pfFree)(void *))
{
    sl_node_s *currnode;
    sl_node_s *nextnode;
    SL_FOREACH_SAFE(plist, currnode, nextnode)
    {
        pfFree(currnode);
    }
    api_sl_init(plist);
    return;
}
typedef struct tagSTQ_NODE
{
    struct tagSTQ_NODE *next;
} stq_node_s;
#define STQ_ENTRY(ptr, type, member)  (container_of(ptr, type, member))
typedef struct tagSTQ_HEAD
{
    stq_node_s *pfirst;
    stq_node_s *plast;
} stq_head_s;
static inline void api_stq_init(IN stq_head_s *plist);
static inline void api_stq_node_init(IN stq_node_s *pnode);
static inline BOOL_T api_stq_is_empty(IN const stq_head_s *plist);
static inline stq_node_s *api_stq_first(IN const stq_head_s *plist);
static inline stq_node_s *api_stq_last(IN const stq_head_s *plist);
static inline stq_node_s *api_stq_next(IN const stq_node_s *pnode);
static inline void api_stq_add_head(IN stq_head_s *plist, IN stq_node_s *pnode);
static inline stq_node_s *api_stq_del_head(IN stq_head_s *plist);
static inline void api_stq_add_tail(IN stq_head_s *plist, IN stq_node_s *pnode);
static inline void api_stq_add_after(IN stq_head_s *plist, IN stq_node_s *prev, IN stq_node_s *pinst);
static inline stq_node_s *api_stq_del_after(IN stq_head_s *plist, IN stq_node_s *prev);
static inline void api_stq_del(IN stq_head_s *plist, IN const stq_node_s *pnode);
static inline void api_stq_append(IN stq_head_s *pdstlist, IN stq_head_s *psrclist);
static inline void api_stq_free_all(IN stq_head_s *plist, IN void (*pfFree)(void *));
/*************************************************************************
* func name   :  api_stq_init
* author      :  haungzhonglei
* description :  initial a singly-linked tail queue head
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_init(IN stq_head_s *plist)
{
    plist->pfirst = (stq_node_s *)NULL;
    plist->plast  = (stq_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_stq_node_init
* author      :  Trail
* description :  initial a singly-linked tail queue  node
* date        :  2015/08/11
* input       :  IN stq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_node_init(IN stq_node_s *pnode)
{
    pnode->next = (stq_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_stq_is_empty
* author      :  Trail
* description :  Whether the singly-linked tail queue is empty
* date        :  2015/08/11
* input       :  IN const stq_head_s *plist
* output      :
* return      :  BOOL_TRUE 空  BOOL_FALSE  非空
* modify      :
*************************************************************************/
static inline BOOL_T api_stq_is_empty(IN const stq_head_s *plist)
{
    return (NULL == plist->pfirst);
}
/*************************************************************************
* func name   :  api_stq_first
* author      :  Trail
* description :  Get the first element of a singly-linked tail queue
* date        :  2015/08/11
* input       :  IN const stq_head_s *plist
* output      :
* return      :  sl_node_s *     节点指针
* modify      :
*************************************************************************/
static inline stq_node_s *api_stq_first(IN const stq_head_s *plist)
{
    return (plist->pfirst);
}
/*************************************************************************
* func name   :  api_stq_last
* author      :  Trail
* description :  Get the last element of a singly-linked tail queue
* date        :  2015/08/11
* input       :  IN const stq_node_s *pnode
* output      :
* return      :  sl_node_s *   节点指针
* modify      :
*************************************************************************/
static inline stq_node_s *api_stq_last(IN const stq_head_s *plist)
{
    return (plist->plast);
}
/*************************************************************************
* func name   :  api_stq_next
* author      :  Trail
* description :  Get the next element of current one
* date        :  2015/08/11
* input       :  IN const stq_node_s *pnode
* output      :
* return      :  sl_node_s *   节点指针
* modify      :
*************************************************************************/
static inline stq_node_s *api_stq_next(IN const stq_node_s *pnode)
{
    return (pnode->next);
}
/*************************************************************************
* func name   :  api_stq_add_head
* author      :  Trail
* description :  Add an element to the head of the queue
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN stq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_add_head(IN stq_head_s *plist, IN stq_node_s *pnode)
{
    pnode->next = plist->pfirst;
    plist->pfirst = pnode;
    if (NULL == plist->plast)
    {
        plist->plast = pnode;
    }
    return ;
}
/*************************************************************************
* func name   :  api_stq_del_head
* author      :  Trail
* description :  Delete the first element from the queue
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
* output      :
* return      :  stq_node_s *
* modify      :
*************************************************************************/
static inline stq_node_s *api_stq_del_head(IN stq_head_s *plist)
{
    stq_node_s *pnode = plist->pfirst;
    if (NULL != pnode)
    {
        plist->pfirst = pnode->next;
    }
    if (NULL == plist->pfirst)
    {
        plist->plast = (stq_node_s *)NULL;
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_stq_add_tail
* author      :  Trail
* description :  Add an element to the tail of the queue
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN stq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_add_tail(IN stq_head_s *plist, IN stq_node_s *pnode)
{
    pnode->next = (stq_node_s *)NULL;
    if (NULL != plist->plast)
    {
        plist->plast->next = pnode;
        plist->plast = pnode;
    }
    else
    {
        plist->plast  = pnode;
        plist->pfirst = pnode;
    }
    return ;
}
/*************************************************************************
* func name   :  api_stq_add_after
* author      :  Trail
* description :  Add an element after another one
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN stq_node_s *prev
                 IN stq_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_add_after(IN stq_head_s *plist, IN stq_node_s *prev, IN stq_node_s *pinst)
{
    if (NULL == prev)
    {
        api_stq_add_head(plist, pinst);
    }
    else
    {
        pinst->next = prev->next;
        prev->next = pinst;
        if (plist->plast == prev)
        {
            plist->plast = pinst;
        }
    }
    return ;
}
/*************************************************************************
* func name   :  api_stq_del_after
* author      :  Trail
* description :  Delete the element after the specified one
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN stq_node_s *prev
* output      :
* return      :  sl_node_s *
* modify      :
*************************************************************************/
static inline stq_node_s *api_stq_del_after(IN stq_head_s *plist, IN stq_node_s *prev)
{
    stq_node_s *pnode;
    if (NULL == prev)
    {
        pnode = api_stq_del_head(plist);
    }
    else
    {
        pnode = prev->next;
        if (NULL != pnode)
        {
            prev->next = pnode->next;
        }
        if (plist->plast == pnode)
        {
            plist->plast = prev;
        }
    }
    return pnode;
}
/************************************宏定义**********************************/
#define STQ_FOREACH(plist, pnode) \
    for((pnode) = api_stq_first(plist); \
        NULL != (pnode); \
        (pnode) = api_stq_next(pnode))
#define STQ_FOREACH_SAFE(plist, pnode, next) \
    for((pnode) = api_stq_first(plist); \
        (NULL != (pnode)) && ({(next) = api_stq_next(pnode); BOOL_TRUE;}); \
        (pnode) = (next))
#define STQ_FOREACH_PREVPTR(plist, pnode, prev) \
    for((pnode) =  api_stq_first(plist), (prev) = (stq_node_s *)NULL; \
        NULL != (pnode); \
        (void)({(prev) = (pnode); (pnode) = api_stq_next(pnode);}))
#define STQ_ENTRY_FIRST(plist, type, member) \
    (api_stq_is_empty(plist) ? NULL : STQ_ENTRY(api_stq_first(plist), type, member))
#define STQ_ENTRY_LAST(plist, type, member) \
    (api_stq_is_empty(plist) ? NULL : STQ_ENTRY(api_stq_last(plist), type, member))
#define STQ_ENTRY_NEXT(pstEntry, member) \
    (NULL == (pstEntry) ? NULL: \
        (NULL == api_stq_next(&((pstEntry)->member))) ? NULL : \
            STQ_ENTRY(api_stq_next(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define STQ_FOREACH_ENTRY(plist, pstEntry, member) \
    for((pstEntry) = STQ_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        NULL != (pstEntry); \
        (pstEntry) = STQ_ENTRY_NEXT(pstEntry, member))
#define STQ_FOREACH_ENTRY_SAFE(plist, pstEntry, nextEntry, member) \
    for((pstEntry) = STQ_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        (NULL != (pstEntry)) && \
        ({(nextEntry) = STQ_ENTRY_NEXT(pstEntry, member); BOOL_TRUE;}); \
        (pstEntry) = (nextEntry))
#define STQ_FOREACH_ENTRY_PREVPTR(plist, pstEntry, prevEntry, member) \
    for((pstEntry) = STQ_ENTRY_FIRST(plist, typeof(*(pstEntry)), member), \
        (prevEntry) = NULL ; \
        NULL != (pstEntry); \
        (void)({(prevEntry) = (pstEntry); (pstEntry) = STQ_ENTRY_NEXT(prevEntry);}))
/*************************************************************************
* func name   :  api_stq_del
* author      :  Trail
* description :  Delete an element from the rail queue
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN const stq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_del(IN stq_head_s *plist, IN const stq_node_s *pnode)
{
    stq_node_s *pstCur, *prev;
    STQ_FOREACH_PREVPTR(plist, pstCur, prev)
    {
        if (pstCur == pnode)
        {
            (void)api_stq_del_after(plist, prev);
            break;
        }
    }
    return;
}
/*************************************************************************
* func name   :  api_stq_append
* author      :  Trail
* description :  Append psrclist to pdstlist
* date        :  2015/08/11
* input       :  IN stq_head_s *pdstlist
                 IN stq_head_s *psrclist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_append(IN stq_head_s *pdstlist, IN stq_head_s *psrclist)
{
    if (BOOL_TRUE != api_stq_is_empty(psrclist))
    {
        if (NULL != pdstlist->plast)
        {
            pdstlist->plast->next = api_stq_first(psrclist);
        }
        else
        {
            pdstlist->pfirst = api_stq_first(psrclist);
        }
        pdstlist->plast = api_stq_last(psrclist);
        api_stq_init(psrclist);
    }
    return;
}
/*************************************************************************
* func name   :  api_stq_free_all
* author      :  Trail
* description :  Remove an free all nodes from STQ list
* date        :  2015/08/11
* input       :  IN stq_head_s *plist
                 IN void(*pfFree)(void *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_stq_free_all(IN stq_head_s *plist, IN void(*pfFree)(void *))
{
    stq_node_s *currnode;
    stq_node_s *nextnode;
    STQ_FOREACH_SAFE(plist, currnode, nextnode)
    {
        pfFree(currnode);
    }
    api_stq_init(plist);
    return;
}
typedef struct tagDL_NODE
{
    struct tagDL_NODE *next;
    struct tagDL_NODE **ppstpre; /* the address of previous element's next */
} dl_node_s;
#define DL_ENTRY(ptr,type, member) (container_of(ptr, type, member))
#define DL_NODE_FROM_PPRE(ppstpre) (container_of(ppstpre, dl_node_s, next))
#define DL_ENTRY_FROM_PPRE(ppstpre, type, member) \
        DL_ENTRY(DL_NODE_FROM_PPRE(ppstpre), type, member)
typedef struct tagDL_HEAD
{
    dl_node_s *pfirst;
} dl_head_s;
static inline void api_dl_init(IN dl_head_s *plist);
static inline void api_dl_node_init(IN dl_node_s *pnode);
static inline BOOL_T api_dl_is_empty(IN const dl_head_s *plist);
static inline dl_node_s *api_dl_first(IN const dl_head_s *plist);
static inline dl_node_s *api_dl_next(IN const dl_node_s *pnode);
static inline dl_node_s *api_dl_prev(IN const dl_node_s *pnode);
static inline void api_dl_del(IN const dl_node_s *pnode);
static inline void api_dl_add_head(IN dl_head_s *plist, IN dl_node_s *pnode);
static inline dl_node_s *api_dl_del_head(IN dl_head_s *plist);
static inline void api_dl_add_after(IN dl_node_s *prev, IN dl_node_s *pinst);
static inline void api_dl_add_after_ptr(IN dl_node_s **ppstpre, IN dl_node_s *pinst);
static inline void api_dl_add_before(IN dl_node_s *prev, IN dl_node_s *pinst);
static inline void api_dl_append(IN dl_head_s *pdstlist, IN dl_head_s *psrclist);
static inline void api_dl_free_all(IN dl_head_s *plist, IN void (*pfFree)(void *));
/*************************************************************************
* func name   :  api_dl_init
* author      :  haungzhonglei
* description :  initial a doubly-linked list head
* date        :  2015/08/08
* input       :  IN dl_head_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_init(IN dl_head_s *plist)
{
    plist->pfirst = (dl_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_dl_node_init
* author      :  Trail
* description :  initial a doubly-linked list node
* date        :  2015/08/11
* input       :  IN sl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_node_init(IN dl_node_s *pnode)
{
    pnode->next = (dl_node_s *)NULL;
    pnode->ppstpre = (dl_node_s **)NULL;
    return;
}
/*************************************************************************
* func name   :  api_dl_is_empty
* author      :  Trail
* description :  Whether the doubly-linked list is empty
* date        :  2015/08/11
* input       :  IN const sl_head_s *plist
* output      :
* return      :  BOOL_TRUE 空  BOOL_FALSE  非空
* modify      :
*************************************************************************/
static inline BOOL_T api_dl_is_empty(IN const dl_head_s *plist)
{
    return (NULL == plist->pfirst);
}
/*************************************************************************
* func name   :  api_dl_first
* author      :  Trail
* description :  Get the first element of a doubly-linked list
* date        :  2015/08/11
* input       :  IN const dl_head_s *plist
* output      :
* return      :  dl_node_s *     节点指针
* modify      :
*************************************************************************/
static inline dl_node_s *api_dl_first(IN const dl_head_s *plist)
{
    return (plist->pfirst);
}
/*************************************************************************
* func name   :  api_dl_next
* author      :  Trail
* description :  Get the next element of current one
* date        :  2015/08/11
* input       :  IN const dl_node_s *pnode
* output      :
* return      :  sl_node_s *
* modify      :
*************************************************************************/
static inline dl_node_s *api_dl_next(IN const dl_node_s *pnode)
{
    return (pnode->next);
}
/*************************************************************************
* func name   :  api_dl_prev
* author      :  Trail
* description :  Get the previous element of current one
* date        :  2015/08/11
* input       :  IN const dl_node_s *pnode
* output      :
* return      :  sl_node_s *
* modify      :
*************************************************************************/
static inline dl_node_s *api_dl_prev(IN const dl_node_s *pnode)
{
    return DL_NODE_FROM_PPRE(pnode->ppstpre);
}
/*************************************************************************
* func name   :  api_dl_del
* author      :  Trail
* description :  Delete an element from the list
* date        :  2015/08/11
* input       :  IN const dl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_del(IN const dl_node_s *pnode)
{
    if (NULL != pnode->ppstpre)
    {
        *pnode->ppstpre = pnode->next;
    }
    if (NULL != pnode->next)
    {
        pnode->next->ppstpre = pnode->ppstpre;
    }
    return;
}
/*************************************************************************
* func name   :  api_dl_add_head
* author      :  Trail
* description :  Add an element to the head of the list
* date        :  2015/08/11
* input       :  IN dl_head_s *plist
                 IN dl_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_add_head(IN dl_head_s *plist, IN dl_node_s *pnode)
{
    pnode->ppstpre = &plist->pfirst;
    pnode->next = plist->pfirst;
    if (NULL != pnode->next)
    {
        pnode->next->ppstpre = &pnode->next;
    }
    plist->pfirst = pnode;
    return ;
}
/*************************************************************************
* func name   :  api_dl_del_head
* author      :  Trail
* description :  Delete the first element from the list
* date        :  2015/08/08
* input       :  IN dl_head_s *plist
* output      :
* return      :  dl_node_s *
* modify      :
*************************************************************************/
static inline dl_node_s *api_dl_del_head(IN dl_head_s *plist)
{
    dl_node_s *pnode = api_dl_first(plist);
    {
        api_dl_del(pnode);
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_dl_add_after
* author      :  Trail
* description :  Add an element after another one
* date        :  2015/08/11
* input       :  IN dl_node_s *prev
                 IN dl_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_add_after(IN dl_node_s *prev, IN dl_node_s *pinst)
{
    pinst->ppstpre = &prev->next;
    pinst->next = prev->next;
    prev->next = pinst;
    if (NULL != pinst->next)
    {
        pinst->next->ppstpre = &pinst->next;
    }
    return ;
}
/*************************************************************************
* func name   :  api_dl_add_after_ptr
* author      :  Trail
* description :  Add an element after another one
* date        :  2015/08/11
* input       :  IN dl_node_s **ppstpre
                 IN dl_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_add_after_ptr(IN dl_node_s **ppstpre, IN dl_node_s *pinst)
{
    pinst->ppstpre = ppstpre;
    pinst->next = *ppstpre;
    *ppstpre = pinst;
    if (NULL != pinst->next)
    {
        pinst->next->ppstpre = &pinst->next;
    }
    return ;
}
/*************************************************************************
* func name   :  api_dl_add_before
* author      :  Trail
* description :  Add an element before another one
* date        :  2015/08/11
* input       :  IN dl_node_s *next
                 IN dl_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_add_before(IN dl_node_s *next, IN dl_node_s *pinst)
{
    pinst->ppstpre = next->ppstpre;
    pinst->next = next;
    if (NULL != pinst->ppstpre)
    {
        *pinst->ppstpre = pinst;
    }
    pinst->next->ppstpre = &pinst->next;
    return ;
}
/************************************宏定义**********************************/
#define DL_FOREACH(plist, pnode) \
    for((pnode) = api_dl_first(plist); \
        NULL != (pnode); \
        (pnode) = api_dl_next(pnode))
#define DL_FOREACH_SAFE(plist, pnode, next) \
    for((pnode) = api_dl_first(plist); \
        (NULL != (pnode)) && ({(next) = api_dl_next(pnode); BOOL_TRUE;}); \
        (pnode) = (next))
#define DL_FOREACH_PREVPTR(plist, pnode, ppstpre) \
    for((pnode) =  api_dl_first(plist), (ppstpre) = &((plist)->pfirst); \
        NULL != (pnode); \
        (void)({(ppstpre) = &((pnode)->next); (pnode) = api_dl_next(pnode);}))
#define DL_ENTRY_FIRST(plist, type, member) \
    (api_dl_is_empty(plist) ? NULL : DL_ENTRY(api_dl_first(plist), type, member))
#define DL_ENTRY_NEXT(pstEntry, member) \
    (NULL == (pstEntry) ? NULL: \
        (NULL == api_dl_next(&((pstEntry)->member))) ? NULL : \
            DL_ENTRY(api_dl_next(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define DL_ENTRY_PREV(pstEntry, member) \
    (NULL == (pstEntry) ? NULL: \
        (NULL == api_dl_prev(&((pstEntry)->member))) ? NULL : \
            DL_ENTRY(api_dl_prev(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define DL_FOREACH_ENTRY(plist, pstEntry, member) \
    for((pstEntry) = DL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        NULL != (pstEntry); \
        (pstEntry) = DL_ENTRY_NEXT(pstEntry, member))
#define DL_FOREACH_ENTRY_SAFE(plist, pstEntry, nextEntry, member) \
    for((pstEntry) = DL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member); \
        (NULL != (pstEntry)) && \
        ({(nextEntry) = DL_ENTRY_NEXT(pstEntry, member); BOOL_TRUE;}); \
        (pstEntry) = (nextEntry))
#define DL_FOREACH_ENTRY_PREVPTR(plist, pstEntry, ppstpre, member) \
    for((pstEntry) = DL_ENTRY_FIRST(plist, typeof(*(pstEntry)), member), \
        (ppstpre) = &((plist)->pfirst); \
        NULL != (pstEntry); \
        (void)({(ppstpre) = &((pstEntry)->member.next); (pstEntry) = DL_ENTRY_NEXT(pstEntry, member);}))
/*************************************************************************
* func name   :  api_dl_append
* author      :  Trail
* description :  Append psrclist to pdstlist
* date        :  2015/08/11
* input       :  IN dl_head_s *pdstlist
                 IN dl_head_s *psrclist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_append(IN dl_head_s *pdstlist, IN dl_head_s *psrclist)
{
    dl_node_s *pnode, **ppstpre;
    if (BOOL_TRUE != api_dl_is_empty(psrclist))
    {
        DL_FOREACH_PREVPTR(pdstlist, pnode, ppstpre)
        {
            ;/* do nothing */
        }
        *ppstpre = psrclist->pfirst;
        psrclist->pfirst->ppstpre = ppstpre;
        api_dl_init(psrclist);
    }
    return;
}
/*************************************************************************
* func name   :  api_dl_free_all
* author      :  Trail
* description :  Remove an free all nodes from DL list
* date        :  2015/08/11
* input       :  IN dl_head_s *plist
                 IN void(*pfFree)(void *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dl_free_all(IN dl_head_s *plist, IN void(*pfFree)(void *))
{
    dl_node_s *currnode;
    dl_node_s *nextnode;
    DL_FOREACH_SAFE(plist, currnode, nextnode)
    {
        pfFree(currnode);
    }
    api_dl_init(plist);
    return;
}
typedef struct tagDTQ_NODE
{
    struct tagDTQ_NODE *prev;
    struct tagDTQ_NODE *next;
} dtq_node_s;
#define DTQ_ENTRY(ptr, type, member) (container_of(ptr, type, member))
typedef struct tagDTQ_HEAD
{
    dtq_node_s stHead;
} dtq_head_s;
static inline void api_dtq_init(IN dtq_head_s *plist);
static inline void api_dtq_node_init(IN dtq_node_s *pnode);
static inline BOOL_T api_dtq_is_empty(IN const dtq_head_s *plist);
static inline dtq_node_s *api_dtq_first(IN const dtq_head_s *plist);
static inline dtq_node_s *api_dtq_last(IN const dtq_head_s *plist);
static inline BOOL_T api_dtq_is_end_ofq(IN const dtq_head_s *plist, IN const dtq_node_s *pnode);
static inline dtq_node_s *api_dtq_prev(IN const dtq_node_s *pnode);
static inline dtq_node_s *api_dtq_next(IN const dtq_node_s *pnode);
static inline void api_dtq_add_after(IN dtq_node_s *prev, IN dtq_node_s *pinst);
static inline void api_dtq_add_before(IN dtq_node_s *next, IN dtq_node_s *pinst);
static inline void api_dtq_del(IN dtq_node_s *pnode);
static inline void api_dtq_add_head(IN dtq_head_s *plist, IN dtq_node_s *pnode);
static inline dtq_node_s *api_dtq_del_head(IN dtq_head_s *plist);
static inline void api_dtq_add_tail(IN dtq_head_s *plist, IN dtq_node_s *pnode);
static inline dtq_node_s *api_dtq_del_tail(IN dtq_head_s *plist);
static inline void api_dtq_append(IN dtq_head_s *pdstlist, IN dtq_head_s *psrclist);
static inline void api_dtq_free_all(IN dtq_head_s *plist, IN void (*pfFree)(void *));
/*************************************************************************
* func name   :  api_dtq_init
* author      :  haungzhonglei
* description :  initial a doubly-linked tail queue head
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_init(IN dtq_head_s *plist)
{
    plist->stHead.next = &plist->stHead;
    plist->stHead.prev = &plist->stHead;
    return;
}
/*************************************************************************
* func name   :  api_dtq_node_init
* author      :  Trail
* description :  initial a doubly-linked tail queue  node
* date        :  2015/08/11
* input       :  IN dtq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_node_init(IN dtq_node_s *pnode)
{
    pnode->next = (dtq_node_s *)NULL;
    pnode->prev = (dtq_node_s *)NULL;
    return;
}
/*************************************************************************
* func name   :  api_dtq_is_empty
* author      :  Trail
* description :  Whether the doubly-linked tail queue is empty
* date        :  2015/08/11
* input       :  IN const dtq_head_s *plist
* output      :
* return      :  BOOL_TRUE 空  BOOL_FALSE  非空
* modify      :
*************************************************************************/
static inline BOOL_T api_dtq_is_empty(IN const dtq_head_s *plist)
{
    return (plist->stHead.next == &plist->stHead);
}
/*************************************************************************
* func name   :  api_dtq_first
* author      :  Trail
* description :  Get the first element of a doubly-linked tail queue
* date        :  2015/08/11
* input       :  IN const dtq_head_s *plist
* output      :
* return      :  sl_node_s *     节点指针
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_first(IN const dtq_head_s *plist)
{
    dtq_node_s *pnode = plist->stHead.next;
    if (pnode == &(plist->stHead))
    {
        return NULL;
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_dtq_last
* author      :  Trail
* description :  Get the last element of a doubly-linked tail queue
* date        :  2015/08/11
* input       :  IN const dtq_node_s *pnode
* output      :
* return      :  dtq_node_s *   节点指针
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_last(IN const dtq_head_s *plist)
{
    dtq_node_s *pnode = plist->stHead.prev;
    if (pnode == &plist->stHead)
    {
        return NULL;
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_dtq_is_end_ofq
* author      :  Trail
* description :  Wether the node is the end of the queue
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
                 IN dtq_node_s *pnode
* output      :
* return      :  BOOL_TRUE   BOOL_FALSE
* modify      :
*************************************************************************/
static inline BOOL_T api_dtq_is_end_ofq(IN const dtq_head_s *plist, IN const dtq_node_s *pnode)
{
    if (api_dtq_is_empty(plist))
    {
        return BOOL_TRUE;
    }
    if (NULL == pnode)
    {
        return BOOL_TRUE;
    }
    return (pnode == &plist->stHead);
}
/*************************************************************************
* func name   :  api_dtq_prev
* author      :  Trail
* description :  Get the previous element of current one
* date        :  2015/08/11
* input       :  IN const dtq_node_s *pnode
* output      :
* return      :  dtq_node_s *
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_prev(IN const dtq_node_s *pnode)
{
    return (pnode->prev);
}
/*************************************************************************
* func name   :  api_dtq_next
* author      :  Trail
* description :  Get the next element of current one
* date        :  2015/08/11
* input       :  IN const dtq_node_s *pnode
* output      :
* return      :  dtq_node_s *
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_next(IN const dtq_node_s *pnode)
{
    return (pnode->next);
}
/*************************************************************************
* func name   :  api_dtq_add_after
* author      :  Trail
* description :  Add an element after another one
* date        :  2015/08/11
* input       :  IN dtq_node_s *prev
                 IN dtq_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_add_after(IN dtq_node_s *prev, IN dtq_node_s *pinst)
{
    pinst->prev = prev;
    pinst->next = prev->next;
    prev->next = pinst;
    pinst->next->prev = pinst;
    return;
}
/*************************************************************************
* func name   :  api_dtq_add_before
* author      :  Trail
* description :  Add an element before another one
* date        :  2015/08/11
* input       :  IN dtq_node_s *next
                 IN dtq_node_s *pinst
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_add_before(IN dtq_node_s *next, IN dtq_node_s *pinst)
{
    pinst->prev = next->prev;
    pinst->next = next;
    pinst->prev->next = pinst;
    pinst->next->prev = pinst;
    return;
}
/*************************************************************************
* func name   :  api_dtq_del
* author      :  Trail
* description :  Delete an element from the tail queue
* date        :  2015/08/11
* input       :  IN dtq_node_s *pnode
* output      :
* return      :
* modify      :
*************************************************************************/
static inline void api_dtq_del(IN dtq_node_s *pnode)
{
    pnode->prev->next = pnode->next;
    pnode->next->prev = pnode->prev;
    return;
}
/*************************************************************************
* func name   :  api_dtq_add_head
* author      :  Trail
* description :  Add an element to the head of the queue
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
                 IN dtq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_add_head(IN dtq_head_s *plist, IN dtq_node_s *pnode)
{
    api_dtq_add_after(&plist->stHead, pnode);
    return;
}
/*************************************************************************
* func name   :  api_dtq_del_head
* author      :  Trail
* description :  Delete the first element from the queue
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
* output      :
* return      :  dtq_node_s *
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_del_head(IN dtq_head_s *plist)
{
    dtq_node_s *pnode = api_dtq_first(plist);
    if (api_dtq_is_end_ofq(plist, pnode))
    {
        pnode = (dtq_node_s *)NULL;
    }
    else
    {
        api_dtq_del(pnode);
    }
    return pnode;
}
/*************************************************************************
* func name   :  api_dtq_add_tail
* author      :  Trail
* description :  Add an element to th tail of the queue
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
                 IN dtq_node_s *pnode
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_add_tail(IN dtq_head_s *plist, IN dtq_node_s *pnode)
{
    api_dtq_add_before(&plist->stHead, pnode);
    return;
}
/*************************************************************************
* func name   :  api_dtq_del_tail
* author      :  Trail
* description :  Delete the last element from the queue
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
* output      :
* return      :  dtq_node_s *
* modify      :
*************************************************************************/
static inline dtq_node_s *api_dtq_del_tail(IN dtq_head_s *plist)
{
    dtq_node_s *pnode = api_dtq_last(plist);
    if (api_dtq_is_end_ofq(plist, pnode))
    {
        pnode = (dtq_node_s *)NULL;
    }
    else
    {
        api_dtq_del(pnode);
    }
    return pnode;
}
/************************************宏定义**********************************/
#define DTQ_FOREACH(plist, pnode) \
    for((pnode) = api_dtq_first(plist); \
        (pnode) != &((plist)->stHead); \
        (pnode) = api_dtq_next(pnode))
#define DTQ_FOREACH_SAFE(plist, pnode, nextnode) \
    for((pnode) = (plist)->stHead.next; \
        (pnode) != &((plist)->stHead) && \
        ({(nextnode) = api_dtq_next(pnode); BOOL_TRUE;}); \
        (pnode) = (nextnode))
#define DTQ_FOREACH_REVERSE(plist, pnode) \
    for((pnode) =  api_dtq_last(plist); \
        (BOOL_TRUE) != api_dtq_is_end_ofq(plist, pnode); \
        (pnode) = api_dtq_prev(pnode)
#define DTQ_FOREACH_REVERSE_SAFE(plist, pnode, prev) \
    for((pnode) = api_dtq_last(plist); \
        (BOOL_TRUE != api_dtq_is_end_ofq(plist, pnode)) && \
        ({(prev) = api_dtq_prev(pnode); BOOL_TRUE;}); \
        (pnode) = (prev))
#define DTQ_ENTRY_FIRST(plist, type, member) \
    ({dtq_node_s *pnode__Tmp__Mx = api_dtq_first(plist); \
    (NULL == pnode__Tmp__Mx) ? NULL : DTQ_ENTRY(pnode__Tmp__Mx, type, member);})
#define DTQ_ENTRY_LAST(plist, type, member) \
    ({dtq_node_s *pnode__Tmp__Mx = api_dtq_last(plist); \
    (NULL == pnode__Tmp__Mx) ? NULL : DTQ_ENTRY(pnode__Tmp__Mx, type, member);})
#define DTQ_ENTRY_NEXT(plist, pstEntry, member) \
    (api_dtq_is_end_ofq(plist, (NULL == (pstEntry) ? NULL : api_dtq_next(&((pstEntry)->member)))) ? \
    NULL : \
    DTQ_ENTRY(api_dtq_next(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define DTQ_ENTRY_PREV(plist, pstEntry, member) \
    (api_dtq_is_end_ofq(plist, (NULL == (pstEntry) ? NULL : api_dtq_prev(&((pstEntry)->member)))) ? \
    NULL : \
    DTQ_ENTRY(api_dtq_prev(&((pstEntry)->member)), typeof(*(pstEntry)), member))
#define DTQ_FOREACH_ENTRY(plist, pstEntry, member) \
    for((pstEntry) = DTQ_ENTRY((plist)->stHead.next, typeof(*(pstEntry)), member); \
        ((&(pstEntry)->member != &(plist)->stHead) || ({pstEntry = NULL; BOOL_FALSE;})); \
        (pstEntry) = DTQ_ENTRY((pstEntry)->member.next, typeof(*(pstEntry)), member))
#define DTQ_FOREACH_ENTRY_SAFE(plist, pstEntry, nextEntry, member) \
    for((pstEntry) = DTQ_ENTRY((plist)->stHead.next, typeof(*(pstEntry)), member); \
        (((&(pstEntry)->member != &(plist)->stHead) && \
        ({(nextEntry) = DTQ_ENTRY((pstEntry)->member.next, typeof(*(pstEntry)), member); BOOL_TRUE;})) || \
        ({(pstEntry) = NULL; BOOL_FALSE;})); \
        (pstEntry) = (nextEntry))
#define DTQ_FOREACH_ENTRY_REVERSE(plist, pstEntry, member) \
    for ((pstEntry) = DTQ_ENTRY_LAST(plist, typeof(*(pstEntry)), member); \
        NULL != (pstEntry); \
        (pstEntry) = DTQ_ENTRY_PREV(plist, pstEntry, member))
#define DTQ_FOREACH_ENTRY_REVERSE_SAFE(plist, pstEntry, prevEntry, member) \
    for((pstEntry) = DTQ_ENTRY_LAST(plist, typeof(*(pstEntry)), member); \
        (NULL !=(pstEntry)) && \
        ({(prevEntry) = DTQ_ENTRY_PREV(plist, pstEntry, member); BOOL_TRUE;}); \
        (pstEntry) = (prevEntry))
/*************************************************************************
* func name   :  api_dtq_append
* author      :  Trail
* description :  Append psrclist to pdstlist
* date        :  2015/08/11
* input       :  IN dtq_head_s *pdstlist
                 IN dtq_head_s *psrclist
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_append(IN dtq_head_s *pdstlist, IN dtq_head_s *psrclist)
{
    if (BOOL_TRUE != api_dtq_is_empty(psrclist))
    {
        psrclist->stHead.next->prev = pdstlist->stHead.prev;
        psrclist->stHead.prev->next = pdstlist->stHead.prev->next;
        pdstlist->stHead.prev->next = psrclist->stHead.next;
        pdstlist->stHead.prev = psrclist->stHead.prev;
        api_dtq_init(psrclist);
    }
    return;
}
/*************************************************************************
* func name   :  api_dtq_free_all
* author      :  Trail
* description :  Remove an free all nodes from DTQ list
* date        :  2015/08/11
* input       :  IN dtq_head_s *plist
                 IN void(*pfFree)(void *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
static inline void api_dtq_free_all(IN dtq_head_s *plist, IN void(*pfFree)(void *))
{
    dtq_node_s *currnode;
    dtq_node_s *nextnode;
    DTQ_FOREACH_SAFE(plist, currnode, nextnode)
    {
        pfFree(currnode);
    }
    api_dtq_init(plist);
    return;
}
#ifdef __cplusplus
}
#endif
#endif
