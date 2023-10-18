#include "main.h"
/**
 * find_builtin - finding function pointer of a command
 * @command: command to  find function pointer
 * Return: function pointer
 */
int (*find_builtin(char *command))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", print_environ },
		{ "exit", exit_shell },
		{ "setenv", _set_environ },
		{ "unsetenv", _unset_environ },
		{ "cd", cdShell },
		{ "help", handle_help },
		{ NULL, NULL }
	};
	int index;

	for (index = 0; builtin[index].name; index++)
	{
		if (strCmp(builtin[index].name, command) == 0)
			break;
	}
	return (builtin[index].f);
}
/**
 * execute_line - determines input is a builtin command
 * @data_struct: data pointer
 * Return: 1 on success.
 */
int execute_line(data_shell *data_struct)
{
	int (*builtin)(data_shell *data_struct);

	if (data_struct->args[0] == NULL)
		return (1);

	builtin = find_builtin(data_struct->args[0]);

	if (builtin != NULL)
		return (builtin(data_struct));

	return (cmdExec(data_struct));
}
