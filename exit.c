#include "main.h"
/**
 * exit_shell - function that exits the shell
 * @data_struct: data relevant
 * Return: 0 on success.
 */
int exit_shell(data_shell *data_struct)
{
	unsigned int ustat;
	int digit;
	int str_length;
	int max_no;

	if (data_struct->args[1] != NULL)
	{
		ustat = aToI(data_struct->args[1]);
		digit = isDigit(data_struct->args[1]);
		str_length = strLength(data_struct->args[1]);
		max_no = ustat > (unsigned int)INT_MAX;
		if (!digit || str_length > 10 || max_no)
		{
			handle_error(data_struct, 2);
			data_struct->status = 2;
			return (1);
		}
		data_struct->status = (ustat % 256);
	}
	return (0);
}
