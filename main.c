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
    createCourse("234111", "moshe", 5.0, &course2);

    sysAddCourse(system, course1);
    sysAddCourse(system, course2);

    printf("%d\n", system->courses->len);
    printf("%s\n", system->courses->elements[0]->id);
    printf("%s\n", system->courses->elements[1]->id);

    return 0;
}