//
// Created by Ilya on 11/22/2017.
//

#include "Course.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static char* duplicateString(const char* str)
{
    int new_string_size = strlen(str);
    char* duplicated_string = malloc(new_string_size*sizeof(char) + 1);
    if (duplicated_string == NULL) return NULL;
    return duplicated_string;
}

CourseResult createCourse(char *id, char *name, double credits, Course *course)
{
    assert(name != NULL && id != NULL && course != NULL);
    if(credits < 0) return COURSE_ILLEGAL_PARAMETER;

}