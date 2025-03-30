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
    // Casos básicos (0-20, dezenas redondas, 100, 1000, magnitudes maiores)
    if (num <= 20 || num == 30 || num == 40 || num == 50 || 
        num == 60 || num == 70 || num == 80 || num == 90 || 
        num == 100 || num == 1000 || num == 1000000 || num == 1000000000 ||
        num == 1000000000000 || num == 1000000000000000 || num == 1000000000000000000
       )
    {
        char *word = get_word(dict, num);
        if (!word) dict_error(dict);
        write(1, word, strlen(word));
        return;
    }
    
    // Números 21-99
    if (num < 100)
    {
        print_number(dict, (num / 10) * 10);
        write(1, "-", 1);
        print_number(dict, num % 10);
        return;
    }
    
    // Centenas (101-999)
    if (num < 1000)
    {
        print_number(dict, num / 100);
        write(1, " ", 1);
        print_number(dict, 100);
        if (num % 100 != 0)
        {
            write(1, " and ", 5);
            print_number(dict, num % 100);
        }
        return;
    }

    // Array de magnitudes (mil, milhão, bilhão, etc.)
    static const struct {
        unsigned long magnitude;
        const char *name;
    } magnitudes[] = {
        {1000000000000000000, "sextillion"},
        {1000000000000000, "quintillion"},
        {1000000000000, "quadrillion"},
        {1000000000, "billion"},
        {1000000, "million"},
        {1000, "thousand"},
        {0, NULL}
    };

    // Processa números grandes (>= 1000)
    for (int i = 0; magnitudes[i].magnitude != 0; i++) {
        if (num >= magnitudes[i].magnitude) {
            unsigned long big_part = num / magnitudes[i].magnitude;
            unsigned long small_part = num % magnitudes[i].magnitude;
            
            print_number(dict, big_part);
            write(1, " ", 1);
            write(1, magnitudes[i].name, strlen(magnitudes[i].name));
            
            if (small_part != 0) {
                write(1, " ", 1);
                print_number(dict, small_part);
            }
            return;
        }
    }
}
