#include "lists.h"
/**
* sum_listint - Summarizes sum of all info in the listint_t list
* @head: First node in linked list
*
* Return: Total sum
*/
int sum_listint(listint_t *head)
{
	int sum = 0;
	listint_t *temp = head;

	while (temp)
	{
		sum += temp->n;
		temp = temp->next;
	}

	return (sum);
}
