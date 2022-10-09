#ifndef S21_GREP_H
#define S21_GREP_H

typedef struct {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} options;

typedef struct {
    int str_i;
    char patterns[128][128];
    int pat_n;
    int pat_i;
    char files[128][128];
    int file_n;
    int file_i;
} params;

void init_params(params *p);
void parse(params *p, options *o, char *str, int *is_e, int *is_f);
void read_pattern(params *p, options o, char *file_name);
void grep_file(params *p, options o);
int grep_str(params *p, options o, char *str);
int exec_pattern(params *p, options o, char *str);

#endif // S21_GREP_H