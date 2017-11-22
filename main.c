//
// Created by Omer on 22/11/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DynamicArray.h"

int main(){

//########################## OMER ###############################

    DynamicArray da = createDynamicArray();

    Element element1 = malloc(sizeof(Element));
    element1->data = 111;

    Element element2 = malloc(sizeof(Element));
    element2->data = 222;

    addElementStart(da, element1);
    addElementStart(da, element1);
    addElementStart(da, element1);
    addElementStart(da, element1);

    addElementBefore(da, element2, 1);
    addElementEnd(da, element2);

    for (int i = 0; i < da->len; ++i) {
        assert(da->elements[i] != NULL);
        printf("%d, ", da->elements[i]->data);
    }
    printf("\n");

    removeElement(da, 1);

    for (int i = 0; i < da->len; ++i) {
        assert(da->elements[i] != NULL);
        printf("%d, ", da->elements[i]->data);
    }
    printf("\n");

    free(element1);
    free(element2);
    free(da->elements);
    free(da);

//########################## ILIYA ###############################

    return 0;
}