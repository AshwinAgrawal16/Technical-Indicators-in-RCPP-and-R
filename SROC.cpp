#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;

//  SMOTHED


double exponential(Rcpp::NumericVector price, double smoothingValue, int dataSetSize,int j)                //FUNCTION TO CALCULATE THE EXPONENTIAL MOVING AVERAGE
{
  int i;
  double cXAvg;
  cXAvg = price[ dataSetSize - 2 ] ;

  for (i= dataSetSize - 2; i > -1+j; --i)
    cXAvg += (smoothingValue * (price[ i ] - cXAvg)) ;

  return ( cXAvg) ;
}

// [[Rcpp::export]]
Rcpp::NumericVector SROC(Rcpp::NumericVector close,int n,int m)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector ROC(size);
  Rcpp::NumericVector EMA13(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=0;i<close.size()-n;i++)
  {
    EMA13[i]=exponential(close,2/(1+n),i+n,i);
  }

#pragma omp parallel for
  for(i=0;i<EMA13.size()-m;i++)
  {
    ROC[i]=(EMA13[i]-EMA13[i+m])/EMA13[i+m];
  }
  return ROC;

}
