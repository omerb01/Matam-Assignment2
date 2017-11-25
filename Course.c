//
// Created by Ilya on 11/22/2017.
//

#include "Course.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define CHECK_DA_MEMORY_ERROR($$function$$) \
DAResult $$error$$ = ($$function$$) ; \
if ($$error$$ == DA_MEMORY_ERROR) {return COURSE_MEMORY_ERROR;} \
else if ($$error$$ == DA_ILLEGAL_INDEX) {return COURSE_ILLEGAL_PARAMETER;} \

// TODO: CHECK WITH OMER THE ILLEGAL INDEX, SHOULDN'T GET THIS ERROR ANYHOW ****

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
    CHECK_DA_MEMORY_ERROR(indexOfElement(c1->preCourses, c2, 0, &index_of_c2));
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

    Course new_course;
    new_course = malloc(sizeof(*new_course));
    DynamicArray pre_courses;
    pre_courses = createDynamicArray();
    if (pre_courses == NULL) return COURSE_MEMORY_ERROR;

    new_course->preCourses = pre_courses;
    new_course->id = duplicateString(id);
    new_course->name = duplicateString(name);
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
    if (name == NULL) return COURSE_MEMORY_ERROR;

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
        CHECK_DA_MEMORY_ERROR(addElementStart(course1->preCourses, course2));
        return COURSE_OK;
    } else {
        Course pre_course;
        for (int i = 0; i < pre_course_size; i++) {
            pre_course = getPreCourse(course1, i);
            if (courseLessThan(course2, pre_course) == 1) {
                CHECK_DA_MEMORY_ERROR(
                        addElementBefore(course1->preCourses, course2,
                                         i));
                return COURSE_OK;
            }
        }
        CHECK_DA_MEMORY_ERROR(addElementEnd(course1->preCourses, course2));
        return COURSE_OK;
    }
}

CourseResult removePreCourse(Course course1, Course course2) {
    assert(course1 != NULL && course2 != NULL);
    if (isPreCourseExist(course1, course2) == 0) return COURSE_NOT_EXIST;

    DAResult temp;
    int index_of_course2;
    temp = indexOfElement(course1->preCourses, course2, 0, &index_of_course2);
    if (temp == DA_ILLEGAL_INDEX) return COURSE_ILLEGAL_PARAMETER;

    CHECK_DA_MEMORY_ERROR(removeElement(course1->preCourses, index_of_course2));
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
        to_pre_course = 0;
    } else {
        printf("%s ", course1->id);
    }
}

void destroyCourse(Course course1) {
    free(course1->id);
    free(course1->name);
    destroyDynamicArray(course1->preCourses);
    free(course1);
}
