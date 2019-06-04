#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treelist_common.h"
#include "treelist.h"

Ptreelist treelist_creat_one(int key, Ptreelist left, Ptreelist right)
{
	Ptreelist new = malloc(sizeof(treelist));
	memset(new, 0, sizeof(treelist));
	new->key = key;
	sprintf(new->string, "-%d-", key);
	new->left = left;
	new->right = right;
	//new->parent = praent;

	return new;
}

//递归插入,保存头结点,最后输出
Ptreelist treelist_insert(Ptreelist new, Ptreelist list)
{
	Ptreelist head = list;
	if(new->key < list->key)
	{
		if(list->left != NULL)
			treelist_insert(new, list->left);
		else
		{
			list->left = new;
			new->parent = list;
		}
	}
	else
	{
		if(list->right != NULL)
			treelist_insert(new, list->right);
		else
		{
			list->right = new;
			new->parent = list;
		}
	}
	return head;
}

//创建的话貌似只能创建二叉查找树,因为这个才是有规律可寻的,如果y是x的左子树中的一个结点，则key[y] <= key[x]；如果y是x的右子树的一个结点，则key[y] >= key[x]。
Ptreelist treelist_create_all(int *key, int all_num)
{
	int cur_num = 0;
	Ptreelist list = NULL;
	Ptreelist new = NULL;
	while(cur_num < all_num)
	{
		new = treelist_creat_one(key[cur_num], NULL, NULL);
		if(list == NULL)
		{
			list = new;
		}
		else
		{
			list = treelist_insert(new, list);
		}
		cur_num++;
	}

	return list;
}

//前序遍历
//输出根节点的关键之值位于关键字的左子树和右子树之前
void treelist_preorder(Ptreelist list)
{
	if(list != NULL)
	{
		printf("%s:list->key = %d, list->string:%s\n", __func__, list->key, list->string);
		//if(list->parent != NULL)
		//{
		//	printf("%s:list->parent->key = %d\n", __func__, list->parent->key);
		//}
		treelist_preorder(list->left);
		treelist_preorder(list->right);
	}
}

//中序遍历
//输出根节点关键字位于关键字的左子树和右子树之间
void treelist_inorder(Ptreelist list)
{
	if(list != NULL)
	{
		treelist_inorder(list->left);
		printf("%s:list->key = %d, list->string:%s\n", __func__, list->key, list->string);
		treelist_inorder(list->right);
	}
}

//后序遍历
//输出根节点的关键之值位于关键字的左子树和右子树之后
void treelist_postorder(Ptreelist list)
{
	if(list != NULL)
	{
		treelist_postorder(list->left);
		treelist_postorder(list->right);
		printf("%s:list->key = %d, list->string:%s\n", __func__, list->key, list->string);
	}
}

Ptreelist treelist_find_max_min(Ptreelist head, TREELIST_MAIN_MIN_NUM flag)
{
	if(head == NULL)
		return NULL;
	switch(flag)
	{
		case TREELIST_MIN:
			{
				while(head->left != NULL)
				{
					head = head->left;
				}
			}
			break;
		case TREELIST_MAX:
			{
				while(head->right != NULL)
				{
					head = head->right;
				}
			}
			break;
		default:
			{
				printf("%s:%d-No THis flag to find:%d\n", __func__, __LINE__, flag);
			}
			break;
	}
	printf("head->key = %d\n", head->key);
	return head;
}

//查找树的前驱或者后继
/*
   结点node的前驱结点是所有键值小于node的结点中的最大结点，也就是node的左子树的最大结点

   结点node的后继结点是所有键值大于node的结点中的最小结点，也就是node的右子树的最小结点
*/
Ptreelist treelist_find_PRE_POST(Ptreelist head, TREELIST_ENUM flag)
{
	Ptreelist need_item = NULL;
	if(head == NULL)
	{
		return NULL;
	}
	switch(flag)
	{
		//就是顺序排列的时候,该节点前一个节点
		//前驱节点
		case TREELIST_PRE:
			{
				if(head->left != NULL)
				{
					//找到左子树中的最大节点
					need_item = treelist_find_max_min(head->left, TREELIST_MAX);
				}
				else
				{
					//如果没有左子树,那么就向上查找到其父节点有右孩子并且是父节点的右子树的节点
					need_item = head->parent;
					while(need_item != NULL && head == need_item->left)
					{
						head = head->parent;
						need_item = head->parent;
					}
				}
			}
			break;
		//就是顺序排列的时候,该节点的后一个节点
		//后继节点
		case TREELIST_POST:
			{
				//如果head的右子树为NULL,那么从右子树中找到最左的点
				if(head->right != NULL)
				{
					//找到右子树中的最小节点
					need_item = treelist_find_max_min(head->right, TREELIST_MIN);
				}
				else
				{
					//如果没有右子树,那么就向上查找到其父节点有左孩子并且是父节点的左子树的节点
					need_item = head->parent;
					while(need_item != NULL && head == need_item->right)
					{
						head = head->parent;
						need_item = head->parent;
					}
				}
			}
			break;
		default:
			printf("%s-%d:No This flag:%d\n", __func__, __LINE__, flag);
			break;
	}

	return need_item;
}

//找到到相关的节点,用指针传出去
static Ptreelist treelist_find_need(Ptreelist list, int key)
{
	if(list != NULL)
	{
		if(list->key != key)
		{
			return treelist_find_need(list->key > key?list->left:list->right, key);
		}
		else
		{
			return list;
		}
	}
	return 0;
}

static Ptreelist treelist_del_item(Ptreelist head, Ptreelist del_item)
{
	Ptreelist child_item = NULL;
	if(del_item != NULL && head != NULL)
	{
		//if(head == del_item)
		//{
		//	//如果是头结点删除
		//}
		//else
		{
			if(del_item->left != NULL && del_item->right != NULL)
			{
				//要求找到删除节点的后继节点,替换为当前节点,找到的节点,要把父节点的左子树置NULL
				child_item = treelist_find_PRE_POST(del_item, TREELIST_POST);
				printf("child_item->key = %d, del_item->key = %d, del_item->right->key = %d\n", child_item->key, del_item->key, del_item->right->key);
				//如果刚好这个是删除节点的右子树,那么右子树不变,否则给为原来的右子树
				child_item->left = del_item->left;
				if(child_item != del_item->right)
				{
					child_item->parent->left = NULL;
					child_item->right = del_item->right;
				}
				if(del_item->parent != NULL)
				{
					child_item->parent = del_item->parent;
					//再把要删除的节点的父节点到删除节点的这条路打通
					del_item->parent->left == del_item?(del_item->parent->left = child_item):(del_item->parent->right = child_item);
				}
				else
				{
					head = child_item;
				}
			}
			else if((del_item->left != NULL && del_item->right == NULL) || (del_item->left == NULL && del_item->right != NULL))
			{
				child_item = del_item->left == NULL?del_item->right:del_item->left;
				//只有一个子节点,把他放在父节点的下属位置就行了
				if(child_item->key > del_item->parent->key)
				{
					//这里del_item一定是右节点
					del_item->parent->right = child_item;
				}
				else
				{
					//这里del_item一定是左节点
					del_item->parent->left = child_item;
				}
				child_item->parent = del_item->parent;
			}
			else
			{
				del_item->parent->left = NULL;
				del_item->parent->right = NULL;
			}
		}
		free(del_item);
	}
	return head;
}

//查找某一个并且删除该节点
//先找到这个节点
Ptreelist treelist_del_one(Ptreelist list, int key)
{
	Ptreelist old_list_head = list;
	Ptreelist find_list_item = NULL;
	if(list != NULL)
	{
		if((find_list_item = treelist_find_need(list, key))!= NULL)
		{
			printf("find_list_item->key = %d\n", find_list_item->key);
			list = treelist_del_item(old_list_head, find_list_item);
		}
	}

	return list;
}




