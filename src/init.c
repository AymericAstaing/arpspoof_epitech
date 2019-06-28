/*
** EPITECH PROJECT, 2017
** init.c
** File description:
** init arp system
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include "../include/arpvariables.h"
#include "../include/arp.h"

int proceed_initialisation(struct arp_options *arp)
{
    if (set_personnal_mac_adress(arp) == ERROR)
        return (ERROR);
    if (set_src_device_info(arp) == ERROR)
        return (ERROR);
    if (set_dest_device_info(arp) == ERROR)
        return (ERROR);
    if (build_arp_header(arp) == ERROR)
        return (ERROR);
    return (SUCCESS);
}

int set_personnal_mac_adress(struct arp_options *arp)
{
    struct ifreq ifr;
    int sd = 0;

    arp->src_mac = malloc(sizeof(uint8_t) * 6);
    if (arp->_printBroacast_flag == 1 ||arp->_printSpoof_flag == 1)
        sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    else
        sd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sd < 0) {
        printf("Socket init error nbr %d.", sd);
        return (ERROR);
    }
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", arp->iface);
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0) {
        printf("Ioctl() info failed.");
        return (ERROR);
    }
    memcpy(arp->src_mac, ifr.ifr_hwaddr.sa_data, 6 * sizeof(uint8_t));
    return (SUCCESS);
}

int set_src_device_info(struct arp_options *arp)
{
    memset(&(arp->device_info), 0, sizeof(arp->device_info));
    arp->device_info.sll_ifindex = if_nametoindex(arp->iface);
    if (arp->device_info.sll_ifindex == 0) {
        printf("Failed to obtain interface index.");
        return (ERROR);
    }
    arp->dst_mac = malloc(sizeof(uint8_t) * 6);
    memset(arp->dst_mac, 0xff, 6 * sizeof (uint8_t));
    memset(&(arp->source_addrinfo), 0, sizeof(struct addrinfo));
    arp->source_addrinfo.ai_family = AF_INET;
    arp->source_addrinfo.ai_socktype = SOCK_STREAM;
    arp->source_addrinfo.ai_flags = arp->source_addrinfo.ai_flags
    | AI_CANONNAME;
    if (inet_pton(AF_INET, arp->source_ip,
    (&(arp->arp_header_s.source_ip))) < 0) {
        printf("Inet_pton() failed for src ip.");
        return (ERROR);
    }
    return (SUCCESS);
}

int set_dest_device_info(struct arp_options *arp)
{
    struct sockaddr_in* ipv_4 = NULL;

    if (getaddrinfo(arp->dest_ip, NULL, &arp->source_addrinfo,
    &(arp->dest_addrinfo)) != 0) {
        printf("Error on get_addrinfo (test device).");
        return (ERROR);
    }
    ipv_4 = (struct sockaddr_in *)arp->dest_addrinfo->ai_addr;
    memcpy(&(arp->arp_header_s.dest_ip),
    &ipv_4->sin_addr, 4 * sizeof (uint8_t));
    arp->device_info.sll_family = AF_PACKET;
    memcpy(arp->device_info.sll_addr, arp->src_mac, 6 * sizeof (uint8_t));
    arp->device_info.sll_halen = 6;
    return (SUCCESS);
}

int build_arp_header(struct arp_options *arp)
{
    arp->arp_header_s.h_type = htons(1);
    arp->arp_header_s.p_type = htons(ETH_P_IP);
    arp->arp_header_s.h_length = 6;
    arp->arp_header_s.p_length = 4;
    if (arp->_printSpoof_flag == 1)
        arp->arp_header_s.op_code = htons(2);
    else
        arp->arp_header_s.op_code = htons(1);
    memcpy(&arp->arp_header_s.source_mac, arp->src_mac, 6 * sizeof (uint8_t));
    memset(&arp->arp_header_s.dest_mac, 0, 6 * sizeof (uint8_t));
    arp->frame_length = 42;
    memcpy(arp->eth_frame, arp->dst_mac, 6 * sizeof (uint8_t));
    memcpy(arp->eth_frame + 6, arp->src_mac, 6 * sizeof (uint8_t));
    arp->eth_frame[12] = ETH_P_ARP / 256;
    arp->eth_frame[13] = ETH_P_ARP % 256;
    memcpy(arp->eth_frame + ETH_HDRLEN,
    &arp->arp_header_s, 28 * sizeof (uint8_t));
    return(SUCCESS);
}