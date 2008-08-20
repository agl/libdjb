#ifndef SOCKET_H
#define SOCKET_H

#include "uint16.h"

/**
 * socket_tcp - create a TCP socket
 * returns: the fd, or -1 on error
 *
 * The socket has Nagle disabled
 */
extern int socket_tcp();

/**
 * socket_udp - create a UDP socket
 * returns: the fd, or -1 on error
 *
 * The socket has Nagle disabled
 */
extern int socket_udp();

/**
 * socket_connect4 - connect a socket
 * @ip: a pointer to a 4-byte, big-endian IP address
 * returns: -1 on error
 */
extern int socket_connect4(int fd,const char *ip, uint16 port);

/**
 * socket_connected - check to see if a fd is connected
 * returns: 1 if it is, 0 otherwise
 */
extern int socket_connected(int fd);

/* socket_bind4 - bind a socket
 * @ip: a pointer to be 4-byte, big-endian IP address
 * returns: -1 on error
 */
extern int socket_bind4(int fd, char *ip, uint16 port);


extern int socket_bind4_reuse(int,char *,uint16);
extern int socket_listen(int,int);
extern int socket_accept4(int,char *,uint16 *);
extern int socket_recv4(int,char *,int,char *,uint16 *);
extern int socket_send4(int,const char *,int,const char *,uint16);
extern int socket_local4(int,char *,uint16 *);
extern int socket_remote4(int,char *,uint16 *);

/**
 * socket_tryreservein - attempt to set the kernel's recv buffer size
 */
extern void socket_tryreservein(int fd, int bytes);

#endif
