#include "ft_dict.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void dict_error(t_dict *dict) {
    if (dict) free_dict(dict);
    write(2, "Dict Error\n", 11);
    exit(1);
}

unsigned long parse_number(const char *str) {
    unsigned long num = 0;
    while (*str >= '0' && *str <= '9') {
        num = num * 10 + (*str - '0');
        str++;
    }
    return (*str == '\0') ? num : 0;
}

char *trim_whitespace(char *str) {
    while (*str == ' ' || *str == '\t') str++;
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) end--;
    *(end + 1) = '\0';
    return str;
}

t_dict *parse_dictionary(const char *filename) {
    t_dict *dict = malloc(sizeof(t_dict));
    if (!dict) dict_error(NULL);
    dict->head = NULL;

    int fd = open(filename, O_RDONLY);
    if (fd == -1) dict_error(dict);

    char buffer[4096];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    if (bytes_read <= 0) dict_error(dict);
    buffer[bytes_read] = '\0';

    char *line = strtok(buffer, "\n");
    while (line) {
        line = trim_whitespace(line);
        if (*line && *line != '#') {
            char *colon = strchr(line, ':');
            if (!colon) dict_error(dict);

            *colon = '\0';
            unsigned long num = parse_number(trim_whitespace(line));
            char *text = trim_whitespace(colon + 1);

            if (!num && *line != '0') dict_error(dict);

            t_node *new = malloc(sizeof(t_node));
            if (!new) dict_error(dict);
            new->number = num;
            new->text = strdup(text);
            if (!new->text) dict_error(dict);
            new->next = dict->head;
            dict->head = new;
        }
        line = strtok(NULL, "\n");
    }
    return dict;
}

char *get_word(t_dict *dict, unsigned long num) {
    t_node *current = dict->head;
    while (current) {
        if (current->number == num)
            return current->text;
        current = current->next;
    }
    return NULL;
}

void free_dict(t_dict *dict) {
    t_node *current = dict->head;
    while (current) {
        t_node *next = current->next;
        free(current->text);
        free(current);
        current = next;
    }
    free(dict);
}
