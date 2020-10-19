#include "common_socket.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>


const int ERROR = 1;

int socket_init(socket_t *self, int domain) {
    self->fd = socket(domain, AF_INET, SOCK_STREAM);
    self->domain = domain;
    if (self->fd == -1) {
        return ERROR;
    }
    
    return 0;
}

int socket_bind_listen(socket_t *self, 
                       const char *host, 
                       const char *service) {
    struct addrinfo hints;
    struct addrinfo *result;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, service, &hints, &result);
    if (status != 0){
        return ERROR;
    }

    status = bind(self->fd, result->ai_addr, result->ai_addrlen);
    if (status != 0){
        return ERROR;
    }

    freeaddrinfo(result);
    
    status = listen(self->fd, 10);
    if (status != 0){
        return ERROR;
    }

    return 0;
}

int socket_accept(socket_t *listener, socket_t *peer) {
    peer = accept(listener, NULL, NULL);
    if (peer = -1) {
        return ERROR;
    }
    
    return 0;
}

int socket_connect(socket_t *self, 
                   const char *host, 
                   const char *service) {
    struct addrinfo hints;
    struct addrinfo *result, *aux;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int status = getaddrinfo(host, service, &hints, &result);
    if (status != 0) {
        return ERROR;
    }
    
    int skt;
    bool connected = false;
    for (aux = result; aux != NULL && connected == false; aux = aux->ai_next) {
        skt = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (skt == -1) {
            return ERROR;
        } 
        
        status = connect(skt, aux->ai_addr, aux->ai_addrlen);
        if (status != 0) {
            close(skt);
        }

        connected = (status != -1);
    }

    freeaddrinfo(result);
    if (connected == false) {
        return ERROR;
    }

    return 0;
}

int socket_uninit(socket_t *self) {
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);

    return 0;
}