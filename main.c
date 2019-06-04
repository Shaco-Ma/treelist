#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treelist_common.h"
#include "treelist.h"
//先创建一个树,查找某一个,三次,三种遍历方式来一次
/*
					9
		5						13
	2		7				11		15
1	  3  6		8		10     12 14	16
*/
int main(void)
{
	Ptreelist list = NULL;
	//int key[] = {11, 12,13,14,15,16,17,18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int key[] = {9, 5, 2, 7, 1, 3, 6, 8, 13, 11, 10, 12, 15, 14, 16};
	//int key[] = {1,5,4,3,2,6};
	list = treelist_create_all(key, sizeof(key)/sizeof(key[0]));
	treelist_preorder(list);
	treelist_inorder(list);
	treelist_postorder(list);
	printf("%s-%d\n", __func__, __LINE__);
	list = treelist_del_one(list, 13);
	treelist_preorder(list);
	treelist_inorder(list);
	treelist_postorder(list);
	return 1;
}






