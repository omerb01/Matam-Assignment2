//
// Created by Omer on 22/11/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "CourseSystem.h"

int main()
{
    CourseSystem system = createSystem("sys");

    Course course1;
    createCourse("234118", "omer", 5.0, &course1);

    Course course2;
    createCourse("234111", "m0she", 5.0, &course2);

    Course course3;
    createCourse("234141", "I hate combi", 3.5, &course3);

    Course course4;
    createCourse("234142", "I hate c0mbi", 3.5, &course4);

    sysAddCourse(system, course1);
    sysAddCourse(system, course2);
    sysAddCourse(system, course3);
    sysAddCourse(system, course4);

    sysAddPreCourse(system, "omer", "I hate combi");

    displaySystem(system);


    return 0;
}