/*************************************************************************
	> File Name: sl_test.c
	> Author: Trail
	> Mail: 
	> Created Time: Sat 25 Feb 2017 05:04:54 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
	sl_node_s node;
	int data;
}sl_data_s;

sl_head_s g_sl_list;
sl_data_s *get_node (int data)
{
    sl_data_s *pnode = NULL;
    
    pnode = (sl_data_s *)malloc (sizeof(sl_data_s));
    if (pnode == NULL)
    {
        return NULL;
    }
    api_sl_node_init(&pnode->node);
    pnode->data = data;

    return pnode;
}
void show_node()
{
    sl_node_s *curr = NULL, *next = NULL;
    sl_data_s *node = NULL;
    SL_FOREACH_SAFE(&g_sl_list, curr, next)
    {
        if (curr != NULL)
        {
            node = (sl_data_s *)curr;
            printf("%d -> ", node->data);

        }

    }
    printf("\n");
    
    return;
}

int main ()
{
    sl_data_s *pnode = NULL;
    api_sl_init(&g_sl_list);

    pnode = get_node(2);
    if (pnode != NULL)
    {
        api_sl_add_head(&g_sl_list, &pnode->node);

    }
    show_node();
    pnode = get_node(3);
    if (pnode != NULL)
    {
        api_sl_add_head(&g_sl_list, &pnode->node);

    }
    show_node();
    api_sl_del_after(&g_sl_list, &pnode->node);
    show_node();
    pnode = get_node(5);
    if (pnode != NULL)
    {
        api_sl_add_head(&g_sl_list, &pnode->node);

    }
    show_node();
    api_sl_add_after(&g_sl_list, &pnode->node, &(get_node(8))->node); 


    show_node();
    api_sl_del_head(&g_sl_list);
    show_node();

    return 0;
}
