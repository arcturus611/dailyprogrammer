#include <stdio.h>

void looknsay(const char *in, char *out)
{
    char seen = *in;
    int count = 0;
    do {
        if (*in != seen) {
            out += sprintf(out, "%d%c", count, seen);
            count = 1;
            seen = *in;
        } else {
            count++;
        }
    } while (*in++);
}

int main()
{
    char buffer[1024] = {'1'};
    char *p[2] = { buffer, buffer + sizeof(buffer) / 2 };
    int n;
    scanf("%d", &n);
    printf("%s\n", p[0]);
    for (int i = 0; i < n - 1; i++) {
        looknsay(p[i & 1], p[~i & 1]);
        printf("%s\n", p[~i & 1]);
    }
    return 0;
}
