#include "main.h"
/**
 * release_data_structure - frees data structure memory
 * @data_struct: data structure to be released
 * Return: no return
 */
void release_data_structure(data_shell *data_struct)
{
	unsigned int x;

	for (x = 0; data_struct->_environ[x]; x++)
	{
		free(data_struct->_environ[x]);
	}
	free(data_struct->_environ);
	free(data_struct->pid);
}
/**
 * init_data_structure - Initialize data structure with given arguements
 * @data_struct: data structure
 * @arguement_vector: argument vector
 * Return: no return
 */
void init_data_structure(data_shell *data_struct, char **arguement_vector)
{
	unsigned int x;

	data_struct->av = arguement_vector;
	data_struct->input = NULL;
	data_struct->args = NULL;
	data_struct->status = 0;
	data_struct->counter = 1;

	for (x = 0; environ[x]; x++)
		;
	data_struct->_environ = malloc(sizeof(char *) * (x + 1));

	for (x = 0; environ[x]; x++)
	{
		data_struct->_environ[x] = strDup(environ[x]);
	}
	data_struct->_environ[x] = NULL;
	data_struct->pid = iToA(getpid());
}
/**
 * main - Main shell entry point
 * @arguement_count: argument count
 * @arguement_vector: argument vector
 * Return: 0 on success.
 */
int main(int arguement_count, char **arguement_vector)
{
	data_shell data_struct;
	(void) arguement_count;

	signal(SIGINT, handle_sigint);
	init_data_structure(&data_struct, arguement_vector);
	run_shell(&data_struct);
	release_data_structure(&data_struct);
	if (data_struct.status < 0)
		return (255);
	return (data_struct.status);
}
