#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;


//COpPOCK INDICATOR(OSCILLATOR)

// [[Rcpp::export]]
Rcpp::NumericVector Coppock(Rcpp::NumericVector close,double T1,double T2,double T3)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector ROC1(size);
  Rcpp::NumericVector ROC2(size);
  Rcpp::NumericVector ROC(size);
  Rcpp::NumericVector WMA1(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);
#pragma omp parallel for
  for(i=0;i<close.size()-(T1>T2?T2:T1);i++)
  {
    ROC1[i]=ROC(close,T1,i);    //FUNCTION TO CALCULATE THE RATE OF CHANGE OF PRICE
  }

#pragma omp parallel for
  for(i=0;i<close.size()-(T1>T2?T2:T1);i++)
  {
    ROC2[i]=ROC(close,T2,i);
  }

#pragma omp parallel for
  for(i=0;i<close.size()-(T1>T2?T2:T1);i++)
  {
    ROC[i]=ROC1[i]+ROC2[i];
  }

#pragma omp parallel for
  for(i=0;i<close.size()-T3;i++)
  {
    WMA1[i]=WMA(ROC,T3,i);     //FUNCTION TO CALCULATE THE WEIGHTED MOVING AVERAGE OF PRICE(ROC)
  }
  //return ROC;
  return WMA1;

}


