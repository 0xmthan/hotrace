/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:32:11 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 18:18:09 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	arena_init(t_arena *arena)
{
	t_arena_chunk	*chunk;

	chunk = malloc(sizeof(t_arena_chunk));
	if (!chunk)
		return (-1);
	chunk->buf = malloc(ARENA_CHUNK_SIZE);
	if (!chunk->buf)
	{
		free(chunk);
		return (-1);
	}
	chunk->next = NULL;
	arena->chunks = chunk;
	arena->current = chunk;
	arena->offset = 0;
	return (0);
}

char	*arena_strdup(t_arena *arena, const char *s)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s) + 1;
	if (arena->offset + len > ARENA_CHUNK_SIZE)
	{
		t_arena_chunk	*new_chunk;

		new_chunk = malloc(sizeof(t_arena_chunk));
		if (!new_chunk)
			return (NULL);
		new_chunk->buf = malloc(ARENA_CHUNK_SIZE);
		if (!new_chunk->buf)
		{
			free(new_chunk);
			return (NULL);
		}
		new_chunk->next = NULL;
		arena->current->next = new_chunk;
		arena->current = new_chunk;
		arena->offset = 0;
	}
	result = arena->current->buf + arena->offset;
	ft_memmove(result, s, len);
	arena->offset += len;
	return (result);
}

void	arena_free(t_arena *arena)
{
	t_arena_chunk	*chunk;
	t_arena_chunk	*next;

	chunk = arena->chunks;
	while (chunk)
	{
		next = chunk->next;
		free(chunk->buf);
		free(chunk);
		chunk = next;
	}
	arena->chunks = NULL;
	arena->current = NULL;
	arena->offset = 0;
}

void	ft_memmove(char *dst, const char *src, size_t n)
{
	size_t	i;

	if (dst == src || n == 0)
		return ;
	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
		return ;
	}
	while (n > 0)
	{
		n--;
		dst[n] = src[n];
	}
}

char	*ft_memchr(char *s, char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memmove(dup, s, len + 1);
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	djb2_hash(const char *str)
{
	size_t	hash;
	int		c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash & (HASH_SIZE - 1));
}
