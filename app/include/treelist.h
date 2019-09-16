#ifndef _TREELIST_H_
#define _TREELIST_H_

typedef struct _treelist_
{
	int key;
	char string[12];
	struct _treelist_ *left;
	struct _treelist_ *right;
	struct _treelist_ *parent;
}treelist, *Ptreelist;

Ptreelist treelist_create_all(int *key, int all_num);

int treelist_get_hight(Ptreelist list);

void treelist_preorder(Ptreelist list);

void treelist_inorder(Ptreelist list);

void treelist_postorder(Ptreelist list);

Ptreelist treelist_del_one(Ptreelist list, int key);

Ptreelist treelist_find_PRE_POST(Ptreelist head, TREELIST_ENUM flag);

Ptreelist treelist_find_pre_post(Ptreelist head, TREELIST_ENUM flag);

#endif




