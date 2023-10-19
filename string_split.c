#include "main.h"
/**
 * swap_special_chars - function to swap special characters
 * @input: string input
 * @bool: swapping flag
 * Return: string
 */
char *swap_special_chars(char *input, int bool)
{
	int x = 0;

	if (bool == 0)
		for (x = 0; input[x]; x++)
		{
			if (input[x] == '|')
			{
				if (input[x + 1] != '|')
					input[x] = 16;
				x++;
			}
			if (input[x] == '&')
			{
				if (input[x + 1] != '&')
					input[x] = 12;
				x++;
			}
		}
	else
		for (x = 0; input[x]; x++)
		{
			input[x] = (input[x] == 16 ? '|' : input[x]);
					input[x] = (input[x] == 12 ? '&' : input[x]);
		}
	return (input);
}
/**
 * addNode - parses the input string and creates separator and command line
 * @input: string input
 * @head_s: separator list head
 * @head_l: command line list head
 * Return: 0
 */
void addNode(sep_list **head_s, line_list **head_l, char *input)
{
	char *line;
	int x;

	input = swap_special_chars(input, 0);
	for (x = 0; input[x]; x++)
	{
		if (input[x] == ';')
			addSepNodeEnd(head_s, input[x]);
	}
	if (input[x] == '|' || input[x] == '&')
		addSepNodeEnd(head_s, input[x]);
	x++;

	line = strTok(input, ";|&");
	do {
		line = swap_special_chars(line, 1);
		addLineNodeEnd(head_l, line);
		line = strTok(NULL, ";|&");
	} while (line != NULL);
}
/**
 * move_to_nxt - move to the next command line stored based on the separator
 * @sep_l: list separator
 * @line_l: line list command
 * @data_struct: relevant data
 */
void move_to_nxt(sep_list **sep_l, line_list **line_l, data_shell *data_struct)
{
	int continue_loop;
	sep_list *sep_node;
	line_list *line_node;

	continue_loop = 1;
	sep_node = *sep_l;
	line_node = *line_l;
	while (sep_node != NULL && continue_loop)
	{
		if (data_struct->status == 0)
		{
			if (sep_node->separator == '&' || sep_node->separator == ';')
				continue_loop = 0;
	if (sep_node->separator == '|')
		line_node = line_node->next;
	sep_node = sep_node->next;
		}
		else
	{
		if (sep_node->separator == '|' || sep_node->separator == ';')
			continue_loop = 0;
		if (sep_node->separator == '&')
			line_node = line_node->next;
		sep_node = sep_node->next;
	}
	if (sep_node != NULL && !continue_loop)
		sep_node = sep_node->next;
	}
	*sep_l = sep_node;
	*line_l = line_node;
}
/**
 * splitLine - function that tokenizes a string input
 * @input: string input to tokenize
 * Return: token array
 */
char **splitLine(char *input)
{
	size_t token_size;
	size_t x = 0;
	char **tokens;
	char *token;

	token_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (token_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = strTok(input, TOK_DELIM);
	tokens[0]  = token;

	for (x = 1; token != NULL; x++)
	{
		if (x == token_size)
		{
			token_size += TOK_BUFSIZE;
			tokens = reAllocDp(tokens, x, sizeof(char *)  * token_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = strTok(NULL, TOK_DELIM);
		tokens[x] = token;
	}
	return (tokens);
}
/**
 * execute_commands - function that execute command lines separated by ;, |, &
 * @data_struct: relevant data
 * @input: string input
 * Return: 0 on exit, 1 to continue
 */
int execute_commands(data_shell *data_struct, char *input)
{
	sep_list *head_s, *sep_l;
	line_list *head_l, *line_l;
	int count;

	head_l = NULL;
	head_s = NULL;
	addNode(&head_s, &head_l, input);
	sep_l = head_s;
	line_l = head_l;
	while (line_l != NULL)
	{
		data_struct->input = line_l->line;
		data_struct->args  = splitLine(data_struct->input);
		count = execute_line(data_struct);
		free(data_struct->args);
		if (count == 0)
			break;
		move_to_nxt(&sep_l, &line_l, data_struct);
		if (sep_l != NULL)
			sep_l = sep_l->next;
		if (line_l != NULL)
			line_l = line_l->next;
	}
	freeSepList(&head_s);
	freeLineList(&head_l);
	if (count == 0)
	return (0);
	return (1);
}
