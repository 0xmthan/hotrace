#include "hotrace.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putendl(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (write(1, str, len) == -1)
        ft_putendl(strerror(errno));
}

bool    ft_strcmp(const char* s1, const char* s2)
{
    size_t  i;

    if (ft_strlen(s1) != ft_strlen(s2))
        return (false);
    
    i = 0;
    while (s1[i])
    {
        if (s1[i] != s2[i])
            return (false);
        i++;
    }
    return (true);
}
