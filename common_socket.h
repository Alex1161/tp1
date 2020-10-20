#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <stddef.h>

typedef struct {
    int fd;
} socket_t;

int socket_init(socket_t *self);
int socket_uninit(socket_t *self);

int socket_bind_listen(socket_t *self, const char *service);
int socket_accept(socket_t *listener, socket_t *peer);
int socket_connect(socket_t *self, 
                   const char *host, 
                   const char *service);

int socket_send(socket_t *self, const char *buffer, size_t length);
int socket_receive(socket_t *self, char *buffer, size_t length);

#endif
