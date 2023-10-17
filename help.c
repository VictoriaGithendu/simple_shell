#include "main.h"
/**
 * handle_help - retrieves help messages according builtin
 * @data_struct: data structure
 * Return: Return 0
*/
int handle_help(data_shell *data_struct)
{
	char *command = data_struct->args[1];

	if (command == NULL)
		generalHelp();
	else if (strCmp(command, "setenv") == 0)
		setenvHelp();
	else if (strCmp(command, "env") == 0)
		envHelp();
	else if (strCmp(command, "unsetenv") == 0)
		unsetenvHelp();
	else if (strCmp(command, "help") == 0)
		infHelp();
	else if (strCmp(command, "exit") == 0)
		exitHelp();
	else if (strCmp(command, "cd") == 0)
		cdHelp();
	else if (strCmp(command, "alias") == 0)
		aliasHelp();
	else
		write(STDERR_FILENO, data_struct->args[0],
		      strLength(data_struct->args[0]));

	data_struct->status = 0;
	return (1);
}
