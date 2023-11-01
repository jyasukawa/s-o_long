#include "so_long.h"

static void	ft_putchar(int c)
{
	write(1, &c, 1);
}

static void	ft_putunsigned_count(size_t n)
{
	if (n >= 10)
		ft_putunsigned_count(n / 10);
	ft_putchar((n % 10 + '0'));
}

static void	ft_check_format(char c, va_list *ap, size_t *i)
{
	if (c == 'n')
		ft_putunsigned_count(va_arg(*ap, size_t));
	else
		(*i)--;
}

void	ft_printf_n(const char *format, ...)
{
	va_list	ap;
	size_t	i;

	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_check_format(format[i], &ap, &i);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			i++;
		}
	}
	va_end(ap);
}
