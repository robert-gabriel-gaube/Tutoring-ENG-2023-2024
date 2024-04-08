#include <stdarg.h>
#include <stdio.h>

void mini_printf(const char *format, ...) {
  va_list args; // Declare a va_list variable to manage the variable arguments

  // Initialize the va_list 'args' to start at the argument after 'format'
  va_start(args, format);

  while (*format) // Loop through the format string
  {
    // If a format specifier is encountered
    if (*format == '%') {
      format++;
      if (*format == 'd') {
        // Fetch the next argument as an integer and print it
        printf("%d", va_arg(args, int));
      } else if (*format == 's') {
        // Fetch the next argument as a string and print it
        printf("%s", va_arg(args, char *));
      }
    } else {
      // Print regular characters
      putchar(*format);
    }
    format++; // Move to the next character
  }
  // Cleanup the va_list 'args' after processing
  va_end(args);
}

int main(void) {
  mini_printf("Hello %s, number is %d\n", "World", 42);
  return (0);
}