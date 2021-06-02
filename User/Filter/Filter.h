#ifndef FILTER_H
#define FILTER_H


int Limit_Filter(int x,int A);
int Median_Filter(int x,int N);
int Arithmetic_Average_Filter(int x,int N);
int Moving_Average_Filter(int x,int N);
int Median_Average_Filter(int x,int N);
int FirstOrder_Lag_Filter(int x,int a);
int Weighted_Recursive_Average_Filter(int x,int N);
int Debounce_Filter(int x,int N);
#endif

