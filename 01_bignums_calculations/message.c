#include <stdio.h>
#include <stdlib.h>
#include "message.h"

void show_menu()
{   
    printf("%s%s%s", TITLE, RULES_INT, RULES_FLOAT);
}

void message(char *message)
{
    printf("%s", message);
}
