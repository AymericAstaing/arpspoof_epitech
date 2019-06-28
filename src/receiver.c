/*
** EPITECH PROJECT, 2017
** Receiver.c
** File description:
** receiver 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <errno.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

int intercept_answer(uint8_t *eth_frame, int sd, struct arp_options *arp)
{
    if (recv(sd, eth_frame, IP_MAXPACKET, 0) < 0)
        return (ERROR);
    if (read(sd, eth_frame, IP_MAXPACKET) < 0)
        return (ERROR);
    for (int i = 6; i < 11; i++)
        arp->victim.dest_mac[i - 6] = eth_frame[i];
    arp->victim.dest_mac[5] = eth_frame[11];
    close (sd);
    free (eth_frame);
    return (SUCCESS);
}

int get_mac_victim(struct arp_options *arp)
{
    int sd = 0;
    uint8_t *eth_frame;

    eth_frame = malloc(sizeof(uint8_t) * IP_MAXPACKET);
    memset(eth_frame, 0, sizeof(uint8_t) * IP_MAXPACKET);
    sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sd < 0) {
        printf("Socket errror %d.", sd);
        return (EXIT_ERR);
    }
    while (1) {
        if (send_mac_request(arp) == ERROR)
            return (ERROR);
        if (intercept_answer(eth_frame, sd, arp) == SUCCESS)
            return (SUCCESS);
    }
    return (SUCCESS);
}