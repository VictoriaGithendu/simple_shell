#include "main.h"
/**
 * dup_inf - duplicates info to create new env or aliaas
 * @cmd_name: name
 * @cmd_value: value
 * Return: new env or alias.
 */
char *dup_inf(char *cmd_name, char *cmd_value)
{
	char *new_value;
	int length_name, length_value, length;

	length_name = strLength(cmd_name);
	length_value = strLength(cmd_value);
	length = length_name + length_value + 2;
	new_value = malloc(sizeof(char) * (length));
	strCpy(new_value, cmd_name);
	strCat(new_value, "=");
	strCat(new_value, cmd_value);
	strCat(new_value, "\0");

	return (new_value);
}
/**
 * _setenviron - sets an environment variable
 * @cmd_name: environment variable name
 * @cmd_value: environment variable value
 * @data_struct: data structure (environ)
 * Return: no return
 */
void _setenviron(char *cmd_name, char *cmd_value, data_shell *data_struct)
{
	int x;
	char *environ_var, *environ_name;

	for (x = 0; data_struct->_environ[x]; x++)
	{
		environ_var = strDup(data_struct->_environ[x]);
		environ_name = strTok(environ_var, "=");
		if (strCmp(environ_name, cmd_name) == 0)
		{
			free(data_struct->_environ[x]);
			data_struct->_environ[x] = dup_inf(environ_name, cmd_value);
			free(environ_var);
			return;
		}
		free(environ_var);
	}

	data_struct->_environ = reAllocDp(data_struct->_environ,
			x, sizeof(char *) * (x + 2));
	data_struct->_environ[x] = dup_inf(cmd_name, cmd_value);
	data_struct->_environ[x + 1] = NULL;
}
/**
 * _set_environ - function that compares env variables names
 * @data_struct: data
 * Return: 1 on success.
 */
int _set_environ(data_shell *data_struct)
{

	if (data_struct->args[1] == NULL || data_struct->args[2] == NULL)
	{
		handle_error(data_struct, -1);
		return (1);
	}
	_setenviron(data_struct->args[1], data_struct->args[2], data_struct);
	return (1);
}
/**
 * _unset_environ - function that deletes environment variable
 * @data_struct: data relevant
 * Return: 1 on success.
 */
int _unset_environ(data_shell *data_struct)
{
	char **realloc_environ;
	char *environ_var, *environ_name;
	int x, y, z;

	if (data_struct->args[1] == NULL)
	{
		handle_error(data_struct, -1);
		return (1);
	}
	z = -1;
	for (x = 0; data_struct->_environ[x]; x++)
	{
		environ_var = strDup(data_struct->_environ[x]);
		environ_name = strTok(environ_var, "=");
		if (strCmp(environ_name, data_struct->args[1]) == 0)
		{
			z = x;
		}
		free(environ_var);
	}
	if (z == -1)
	{
		handle_error(data_struct, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (x));
	for (x = y = 0; data_struct->_environ[x]; x++)
	{
		if (x != z)
		{
			realloc_environ[y] = data_struct->_environ[x];
			y++;
		}
	}
	realloc_environ[y] = NULL;
	free(data_struct->_environ[z]);
	free(data_struct->_environ);
	data_struct->_environ = realloc_environ;
	return (1);
}

