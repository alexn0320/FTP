#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
*   FTP server functionality. The server should send the data to the client.
*/

#define PORT 5000

int run()
{
    //creates a socket for the server
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    if(fd < 0)
    {
        printf("Server error: could not create socket\n");
        return 0;
    }

    //socket data (port and address)
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to the socket data
    if(bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
    {
        printf("Server error: could not bind socket\n");
        return 0;
    }

    //waits and accepts one connection
    if(listen(fd, 10) < 0)
    {
        printf("Server error: could not listen for client socket\n");
        return 0;
    }

    //accepts the connection
    int c_fd = accept(fd, NULL, NULL);

    printf("Accepted connection\n");

    char buf[1024] = "Test";
    write(c_fd, buf, strlen(buf));
    printf("Sent\n");

    //close socket
    close(fd);

    return 1;
}

int main()
{
    printf("Server\n");
    run();
    return 0;
}