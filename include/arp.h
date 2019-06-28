/*
** EPITECH PROJECT, 2017
** arp.h
** File description:
** arp_header
*/

#ifndef ARP_H_
#define ARP_H_

#include <stdint.h>
#include <netdb.h>
#include <linux/if_packet.h>

struct arp_header {
    uint16_t h_type;
    uint16_t p_type;
    uint8_t h_length;
    uint8_t p_length;
    uint16_t op_code;
    uint8_t source_mac[6];
    uint8_t source_ip[4];
    uint8_t dest_mac[6];
    uint8_t dest_ip[4];
};

struct victim {
    uint8_t             dest_mac[6];
    char                *str_dst_mac;
};

struct arp_options {
    int                 _printBroacast_flag;
    int                 _printSpoof_flag;
    char                *source_ip;
    char                *dest_ip;
    uint8_t             *given_mac_adress;
    uint8_t             *src_mac;
    uint8_t             *dst_mac;
    char                *iface;
    int                 frame_length;
    uint8_t             *eth_frame;
    struct sockaddr_ll  device_info;
    struct addrinfo     source_addrinfo;
    struct addrinfo     *dest_addrinfo;
    struct arp_header   arp_header_s;
    struct victim       victim;
};

/*************** INIT HEADER ***************/
int set_personnal_mac_adress(struct arp_options *arp);
int set_src_device_info(struct arp_options *arp);
int set_dest_device_info(struct arp_options *arp);
int build_arp_header(struct arp_options *arp);
int proceed_initialisation(struct arp_options *arp);

/*************** BROADCAST ***************/
int send_mac_request(struct arp_options *arp);

/*************** RECEIVER ***************/
int get_mac_victim(struct arp_options *arp);

/*************** OUTPUT ***************/
void print_str_mac(char *str);
void print_arp_header(struct arp_options *arp);
void print_arp_spoof_header(struct arp_options *arp, char *mac_str);

/*************** SPOOF ***************/
int start_spoofing(struct arp_options *arp);

/*************** UTILS ***************/
uint8_t *string_to_mac(char *mac_str);

#endif