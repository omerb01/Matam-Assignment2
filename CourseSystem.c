//
// Created by Omer on 23/11/2017.
//

#include <stdlib.h>
#include <string.h>
#include "CourseSystem.h"

static char *duplicateString(const char *str) {
    int new_string_size = strlen(str);
    char *duplicated_string = malloc(new_string_size * sizeof(char) + 1);
    strcpy(duplicated_string, str);
    if (duplicated_string == NULL) return NULL;
    return duplicated_string;
}

