/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:22:52 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 18:41:10 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	process_store_search(t_reader *reader, t_node **list, t_arena *arena, t_pool **pool)
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
				if (list_add(list, key, arena_strdup(arena, line), pool) < 0)
					return (-1);
				key = NULL;
				state = WAITING_KEY;
			}
		}
		else if (state == SEARCHING)
		{
			char	*value;

			value = list_find(*list, line);
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
	t_node		*list;
	t_arena		arena;
	t_pool		*pool;
	int			ret;

	list = NULL;
	pool = NULL;
	if (reader_init(&reader) < 0)
		return (write(2, "Error on reader_init\n", 21));
	if (arena_init(&arena) < 0)
	{
		reader_free(&reader);
		return (write(2, "Error on arena_init\n", 21));
	}
	ret = process_store_search(&reader, &list, &arena, &pool);
	if (out_flush() < 0)
		ret = -1;
	reader_free(&reader);
	list_free(list);
	pool_free(pool);
	arena_free(&arena);
	if (ret < 0)
		return (write(2, "Error\n", 6));
	return (0);
}
