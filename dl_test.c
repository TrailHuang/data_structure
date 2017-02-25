/*************************************************************************
	> File Name: dl_test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Feb 2017 05:04:54 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "list.h"

typedef struct {
	dl_node_s node;
	int data;
}dl_data_s;

dl_head_s g_dl_list;
dl_data_s *get_node (int data)
{
    dl_data_s *pnode = NULL;
    
    pnode = (dl_data_s *)malloc (sizeof(dl_data_s));
    if (pnode == NULL)
    {
        return NULL;
    }
    api_dl_node_init(&pnode->node);
    pnode->data = data;

    return pnode;
}
void show_node()
{
    dl_node_s *curr = NULL, *next = NULL;
    dl_data_s *node = NULL;
    DL_FOREACH_SAFE(&g_dl_list, curr, next)
    {
        if (curr != NULL)
        {
            node = (dl_data_s *)curr;
            printf("%d -> ", node->data);

        }

    }
    printf("\n");
    
    return;
}

int main ()
{
    dl_data_s *pnode = NULL;
    api_dl_init(&g_dl_list);

    pnode = get_node(2);
    if (pnode != NULL)
    {
        api_dl_add_head(&g_dl_list, &pnode->node);

    }
    show_node();
    pnode = get_node(3);
    if (pnode != NULL)
    {
        api_dl_add_head(&g_dl_list, &pnode->node);

    }
    show_node();
    api_dl_del_head(&g_dl_list);
    show_node();
    pnode = get_node(5);
    if (pnode != NULL)
    {
        api_dl_add_head(&g_dl_list, &pnode->node);

    }
    show_node();
    api_dl_add_after(&pnode->node, &(get_node(8))->node); 


    show_node();
    api_dl_del_head(&g_dl_list);
    show_node();

    return 0;
}

