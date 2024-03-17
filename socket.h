#ifndef _SOCKET_H
#define _SOCKET_H


#include "list.h"
#include <arpa/inet.h>
#include <pthread.h>


#define MSG_LEN 1024


extern const char* Port_S;
extern const char* Port_R;
extern const char* HostName_R;


extern struct addrinfo *rp_S; 
extern struct addrinfo *result;
extern struct sockaddr_in rp_R;


extern pthread_mutex_t input_send_mutex;
extern pthread_mutex_t output_receive_mutex;
extern pthread_cond_t input_send_cond;
extern pthread_cond_t output_receive_cond;


extern List* list_input_send;
extern List* list_output_receive;


extern int endProgram;


int socket_R_init();


int socket_S_init();


void socket_R_close(int socketDescriptor_R);


void socket_S_close(int socketDescriptor_S);


#endif
