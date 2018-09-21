#ifndef POLY_H
#define POLY_H
#include <stdbool.h>

typedef struct term
{
    int coeff;
    unsigned exp;
    struct term *next;
} term, polynomial;

term *term_create(int coeff, unsigned exp);
void poly_destroy(polynomial *eqn);
void poly_print(const polynomial *eqn);

char *poly_to_string(const polynomial *p);
void poly_iterate(polynomial *p, void (*transform)(term *));
bool poly_equal(const polynomial *a, const polynomial *b);
double poly_eval(const polynomial *p, double x);
polynomial *poly_add(const polynomial *a, const polynomial *b);
polynomial *poly_sub(const polynomial *a, const polynomial *b);

int count_unique(const polynomial *a, const polynomial *b);
int *get_vals(const polynomial *a);
polynomial *array_sum(int *a_array, int *b_array, int num_of_unique);
polynomial *array_diff(int *a_array, int *b_array, int num_of_unique);

#endif
