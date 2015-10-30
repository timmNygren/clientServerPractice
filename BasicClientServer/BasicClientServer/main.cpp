//
//  main.cpp
//  BasicClientServer
//
//  Created by Timm Nygren on 10/30/15.
//  Copyright © 2015 Timm Nygren. All rights reserved.
//

#include <iostream>
//#include <sys/socket.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/types.h>
#include <netinet/in.h>


void error(const char *message);

int main(int argc, const char * argv[]) {
    
    int socketfd, newSockfd, portNo;
    socklen_t clientLen;
    char buffer[256];
    struct sockaddr_in serverAddr, clientAddr;
    int returnVal;
    
    if (argc < 2)
    {
        std::cerr << "ERROR, no port provided!\n";
        std::cerr << "Provide a port number between 49152 - 65535\n";
        exit(1);
    }
    
    
    return 0;
}

void error(const char *message)
{
    perror(message);
    exit(1);
}
