#ifndef HOTRACE_H
#define HOTRACE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

// read syscall için kritik performans
#define READ_BUFFER_SIZE 65536 // 64 KB

size_t	ft_strlen(const char *str);
void	ft_putendl(const char *str);
bool	ft_strcmp(const char* s1, const char* s2);
#endif