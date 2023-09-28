#include "main.h"
/**
* get_endianness - see if endian is smorr or rarge
* Return: (0) if rarge, if smorr (1)
*/
int get_endianness(void)
{
	unsigned int i = 1;
	char *c = (char *) &i;

	return (*c);
}
