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
double MIN(Rcpp::NumericVector low,int t,int i)
{
  int j;
  double min=0;
#pragma omp parallel for
  for(j=i;j<t+i;j++)
  {
    if(low[i]<min)
      min=low[i];
  }
  return min;
}


//DONCHIAN CHANNELS
// [[Rcpp::export]]
Rcpp::NumericVector Donchian(Rcpp::NumericVector high,Rcpp::NumericVector low,int time)
{
  int i,max1;
  int size=high.size();
  Rcpp::NumericVector maxh1(size);
  Rcpp::NumericVector minl1(size);
  Rcpp::NumericVector DON(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=1;i<high.size()-time;i++)      //i=1 because the donchian channels takes max of high of past 20 dyas nad not including the current day
  {
    maxh1[i-1]=MAX(high,time,i);
  }
#pragma omp parallel for
  for(i=1;i<high.size()-time;i++)     //i=1 because the donchian channels takes max of high of past 20 dyas nad not including the current day
  {
    minl1[i-1]=MIN(low,time,i);
  }

#pragma omp parallel for
  for(i=1;i<minl1.size()-time;i++)
  {
    DON[i]=(maxh1[i]+minl1[i])/2;
  }

  return DON;


  /*double maxh=0;
  int i;
  for(i=1;i<=time;i++)  //i=1 because the donchian channels takes max of high of past 20 dyas nad not including the current day
  if(high[i]>max)
  maxh=high[i];

  double minl=0;
  for(i=1;i<=time;i++)
  if(low[i]>max)
  minl=low[i];*/


}

