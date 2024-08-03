#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
*   FTP client functionality. The client will send commands to the server and will receive data.
*/

#define PORT 5000

int run()
{
    //creates a socket for the client
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if(fd < 0)
    {
        printf("Client error: could not create socket\n");
        return 0;
    }

    //socket data (port and address)
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
    {
        printf("Client error: could not connect to server\n");
        return 0;
    }

    printf("Connected\n");

    char buf[1024] = { 0 };
    read(fd, buf, 1023);
    printf("%s\n", buf);

    //close socket
    close(fd);

    return 1;
}


int main()
{
    printf("Client\n");
    run();
    return 0;
}