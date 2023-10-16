#include "main.h"
/**
 * get_environ - function that gets environment variable value
 * @name: environment variable name to retrieve
 * @environ: environment variables array
 * Return: environment variable value
 */
char *get_environ(const char *name, char **environ)
{
	int x, y;

	for (x = 0; environ[x]; x++)
	{
		for (y = 0; environ[x][y] == name[y]; y++)
		{
			if (name[y] == '\0')
			{
				return (environ[x] + y + 1);
			}
		}
	}
	return (NULL);
}
/**
 * print_environ - function that prints environment variables
 * @environ: environment variable array
 * Return: 1 on success
 */
int print_environ(char **environ)
{
	int x, y;

	for (x = 0; environ[x]; x++)
	{
		for (y = 0; environ[x][y]; y++)
			write(STDOUT_FILENO, environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}
/**
 * cmp_environ_var - function that compares environ variable
 * @environ_var: environment variable name
 * @name: name to compare
 * Return: 0 on success
 */
int cmp_environ_var(const char *environ_var, const char *name)
{
	int x;

	for (x = 0; environ_var[x] != '='; x++)
	{
		if (environ_var[x] != name[x])
			return (0);
	}
	return (x + 1);
}
