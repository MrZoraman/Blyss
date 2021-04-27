#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Rectangle.h"

int main()
{
    struct rectangle r;
    memset(&r, 0, sizeof r);
    rectangle_init(&r, 5, 10);
    printf("Rectangle area: %d\n", rectangle_area(&r));
    return EXIT_SUCCESS;
}