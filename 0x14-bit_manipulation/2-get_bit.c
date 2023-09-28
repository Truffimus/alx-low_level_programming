#include "main.h"
/**
* get_bit - shows NUM of bit in posision at decmal NUM
* @n: NUM sangched
* @index: posision of bit
*
* Return: NUM of bit
*/
int get_bit(unsigned long int n, unsigned int index)
{
	int bit_val;

	if (index > 63)
		return (-1);
	bit_val = (n >> index) & 1;
	return (bit_val);
}
