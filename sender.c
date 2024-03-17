#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "socket.h"
#include "list.h"
#include "sender.h"



List* list_input_send;
pthread_t threadPID_S;
pthread_cond_t input_send_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t input_send_mutex = PTHREAD_MUTEX_INITIALIZER;

 
void sender_init(void *arg){

    pthread_create(&threadPID_S, NULL, sender_transmitting, arg); 

}


void * sender_transmitting(void *arg){

    int* socketDescriptor_S = (int *)arg;
    char *messageTX;


    while(1){

        pthread_mutex_lock(&input_send_mutex);
        {   
            pthread_cond_wait(&input_send_cond, &input_send_mutex);
            if(List_count(list_input_send) != 0){
                List_last(list_input_send); // CS
                messageTX = List_remove(list_input_send); // CS
            }     
        }
        pthread_mutex_unlock(&input_send_mutex); 
                                         
        
        int bytesTx = sendto(*socketDescriptor_S, messageTX, strlen(messageTX), 0, rp_S->ai_addr, rp_S->ai_addrlen);

        if (bytesTx == -1) {
            printf("Error in sendto()!\n");
        }else{
            printf("Message sent -> %s", messageTX);
        }

    }

    return NULL;

}


void sender_shutdown(){

    pthread_cancel(threadPID_S);
    pthread_join(threadPID_S, NULL);

}
