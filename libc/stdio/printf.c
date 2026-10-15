#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, int amount){
    for(size_t i=0;i<amount;i++){
        if(putchar(data[i])==EOF){
            return false;
        }
    }
    return true;
}

static int print_Int(int data){
    unsigned int number;

    if(data < 0){
        if(putchar('-') == EOF){
            return -1;
        }
        number = 0u - (unsigned int)data;
    } else {
        number = (unsigned int)data;
    }

    char digits[sizeof(unsigned int) * CHAR_BIT];
    int count = 0;

    if(number == 0){
        digits[count++] = '0';
    }

    while(number > 0){
        digits[count++] = '0' + (number % 10);
        number /= 10;
    }

    while(count > 0){
        if(putchar(digits[--count]) == EOF){
            return -1;
        }
    }

    return 0;
}

static int print_Hex(unsigned int number){
    char digits[sizeof(unsigned int) * CHAR_BIT];
    int count = 0;

    if(number == 0){
        digits[count++] = '0';
    }

    while(number > 0){
        unsigned int digit = number % 16;

        if(digit < 10){
            digits[count++] = '0' + digit;
        } else {
            digits[count++] = 'a' + (digit - 10);
        }

        number /= 16;
    }

    while(count > 0){
        if(putchar(digits[--count]) == EOF){
            return -1;
        }
    }

    return 0;
}

int printf(const char* __restrict buffer, ...){
    va_list arguments;
    va_start(arguments,buffer);
    int counter=0;
    int printed=0;
    int size=sizeof(buffer);
    while(buffer[counter]!='\0'){
        int amount=0;
        if(buffer[counter]!='%'){
            while (buffer[counter+amount]!='%' && buffer[counter+amount]!='\0') {
                amount++;
            }
            if(!print(&buffer[counter],amount)){
                //reached EOF
                return -1;
            }
            printed+=amount;
            counter+=amount;
            continue;
        }

        switch (buffer[++counter]) {
            case '\0': {
                //Ends with %
                va_end(arguments);
                return -1;
                break;
            }
            case 's': {
                const char* str=va_arg(arguments,const char*);
                int len=strlen(str);
                if(!print(str, len)){
                    return -1;
                }
                printed+=len;
                break;
            }
            case 'd': {
                int number = va_arg(arguments, int);

                if(print_Int(number) == -1){
                    va_end(arguments);
                    return -1;
                }

                printed += number == 0 ? 1 : 0;

                unsigned int temp = number < 0
                    ? 0u - (unsigned int)number
                    : (unsigned int)number;

                while(temp > 0){
                    printed++;
                    temp /= 10;
                }

                if(number < 0){
                    printed++;
                }

                break;
            }
            case 'x': {
                unsigned int number = va_arg(arguments, unsigned int);

                if(print_Hex(number) == -1){
                    va_end(arguments);
                    return -1;
                }

                if(number == 0){
                    printed++;
                }

                while(number > 0){
                    printed++;
                    number /= 16;
                }

                break;
            }
            case 'c':{
                const char c=(char)va_arg(arguments,int);
                if(!print(&c, 1)){
                    return -1;
                }
                printed+=1;
                break;
            }
            case '%': {
                const char c='%';
                if(!print(&c, 1)){
                    return -1;
                }
                printed+=1;
                break;
            }
            default:{
                printf("This has not been implemented");
                return -1;
            }
        }
        counter++;
    }
    va_end(arguments);
    return printed;
}
