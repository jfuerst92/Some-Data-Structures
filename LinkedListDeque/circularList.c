/**********************
 * Name: Joseph Fuerst
 * Date: 4/21/2014
 **********************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	assert(list != 0);
	list->sentinel = (struct Link*) malloc(sizeof(struct Link)); //initialize sentinel
	assert(list->sentinel != 0);
	list->sentinel->next = list->sentinel; //In an empty circular linked list, sentinel points to itself both ways
	list->sentinel->prev = list->sentinel;
	list->size = 0; //size is 0, no links yet
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link* newLink = (struct Link*) malloc(sizeof(struct Link)); //create new link
	assert(newLink != 0);
	newLink->value = value; //assign value
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
    assert(link != 0);
    struct Link* newLink = createLink(value); //sets newLink to address of newly created link
    link->next->prev = newLink; //next 4 lines inserts link into list, updates next and prev values
    newLink->next = link->next;
    link->next = newLink;
    newLink->prev = link;
    list->size++; //size increases by one

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
    assert(list->size != 0);
    link->prev->next = link->next; //sets next val to skip over link
    link->next->prev = link->prev; //sets prev val to skip over link
    free(link); //deletes the link
    list->size--; //decrease size
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (list->size != 0) //while list has links
    {
        //printf("Deleting link with value of %g...\n", circularListFront(list));  //For testing purposes, accidentally decremented size here as well
        removeLink(list, list->sentinel->next); //remove front link from list
    }
    free(list->sentinel); //free space for sentinel
    free(list); //free list
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel, value); //adds link after sentinel
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	addLinkAfter(list, list->sentinel->prev, value); //adds link before sentinel
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list->size != 0);
	return list->sentinel->next->value; //return value of link after sentinel
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list->size != 0);
	return list->sentinel->prev->value; //return valeu of link before sentinel
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list->size != 0);
	removeLink(list, list->sentinel->next); //remove link after sentinel
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    assert(list->size != 0);
	removeLink(list, list->sentinel->prev); //remove link before sentinel
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	assert(list != 0);
	if (list->size == 0 || list->sentinel->next == list->sentinel); //checks if list is empty. if size is in error, checks that sentinel points to itself
    {
        return 1;
    }
    return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	assert(list->size != 0);
	struct Link* curLink = list->sentinel->next; //curLink points to first link
	while (curLink != list->sentinel) //while curlink does not point to end of list
    {
        printf("%g\n", curLink->value); //print value of curLink
        curLink = curLink->next; //curLink moves to next link
    }
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list->size != 0);
	struct Link* curLink = list->sentinel; //curLink point to sentinel
	struct Link* temp; //temp value holds next value while dswapping
	do
    {
        temp = curLink->next; //next stored in temp
        curLink->next = curLink->prev; //prev stored in next
        curLink->prev = temp; //next stored in prev
        curLink = curLink->prev; //curLink moves to 'next' link in list

	} while (curLink != list->sentinel); //do until end of list
}
