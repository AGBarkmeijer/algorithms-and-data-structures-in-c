/* evalEq.c
 * s2615371, s3547558
 * 19 February 2019
 */

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "evalEq.h"

/* The function valueNumber is an extension of acceptNumber: the second parameter
 * is a pointer. After successful execution it refers to the numerical value
 * of the token that is recognized as a number.
 */

int valueNumber(List *lp, double *wp) {
  if (*lp != NULL && (*lp)->tt == Number ) {
    *wp = ((*lp)->t).number;
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

/* The functions valueFactor, valueTerm and valueExpression are extensions of
 * acceptFactor, acceptTerm en acceptExpression. The second parameter
 * is a pointer: after successful execution it refers to the value
 * of the initial segment of the token list that is recognized as a factor, term
 * or expression, respectively.
 */

int valueFactor(List *lp, double *wp) {
  return valueNumber(lp,wp)
    || ( acceptCharacter(lp,'(')
      && valueExpression(lp,wp)
      && acceptCharacter(lp,')')
    );
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

/* The function evaluateExpressions performs a dialogue with the user, which demonstrates
 * the recognizer and the evaluator.
 */

void evaluateExpressions() {
  char *ar;
  List tl, tl1;
  double w;
  printf("give an expression: ");
  ar = readInput();
  while (ar[0] != '!') {
    tl = tokenList(ar);
    printf("\nthe token list is ");
    printList(tl);
    tl1 = tl;
    if ( valueExpression(&tl1,&w) && tl1==NULL ) {
               /* there may be no tokens left */
      printf("this is a numerical expression with value %g\n",w);
    } else {
      tl1 = tl;
      if ( acceptExpression(&tl1) && tl1 == NULL ) {
        printf("this is an arithmetical expression\n");
      } else {
        printf("this is not an expression\n");
      }
    }
    free(ar);
    freeTokenList(tl);
    printf("\ngive an expression: ");
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}
