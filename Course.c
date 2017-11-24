//
// Created by Ilya on 11/22/2017.
//

#include "Course.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

CourseResult removePreCourse(Course course1, Course course2){return COURSE_OK;}

static char* duplicateString(const char* str)
{
    int new_string_size = strlen(str);
    char* duplicated_string = malloc(new_string_size*sizeof(char) + 1);
    strcpy(duplicated_string,str);
    if (duplicated_string == NULL) return NULL;
    return duplicated_string;
}

static int compareCoursesById(Course course1, Course course2)
{
    int compare_result = strcmp(course1->id, course2->id);
    return compare_result;
}

CourseResult createCourse(char *id, char *name, double credits, Course *course)
{
    assert(name != NULL && id != NULL && course != NULL);
    if(credits < 0) return COURSE_ILLEGAL_PARAMETER;
    Course new_course;
    new_course = malloc(sizeof(*new_course));
    DynamicArray pre_courses;
    pre_courses = createDynamicArray();
    if(pre_courses == NULL) return COURSE_MEMORY_ERROR;
    new_course->preCourses = pre_courses;
    new_course->id = duplicateString(id);
    new_course->name = duplicateString(name);
    new_course->credits = credits;
    *course = new_course;
    return COURSE_OK;
}

int coursesEqualId(Course course1, Course course2)
{
    assert(course1 != NULL && course2 != NULL);
    int compare_result;
    compare_result = compareCoursesById(course1, course2);
    if (compare_result == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int courseLessThan(Course course1, Course course2)
{
    assert(course1 != NULL && course2 != NULL);
    int compare_result;
    compare_result = compareCoursesById(course1,course2);
    if (compare_result < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

CourseResult courseUpdateName(Course course1, char *new_name) {
    assert(course1 != NULL && new_name != NULL);
    char *temp_store_name = course1->name;
    char *name = duplicateString(new_name);
    if (name == NULL)   return COURSE_MEMORY_ERROR;
    course1->name = name;
    free(temp_store_name);
    return COURSE_OK;
}

void displayCourse(Course course1) {
    static int to_pre_course = 0;
    if (to_pre_course == 0) {
        to_pre_course = 1;
        printf("%s %s %.1f ", course1->id, course1->name,
               course1->credits);
        for (int i = 0; i < size(course1->preCourses); ++i) {
            displayElement(course1->preCourses, i);
        }
    } else {
        printf("%s ", course1->id);
    }
}

void destroyCourse(Course course1)
{
    free(course1->id);
    free(course1->name);
    destroyDynamicArray(course1->preCourses);
    free(course1);
}
