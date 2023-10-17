#include "main.h"
/**
 * run_shell - function that runs shell loop
 * @data_struct: relevant data
 * Return: 0
 */
void run_shell(data_shell *data_struct)
{
	int continue_loop = 1, eof_indicator;
	char *input;

	while (continue_loop == 1)
	{
		printf("^-^ ");
		input = read_input_line(&eof_indicator);
		if (eof_indicator != -1)
			input = remove_comment(input);
		if (input == NULL)
			continue;
		if (checkSyntaxError(data_struct, input) == 1)
		{
			data_struct->status = 2;
			free(input);
			continue;
		}
		input = rep_str_var(input, data_struct);
		continue_loop = execute_commands(data_struct, input);
		data_struct->counter += 1;
		free(input);
	}
	{
		continue_loop = 0;
		free(input);
	}
}
/**
 * remove_comments - function that removes comments from input string
 * @input: string input
 * Return: input without comments
 */
char *remove_comments(char *input)
{
	int x, end_index;

	end_index = -1;

	for (x = 0; input[x]; x++)
		if (input[x] == '#')
			if (x == 0)
				free(input);
	return (NULL);
	if (input[x - 1] == ' ' || input[x - 1] == '\t' || input[x - 1] == ';')
		end_index = x;
	if (end_index != -1)
		input[end_index] = '\0';
	return (input);
}
