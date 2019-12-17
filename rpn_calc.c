/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcabrol <mcabrol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:04:17 by mcabrol           #+#    #+#             */
/*   Updated: 2019/12/17 17:14:47 by mcabrol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF	100

int 	op(char operator, int a, int b)
{
	if (operator == '+')
		return (a + b);
	else if (operator == '-')
		return (a - b);
	else if (operator == '*')
		return (a * b);
	else if (operator == '/')
		return (a / b);
	else if (operator == '%')
		return (a % b);
	else
		return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int		is_opt(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int		rpn_calc(char *expr)
{
	int 	stack[BUFF];
	int 	nb;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (expr[++i])
		if (is_num(expr[i]))
		{
			stack[j] = atoi(expr + i);
			j++;
			while (is_num(expr[i]))
				i++;
		}
		else if (is_opt(expr[i]))
		{
			j--;
			stack[j - 1] = op(expr[i], stack[j - 1], stack[j]);
		}
	return (stack[0]);
}

int		check(char *expr)
{
	if (!is_num(expr[0]) || !is_opt(expr[ft_strlen(expr) - 1]))
		return (1);
	while (*expr)
	{
		if (!is_num(*expr) && !is_opt(*expr) && *expr != ' ')
			return (1);
		if (*expr == ' ' && *(expr + 1) == ' ')
			return (1);
		expr++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac != 2 || check(av[1]))
		printf("Error\n");
	else
		printf("%d\n", rpn_calc(av[1]));
	return (0);
}
