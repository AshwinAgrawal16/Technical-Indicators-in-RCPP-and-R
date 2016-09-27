#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;


// Volatility Ratio
double VAR(Rcpp::NumericVector close,int j,int n)
{
  double close_sum=0;
  int i;

#pragma omp parallel for
  for(i=j;i<n+j;i++)
  {
    close_sum=close[i]+close_sum;
  }
  double mean_close=close_sum/n;
  double sum_dev=0;

#pragma omp parallel for
  for(i=j;i<n+j;i++)
  {
    sum_dev=(close[i]-mean_close)*(close[i]-mean_close)+sum_dev;
  }
  double var=sum_dev/n;

  //sum_of_elems = std::accumulate(vector.begin(), vector.end(), 0);
  return var;
}

double mean(Rcpp::NumericVector close,int j,int n)
{
  double close_sum=0;
  int i;

#pragma omp parallel for
  for(i=j;i<n+j;i++)
  {
    close_sum=close[i]+close_sum;
  }
  double mean_close=close_sum/n;
  return mean_close;

}
// [[Rcpp::export]]
Rcpp::NumericVector VR(Rcpp::NumericVector close, int n)
{
  int i,max1;
  int size=close.size();
  Rcpp::NumericVector vr(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=0;i<close.size()-n;i++)
  {
    vr[i]=sqrt(VAR(close,i,n))/mean(close,i,n);
  }
  return vr;
}


