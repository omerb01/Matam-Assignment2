#ifndef COURSE_H
#define COURSE_H

#include "DynamicArray.h"

typedef struct course
{
    char *id;
    char *name;
    double credits;
    DynamicArray preCourses;
} *Course;


/*******************************************************************/
/* Interface of data type CourseDynamicArray  */

typedef enum { COURSE_OK , COURSE_MEMORY_ERROR , COURSE_ILLEGAL_PARAMETER ,
               COURSE_THE_SAME_COURSE , COURSE_ALREADY_EXISTS , COURSE_NOT_EXIST} CourseResult;

//------------------------------------------------------------------------------------------
// create a new course with the details of the parameters id , name , credits;
// no pre courses are defined here.
// id and name should be copied into the new created course by duplication.
// they must not be changed.
// Either id or name or course must not be NULL. (handled by assert).
// course is an output parameter which gets the created new course.
// return value : COURSE_OK ,
//                COURSE_MEMORY_ERROR  if there are memory problems
//                COURSE_ILLEGAL_PARAMETER if credits < 0
CourseResult createCourse(char *id, char *name, double credits, Course *course) ;

//------------------------------------------------------------------------------------------
// checks if course1 and course2 have the same id. returns 1 or 0 accordingly.
// Either course1 or course2 must not be NULL. (handled by assert).

int coursesEqualId(Course course1, Course course2);

//------------------------------------------------------------------------------------------
// checks if course1 is less than (not equal) course2. returns 1 if yes or 0 if no.
// the comparison is made according to the id of the courses, by means of a lexicographic order.
// Either course1 or course2 must not be NULL. (handled by assert).
int courseLessThan(Course course1, Course course2);

//------------------------------------------------------------------------------------------
// update course1 so that its name will be as new_name.
// the new name should be physically duplicated into course1.
// new_name must not be NULL. (handled by assert).
// return value : COURSE_OK ,
//                COURSE_MEMORY_ERROR  if there are memory problems. in that case,
//                the old name stays.
CourseResult courseUpdateName(Course course1, char *new_name);

//------------------------------------------------------------------------------------------
// add course2 as a pre course of course1. course2 is not duplicated. just a simple assignment.
// all the pre courses of course1 should be keeped sorted, according to their id (lexicographic order,
// from small to big).
// Either course1 or course2 must not be NULL. (handled by assert).
// return value : COURSE_OK,
//                COURSE_THE_SAME_COURSE  if the id of course2 is the same as the id of course1
//                COURSE_ALREADY_EXISTS if a course with the id of course2 already registered as a pre course of course1
CourseResult addPreCourse(Course course1, Course course2);

//------------------------------------------------------------------------------------------
// remove a course with the same id as of course2 from being a pre course of course1.
// no need to do any free here. just erase the pre course connection.
// all the rest pre courses of course1 should be keeped sorted, according to their id (lexicographic order,
// from small to big).
// Either course1 or course2 must not be NULL. (handled by assert).
// return value : COURSE_OK,
//                COURSE_NOT_EXIST if a course with the id of course2 is not defined as a pre course of course1
CourseResult removePreCourse(Course course1, Course course2);

//------------------------------------------------------------------------------------------
// display in a single line the details of course1 as follows (from left to right) :
// id , name , credits , ids of pre courses.
// credits is displayed in the format of %.1f
// the ids of pre courses are dispalyed sorted from left to right from small to big.
// between every 2 adjacent words there is a single space. no spaces in the beginning of the line or
// at its end. no new line at the end of the displayed line.

void displayCourse(Course course1);

//------------------------------------------------------------------------------------------
// deallocate all relevant memory of course1 and stop using it.
void destroyCourse(Course course1);

//------------------------------------------------------------------------------------------


#endif // COURSE_H
