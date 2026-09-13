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

t_pool	*pool_new(void)
{
	t_pool	*pool;

	pool = malloc(sizeof(t_pool));
	if (!pool)
		return (NULL);
	pool->idx = 0;
	pool->next = NULL;
	return (pool);
}

t_node	*pool_alloc(t_pool **pool)
{
	t_pool	*current;

	if (!*pool)
	{
		*pool = pool_new();
		if (!*pool)
			return (NULL);
	}
	current = *pool;
	while (current->idx >= POOL_SIZE && current->next)
		current = current->next;
	if (current->idx >= POOL_SIZE)
	{
		current->next = pool_new();
		if (!current->next)
			return (NULL);
		current = current->next;
	}
	return (&current->nodes[current->idx++]);
}

void	pool_free(t_pool *pool)
{
	t_pool	*next;

	while (pool)
	{
		next = pool->next;
		free(pool);
		pool = next;
	}
}

int	list_add(t_node **list, char *key, char *value, t_pool **pool)
{
	t_node	*node;

	node = pool_alloc(pool);
	if (!node || !value)
	{
		free(key);
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
	(void)list;
}
