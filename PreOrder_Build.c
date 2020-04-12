#define _CRT_SECURE_WARNINGS
#include <stdio.h>

typedef struct BinaryTreeNode
{
	char data;
	struct BinaryTreeNode *left;
	struct BinaryTreeNode *right;
}BTNode;

typedef struct {
	BTNode *root;		
	int	used;
}	Result;

Result CreateTree(char preorder[], int size)
{
	if (size == 0)
	{
		Result result =
		{
			.root = NULL,
			.used = 0
		};
		return result;
	}

	char RootValue = preorder[0];

	if (RootValue == '#')
	{
		Result result =
		{
			.root = NULL,
			.used = 1
		};
		return result;
	}
	
	BTNode *root = (BTNode*)malloc(sizeof(BTNode));
	root->data = RootValue;
	Result LeftNode = CreateTree(preorder + 1, size - 1);
	Result RightNode = CreateTree(preorder + LeftNode.used + 1, size - LeftNode.used - 1);

	root->left = LeftNode.root;
	root->right = RightNode.root;

	Result result =
	{
		.root = root,
		.used = 1 + LeftNode.used + RightNode.used
	};
	return result;
}

void GetSize(BTNode *root)
{
	int n = 0;

	if (root == NULL)
	{
		return;
	}

	n++;
	GetSize(root->left);
	GetSize(root->right);
}

void GetLeafSize(BTNode *root)
{
	int n = 0;
	if (root->left == NULL && root->right == NULL)
	{
		n++;
	}

	GetLeafSize(root->left);
	GetLeafSize(root->right);
}

BTNode * Find(BTNode *root, char val)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->data == val)
	{
		return root;
	}

	BTNode *n = Find(root->left, val);
	if (n != NULL)
	{
		return n;
	}

	n = Find(root->right, val);
	if (n != NULL)
	{
		return n;
	}

	return NULL;
}