
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
     
    enum value_type { TYPE_STRING, TYPE_LIST };
     
    struct cons {
        struct value *value;
        struct cons *next;
    };
    // constructor that takes in pointers to field-values for a struct cons object and returns the constructed object (yes, it's a constructor!) 
    struct cons *cons(struct value *value, struct cons *next)
    {
        struct cons *cons = malloc(sizeof(struct cons));
        cons->value = value;
        cons->next = next;
        return cons;
    }
     
    /* Tagged union. */
    struct value {
        enum value_type type;
        union {
            char string[64];
            struct cons *list;
        };
    };
     
    struct value *value_read(FILE *in); // i think this declaration prevents the need for all function definitions to be in the order in which they are used
     
    struct value *string_read(FILE *in) //returns string inside single quotes, excluding the single quotes
    {   // Very skeeto style. Whatever needs to be returned (in this case, pointer to struct value), is created completely inside the function, starting from memory allocation.
        struct value *v = malloc(sizeof(struct value));
        v->type = TYPE_STRING;// don't forget that it's a pointer, hence use ->, not . for fields.
        char *p = v->string;// storing the address in p
        for (int c = fgetc(in); c != '\''; c = fgetc(in), p++)
            *p = c;
        *p = '\0';
        return v;
    }
     
    struct value *list_read(FILE *in) //*in points to the first character inside the '[]'.
    {
        struct value *value = malloc(sizeof(struct value));
        value->type = TYPE_LIST;
        struct cons head = {0}, *tail = &head;// it's a list. obviously you want a head and a tail. 
        int c;
        while (1) {
            while (isspace(c = fgetc(in))); // consume comma or initial whitespace. Get out of while loop with c = '\'' and *in pointing to the cahracter after the first single quote. 
            printf("Out of while loop, c is: %c\n", c); 
            if (c == ']')
                break;
            else if (c != ',')
                ungetc(c, in); // if c is anything else, pointer *in is moved back
            tail->next = cons(value_read(in), NULL); 
            tail = tail->next;
        }
        value->list = head.next;// good one. Here you are handing over to value, the head of the entire linked list. Note how value, being a pointer, uses ->, while head, being a non-pointer, uses ..
        return value;
    }
     
    struct value *value_read(FILE *in)
    {
        struct value *v = malloc(sizeof(struct value));
        int c;
        while (isspace(c = fgetc(in))); // skip whitespace. c= '[', and *in is moved to the character after '['. (or, c = '\'', and *in is moved to the first character of the string).
        switch (c) {
        case '[':
            return list_read(in); //return a struct value* pointing to the whole list. 
            break;
        case '\'':
            printf("Present char is %c\n", c); 
            return string_read(in);
            break;
        default:
            abort();
        }
        return v;
    }
     
    void value_print(struct value *value)
    {
        switch (value->type) {
        case TYPE_STRING:
            printf("'%s'", value->string);
            break;
        case TYPE_LIST:
            printf("[");
            for (struct cons *list = value->list; list; list = list->next) {
                value_print(list->value);
                if (list->next)
                    printf(", ");
            }
            printf("]");
            break;
        }
    }
     
    int list_length(struct value *value)
    {
        if (value->type != TYPE_LIST)
            abort();
        int length = 0;
        for (struct cons *cons = value->list; cons; cons = cons->next, length++);
        return length;
    }
     
    struct cons *nth(struct value *list, int n)
    {
        struct cons *cons = list->list;
        for (; n; cons = cons->next, n--);
        return cons;
    }
     
    int max(int a, int b)
    {
        return a > b ? a : b;
    }
     
    void table_div(int widths[], int ncols)
    {
        putchar('+');
        for (int col = 0; col < ncols; col++) {
            for (int i = 0; i < widths[col] + 2; i++)
                putchar('-');
            putchar('+');
        }
        putchar('\n');
    }
     
    void table_print(struct value *headings, struct value *rows)
    {
        /* Compute column sizes. */
        int ncols = list_length(headings);
        int widths[ncols];
        char formats[ncols][8];
        memset(widths, 0, ncols * sizeof(widths[0]));
        struct cons *hlist = headings->list;
        for (int col = 0; col < ncols; col++) {
            widths[col] = strlen(hlist->value->string);
            for (struct cons *rlist = rows->list; rlist; rlist = rlist->next) {
                int len = strlen(nth(rlist->value, col)->value->string);
                widths[col] = max(widths[col], len);
            }
        }
     
        /* Compute format strings. */
        for (int col = 0; col < ncols; col++)
            sprintf(formats[col], " %%-%ds ", widths[col]);
     
        /* Print headings. */
        table_div(widths, ncols);
        hlist = headings->list;
        putchar('|');
        for (int col = 0; col < ncols; col++, hlist = hlist->next) {
            printf(formats[col], hlist->value->string);
            putchar('|');
        }
        putchar('\n');
     
        /* Print rows. */
        for (struct cons *rlist = rows->list; rlist; rlist = rlist->next) {
            table_div(widths, ncols);
            struct cons *clist = rlist->value->list;
            putchar('|');
            for (int col = 0; col < ncols; col++, clist = clist->next) {
                printf(formats[col], clist->value->string);
                putchar('|');
            }
            putchar('\n');
        }
        table_div(widths, ncols);
    }
     
    int main()
    {
        struct value *headings = value_read(stdin);
        struct value *rows = value_read(stdin);
        table_print(headings, rows);
        return 0;
    }


