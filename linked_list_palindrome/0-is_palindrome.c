#include <stdlib.h>
#include "lists.h"

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to pointer of first node
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(listint_t **head)
{
	listint_t *current;
	int *arr;
	size_t len, i;

	if (*head == NULL)
		return (1);

	len = 0;
	current = *head;
	while (current)
	{
		len++;
		current = current->next;
	}

	arr = malloc(sizeof(int) * len);
	if (!arr)
		return (0);

	current = *head;
	for (i = 0; i < len; i++)
	{
		arr[i] = current->n;
		current = current->next;
	}

	for (i = 0; i < len / 2; i++)
	{
		if (arr[i] != arr[len - 1 - i])
		{
			free(arr);
			return (0);
		}
	}

	free(arr);
	return (1);
}
