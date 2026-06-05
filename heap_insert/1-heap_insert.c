#include <stdlib.h>
#include "binary_trees.h"

/**
 * tree_size - Counts all nodes in a binary tree
 * @root: Pointer to the root
 * Return: Total number of nodes
 */
static size_t tree_size(heap_t *root)
{
	if (root == NULL)
		return (0);
	return (1 + tree_size(root->left) + tree_size(root->right));
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to store in the new node
 * Return: Pointer to the inserted node (after sift-up), or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *node, *parent;
	size_t size, path, tmp;
	int bits[64];
	int depth, i;

	if (root == NULL)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = tree_size(*root);

	/*
	 * For a complete binary tree, the (size+1)-th node position
	 * can be found by reading the bits of (size+1) after the MSB:
	 * 0 = go left, 1 = go right.  The last bit picks left/right child.
	 */
	path = size + 1;
	depth = 0;
	tmp = path;
	while (tmp > 1)
	{
		bits[depth++] = tmp & 1;
		tmp >>= 1;
	}
	/* bits[0] = LSB ... bits[depth-1] = bit just below MSB */

	parent = *root;
	for (i = depth - 1; i > 0; i--)
	{
		if (bits[i] == 0)
			parent = parent->left;
		else
			parent = parent->right;
	}

	node = binary_tree_node(parent, value);
	if (node == NULL)
		return (NULL);

	if (bits[0] == 0)
		parent->left = node;
	else
		parent->right = node;

	/* Sift up: swap values until heap property is restored */
	while (node->parent && node->n > node->parent->n)
	{
		tmp = node->n;
		node->n = node->parent->n;
		node->parent->n = (int)tmp;
		node = node->parent;
	}

	return (node);
}
