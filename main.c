#include <stdio.h>
#include "poly.h"

int main(void)
{
    term *nox = term_create(6, 0);
    term *x = term_create(3, 1);
    term *x2 = term_create(5, 2);

    term *noy = term_create(5, 0);
    term *y = term_create(2, 1);
    term *y2 = term_create(-6, 2);
    term *y3 = term_create(5, 3);

    x2->next = x;
    x->next = nox;

    y3->next = y2;
    y2->next = y;
    y->next = noy;

    term *new = poly_add(x2, y3);
    printf("Add: ");
    poly_print(new);
    printf("\n");
    new = poly_sub(x2, y3);
    printf("Sub: ");
    poly_print(new);
    printf("\n");
    poly_destroy(x2);
    poly_destroy(y3);
    poly_destroy(new);

    return 0;
}
