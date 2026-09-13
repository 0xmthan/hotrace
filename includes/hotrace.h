#ifndef HOTRACE_H
#define HOTRACE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>


// read syscall için kritik performans
// Max Linux pipe kapasitesi ve L1 Cache uyumu (64KB)

#define READ_BUFFER_SIZE 65536 // 64 KB


typedef struct s_item
{
	char			*key;
	char			*value;
	struct s_item	*next;

}	t_item;


// utils
size_t	ft_strlen(const char *str);
void	ft_putendl(const char *str);
bool	ft_strcmp(const char* s1, const char* s2);


#endif