#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

term *term_create(int coeff, unsigned exp)
{
    if(exp > 9)
    {
        printf("Polynomials above x\u2079 only available in PREMIUM version.\n");
        return NULL;
    }
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
            printf("%c%d", eqn->coeff > 0 ? '\0' : '\0', eqn->coeff);
            first++;
        }
        else
        {
            printf("\b%c%d", eqn->coeff > 0 ? '+' : '\0', eqn->coeff);
        }
        if(eqn->exp > 1)
        {
            printf("x^%d", eqn->exp);
        }
        else if(eqn->exp == 1)
        {
           printf("x"); 
        }
        printf(" ");
    }
    poly_print(eqn->next);
}

polynomial *poly_add(const polynomial *a, const polynomial *b)
{
    int count = count_unique(a, b);
    int *values_of_a = get_vals(a);
    int *values_of_b = get_vals(b);

    polynomial *sum_of_poly = array_sum(values_of_a, values_of_b, count); 

    free(values_of_a);
    free(values_of_b);
    return sum_of_poly;
}

polynomial *poly_sub(const polynomial *a, const polynomial *b)
{
    int count = count_unique(a, b);
    int *values_of_a = get_vals(a);
    int *values_of_b = get_vals(b);

    polynomial *diff_of_poly = array_diff(values_of_a, values_of_b, count); 

    free(values_of_a);
    free(values_of_b);
    return diff_of_poly;

}

polynomial *array_diff(int *a_array, int *b_array, int num_of_unique)
{
    int j = num_of_unique;
    int *array_of_sums = calloc(sizeof(int), num_of_unique + 1);

    for(int i = 10; i >= 0; i--)
    {
        if(a_array[i] != 0 && b_array[i] != 0)
        {
            array_of_sums[j] = a_array[i] - b_array[i];
            j--;
        }
        else if(a_array[i] != 0)
        {
            array_of_sums[j] = a_array[i];
            j--;
        }
        else if(b_array[i] != 0)
        {
            array_of_sums[j] = b_array[i];
            j--;
        }
    }

    polynomial *result = term_create(0, 0);
    term *put_tracker = result;
    for(int i = num_of_unique; i > 0; i--)
    {
        term *tmp = term_create(array_of_sums[i], i - 1);
        put_tracker->next = tmp;
        put_tracker = tmp;
    }
    free(array_of_sums);
    return result;
}

polynomial *array_sum(int *a_array, int *b_array, int num_of_unique)
{
    int j = num_of_unique;
    int *array_of_sums = calloc(sizeof(int), num_of_unique + 1);

    for(int i = 10; i >= 0; i--)
    {
        if(a_array[i] != 0 && b_array[i] != 0)
        {
            array_of_sums[j] = a_array[i] + b_array[i];
            j--;
        }
        else if(a_array[i] != 0)
        {
            array_of_sums[j] = a_array[i];
            j--;
        }
        else if(b_array[i] != 0)
        {
            array_of_sums[j] = b_array[i];
            j--;
        }
    }

    polynomial *result = term_create(0, 0);
    term *put_tracker = result;
    for(int i = num_of_unique; i > 0; i--)
    {
        term *tmp = term_create(array_of_sums[i], i - 1);
        put_tracker->next = tmp;
        put_tracker = tmp;
    }
    free(array_of_sums);
    return result;
}

int count_unique(const polynomial *a, const polynomial *b)
{
    int unique[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int count = 0;
    while(a != NULL)
    {
        if(unique[a->exp] == 0)
        {
            count++;
            unique[a->exp] = 1;
        }
        a = a->next;
    }
    while(b != NULL)
    {
        if(unique[b->exp] == 0)
        {
            count++;
            unique[b->exp] = 1;
        }
        b = b->next;
    }

    return count;
}

int *get_vals(const polynomial *a)
{
    int *vals = calloc(sizeof(int), 11);
    while(a != NULL)
    {
        if(a->coeff != 0)
        {
            vals[a->exp] = a->coeff;
        }
        a = a->next;
    }
    return vals;
}













