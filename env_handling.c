#include "shell.h"

/**
 * get_environ - Returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: The string array copy of the environ
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = convert_env_list_to_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t **head = &(info->env);
	list_t *current = *head;
	size_t i = 0;
	char *p;

	if (!current || !var)
		return (0);

	while (current)
	{
		p = starts_with(current->str, var);
		if (p && *p == '=')
		{
			delete_node_at_index(head, i);
			info->env_changed = 1;
			i = 0;
			current = *head;
			continue;
		}
		current = current->next;
		i++;
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string env var property
 * @value: The string env var value
 *
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *new_env_var = NULL;
	list_t *current = info->env;
	char *p;

	if (!var || !value)
		return (0);

	new_env_var = malloc(_strlen(var) + _strlen(value) + 2);
	if (!new_env_var)
		return (1);

	_strcpy(new_env_var, var);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);

	while (current)
	{
		p = starts_with(current->str, var);
		if (p && *p == '=')
		{
			free(current->str);
			current->str = new_env_var;
			info->env_changed = 1;
			return (0);
		}
		current = current->next;
	}

	add_node_end(&(info->env), new_env_var, 0);
	info->env_changed = 1;

	return (0);
}
