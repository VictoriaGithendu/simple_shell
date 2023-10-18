#include "main.h"
/**
 * cmp_environ_var - compares env variables names
 * @environ_var: name of the environment variable
 * @envname: name passed
 * Return: 0 if are not equal
 */
int cmp_environ_var(const char *environ_var, const char *envname)
{
	int x;

	for (x = 0; environ_var[x] != '='; x++)
	{
		if (environ_var[x] != envname[x])
		{
			return (0);
		}
	}
	return (x + 1);
}
/**
 * get_environ - function that gets an environment variable
 * @envname: environment variable name
 * @environ_var: environment variable
 * Return: environment variable value
 */
char *get_environ(const char *envname, char **environ_var)
{
	char *ptr;
	int x, y;

	ptr = NULL;
	y = 0;

	for (x = 0; environ_var[x]; x++)
	{
		y = cmp_environ_var(environ_var[x], envname);
		if (y)
		{
			ptr = environ_var[x];
			break;
		}
	}
	return (ptr + y);
}
/**
 * print_environ -function that prints the evironment variables
 * @data_struct: data
 * Return: 1 on success.
 */
int print_environ(data_shell *data_struct)
{
	int x, y;

	for (x = 0; data_struct->_environ[x]; x++)
	{
		for (y = 0; data_struct->_environ[x][y]; y++)
			;
		write(STDOUT_FILENO, data_struct->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	data_struct->status = 0;

	return (1);
}
