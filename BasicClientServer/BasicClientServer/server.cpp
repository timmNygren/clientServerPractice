//
//  server.cpp
//  BasicClientServer
//
//  Created by Timm Nygren on 10/30/15.
//  Copyright © 2015 Timm Nygren. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>




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
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
        error("ERROR opening socket");
    
    bzero( (char*) &serverAddr, sizeof(serverAddr) );
    portNo = atoi(argv[1]);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(portNo);
    
    if (bind(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
        error("ERROR binding socket");
    
    listen(socketfd, 5);    // might want to check later
    clientLen = sizeof(clientAddr);
    newSockfd = accept(socketfd, (struct sockaddr *) &clientAddr, &clientLen);
    
    if (newSockfd < 0)
        error("ERROR on accept");
    
    bzero(buffer, 256);
    returnVal = static_cast<int>( read(newSockfd, buffer, 255) );   // cast to int because this isn't expected to read (long) number of bytes
    
    if (returnVal < 0)
        error("ERROR reading from socket");
    
    std::cout << "Here is the message: " << buffer << std::endl;
    
    returnVal = static_cast<int>( write(newSockfd, "I got your message", 18) ); // same reason as read(above)
    
    if (returnVal < 0)
        error("ERROR writing to socket");
    
    close(newSockfd);
    close(socketfd);
    
    return 0;
}

void error(const char *message)
{
    perror(message);
    exit(1);
}
