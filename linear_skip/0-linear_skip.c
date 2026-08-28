#include "search.h"

/**
 * linear_skip - Searches for a value in a sorted skip list of integers
 * using the express lane to narrow down the search range.
 * @list: Pointer to the head of the skip list to search in
 * @value: Value to search for
 *
 * Return: Pointer to the first node where value is located, or NULL if
 * value is not present in list or if list is NULL
 */
skiplist_t *linear_skip(skiplist_t *list, int value)
{
	skiplist_t *prev, *cur, *boundary, *node;

	if (list == NULL)
		return (NULL);

	prev = list;
	cur = list->express;

	while (cur != NULL && cur->n < value)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       cur->index, cur->n);
		prev = cur;
		cur = cur->express;
	}

	if (cur != NULL)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       cur->index, cur->n);
		boundary = cur;
	}
	else
	{
		boundary = prev;
		while (boundary->next != NULL)
			boundary = boundary->next;
	}

	printf("Value found between indexes [%lu] and [%lu]\n",
	       prev->index, boundary->index);

	for (node = prev; node != NULL; node = node->next)
	{
		printf("Value checked at index [%lu] = [%d]\n",
		       node->index, node->n);
		if (node->n == value)
			return (node);
		if (node == boundary)
			break;
	}

	return (NULL);
}
