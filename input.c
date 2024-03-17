#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "socket.h"
#include "list.h"
#include "input.h"



pthread_t threadPID_IN;


void input_init(){

    pthread_create(&threadPID_IN, NULL, input_keyboard, NULL); 

}


void * input_keyboard(){

    char messageTX[MSG_LEN];
    
    while(1){

        fgets(messageTX, MSG_LEN, stdin);

        if(strcmp(messageTX, "!\n") == 0){
            endProgram = 1;
            break;
        }

        pthread_mutex_lock(&input_send_mutex);
        {
            if(List_prepend(list_input_send, messageTX) == -1){ // CS
                printf("Program failed to save the typed message in the list!\n");
            }
            pthread_cond_signal(&input_send_cond);

        }
        pthread_mutex_unlock(&input_send_mutex);
        
    }
    
    return NULL;

}


void input_shutdown(){

    pthread_cancel(threadPID_IN);
    pthread_join(threadPID_IN, NULL);

}