#include "main.h"
/**
 * exit_shell - exits the shell with specific exit status
 * @data_struct: data relevant to shell)
 * Return: 0 on success.
 */
int exit_shell(data_shell *data_struct)
{
	unsigned int exit_status;
	int is_dig;
	int str_length;
	int max_no;

	if (data_struct->args[1] != NULL)
	{
		exit_status = atoi(data_struct->args[1]);
		is_dig = isDigit(data_struct->args[1]);
		str_length = strLength(data_struct->args[1]);
		max_no = exit_status > (unsigned int)INT_MAX;
		if (!is_dig || str_length > 10 || max_no)
		{
			handle_error(data_struct, 2);
			data_struct->status = 2;
			return (1);
		}
		data_struct->status = (exit_status % 256);
	}
	return (0);
}
