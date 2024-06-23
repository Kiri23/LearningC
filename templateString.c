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

// example of how to "maybe" parse the HTML and add for loop specifiers or boolean logic, and other logic
// i will add the new operators to the if below

// I will be missing modularity if I use prinft-style format specifiers, because with a template engine
// it can divided into "components" but how to create the idea of html component with string in c
// well you could "merge" strings with printf-style format specifiers? :thinking_face:

// mustache existe en c!!!! yay!!! - https://gitlab.com/jobol/mustach
void my_putchar(char c)
{
    putchar(c); // Use the standard library function to print a character
}

// Custom printf function
void my_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++)
    {
        if (*p == '%')
        {
            p++;
            switch (*p)
            {
            case 'd':
            {
                int i = va_arg(args, int);
                char buffer[20];
                snprintf(buffer, sizeof(buffer), "%d", i);
                for (char *b = buffer; *b != '\0'; b++)
                {
                    my_putchar(*b);
                }
                break;
            }
            case 'c':
            {
                int c = va_arg(args, int);
                my_putchar(c);
                break;
            }
            case 's':
            {
                const char *s = va_arg(args, const char *);
                while (*s)
                {
                    my_putchar(*s++);
                }
                break;
            }
            case '%':
            {
                my_putchar('%');
                break;
            }
            default:
            {
                my_putchar('%');
                my_putchar(*p);
                break;
            }
            }
        }
        else
        {
            my_putchar(*p);
        }
    }

    va_end(args);
}

int main()
{
    // the template contains printf-style format specifiers
    const char *template = "<html><head><title>%s</title></head><body>%s</body></html>";
    render_template(template, "Hello, World!", "<h1>Welcome to my website</h1>");
    my_printf("\n");
    my_printf("Hello, %s! You have %d new messages. Your grade is %c.\n", "Alice", 5, 'A');
    return 0;
}
