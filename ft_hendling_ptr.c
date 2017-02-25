/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hendling_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 21:32:52 by ochayche          #+#    #+#             */
/*   Updated: 2017/02/24 21:32:52 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static char				ft_strlen_ptr(t_list *lst, intmax_t digit)
{
	char	res;
	char	tmp;
	intmax_t digit_tmp;
	
	digit_tmp = digit;
	res = 1;
	tmp = 0;
	digit_tmp /= 16;
	while (digit_tmp)
	{
		digit_tmp /= 16;
		res++;
	}
	if (lst->precision != -1 && lst->precision > res)
	{
		tmp = (lst->precision - res);
		res = lst->precision;
	}
	if (digit != 0)
		res += 2;
	if (tmp > 0)
		lst->precision = tmp;
	else if (digit == 0 && lst->precision == 0)
	{
		lst->precision = -2;
		res = 2;
	}
	else
		lst->precision = -1;
	return (res);
}


static char			ft_print_ptr(uintmax_t digit, t_list *lst, char *base)
{
	char len;

	len = 0;
	

	if (digit == 0 && lst->precision == -2)
		return (0);

	if (digit >= 16)
	{
		len += ft_print_ptr(digit / 16, lst, base);
		len += ft_print_char(base[digit % 16]);
	}
	else
		len += ft_print_char(base[digit % 16]);
	return (len);
}





static short ft_hend_ptr(t_list *lst, uintmax_t digit)
{
	short len;

	len = 0;
	if ((lst->flags)[2] == '0' && lst->precision == -1)
		(lst->flags)[0] = '0';

	lst->size = ft_strlen_ptr(lst, digit);
	printf("size precision (%d)\n", lst->precision);
	printf("size size (%d)\n", lst->size);
	printf("size width (%d)\n", lst->width);


	if (lst->flags[0] == '0')// &&  digit != 0)
		len += ft_print_str("0x", -1);



	while ((lst->flags)[3] != '-' && lst->width > (lst->size))
		(len += ft_print_char((lst->flags)[0])) && lst->width--;



	if (lst->flags[0] == ' ')// && digit != 0)
		len += ft_print_str("0x", -1);
	while (lst->precision != -1 && lst->precision > 0)								//precision
		(len += ft_print_char('0')) && lst->precision--;
	len += ft_print_ptr(digit, lst, "0123456789abcdef");


	while (lst->width > lst->size && (lst->flags)[3] == '-')
		(len += ft_print_char(' ')) && lst->width--;
	return (len);
}
























int			ft_hendling_ptr(t_list *lst, void *digit)
{
	return (ft_hend_ptr(lst, (uintmax_t)digit));
}