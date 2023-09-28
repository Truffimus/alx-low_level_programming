#include "main.h"
/**
* clear_bit - puts NUM of paricurar bit to 0
* @n: sows NUM for changing
* @index: posision of lemoved bit
*
* Return: (1) if Successful, if Fails (-1)
*/
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);
	*n = (~(1UL << index) & *n);
	return (1);
}
