#include "lists.h"

/**
 * is_palindrome - checks if a singly linked list is a palindrome
 * @head: pointer to pointer of first node
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow, *fast, *prev, *next, *second, *p1, *p2;
	int result;

	if (*head == NULL || (*head)->next == NULL)
		return (1);

	slow = *head;
	fast = *head;
	while (fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	second = slow->next;
	slow->next = NULL;

	prev = NULL;
	while (second)
	{
		next = second->next;
		second->next = prev;
		prev = second;
		second = next;
	}
	second = prev;

	result = 1;
	p1 = *head;
	p2 = second;
	while (p2)
	{
		if (p1->n != p2->n)
		{
			result = 0;
			break;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	prev = NULL;
	while (second)
	{
		next = second->next;
		second->next = prev;
		prev = second;
		second = next;
	}
	slow->next = prev;

	return (result);
}
