#ifndef _TREELIST_AVL_H_
#define _TREELIST_AVL_H_

typedef struct _ptreelist_avl_
{
	int key;
	char key_string[12];
	char hight;
	struct _ptreelist_avl_ *left;
	struct _ptreelist_avl_ *right;
	//struct _ptreelist_avl_ *parent;
}treelist_avl, *Ptreelist_avl;

Ptreelist_avl treelist_avl_creat(Ptreelist_avl head, int key);

int treelist_avl_get_hight(Ptreelist_avl list);

void treelist_avl_preorder(Ptreelist_avl list);

void treelist_avl_inorder(Ptreelist_avl list);

void treelist_avl_postorder(Ptreelist_avl list);

Ptreelist_avl treelist_avl_find_pre_post(Ptreelist_avl head, TREELIST_ENUM flag);

Ptreelist_avl treelist_avl_delete(Ptreelist_avl head, int key, Ptreelist_avl parent_node);

#endif



