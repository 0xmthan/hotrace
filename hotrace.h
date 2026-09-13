/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 11:00:32 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 18:34:36 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <unistd.h>

# define READ_SIZE 65536
# define OUT_SIZE 65536
# define HASH_SIZE 1024

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_hashtable
{
	t_node	*buckets[HASH_SIZE];
}	t_hashtable;

typedef struct s_reader
{
	char	*buf;
	size_t	cap;
	size_t	start;
	size_t	end;
	int		eof;
}	t_reader;

int				reader_init(t_reader *r);
int				reader_next(t_reader *r, char **line);
void			reader_free(t_reader *r);

int				out_write(const char *s, size_t len);
int				out_str(const char *s);
int				out_flush(void);

int				list_add(t_hashtable *ht, char *key, char *value);
char			*list_find(t_hashtable *ht, const char *key);
void			list_free(t_hashtable *ht);

void			ft_memmove(char *dst, const char *src, size_t n);
char			*ft_memchr(char *s, char c, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
size_t			djb2_hash(const char *str);

#endif
