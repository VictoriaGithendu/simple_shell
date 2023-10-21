#include "main.h"
/**
 * exit_shell - function that exits shell
 * @datash: data structure
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int isDigit;
	int str_length;
	int max_number;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		isDigit = _isdigit(datash->args[1]);
		str_length = _strlen(datash->args[1]);
		max_number = ustatus > (unsigned int)INT_MAX;
		if (!isDigit || str_length > 10 || max_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
