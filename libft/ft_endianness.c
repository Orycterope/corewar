#include "libft.h"

int			ft_write_big_endian(long long n, void *dst, size_t lenght)
{
	size_t	i;
	char	*dest;

	if (lenght == 0)
		return (0);
	dest = (char *)(dst + lenght - 1);
	i = 0;
	while (i < lenght && n != 0)
	{
		*dest-- = (n & 0xFF);
		n >>= 8;
		i++;
	}
	return (i);
}

long long	ft_read_big_endian(void *src, size_t length)
{
	long long	n;
	long long	power;
	char		*ptr;

	n = 0;
	power = 1;
	ptr = (char *)src;
	while (length > 0)
	{
		n += ((long long)ptr[length - 1]) * power;
		power <<= 8;
		length--;
	}
	return (n);
}


