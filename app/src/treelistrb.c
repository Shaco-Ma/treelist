#include <stdio.h>
#include <stdlib.h>
#include "treelistrb.h"

#define SWAP_COLOR(a, b)	(a^=b,b^=a,a^=b)

//颜色变化,向下递归颜色改变
void treelisrrb_change_colour(Ptreelistrb head)
{
	while(head != NULL)
	{
		head->color = (head->color == RED)?(BLACK):(RED);
		treelisrrb_change_colour(head->left);
		treelisrrb_change_colour(head->right);
	}
}

//左旋->把该节点成为右孩子的左孩子,右孩子必须存在,且右孩子的左孩子应该为空
//相应的颜色也要变化;除了变化后的head的右子树不变,其他都要变化颜色
Ptreelistrb treelistrb_left_ratation(Ptreelistrb head)
{
	if(head != NULL && head->right != NULL)
	{
		Ptreelistrb temp = head->right;
		SWAP_COLOR(temp->color, head->color);
		head->right = temp->left;
		temp->left = head;
		head = temp;
		//head->left的右边是原来的head的right的left,等于是同级左右移动,不需要改变颜色
		if(head->left->left != NULL)
			treelisrrb_change_colour(head->left->left);
		if(head->right != NULL)
			treelisrrb_change_colour(head->right);
	}
	return head;
}

//右旋->把该节点成为左孩子的右孩子,左孩子必须存在,且做孩子的右孩子应该为空
//相应的颜色也要变化
Ptreelistrb treelistrb_right_ratation(Ptreelistrb head)
{
	if(head != NULL && head->left != NULL)
	{
		Ptreelistrb temp = head->left;
		SWAP_COLOR(temp->color, head->color);
		head->left = temp->right;
		temp->right = head;
		head = temp;
		//head->left的右边是原来的head的right的left,等于是同级左右移动,不需要改变颜色
		if(head->right->right != NULL)
			treelisrrb_change_colour(head->right->right);
		if(head->left != NULL)
			treelisrrb_change_colour(head->left);
	}
	return head;
}

//修复rb tree
Ptreelistrb treelistrb_fixed(Ptreelistrb head)
{
	return head;
}

//插入,并将节点置为红色
//父节点是红色,比较麻烦,慢慢处理,分三种情况
//1,叔叔z节点是红色,那么需要把父节x点置为黑色,父节点的父节点y置为红色,父节点的父节点的另一个子节点z置为黑色
//2叔叔节点z是黑色,因为父节点x是红色,祖父y一定是黑色,叔叔z是黑色的,否则违背定理
//并且当前节点是父节点的右节点
//2叔叔节点z是黑色,因为父节点x是红色,祖父y一定是黑色,叔叔z是黑色的,否则违背定理
//并且当前节点是父节点的左节点
Ptreelistrb treelistrb_insert(Ptreelistrb head, int key)
{
	if(head)
	{
		if(key < head->key)
		{
			return treelistrb_insert(head->left, key);
		}
		else
		{
			return treelistrb_insert(head->right, key);
		}
	}
	else
	{
		Ptreelistrb new_node = malloc(sizeof(treelistrb));
		new_node->color = RED;
		new_node->key = key;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	return head;
}











