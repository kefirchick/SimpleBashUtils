#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "s21_cat.h"

int main(int argc, char **argv) {
    options opt = {0, 0, 0, 0, 0, 0, 0, 0};

    if (argc > 1) {
        int i = 1;
        while (i < argc && parse(&opt, argv[i]))
            i++;
        while (i < argc) {
            print_file(opt, argv[i]);
            i++;
        }
    }

    return 0;
}

int parse(options *opt, char *str) {
    int result = 1;

    if (str[0] == '-' && str[1] == '-') {
        if (strstr(str, "number-nonblank"))
            opt->b = 1;
        if (strstr(str, "number"))
            opt->n = 1;
        if (strstr(str, "squeeze-blank"))
            opt->s = 1;
    } else if (str[0] == '-') {
        if (strchr(str, 'b'))
            opt->b = 1;
        if (strchr(str, 'e'))
            opt->e = 1;
        if (strchr(str, 'n'))
            opt->n = 1;
        if (strchr(str, 's'))
            opt->s = 1;
        if (strchr(str, 't'))
            opt->t = 1;
        if (strchr(str, 'v'))
            opt->v = 1;
        if (strchr(str, 'E'))
            opt->E = 1;
        if (strchr(str, 'T'))
            opt->T = 1;
    } else {
        result = 0;
    }

    return result;
}

void print_file(options opt, char *file_name) {
    FILE *fp = NULL;
    int c = 0;
    int prev_c = '\n';
    int count = 1;
    int is_squeeeze = 0;

    if ((fp = fopen(file_name, "r"))) {
        while ((c = getc(fp)) != EOF) {
            if (opt.s && c == '\n' && is_squeeeze)
                continue;
            is_squeeeze = (prev_c == '\n' && c == '\n') ? 1 : 0;

            if (opt.n && prev_c == '\n') {
                for (int i = 5; i > count/pow(10, i); i--) putchar(' ');
                printf("%d%c", count++, 9);
                print_unprinted(opt, c);
            } else if (opt.b && prev_c == '\n' && c != '\n') {
                for (int i = 5; i > count/pow(10, i); i--) putchar(' ');
                printf("%d%c", count++, 9);
                print_unprinted(opt, c);
            } else {
                print_unprinted(opt, c);
            }

            prev_c = c;
        }

        fclose(fp);
    } else {
        fprintf(stderr, "File open failed: %s.\n", file_name);
    }
}

void print_unprinted(options opt, int c) {
    if (opt.v || opt.e || opt.t) {
        if (c < 32 && c != 9 && c != 10) {
            printf("^%c", c + 64);
        } else if (c == 127) {
            printf("^?");
        } else if (c > 127 && c < 160) {
            printf("M-^%c", c - 64);
        } else if (c >= 160 && c != 255) {
            printf("M-%c", c - 128);
        } else if (c == 255) {
            printf("M-^?");
        } else {
            print_char(opt, c);
        }
    } else {
        print_char(opt, c);
    }
}

void print_char(options opt, int c) {
    if ((opt.t || opt.T) && c == 9) {
        printf("^I");
    } else if ((opt.e || opt.E) && c == '\n') {
        printf("$\n");
    } else {
        putchar(c);
    }
}
