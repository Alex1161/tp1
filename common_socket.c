#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

const int ERROR = -1;

int socket_init(socket_t *self) {
    return 0;
}

int socket_bind_listen(socket_t *self, const char *service) {
    struct addrinfo hints;
    struct addrinfo *result, *aux;
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, service, &hints, &result);
    if (status != 0){
        return ERROR;
    }
    
    bool bound = false;
    for (aux = result; aux != NULL && bound == false; aux = aux->ai_next) {
        self->fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (self->fd == -1) {
            return ERROR;
        } 
        
        status = bind(self->fd, aux->ai_addr, aux->ai_addrlen);
        if (status != 0) {
            close(self->fd);
        }

        bound = (status != -1);
    }

    freeaddrinfo(result);
    
    status = listen(self->fd, 10);
    if (status != 0){
        return ERROR;
    }

    return 0;
}

int socket_accept(socket_t *listener, socket_t *peer) {
    peer->fd = accept(listener->fd, NULL, NULL);
    if (peer->fd == -1) {
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
    
    bool connected = false;
    for (aux = result; aux != NULL && connected == false; aux = aux->ai_next) {
        self->fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (self->fd == -1) {
            return ERROR;
        } 
        
        status = connect(self->fd, aux->ai_addr, aux->ai_addrlen);
        if (status != 0) {
            close(self->fd);
        }

        connected = (status != -1);
    }

    freeaddrinfo(result);
    if (connected == false) {
        return ERROR;
    }

    return 0;
}

int socket_send(socket_t *self, const char *buffer, size_t length) {
    int sent = 0;
    bool socket_valid = true;

    while (sent < (int)length && socket_valid) {
        int status =send(self->fd, 
                         &buffer[sent], 
                         (int)length - sent, 
                         MSG_NOSIGNAL);

        if (status == 0) {
            socket_valid = false;
        } else if (status == -1) {
            socket_valid = false;
        } else {
            sent += status;
        }
    }

    if (socket_valid) {
        return (int)sent;
    } else {
        return ERROR;
    }
}

int socket_receive(socket_t *self, char *buffer, size_t length) {
    int received = 0;
    bool socket_valid = true;

    while (received < (int)length && socket_valid) {
        int status = recv(self->fd, 
                          &buffer[received], 
                          (int)length - received, 
                          0);

        if (status == 0) {
            break;
        } else if (status == -1) {
            socket_valid = false;
        } else {
            received += status;
        }
    }

    if (socket_valid) {
        return (int)received;
    } else {
        return ERROR;
    }
}

int socket_uninit(socket_t *self) {
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);

    return 0;
}
