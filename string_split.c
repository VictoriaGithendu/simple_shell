#include "main.h"
/**
 * swap_char - function that swaps | and &
 * @input: input string
 * @bool: swap type
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
	int x;

	if (bool == 0)
	{
		for (x = 0; input[x]; x++)
		{
			if (input[x] == '|')
			{
				if (input[x + 1] != '|')
					input[x] = 16;
				else
					x++;
			}
			if (input[x] == '&')
			{
				if (input[x + 1] != '&')
					input[x] = 12;
				else
					x++;
			}
		}
	}
	else
	{
		for (x = 0; input[x]; x++)
		{
			input[x] = (input[x] == 16 ? '|' : input[x]);
			input[x] = (input[x] == 12 ? '&' : input[x]);
		}
	}
	return (input);
}
/**
 * add_nodes - function thhat add separators and command lines
 * @head_s: separator list head
 * @head_l: command lines list head
 * @input: input string
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int x;
	char *line;

	input = swap_char(input, 0);

	for (x = 0; input[x]; x++)
	{
		if (input[x] == ';')
			add_sep_node_end(head_s, input[x]);

		if (input[x] == '|' || input[x] == '&')
		{
			add_sep_node_end(head_s, input[x]);
		x++;
		}
	}
	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}
/**
 * go_next - function that moves to next command line stored
 * @list_s: separator list double pointer
 * @list_l: command line list double pointer
 * @datash: data structure
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
/**
 * split_line - function that splits the input string
 * @input: pointer to input string.
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * split_commands - executes command lines and separators
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit
 */
int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;
	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;
	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;
		go_next(&list_s, &list_l, datash);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	free_sep_list(&head_s);
	free_line_list(&head_l);
	if (loop == 0)
		return (0);
	return (1);
}
