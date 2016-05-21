/**********************
 * Name: Joseph Fuerst
 * Date: 4/21/2014
 **********************/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	list->frontSentinel = malloc(sizeof(struct Link)); //initialize sentinels
    list->backSentinel = malloc(sizeof(struct Link));
    assert(list->frontSentinel != 0);
    assert(list->backSentinel != 0);
    list->frontSentinel->next = list->backSentinel; //link front sentinel and back sentinel
    list->backSentinel->prev = list->frontSentinel;
    list->size = 0;

}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    struct Link* newLink = (struct Link *) malloc(sizeof(struct Link)); //create new link
    assert(newLink != 0);
    newLink->value = value; //add value to link
    newLink->next = link;  //set next and prev pointers to include new link
    newLink->prev = link->prev;
    link->prev->next = newLink;
    link->prev = newLink;
    list->size++; //increase size

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	assert(!linkedListIsEmpty(list));
    link->prev->next = link->next; //next and prev pointers skip over current link
    link->next->prev = link->prev;
    list->size--; //size decreases
    free(link); //free link

}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->frontSentinel->next, value); //adds link to front
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	addLinkBefore(list, list->backSentinel, value); //add link before sentinel
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	return(list->frontSentinel->next->value); //return value of front link

}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	return(list->backSentinel->prev->value); //return value of link before sentinel
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	removeLink(list, list->frontSentinel->next); //remove front link
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	removeLink(list, list->backSentinel->prev); //remove link before sentinel
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	return list->size == 0; //checks if size is 0
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != 0);
	struct Link* curLink = list->frontSentinel; //curLink points to frontSentinel
	while (curLink->next != list->backSentinel) //while it hasnt reached back sentinel
    {
        curLink = curLink->next; //curLink points to next value
        printf("%d\n", curLink->value); //print value
    }

}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	addLinkBefore(list, list->frontSentinel->next, value); //add link to list

}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	if (list->size == 0)
        return 0;

    struct Link* curLink = list->frontSentinel; //curLink points to front sentinel

    while(curLink->next != list->backSentinel) //before it reaches back sentinel
    {
        curLink = curLink->next; //curLink points to next value
        if (curLink->value == value) //if curlinks value is equal to argument value, return 1
        {
           return 1;
        }
    }
    return 0;


}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    int removed = 0; //bool to check if already removed
	assert(list != 0);
	if (list->size == 0) //if no links, return without doing anything.
    {
        return;
    }
    struct Link* curLink = list->frontSentinel; //curLink points to front sentinel

    while(curLink->next != list->backSentinel && removed == 0)  //before list ends and while link is not removed
    {
         curLink = curLink->next; //curLink points to next value
         if (curLink->value == value) //if value is found
         {
            removeLink(list, curLink); //remove link
            removed = 1; //terminate loop
         }
    }


}
