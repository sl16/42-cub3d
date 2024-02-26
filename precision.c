/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:18:57 by aulicna           #+#    #+#             */
/*   Updated: 2024/02/26 16:31:32 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/cub3d.h"

bool	almost_equal(double a, double b, double epsilon)
{
	return (fabs(a - b) < epsilon);
}

bool	almost_less_than(double a, double b, double epsilon)
{
	return (b - a > epsilon);
}

bool	almost_greater_than(double a, double b, double epsilon)
{
	return (a - b > epsilon);
}
