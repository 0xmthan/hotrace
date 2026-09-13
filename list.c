/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:53:09 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 18:34:54 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	list_add(t_node **list, char *key, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node || !value)
	{
		free(node);
		free(key);
		free(value);
		return (-1);
	}
	node->key = key;
	node->value = value;
	node->next = *list;
	*list = node;
	return (0);
}

char	*list_find(t_node *list, const char *key)
{
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

void	list_free(t_node *list)
{
	t_node	*next;

	while (list)
	{
		next = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = next;
	}
}
