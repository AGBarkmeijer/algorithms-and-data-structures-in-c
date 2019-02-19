/* recognizeEq.h
 * s2615371, s3547558
 * 19 February 2019
 */

#ifndef RECOGNIZEEQ_H
#define RECOGNIZEEQ_H

int acceptTermEq(List *lp);
int acceptExpressionEq(List *lp);
int acceptEquation(List *lp);
int sameIdentifier(char *id1, char *id2);
int checkVarAndDegree(List *tl);
void recognizeEquations();

#endif
