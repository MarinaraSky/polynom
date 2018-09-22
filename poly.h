#ifndef POLY_H
#define POLY_H
#include <stdbool.h>

typedef struct term
{
    int coeff;
    unsigned exp;
    struct term *next;
} term, polynomial;

/* Creates a new term and returns a term* */
term *term_create(int coeff, unsigned exp);
/* Frees an entire polynomial recursively */
void poly_destroy(polynomial *eqn);
/* Prints an entire polynomial expression */
void poly_print(const polynomial *eqn);

/* Returns new string to display polynomial */
char *poly_to_string(const polynomial *p);
/* Calls function transform on each term in polynomial */
void poly_iterate(polynomial *p, void (*transform)(term *));
/* Returns true if the two arguments have the same terms, false otherwise */
bool poly_equal(const polynomial *a, const polynomial *b);
/* Evaluates the polynomial by subsituting x  */
double poly_eval(const polynomial *p, double x);
/* Returns new polynomial* to the sum of the arguments */
polynomial *poly_add(const polynomial *a, const polynomial *b);
/* Returns new polynomial* to the difference of the arguments */
polynomial *poly_sub(const polynomial *a, const polynomial *b);
/* Returns new polynomial* to the product of the arguments */
polynomial *poly_mult(const polynomial *a, const polynomial *b);
/* Returns new polynomial* to the product of the argument to the e power */
polynomial *poly_pow(const polynomial *a, unsigned e);

#endif
