//
//<<<<<<< Updated upstream
// Created by Omer on 22/11/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Course.h"


//int main(){

//########################## OMER ###############################


//########################## ILIYA ###############################
/*
    return 0;
=======*/
// Created by Ilya on 11/22/2017.
//


int main()
{
    Course tst,tst2;
    CourseResult rsl1 = createCourse("FUCK01", "whatthehell", 0.01, &tst);
    CourseResult rsl2 = createCourse("LITASFUCKKKKKk", "yeahright", 666, &tst2);
    if (rsl1 == COURSE_OK && rsl2 == COURSE_OK) printf("...nothing here...\n");
    printf("%s less than %s ? %s\n", tst->id,tst2->id, courseLessThan(tst,tst2) ? "yes":"no");
    printf("%s equal to %s ? %s", tst->id,tst2->id, coursesEqualId(tst,tst2) ? "yes":"no");

//>>>>>>> Stashed changes
}