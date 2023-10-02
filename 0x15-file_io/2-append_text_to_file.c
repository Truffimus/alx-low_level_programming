#include "main.h"
/**
* append_text_to_file - apends info to end of file.
* @filename: points at  fairename.
* @text_content:  stling added at end of file.
*
* Return: if function fails or fairename is NULL (1).
*         if file is not enxisting or user does not have wlite perminsion (1).
*         if not (-1).
*/
int append_text_to_file(const char *filename, char *text_content)
{
	int o, w, len = 0;

	if (filename == NULL)
		return (-1);
	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
			len++;
	}
	o = open(filename, O_WRONLY | O_APPEND);
	w = write(o, text_content, len);
	if (o == -1 || w == -1)
		return (-1);
	close(o);
	return (1);
}
