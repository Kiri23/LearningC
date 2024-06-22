#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void render_template(const char *template, const char *title, const char *body)
{
    char buffer[1024];
    // replace template variables with printf-style format specifiers
    snprintf(buffer, sizeof(buffer), template, title, body);
    printf("%s", buffer);
}

int main()
{
    // the template contains printf-style format specifiers
    const char *template = "<html><head><title>%s</title></head><body>%s</body></html>";
    render_template(template, "Hello, World!", "<h1>Welcome to my website</h1>");
    return 0;
}
