/* cc -std=c99 -Wall -D_BSD_SOURCE roll.c -lbsd -lncurses -o roll */
#include <ncurses.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <bsd/stdlib.h>

#define HEIGHT 24
#define WIDTH 80

void display(uint64_t *counts, size_t length, int count) {
    uint64_t highest = 0;
    for (int i = 0; i < length; i++) {
        highest = counts[i] > highest ? counts[i] : highest;
    }
    int width = WIDTH / length;
    for (size_t x = 0; x < length; x++) {
        int height = ((double) counts[x]) / highest * HEIGHT;
        for (size_t y = 0; y < HEIGHT; y++) {
            for (int w = 0; w < width; w++) {
                mvaddch(HEIGHT - y, x * width + w, y < height ? '*' : ' ');
            }
        }
    }
    for (int n = 0; n < length; n++) {
        mvprintw(0, n * width, "%d", n + count);
    }
}

int main() {
    initscr();
    curs_set(0);
    erase();
    int sides = 6, count = 3;  // consider reading these from stdin or argv

    uint64_t total = 0;
    size_t length = sides * count - count + 1;
    uint64_t *counts = calloc(length, sizeof(uint64_t));
    while (true) {
        total++;
        int sum = 0;
        for (int die = 0; die < count; die++) {
            sum += (arc4random() % sides) + 1;
        }
        counts[sum - count]++;
        display(counts, length, count);
        mvprintw(HEIGHT + 1, 0, "%dd%d, %ld rolls", count, sides, total);
        refresh();
        usleep(1000);
    }

    endwin();
    return 0;
}
