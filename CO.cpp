#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;







// CHAIKIN OSCILLATOR


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
Rcpp::NumericVector CHAIKIN( Rcpp::NumericVector close,Rcpp::NumericVector high,Rcpp::NumericVector low,Rcpp::NumericVector open,Rcpp::NumericVector volume)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector EMA10(size);
  Rcpp::NumericVector EMA3(size);
  Rcpp::NumericVector Chaikin(size);

  Rcpp::NumericVector AD(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);
#pragma omp parallel for
  for(i=0;i<close.size();i++)
  {
    AD[i]=((close[i]-open[i])/(high[i]-low[i]))*volume[i];
  }
#pragma omp parallel for
  for(i=0;i<close.size()-10;i++)                          //10 DAY EMA OF AD -FAST MOVING AVERAGE
  {
    EMA10[i]=exponential(AD,2/(10+1),i+10,i);         //SMOTHING FACTOR IS DEFAULT 2/(1+n)
  }
#pragma omp parallel for
  for(i=0;i<close.size()-3;i++)                           //3 DAY EMA OF AD -SLOW MOVING AVERAGE
  {
    EMA3[i]=exponential(AD,2/(3+1),i+3,i);
  }
#pragma omp parallel for
  for(i=0;i<close.size()-10;i++)
  {
    Chaikin[i]=EMA10[i]-EMA3[i];

  }

  return Chaikin;
}
