/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:02:28 by emtemir           #+#    #+#             */
/*   Updated: 2023/09/04 18:41:38 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	message_recieved(int a)
{
	(void)a;
	ft_putstr("***********************************************\n");
	ft_putstr("* 👨‍💻*--👾 MESAJ BAŞARIYLA GÖNDERİLİDİ💪🏻 👾--*👨‍💻 *\n");
	ft_putstr("***********************************************\n");
}

static void	send_byte_to_server(char byte, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (byte >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(300);
		i--;
	}
}

int	main(int ac, char *av[])
{
	char	*str;
	pid_t	pid;

	signal(SIGUSR1, message_recieved); // to detect if the message has been sent. if yes message_recieved get print on client screen
	
	if (ac != 3)
	{
		ft_putstr("Client iki argüman alır:   \n -PID(serverdan gelecek).\n -Gönderilecek Mesaj. \n");
		exit(1);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
	while (*str)
	{
		send_byte_to_server(*str, pid);
		str++;
	}
	send_byte_to_server(0, pid);
    
	return (0);
}