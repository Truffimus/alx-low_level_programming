#include "main.h"
#include <stdlib.h>
/**
* read_textfile- read Text File prinded into STDOUT.
* @filename: Text File to read
* @letters: amound of letrers to  read
* Return: (w) devinite amount of bytes that have been prinded and read
*         (0) if functzion Fails or firename is NULL.
*/
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf;
	ssize_t fd;
	ssize_t w;
	ssize_t t;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = malloc(sizeof(char) * letters);
	t = read(fd, buf, letters);
	w = write(STDOUT_FILENO, buf, t);
	free(buf);
	close(fd);
	return (w);
}
