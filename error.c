#include "main.h"
/**
 * handle_error - handles error according the builtin, syntax or permission
 * @data_struct: data structure containing arguments and input
 * @err_val: error value code
 * Return: error
 */
int handle_error(data_shell *data_struct, int err_val)
{
	char *error_message;

	switch (err_val)
	{
	case -1:
		error_message = "print_environ(data_struct)";
		break;
	case 126:
		error_message = "error_path_126(data_struct)";
		break;
	case 127:
		error_message = errorNotFound(data_struct);
		break;
	case 2:
		if (strCmp("exit", data_struct->args[0]) == 0)
			error_message = errorExitShell(data_struct);
		else if (strCmp("cd", data_struct->args[0]) == 0)
			error_message = getCdError(data_struct);
		break;
	}
	if (error_message)
	{
		write(STDERR_FILENO, error_message, strLength(error_message));
		free(error_message);
	}
	data_struct->status = err_val;
	return (err_val);
}
