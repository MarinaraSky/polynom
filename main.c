#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

void triple(term *p)
{
    p->coeff *= 3;
}

int main(void)
{
    term *nox = term_create(6, 0);
    term *x = term_create(3, 1);
    term *x2 = term_create(5, 3);

    term *noy = term_create(5, 0);
    term *y = term_create(2, 1);
    term *y2 = term_create(-6, 2);
    term *y3 = term_create(-5, 3);
    
    term *eval = term_create(2, 2);

    term *nobreak0 = term_create(5, 0);
    term *nobreak1 = term_create(5, 0);
    term *nobreak2 = term_create(5, 0);
    term *nobreak3 = term_create(5, 0);
    term *nobreak4 = term_create(5, 0);
    term *nobreak5 = term_create(5, 0);
    term *nobreak6 = term_create(5, 0);
    term *nobreak7 = term_create(5, 0);
    term *nobreak8 = term_create(5, 0);
    term *nobreak9 = term_create(5, 0);
    term *nobreak10 = term_create(5, 0);
    term *nobreak11 = term_create(5, 0);

    nobreak11->next = nobreak10;
    nobreak10->next = nobreak9;
    nobreak9->next = nobreak8;
    nobreak8->next = nobreak7;
    nobreak7->next = nobreak6;
    nobreak6->next = nobreak5;
    nobreak5->next = nobreak4;
    nobreak4->next = nobreak3;
    nobreak3->next = nobreak2;
    nobreak2->next = nobreak1;
    nobreak1->next = nobreak0;

    x2->next = x;
    x->next = nox;

    y3->next = y2;
    y2->next = y;
    y->next = noy;

    polynomial *test = poly_add(nobreak11, y3);
    printf("Larger than 10: ");
    poly_print(test);
    printf("\n");
    x2->next = x;
    x->next = nox;

    y3->next = y2;
    y2->next = y;
    y->next = noy;
    bool same = poly_equal(x2,y3);
    if(same)
    {
        printf("Same\n");
    }
    else
    {
        printf("Diff\n");
    }
    term *new = poly_add(x2, y3);
    printf("Add: ");
    poly_print(new);
    printf("\n");
    poly_destroy(new);
    new = poly_sub(x2, y3);
    printf("Sub: ");
    poly_print(new);
    printf("\n");
    printf("Evaluated: %f\n", poly_eval(y3, 2));
    //poly_destroy(test);
    //poly_destroy(nobreak11);
    char *array = NULL;
    array = poly_to_string(new);
    printf("String: %s\n", array);
    printf("Pre Iter: ");
    poly_print(y3);
    printf("\n");
    printf("Post Iter: ");
    poly_iterate(y3, triple);
    poly_print(y3);
    printf("\n");
    free(array);
    poly_destroy(nobreak11);
    poly_destroy(test);
    poly_destroy(eval);
    poly_destroy(x2);
    poly_destroy(y3);
    poly_destroy(new);

    return 0;
}
