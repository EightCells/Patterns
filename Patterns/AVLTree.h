#pragma once
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

template<typename T>
struct TreeNode
{
	T data{};
	TreeNode* left{};
	TreeNode* right{};
	int height = 0;
	TreeNode() = default;
	explicit TreeNode(T d) :data(d) {}
};

template<typename T>
class AVLTree
{
public:
	int height(TreeNode<T>* t)
	{
		return t == nullptr ? -1 : t->height;
	}
	void UpdateHeight(TreeNode<T>* t)
	{
		t->height = (height(t->left) > height(t->right) ? height(t->left) : height(t->right)) + 1;
	}
	int BalanceFactor(TreeNode<T>* t)
	{
		if (t == nullptr)return 0;
		return height(t->left) - height(t->right);
	}
	void insert(TreeNode<T>* root, T& val)
	{
		root = insetHelper(root, val);
	}
private:
	TreeNode<T>* rightRotate(TreeNode<T>* t)
	{
		TreeNode<T>* child = t->left;
		TreeNode<T>* grandchild = child->right;
		child->right = t;
		t->left = grandchild;
		UpdateHeight(t);
		UpdateHeight(child);
		return child;
	}
	TreeNode<T>* leftRotate(TreeNode<T>* t)
	{
		TreeNode<T>* child = t->right;
		TreeNode<T>* grandchild = child->left;
		child->left = t;
		t->right = grandchild;
		UpdateHeight(t);
		UpdateHeight(child);
		return child;
	}
	TreeNode<T>* Rotate(TreeNode<T>* t)
	{
		int balance_factor = BalanceFactor(t);
		if (balance_factor > 1)
		{
			if (BalanceFactor(t->left) >= 0)
			{
				return rightRotate(t);
			}
			else
			{
				t->left = leftRotate(t->left);
				return rightRotate(t);
			}
		}
		if (balance_factor < -1)
		{
			if (BalanceFactor(t->right) <= 0)
			{
				return leftRotate(t);
			}
			else
			{
				t->right = rightRotate(t->right);
				return leftRotate(t);
			}
		}
		return t;
	}
	TreeNode<T>* insetHelper(TreeNode<T>* t, T& val)
	{
		if (t == nullptr)
		{
			return new TreeNode<T>(val);
		}
		if (val < t->data)
		{
			t->left = insetHelper(t->left, val);
		}
		else if (val > t->data)
		{
			t->right = insetHelper(t->right, val);
		}
		else
		{
			return t;
		}
		UpdateHeight(t);
		t = Rotate(t);
		return t;
	}
};




#endif // !__AVL_TREE__
