#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treelist_common.h"
#include "treelist_avl.h"

#define HIGHT(x)	((x==NULL)?-1:(((Ptreelist_avl)x)->hight))
#define MAX(a, b)	(a>b?a:b)
#define SUB(a, b)	((a==-1||b==-1)?(0):(a>b)?(a-b):(b-a))
//#define SUB(a, b)	((a>b)?(a-b):(b-a))

//返回找到的节点
Ptreelist_avl treelist_avl_search(Ptreelist_avl head, int key, Ptreelist_avl *parent_node)
{
	Ptreelist_avl need_node = NULL;
	if(head == NULL)
	{
		parent_node = NULL;
		return NULL;
	}

	if(key != head->key)
	{
		need_node = treelist_avl_search(head->key > key?head->right:head->left, key, &head);
	}
	else
	{
		//这个是需要的那个节点
		return head;
	}

	return need_node;
}

//left left rotation
//A的左孩子的左子树插入导致了不平衡
//需要对A进行左旋
//A的左子树B替换节点A,成为根节点
//B的右节点成为A的左节点(A的原来的左节点为B)
//A成为B的右节点
Ptreelist_avl treelist_avl_ll_ratation(Ptreelist_avl head)
{
	Ptreelist_avl new_head = NULL;
	new_head = head->left;
	head->left = new_head->right;
	new_head->right = head;

	head->hight = MAX(HIGHT(head->left), HIGHT(head->right)) + 1;
	new_head->hight = MAX(HIGHT(head->left), HIGHT(new_head->right)) + 1;

	return new_head;
}

//right righnt rotation
//A的右孩子的右子树插入节点导致了不平衡
//需要对A队形右旋
//A的右子树B替换节点A,成为根节点
//B的左节点给A的右节点(A原来的右节点是B)
//A成为B的左节点
Ptreelist_avl treelist_avl_rr_ratation(Ptreelist_avl head)
{
	Ptreelist_avl new_head = NULL;
	new_head = head->right;
	head->right = new_head->left;
	new_head->left = head;

	head->hight = MAX(HIGHT(head->left), HIGHT(head->right)) + 1;
	new_head->hight = MAX(HIGHT(head->left), HIGHT(new_head->right)) + 1;
	return new_head;
}

//left righnt rotation
//A的左孩子的右子树插入节点导致了不平衡
//要先对A的左子树进行RR旋转
//再对A进行LL旋转
Ptreelist_avl treelist_avl_lr_ratation(Ptreelist_avl head)
{
	head->left = treelist_avl_rr_ratation(head->left);
	return treelist_avl_ll_ratation(head);
}

//righnt left rotation
//A的右孩子的左子树插入节点导致不平衡
//先对A的右子树进行LL旋转(因为是对A的右子树的左子树插入)
//再对A进行RR旋转
Ptreelist_avl treelist_avl_rl_ratation(Ptreelist_avl head)
{
	head->right = treelist_avl_ll_ratation(head->right);
	return treelist_avl_rr_ratation(head);
}

void treelist_avl_preorder(Ptreelist_avl list)
{
	if(list != NULL)
	{
		printf("%s---list->key = %d, list->sring:%s, list->hight = %d\n", __func__, list->key, list->key_string, list->hight);
		treelist_avl_preorder(list->left);
		treelist_avl_preorder(list->right);
	}
}

void treelist_avl_inorder(Ptreelist_avl list)
{
	if(list != NULL)
	{
		treelist_avl_inorder(list->left);
		printf("%s---list->key = %d, list->sring:%s\n", __func__, list->key, list->key_string);
		treelist_avl_inorder(list->right);
	}
}

void treelist_avl_postorder(Ptreelist_avl list)
{
	if(list != NULL)
	{
		treelist_avl_postorder(list->left);
		treelist_avl_postorder(list->right);
		printf("%s---list->key = %d, list->sring:%s\n", __func__, list->key, list->key_string);
	}
}

int treelist_avl_get_hight(Ptreelist_avl list)
{
	if(list == NULL)
		return 0;
	int left = treelist_avl_get_hight(list->left);
	int right = treelist_avl_get_hight(list->right);
	return (left>right)?(left+1):(right+1);
}

Ptreelist_avl treelist_avl_insert(Ptreelist_avl head, Ptreelist_avl new_item)
{
	//printf("%s-%d\n", __func__, __LINE__);
	if(head == NULL)
	{
		head = new_item;
		//new_list->hight = 0;
	}
	else if(head->key > new_item->key)
	{
		head->left = treelist_avl_insert(head->left, new_item);
		//出现不平衡
		if(HIGHT(head->left) - HIGHT(head->right) >= 2)
		{
			//判断是右子树还是左子树出现的失衡
			//如果是在此节点的左边出现失衡,那么应该是LL旋转此节点
			if(head->left->key > new_item->key)
			{
				head = treelist_avl_ll_ratation(head);
			}
			//就是根节点的左节点的右子树数显失衡
			else
			{
				head = treelist_avl_lr_ratation(head);
			}
		}
	}
	else if(head->key < new_item->key)
	{
		head->right = treelist_avl_insert(head->right, new_item);
		//出现不平衡
		if((HIGHT(head->right) - HIGHT(head->left)) >= 2)
		{
			//判断是右子树还是左子树出现的失衡
			//如果是在此节点有字数的的左边出现失衡,那么应该是RL旋转此节点
			if(head->right->key > new_item->key)
			{
				head = treelist_avl_rl_ratation(head);
			}
			//就是根节点的右节点的左子树数显失衡
			else
			{
				head = treelist_avl_rr_ratation(head);
			}
		}
	}
	else
	{
		printf("Same key value, can't insert!!!!!!\n");
	}
	//printf("%s-%d\n", __func__, __LINE__);
	head->hight = MAX(HIGHT(head->left), HIGHT(head->right)) + 1;
	return head;
}

Ptreelist_avl treelist_avl_creat(Ptreelist_avl head, int key)
{
	Ptreelist_avl new_list = NULL;
	Ptreelist_avl new_item = malloc(sizeof(treelist_avl));
	memset(new_item, 0, sizeof(treelist_avl));
	new_item->key = key;
	sprintf(new_item->key_string, "--%d--", key);
	//printf("new_item->key = %d\n", new_item->key);
	new_list = treelist_avl_insert(head, new_item);
	//查找最大左右深度
	return new_list;
}

Ptreelist_avl treelist_avl_find_pre(Ptreelist_avl head)
{
	if(head != NULL && head->right != NULL)
	{
		return treelist_avl_find_pre(head->right);
	}
	return head;
}

Ptreelist_avl treelist_avl_find_post(Ptreelist_avl head)
{
	if(head != NULL && head->left != NULL)
	{
		return treelist_avl_find_post(head->left);
	}
	return head;
}

Ptreelist_avl treelist_avl_find_pre_post(Ptreelist_avl head, TREELIST_ENUM flag)
{
	Ptreelist_avl need_node = head;
	switch(flag)
	{
		case TREELIST_PRE:
			{
				if(head->left != NULL)
				{
					need_node = treelist_avl_find_pre(head->left);
				}
			}
			break;
		case TREELIST_POST:
			{
				if(head->right != NULL)
				{
					need_node = treelist_avl_find_post(head->right);
				}
			}
			break;
		default:
			printf("Some Wrong in here:%s---%d\n", __func__, __LINE__);
			break;
	}
	return need_node;
}

//需要找到他的父节点,找到要删除的节点,需要判断是否不平衡,不平衡要旋转
//二叉树的删除,要分几种情况:
//1:如果有两个子节点,那么查找该节点的后继节点B(就是节点A的右节点的最小节点),替换为节点A,并把B的右节点C给到B的父节点的左节点
//	或许有这么一个思路:先把B的值和A的值都替换了,在递归执行删除节点A
//2:如果只有一个子节点,替换当前删除的节点
//3:如果没有子节点,直接删除
Ptreelist_avl treelist_avl_delete(Ptreelist_avl head, int key, Ptreelist_avl parent_node)
{
	if(head == NULL)
	{
		return NULL;
	}
	//printf("head->key = %d\n", head->key);
	if(key < head->key)
	{
		head->left = treelist_avl_delete(head->left, key, head);
		if((HIGHT(head->right) - HIGHT(head->left)) >= 2)
		{
			//判断是右子树还是左子树出现的失衡
			//如果是在此节点有字数的的左边出现失衡,那么应该是RL旋转此节点
			//if(head->right->key > key)
			if(HIGHT(head->left) > HIGHT(head->right))
			{
				head = treelist_avl_rl_ratation(head);
			}
			//就是根节点的右节点的左子树数显失衡
			else
			{
				head = treelist_avl_rr_ratation(head);
			}
		}
		printf("%d----head->key = %d\n", __LINE__, head->key);
	}
	else if(key > head->key)
	{
		head->right = treelist_avl_delete(head->right, key, head);
		if((HIGHT(head->left) - HIGHT(head->right)) >= 2)
		{
			//判断是右子树还是左子树出现的失衡
			//如果是在此节点的左边出现失衡,那么应该是LL旋转此节点
			//if(head->left->key > key)
			if(HIGHT(head->right) > HIGHT(head->left))
			{
				head = treelist_avl_ll_ratation(head);
			}
			//就是根节点的左节点的右子树数显失衡
			else
			{
				head = treelist_avl_lr_ratation(head);
			}
		}
		printf("%d----head->key = %d\n", __LINE__, head->key);
	}
	else
	{
		//找到真正需要删除的节点,比如前驱或者后继之类的
		if(head->left != NULL && head->right != NULL)
		{
			/*
			Ptreelist_avl need_node = treelist_avl_find_pre_post(head, TREELIST_POST);
			head->key = need_node->key;
			memset(head->key_string, 0, sizeof(head->key_string));
			strcpy(head->key_string, need_node->key_string);
			head->right = treelist_avl_delete(head->right, need_node->key, head);
			*/
			// 如果tree的左子树比右子树高；
			// 则(01)找出tree的左子树中的最大节点
			//   (02)将该最大节点的值赋值给tree。
			//   (03)删除该最大节点。
			// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
			// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
			if(HIGHT(head->left) > HIGHT(head->right))
			{
				Ptreelist_avl need_node = treelist_avl_find_pre_post(head, TREELIST_PRE);
				head->key = need_node->key;
				memset(head->key_string, 0, sizeof(head->key_string));
				strcpy(head->key_string, need_node->key_string);
				head->left = treelist_avl_delete(head->left, need_node->key, head);
			}
			// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
			// 则(01)找出tree的右子树中的最小节点
			//   (02)将该最小节点的值赋值给tree。
			//   (03)删除该最小节点。
			// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
			// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
			else
			{
				Ptreelist_avl need_node = treelist_avl_find_pre_post(head, TREELIST_POST);
				head->key = need_node->key;
				memset(head->key_string, 0, sizeof(head->key_string));
				strcpy(head->key_string, need_node->key_string);
				head->right = treelist_avl_delete(head->right, need_node->key, head);
			}
		}
		else if((head->left != NULL && head->right == NULL) || (head->left == NULL && head->right != NULL))
		{
			//只有一个子节点,替换为要删除的节点
			(head == parent_node->left)?(parent_node->left = (head->right == NULL)?head->left:head->right):(parent_node->right = (head->right == NULL)?head->left:head->right);
			free(head);
			head = NULL;
		}
		else
		{
			//没有子孩子,直接删除,还要确定父节点到这里的关系
			(head == parent_node->left)?(parent_node->left = NULL):(parent_node->right = NULL);
			free(head);
			head = NULL;
		}
	}

	return head;
}



