/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:02:30 by emtemir           #+#    #+#             */
/*   Updated: 2023/09/04 21:04:28 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*  ******SİNYAL İŞLEME********
İşlem başladığında, i, c, ve pid değişkenleri sıfırlanır ve istemci PID'si (info->si_pid) kontrol edilir. 
Eğer daha önce işlem yapılan bir istemciyle aynı değilse, tüm değişkenler sıfırlanır ve yeni istemci PID'si saklanır.
mysig değeri SIGUSR1 sinyalinden çıkarılır. Eğer mysig SIGUSR1 ile aynıysa, sonuç 0 olur; aksi takdirde sonuç 1 olur.
c, mysig değerini bir sola kaydırır (c << 1) ve ardından mysig değerini OR işlemi ile (|) ekler. 
Bu, gelen bitleri irleştirerek karakter oluşturur.
i değişkeni, işlenen bit sayısını takip eder. Her mysig işlendiğinde i bir artırılır.
i 8 olduğunda, yani 8 bit işlendiğinde, oluşturulan karakterin son hali c olarak kontrol edilir.
 Eğer bu karakter NULL karakterse ('\0'), sunucu mesajın tamamlandığını
belirtmek için ilgili istemciye (info->si_pid) SIGUSR1 sinyal
i gönderir ve c ekrana yazdırılmaz. Aksi takdirde, c karakteri ekrana yazdırılır, i ve c sıfırlanır, ve pid sıfırlanır.
Son olarak, işlenen istemcinin PID'si (info->si_pid) saklanır.

*/

static void	my_handler(int mysig, siginfo_t *info, void *context)
{
    static int i;        // Karakteri oluşturmak için kullanılan bit sayacı
    static char c;       // Alınan bitleri birleştirmek için kullanılan karakter
    static int pid;      // İstemci PID'sini saklayan değişken

    (void)context; // Bağlam (context) kullanılmayacak, bu nedenle uyarıyı engelle

    // Eğer gönderen istemcinin kimliği (PID) önceden saklanmış PID ile eşleşmiyorsa,
    // karakter ve sayacı sıfırlar, yeni istemci PID'sini saklar.
    if (pid != info->si_pid)
    {
        c = 0;
        i = 0;
        pid = 0;
    }   
    // Alınan sinyali SIGUSR1'den çıkarır. Eğer mysig SIGUSR1 ile aynıysa sonuç 0 olur,
    // aksi takdirde sonuç 1 olur.
    mysig -= SIGUSR1;

    // Karakteri bir sola kaydırır ve OR işlemi uygular, yeni biti ekler.
    c = c << 1 | mysig;
    i++;

    // 8 bit alındığında karakter tamamlandığında
    if (i == 8)
    {
        // Eğer karakter NULL karakterse (bitleri tamamladığımızda),
        // istemciye mesaj alındığını belirtmek için SIGUSR1 sinyali gönderir.
        if (c == '\0')
            kill(info->si_pid, SIGUSR1);
        // Karakteri ekrana yazdırır.
        ft_putchar(c);
        i = 0;
        c = 0;
        pid = 0;
    }

    // İstemci PID'sini saklar.
    pid = info->si_pid;
}

int main()
{
    struct sigaction signal; // Sinyal işleyici için yapı
    int signal_return;      // sigaction işleminin dönüş değeri

    // Sinyal işleyici işlevini ayarlar
    signal.sa_sigaction = &my_handler;
    signal.sa_flags = SA_SIGINFO;

    // SIGUSR1 ve SIGUSR2 sinyallerini işler
    signal_return = sigaction(SIGUSR1, &signal, NULL);
    if (signal_return == -1)
        exit(1);
    signal_return = sigaction(SIGUSR2, &signal, NULL);
    if (signal_return == -1)
        exit(1);
    
    // Sunucu PID'sini ekrana yazdırır
    ft_putstr("SERVER ID-> ");
    ft_putnbr(getpid());
    ft_putchar('\n');

    // Sonsuz bir döngüde sinyal işleme işlevini bekler
    while (1)
    {
        sleep(1);
    } 
}
