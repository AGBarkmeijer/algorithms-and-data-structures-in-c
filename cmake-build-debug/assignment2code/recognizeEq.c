/* recognizeEq.c
 * s2615371, s3547558
 * 19 February 2019
 */

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeEq.h"
#include "recognizeExp.h"


/* The functions acceptTermEq, acceptExpressionEq and acceptEquation have as
 * argument a pointer to a token list. They check whether the token list
 * has an initial segment that can be recognized as term, expression or
 * an equation, respectively.
 * When that is the case, they yield the value 1 and the pointer points to the rest of
 * the token list. Otherwise they yield 0 and the pointer remains unchanged.
 */

int acceptTermEq(List *lp) {
  if (*lp == NULL) {
    return 0;
  }
  if (acceptIdentifier(lp)) {
    if ((*lp != NULL) && (*lp)->tt == Symbol && (*lp)->t.symbol == '^') {
      if ((*lp)->next != NULL &&  ((*lp)->next)->tt == Number ) {
        return (acceptCharacter(lp,'^') && acceptNumber(lp));
      }
      return 0;
    }
    return 1;
  }
  else if (acceptNumber(lp)) {
    if (acceptIdentifier(lp)) {
      if ((*lp != NULL) && (*lp)->tt == Symbol && (*lp)->t.symbol == '^') {
        if ((*lp)->next != NULL &&  ((*lp)->next)->tt == Number ) {
          return (acceptCharacter(lp,'^') && acceptNumber(lp));
        }
        return 0;
      }
      return 1;
    }
    return 1;
  }
  return 0;
}

int acceptExpressionEq(List *lp) {
  if (*lp == NULL) {
    return 0;
  }
   if ( acceptTermEq(lp)) {
     while (acceptCharacter(lp,'+') || acceptCharacter(lp,'-') ) {
       if (!acceptTermEq(lp) ) {
         return 0;
       }
     } /* no + or -, so we reached the end of the expression */
     return 1;
   }
   else if (acceptCharacter(lp,'-')) {
     if ( acceptTermEq(lp)) {
       while (acceptCharacter(lp,'+') || acceptCharacter(lp,'-') ) {
         if (!acceptTermEq(lp) ) {
           return 0;
         }
       } /* no + or -, so we reached the end of the expression */
       return 1;
     }
   }
   return 0;
}

int acceptEquation(List *lp) {
   /* A tokenlist is only an equation if it is non-empty initially, and empty
    * after we have found one equation. */
   if (*lp != NULL &&
       acceptExpressionEq(lp) &&
       acceptCharacter(lp, '=') &&
       acceptExpressionEq(lp) &&
       *lp == NULL) {
     return 1;
   }
   return 0;
}

/* Check if the equation is an equation in 1 variable.
 * If so, determine the highest power of this variable. This is the degree.
 * The output is -1 if there are 0 variables or more dan 1 variables.
 * The output is equal to the degree of the variable if there is 1 variable.
 */
int checkVarAndDegree(List *tl) {
    char *ident, *ident2;
    int degree = -1;

    // Find first variable.
    while ((*tl) != NULL && (*tl)->tt != Identifier) {
      (*tl) = (*tl)->next;
    }
    if ((*tl) != NULL) {
      ident = (*tl)->t.identifier;
      (*tl) = (*tl)->next;
    }

    // Find the degree of the first variable.
    if ((*tl) != NULL && ((*tl)->t).symbol != '^') {
      degree = 1;
    }
    if ((*tl) != NULL && ((*tl)->t).symbol == '^' && (((*tl)->next)->t).number > degree) {
      degree = ((*tl)->next)->t.number;
    }

    // Check if there are more variables.
    while ((*tl) != NULL) {
      while ((*tl) != NULL && (*tl)->tt != Identifier) {
        (*tl) = (*tl)->next;
      }
      /* For each variable we find, compare it
       * with the first variable we found. If we find a variable that is different
       * from the first one we found in this equation, return -1 to indicate that
       * the equation is not an equation in 1 variable.
       */
      if ((*tl) != NULL) {
        ident2 = (*tl)->t.identifier;
        if (!sameIdentifier(ident, ident2)) {
          return -1;
        }
        (*tl) = (*tl)->next;
      }
      /* Each time there is an occurrence of the first variable we found,
       * compare its power to the current value in the degree parameter. If the
       * power is higer, set the degree to this new value.
       */
      if ((*tl) != NULL && ((*tl)->t).symbol != '^' && degree < 1) {
        degree = 1;
      }
      if ((*tl) != NULL && ((*tl)->t).symbol == '^' && (((*tl)->next)->t).number > degree) {
        degree = (((*tl)->next)->t).number;
      }
    }
    return degree;
}

/* Function to check if two identifiers are the same. */
int sameIdentifier(char *id1, char *id2) {
  for (int i=0; id1[i] != 0 || id2[i] != 0; i++) {
    if (id1[i] != id2[i]) {
      return 0;
    }
  }
  return 1;
}


/* The function recognizeEquations demonstrates the recognizer. */
void recognizeEquations() {
    char *ar;
    List tl, tl1, tl2;
    printf("give an equation: ");
    ar = readInput();
    while (ar[0] != '!') {
        tl = tokenList(ar);
        printList(tl);
        tl1 = tl;
        tl2 = tl;
        if (acceptEquation(&tl1) && tl1 == NULL) {
            printf("this is an equation");
            int x = checkVarAndDegree(&tl2);
            if(x == -1){
                printf(", but not in 1 variable\n");
            }else{
                printf(" in 1 variable of degree %d\n", x);
            }
        } else {
            printf("this is not an equation\n");
        }
        free(ar);
        freeTokenList(tl);
        printf("\ngive an equation: ");
        ar = readInput();
    }
    free(ar);
    printf("good bye\n");
}
