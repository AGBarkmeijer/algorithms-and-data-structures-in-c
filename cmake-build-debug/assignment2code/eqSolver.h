/* eqSolver.h
 * s2615371, s3547558
 * 19 February 2019
 */

#ifndef EQSOLVER_H
#define EQSOLVER_H

int valueNumber(List *lp, double *wp);
int valueTermEq(List *lp, double *wp);
int valueTerm(List *lp, double *wp);
int valueExpression(List *lp, double *wp);
void recognizeAndSolveEquation();



#endif
