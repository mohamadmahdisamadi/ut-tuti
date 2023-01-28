#include "ut_tuti_functions.h"

void main()
{
    int loggedin = 0;
    USER *head = (USER *)malloc(sizeof(USER));
    head->next_user = '\0';
    print_messages(1);
    while (TRUE)
    {
        print_messages(2);
        char **input = (char **)malloc(sizeof(char *));
        get_input(input);
        do_what(head, input, &loggedin);
        free(input);
    }
}