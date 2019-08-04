/*
void get_gateway_mac_address(unsigned char gw_mac_address[6] ,const char* gateway_ip_address)
{
    FILE *arpCache = fopen(ARP_CACHE, "r");
    if (!arpCache)
    {
        perror("Arp Cache: Failed to open file \"" ARP_CACHE "\"");
        return;
    }

    /* Ignore the first line, which contains the header */
    char header[ARP_BUFFER_LEN];
    if (!fgets(header, sizeof(header), arpCache))
    {
        return;
    }

    char ipAddr[ARP_BUFFER_LEN], hwAddr[ARP_BUFFER_LEN], device[ARP_BUFFER_LEN], state[ARP_BUFFER_LEN];
    int count = 0;
    while (4 == fscanf(arpCache, ARP_LINE_FORMAT, ipAddr, state, hwAddr, device))
    {
        if(strcmp(ipAddr,gateway_ip_address)==0){
        printf("%03d: Mac Address of [%s]\t on [%s] is \"%s\"  State: %s\n",
                ++count, ipAddr, device, hwAddr, state);
        sscanf(hwAddr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &gw_mac_address[0], &gw_mac_address[1], &gw_mac_address[2], &gw_mac_address[3], &gw_mac_address[4], &gw_mac_address[5]);
       // strcpy(gw_mac_address,hwAddr);
        }
        ++count;
    }
    fclose(arpCache);
    return;
}
