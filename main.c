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

static int	store_pairs(t_reader *reader, t_hashtable *ht)
{
	char	*line;
	char	*key;
	int		ret;

	ret = reader_next(reader, &line);
	while (ret == 1 && line[0] != '\0')
	{
		key = ft_strdup(line);
		if (!key)
			return (-1);
		ret = reader_next(reader, &line);
		if (ret != 1)
		{
			free(key);
			return (ret);
		}
		if (list_add(ht, key, ft_strdup(line)) < 0)
			return (-1);
		ret = reader_next(reader, &line);
	}
	return (ret);
}

static int	search_keys(t_reader *reader, t_hashtable *ht)
{
	char	*line;
	char	*value;
	int		ret;

	ret = reader_next(reader, &line);
	while (ret == 1)
	{
		value = list_find(ht, line);
		if (value && (out_str(value) < 0 || out_str("\n") < 0))
			return (-1);
		if (!value && (out_str(line) < 0 || out_str(": Not found.\n") < 0))
			return (-1);
		ret = reader_next(reader, &line);
	}
	return (ret);
}

int	main(void)
{
	t_reader	reader;
	t_hashtable	ht;
	int			ret;
	size_t		i;

	i = 0;
	while (i < HASH_SIZE)
	{
		ht.buckets[i] = NULL;
		i++;
	}
	if (reader_init(&reader) < 0)
		return (write(2, "Error on reader_init\n", 21));
	ret = store_pairs(&reader, &ht);
	if (ret == 1)
		ret = search_keys(&reader, &ht);
	if (out_flush() < 0)
		ret = -1;
	reader_free(&reader);
	list_free(&ht);
	if (ret < 0)
		return (write(2, "Error\n", 6));
	return (0);
}
