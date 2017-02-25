/*************************************************************************
	> File Name: stq_test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Feb 2017 05:04:54 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct {
	stq_node_s node;
	int data;
}stq_data_s;

stq_head_s g_stq_list;
stq_data_s *get_node (int data)
{
    stq_data_s *pnode = NULL;
    
    pnode = (stq_data_s *)malloc (sizeof(stq_data_s));
    if (pnode == NULL)
    {
        return NULL;
    }
    api_stq_node_init(&pnode->node);
    pnode->data = data;

    return pnode;
}
void show_node()
{
    stq_node_s *curr = NULL, *next = NULL;
    stq_data_s *node = NULL;
    STQ_FOREACH_SAFE(&g_stq_list, curr, next)
    {
        if (curr != NULL)
        {
            node = (stq_data_s *)curr;
            printf("%d -> ", node->data);

        }

    }
    printf("\n");
    
    return;
}

int main ()
{
    stq_data_s *pnode = NULL;
    api_stq_init(&g_stq_list);

    pnode = get_node(2);
    if (pnode != NULL)
    {
        api_stq_add_head(&g_stq_list, &pnode->node);

    }
    show_node();
    pnode = get_node(3);
    if (pnode != NULL)
    {
        api_stq_add_head(&g_stq_list, &pnode->node);

    }
    show_node();
    api_stq_del_after(&g_stq_list, &pnode->node);
    show_node();
    pnode = get_node(5);
    if (pnode != NULL)
    {
        api_stq_add_head(&g_stq_list, &pnode->node);

    }
    show_node();
    api_stq_add_after(&g_stq_list, &pnode->node, &(get_node(8))->node); 


    show_node();
    api_stq_del_head(&g_stq_list);
    show_node();

    return 0;
}

