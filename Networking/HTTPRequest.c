//
//  HTTPRequest.c
//  hdelibc
//
//  Created by Eric Meehan on 2/9/21.
//

#include "HTTPRequest.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// find the \r\n in the request string
// debugging function
void find_crlf(const char *str)
{
    printf("Finding \\r\\n...\n");
    int length = strlen(str);

    for (int i = 0; i < length; i++)
    {
        if (str[i] == '\r' && (i + 1 < length) && str[i + 1] == '\n')
        {
            printf("Found \\r\\n at position %d\n", i);
            printf("string at position %d (ASCII %d) is /r %c\n", i, str[i], str[i]);
            printf("string at position %d (ASCII %d) is  /n%c\n", i + 1, str[i + 1], str[i + 1]);
            // printf("string at position %d (ASCII %d) is %c\n", i - 1, str[i - 1], str[i - 1]);
            // printf("string at position %d (ASCII %d) is %c\n", i - 2, str[i - 2], str[i - 2]);
            // printf("string at position %d is %c (ASCCII %d)\n", i - 3, str[i - 3], str[i - 3]);
            // printf("string at position %d (ASCII %d) is %c\n", i - 4, str[i - 4], str[i - 4]);
            // printf("string at position %d is %c\n", i - 5, str[i - 5]);
            // printf("string at position %d is %c\n", i - 6, str[i - 6]);
            i++; // Move past the \n character to avoid overlapping matches
        }
    }
}

int method_select(char *method)
{
    if (strcmp(method, "GET") == 0)
    {
        return GET;
    }
    else if (strcmp(method, "POST") == 0)
    {
        return POST;
    }
    else if (strcmp(method, "PUT") == 0)
    {
        return PUT;
    }
    else if (strcmp(method, "HEAD") == 0)
    {
        return HEAD;
    }
    else if (strcmp(method, "PATCH") == 0)
    {
        return PATCH;
    }
    else if (strcmp(method, "DELETE") == 0)
    {
        return DELETE;
    }
    else if (strcmp(method, "CONNECT") == 0)
    {
        return CONNECT;
    }
    else if (strcmp(method, "OPTIONS") == 0)
    {
        return OPTIONS;
    }
    else if (strcmp(method, "TRACE") == 0)
    {
        return TRACE;
    }
    else
    {
        return -1;
    }
}

struct HTTPRequest http_request_constructor(char *request_string)
{
    struct HTTPRequest request;
    char requested[strlen(request_string) + 1];
    strcpy(requested, request_string);
    // Need to find the headers first since strtok mutates the string
    // and need to find the end of the headers to separate the body before mutating the string
    // to find the request line
    // Find the end of the headers (find substring \r\n\r\n)
    char *headers_end = strstr(requested, "\r\n\r\n");
    if (!headers_end)
    {
        printf("Invalid HTTP request: No end of headers found.\n");
        return request;
    }

    // Terminate the headers part
    // el \0 es importante pq no permite que se vea el body despues de los headers
    // le dice a las funciones mira aqui llegan los headers marca el fin de los headers
    *headers_end = '\0';
    headers_end += 4; // Move past the \r\n\r\n

    // strok muta el string original
    // separate a string by a delimiter into tokens
    char *request_line = strtok(requested, "\r\n");
    printf("Request Line: %s\n", request_line);
    char *header_fields = request_line + strlen(request_line) + 2;
    printf("Header Fields: %s\n", header_fields);

    // The body starts right after the headers_end
    char *body = headers_end;
    printf("Body: %s\n", body);

    char *method = strtok(request_line, " ");
    printf("Method: %s\n", method);
    request.Method = method_select(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    // skip the HTTP
    HTTPVersion = strtok(HTTPVersion, "/");
    //skip the / in /1.1
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVersion = (float)atof(HTTPVersion);

    return request;
}