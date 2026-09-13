/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:22:52 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 21:06:16 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	process_store_search(t_reader *reader, t_hashtable *ht, t_arena *arena, t_pool **pool)
{
	char	*line;
	char	*key;
	t_state	state;
	int		ret;

	state = WAITING_KEY;
	key = NULL;
	ret = reader_next(reader, &line);
	while (ret == 1)
	{
		if (state == WAITING_KEY)
		{
			if (line[0] == '\0')
				state = SEARCHING;
			else
			{
				key = arena_strdup(arena, line);
				if (!key)
					return (-1);
				state = WAITING_VALUE;
			}
		}
		else if (state == WAITING_VALUE)
		{
			if (line[0] == '\0')
			{
				key = NULL;
				state = SEARCHING;
			}
			else
			{
				if (list_add(ht, key, arena_strdup(arena, line), pool) < 0)
					return (-1);
				key = NULL;
				state = WAITING_KEY;
			}
		}
		else if (state == SEARCHING)
		{
			char	*value;

			value = list_find(ht, line);
			if (value && (out_str(value) < 0 || out_str("\n") < 0))
				return (-1);
			if (!value && (out_str(line) < 0 || out_str(": Not found.\n") < 0))
				return (-1);
		}
		ret = reader_next(reader, &line);
	}
	return (ret);
}

int	main(void)
{
	t_reader	reader;
	t_hashtable	*ht;
	t_arena		arena;
	t_pool		*pool;
	int			ret;
	size_t		i;

	ht = malloc(sizeof(t_hashtable));
	if (!ht)
		return (write(2, "Error on hashtable malloc\n", 26));
	i = 0;
	while (i < HASH_SIZE)
	{
		ht->buckets[i] = NULL;
		i++;
	}
	pool = NULL;
	if (reader_init(&reader) < 0)
	{
		free(ht);
		return (write(2, "Error on reader_init\n", 21));
	}
	if (arena_init(&arena) < 0)
	{
		reader_free(&reader);
		free(ht);
		return (write(2, "Error on arena_init\n", 21));
	}
	ret = process_store_search(&reader, ht, &arena, &pool);
	if (out_flush() < 0)
		ret = -1;
	reader_free(&reader);
	list_free(ht);
	pool_free(pool);
	arena_free(&arena);
	free(ht);
	if (ret < 0)
		return (write(2, "Error\n", 6), 1);
	return (0);
}
