#ifndef _TREELISTRB_H_
#define _TREELISTRB_H_

typedef enum
{
	BLACK,
	RED,
}RB_TREE_COLOR;

typedef struct _treelistrb_
{
	int key;
	RB_TREE_COLOR color;
	struct _treelistrb_ *right;
	struct _treelistrb_ *left;
}treelistrb, *Ptreelistrb;


#endif




