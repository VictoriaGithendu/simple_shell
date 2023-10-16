include "main.h"
/**
 * find_builtin - finding function pointer of a command
 * @command: command to  find function pointer
 * Return: function pointer of the builtin command
 */
int (*find_builtin(char *command))(shell *)
{
	int index;

	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	for (index = 0; builtin[index].name; index++)
	{
		if (_strcmp(builtin[index].name, command) == 0)
			break;
	}
	return (builtin[index].f);
}
