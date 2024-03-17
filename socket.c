#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "socket.h"



const char* Port_S;
const char* Port_R;
const char* HostName_R;
struct addrinfo *rp_S, *result;
struct sockaddr_in rp_R;


int socket_R_init(){

    // rp_R for receiving
    memset(&rp_R, 0 , sizeof(rp_R));
    rp_R.sin_family = AF_INET;
    rp_R.sin_addr.s_addr = htonl(INADDR_ANY); 
    rp_R.sin_port = htons(atoi(Port_R));

    int socketDescriptor_R = socket(PF_INET, SOCK_DGRAM, 0);
    if(socketDescriptor_R == -1){
        printf("Error in socket()!\n");
        exit(EXIT_FAILURE);
    }
    
    int thebind = bind(socketDescriptor_R, (struct sockaddr*)&rp_R, sizeof(rp_R));
    if(thebind == -1){
        printf("Error in bind()!\n");
        exit(EXIT_FAILURE);
    }

    return socketDescriptor_R;

}


int socket_S_init(){

    // rp_S for sending
    int socketDescriptor_S;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    
    int status = getaddrinfo(HostName_R, Port_S, &hints, &result);
    if(status != 0){
        printf("Error in finding IP in getaddrinfo()!\n");
        exit(EXIT_FAILURE);
    } 
    for(rp_S = result; rp_S != NULL; rp_S = rp_S->ai_next){

        socketDescriptor_S = socket(rp_S->ai_family, rp_S->ai_socktype, 0);
        if(socketDescriptor_S == -1){
            printf("Error in socket()!\n");
            exit(EXIT_FAILURE);
        }
        break;
    }

    if(rp_S == NULL){
        printf("Could not creat a socket!\n"); 
        exit(EXIT_FAILURE);
    }

    return socketDescriptor_S;

}


void socket_R_close(int socketDescriptor_R){

    close(socketDescriptor_R);

}


void socket_S_close(int socketDescriptor_S){

    freeaddrinfo(result);
    close(socketDescriptor_S);

}

