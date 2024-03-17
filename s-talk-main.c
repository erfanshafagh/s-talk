#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "output.h"
#include "input.h"
#include "receive.h"
#include "sender.h"
#include "socket.h"



int endProgram;


int main(int argc, char* args[]){

    if (argc != 4){
        printf("Not Enough Arguments Passed To The Program!\n");
        printf("Run The Program With The Format Of ./s-talk yourPort remoteIP remotePort\n");
        return 0;
    }

    Port_S = args[1];
    Port_R = args[3];
    HostName_R = args[2];

    printf("\n***********Welcome to s-talk program***********\n\n");
    printf("Information:\n");
    printf("\tYou will be sending messages on port   (%s)\n", Port_S);
    printf("\tYou will be receiving messages on port (%s)\n", Port_R);
    printf("\tYou will be receiving messages from    (%s)\n", HostName_R);
    printf("\tYou can write your messages by keyboard and sent it by pressing enter.\n");
    printf("\tYou can exit by writing '!' and pressing enter.\n\n");

    endProgram = 0;

    int  socketDescriptor_S = socket_S_init();
    int  socketDescriptor_R = socket_R_init();

    list_input_send = List_create();
    list_output_receive = List_create();

    input_init();
    sender_init((void *) &socketDescriptor_S);
    receive_init((void *) &socketDescriptor_R);
    output_init(NULL);
    
    while(1){ // Waiting for "!"
        if(endProgram == 1){
            break;
        }
    }

    receive_shutdown();
    sender_shutdown();
    output_shutdown();
    input_shutdown();

    socket_S_close(socketDescriptor_S);
    socket_R_close(socketDescriptor_R);
    

    return 0;
}

