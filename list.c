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

int	list_add(t_hashtable *ht, char *key, char *value)
{
	t_node	*node;
	size_t	index;

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
	t_node	*node;
	t_node	*next;
	size_t	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		node = ht->buckets[i];
		while (node)
		{
			next = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = next;
		}
		ht->buckets[i] = NULL;
		i++;
	}
}
