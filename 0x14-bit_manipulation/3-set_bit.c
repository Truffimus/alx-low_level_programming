#include "main.h"
/**
* set_bit - puts bit to catein posision at 1
* @n: sows NUM for changing
* @index: posision of bit put at 1
*
* Return: (1) if Successful, if Fails (-1)
*/
int set_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);
	*n = ((1UL << index) | *n);
	return (1);
}
