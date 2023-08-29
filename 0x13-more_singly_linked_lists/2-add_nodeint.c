#include "lists.h"
/**
* add_nodeint - add new node to the beginning of linked list
* @head: points at first node in list
* @n: info to input in new node
*
* Return: pointer to new node, or NULL if it fails
*/
listint_t *add_nodeint(listint_t **head, const int n)
{
	listint_t *new;

	new = malloc(sizeof(listint_t));
	if (!new)
		return (NULL);

	new->n = n;
	new->next = *head;
	*head = new;

	return (new);
}
