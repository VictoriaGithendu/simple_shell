#include "main.h"
/**
 * handle_help - retrieves help messages according builtin
 * @data_struct: data structure
 * Return: Return 0
*/
int handle_help(data_shell *data_struct)
{
	if (data_struct->args[1] == NULL)
		generalHelp();
	else if (strCmp(data_struct->args[1], "setenv") == 0)
		setenvHelp();
	else if (strCmp(data_struct->args[1], "env") == 0)
		envHelp();
	else if (strCmp(data_struct->args[1], "unsetenv") == 0)
		unsetenvHelp();
	else if (strCmp(data_struct->args[1], "help") == 0)
		infHelp();
	else if (strCmp(data_struct->args[1], "exit") == 0)
		exitHelp();
	else if (strCmp(data_struct->args[1], "cd") == 0)
		cdHelp();
	else if (strCmp(data_struct->args[1], "alias") == 0)
		aliasHelp();
	else
		write(STDERR_FILENO, data_struct->args[0],
		      strLength(data_struct->args[0]));

	data_struct->status = 0;
	return (1);
}
