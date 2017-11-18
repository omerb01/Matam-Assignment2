#include <stdio.h>

#include "Course.h"
#include "CourseSystem.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);


int main(int argc, char **argv)
{

    CourseSystem sys=NULL;
    SysResult rs = SYS_OK;
    CourseResult rc = COURSE_OK;

    sys=createSystem("Technion_2017_2018");
    ASSERT("1.1" , sys!=NULL)

    Course c1;
    rc = createCourse("234114", "Introduction to Computer Science", -4, &c1);
    ASSERT("1.2" , rc==COURSE_ILLEGAL_PARAMETER)
    rc = createCourse("234114", "Introduction to Computer Science", 4, &c1);
    ASSERT("1.3" , rc==COURSE_OK)

    int n=sysNumCourses(sys);
    ASSERT("1.4" , n==0)

    rs=sysAddCourse(sys, c1);
    n=sysNumCourses(sys);
    ASSERT("1.5" , n==1)

    rs=sysAddCourse(sys, c1);
    ASSERT("1.6" , rs==SYS_COURSE_ALREADY_EXIST)

    rc = createCourse("234218", "Data Structures 1", 3, &c1);
    rs=sysAddCourse(sys, c1);
    n=sysNumCourses(sys);
    ASSERT("1.5" , n==2)

    int ans=-1;
    rs=sysIsPreCourse(sys, "234122", "234114", &ans);
    ASSERT("1.6" , rs==SYS_NOT_IN_SYSTEM && ans==-1)

    rc = createCourse("234122", "Introduction to Systems Programming", 3, &c1);
    rs=sysAddCourse(sys, c1);
    n=sysNumCourses(sys);
    ASSERT("1.7" , n==3)

    rs=sysAddPreCourse(sys, "234122", "234114");
    ASSERT("1.6" , rs==SYS_OK)

    rs=sysAddPreCourse(sys, "234122", "234114");
    ASSERT("1.8" , rs==SYS_ALREADY_PRE_COURSE)

    displaySystem(sys);
/*
Technion_2017_2018
234114 Introduction to Computer Science 4
234122 Introduction to Systems Programming 3 234114
234218 Data Structures 1 3
*/

    rs=sysRemovePreCourse(sys, "234122", "234114");
    ASSERT("1.9" , rs==SYS_OK)

    rs=sysRemovePreCourse(sys, "234122", "234114");
    ASSERT("1.10" , rs==SYS_NOT_PRE_COURSE)

    displaySystem(sys);
/*
Technion_2017_2018
234114 Introduction to Computer Science 4
234122 Introduction to Systems Programming 3
234218 Data Structures 1 3
*/

    rs=sysAddPreCourse(sys, "234218", "234122");
    ASSERT("1.11" , rs==SYS_OK)
    displaySystem(sys);
/*
Technion_2017_2018
234114 Introduction to Computer Science 4
234122 Introduction to Systems Programming 3
234218 Data Structures 1 3 234122
*/

    rs=sysRemoveCourse(sys, "234118");
    ASSERT("1.12" , rs==SYS_NOT_IN_SYSTEM)

    rs=sysRemoveCourse(sys, "234122");
    ASSERT("1.13" , rs==SYS_OK)
    displaySystem(sys);
/*
Technion_2017_2018
234114 Introduction to Computer Science 4
234218 Data Structures 1 3
*/
/* remark - also destroy 234122 */

    n=sysNumCourses(sys);
    ASSERT("1.14" , n==2)

    rs=sysUpdateCourseName(sys, "234122", "Systems Programming");
    ASSERT("1.15" , rs==SYS_NOT_IN_SYSTEM)

    rs=sysUpdateCourseName(sys, "234114", "Introduction to Computer Science M");
    ASSERT("1.16" , rs==SYS_OK)

    displaySystem(sys);
/*
Technion_2017_2018
234114 Introduction to Computer Science M 4
234218 Data Structures 1 3
*/

    destroySystem(sys);
    return 0;
}

