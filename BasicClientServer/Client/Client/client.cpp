//
//  client.cpp
//  Client
//
//  Created by Timm Nygren on 10/31/15.
//  Copyright © 2015 Timm Nygren. All rights reserved.
//

#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>

void error(const char *message);

int main(int argc, char* argv[])
{
    int socketfd, portNo, returnValue;
    struct sockaddr_in serverAddr;
    struct hostent *server;
    
    char buffer[256];
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " hostname port\n";
        exit(EXIT_FAILURE);
    }
    
    portNo = atoi(argv[2]);
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
        error("ERROR opening socket");
    
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        std::cerr << "ERROR, no such host!\n";
        exit(EXIT_FAILURE);
    }
    
    bzero( (char*) &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
          (char*)&serverAddr.sin_addr.s_addr,
          server->h_length);
    
    serverAddr.sin_port = htons(portNo);
    
    if (connect(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        error("ERROR connecting");
    
    std::cout << "Please enter the message: ";
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    returnValue = static_cast<int>( write(socketfd, buffer, 256) );
    
    if (returnValue < 0) {
        error("ERROR writing to socket");
    }
    
    bzero(buffer, 256);
    returnValue = static_cast<int>( read(socketfd, buffer, 255) );
    
    if (returnValue < 0) {
        error("ERROR reading from socket");
    }
    std::cout << buffer << std::endl;
    close(socketfd);
    
    return 0;
}

void error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}
