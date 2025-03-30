//main.c

#include "ft_dict.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>  // Adicione esta linha

#include "ft_dict.h"

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 3)
    {
        write(2, "Error\n", 6);
        return 1;
    }

    t_dict *dict;
    unsigned long num;

    if (argc == 2)
    {
        num = ft_atoi(argv[1]);  // Usa a nova ft_atoi
        if (num == 0 && strcmp(argv[1], "0") != 0)
        {
            write(2, "Error\n", 6);
            return 1;
        }
        dict = parse_dictionary("numbers.dict");
    }
    else
    {
        dict = parse_dictionary(argv[1]);
        num = ft_atoi(argv[2]);
        if (num == 0 && strcmp(argv[2], "0") != 0)
            dict_error(dict);
    }

    print_number(dict, num);  // Chama a função de impressão
    write(1, "\n", 1);
    free_dict(dict);
    return 0;
}
