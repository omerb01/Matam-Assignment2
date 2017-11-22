//
// Created by Omer on 22/11/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DynamicArray.h"

DynamicArray createDynamicArray() {
    DynamicArray dynamic_array = (DynamicArray) malloc(sizeof(DynamicArray));
    if (dynamic_array == NULL) return NULL;
    dynamic_array->len = 0;
    dynamic_array->elements = NULL;
    return dynamic_array;
}

static DAResult updateElementsSize(DynamicArray dynamic_array, int new_size) {
    Element *array = malloc(sizeof(dynamic_array->elements) * new_size);
    if (array == NULL) return DA_MEMORY_ERROR;

    for (int i = 0; i < new_size; i++) {
        if (i >= dynamic_array->len) {
            array[i] = NULL;
        } else {
            array[i] = dynamic_array->elements[i];
        }
    }
    free(dynamic_array->elements);

    dynamic_array->len = new_size;
    dynamic_array->elements = array;
    return DA_OK;
}

#define UPDATE_ELEMENTS_SIZE($$dynamic_array$$, $$size$$) \
    if (updateElementsSize(($$dynamic_array$$), ($$size$$)) == DA_MEMORY_ERROR) { \
        return DA_MEMORY_ERROR; \
    } \

#define CHECK_INDEX($$dynamic_array$$, $$index$$) \
    if ((($$index$$) < 0 || ($$index$$) >= ($$dynamic_array$$)->len) && \
($$index$$) != 0) { \
        return DA_ILLEGAL_INDEX; \
    } \


static void swapElements(Element *element1, Element *element2) {
    assert(element1 != NULL && element2 != NULL);
    Element temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

DAResult addElementBefore(DynamicArray dynamic_array, Element element, int
index) {
    CHECK_INDEX(dynamic_array, index);
    UPDATE_ELEMENTS_SIZE(dynamic_array, dynamic_array->len + 1);

    for (int i = dynamic_array->len - 1; i >= 0; i--) {
        if (index == i) {
            (dynamic_array->elements)[i] = element;
            break;
        }
        if (i != 0) {
            swapElements(dynamic_array->elements + i,
                         dynamic_array->elements + i - 1);
        }
    }

    return DA_OK;
}

DAResult addElementStart(DynamicArray dynamic_array, Element element) {
    return addElementBefore(dynamic_array, element, 0);
}

int main() {
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

    for (int i = 0; i < da->len; ++i) {
        assert(da->elements[i] != NULL);
        printf("%d, ", da->elements[i]->data);
    }

    free(element1);
    free(element2);
    free(da->elements);
    free(da);
    return 0;
}