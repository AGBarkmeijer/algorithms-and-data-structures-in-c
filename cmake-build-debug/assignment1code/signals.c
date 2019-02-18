/*
* Algorithms and Data Structures, Assignment 1: Digital signals
* Authors: s2615371, s3547558
*
* Program description:
* This program takes as input a number of digital signals, and for each of
* these signals it prints its level representation.
*/

#include <stdio.h>
#include <stdlib.h>

#include "LibStack.h"
#include "LibQueue.h"
#include "LibList.h"

/* Function that determines and prints the layers */
void printLayers(int value, int index, Stack *stp) {
    int numberOfPops = 0;

    while (!isEmptyStack(*stp) && value < (stp->array)[stp->top - 1]) {
        int poppedInt = pop(stp);
        numberOfPops++;

        /* Determine the startpoint of the highest layer(s) by popping values
        from the stack until we encounter a value that is not equal to the
        first value that we popped from the stack. */
        while (!isEmptyStack(*stp) && (stp->array)[stp->top - 1] == poppedInt) {
            pop(stp);
            numberOfPops++;
        }

        /* Print the intervals that are at the highest layer(s).
        We have to make a distiction between situations when the stack is empty
        and when the stack it is not, in order to avoid invalid reads. */
        if (!isEmptyStack(*stp)) {
          for (int k = poppedInt; k > (stp->array)[stp->top - 1] && k > value; k--) {
            printf("[%d,%d)@%d ", stp->top, index, k);
          }
        } else {
          for (int k = poppedInt; k > value; k--) {
            printf("[%d,%d)@%d ", stp->top, index, k);
          }
        }

    }
    /* Push a lower value onto the stack, to represent the lower layers that we
    did not yet print */
    for (int i = 0; i < numberOfPops; i++) {
      push(value, stp);
    }

}

int main(int argc, char *argv[]) {
    int numOfSignals;

    // Read how many signals there will be
    scanf("%d", &numOfSignals);

    for (int i = 0; i < numOfSignals; i++) {

        int signalLength, value;

        // Read the length of the signal and make a new stack of this size.
        scanf("%d", &signalLength);
        Stack st = newStack(signalLength);

        /* To print correct intervals of the layers, we need to keep track of the
        time points (index) of the values */
        int index = 0;

        // Read the values of the signal one by one
        for (int j = 0; j < signalLength; j++) {
            // Read the next signal value
            scanf("%d", &value);

            // If value is higher than its predecessor push it onto the stack
            if (isEmptyStack(st) || value >= (st.array)[st.top - 1]) {
                push(value, &st);
            }
                /* If value is lower than its predecessor, first determine the layers and
                print them, and then push the value onto the stack */
            else {
                printLayers(value, index, &st);
                push(value, &st);
            }
            // Increase the index and go to the next value in the signal.
            index++;
        }

        /* As of now the stack consists of a decreasing (or rather non-increasing)
        set of numbers (i.e. if we pop the value n after we pop the value m, we have
        that n <= m). We still need to print these layers. */
        printLayers(0, index, &st);

        // Free the stack
        freeStack(st);
        // Make sure that the output for the next signal is printed on a new line
        printf("\n");
    }

    return 0;
}
