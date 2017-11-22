//
// Created by Ilya on 11/22/2017.
//

#include "Course.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int coursesEqualId(Course course1, Course course2){return 1;}
void displayCourse(Course course1){}
void destroyCourse(Course course1){}

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
    Course new_course = *course;
    //new_course = malloc(sizeof(*new_course));
    DynamicArray pre_courses;
    pre_courses = createDynamicArray();
    if(pre_courses == NULL) return COURSE_MEMORY_ERROR;
    new_course->preCourses = pre_courses;
    new_course->id = duplicateString(id);
    new_course->name = duplicateString(name);
    new_course->credits = credits;
    return COURSE_OK;
}

