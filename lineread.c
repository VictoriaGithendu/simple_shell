#include "main.h"
/**
 * read_line - function that gets the input string.
 * @i_eof: getline function value
 * Return: input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);
	return (input);
}
