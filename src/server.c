#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int main(int argc, char **argv)
{
    int addr_len;
    struct sockaddr_in local, client_addr;

    SOCKET sock, msg_sock;
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == SOCKET_ERROR)
        error_die("WSAStartup()");

    // Fill in the address structure
    local.sin_family        = AF_INET;
    local.sin_addr.s_addr   = INADDR_ANY;
    local.sin_port          = htons(DEFAULT_PORT);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
        error_die("socket()");

    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR)
        error_die("bind()");

listen_goto:

    if (listen(sock, 10) == SOCKET_ERROR)
        error_die("listen()");

    printf("Waiting for connection...\n");

    int count = 0;

    forever
    {
        addr_len = sizeof(client_addr);
        msg_sock = accept(sock, (struct sockaddr*)&client_addr, &addr_len);

        if (msg_sock == INVALID_SOCKET || msg_sock == -1)
            error_die("accept()");

        printf("\n\n#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$ %d\n\n", ++count);
        printf("Connected to %s:%d\n", inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port));

        REQUEST *request = GetRequest(msg_sock);
        printf("Client requested %d %s\n", request->type, request->value);

        if (request->length == 0)
            continue;

        RESPONSE *response = GetResponse(request);
        int sent = SendResponse(msg_sock, response);

        closesocket(msg_sock);

        if (sent == 0)
            break;
        else if (sent == -1)
            goto listen_goto;

    }

    WSACleanup();
}
