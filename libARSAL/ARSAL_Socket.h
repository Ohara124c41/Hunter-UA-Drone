/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
/**
 * @file libARSAL/ARSAL_Socket.h
 * @brief This file contains headers about socket abstraction layer
 * @date 06/06/2012
 * @author frederic.dhaeyer@parrot.com
 */
#ifndef _ARSAL_SOCKET_H_
#define _ARSAL_SOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct iovec;

/**
 * @brief Type of Service class selector
 */
typedef enum {
    ARSAL_SOCKET_CLASS_SELECTOR_CS0 = 0,
    ARSAL_SOCKET_CLASS_SELECTOR_UNSPECIFIED = ARSAL_SOCKET_CLASS_SELECTOR_CS0,
    ARSAL_SOCKET_CLASS_SELECTOR_CS1 = 32, /* 0x20 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS2 = 64, /* 0x40 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS3 = 96, /* 0x60 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS4 = 128, /* 0x80 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS5 = 160, /* 0xA0 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS6 = 192, /* 0xC0 */
    ARSAL_SOCKET_CLASS_SELECTOR_CS7 = 224, /* 0xE0 */
} eARSAL_SOCKET_CLASS_SELECTOR;

/**
 * @brief Creates an endpoint for communication and returns a descriptor.
 *
 * @param domain The communication domain
 * @param type The communication semantics.
 * @param protocol A protocol to be used with the socket
 * @retval On success, a file descriptor for the new socket is returned. On error, -1 is returned, and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Create(int domain, int type, int protocol);

/**
 * @brief Initiate a connection on a socket,
 * If the socket sock is of type SOCK_DGRAM then addr is the address to which datagrams are sent by default, and the only address from which datagrams are received.
 * If the socket is of type SOCK_STREAM, this call attempts to make a connection to the socket that is bound to the address specified by addr.
 *
 * @param sockfd The socket descriptor used to connect
 * @param addr The address to connect.
 * @param addrlen The size of the addr
 * @retval On success, 0 is returned. Otherwise, -1 is returned and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * @brief Transmit a message on a socket
 * If sal_sendto() is used on a connection-mode (SOCK_STREAM) socket, the arguments dest_addr and addrlen are ignored (and the error EISCONN may be returned when they are not NULL and 0)
 * Otherwise, the target address is given by dest_addr with addrlen specifying its size.
 *
 * @param sockfd The socket descriptor used to send
 * @param buf The buffer to send
 * @param buflen The buffer size
 * @param flags The bitwise OR of zero or more of the socket flags.
 * @param dest_addr The target address
 * @param addrlen The size of the target address
 *
 * @retval On success, 0 is returned. Otherwise, -1 is returned and errno is set appropriately. (See errno.h)
 */
ssize_t ARSAL_Socket_Sendto(int sockfd, const void *buf, size_t buflen, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

/**
 * @brief Transmit a message on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param buf The buffer to send
 * @param buflen The buffer size
 * @param flags The bitwise OR of zero or more of the socket flags
 *
 * @retval On success, 0 is returned. Otherwise, -1 is returned and errno is set appropriately. (See errno.h)
 */
ssize_t ARSAL_Socket_Send(int sockfd, const void *buf, size_t buflen, int flags);

/**
 * @brief Receive a message on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param buf The buffer to fill with data received
 * @param buflen The buffer size
 * @param flags The bitwise OR of zero or more of the socket flags
 * @param src_addr The source address
 * @param addrlen The size of the source address
 *
 * @retval On success, the number of bytes received is returned. 0 is returned when the peer has performed an orderly shutdown.
 * Otherwise -1 is returned if an error occurred and errno is set appropriately. (See errno.h).
 */
ssize_t ARSAL_Socket_Recvfrom(int sockfd, void *buf, size_t buflen, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

/**
 * @brief Receive a message on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param buf The buffer to fill with data received
 * @param buflen The buffer size
 * @param flags The bitwise OR of zero or more of the socket flags
 *
 * @retval On success, the number of bytes received is returned. 0 is returned when the peer has performed an orderly shutdow.
 * Otherwise -1 is returned if an error occurred and errno is set appropriately. (See errno.h).
 */
ssize_t ARSAL_Socket_Recv(int sockfd, void *buf, size_t buflen, int flags);

/**
 * @brief Send multiple data on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param iov An array of struct iovec, which describes the data buffers
 * @param iovcnt The number of data buffers in iov
 *
 * @return On success, the number of written bytes is returned. On error, -1 is returned, and errno is set
 */
ssize_t ARSAL_Socket_Writev (int sockfd, const struct iovec *iov, int iovcnt);

/**
 * @brief Read multiple data from a socket
 *
 * @param sockfd The socket descriptor used to read
 * @param iov An array of struct iovec, which describes the data buffers
 * @param iovcnt The number of data buffers in iov
 *
 * @return On success, the number of bytes read is returned. On error, -1 is returned, and errno is set
 */
ssize_t ARSAL_Socket_Readv (int sockfd, const struct iovec *iov, int iovcnt);

/**
 * @brief Bind a name to a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param addr The address
 * @param addrlen The size of the address
 *
 * @retval On succes, 0 is returned. Otherwise -1 is returned if an error occurred and errno is set appropriately. (See errno.h).
 */
int ARSAL_Socket_Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/**
 * @brief Listen for connections on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param backlog The maximum length to which the queue of pending connections for sockfd may grow
 *
 * @retval On succes, 0 is returned. Otherwise -1 is returned if an error occurred and errno is set appropriately. (See errno.h).
 */
int ARSAL_Socket_Listen(int sockfd, int backlog);

/**
 * @brief Accept a connection on a socket
 *
 * @param sockfd The socket descriptor used to send
 * @param addr The address
 * @param addrlen The size of address
 *
 * @retval On succes, a nonnegative integer is returned. Otherwise -1 is returned if an error occurred and errno is set appropriately. (See errno.h).
 */
int ARSAL_Socket_Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/**
 * @brief Close a socket
 *
 * @param sockfd The socket to close
 * @retval On success, 0 is returned. Otherwise, -1 is returned, and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Close(int sockfd);

/**
 * @brief Set the socket options
 *
 * @param sockfd The socket to set options
 * @param level the protocol level
 * @param optname the option name
 * @param optval the option value
 * @param optlen the length of the option value
 * @retval On success, 0 is returned. Otherwise, -1 is returned, and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/**
 * @brief Get the socket options
 *
 * @param sockfd The socket to get options
 * @param level the protocol level
 * @param optname the option name
 * @param optval the option value
 * @param optlen the length of the option value
 * @retval On success, 0 is returned. Otherwise, -1 is returned, and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);

/**
 * @brief Get the socket name
 *
 *
 * @param sockfd The socket to get options
 * @param addr current address to which the socket sockfd is bound,
 * @param addrlen size of addr buffer
 * @retval On success, 0 is returned. Otherwise, -1 is returned, and errno is set appropriately. (See errno.h)
 */
int ARSAL_Socket_Getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif // _ARSAL_SOCKET_H_
