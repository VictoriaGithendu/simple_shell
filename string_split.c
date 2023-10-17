#include "main.h"
/**
 * tokenize_input - function that tokenizes a string input
 * @input: string input to tokenize
 * Return: token array
 */
char **tokenize_input(char *input)
{
	size_t token_size = 64;
	size_t x = 0;
	char **tokens = (char **)malloc(token_size * sizeof(char *));
	char *token;
	if (tokens == NULL)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strTok(input, TOK_DELIM);

	while (token != NULL)
	{
		if (x >= token_size - 1)
		{
			token_size += 64;
			tokens = (char **)realloc(tokens, token_size * sizeof(char *));
			if (tokens == NULL)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		tokens[x++] = token;
		token = strTok(NULL, TOK_DELIM);
	}
	tokens[x] = NULL;
	return (tokens);
}
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
			if (input[x] == '|' && input[x + 1] != '|')
				input[x] = '\x10';
			else if (input[x] == '&' && input[x + 1] != '&')
				input[x] = '\f';
		}
	else
		for (x = 0; input[x]; x++)
		{
			if (input[x] == '\x10')
				input[x] = '|';
			else if (input[x] == '\f')
				input[x] = '&';
		}
	return (input);
}
/**
 * parse_input - parses the input string and creates separator and command line
 * @input: string input
 * @head_s: separator list head
 * @head_l: command line list head
 * Return: 0
 */
void parse_input(char *input, sep_list **head_s, line_list **head_l)
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
	int continue_loop = 1;
	sep_list *sep_node = *sep_l;
	line_list *line_node = *line_l;

	while (sep_node != NULL && continue_loop)
	{
		if (data_struct->status == 0)
			if (sep_node->separator == '&' || sep_node->separator == ';')
				continue_loop = 0;
	}
	if (sep_node->separator == '|')
		line_node = line_node->next;
	sep_node = sep_node->next;
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
/**
 * execute_commands - function that execute command lines separated by ;, |, &
 * @data_struct: relevant data
 * @input: string input
 * Return: 0 on exit, 1 to continue
 */
int execute_commands(data_shell *data_struct, char *input)
{
	sep_list *sep, *sep_node = NULL;
	line_list *line, *line_node = NULL;
	int count;

	parse_input(input, &sep, &line);
	while (line_node)
	{
		data_struct->input = line_node->line;
		data_struct->args  = tokenize_input(data_struct->input);
		count = execute_line(data_struct);
		free(data_struct->args);
		if (count == 0)
			break;
		move_to_nxt(&sep_node, &line_node, data_struct);
		if (line_node)
			line_node = line_node->next;
	}
	freeSepList(&sep);
	freeLineList(&line);
	return (count ? 1 : 0);
}
