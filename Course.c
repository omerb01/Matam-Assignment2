//
// Created by Ilya on 11/22/2017.
//

#include "Course.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define CONVERT_DA_ERROR($$function$$) \
DAResult $$error$$ = ($$function$$) ; \
if ($$error$$ == DA_MEMORY_ERROR) {return COURSE_MEMORY_ERROR;} \
else if ($$error$$ == DA_ILLEGAL_INDEX) {return COURSE_NOT_EXIST;} \


static char *duplicateString(const char *str);

static int compareCoursesById(Course course1, Course course2);

static Course getPreCourse(Course c, int index);

static int isPreCourseExist(Course c1, Course c2);

static char *duplicateString(const char *str) {
    int new_string_size = strlen(str);
    char *duplicated_string = malloc(new_string_size * sizeof(char) + 1);
    if (duplicated_string == NULL) return NULL;
    strcpy(duplicated_string, str);
    return duplicated_string;
}

static int compareCoursesById(Course course1, Course course2) {
    int compare_result = strcmp(course1->id, course2->id);
    return compare_result;
}

static Course getPreCourse(Course c, int index) {
    return c->preCourses->elements[index];
}

static int isPreCourseExist(Course c1, Course c2) {
    int index_of_c2;
    indexOfElement(c1->preCourses, c2, 0, &index_of_c2);
    if (index_of_c2 == -1) {
        return 0;
    } else {
        return 1;
    }

}

CourseResult
createCourse(char *id, char *name, double credits, Course *course) {
    assert(name != NULL && id != NULL && course != NULL);
    if (credits < 0) return COURSE_ILLEGAL_PARAMETER;

    char *duplicated_id = duplicateString(id);
    char *duplicated_name = duplicateString(name);
    DynamicArray pre_courses = createDynamicArray();
    Course new_course = malloc(sizeof(*new_course));
    if (duplicated_id == NULL || duplicated_name == NULL || pre_courses ==
                                                            NULL || new_course
                                                                    == NULL) {
        free(duplicated_id);
        free(duplicated_name);
        free(new_course);
        if (pre_courses != NULL) destroyDynamicArray(pre_courses);
        return COURSE_MEMORY_ERROR;
    }

    new_course->preCourses = pre_courses;
    new_course->id = duplicated_id;
    new_course->name = duplicated_name;
    new_course->credits = credits;
    *course = new_course;

    return COURSE_OK;
}

int coursesEqualId(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    int compare_result;
    compare_result = compareCoursesById(course1, course2);
    if (compare_result == 0) {
        return 1;
    } else {
        return 0;
    }
}

//checks if course1 is less than course2
int courseLessThan(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    int compare_result;
    compare_result = compareCoursesById(course1, course2);
    if (compare_result < 0) {
        return 1;
    } else {
        return 0;
    }
}

CourseResult courseUpdateName(Course course1, char *new_name) {
    assert(course1 != NULL && new_name != NULL);
    char *temp_store_name = course1->name;

    char *name = duplicateString(new_name);
    if (name == NULL) {
        return COURSE_MEMORY_ERROR;
    }

    course1->name = name;
    free(temp_store_name);

    return COURSE_OK;
}

CourseResult addPreCourse(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    if (coursesEqualId(course1, course2) == 1) return COURSE_THE_SAME_COURSE;
    if (isPreCourseExist(course1, course2) == 1) return COURSE_ALREADY_EXISTS;

    int pre_course_size = size(course1->preCourses);
    if (pre_course_size == 0) {
        CONVERT_DA_ERROR(addElementStart(course1->preCourses, course2));
        return COURSE_OK;
    } else {
        Course pre_course;
        for (int i = 0; i < pre_course_size; i++) {
            pre_course = getPreCourse(course1, i);
            if (courseLessThan(course2, pre_course) == 1) {
                CONVERT_DA_ERROR(
                        addElementBefore(course1->preCourses, course2,
                                         i));
                return COURSE_OK;
            }
        }
        CONVERT_DA_ERROR(addElementEnd(course1->preCourses, course2));
        return COURSE_OK;
    }
}

CourseResult removePreCourse(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    if (isPreCourseExist(course1, course2) == 0) return COURSE_NOT_EXIST;

    int index_of_course2;
    indexOfElement(course1->preCourses, course2, 0, &index_of_course2);

    CONVERT_DA_ERROR(removeElement(course1->preCourses, index_of_course2));
    return COURSE_OK;
}

static void printTrimedString(char *str) {
    int len = strlen(str);
    char *tail = str + len - 1;
    while (tail > str && *tail == ' ') {
        tail--;
    }

    while (*str == ' ') {
        str++;
    }
    int space_counter = 0;
    while (str <= tail) {
        if (*str == ' ') {
            space_counter++;
        } else {
            space_counter = 0;
        }
        if (space_counter <= 1) {
            printf("%c", *str);
        }
        str++;
    }
}

void displayCourse(Course course1) {
    static int to_pre_course = 0;
    if (to_pre_course == 0) {
        to_pre_course = 1;
        printTrimedString(course1->id);
        printf(" ");
        printTrimedString(course1->name);
        printf(" ");
        printf("%.1f ", course1->credits);
        int len = size(course1->preCourses);
        for (int i = 0; i < len; ++i) {
            displayElement(course1->preCourses, i);
            if (i != len - 1) printf(" ");
        }
        to_pre_course = 0;
    } else {
        printTrimedString(course1->id);
    }
}

void destroyCourse(Course course1) {
    free(course1->id);
    free(course1->name);
    destroyDynamicArray(course1->preCourses);
    free(course1);
}
