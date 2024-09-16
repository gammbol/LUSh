#ifndef LUSH_H
#define LUSH_H

#define BUFSIZE 4096

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "argsbuf.h"

typedef struct userinfo {
    char hostname[1024];
    char username[1024];
} userinfo;

void lush_init();
void lush_loop();
char *lush_input();
argsbuf *lush_parse(char *com);
void lush_exec(argsbuf *args);

#endif