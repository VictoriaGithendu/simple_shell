#include "main.h"
/**
 * handle_sigint - Handle the crtl + c signal in prompt
 * @signal: Signal number
 */
void handle_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
