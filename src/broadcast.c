/*
** EPITECH PROJECT, 2017
** Broacast.c
** File description:
** broadcast functions
*/

#include <stdio.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

int send_mac_request(struct arp_options *arp)
{
    int sd = 0;

    sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sd < 0) {
        printf("Socket error...");
        return (ERROR);
    }
    if (sendto(sd, arp->eth_frame, arp->frame_length, 0,
    (struct sockaddr *) &arp->device_info,
    sizeof(arp->device_info)) < 1) {
        printf("Send fail...");
        return(ERROR);
    }
    close(sd);
    return (SUCCESS);
}