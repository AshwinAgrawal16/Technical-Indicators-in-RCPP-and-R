#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;
// TRUE RANGE

/* Function maximum definition */
/* x, y and z are parameters */
double maximum(double x, double y, double z) {
  int max = x; /* assume x is the largest */

if (y > max)
max = y;


if (z > max)
max = z;


return max; /* max is the largest value */
} /* end function maximum */

// [[Rcpp::export]]
Rcpp::NumericVector TR(Rcpp::NumericVector close,Rcpp::NumericVector high, Rcpp::NumericVector low)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector tr(size);

  max1=omp_get_max_threads();
  omp_set_num_threads(max1);
#pragma omp parallel for
  for(i=0;i<close.size()-1;i++)
  {
    tr[i]=maximum(high[i]-low[i],high[i]-close[i-1],close[i-1]-low[i]);
  }
  return tr;
}

