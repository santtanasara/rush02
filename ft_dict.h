#ifndef FT_DICT_H
#define FT_DICT_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_node {
    unsigned long number;
    char *text;
    struct s_node *next;
} t_node;

typedef struct s_dict {
    t_node *head;
} t_dict;

// Funções do dicionário
t_dict *parse_dictionary(const char *filename);
char *get_word(t_dict *dict, unsigned long num);
void free_dict(t_dict *dict);
void dict_error(t_dict *dict);

// Funções de conversão (agora declaradas aqui)
unsigned long ft_atoi(const char *str);
void print_number(t_dict *dict, unsigned long num);

#endif
