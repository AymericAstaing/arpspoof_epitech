# ARP spoof_epitech (TECH 2 2018-2019)

/!\ WORKS ON LINUX ONLY (linux socket lib)

The goal of this project to create a program that spoofs ARP packets.

The program must first broadcast an ARP packet in order to retrieve the corresponding MAC address of
the IPv4 address which belongs to the target/victim. After this step, the program must send spoofed ARP
reply packets every 1 second (using that MAC address). Those spoofed ARP packets should basically lie to
the target/victim by saying that our MAC address resolves to an IPv4 that we have provided as an argument
to our program.

constraints:

    - NO libraries are allowed, only the standard C library!  
    - The socket that sends arbitrary ARP packets should be called with SOCK_RAW as second parameter (and not SOCK_DGRAM).

to launch:

    - make / make re
    
BASIC USAGE (execute very carefully):

    - sudo ./myARPspoof 42.42.42.42 192.168.1.1 wlo1
    
ADVANCED USAGE:
    
- print broadcast:

If the --printBroadcast option is passed as a parameter to the program, the program must print on stdout the ARP packet (step 1 - the ARP request packet sent to broadcast) followed by a newline and exit WITHOUT actually sending the packet. 
    
    ./myARPspoof 42.42.42.42 192.168.1.1 wlo1 ––printBroadcast
    
- print spoof:

If the --printSpoof [MAC addr] option is passed as a parameter to the program, the program must print the
spoofed ARP packet (step 3) and exit:
    
    ./myARPspoof 42.42.42.42 192.168.1.1 wlo1 ––printSpoof
   
Aymeric Astaing - EPITECH PARIS PROMO 2022
