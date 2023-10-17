#include "main.h"

/**
 * infHelp - function for information for the builtin help
 * Return: nothing
 */
 
void infHelp(void)
{
	char *helpVar = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}


/**
 * aliasHelp - function with info for builtin alias
 * Return: nothing
 */
void aliasHelp(void)
{
	char *helpVar = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}


/**
 * cdHelp - function with info for builtin cd
 * Return: nothing
 */
void cdHelp(void)
{
	char *helpVar = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, helpVar, strLength(helpVar));
	helpVar = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, helpVar, strLength(helpVar));
}
