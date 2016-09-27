#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;


// CHAIKIN VOLATILITY INDEX

double exponential(Rcpp::NumericVector price, double smoothingValue, int dataSetSize,int j)                //FUNCTION TO CALCULATE THE EXPONENTIAL MOVING AVERAGE
{
  int i;
  double cXAvg;
  cXAvg = price[ dataSetSize - 2 ] ;

#pragma omp parallel for
  for (i= dataSetSize - 2; i > -1+j; --i)
    cXAvg += (smoothingValue * (price[ i ] - cXAvg)) ;

  return ( cXAvg) ;
}


// [[Rcpp::export]]
Rcpp::NumericVector ChaikinVolatility(Rcpp::NumericVector high,Rcpp::NumericVector low)
{
  int i,max1;
  int size=high.size();
  Rcpp::NumericVector Diff(size);
  Rcpp::NumericVector EMA10(size);
  Rcpp::NumericVector volatility(size);
  Rcpp::NumericVector EMA20(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=0;i<high.size();i++)
  {
    Diff[i]=high[i]-low[i];
  }
#pragma omp parallel for
  for(i=0;i<Diff.size()-10;i++)
  {
    EMA10[i]=exponential(Diff,2/(1+10),i+10,i);
  }

  int j=10;                                       //DEFAULT VALUE OF CHAIKIN VOLATILITY OF SECOND MOVING AVERAGE
#pragma omp parallel for
  for(i=0;i<Diff.size()-20;i++)
  {
    EMA20[i]=exponential(Diff,2/(1+10+j),i+10+j,i);
  }
#pragma omp parallel for
  for(i=0;i<EMA20.size();i++)
  {
    volatility[i]=((EMA10[i]-EMA20[i])/EMA20[i])*100;
  }

  return volatility;
}



