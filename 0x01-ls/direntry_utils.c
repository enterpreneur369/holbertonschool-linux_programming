#include "hls.h"

/**
 * get_direntres - gets the list of the Direntres with specified value
 * @str: The value of the Direntry to be searched.
 * @en: The Direntry where the value are to be looked in.
 *
 * Return: on success: List of of the Direntres, on Failure: NULL
 */
Direntry *get_direntres(char *str, Direntry *en)
{
	Direntry *result = NULL, *temp = NULL;
	int index = 0;

	while (en != NULL)
	{
		if (_strncmp(en->str, str, _strlen(str)) == 0)
		{
			if (_strchr(str, '/') == NULL)
				index = _strlen(str);
			else
				index = _strlen(str) + 1;
			if (_strchr(en->str + index, '/') == NULL)
			{
				if (temp == NULL)
				{
					result = malloc(sizeof(Direntry));
					temp = result;
				}
				else
				{
					temp->next = malloc(sizeof(Direntry));
					temp = temp->next;
				}
				temp->str = _strdup(en->str);
				temp->next = NULL;
			}
		}
		en = en->next;
	}
	return (result);
}


/**
 * get_files - gets the list of the Direntres which are files in params
 * @diren: The Direntry where the value are to be looked in.
 * @params: THe list of params
 * Return: on success: List of of the Direntres, on Failure: NULL
 */
Direntry *get_files(Direntry *diren, List *params)
{
	Direntry *result = NULL, *temp = NULL, *en =  NULL;
	int i = 0;

	for (i = 0 ; get_node(params, i); i++)
	{
		en = diren;
		while (en != NULL)
		{
			if (_strcmp(en->str, get_node(params, i)) == 0 && !is_directory(en->str))
			{
				if (temp == NULL)
				{
					result = malloc(sizeof(Direntry));
					temp = result;
				}
				else
				{
					temp->next = malloc(sizeof(Direntry));
					temp = temp->next;
				}
				temp->str = _strdup(en->str);
				temp->next = NULL;
				break;
			}
			en = en->next;
		}
	}
	return (result);
}
/**
 * deleteDirent - Deletes the Direntry with a specified value
 * @head_ref: The List where the value are to be deleted.
 * @key: The value of the node to be deleted.
 *
 * Return: void
 */
void deleteDirent(Direntry **head_ref, char *key)
{
	Direntry *temp = *head_ref, *prev;

	if (temp != NULL && _strcmp(temp->str, key) == 0)
		{
		*head_ref = temp->next;
		free(temp->str);
		free(temp);
		return;
	}
	while (temp != NULL && _strcmp(temp->str, key) != 0)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL)
		return;
	prev->next = temp->next;
	free(temp->str);
	free(temp);
}

/**
 * removeDuplicates - removes duplicate the Direntry with a specified value
 * @head: The List where the value are to be deleted.
 *
 * Return: void
 */
void removeDuplicates(Direntry *head)
{
	Direntry *temp;

	while (head != NULL)
	{
		if (head->next != NULL)
		{
			while (head->next != NULL && _strcmp(head->next->str, head->str) == 0)
			{
				temp = head->next;
				head->next = temp->next;
				free(temp->str);
				free(temp);
			}
		}
		head = head->next;
	}
}
