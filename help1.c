#include "main.h"

/**
 * envHelp - function with information for builtin env
 * Return: nothing
 */
 
void envHelp(void)
{
	char *helpVar = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));

}


/**
 * setenvHelp - function for builtin setenv
 * Return: nothing
 */
 
void setenvHelp(void)
{

	char *helpVar = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "int replace)\n\t";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}


/**
 * unsetenvHelp - function for builtin unsetenv
 * Return: nothing
 */
void unsetenvHelp(void)
{
	char *helpVar = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}


/**
 * generalHelp - function with general information for builtin
 * Return: nothing
 */
 
void generalHelp(void)
{
	char *helpVar = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "unsetenv [variable]\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}


/**
 * exitHelp - function for help with exit builtin
 * Return: no return
 */
void exitHelp(void)
{
	char *helpVar = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}
