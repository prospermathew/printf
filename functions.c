0x11 C printf
README.md


0x11. C - printf team project


Group Project:                                                                      

                                                                                   

0. I'm not going anywhere. You can print that wherever you want to. I'm here and I'm

 a Spur for life                                                                    

Write a function that produces output according to a format.                        

                                                                                   

                                                                                   

1. Education is when you read the fine print. Experience is what you get if you don'

t                                                                                  

Handle the following conversion specifiers:


2. With a face like mine, I do better in print                                      

Handle the following custom conversion specifiers:                                  

                                                                                   

3. What one has not experienced, one will never understand in print                

Handle the following conversion specifiers:                                        

                                                                                   

4. Nothing in fine print is ever good news                                          

Use a local buffer of 1024 chars in order to call write as little as possible.      

                                                                                   

5. My weakness is wearing too much leopard print                                    

Handle the following custom conversion specifier:                                  

                                                                                   

6. How is the world ruled and led to war? Diplomats lie to journalists and believe t

hese lies when they see them in print                                              

Handle the following conversion specifier: p.                                      

                                                                                   

7. The big print gives and the small print takes away                              

Handle the following flag characters for non-custom conversion specifiers:          

                                                                                   

8. Sarcasm is lost in print                                                        

Handle the following length modifiers for non-custom conversion specifiers:        

                                                                                   

l                                                                                  

h                                                                                  

Conversion specifiers to handle: d, i, u, o, x, X                                  

                                                                                   

9. Print some money and give it to us for the rain forests                          

Handle the field width for non-custom conversion specifiers.                        

                                                                                   

10. The negative is the equivalent of the composer's score, and the print the perfor

mance                                                                              

Handle the precision for non-custom conversion specifiers.                          

                                                                                   

11. It's depressing when you're still around and your albums are out of print      

Handle the 0 flag character for non-custom conversion specifiers.                  

                                                                                   

12. Every time that I wanted to give up, if I saw an interesting textile, print what

 ever, suddenly I would see a collection                                            

Handle the - flag character for non-custom conversion specifiers.                  

                                                                                   

13. Print is the sharpest and the strongest weapon of our party                    

Handle the following custom conversion specifier:                                  

                                                                                   

14. The flood of print has turned reading into a process of gulping rather than savo

ring                                                                                

Handle the following custom conversion specifier:                                  

                                                                                   

15. *                                                                              

All the above options work well together.



========================================


_printf.c CODE



#include "main.h"


void print_buffer(char buffer[], int *buff_ind);


/**

 * _printf - Printf function

 * @format: format.

 * Return: Printed chars.

 */

int _printf(const char *format, ...)

{

        int i, printed = 0, printed_chars = 0;

        int flags, width, precision, size, buff_ind = 0;

        va_list list;

        char buffer[BUFF_SIZE];


        if (format == NULL)

                return (-1);


        va_start(list, format);


        for (i = 0; format && format[i] != '\0'; i++)

        {

                if (format[i] != '%')

                {

                        buffer[buff_ind++] = format[i];

                        if (buff_ind == BUFF_SIZE)

                                print_buffer(buffer, &buff_ind);

                        /* write(1, &format[i], 1);*/

                        printed_chars++;

                }

                else

                {

                        print_buffer(buffer, &buff_ind);

                        flags = get_flags(format, &i);

                        width = get_width(format, &i, list);

                        precision = get_precision(format, &i, list);

                        size = get_size(format, &i);

                        ++i;

                        printed = handle_print(format, &i, list, buffer,

                                flags, width, precision, size);

                        if (printed == -1)

                                return (-1);

                        printed_chars += printed;

                }

        }


        print_buffer(buffer, &buff_ind);


        va_end(list);


        return (printed_chars);

}


/**

 * print_buffer - Prints the contents of the buffer if it exist

 * @buffer: Array of chars

 * @buff_ind: Index at which to add next char, represents the length.

 */

void print_buffer(char buffer[], int *buff_ind)

{

        if (*buff_ind > 0)

                write(1, &buffer[0], *buff_ind);


        *buff_ind = 0;

}


======================================


functions.c CODE



#include "main.h"


/************************* PRINT CHAR *************************/


/**

 * print_char - Prints a char

 * @types: List a of arguments

 * @buffer: Buffer array to handle print

 * @flags:  Calculates active flags

 * @width: Width

 * @precision: Precision specification

 * @size: Size specifier

 * Return: Number of chars printed

 */

int print_char(va_list types, char buffer[],

        int flags, int width, int precision, int size)

{

        char c = va_arg(types, int);


        return (handle_write_char(c, buffer, flags, width, precision, size));

}

/************************* PRINT A STRING *************************/

/**

 * print_string - Prints a string

 * @types: List a of arguments

 * @buffer: Buffer array to handle print

 * @flags:  Calculates active flags

 * @width: get width.

 * @precision: Precision specification

 * @size: Size specifier

 * Return: Number of chars printed

 */

int print_string(va_list types, char buffer[],

        int flags, int width, int precision, int size)

{

        int length = 0, i;

        char *str = va_arg(types, char *);


        UNUSED(buffer);

        UNUSED(flags);

        UNUSED(width);

        UNUSED(precision);

        UNUSED(size);

        if (str == NULL)

        {

                str = "(null)";

                if (precision >= 6)

                        str = "      ";

        }


        while (str[length] != '\0')

                length++;


        if (precision >= 0 && precision < length)

                length = precision;


        if (width > length)

        {

                if (flags & F_MINUS)

                {

                        write(1, &str[0], length);

                        for (i = width - length; i > 0; i--)

                                write(1, " ", 1);

                        return (width);

                }

                else

                {

                        for (i = width - length; i > 0; i--)

                                write(1, " ", 1);

                        write(1, &str[0], length);

                        return (width);

                }

        }


        return (write(1, str, length));

}

/************************* PRINT PERCENT SIGN *************************/

/**

 * print_percent - Prints a percent sign

 * @types: Lista of arguments

 * @buffer: Buffer array to handle print

 * @flags:  Calculates active flags

 * @width: get width.

 * @precision: Precision specification

 * @size: Size specifier

 * Return: Number of chars printed

 */

int print_percent(va_list types, char buffer[],

        int flags, int width, int precision, int size)

{

        UNUSED(types);

        UNUSED(buffer);

        UNUSED(flags);

        UNUSED(width);

        UNUSED(precision);

        UNUSED(size);

        return (write(1, "%%", 1));

}


/************************* PRINT INT *************************/

/**

 * print_int - Print int

 * @types: Lista of arguments

 * @buffer: Buffer array to handle print

 * @flags:  Calculates active flags

 * @width: get width.

 * @precision: Precision specification

 * @size: Size specifier

 * Return: Number of chars printed

 */

int print_int(va_list types, char buffer[],

        int flags, int width, int precision, int size)

{

        int i = BUFF_SIZE - 2;

        int is_negative = 0;

        long int n = va_arg(types, long int);

        unsigned long int num;


        n = convert_size_number(n, size);


        if (n == 0)

                buffer[i--] = '0';


        buffer[BUFF_SIZE - 1] = '\0';

        num = (unsigned long int)n;


        if (n < 0)

        {

                num = (unsigned long int)((-1) * n);

                is_negative = 1;

        }


        while (num > 0)

        {

                buffer[i--] = (num % 10) + '0';

                num /= 10;

        }


        i++;


        return (write_number(is_negative, i, buffer, flags, width, precision, size));

}


/************************* PRINT BINARY *************************/

/**

 * print_binary - Prints an unsigned number

 * @types: Lista of arguments

 * @buffer: Buffer array to handle print

 * @flags:  Calculates active flags

 * @width: get width.

 * @precision: Precision specification

 * @size: Size specifier

 * Return: Numbers of char printed.

 */

int print_binary(va_list types, char buffer[],

        int flags, int width, int precision, int size)

{

        unsigned int n, m, i, sum;

        unsigned int a[32];

        int count;


        UNUSED(buffer);

        UNUSED(flags);

        UNUSED(width);

        UNUSED(precision);

        UNUSED(size);


        n = va_arg(types, unsigned int);

        m = 2147483648; /* (2 ^ 31) */

        a[0] = n / m;

        for (i = 1; i < 32; i++)

        {

                m /= 2;

                a[i] = (n / m) % 2;

        }

        for (i = 0, sum = 0, count = 0; i < 32; i++)

        {

                sum += a[i];

                if (sum || i == 31)

                {

                        char z = '0' + a[i];


                        write(1, &z, 1);

                        count++;

                }

        }

        return (count);

}
