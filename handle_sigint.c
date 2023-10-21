#include "main.h"
/**
 * handle_sigint - handle the crtl + c signal in prompt
 * @signal: signal number
 */
void handle_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
