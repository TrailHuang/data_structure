/*************************************************************************
	> File Name: dtq_test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Feb 2017 05:04:54 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct {
	dtq_node_s node;
	int data;
}dtq_data_s;

dtq_head_s g_dtq_list;
dtq_data_s *get_node (int data)
{
    dtq_data_s *pnode = NULL;
    
    pnode = (dtq_data_s *)malloc (sizeof(dtq_data_s));
    if (pnode == NULL)
    {
        return NULL;
    }
    api_dtq_node_init(&pnode->node);
    pnode->data = data;

    return pnode;
}
void show_node()
{
    dtq_node_s *curr = NULL, *next = NULL;
    dtq_data_s *node = NULL;
    DTQ_FOREACH_SAFE(&g_dtq_list, curr, next)
    {
        if (curr != NULL)
        {
            node = (dtq_data_s *)curr;
            printf("%d -> ", node->data);

        }

    }
    printf("\n");
    
    return;
}

int main ()
{
    dtq_data_s *pnode = NULL;
    api_dtq_init(&g_dtq_list);

    pnode = get_node(2);
    if (pnode != NULL)
    {
        api_dtq_add_head(&g_dtq_list, &pnode->node);

    }
    show_node();
    pnode = get_node(3);
    if (pnode != NULL)
    {
        api_dtq_add_head(&g_dtq_list, &pnode->node);

    }
    show_node();
    api_dtq_del_head(&g_dtq_list);
    show_node();
    pnode = get_node(5);
    if (pnode != NULL)
    {
        api_dtq_add_head(&g_dtq_list, &pnode->node);

    }
    show_node();
    api_dtq_add_after(&pnode->node, &(get_node(8))->node); 


    show_node();
    api_dtq_del_head(&g_dtq_list);
    show_node();

    return 0;
}

