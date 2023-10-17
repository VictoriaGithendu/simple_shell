#include "main.h"
/**
 * check_env_alt - checks if the input string is an env variable
 * @var_list: head of linked list
 * @input_str: input string to check
 * @data_struct: data structure
 * Return: no return
 */
void check_env_alt(r_var **var_list, char *input_str, data_shell *data_struct)
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
				length = strLength(env_variables[x] + y + 1);
				addVarNode(var_list, z, env_variables[x] + y + 1, length);
				return;
			}
			if (input_str[z] == env_variables[x][y])
				z++;
			else
				break;
		}
	}
	for (z = 0; input_str[z]; z++)
	{
		if (input_str[z] == ' ' || input_str[z] == '\t' ||
				input_str[z] == ';' || input_str[z] == '\n')
			break;
	}
	addVarNode(var_list, z, NULL, 0);
}
/**
 * find_var - check if the input string contains $$ or $?
 * @var_l: head of the linked list to store results
 * @input_s: input string to check
 * @stat: last status of the Shell
 * @data_struct: data structure
 * Return: no return
 */
int find_var(r_var **var_l, char *input_s, char *stat, data_shell *data_struct)
{
	int x;
	int length_status = strLength(stat);
	int length_pid = strLength(data_struct->pid);

	while (input_s[x])
	{
		if (input_s[x] == '$')
		{
			if (input_s[x + 1] == '?')
				addVarNode(var_l, 2, stat, length_status), x++;
			else if (input_s[x + 1] == '$')
				addVarNode(var_l, 2, data_struct->pid, length_pid), x++;
			else if (input_s[x + 1] == '\n' || input_s[x + 1] == '\0' ||
			input_s[x + 1] == 't' || input_s[x + 1] == ';')
				addVarNode(var_l, 0, NULL, 0);
			else
				check_env_alt(var_l, input_s + x, data_struct);
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
	r_var *current;
	int x, y, z;
	current = *var_l;
	
	for (x = y = 0;  x < new_length; x++)
		if (input_s[y] == '$')
		{
			if(!(current->len_var) && !(current->len_val))
				{
					new_input[x] = input_s[y];
					y++;
				}
			y += (current->len_var);
			x--;
		}
	current = current->next;
	{
		new_input[x] = input_s[y];
		y++;
	}
	return (new_input);
}
/**
 * rep_str_var - replaces variables in the input string
 * @input_str: input string
 * @data_struct: data structure
 * Return: replaced string
 */
char *rep_str_var(char *input_str, data_shell *data_struct)
{
	r_var *var_list;
	char *status_str = iToA(data_struct->status);
	int origin_length = find_var(&var_list, input_str, status_str, data_struct);
	int new_length = 0;
	char *new_input;

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
	new_input = rep_var(&var_list, input_str, new_input, new_length);

	free(input_str);
	free(status_str);
	freeVarList(&var_list);

	return (new_input);
}
