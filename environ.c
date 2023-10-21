#include "main.h"
/**
 * cmp_env_name - function that checks equal  name of environment variables
 * @nenv: environment variable name to  compare
 * @name: name to compare against
 * Return: 0 on failure
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int x;

	for (x = 0; nenv[x] != '='; x++)
	{
		if (nenv[x] != name[x])
		{
			return (0);
		}
	}
	return (x + 1);
}
/**
 * _getenv - function that retrieves environment variable value
 * @name: environment variable name to retrieve
 * @_environ: environment variable list
 * Return: environment variable value  found.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int x, mov;

	ptr_env = NULL;
	mov = 0;

	for (x = 0; _environ[x]; x++)
	{
		mov = cmp_env_name(_environ[x], name);
		if (mov)
		{
			ptr_env = _environ[x];
			break;
		}
	}
	return (ptr_env + mov);
}
/**
 * _env - function that prints relevant data to the evironment variables
 * @datash: relevant environment variables data.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int x, y;

	for (x = 0; datash->_environ[x]; x++)
	{
		for (y = 0; datash->_environ[x][y]; y++)
			;
		write(STDOUT_FILENO, datash->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;
	return (1);
}
