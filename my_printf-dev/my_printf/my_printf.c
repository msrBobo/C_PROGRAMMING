#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

int count = 0;
for (size_t i = 0; format[i]; i++) {
    if (format[i] == '%') {
        i++;
        char buffer[64];
        int j=0;
        switch (format[i]) {
            case 'c': {
                char val = (char)va_arg(args, int);
                buffer[0]=val;
                j=1;
                break;
            }
            case 's': {
                char *val = va_arg(args, char*);
                if (val == 0) {
                    strcpy(buffer, "(null)");
                    j = strlen(buffer);
                } else {
                for (j = 0; val[j]; j++) {
                    buffer[j] = val[j];
                }
                }
                break;
            }
            case 'd': {
int val = va_arg(args, int);
int digits = 1;
int isNegative = (val < 0);
if (isNegative) {
val = -val;
}
for (int k = val/10; k!=0; k/=10) {
digits++;
}
char buffer[digits + 1 + isNegative];
int j = digits - 1;
if (isNegative) {
buffer[0] = '-';
j++;
}
for (int i = 0; i < digits; i++) {
buffer[j--] = (val % 10) + '0';
val /= 10;
}
buffer[digits + isNegative] = '\0';
write(1, buffer, digits + isNegative);
count += digits + isNegative;
break;
}

            case 'o': {
                    unsigned int val = va_arg(args, unsigned int);
                    int digits = 1;
                    unsigned int k = val;
                    while (k > 7) {
                        digits++;
                        k /= 8;
                    }
                    for (j = digits-1; j >= 0; j--) {
                        buffer[j] = (val % 8) + '0';
                        val /= 8;
                    }
                    write(1, buffer, digits);
                    count += digits;
                    count += 1;
                    break;
                }
            case 'u': {
                unsigned int val = va_arg(args, unsigned int);
                int digits = 1;
                for (unsigned int k = val/10; k!=0; k/=10) {
                    digits++;
                }
                for (j = digits-1; j >= 0; j--) {
                    buffer[j] = (val % 10) + '0';
                    val /= 10;
                }
                write(1, buffer, digits);
                count += digits;
                count += 1;
                break;
            }
            case 'x': {
                    unsigned int val = va_arg(args, unsigned int);
                    int digits = 1;
                    for (unsigned int k = val / 16; k != 0; k /= 16) {
                        digits++;
                    }
                    for (j = digits - 1; j >= 0; j--) {
                        unsigned int digit = val % 16;
                        if (digit < 10) {
                            buffer[j] = digit + '0';
                        } else {
                            buffer[j] = digit - 10 + 'A';
                        }
                        val /= 16;
                    }
                    write(1, buffer, digits);
                    count += digits;
                    count += 1;
                    break;
                }
            case 'p': {
void* val = va_arg(args, void*);
unsigned long num = (unsigned long)val;
char hex_digits[] = "0123456789abcdef";
buffer[0]='0';
buffer[1]='x';
            int digits = 1;
            for (unsigned long k = num/16; k!=0; k/=16) {
                digits++;
            }
            int i = 2 + digits;
            for (int j = 0; j < digits; j++) {
                buffer[--i] = hex_digits[num % 16];
                num /= 16;
            }
            write(1, buffer, digits+2);
            count = digits+2;
            break;
        }


            
            
                
            default:
                buffer[0]='%';
                buffer[1]=format[i];
                j=2;
                break;
        }
        count += write(1, buffer, j);
    } else {
        count += write(1, &format[i], 1);
    }
}

va_end(args);
return count;
}
