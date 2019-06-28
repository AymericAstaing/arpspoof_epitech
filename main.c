/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

void free_data(struct arp_options* opt)
{
    freeaddrinfo(opt->dest_addrinfo);
    free(opt->eth_frame);
    free(opt->src_mac);
    free(opt->dst_mac);
}

struct arp_options parse_params(char **argv)
{
    struct arp_options arp;

    arp._printBroacast_flag = 0;
    arp._printSpoof_flag = 0;
    if (argv[4] && strcmp(argv[4], PRINT_BROACAST_FLAG) == 0)
        arp._printBroacast_flag = 1;
    if (argv[4] && strcmp(argv[4], PRINT_SPOOF_FLAG) == 0) {
        arp._printSpoof_flag = 1;
        arp.given_mac_adress = string_to_mac(argv[5]);
    }
    arp.eth_frame = malloc(IP_MAXPACKET * sizeof(uint8_t));
    arp.source_ip = malloc(sizeof(char) * (strlen(argv[1])));
    arp.source_ip = argv[1];
    arp.dest_ip = malloc(sizeof(char) * (strlen(argv[2])));
    arp.dest_ip = argv[2];
    arp.iface = malloc(sizeof(char) * (strlen(argv[3])));
    arp.iface = argv[3];
    return (arp);
}

int special_flag_handler(struct arp_options* arp, char **argv)
{
    if (arp->_printBroacast_flag) {
        print_arp_header(arp);
        return (SUCCESS);
    }
    if (arp->_printSpoof_flag) {
        print_str_mac(argv[5]);
        print_arp_spoof_header(arp, argv[5]);
        return (SUCCESS);
    }
    return (ERROR);
}

int main(int argc, char **argv)
{
    struct arp_options arp;

    if (argc < 4)
        return (EXIT_ERR);
    arp = parse_params(argv);
    if (!arp.eth_frame || !arp.source_ip || !arp.dest_ip || !arp.iface)
        return (EXIT_ERR);
    if (proceed_initialisation(&arp) == ERROR) {
        printf("Init error...");
        return (EXIT_ERR);
    }
    if (special_flag_handler(&arp, argv) == SUCCESS)
        return (EXIT_SUCC);
    if (get_mac_victim(&arp) == ERROR)
        return (EXIT_ERR);
    if (start_spoofing(&arp) == ERROR)
        return (EXIT_ERR);
    free_data(&arp);
    return (EXIT_SUCC);
}