/*************************************************************************
* Copyright (c) 2015, WuHan LangDi Co., Ltd. all rights reserved
*  -----------------------------------------------------------------------
*                            hash.c
*   Project Code :
*   Module Name  :
*   Data Created : 2015/09/16
*   Author       :
*   Description  :
*
*  -----------------------------------------------------------------------
*     Modification History
*      DATA        NAME                    description
*  -----------------------------------------------------------------------
*
*************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"

/*************************************************************************
* func name   :  api_hash_create
* author      :  Trail
* description :  create hash table
* date        :  2015/08/11
* input       :  IN unsigned long size
                 IN unsigned long (*pfhash)(void *)
* output      :
* return      :  hash_table_s *
* modify      :
*************************************************************************/
hash_table_s *api_hash_create(IN unsigned long size, IN unsigned long (*pfhash)(const void *))
{
    hash_table_s *phashtbl = NULL;
    phashtbl = (hash_table_s *)malloc(sizeof(hash_table_s));
    if (NULL != phashtbl)
    {
        memset(phashtbl, 0, sizeof(hash_table_s));
        phashtbl->pbckt = (hash_list_s *)malloc(sizeof(hash_list_s) * size);
        if (NULL != phashtbl->pbckt)
        {
            memset(phashtbl->pbckt, 0, (sizeof(hash_list_s) * size));
            phashtbl->pfhash = pfhash;
            phashtbl->size = size;
        }
        else
        {
            phashtbl = NULL;
        }
    }
    return phashtbl;
}

/*************************************************************************
* func name   :  HASH_destroy
* author      :  Trail
* description :  destroy hash table
* date        :  2015/08/11
* input       :  IN hash_table_s *phashtbl
                 IN void  (*pfFree)(hash_node_s *)
* output      :
* return      :  void
* modify      :
*************************************************************************/
void api_hash_destory(IN hash_table_s *phashtbl, IN void  (*pfFree)(hash_node_s *))
{
    hash_node_s *pnode;
    hash_node_s *next;
    unsigned long index;
    if (NULL == phashtbl)
    {
        return;
    }
    if (NULL != pfFree)
    {
        HASH_SCAN_TBL_SAFE(phashtbl, index, pnode, next)
        {
            (*pfFree)(pnode);
        }
    }
    free(phashtbl->pbckt);
    phashtbl->pbckt = NULL;
    free(phashtbl);
    return;
}

/*************************************************************************
* func name   :  api_hash_find
* author      :  Trail
* description :  find node with key
* date        :  2015/08/11
* input       :  IN hash_table_s *ptbl
                 IN void *pkey
                 IN long(*pfkeycmp)(IN hash_node_s *,IN void *)
* output      :
* return      :  hash_node_s *
* modify      :
*************************************************************************/
hash_node_s *api_hash_find(IN hash_table_s *ptbl,
                       IN void *pkey,
                       IN long(*pfkeycmp)(IN hash_node_s *, IN void *))
{
    hash_node_s *pnode;
    unsigned long index;
    if ((NULL == ptbl) || (NULL == pkey) || (NULL == pfkeycmp))
    {
        return NULL;
    }
    index = HASH_GET_INDEX(ptbl, pkey);
    if (!HASH_IS_VALID_INDEX(ptbl, index))
    {
        return NULL;
    }
    HASH_SCAN_BCKT(ptbl, index, pnode)
    {
        if (0 == (*pfkeycmp)(pnode, pkey))
        {
            break;
        }
    }
    return pnode;
}




