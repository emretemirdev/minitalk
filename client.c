/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:02:28 by emtemir           #+#    #+#             */
/*   Updated: 2023/09/02 14:23:51 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void send_signal(pid_t server_pid, const char *message) {
    if (strlen(message) <= 100) {
        kill(server_pid, SIGUSR1);
    } else {
        kill(server_pid, SIGUSR2);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Server PID> <Message>\n", argv[0]);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    const char *message = argv[2];

    send_signal(server_pid, message);
    printf("Sent message to Server: '%s'\n", message);

    return 0;
}
