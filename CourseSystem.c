//
// Created by Omer on 23/11/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "CourseSystem.h"

#define CHECK_DA_MEMORY_ERROR($$function$$) \
DAResult $$error$$ = ($$function$$) ; \
if ($$error$$ == DA_MEMORY_ERROR) {return SYS_MEMORY_PROBLEM;} \


static char *duplicateString(const char *str) {
    int new_string_size = strlen(str);
    char *duplicated_string = malloc(new_string_size * sizeof(char) + 1);
    if (duplicated_string == NULL) return NULL;
    strcpy(duplicated_string, str);
    return duplicated_string;
}

CourseSystem createSystem(char *name) {
    CourseSystem system = malloc(sizeof(CourseSystem));
    if (system == NULL) return NULL;
    DynamicArray courses = createDynamicArray();
    if (courses == NULL) return NULL;

    char *duplicated_name = duplicateString(name);
    system->name = duplicated_name;
    system->courses = courses;

    return system;
}

static int isCourseExist(CourseSystem system, Course course) {
    int index;
    indexOfElement(system->courses, course, 0, &index);

    if (index == -1) {
        return 0;
    } else {
        return 1;
    }
}

static Course getCourse(CourseSystem system, int index) {
    return system->courses->elements[index];
}

SysResult sysAddCourse(CourseSystem system, Course course) {
    assert(system != NULL && course != NULL);
    if (isCourseExist(system, course) == 1) return SYS_COURSE_ALREADY_EXIST;

    int courses_number = size(system->courses);
    if (courses_number == 0) {
        CHECK_DA_MEMORY_ERROR(addElementStart(system->courses, course));
        return SYS_OK;
    }

    for (int i = 0; i < courses_number; ++i) {
        Course currect_course = getCourse(system, i);
        if (courseLessThan(course, currect_course) == 1) {
            CHECK_DA_MEMORY_ERROR(addElementBefore(system->courses, course, i));
            return SYS_OK;
        }
    }

    CHECK_DA_MEMORY_ERROR(addElementEnd(system->courses, course));
    return SYS_OK;
}

static Course findCourseById(CourseSystem system, char *course_id) {
    for (int i = 0; i < size(system->courses); ++i) {
        Course currect_course = getCourse(system, i);
        if (strcmp(currect_course->id, course_id) == 0) {
            return currect_course;
        }
    }

    return NULL;
}

static DynamicArray getPreCourses(Course course) {
    return course->preCourses;
}

SysResult sysIsPreCourse(CourseSystem system, char *course_id1, char
*course_id2, int *result) {
    assert(system != NULL && course_id1 != NULL && course_id2 != NULL);

    Course course1 = findCourseById(system, course_id1);
    Course course2 = findCourseById(system, course_id2);

    if (course1 == NULL || course2 == NULL) {
        return SYS_NOT_IN_SYSTEM;
    }

    *result = 0;

    int index;
    indexOfElement(getPreCourses(course1), course2, 0, &index);
    if (index != -1) *result = 1;

    return SYS_OK;
}

// TODO: CHECK WITH ILIYA'S FUNCTION
SysResult sysRemovePreCourse(CourseSystem system, char *course_id1, char
*course_id2) {
    assert(system != NULL && course_id1 != NULL && course_id2 != NULL);

    Course course1 = findCourseById(system, course_id1);
    Course course2 = findCourseById(system, course_id2);

    if (course1 == NULL || course2 == NULL) {
        return SYS_NOT_IN_SYSTEM;
    }

    CourseResult error = removePreCourse(course1, course2);
    if (error == COURSE_NOT_EXIST) return SYS_NOT_PRE_COURSE;
    if (error == COURSE_MEMORY_ERROR) return SYS_MEMORY_PROBLEM;

    return SYS_OK;
}

void displaySystem(CourseSystem system) {
    assert(system != NULL);

    printf("%s\n", system->name);
    displayAllElements(system->courses);
}