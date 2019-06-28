/*
** EPITECH PROJECT, 2017
** output.c
** File description:
** print details
*/

#include <stdio.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

void print_arp_header(struct arp_options *arp)
{
    int data_nbr = 41;
    int index = 0;

    for (; index < data_nbr - 9; index++)
        printf("%02x ", arp->eth_frame[index]);
    for (int i = 0; i < 6; i++, index++)
        printf("ff ");
    for (; index < data_nbr; index++)
        printf("%02x ", arp->eth_frame[index]);
    printf("%02hx\n", arp->eth_frame[data_nbr]);
}

void print_arp_spoof_header(struct arp_options *arp, char *mac_str)
{
    int data_nbr = 6;

    for (; data_nbr < 41 - 9; data_nbr++) {
        printf("%02x ", arp->eth_frame[data_nbr]);
    }
    for (int i = 0; mac_str[i] != '\0'; i++) {
        if (mac_str[i] == ':')
            printf(" ");
        else
            printf("%c", mac_str[i]);
    }
    printf(" ");
    data_nbr += 6;
    for (; data_nbr < 41; data_nbr++)
        printf("%02x ", arp->eth_frame[data_nbr]);
    printf("%02x\n", arp->eth_frame[data_nbr]);
}

void print_str_mac(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ':')
            printf(" ");
        else
            printf("%c", str[i]);
    }
    printf(" ");
}