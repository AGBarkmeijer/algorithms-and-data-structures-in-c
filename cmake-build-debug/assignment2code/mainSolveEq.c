/* mainSolveEq.c
 * s2615371, s3547558
 * 19 February 2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "scanner.c"
#include "recognizeExp.c"
#include "recognizeEq.c"
#include "evalExp.c"

// valueTermOnlyNumer(List *lp, double *sp)
// valueTermContainsIdentifier(List *lp, *vp) = min of meer onderstaande functie, zonder dingen met *sp
int valueTermEq(List *lp, double *vp, double *sp) {
  double v, s;
  if (*lp == NULL) {
    return 0;
  }
  v = *vp;
  s = *sp;
  if (acceptIdentifier(lp)) {
    if (acceptCharacter(lp,'^')) {
      if (acceptNumber(lp)) {
        v = 1;
        return 1;
      }
      return 0;
    }
    return 1;
  }
  else if (valueNumber(lp, vp)) {
    if (acceptIdentifier(lp)) {
      if (acceptCharacter(lp,'^')) {
        if (acceptNumber(lp)) {
          v = *vp;
          return 1;
        }
        return 0;
      }
      return 1;
    }
    s = *vp;
    return 1;
  }
  *vp = v;
  return 0;
}

int valueExpressionEq( Lisp *lp, double *vp, double *sp) {
  double v;
  if ( !valueTermEq(lp,vp) ) {
    return 0;
  }
  v = *vp;
  while ( *lp != NULL ) {
    if ( acceptCharacter(lp,'+') ) {
      if ( valueTermEq(lp,vp) ) {
        v = v+(*vp);
      } else {
        return 0;
      }
    } else if ( acceptCharacter(lp,'-') ) {
      if ( valueTermEq(lp,vp) ) {
        v = v-(*vp);
      } else {
        return 0;
      }
    } else {
      *vp = v;
      return 1;
    }
  }
  *vp = v;
  return 1;
}

void solveEquation(List *lp, double *var_p, double *sol_p) {

}

void recognizeAndSolveEquation() {
    char *ar;
    double *var_p, *sol_p;
    List tl, tl1, tl2;
    printf("give an equation: ");
    ar = readInput();
    while (ar[0] != '!') {
        tl = tokenList(ar);
        printList(tl);
        tl1 = tl;
        tl2 = tl;
        tl3 = t1;
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
                   solveEquation(&tl3, var_p, sol_p);
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


int main(int argc, char *argv[]) {
  recognizeAndSolveEquation();
  return 0;
}
