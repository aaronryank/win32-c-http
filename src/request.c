#include <winsock2.h>
#include <stdio.h>
#include "server.h"

int get_request_type(char *buf)
{
    char retval[10] = {0};
    sscanf(buf, "%s ", &retval);

    if (!strcmp(retval, "GET"))
        return GET;
    else if (!strcmp(retval, "POST"))
        return POST;
    else if (!strcmp(retval, "PUT"))
        return PUT;
    else
        return RQ_UNDEF;
}

char *get_request_value(char *buf)
{
    char retval[100] = {0};

    sscanf(buf, "%s %s ", &retval, &retval);  // tee hee

    if (retval[strlen(retval)-1] == '/')
        strcat(retval, "index.html");

    return strdup(retval);
}

REQUEST *GetRequest(SOCKET sock)
{
    REQUEST *request;
    int msg_len;
    char buf[REQUEST_SIZE];

    msg_len = recv(sock, buf, sizeof(buf), 0);
    //printf("Bytes Received: %d, message: %s from %s\n", msg_len, buf, inet_ntoa(client.sin_addr));

    request         = malloc(sizeof(REQUEST));
    request->type   = get_request_type(buf);
    request->value  = get_request_value(buf);
    request->length = msg_len;

    return request;
}