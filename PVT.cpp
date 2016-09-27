#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;



// PRICE VOLUME TREND
//This measures the trend of the market using the voulme as the supporting indicator

// [[Rcpp::export]]
Rcpp::NumericVector PVT(Rcpp::NumericVector close, Rcpp::NumericVector volume)
{
int i,max1;
Rcpp::NumericVector pvt(close.size()+1,0.0);

max1=omp_get_max_threads();
omp_set_num_threads(max1);

#pragma omp parallel for
for(i=close.size()-1;i>0;i--)
{
pvt[i-1]=((close[i-1]-close[i])/close[i])*volume[i]+pvt[i];//change in the closing price times the volume
}
return pvt;
}




