#include "lists.h"
/**
* get_nodeint_at_index - Return node to specified num on linked list
* @head: First node at linked list
* @index: num of node to return
*
* Return: Points at node that is being searched, or NULL
*/
listint_t *get_nodeint_at_index(listint_t *head, unsigned int index)
{
	unsigned int i = 0;
	listint_t *temp = head;

	while (temp && i < index)
	{
		temp = temp->next;
		i++;
	}

	return (temp ? temp : NULL);
}
