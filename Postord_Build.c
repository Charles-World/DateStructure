#include <stdio.h>
#include <stdlib.h>
struct TreeNode
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

 struct TreeNode* Find(struct TreeNode* root, int val)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->val == val)
	{
		return root;
	}

	struct TreeNode* n = Find(root->left, val);
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



struct TreeNode* buildTree(int *postorder, int *inorder, int size)
{
	if (size == 0)
	{
		return NULL;
	}
	int rootValue = postorder[size - 1];
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (inorder[i] == rootValue)
		{
			index = i;
			break;
		}
	}
	struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	root->val = rootValue;
	root->left = buildTree(postorder, inorder, index);
	root->right = buildTree(postorder + index, inorder + index + 1, size - index - 1);
	
	return root;
}

void postorder2(struct TreeNode* root)
{
	if (!root)
	{
		return;
	}
	postorder2(root->left);
	postorder2(root->right);

	printf("%d ", root->val);
}

void inorder2(struct TreeNode* root)
{
	if (!root)
	{
		return;
	}
	inorder2(root->left);
	printf("%d ", root->val);
	inorder2(root->right);
}

void preorder2(struct TreeNode* root)
{
	if (!root)
	{
		return;
	}
	printf("%d ", root->val);
	preorder2(root->left);
	preorder2(root->right);
}


int GetTreeC(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	return GetTreeC(root->right) + GetTreeC(root->left) + 1;
}

int TreeHigh(struct TreeNode* root)
{
	if (root == NULL)
	{
		return 0;
	}

	int L = TreeHigh(root->left);
	int R = TreeHigh(root->right);

	return (L > R ? L : R) + 1;
}



int main()
{
	int postorder[] = { 5, 6, 2, 8, 31, 9, 17, 13, 3 };
	int inorder[] = { 5, 6, 8, 2, 3, 13, 31, 17, 9 };
	int len = sizeof(inorder) / sizeof(inorder[0]);
	struct TreeNode* root = buildTree(postorder, inorder, len);
	/*struct TreeNode* ret = Find(root, 31);
	if (!ret)
	{
		printf("Ã»ÕÒµ½\n");
	}
	else
	{
		printf("%d\n", ret->val);
	}*/

	/*postorder2(root);
	printf("\n");
	inorder2(root);*/

	int C = GetTreeC(root);
	printf("%d ", C);
	int h = TreeHigh(root);
	printf("%d ", h);

	system("pause");
	return 0;
}