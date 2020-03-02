#include <winsock2.h>
#include <stdio.h>
#include "server.h"
#include <unistd.h>

char *get_full_path(char *name)
{
    char filename[1024] = {0};
    getcwd(filename, 1024);

    if ((filename[strlen(filename)] != '\\') && 
        (name[strlen(name)] != '/') &&
        (name[strlen(name)] != '\\'))
    {
        strcat(filename, "\\");
    }

    int i;
    for (i = 0; name[i]; i++)
        if (name[i] == '/')
            name[i] = '\\';

    strcat(filename, name);
    return strdup(filename);
}

RESPONSE *GetResponse(REQUEST *request)
{
    RESPONSE *response;

    response = malloc(sizeof(RESPONSE));
    response->error    = 0;
    response->filename = request->value;
    response->filepath = get_full_path(request->value);
    response->header   = get_header(response);

    return response;
}

int SendResponse(SOCKET sock, RESPONSE *response)
{
    if (response->error) {
        send(sock, DEFAULT_ERROR_404, strlen(DEFAULT_ERROR_404), 0);
        return 1;
    }

    FILE *f = fopen(response->filepath, "rb");
    char buf[1024] = {0};
    int msg_len;

    if (!f) {
        send(sock, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n", 57, 0);
        return 1;
    }

    send(sock, response->header, strlen(response->header), 0);

    int result = 0;
    while ((result = fread(buf, 1, 1024, f)) > 0)
    {
        msg_len = send(sock, buf, result, 0);

        if (msg_len == SOCKET_ERROR) {
            //error_live("send()");
            printf("Error sending data, reconnecting...\n");
            closesocket(sock);
            return -1;
        }
        else if (!msg_len)
        {
            printf("Client closed connection\n");
            closesocket(sock);
            return 0;
            //WSACleanup();
        }
    }

    printf("Served file %s\n", response->filepath);

    return 1;
}
