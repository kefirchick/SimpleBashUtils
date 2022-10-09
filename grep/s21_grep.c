#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <pcre.h>
#include "s21_grep.h"

int main(int argc, char **argv) {
    params p;
    init_params(&p);
    options o = {0};
    int is_e = 1;
    int is_f = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            parse(&p, &o, argv[i], &is_e, &is_f);
        }
    }

    while (p.file_i < p.file_n) {
        grep_file(&p, o);
        p.file_i++;
    }

    return 0;
}

void init_params(params *p) {
    p->str_i = 0;
    p->pat_i = 0;
    p->pat_n = 0;
    p->file_i = 0;
    p->file_n = 0;
    for (int i = 0; i < 128; i++)
        for (int j = 0; j < 128; j++) {
            p->patterns[i][j] = 0;
            p->files[i][j] = 0;
        }
}

void parse(params *p, options *o, char *str, int *is_e, int *is_f) {
    if (str[0] == '-') {
        if ( strchr(str, 'e') ) {
            o->e = 1;
            *is_e = 1;
        }
        if ( strchr(str, 'i') ) o->i = 1;
        if ( strchr(str, 'v') ) o->v = 1;
        if ( strchr(str, 'c') ) o->c = 1;
        if ( strchr(str, 'l') ) o->l = 1;
        if ( strchr(str, 'n') ) o->n = 1;
        if ( strchr(str, 'h') ) o->h = 1;
        if ( strchr(str, 's') ) o->s = 1;
        if ( strchr(str, 'f') ) {
            o->f = 1;
            *is_f = 1;
        }
        if ( strchr(str, 'o') ) o->o = 1;
    } else if (*is_f) {
        read_pattern(p, *o, str);
        *is_f = 0;
        *is_e = 0;
    } else if (*is_e) {
        strcpy(p->patterns[p->pat_n++], str);
        *is_f = 0;
        *is_e = 0;
    } else {
        strcpy(p->files[p->file_n++], str);
    }
}

void read_pattern(params *p, options o, char *file_name) {
    FILE *fp = NULL;
    char str[1024];

    if ((fp = fopen(file_name, "r"))) {
        while ( fgets(str, 1024, fp) ) {
            if ( strchr(str, '\n') ) *strchr(str, '\n') = '\0';
            strcpy(p->patterns[p->pat_n++], str);
        }

        fclose(fp);
    } else {
        if (!o.s) fprintf (stderr, "File open failed: %s.\n", str);
    }
}

void grep_file(params *p, options o) {
    FILE *fp = NULL;

    if ((fp = fopen(p->files[p->file_i], "r"))) {
        int count = 0;
        char str[1024];
        p->str_i = 1;

        while (fgets(str, 1024, fp)) {
            count += grep_str(p, o, str);
            p->str_i++;
        }

        if (o.l && count) {
            printf("%s\n", p->files[p->file_i]);
        } else if (o.c && count) {
            printf("%s:%d\n", p->files[p->file_i], count);
        }

        fclose(fp);
    } else {
        if (!o.s) fprintf (stderr, "File open failed: %s.\n", p->files[p->file_i]);
    }
}

int grep_str(params *p, options o, char *str) {
    int result = 0;
    p->pat_i = 0;

    while (p->pat_i < p->pat_n) {
        result += exec_pattern(p, o, str);
        p->pat_i++;
    }

    if (o.v) result = !result;
    if (result && !o.c && !o.l && !o.o) {
        if (!o.h && p->file_n > 1) printf("%s:", p->files[p->file_i]);
        if (o.n) printf("%d:", p->str_i);
        printf("%s", str);
        if (str[strlen(str)-1] != '\n') putchar('\n');
    }

    return result;
}

int exec_pattern(params *p, options o, char *str) {
    int result = 0;
    pcre *re;
    const char *error;
    int erroffset;
    int options = (o.i) ? PCRE_CASELESS : 0;

    re = pcre_compile(p->patterns[p->pat_i], options, &error, &erroffset, NULL);

    if (!re) {
        fprintf(stderr, "Pattern error: %s.\n", p->patterns[p->pat_i]);
    } else {
        int count = 0;
        int ovector[30];

        count = pcre_exec(re, NULL, (char *)str, strlen(str), 0, 0, ovector, 30);

        if (count > 0) result = count;

        if (o.o && !o.c && !o.l && count > 0) {
            for (int i = 0; i < count * 2; i += 2) {
                if (!o.h && p->file_n > 1) printf("%s:", p->files[p->file_i]);
                if (o.n) printf("%d:", p->str_i);

                for (int j = ovector[i]; j < ovector[i+1]; j++)
                    putchar(str[j]);

                printf("\n");
            }
        }
    }

    pcre_free((void *) re);

    return result;
}
