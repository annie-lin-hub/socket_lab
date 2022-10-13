#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *addr = (argv[1]);
    int port = 1234;
    printf("start TCP Client to connect TCP Server...\n");

    int fd_client;
    fd_client = socket(PF_INET, SOCK_STREAM, 0);
    if (fd_client < 0) {
        perror("socket error");
        return 1;
    }

    struct sockaddr_in remote_address;
    memset(&remote_address, 0, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr("140.118.121.109");
    remote_address.sin_port = htons(port);
    struct sockaddr *remote_socket_address = (struct sockaddr *) &remote_address;
    size_t socket_address_length = sizeof(struct sockaddr);

    int connect_ret = connect(fd_client, remote_socket_address, socket_address_length);
    if (connect_ret < 0) {
        perror("connect server failed");
        return 1;
    }

   while (1) {
        
        char buf[BUFSIZ];
        printf("please input message:");
        scanf("%s", buf);
        
        size_t send_ret = write(fd_client, buf, strlen(buf));
        if (send_ret <= 0) {
            perror("send error");
            return 1;
        }  
        
   }

    close(fd_client);

    return 0;
}