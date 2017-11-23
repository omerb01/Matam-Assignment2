//
// Created by Omer on 22/11/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Course.h"

int main()
{
    Course c1;
    createCourse("234111", "Computer Science", 3.0, &c1);
    Course c2;
    createCourse("234118", "Omer", 3.0, &c2);

    addElementStart(c1->preCourses, c2);

    displayCourse(c1);

    return 0;
}