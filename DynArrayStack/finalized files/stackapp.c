/*	stack.c: Stack application. */
/* CS261- Assignment 2*/
/* Name: Joseph Fuerst
 * Date:4/13/2016
 * Solution description: Tests the stack implementation in dynamicArray.c by using it to see if a string of (), {}, and [] is balanced.
 */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
    char check;
    char cmp;
    DynArr *stck;
	stck = newDynArr(100);
    do
    {
        check = nextChar(s);

        if (check == '(' || check == '{' || check == '[')
        {
            pushDynArr(stck, check);
        }
        else if (check == ')' || check == '}' || check == ']')
        {
			if (isEmptyDynArr(stck))
			{
				return 0;
			}
            cmp = topDynArr(stck);
            if ((check == ')' && cmp == '(') || (check == '}' && cmp == '{') || (check == ']' && cmp == '['))
            {
                popDynArr(stck);
            }
        }
    } while (check != '\0');
    if (isEmptyDynArr(stck))
    {
        return 1;
    }
    else
        return 0;
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	if (s == NULL)
	{
		printf("Error: an argument is required.");
	}
	else
	{	
		int res;

		printf("Assignment 2\n");

		res = isBalanced(s);

		if (res)
			printf("The string %s is balanced\n",s);
		else
			printf("The string %s is not balanced\n",s);
	}
	return 0;
}

