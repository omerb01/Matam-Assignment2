//
// Created by Omer on 22/11/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Course.h"

int main()
{
    DynamicArray da = createDynamicArray();

    Course c1;
    createCourse("234111", "Computer Science", 3.0, &c1);

    addElementStart(da, c1);
    printf("%d", da->len);
    removeElement(da, 0);
    printf("%d", da->len);

    return 0;
}