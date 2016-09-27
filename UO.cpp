#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;
using namespace Rcpp;


// [[Rcpp::export]]
Rcpp::NumericVector ultimate(Rcpp::NumericVector close,Rcpp::NumericVector low,Rcpp::NumericVector high )
{
  int i,max1;
  int size=close.size();
  //double TL[10000];
  //double TH[10000];
  Rcpp::NumericVector TR(size);
  Rcpp::NumericVector BP(size);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=0;i<close.size()-1;i++)
  {
    //	TL[i]=min(low[i],close[i+1]);
    //	TH[i]=max(high[i],close[i+1]);
    TR[i]=(max(high[i],close[i+1])-min(low[i],close[i+1]));
    BP[i]=(close[i]-min(low[i],close[i+1]));
  }
  //compute(TR,BP);
  Rcpp::NumericVector AVG7(size);
  Rcpp::NumericVector AVG14(size);
  Rcpp::NumericVector AVG28(size);
  Rcpp::NumericVector UO(size);
  //int i;
#pragma omp parallel for
  for(i=0;i<TR.size()-28;i++)
  {
    AVG7[i]=(BP[i]+BP[i+1]);  //sum(BP+i,BP+i+7)/sum(TR+i,TR+i+7);
    AVG14[i]=(BP[i]+BP[i+1]+BP[i+2]+BP[i+3]);  //sum(BP+i,BP+i+14)/sum(TR+i,TR+i+14);
    AVG28[i]=(BP[i]+BP[i+1]+BP[i+2]+BP[i+3]+BP[i+4]+BP[i+5]+BP[i+6]+BP[i+7]);  //sum(BP+i,BP+i+28)/sum(TR+i,TR+i+28);
    UO[i]=((AVG7[i]+AVG14[i]*2+AVG28[i]*4)/(1+2+4));     //ARRAY OF STOCK WEIGHTS
  }


  return UO;
}



/*double compute(array<double> TR,array<double> BP)
{
array<double> AVG7;
array<double> AVG14;
array<double> AVG28;
array<double> UO;
int i;
for(i=TR.begin();<i<TR.end()-28;i++)
{
AVG7[i]=sum(BP+i,BP+i+7)/sum(TP+i,TP+i+7);
AVG14[i]=sum(BP+i,BP+i+14)/sum(TP+i,TP+i+14);
AVG28[i]=sum(BP+i,BP+i+28)/sum(TP+i,TP+i+28);
UO[i]=(AVG7[i]+AVG14[i]*2+AVG28[i]*4)/(1+2+4);
}

}*/
