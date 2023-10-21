#include "main.h"
/**
 * get_sigint - function that finds prompt crtl + c call
 * @sig: Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
