#ifndef S21_CAT_H
#define S21_CAT_H

typedef struct {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
    int T;
} options;

int parse(options *opt, char *str);
void print_file(options opt, char *file_name);
void print_unprinted(options opt, int c);
void print_char(options opt, int c);

#endif // S21_CAT_H