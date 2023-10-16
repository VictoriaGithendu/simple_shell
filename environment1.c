#include "main.h"
/**
 * create_environ_or_alias - creates a new environment or alias
 * @name: environment or alias name
 * @value: environment or alias value
 * Return: new environment or alias
 */
char *create_environ_or_alias(const char *name, const char *value)
{
	int length_name, length_value, length;
	char *new;

	length_name = strlen(name);
	length_value =  strlen(value);
	length = length_name + 2;
	new = (char *)malloc(sizeof(char) * length);

	if (new)
	{
		snprintf(new, length, "%s=%s", name, value);
	}
	return (new);
}
/**
 * _setenviron - function that sets or updates an environment variable
 * @name: environment variable name
 * @value:  environment variable value
 * @environ: environment variable pointer
 */
void _setenviron(char *name, char *value, char ***environ)
{
	int x;
	char *var_environ, *name_environ;

	for (x = 0; (*environ)[x]; x++)
	{
		var_environ = strdup(*environ)[x];
		name_environ = strtok(var_environ, "=");
		if (strcmp(name_environ, name) == 0)
		{
			free((*environ)[x]);
			(*environ)[x] = create_environ_or_alias(name, value);
			free(var_environ);
		}
		free(var_environ);
	}
	*environ = realloc(*environ, (x + 2) * sizeof(char *));
	(*environ)[x] = create_environ_or_alias(name, value);
	(*environ)[x + 1] = NULL;
}
/**
 * set_environ - function that compares environment variable
 * @name: environment variable name
 * @value: environment variable value
 * @data_struct: relevant shell data
 * Return: 1 on success
 */
int set_environ(const char *name, const char *value, shell *data_struct)
{
	if (name == NULL || value == NULL)
	{
		handle_error(data_struct, -1);
		return (0);
	}
	set_environ(name, value, data_struct);
	return (1);
}
/**
 * unset_environ - function that deletes an environment variable
 * @name: environment variable name
 * @data_struct: relevant shell data
 * Return: 1 on success
 */
int unset_environ(const char *name, shell *data_struct)
{
	int x, y;

	if (name == NULL)
	{
		handle_error(data_struct, -1);
		return (0);
	}
	for (x = 0; data_struct->_environ[x]; x++)
	{
		char *var_environ = strdup(data_struct->_environ[x]);
		char *name_environ = strtok(var_environ, "=");

		if (strcmp(name_environ, name) == 0)
		{
			free(data_struct->_environ[x]);
			for (y = x; data_struct->_environ[y]; y++)
			{
				data_struct->_environ[y] = data_struct->_environ[y + 1];
			}
			return (1);
		}
		free(var_environ);
	}
	get_error(datash, -1);
	return (0);
}
