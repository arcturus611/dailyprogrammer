#include <stdio.h>
#include <stdlib.h>

int array_count;
int *array_base;

void draw_array(int a, int b)
{
    int width = 10, height = 100;
    printf("P6\n%d %d\n255\n", width * array_count, height);
    for (int y = 0; y < height; y++) {
        int edge = y < height / 10 || y > height - height / 10;
        for (int x = 0; x < width * array_count; x++) {
            int xx = x / width;
            int selected = xx == a || xx == b;
            int r = 0, g = 0, b = 0;
            if (edge && selected)
                r = 255;
            else
                r = g = b = (array_base[xx] * 255) / array_count;
            printf("%c%c%c", r, g, b);
        }
    }
}

int intcmp(const void *a, const void *b)
{
    const int *ia = (int *) a, *ib = (int *) b;
    draw_array(ia - array_base, ib - array_base);
    return *ia - *ib;
}

void shuffle()
{
    for (int i = array_count - 1; i > 0; i--) {
        int swap = rand() % (i + 1);
        int tmp = array_base[i];
        array_base[i] = array_base[swap];
        array_base[swap] = tmp;
    }
}

int main(int argc, char **argv)
{
    array_count = argc > 1 ? atoi(argv[1]) : 64;
    int array[array_count];
    for (int i = 0; i < array_count; i++)
        array[i] = i;
    array_base = array;
    shuffle();
    draw_array(-1, -1);
    qsort(array, array_count, sizeof(array[0]), intcmp);
    draw_array(-1, -1);
    return 0;
}
