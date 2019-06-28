/*
** EPITECH PROJECT, 2017
** utlis.c
** File description:
** utils functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

uint8_t *string_to_mac(char *mac_str)
{
    uint8_t *mac = malloc(sizeof(uint8_t) * 6);
    int values[6];
    int i = 0;

    if (sscanf(mac_str, "%x:%x:%x:%x:%x:%x%*c",
    &values[0], &values[1], &values[2],
    &values[3], &values[4], &values[5]) != 6) {
        printf("Invalid mac adress.");
        return (NULL);
    }
    for (i = 0; i < 6; i++)
        mac[i] = (uint8_t) values[i];
    return (mac);
}