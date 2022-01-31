/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lschwart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:52:42 by lschwart          #+#    #+#             */
/*   Updated: 2021/10/10 13:52:49 by lschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	client_action(int sig)
{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	mt_kill(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(300);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_putstr_fd("Successfull launch\nPlease add the message to send\n", 1);
		exit(1);
	}
	if (argc == 1)
	{
		ft_putstr_fd("No PID is inserted. Insert the PID", 1);
		exit(1);
	}
	ft_putstr_fd("Sent: ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, client_action);
	signal(SIGUSR2, client_action);
	mt_kill(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
