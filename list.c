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

int	list_add(t_hashtable *ht, char *key, char *value, t_pool **pool)
{
	t_node	*node;
	size_t	index;

	node = pool_alloc(pool);
	if (!node || !value)
	{
		free(key);
		return (-1);
	}
	node->key = key;
	node->value = value;
	index = djb2_hash(key);
	node->next = ht->buckets[index];
	ht->buckets[index] = node;
	return (0);
}

char	*list_find(t_hashtable *ht, const char *key)
{
	t_node	*node;
	size_t	index;

	index = djb2_hash(key);
	node = ht->buckets[index];
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

void	list_free(t_hashtable *ht)
{
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		ht->buckets[i] = NULL;
		i++;
	}
}
