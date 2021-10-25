#include <stdio.h>
#include <stdlib.h>

struct poly
{
    int coef, exp;
};

typedef struct poly poly;

void disp(poly *p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {

        if (p[i].exp > 1)
        {
            if (i == 0)
            {
                if (p[i].coef == 1)
                    printf("x^%d ", p[i].exp);
                else if (p[i].coef == -1)
                    printf("- x^%d ", p[i].exp);
                else
                    printf("%dx^%d ", p[i].coef, p[i].exp);
            }
            else if (p[i].coef < 0)
            {
                if (p[i].coef == -1)
                    printf("- x^%d ", p[i].exp);
                else
                    printf("- %dx^%d ", -(p[i].coef), p[i].exp);
            }
            else
            {
                if (p[i].coef == 1)
                    printf("+ x^%d ", p[i].exp);
                else
                    printf("+ %dx^%d ", p[i].coef, p[i].exp);
            }
        }
        else if (p[i].exp == 1)
        {
            if (i == 0)
            {
                if (p[i].coef == 1)
                    printf("x ");
                else if (p[i].coef == -1)
                    printf("- x ");
                else
                    printf("%dx ", p[i].coef);
            }
            else if (p[i].coef < 0)
            {
                if (p[i].coef == -1)
                    printf("- x ");
                else
                    printf("- %dx ", -(p[i].coef));
            }
            else
            {
                if (p[i].coef == 1)
                    printf("+ x ");
                else
                    printf("+ %dx ", p[i].coef);
            }
        }
        else
        {
            if (i == 0)
                printf("%d ", p[i].coef);
            else if (p[i].coef < 0)
                printf("- %d ", -(p[i].coef));
            else
                printf("+ %d ", p[i].coef);
        }
    }
}

poly *polyapp(poly *p, int *n, int elem, int power)
{
    p = (poly *)realloc(p, (*n + 1) * sizeof(poly));
    p[*n].coef = elem;
    p[*n].exp = power;
    (*n)++;
    return p;
}

poly *polyadd(poly *p1, poly *p2, int n1, int n2, int *n)
{
    int i = 0, j = 0, temp;
    poly *p = NULL;
    while (i < n1 && j < n2)
    {
        if (p1[i].exp == p2[j].exp)
        {
            temp = p1[i].coef + p2[j].coef;
            if (temp != 0)
                p = polyapp(p, n, temp, p1[i].exp);
            i++;
            j++;
        }
        else if (p1[i].exp > p2[j].exp)
        {
            p = polyapp(p, n, p1[i].coef, p1[i].exp);
            i++;
        }
        else
        {
            p = polyapp(p, n, p2[j].coef, p2[j].exp);
            j++;
        }
    }

    while (i < n1)
    {
        p = polyapp(p, n, p1[i].coef, p1[i].exp);
        i++;
    }

    while (j < n2)
    {
        p = polyapp(p, n, p2[j].coef, p2[j].exp);
        j++;
    }
    return p;
}

poly *ins(poly *p, int *n, int elem, int power)
{
    p = (poly *)realloc(p, ((*n + 1) * sizeof(poly)));
    int i = *n;
    while (p[i - 1].exp < power && i > 0)
    {
        p[i] = p[i - 1];
        i--;
    }
    p[i].coef = elem;
    p[i].exp = power;
    (*n)++;
    return p;
}

poly *prod(poly *p1, poly *p2, int n1, int n2, int *n)
{
    int i, j, el, pow, found;
    poly *p = NULL;
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            found = 0;
            el = p1[i].coef * p2[j].coef;
            pow = p1[i].exp + p2[j].exp;
            for (int k = 0; k < *n; k++)
            {
                if (pow == p[k].exp)
                {
                    found = 1;
                    p[k].coef += el;
                    break;
                }
            }
            if (!found)
                p = ins(p, n, el, pow);
        }
    }
    return p;
}

int main()
{
    poly *p1 = NULL, *p2 = NULL, *p = NULL;
    int i, j, max_power, n1 = 0, n2 = 0, n = 0, temp;
    printf("\nEnter the degree of the polynomial1: ");
    scanf("%d", &max_power);
    for (i = max_power; i >= 0; i--)
    {
        printf("Enter the coefficient of x^%d: ", i);
        scanf("%d", &temp);
        if (temp != 0)
            p1 = polyapp(p1, &n1, temp, i);
    }

    printf("\nEnter the degree of the polynomial2: ");
    scanf("%d", &max_power);
    for (i = max_power; i >= 0; i--)
    {
        printf("Enter the coefficient of x^%d: ", i);
        scanf("%d", &temp);
        if (temp != 0)
            p2 = polyapp(p2, &n2, temp, i);
    }

    printf("\nPolynomial 1: ");
    disp(p1, n1);

    printf("\nPolynomial 2: ");
    disp(p2, n2);

    p = polyadd(p1, p2, n1, n2, &n);
    printf("\nSum: \n");
    disp(p, n);

    free(p);
    free(p1);
    free(p2);

    return 0;
}