/* Standard: gnu99 */

#include <stdlib.h>

#include "data-structs/vector.h"

#ifdef VECTOR_DEBUG
	#include <stdio.h>
	#define COLOR_CYAN  "\x1b[36m"
	#define COLOR_RESET "\x1b[0m"
#endif

/*
 * Constructs a resizable array using a struct named, Vector.
 * The struct 'Vector' has two members,
 * 	  int size: the number of indexes in the array
 * 	  GenType* array: a union pointer
 * 	  (GenType is included from the header file, 'Vector.h')
 * Argument(s):
 * 	  int size: The size of the array.
 * 	  GenType* array: The pointer to the array.
 * Memory Management:
 * 	  free the pointer to the array when done.
 * Returns: The struct representing a resizable array.
 */
Vector vector_init(int size) {
	Vector list;
	list.array = (GenType*) calloc(size, sizeof(GenType));
	list.size = size;
	return list;
}

/*
 * Emptys the array in the struct and resets the size to 0.
 * Argument(s):
 *    Vector* list: points to the struct containing the array.
 */
void vector_empty(Vector* list) {
	list->size = 0;
	free(list->array);
	list->array = NULL;
}

/*
 * Gets the element in the structs array at the given index.
 * Argument(s):
 *    int index: the location to retrieve the element from.
 * Returns: The element retrieved from the array.
 */
 GenType vector_get(Vector* list, int index) {
	#ifdef VECTOR_DEBUG
		printf(COLOR_CYAN "VECTOR: GET: %s\n" COLOR_RESET, list->array[index].String);
	#endif
	return list->array[index];
}

/*
 * Sets the element in the structs array at the given
 * index to the given element.
 * Argument(s):
 *    Vector* list: points to the struct containing the array.
 *    int index: the location to set the element at.
 *    GenType value: the new value.
 */
void vector_set(Vector* list, int index, GenType value) {
	list->array[index] = value;
}

/*
 * Adds an element to the structs array at the given index.
 * Argument(s):
 *    Vector* list: points to the struct containing the array.
 *    int index: the location to add the element to.
 *    GenType value: the new value.
 */
void vector_add(Vector* list, int index, GenType value) {
	#ifdef VECTOR_DEBUG
		printf(COLOR_CYAN "VECTOR: Adding value to index %d\n" COLOR_RESET, index);
	#endif
	list->size += 1;
	GenType* tmp = (GenType*) calloc(list->size, sizeof(GenType));
	unsigned int i = 0, o = 0;
	while (i < list->size) {
		if (i == index) {
			((GenType*) tmp)[i] = value;
			o++;
		} else tmp[i] = vector_get(list, i-o);
		i++;
	}
	free(list->array);
	list->array = NULL;
	list->array = tmp;
}

/*
 * Deletes an element from the structs array at the given index.
 * Argument(s):
 *    Vector* list: points to the struct containing the array.
 *	  int index: the location to delete the element from.
 */
void vector_delete(Vector* list, int index) {
	#ifdef VECTOR_DEBUG
		printf(COLOR_CYAN "VECTOR: Deleting value at index %d\n" COLOR_RESET, index);
	#endif
	list->size -= 1;
	GenType* tmp = (GenType*) calloc(list->size, sizeof(GenType));
	unsigned int i = 0, o = 0;
	while (i < list->size) {
		if (i == index) o++;
		tmp[i] = vector_get(list, i+o);
		i++;
	}
	free(list->array);
	list->array = NULL;
	list->array = tmp;
}