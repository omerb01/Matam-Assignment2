//
// Created by Omer on 27/11/2017.
//

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("TEST %s FAILED\n", test_number); } \
   else printf("TEST %s SABABA\n", test_number);

#include <stdio.h>
#include "CourseSystem.h"

int main() {

    CourseResult course_result;
    int result;

    Course course1;
    course_result = createCourse("234111", "Computer Science", -1.0005,
                                 &course1);
    ASSERT("2.01", course_result == COURSE_ILLEGAL_PARAMETER);
    course_result = createCourse("", "Computer Science", 3.0333, &course1);
    ASSERT("2.05", course_result == COURSE_MEMORY_ERROR);
    course_result = createCourse("234141", "Cumbi", 0, &course1);
    ASSERT("2.02", course_result == COURSE_OK);

    Course course2;
    course_result = createCourse("234111", "Computer Science", 3.0333,
                                 &course2);
    ASSERT("2.03", course_result == COURSE_OK);

    Course course3;
    course_result = createCourse("234111", "Computer Science", 3.0333,
                                 &course3);
    ASSERT("2.04", course_result == COURSE_OK);

    Course course4;
    course_result = createCourse("234122", "matam", 999999, &course4);

    Course course5;
    course_result = createCourse("234118", "atam", 3, &course5);

    result = coursesEqualId(course3, course2);
    ASSERT("2.06", result == 1);

    result = coursesEqualId(course3, course3);
    ASSERT("2.07", result == 1);

    result = coursesEqualId(course1, course2);
    ASSERT("2.08", result == 0);

    result = courseLessThan(course3, course2);
    ASSERT("2.09", result == 0);

    result = courseLessThan(course3, course3);
    ASSERT("2.10", result == 0);

    result = courseLessThan(course2, course1);
    ASSERT("2.11", result == 1);

    course_result = courseUpdateName(course1, "Doron loves Cuuumbi");
    ASSERT("2.12", course_result == COURSE_OK);

    course_result = courseUpdateName(course1, "");
    ASSERT("2.13", course_result == COURSE_MEMORY_ERROR);

    course_result = addPreCourse(course1, course1);
    ASSERT("2.14", course_result == COURSE_THE_SAME_COURSE);

    course_result = addPreCourse(course2, course3);
    ASSERT("2.15", course_result == COURSE_THE_SAME_COURSE);

    course_result = addPreCourse(course1, course2);
    ASSERT("2.16", course_result == COURSE_OK);

    course_result = addPreCourse(course1, course3);
    ASSERT("2.17", course_result == COURSE_ALREADY_EXISTS);

    course_result = removePreCourse(course2, course1);
    ASSERT("2.18", course_result == COURSE_NOT_EXIST);

    course_result = removePreCourse(course1, course3);
    ASSERT("2.19", course_result == COURSE_OK);

    course_result = addPreCourse(course1, course4);
    course_result = addPreCourse(course1, course5);
    course_result = addPreCourse(course1, course2);

    displayCourse(course1);
    printf("\n");
    displayCourse(course2);
    printf("\n");
    displayCourse(course3);
    printf("\n");
    displayCourse(course4);
    printf("\n");
    displayCourse(course5);

    /*

 234141 Doron loves Cuuumbi 0.0 234111 234118 234122
 234111 Computer Science 3.0
 234111 Computer Science 3.0
 234122 matam 999999.0
 234118 atam 3.0

     */

    destroyCourse(course1);
    destroyCourse(course2);
    destroyCourse(course3);
    destroyCourse(course4);
    destroyCourse(course5);

}