#ifndef ARGSBUF_H
#define ARGSBUF_H

#include <stdlib.h>
#include <string.h>

typedef struct argsbuf {
    char **args;
    int len;
} argsbuf;

void ab_append(argsbuf *ab, char *arg) {
    ab->args = (char**)realloc(ab->args, sizeof(char*) * ++(ab->len));
    ab->args[ab->len - 1] = (char*)malloc(strlen(arg));
    memcpy(ab->args[ab->len - 1], arg, strlen(arg));
}

void ab_free(argsbuf *ab) {
    for (int i = 0; i < ab->len; i++) free(ab->args[i]);
    free(ab->args);
}

#endif