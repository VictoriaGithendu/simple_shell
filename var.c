#include "main.h"
/**
 * check_env_alt - checks if the input string is an env variable
 * @var_list: head of linked list
 * @input_str: input string to check
 * @data_struct: data structure
 * Return: no return
 */
void check_env_alt(r_var **var_list, char *input_str, shell *data_struct)
{
	int x, y, z, length;
	char **env_variables;

	env_variables = data_struct->_environ;
	for (x = 0; env_variables[x]; x++)
	{
		for (z = 1, y = 0; env_variables[x][y]; y++)
		{
			if (env_variables[x][y] == '=')
			{
				length = _strlen(env_variables[x] + y + 1);
				add_rvar_node(var_list, z, env_variables[x] + y + 1, length);
				return;
			}
			if (in[z] == env_variables[x][y])
				z++;
			else
				break;
		}
	}
	for (z = 0; in[z]; z++)
	{
		if (in[z] == ' ' || in[z] == '\t' || in[z] == ';' || in[z] == '\n')
			break;
	}
	add_rvar_node(var_list, z, NULL, 0);
}
/**
 * check_var_alt - check if the input string contains $$ or $?
 * @var_l: head of the linked list to store results
 * @input_s: input string to check
 * @stat: last status of the Shell
 * @data_struct: data structure
 * Return: no return
 */
int check_var_alt(r_var **var_l, char *input_s, char *stat, shell *data_struct)
{
	int x;
	int length_status = _strlen(status);
	int length_pid = _strlen(data_struct->pid);

	while (input_s[x])
	{
		if (input_s[x] == '$')
		{
			if (input_s[x + 1] == '?')
				add_rvar_node(var_l, 2, stat, length_status), x++;
			else if (input_s[x + 1] == '$')
				add_rvar_node(var_l, 2, data_struct->pid, length_pid), x++;
			else if (input_s[x + 1] == '\n' || input_s[x + 1] == '\0' ||
			input_s[x + 1] == 't' || input_s[x + 1] == ';')
				add_rvar_node(var_list, 0, NULL, 0);
			else
				check_env_alt(va_list, input_s + x, data_struct);
		}
	}
	return (x);
}
/**
 * rep_var - replaces variables in the input string
 * @var_l: head of the linked list
 * @input_s: input string
 * @new_input: new input string (replaced)
 * @new_length: new  string length
 * Return: replaced string
 */
char *rep_var(r_var **var_l, char *input_s, char *new_input, int new_length)
{
	r_var *current = *var_l;
	int x, y, z = 0;

	while (x < new_length)
	{
		if (input_s[y] == '$' && current != NULL)
		{
			if (current->type == 1)
			{
				for (z = 0; z < current->len_val; y++)
					new_input[x] = ((char *)current->value)[z]);
				x++;
			}
			y += current->len_var;
			else
			{
					new_input[x] = input_s[y];
					x++;
			}
			current = current->next;
		}
		else
		{
			new_input[x] = input_s[y];
			y++;
		}
	}
	return (new_input);
}
/**
 * rep_str_var - replaces variables in the input string
 * @input_str: input string
 * @data_struct: data structure
 * Return: replaced string
 */
char *rep_str_var(char *input_str, shell *data_struct)
{
	r_var *var_list;
	char *status_str = aux_itoa(data_struct->status);
	int origin_length = check_vars(&var_list, input_str, status_str, data_struct);
	int new_length = 0;
	char new_input;

	if (var_list == NULL)
	{
		free(status_str);
		return (input_str);
	}
	r_var *current = var_list;

	while (current != NULL)
	{
		new_length += (current->len_val - current->len_var);
		current = current->next;
	}
	new_length += origin_length;
	new_input = malloc(sizeof(char) * (new_length + 1));
	new_input[new_length] = '\0';
	new_input = replace_variables(&var_list, input_str, new_input, new_length);

	free(input_str);
	free(status_str);
	free_rvar_list(&var_list);
	return (new_input);
}
