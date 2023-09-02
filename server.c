/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:02:30 by emtemir           #+#    #+#             */
/*   Updated: 2023/09/02 14:24:15 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Server received data from client.\n");
    } else if (signum == SIGUSR2) {
        printf("Server received data but will process it quickly.\n");
    } else {
        printf("Unknown signal received.\n");
    }
}

int main() {
    pid_t server_pid = getpid();
    printf("Server PID: %d\n", server_pid);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        sleep(1);
    }

    return 0;
}
