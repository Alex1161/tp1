#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

typedef struct {
    int fd;
    int domain;
} socket_t;

int socket_init(socket_t *self, int domain);
int socket_bind_listen(socket_t *self, 
                       const char *host, 
                       const char *service);
int socket_accept(socket_t *listener, socket_t *peer);
int socket_uninit(socket_t *self);

#endif