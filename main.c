#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treelist_common.h"
#include "treelist.h"
#include "treelist_avl.h"
#include "treelistrb.h"
//先创建一个树,查找某一个,三次,三种遍历方式来一次
/*
					9
		5						13
	2		7				11		15
1	  3  6		8		10     12 14	16
*/
int main(int argv, char *argc[])
{
#if 0
	int del_num = 0;
	if(argv >= 2)
	{
		del_num = atoi(argc[1]);
	}
	//int key[] = {11, 12,13,14,15,16,17,18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//int key[] = {1,5,4,3,2,6};
	int key[] = {9, 5, 2, 7, 1, 3, 6, 8, 13, 11, 10, 12, 15, 14, 16};
	del_num = (del_num > sizeof(key)/sizeof(key[0]))?(sizeof(key)/sizeof(key[0])-1):del_num;
	Ptreelist list = NULL;
	list = treelist_create_all(key, sizeof(key)/sizeof(key[0]));
	printf("left = %d, right = %d\n", treelist_get_hight(list->left), treelist_get_hight(list->right));
	//treelist_preorder(list);
	//treelist_inorder(list);
	//treelist_postorder(list);
	//printf("%s-%d\n", __func__, __LINE__);
	list = treelist_del_one(list, key[del_num]);
	//treelist_preorder(list);
	treelist_inorder(list);
	//treelist_postorder(list);
	//Ptreelist node_test = NULL;
	//node_test = treelist_find_pre_post(list, TREELIST_PRE);
	//printf("TREELIST_PRE:node_test->key = %d\n", node_test->key);
	//node_test = treelist_find_pre_post(list, TREELIST_POST);
	//printf("TREELIST_POST:node_test->key = %d\n", node_test->key);
#endif


#if 0
	//AVL tree
	Ptreelist_avl avl_list = NULL;
	int i = 0;
	//int avl_key[] = {9, 5, 2, 7, 1, 3, 6, 8, 13, 11, 10, 12, 15, 14, 16};
	//int avl_key[] = {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,15, 16};
	int avl_key[] = {2, 3, 5, 6, 7, 8, 9, 10};
	//del_num = (del_num > sizeof(avl_key)/sizeof(avl_key[0]))?(sizeof(avl_key)/sizeof(avl_key[0])-1):del_num;
	while(i < sizeof(avl_key)/sizeof(avl_key[0]))
	{
		avl_list = treelist_avl_creat(avl_list, avl_key[i]);
		i++;
	}

	printf("treelist_avl left high = %d\n", treelist_avl_get_hight(avl_list->left));
	printf("treelist_avl right high = %d\n", treelist_avl_get_hight(avl_list->right));

	treelist_avl_preorder(avl_list);
	//treelist_avl_inorder(avl_list);
	printf("\n\n\n");
	Ptreelist_avl test_node = NULL;
	test_node = treelist_avl_find_pre_post(avl_list, TREELIST_PRE);
	printf("TREELIST_PRE:node_test->key = %d\n", test_node->key);
	test_node = treelist_avl_find_pre_post(avl_list, TREELIST_POST);
	printf("TREELIST_POST:node_test->key = %d\n", test_node->key);
	avl_list = treelist_avl_delete(avl_list, 10, NULL);
	treelist_avl_preorder(avl_list);
#endif

	//rbtree

	return 1;
}






