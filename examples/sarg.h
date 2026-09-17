#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* s;
    char* l;
    int n;
    void (*f)(char** argv);
    void (*e)(char *opt);
    char* d;
} Option;

typedef struct {
    char* n;
    void (*f)(char* argv);
    char* d;
} Argument;

typedef struct {
    enum { OPT, ARG } kind;
    union {
        Option     o;
        Argument p;
    };
} Entry;

typedef struct {
    Entry *args;
    int    argc;
    char  *descript;
} Entries;

static inline void args_help(const char *prog, const Entries *opts) {
    if (opts->descript)
        printf("%s\n\n", opts->descript);

    printf("Usage: %s", prog);
    int has_opt = 0;
    for (int i = 0; i < opts->argc; ++i)
        if (opts->args[i].kind == OPT) { has_opt = 1; break; }
    if (has_opt) printf(" [OPTION...]");
    for (int i = 0; i < opts->argc; ++i) {
        if (opts->args[i].kind == ARG)
            printf(" %s", opts->args[i].p.n);
    }
    printf("\n\n");

    if (has_opt) {
        printf("Options :\n");
        for (int i = 0; i < opts->argc; ++i) {
            if (opts->args[i].kind != OPT) continue;
            const Option *o = &opts->args[i].o;

            printf("  ");
            if (o->s && o->l)      printf("%s, %s", o->s, o->l);
            else if (o->s)         printf("    %s", o->s);
            else                   printf("        ");

            for (int k = 0; k < o->n; ++k) printf(" VALEUR");

            if (o->d) printf("\n        %s", o->d);
            printf("\n");
        }
        printf("      --help\n        Affiche cette aide et quitte\n");
    }

    int has_pos = 0;
    for (int i = 0; i < opts->argc; ++i)
        if (opts->args[i].kind == ARG) { has_pos = 1; break; }
    if (has_pos) {
        printf("\nArguments :\n");
        for (int i = 0; i < opts->argc; ++i) {
            if (opts->args[i].kind != ARG) continue;
            const Argument *p = &opts->args[i].p;
            printf("  %s", p->n);
            if (p->d) printf("\n        %s", p->d);
            printf("\n");
        }
    }
}

static inline int args_parse(int argc, char **argv, const Entries *opts) {
    int next_pos = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            args_help(argv[0], opts);
            return 1;
        }

        if (argv[i][0] != '-' || argv[i][1] == '\0') {
            while (next_pos < opts->argc && opts->args[next_pos].kind != ARG)
                ++next_pos;

            if (next_pos >= opts->argc) {
                fprintf(stderr,
                        "\033[31;1mErreur\033[0m : argument inattendu « %s ».\n",
                        argv[i]);
                return -1;
            }

            const Argument *p = &opts->args[next_pos].p;
            if (p->f) p->f(argv[i]);
            ++next_pos;
            continue;
        }

        int found = 0;
        for (int k = 0; k < opts->argc; ++k) {
            if (opts->args[k].kind != OPT) continue;
            const Option *o = &opts->args[k].o;

            if ((o->s && strcmp(argv[i], o->s) == 0) ||
                (o->l && strcmp(argv[i], o->l) == 0)) {

                if (i + o->n >= argc) {
                    if (o->e) o->e(argv[i]);
                    else fprintf(stderr,
                                 "\033[31;1mErreur\033[0m : %s attend %d valeur(s).\n",
                                 argv[i], o->n);
                    return -1;
                }

                if (o->f) o->f(&argv[i + 1]);
                i += o->n;
                found = 1;
                break;
            }
        }

        if (!found) {
            fprintf(stderr,
                    "\033[31;1mErreur\033[0m : option inconnue « %s ».\n",
                    argv[i]);
            return -1;
        }
    }
    return 0;
}