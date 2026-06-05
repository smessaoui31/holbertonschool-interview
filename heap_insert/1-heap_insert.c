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
 * find_parent - Finds the parent node for the next insertion slot
 * @root: Root of the heap
 * @size: Current number of nodes
 * @dir: Set to 0 for left child, 1 for right child
 * Return: Pointer to the parent node
 */
static heap_t *find_parent(heap_t *root, size_t size, int *dir)
{
	int bits[64];
	int depth, i;
	size_t tmp;

	depth = 0;
	tmp = size + 1;
	while (tmp > 1)
	{
		bits[depth++] = tmp & 1;
		tmp >>= 1;
	}
	*dir = bits[0];
	for (i = depth - 1; i > 0; i--)
	{
		if (bits[i] == 0)
			root = root->left;
		else
			root = root->right;
	}
	return (root);
}

/**
 * sift_up - Bubbles a node up to restore Max Heap ordering
 * @node: Newly inserted node
 * Return: Pointer to the node now holding the inserted value
 */
static heap_t *sift_up(heap_t *node)
{
	int tmp;

	while (node->parent && node->n > node->parent->n)
	{
		tmp = node->n;
		node->n = node->parent->n;
		node->parent->n = tmp;
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to store in the new node
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *node, *parent;
	size_t size;
	int dir;

	if (root == NULL)
		return (NULL);
	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}
	size = tree_size(*root);
	parent = find_parent(*root, size, &dir);
	node = binary_tree_node(parent, value);
	if (node == NULL)
		return (NULL);
	if (dir == 0)
		parent->left = node;
	else
		parent->right = node;
	return (sift_up(node));
}
