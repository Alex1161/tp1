#include "common_socket.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>


const int ERROR = -1;

int socket_init(socket_t *self) {
    // self->fd = socket(AF_LOCAL, AF_INET, SOCK_STREAM);
    // if (self->fd == -1) {
    //     return ERROR;
    // }
    
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
    peer->fd = accept(listener->fd, NULL, NULL);
    if (peer->fd = -1) {
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
    int status = 0;
    bool socket_valid = true;

    while (sent < (int)length && socket_valid) {
        status = send(self->fd, &buffer[sent], (int)length - sent, MSG_NOSIGNAL);

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
    size_t received = 0;
    size_t status = 0;
    bool socket_valid = true;

    while (received < length && socket_valid) {
        status = recv(self->fd, &buffer[received], length-received, 0);

        if (status == 0) {
            socket_valid = false;
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