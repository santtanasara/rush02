#include "ft_dict.h"
#include <unistd.h>
#include <string.h>

// Função personalizada para converter string para número (como atoi)
unsigned long ft_atoi(const char *str)
{
    unsigned long num = 0;
    
    while (*str >= '0' && *str <= '9')
    {
        num = num * 10 + (*str - '0');
        str++;
    }
    return num;
}

// Função principal que converte e imprime números compostos
void print_number(t_dict *dict, unsigned long num)
{
    if (num <= 20 || num == 30 || num == 40 || num == 50 || 
        num == 60 || num == 70 || num == 80 || num == 90 || 
        num == 100 || num >= 1000)
    {
        char *word = get_word(dict, num);
        if (!word) dict_error(dict);
        write(1, word, strlen(word));
        return;
    }
    
    // Números 21-99
    if (num < 100)
    {
        print_number(dict, (num / 10) * 10); // Dezena (40)
        write(1, "-", 1);
        print_number(dict, num % 10);       // Unidade (2)
        return;
    }
    
    // Centenas (101-999)
    if (num < 1000)
    {
        print_number(dict, num / 100);      // Centena (1)
        write(1, " ", 1);
        print_number(dict, 100);            // "hundred"
        if (num % 100 != 0)
        {
            write(1, " and ", 5);
            print_number(dict, num % 100);  // Resto (23)
        }
        return;
    }
    

        // Centenas (1000-100000)
    if (num < 1000000)
    {
        print_number(dict, num / 1000);      // Centena (1)
        write(1, " ", 1);
        print_number(dict, 1000);            // "hundred"
        if (num % 1000 != 0)
        {
            write(1, " and ", 6);
            print_number(dict, num % 1000);  // Resto (23)
        }
        return;
    }
    // Números maiores (milhares, milhões...)
    // ... (implementação similar para magnitudes maiores)
}
