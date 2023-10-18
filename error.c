#include "main.h"
/**
 * handle_error - handles error according the builtin
 * @data_struct: data structure containing arguments
 * @err_val: error value code
 * Return: error
 */
int handle_error(data_shell *data_struct, int err_val)
{
	char *err;

	switch (err_val)
	{
	case -1:
		err = errorEnv(data_struct);
		break;
	case 126:
		err = errorPath(data_struct);
		break;
	case 127:
		err = errorNotFound(data_struct);
		break;
	case 2:
		if (strCmp("exit", data_struct->args[0]) == 0)
			err = errorExitShell(data_struct);
		else if (strCmp("cd", data_struct->args[0]) == 0)
			err = getCdError(data_struct);
		break;
	}
	if (err)
	{
		write(STDERR_FILENO, err, strLength(err));
		free(err);
	}
	data_struct->status = err_val;
	return (err_val);
}
