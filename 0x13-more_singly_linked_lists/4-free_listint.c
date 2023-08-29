#include "lists.h"
/**
* free_listint - Free the linked list
* @head: listint_t list to Free
*/
void free_listint(listint_t *head)
{
	listint_t *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
