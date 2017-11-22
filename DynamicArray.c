//
// Created by Omer on 22/11/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Course.h"
#include "DynamicArray.h"


#define UPDATE_ELEMENTS_SIZE($$dynamic_array$$, $$size$$) \
    if (updateElementsSize(($$dynamic_array$$), ($$size$$)) == DA_MEMORY_ERROR) { \
        return DA_MEMORY_ERROR; \
    } \

#define CHECK_INDEX($$dynamic_array$$, $$index$$) \
    if ((($$index$$) < 0 || ($$index$$) >= ($$dynamic_array$$)->len)) { \
        return DA_ILLEGAL_INDEX; \
    } \


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
            dynamic_array->elements[i] = element;
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
    if (dynamic_array->len == 0) {
        UPDATE_ELEMENTS_SIZE(dynamic_array, dynamic_array->len + 1);
        dynamic_array->elements[0] = element;
        return DA_OK;
    }

    return addElementBefore(dynamic_array, element, 0);
}

DAResult addElementEnd(DynamicArray dynamic_array, Element element) {
    UPDATE_ELEMENTS_SIZE(dynamic_array, dynamic_array->len + 1);
    dynamic_array->elements[dynamic_array->len - 1] = element;
    return DA_OK;
}

// TODO: CHECK WITH ILIYA'S FUNCTION
DAResult indexOfElement(DynamicArray dynamic_array, Element element, int
base_index, int *result_index) {
    CHECK_INDEX(dynamic_array, base_index);
    assert(result_index != NULL);

    *result_index = -1;
    for (int i = base_index; i < dynamic_array->len; ++i) {
        if (coursesEqualId(element, dynamic_array->elements[i]) == 1) {
            *result_index = i;
            break;
        }
    }

    return DA_OK;
}

DAResult removeElement(DynamicArray dynamic_array, int index) {
    CHECK_INDEX(dynamic_array, index);

    for (int i = index; i < dynamic_array->len - 1; ++i) {
        swapElements(dynamic_array->elements + i,
                     dynamic_array->elements + i + 1);
    }

    UPDATE_ELEMENTS_SIZE(dynamic_array, dynamic_array->len - 1);
    return DA_OK;
}

DAResult updateElement(DynamicArray dynamic_array, int index, Element element) {
    CHECK_INDEX(dynamic_array, index);
    dynamic_array->elements[index] = element;
    return DA_OK;
}

// TODO: CHECK WITH ILIYA'S FUNCTION
DAResult displayElement(DynamicArray dynamic_array, int index) {
    CHECK_INDEX(dynamic_array, index);
    displayCourse(dynamic_array->elements[index]);
    return DA_OK;
}

// TODO: CHECK WITH ILIYA'S FUNCTION
void displayAllElements(DynamicArray dynamic_array) {
    for (int i = 0; i < dynamic_array->len; ++i) {
        displayElement(dynamic_array, i);
        printf("\n");
    }
}

int size(DynamicArray dynamic_array) {
    return dynamic_array->len;
}

void destroyDynamicArray(DynamicArray dynamic_array) {
    free(dynamic_array->elements);
    free(dynamic_array);
}