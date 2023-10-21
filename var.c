#include "main.h"
/**
 * check_env - function that checks environment variable
 * @h: linked list head
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, x, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (x = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, x, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[x] == _envr[row][chr])
				x++;
			else
				break;
		}
	}
	for (x = 0; in[x]; x++)
	{
		if (in[x] == ' ' || in[x] == '\t' || in[x] == ';' || in[x] == '\n')
			break;
	}
	add_rvar_node(h, x, NULL, 0);
}
/**
 * check_vars - function  that check if variable is $$ or $?
 * @h: linked list head
 * @in: input string
 * @st: last shell status
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int x, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				add_rvar_node(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), x++;
			else if (in[x + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + x, data);
		}
	}
	return (x);
}
/**
 * replaced_input - function that changes string
 * @head: linked list heaad
 * @input: input string
 * @new_input: new input string
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *index;
	int x, y, z;

	index = *head;
	for (y = x = 0; x < nlen; x++)
	{
		if (input[y] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[x] = input[y];
				y++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (z = 0; z < index->len_var; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < index->len_val; z++)
				{
					new_input[x] = index->val[z];
					x++;
				}
				y += (index->len_var);
				x--;
			}
			index = index->next;
		}
		else
		{
			new_input[x] = input[y];
			y++;
		}
	}
	return (new_input);
}
/**
 * rep_var - function to replace string to vars
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *index;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;
	olen = check_vars(&head, input, status, datash);
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	index = head;
	nlen = 0;
	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}
	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);
	return (new_input);
}
