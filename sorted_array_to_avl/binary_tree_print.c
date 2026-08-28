#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

static int _height(const binary_tree_t *tree);
static int print_t(const binary_tree_t *tree, int is_left, int offset,
	int depth, char s[][255]);

/**
 * _height - Measures the height of a binary tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: Height of the tree, or 0 if tree is NULL
 */
static int _height(const binary_tree_t *tree)
{
	int left, right;

	if (tree == NULL)
		return (0);

	left = _height(tree->left);
	right = _height(tree->right);

	return ((left > right ? left : right) + 1);
}

/**
 * print_t - Recursively fills a character matrix with a tree drawing
 * @tree: Pointer to the current node
 * @is_left: 1 if node is a left child, 0 otherwise
 * @offset: Horizontal offset in the matrix
 * @depth: Current depth (row) in the matrix
 * @s: Character matrix to fill
 *
 * Return: Width used by this subtree
 */
static int print_t(const binary_tree_t *tree, int is_left, int offset,
	int depth, char s[][255])
{
	char b[16];
	int width = 5;
	int left, right, i;

	if (!tree)
		return (0);

	sprintf(b, "(%03d)", tree->n);

	left = print_t(tree->left, 1, offset, depth + 1, s);
	right = print_t(tree->right, 0, offset + left + width, depth + 1, s);

	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];

	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}

	return (left + width + right);
}

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char s[100][255];
	int h, i;

	if (!tree)
		return;

	h = _height(tree);
	for (i = 0; i < 100; i++)
		memset(s[i], 32, 254);

	print_t(tree, 0, 0, 0, s);

	for (i = 0; i < h; i++)
	{
		s[i][254] = 0;
		printf("%s\n", s[i]);
	}
}
