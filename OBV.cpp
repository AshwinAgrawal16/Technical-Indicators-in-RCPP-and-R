#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;


double MAX(Rcpp::NumericVector high,int t,int i)
{
  int j;
  double max=0;
#pragma omp parallel for
  for(j=i;j<t+i;j++)
  {
    if(high[i]>max)
      max=high[i];
  }
  return max;
}

// ON BALANCE VOULME INDICATOR
// [[Rcpp::export]]
Rcpp::NumericVector OBV(Rcpp::NumericVector close, Rcpp::NumericVector volume,int n)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector obv(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);
#pragma omp parallel for
  for(i=0;i<close.size()-n;i++)
  {
    if(close[i]>=MAX(close,n+1,i+1))      //HERE WE USE I+1 AND N+1 BECAUSE WE HAVE TO START FROM YESTERDAY
    {
      obv[i]=close[i]+volume[i];
    }
    else
      obv[i]=close[i]-volume[i];
  }
  return obv;
}

