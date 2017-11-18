#ifndef COURSE_SYSTEM_H
#define COURSE_SYSTEM_H

#include "DynamicArray.h"
#include "Course.h"

typedef struct course_system
{
    char *name;
    DynamicArray courses;
} *CourseSystem;


/*******************************************************************/
/* Interface of data type CourseSystem  */


typedef enum { SYS_OK , SYS_COURSE_ALREADY_EXIST , SYS_MEMORY_PROBLEM ,
               SYS_NOT_IN_SYSTEM , SYS_ALREADY_PRE_COURSE , SYS_NOT_PRE_COURSE } SysResult;

//------------------------------------------------------------------------------------------
// create a new empty system whose name is the parameter name.
// if cannot create then NULL is returned.
CourseSystem createSystem(char *name);

//------------------------------------------------------------------------------------------
//return the number of courses that are currently defined in the system (which means - have been added
//                                                                      to the system).
//sys must not be NULL (handled by assert)
int sysNumCourses(CourseSystem sys);

//------------------------------------------------------------------------------------------
// add the course c1 to the system sys.
// sys and c1 must not be NULL (handled by assert)
// all the courses in the system are kept in a dynamic array. They are kept
// in a sorted order according to the course id, from small to big, left to right.
// return values :
// SYS_OK
// SYS_COURSE_ALREADY_EXIST if there is already a course with the same id as the id of c1 in the system.
// SYS_MEMORY_PROBLEM - there is a memory problem.

SysResult sysAddCourse(CourseSystem sys, Course c1);

//------------------------------------------------------------------------------------------
// remove the course whose id is course_id from the system sys.
// this operation frees all memory concerned with the course.
// in addition, if the course is defined as a pre course in other courses, then
// it stops being a pre course of any other course.
// sys and course_id must not be NULL (handled by assert).
// return values :
// SYS_OK
// SYS_NOT_IN_SYSTEM if there is no course with course_id in the system.

SysResult sysRemoveCourse(CourseSystem sys, char *course_id);

//------------------------------------------------------------------------------------------
// check if the course with id course_id2 is defined as a pre course of the course with id course_id1
// the answer (1 or 0) is written to the output parameter ans.
// if the returned value is not SYS_OK then ans is not changed.
// sys, course_id1 , course_id2 , ans must not be NULL (handled by assert)
// return values :
// SYS_OK
// SYS_NOT_IN_SYSTEM if either course_id1 or course_id2 have not been added to the system

SysResult sysIsPreCourse(CourseSystem sys, char *course_id1 , char *course_id2, int *ans);

//------------------------------------------------------------------------------------------
// add the course with id course_id2 to be a pre course of the course with id course_id1
// sys, course_id1 and course_id2 must not be NULL (handled by assert)
// return values :
// SYS_OK
// SYS_NOT_IN_SYSTEM if either course_id1 or course_id2 have not been added to the system
// SYS_ALREADY_PRE_COURSE if course_id2 is already defined as a pre course of course_id1
// SYS_MEMORY_PROBLEM if there is a memory problem

SysResult sysAddPreCourse(CourseSystem sys, char *course_id1 , char *course_id2);

//------------------------------------------------------------------------------------------
// remove the course with id course_id2 from being a pre course of the course with id course_id1
// sys, course_id1 and course_id2 must not be NULL (handled by assert)
// return values :
// SYS_OK
// SYS_NOT_IN_SYSTEM if either course_id1 or course_id2 have not been added to the system
// SYS_NOT_PRE_COURSE if course_id2 is not defined as a pre course of course_id1

SysResult sysRemovePreCourse(CourseSystem sys, char *course_id1 , char *course_id2);

//------------------------------------------------------------------------------------------
// update the name of the course whose id is course_id with new_name.
// sys, course_id and new_name must not be NULL (handled by assert)
// return values :
// SYS_OK
// SYS_NOT_IN_SYSTEM if course_id have not been added to the system
// SYS_MEMORY_PROBLEM if there is a memory problem

SysResult sysUpdateCourseName(CourseSystem sys, char *course_id, char *new_name);

//------------------------------------------------------------------------------------------
// display the contents of the system
// first line contains the system name
// in the rest of the lines there will be all the courses that have been added to the system
// Each course is displayed in a separate line, according to the format of the displayCourse function.
// in the end of each line there is a new line.
// all the lines are displayed in a sorted order according to the id of the course, from small to big, up to down.
// sys must not be NULL (will be handled by assert)
void displaySystem(CourseSystem sys);

//------------------------------------------------------------------------------------------
// deallocate all memory used by the system and close the system.
void destroySystem(CourseSystem sys);

//------------------------------------------------------------------------------------------

#endif // COURSE_SYSTEM_H
