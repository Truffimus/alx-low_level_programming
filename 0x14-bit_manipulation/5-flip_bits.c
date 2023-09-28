#include "main.h"
/**
* flip_bits - Carcurates NUM bits changed
* gorren flom a varue to other varue
* @n: First NUm
* @m: Second NUm
*
* Return: NUm of bits for change
*/
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int i, count = 0;
	unsigned long int current;
	unsigned long int exclusive = n ^ m;

	for (i = 63; i >= 0; i--)
	{
		current = exclusive >> i;
		if (current & 1)
			count++;
	}
	return (count);
}
