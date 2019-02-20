/* mainRecogEq.c
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
#include "eqSolver.c"

int main(int argc, char *argv[]) {
  recognizeAnDSolveEquation();
  return 0;
}
