#include <cstdlib>
#include<bits/stdc++.h>
#include <iostream>
#include <Rcpp.h>
#include <omp.h>
using namespace std;







//TWIGGS MONEY FLOW FORMULA



//function for calculating the simple moving average over n days
double MA_Simple(int period, int ii,Rcpp::NumericVector price) {

  //stp.Start();
  double summ = 0;
#pragma omp parallel for
  for (int i = ii; i<period+ii; i++) {
    summ = summ + price[i+1];
  }
  summ = summ / period;
  return summ;
  //stp.Stop();
  //if (ii == 1500) System.Windows.Forms.MessageBox.Show((stp.ElapsedTicks * 1000.0) / Stopwatch.Frequency + " ms");
  // return summ;
} //else return -1;

// [[Rcpp::export]]
Rcpp::NumericVector twiggs(Rcpp::NumericVector close,Rcpp::NumericVector high,Rcpp::NumericVector low,Rcpp::NumericVector volume)
{
  int i,max1;
  Rcpp::NumericVector TRH(close.size(),0.0);
  Rcpp::NumericVector TRL(close.size(),0.0);
  Rcpp::NumericVector AD(close.size(),0.0);
  Rcpp::NumericVector TWIGGS(close.size(),0.0);
  max1=omp_get_max_threads();
  omp_set_num_threads(max1);

#pragma omp parallel for
  for(i=0;i<close.size()-1;i++)
  {

    TRH[i]=max(high[i],close[i-1]);//for calculating the max high and close (of previous day)

  }
#pragma omp parallel for
  for(i=0;i<close.size()-1;i++)
  {

    TRL[i]=min(low[i],close[i-1]);//for calculating the min of low and close(of previous day)

  }
#pragma omp parallel for
  for(i=0;i<close.size()-1;i++)
  {

    AD[i]=(((close[i]-TRL[i])-(TRH[i]-close[i]))/(TRH[i]-TRL[i]))*volume[i];//formula for the twiggs indicator

  }
#pragma omp parallel for
  for(i=0;i<AD.size()-21;i++)
  {
    TWIGGS[i]=MA_Simple(21,i,AD);//now taking the somthing over a period of 21 days or any other fibonacci number is also possible
  }
  return TWIGGS;
}


