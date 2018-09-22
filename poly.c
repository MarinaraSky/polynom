#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poly.h"

/* Counts how many unique exponents there are in both polynomials */
static int *count_unique(const polynomial *a, const polynomial *b);
/* Returns array of coeffs where the position in the array is the power */
static int *get_vals(const polynomial *a);
/* Addition of two coeff arrays and returns the polynomial */
static polynomial *array_sum(int *a_array, int *b_array, int *num_of_unique, int max_x);
/* Subtraction of two coeff arrays and returns the polynomial */
static polynomial *array_diff(int *a_array, int *b_array, int *num_of_unique, int max_x);
/* Finds the highest value of x in either polynomials for arrays */
static int get_high_x(const polynomial *a, const polynomial *b);
/* Prints polynomial as text to file for easy read in as string */
static void poly_file_print(const polynomial *eqn, FILE *hide_me);

term *term_create(int coeff, unsigned exp)
{
    term *node = malloc(sizeof(*node));
    if(node)
    {
        node->coeff = coeff;
        node->exp = exp;
        node->next = NULL;
    }
    return node;
}

void poly_destroy(polynomial *eqn)
{
    while(eqn)
    {
        term *tmp = eqn->next;
        free(eqn);
        eqn = tmp;
    }
}

static int first = 0;
void poly_print(const polynomial *eqn)
{
    
    if(!eqn)
    {
        first = 0;
        return;
    }
    if(eqn->coeff)
    {
        if(first == 0)
        {
            printf("%d", eqn->coeff);
            first++;
        }
        else
        {
            if(eqn->coeff > 0)
            {
                printf("+%d", eqn->coeff); 
            }
            else
            {
                printf("%d", eqn->coeff); 
            
            }
        }
        if(eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if(eqn->exp == 1)
        {
           printf("x"); 
        }
    }
    poly_print(eqn->next);
}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    int *count = count_unique(a, b);
    int *values_of_a = get_vals(a);
    int *values_of_b = get_vals(b);
    int max_x = get_high_x(a, b);

    polynomial *sum_of_poly = array_sum(values_of_a, values_of_b, count, max_x); 

    free(values_of_a);
    free(values_of_b);
    return sum_of_poly;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    int *count = count_unique(a, b);
    int *values_of_a = get_vals(a);
    int *values_of_b = get_vals(b);
    int max_x = get_high_x(a, b);

    polynomial *diff_of_poly = array_diff(values_of_a, values_of_b, count, max_x); 

    free(values_of_a);
    free(values_of_b);
    return diff_of_poly;

}

bool poly_equal(const polynomial *a, const polynomial *b)
{
    const polynomial *tmp_a = a;
    const polynomial *tmp_b = b;

    while(tmp_a != NULL)
    {
        if(tmp_a->coeff != tmp_b->coeff || tmp_a->exp != tmp_b->exp)
        {
            return false;
        }
        if(tmp_b->next == NULL && tmp_a->next != NULL)
        {
            return false;
        }
        tmp_a = tmp_a->next;
        tmp_b = tmp_b->next; 
    }
    tmp_a = a;
    tmp_b = b;
    while(tmp_b != NULL)
    {
        if(tmp_b->coeff != tmp_a->coeff || tmp_b->exp != tmp_a->exp)
        {
            return false;
        }
        if(tmp_a->next == NULL && tmp_b->next != NULL)
        {
            return false;
        }
        tmp_b = tmp_b->next;
        tmp_a = tmp_a->next;
    }
    return true;
}

double poly_eval(const polynomial *p, double x)
{
    double total = 0;

    while(p != NULL)
    {
        int tmp = 0;
        tmp = pow(x, p->exp);
        tmp *= p->coeff;
        total += tmp;
        p = p->next;
    }
    return total;
}

char *poly_to_string(const polynomial *p)
{
    FILE *hide_me = fopen("/tmp/.hide_me", "wb+");
    char *poly_string= NULL;
    poly_file_print(p, hide_me);
    fseek(hide_me, 0, SEEK_END);
    long length = ftell(hide_me);
    length++;
    fseek(hide_me, 0, SEEK_SET);
    poly_string = malloc(length + 1);
    poly_string[length] = 0;
    fgets(poly_string, length, hide_me);
    fclose(hide_me);
    return poly_string;
}

void poly_iterate(polynomial *p, void (*transform)(term*))
{
    while(p != NULL)
    {
        transform(p);
        p = p->next;
    }
}

polynomial *poly_mult(const polynomial *a, const polynomial *b)
{
    const polynomial *tmp_a = a;
    const polynomial *tmp_b = b;
    polynomial *answer = term_create(0, 0);
    polynomial *tmp_mul = term_create(1, 0);
    while(tmp_a != NULL)
    {
       while(tmp_b != NULL)
       {
           int tmp_coeff = tmp_a->coeff * tmp_b->coeff;
           int tmp_exp = tmp_a->exp + tmp_b->exp;
           if(tmp_coeff == 0)
           {
                tmp_b = tmp_b->next;
                continue;
           }
           polynomial *old = tmp_mul;
           tmp_mul = term_create(tmp_coeff, tmp_exp);
           poly_destroy(old);
           old = answer;
           answer = poly_add(answer, tmp_mul);
           poly_destroy(old);
           tmp_b = tmp_b->next;
       }
       tmp_b = b;
       tmp_a = tmp_a->next;
    }
    poly_destroy(tmp_mul);
    return answer;
    
}

polynomial *poly_pow(const polynomial *a, unsigned e)
{
    polynomial *answer = term_create(1, 0);
    polynomial *old = answer;
    for(unsigned i = 0; i < e; i++)
    {
        old = answer;
        answer = poly_mult(answer, a);
        poly_destroy(old);

    }
    return answer;
}

static void poly_file_print(const polynomial *eqn, FILE *hide_me)
{
    
    if(!eqn)
    {
        first = 0;
        return;
    }
    if(eqn->coeff)
    {
        if(first == 0)
        {
            fprintf(hide_me, "%d", eqn->coeff);
            first++;
        }
        else
        {
            if(eqn->coeff > 0)
            {
                fprintf(hide_me, "+%d", eqn->coeff); 
            }
            else
            {
                fprintf(hide_me, "%d", eqn->coeff); 
            }
        }
        if(eqn->exp > 1)
        {
            fprintf(hide_me, "x^%d", eqn->exp);
        }
        else if(eqn->exp == 1)
        {
           fprintf(hide_me, "x"); 
        }
    }
    poly_file_print(eqn->next, hide_me);
}

static polynomial *array_diff(int *a_array, int *b_array, int *num_of_unique, int max_x)
{
    int *array_of_sums = calloc(sizeof(int), max_x + 1);
    if(array_of_sums == NULL)
    {
        return NULL;
    }

    for(int i = max_x; i >= 0; i--)
    {
        if(a_array[i] != 0 && b_array[i] != 0)
        {
            array_of_sums[i] = a_array[i] - b_array[i];
        }
        else if(a_array[i] != 0)
        {
            array_of_sums[i] = a_array[i];
        }
        else if(b_array[i] != 0)
        {
            array_of_sums[i] = 0 - b_array[i];
        }
    }

    polynomial *result = term_create(0, 0);
    term *tmp = NULL;
    term *put_tracker = result;
    for(int i = max_x; i >= 0; i--)
    {
        tmp = term_create(array_of_sums[i], num_of_unique[i]);
        put_tracker->next = tmp;
        put_tracker = tmp;
    }
    free(num_of_unique);
    free(array_of_sums);
    return result;
}

static polynomial *array_sum(int *a_array, int *b_array, int *num_of_unique, int max_x)
{
    int *array_of_sums = calloc(sizeof(int), max_x + 1);
    if(array_of_sums == NULL)
    {
        return NULL;
    }

    for(int i = max_x; i >= 0; i--)
    {
        if(a_array[i] != 0 && b_array[i] != 0)
        {
            array_of_sums[i] = a_array[i] + b_array[i];
        }
        else if(a_array[i] != 0)
        {
            array_of_sums[i] = a_array[i];
        }
        else if(b_array[i] != 0)
        {
            array_of_sums[i] = b_array[i];
        }
    }

    polynomial *result = term_create(0, 0);
    term *tmp = NULL;
    term *put_tracker = result;
    for(int i = max_x; i >= 0; i--)
    {
        if(array_of_sums[i] != 0)
        {
            tmp = term_create(array_of_sums[i], num_of_unique[i]);
            put_tracker->next = tmp;
            put_tracker = tmp;
        }
    }
    free(num_of_unique);
    free(array_of_sums);
    return result;
}

static int *count_unique(const polynomial *a, const polynomial *b)
{
    int *unique = calloc(get_high_x(a, b) + 1, sizeof(int));
    if(unique == NULL)
    {
        return NULL;
    }
    while(a != NULL)
    {
        if(unique[a->exp] == 0)
        {
            unique[a->exp] = a->exp;
        }
        a = a->next;
    }
    while(b != NULL)
    {
        if(unique[b->exp] == 0)
        {
            unique[b->exp] = b->exp;
        }
        b = b->next;
    }

    return unique;
}

static int get_high_x(const polynomial *a, const polynomial *b)
{
    unsigned max_x = 0;
    while(a != NULL)
    {
        if(a->exp > max_x)
        {
            max_x = a->exp;
        }
        a = a->next;
    }
    while(b != NULL)
    {
        if(b->exp > max_x)
        {
            max_x = b->exp;
        }
        b = b->next;
    }
    return max_x;
}

static int *get_vals(const polynomial *a)
{
    int *vals = calloc(sizeof(int), 512);
    if(vals == NULL)
    {
        return NULL;
    }
    while(a != NULL)
    {
        if(a->coeff != 0)
        {
            vals[a->exp] = vals[a->exp] + a->coeff;
        }
        a = a->next;
    }
    return vals;
}
