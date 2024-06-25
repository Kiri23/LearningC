//
//  test.c
//  hdelibc
//
//  Created by Eric Meehan on 2/7/21.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
// #include "../Networking/Nodes/Server.h"
// #include "../Networking/Protocols/HTTPRequest.h"
#include "../Networking.h"
// How to run with the static library gcc HTTPRequestTest.c ../hdelibc.a (note without -c or -o. a file called a.out will be generated)
// modifies the other examples to run with the library
void launch(struct Server *server)
{
    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\n"
                  "Server: Apache/2.2.14 (Win32)\n"
                  "Last-Modified: Wed, 22 Jul 2023 19:15:56 GMT\n"
                  "Content-Type: text/html\n"
                  "Connection: Closed\n\n"
                  "<html>"
                  "<head>"
                  "<script>"
                  "window.onload = function() {"
                  "document.getElementById('greeting').style.color = 'red';"
                  "console.log('Hello, Christian!');"
                  "};"
                  "</script>"
                  "</head>"
                  "<body>"
                  "<h1 id=\"greeting\" style=\"color: blue;\">Hello christian!!</h1>"
                  "<p style=\"color: blue;\">This is a test of the emergency broadcast system.</p>"
                  "</body>"
                  "</html>";
    int address_length = sizeof(server->address);
    int new_socket;
    while (1)
    {
        printf("===== WAITING FOR CONNECTION =====\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        struct HTTPRequest request = http_request_constructor(buffer);
        printf("Method: %d\n", request.Method);
        printf("Path: %s\n", request.URI);
        printf("Version: %f\n", request.HTTPVersion);
        write(new_socket, hello, strlen(hello));
        close(new_socket);
    }
}

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);
}