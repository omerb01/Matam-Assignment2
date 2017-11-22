#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H


typedef struct cours *Element;

typedef struct dynamic_array
{
    int len;
    Element *elements;
} *DynamicArray;

DynamicArray da;


/*******************************************************************/
/* Interface of data type DynamicArray  */


typedef enum { DA_OK , DA_MEMORY_ERROR , DA_ILLEGAL_INDEX } DAResult;

//------------------------------------------------------------------------------------------
// Create a new empty array
// returns the new array or NULL if can not create one
DynamicArray createDynamicArray();


//------------------------------------------------------------------------------------------
// Enlarge the array and add a given element to the array in a position that appears
// just before a given existing index. First index in the array is 0, as in a regular array.
// the added element is inserted to the array by a simple assignment (without duplication).
// return values : DA_OK, DA_MEMORY_ERROR, DA_ILLEGAL_INDEX
DAResult addElementBefore(DynamicArray, Element, int);

//------------------------------------------------------------------------------------------
// Enlarge the array and add a given element to the array in a position at the start
// of the array. the added element is inserted to the array by a simple assignment (without duplication).
// return values : DA_OK, DA_MEMORY_ERROR.
DAResult addElementStart(DynamicArray, Element);

//------------------------------------------------------------------------------------------
// Enlarge the array and add a given element to the array in a position at the end
// of the array. the added element is inserted to the array by a simple assignment (without duplication).
// return values : DA_OK, DA_MEMORY_ERROR.
DAResult addElementEnd(DynamicArray, Element);

//------------------------------------------------------------------------------------------
// result_index gets an index in the array da at which there exists an element that its id is equal to the id if a given element c.
// the result index is the first (lowest) index that is equal or grea   ter to base_index.
// The comparison between 2 elements is done by using the function coursesEqualId that is guaranteed to be supplied by the data type Course.
// if No element is found, then result_index gets -1.
// da ,c and result_index must not be NULL. (checked by assert).
// return values : DA_OK, DA_ILLEGAL_INDEX.
DAResult indexOfElement(DynamicArray da, Element c , int base_index, int *result_index);


//------------------------------------------------------------------------------------------
// Delete an element (a course) at a given position (index)
// of the array. The size of the array is updated.
// return values : DA_OK, DA_MEMORY_ERROR , DA_ILLEGAL_INDEX
DAResult removeElement(DynamicArray, int);

//------------------------------------------------------------------------------------------
// update an existing element in a given position (index) to be identical
// to a given element. the given element must not be changed.
// no need to duplicate element. just do a simple assignment.
// return values : DA_OK, DA_MEMORY_ERROR , DA_ILLEGAL_INDEX
DAResult updateElement(DynamicArray da, int id, Element element);

//------------------------------------------------------------------------------------------
// display the element in the given index i.
// this function uses the displayCourse function th
// at is guaranteed to exist in the Course data type.
// no need to do here '\n'.
// return values : DA_OK, DA_ILLEGAL_INDEX
DAResult displayElement(DynamicArray da, int i);

//------------------------------------------------------------------------------------------
// display all the elements in the array according to their position in the array, from left to right.
// each element is displayed in a single line and '\n at the end of the line.
// the elements are displayed by using the displayCourse function that is guaranteed to exist in the Course data type.
// return values : DA_OK, DA_ILLEGAL_INDEX
void displayAllElements(DynamicArray);

//------------------------------------------------------------------------------------------
// returns the number of elements in the array.
// return values : CDA_OK

int size(DynamicArray);

//------------------------------------------------------------------------------------------
// deallocate all relevant memory and stop using the array.
void destroyDynamicArray(DynamicArray);

//------------------------------------------------------------------------------------------


#endif // DYNAMIC_ARRAY_H
