#include "header.h"
#include <cstring>
#include <cstdio>

Networks getNetworks()
{
    Networks networks;
    struct ifaddrs *ifaddr, *ifa;
    
    if (getifaddrs(&ifaddr) == -1) {
        return networks;
    }
    
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) continue;
        
        if (ifa->ifa_addr->sa_family == AF_INET) {
            IP4 ip4;
            ip4.name = strdup(ifa->ifa_name);
            struct sockaddr_in* addr_in = (struct sockaddr_in*)ifa->ifa_addr;
            inet_ntop(AF_INET, &(addr_in->sin_addr), ip4.addressBuffer, INET_ADDRSTRLEN);
            networks.ip4s.push_back(ip4);
        }
    }
    
    freeifaddrs(ifaddr);
    return networks;
}