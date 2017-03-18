#include <winsock2.h>
#include <stdio.h>
#include "server.h"

BOOL FileExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

char *get_content_type(char *name)
{
    char *extension = strchr(name, '.');

    if (!strcmp(extension, ".html"))
        return "text/html";
    else if (!strcmp(extension, ".ico"))
        return "image/webp";
    else if (!strcmp(extension, ".css"))
        return "text/css";
    else if (!strcmp(extension, ".jpg"))
        return "image/jpeg";
    else if (!strcmp(extension, ".js"))
        return "text/javascript";

    return "*/*";
}

char *get_header(RESPONSE *rs)
{
    if (!FileExists(TEXT(rs->filepath))) {
        printf("404 Not Found: %s\n", rs->filename);
        rs->error = 404;
        return "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    }

    char header[1024] = {0};
    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\n\r\n", get_content_type(rs->filename));
    return strdup(header);
}