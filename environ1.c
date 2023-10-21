#include "main.h"
/**
 * copy_info - function that copies provided information
 * @name:  new environment or alias name to create
 * @value: new environment or alias value
 * Return: new created environment variable or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int length_name, length_value, length;

	length_name = _strlen(name);
	length_value = _strlen(value);
	length = length_name + length_value + 2;
	new = malloc(sizeof(char) * (length));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");
	return (new);
}
/**
 * set_env - function that sets an environ variable and assigns a value
 * @name: environment variable name to set
 * @value: environment variable   value to assign
 * @datash: data structure
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int x;
	char *var_env, *name_env;

	for (x = 0; datash->_environ[x]; x++)
	{
		var_env = _strdup(datash->_environ[x]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[x]);
			datash->_environ[x] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	datash->_environ = _reallocdp(datash->_environ, x, sizeof(char *) * (x + 2));
	datash->_environ[x] = copy_info(name, value);
	datash->_environ[x + 1] = NULL;
}
/**
 * _setenv - function that compares environment variables names
 * @datash: data structure
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	set_env(datash->args[1], datash->args[2], datash);
	return (1);
}
/**
 * _unsetenv - function that deletes environment variable
 * @datash: data structure
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int x, y, z;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	z = -1;
	for (x = 0; datash->_environ[x]; x++)
	{
		var_env = _strdup(datash->_environ[x]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			z = x;
		}
		free(var_env);
	}
	if (z == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (x));
	for (x = y = 0; datash->_environ[x]; x++)
	{
		if (x != z)
		{
			realloc_environ[y] = datash->_environ[x];
			y++;
		}
	}
	realloc_environ[y] = NULL;
	free(datash->_environ[z]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
