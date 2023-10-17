#include "main.h"
/**
 * cmp_environ_var - compares env variables names
 * @environ_var: name of the environment variable
 * @envname: name passed
 * Return: 0 if are not equal. Another value if they are.
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
 * get_environ - get an environment variable
 * @envname: name of the environment variable
 * @environ_var: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *get_environ(const char *envname, char **environ_var)
{
	char *ptr = NULL;
	int x, y = 0;

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
 * print_environ - prints the evironment variables
 * @data_struct: data relevant.
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
