#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "socket.h"
#include "list.h"
#include "output.h"
#include <string.h>



pthread_t threadPID_OUT;


void output_init(){

    pthread_create(&threadPID_OUT, NULL, output_printing, NULL); 

}


void * output_printing(){

    while(1){

        pthread_mutex_lock(&output_receive_mutex);
        {
            pthread_cond_wait(&output_receive_cond, &output_receive_mutex);
            if(List_count(list_output_receive) != 0){
                List_last(list_output_receive); // CS
                printf("Message received <- %s", (char *)List_remove(list_output_receive)); // CS  
            }
        }
        pthread_mutex_unlock(&output_receive_mutex);

    }

    return NULL;

}


void output_shutdown(){

    pthread_cancel(threadPID_OUT);
    pthread_join(threadPID_OUT, NULL);

}