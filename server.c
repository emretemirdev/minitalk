/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:02:30 by emtemir           #+#    #+#             */
/*   Updated: 2023/09/02 19:16:58 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	my_handler(int mysig, siginfo_t *info, void *context)
{
    static  int     i;
    static  char    c;
    static  int     pid;

    (void)context;
     // Gönderen istemcinin kimliği (PID) önceden saklanmış PID ile eşleşmiyorsa,
    // karakter ve sayaç sıfırlanır ve yeni istemci PID'si saklanır.

    if(pid != info->si_pid)
    {
        c = 0;
        i = 0;
        pid = 0;
    }   
    
    mysig -= SIGUSR1; //eğer  mysig SIGUSR1 ile aynıysa sonuç 0 olur,
    //aksi takdirde sonuç 1 olur;

    c = c << 1 | mysig; //karakteri bir sola kaydırır ve OR işlemi uygular.
    i++;
    if(i == 8)
    {
        if(c == '\0')
                kill(info->si_pid, SIGUSR1);
        ft_putchar(c);
        i = 0;
        c = 0;
        pid = 0;

    }
    pid = info ->si_pid;
}

int main()
{
    struct sigaction       signal;
    int                    signal_return;
    
    signal.sa_sigaction = &my_handler;
    signal.sa_flags = SA_SIGINFO;
    
    signal_return = sigaction(SIGUSR1, &signal, NULL);
    if (signal_return == -1)
        exit(1);
    signal_return = sigaction(SIGUSR2, &signal, NULL);
    if (signal_return == -1)
        exit(1);
    ft_putstr("SERVER ID-> ");
    ft_putnbr(getpid());
    ft_putchar('\n');
    while (1)
    {
        sleep(1);
    } 
}