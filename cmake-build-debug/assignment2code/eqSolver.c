/* eqSolver.c
 * s2615371, s3547558
 * 19 February 2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "eqSolver.h"


int valueNumber(List *lp, double *wp) {
  if (*lp != NULL && (*lp)->tt == Number ) {
    *wp = ((*lp)->t).number;
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

int valueTermEq(List *lp, double *wp) {
  double w;
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

int valueTerm(List *lp, double *wp) {
  double w;
  if ( !valueFactor(lp,wp) ) {
    return 0;
  }
  w = *wp;
  while ( *lp != NULL ) {
    if ( acceptCharacter(lp,'*') ) {
      if ( valueFactor(lp,wp) ) {
        w = w*(*wp);
      } else {
        return 0;
      }
    } else if ( acceptCharacter(lp,'/') ) {
      if ( valueFactor(lp,wp) ) {
        w = w/(*wp);
      } else {
        return 0;
      }
    } else {
      *wp = w;
      return 1;
    }
  }
  *wp = w;
  return 1;
}

int valueExpression(List *lp, double *wp) {
  double w;
  if ( !valueTerm(lp,wp) ) {
    return 0;
  }
  w = *wp;
  while ( *lp != NULL ) {
    if ( acceptCharacter(lp,'+') ) {
      if ( valueTerm(lp,wp) ) {
        w = w+(*wp);
      } else {
        return 0;
      }
    } else if ( acceptCharacter(lp,'-') ) {
      if ( valueTerm(lp,wp) ) {
        w = w-(*wp);
      } else {
        return 0;
      }
    } else {
      *wp = w;
      return 1;
    }
  }
  *wp = w;
  return 1;
}

/* If the equation is not solvable (i.e. it does not have  at least one
* real-valued solution, or it has infinitely many solutions),
* print "not solvable" */
void solveEquation(List tl) {

}

void recognizeAndSolveEquation() {
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
            } else{
                printf(" in 1 variable of degree %d\n", x);
                /* For equations in one variable of degree 1,
                 * try to solve the equation. */
                 if (x == 1) {
                   solveEquation(tl);
                 }
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
