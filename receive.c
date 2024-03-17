#include <stdio.h>
#include <netdb.h>
#include <pthread.h>
#include "socket.h"
#include "list.h"
#include "receive.h"



List* list_output_receive;
pthread_t threadPID_R;
pthread_mutex_t output_receive_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t output_receive_cond = PTHREAD_COND_INITIALIZER;


void receive_init(void *arg){

    pthread_create(&threadPID_R, NULL, receive_listening, arg); 
}


void * receive_listening(void *arg){

    int* socketDescriptor_R = (int *)arg;
    char messageRX[MSG_LEN];
    unsigned int rp_R_len = sizeof(rp_R);


    while(1){

        int bytesRx = recvfrom(*socketDescriptor_R, messageRX, MSG_LEN, 0, (struct sockaddr*)&rp_R, &rp_R_len);

        if (bytesRx == -1) {

            printf("Error in recvfrom()!\n");

        }else{

            int terminateIdx = (bytesRx < MSG_LEN) ? bytesRx : MSG_LEN - 1;
            messageRX[terminateIdx] = 0;

            pthread_mutex_lock(&output_receive_mutex);
            {
                if(List_prepend(list_output_receive, messageRX) == -1){ // CS
                    printf("Program failed to save the received message in the list!\n");
                }
                pthread_cond_signal(&output_receive_cond);
            }
            pthread_mutex_unlock(&output_receive_mutex);
        }

    }

    return NULL;

}


void receive_shutdown(){

    pthread_cancel(threadPID_R);
    pthread_join(threadPID_R, NULL);

}