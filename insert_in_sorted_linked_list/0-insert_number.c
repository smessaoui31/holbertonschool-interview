#include <stdlib.h>
#include "lists.h"

/**
 * insert_node - inserts a number into a sorted singly linked list
 * @head: pointer to pointer of first node of listint_t list
 * @number: integer to be inserted
 * Return: address of the new node, or NULL if it failed
 */
listint_t *insert_node(listint_t **head, int number)
{
    listint_t *new;
    listint_t *current;

    new = malloc(sizeof(listint_t));
    if (new == NULL)
        return (NULL);

    new->n = number;
    new->next = NULL;

    current = *head;

    /* Insert at head if list is empty or number is smallest */
    if (*head == NULL || number <= current->n)
    {
        new->next = *head;
        *head = new;
        return (new);
    }

    /* Traverse to find correct position */
    while (current->next != NULL && current->next->n < number)
        current = current->next;

    new->next = current->next;
    current->next = new;

    return (new);
}