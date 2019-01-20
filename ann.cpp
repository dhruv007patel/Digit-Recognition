/*
Digit Classifier in C++ 
*/
#include<bits/stdc++.h>
using namespace std;
#define NUMPAT 70
#define NUMIN  50
#define NUMHID 15
#define NUMOUT 10
#define rando() ((double)rand()/((double)RAND_MAX+1))
#define RAND_FLOAT ((double) rand() / RAND_MAX) * (0.5-(-0.5)) + (-0.5)
double sigmoid(double x)
{
	return 1.0/(1.0 + exp(-x)); 
}
double sigmoid_d(double x)
{
	return x*(1-x);
}
int main()
{
    int i,j,k,p,np,op,ranpat[NUMPAT+1],epoch;
    int NumPattern=NUMPAT,NumInput=NUMIN,NumHidden=NUMHID,NumOutput=NUMOUT;
double Input[NUMPAT+1][NUMIN+1] = {
   	{7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7},
    {0,0,0,0,0,0,7,7,7,0,0,7,0,7,0,0,7,0,7,0,0,7,0,7,0,0,7,0,7,0,0,7,0,7,0,0,7,0,7,0,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},  
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,7,7,7,0,0,7,0,0,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,0,7,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,7,7,7,7,7,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,0,0,7,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,0,0,7,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,7,7,7,7,7,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,7,0,0,7,0,7,0,0,0,0,7,0,0,0,7,0,0,7,7,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
    {0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,0,0,0,7,0,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,0,0,7,7,0,0,0,0,0,7,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,7,7,7,7,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,0,0,0,7,0,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0},
    {7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7},
    {0,0,0,0,0,0,0,7,7,0,0,7,0,0,7,0,0,0,0,7,0,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,7,0,0,7,0,0,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,0,7,0,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {7,7,7,7,7,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,7,7,7,7,7},
    {0,7,7,7,0,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {0,0,7,7,0,0,7,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,7,0,0,7,0,0,7,7,7,0,0,0,0,0},
    {0,0,7,0,0,0,7,0,7,0,7,0,0,7,0,0,0,7,0,0,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7},
    {0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,7,0,7,0,0,7,0,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,7,7,0,0,7,0,7,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7.7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,7,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,7,0,0,0,7,7,0,0,7,0,7,0,7,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,0,7,0,7,0,0,7,0,0,7,7,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0},
    {7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7},
    {7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,7,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
    {7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,0,0,0,0,0,7,0,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,7,0,7,0,0,0,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,7,7,7,7,0,0,0,0,7,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0},
    {7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,7,7,7,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,0},
    {7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7},
    {0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {0,0,7,7,0,0,7,0,0,7,0,7,0,0,7,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,7,7,7,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,7,7,0,7,7,0,0,7,0,7,0,0,7,0,0,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,7,7,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,7,0,7,0,0,7,0,0,7,7,0,0,0,0,0,0},
    {7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7},
    {7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7},
    {7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,7,7,7,7,7,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,0},
    {7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0},
    {0,0,7,7,7,0,7,0,0,7,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,7,7,7,7,7,0,0,7,0,0,0,0,7,0,0,0,7,0,7,7,7,7,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0},
    {7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7},
    {0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0,0,7,7,0,0,7,0,0,7,0,7,0,0,0,7,0,7,7,7,0},
    {0,0,0,0,0,0,0,7,0,7,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,7,0,0,7,7,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,7,0,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0},
    {0,0,0,0,0,0,0,7,7,7,0,7,0,0,7,0,7,0,0,7,0,7,7,7,7,0,7,0,0,7,0,7,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
    {7,7,7,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7},
    {0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,0,7,7,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
    {0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,0,7,0,0,7,7,7,0,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0},  
    {0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7},
    {0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,7,0,0,7,0,7,0,0,7,0,0,7,7,7,0,0,0,0,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0}};
double Target[NUMPAT+1][NUMOUT+1]={
    {1,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},  
    {1,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,0,0},  
    {0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},  
    {0,1,0,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},  
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},  
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},  
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},  
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},  
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0},  
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},  
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,1,0,0},  
    {0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,1,0,0},  
    {0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,1,0},  
    {0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,1,0},  
    {0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1},  
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,1}};
    double SumH[NUMPAT+1][NUMHID+1];
    double WeightIH[NUMIN+1][NUMHID+1];
    double Hidden[NUMPAT+1][NUMHID+1];
    double SumO[NUMPAT+1][NUMOUT+1];
    double WeightHO[NUMHID+1][NUMOUT+1];
    double Output[NUMPAT+1][NUMOUT+1];
    double DeltaO[NUMOUT+1];
    double SumDOW[NUMHID+1];
    double DeltaH[NUMHID+1];
    double DeltaWeightIH[NUMIN+1][NUMHID+1];
    double DeltaWeightHO[NUMHID+1][NUMOUT+1];
    double Error,eta=0.25,alpha=0.25;
    // Initialize Weights and Deltas 
  	for( j = 1 ; j <= NumHidden ; j++)
    {   for( i = 0 ; i <= NumInput ; i++ ) 
        { 
            DeltaWeightIH[i][j] = 0.0 ;
            WeightIH[i][j] = RAND_FLOAT;
        }
    }
    for( k = 1 ; k <= NumOutput ; k ++ )
    {   for( j = 0 ; j <= NumHidden ; j++ ) {
            DeltaWeightHO[j][k] = 0.0 ;              
            WeightHO[j][k] = RAND_FLOAT; 
        }
    }
    cout<<"Training Starts!!\n";
    //Training Starts in random order!
    for( epoch = 0 ; epoch < 10000; epoch++)
    {    
        for( p = 1 ; p <= NumPattern ; p++ )
        {    
        	ranpat[p] = p ;
        }
        for( p = 1 ; p <= NumPattern ; p++)
        {
            np = p + rando() * ( NumPattern + 1 - p ) ;
            op = ranpat[p] ;
            ranpat[p] = ranpat[np] ;
            ranpat[np] = op ;
        }
        Error = 0.0 ;
        for( np = 1 ; np <= NumPattern ; np++ )
        {    
            p = ranpat[np];
            //Feeding Forward (xi*wi)+bi
            for( j = 1 ; j <= NumHidden ; j++ )
            {   
            	SumH[p][j] = WeightIH[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ )
                {
                    SumH[p][j] += Input[p][i] * WeightIH[i][j] ;
                }
                Hidden[p][j] = sigmoid(SumH[p][j]);
            }
            for( k = 1 ; k <= NumOutput ; k++ )
            { 
            	SumO[p][k] = WeightHO[0][k] ;
                for( j = 1 ; j <= NumHidden ; j++ )
                {
                    SumO[p][k] += Hidden[p][j] * WeightHO[j][k] ;
                }
                Output[p][k] = sigmoid(SumO[p][k]) ;  	 
                Error += 0.5 * (Target[p][k] - Output[p][k]) * (Target[p][k] - Output[p][k]);
                DeltaO[k] =(Target[p][k] - Output[p][k]) * sigmoid_d(Output[p][k]);  
            }
            //Feeding Backward 
            for( j = 1 ; j <= NumHidden ; j++ ) 
            {
                SumDOW[j] = 0.0 ;
                for( k = 1 ; k <= NumOutput ; k++ )
                {
                    SumDOW[j] += WeightHO[j][k] * DeltaO[k] ;
                }
                DeltaH[j] = SumDOW[j] * sigmoid_d(Hidden[p][j]) ;
            }
            //Upadating Weights and Delta
            for( j = 1 ; j <= NumHidden ; j++ )
            {   
            	DeltaWeightIH[0][j] = eta* DeltaH[j] + alpha * DeltaWeightIH[0][j] ;
                WeightIH[0][j] += DeltaWeightIH[0][j] ;
                for( i = 1 ; i <= NumInput ; i++ )
                { 
                    DeltaWeightIH[i][j] = eta* Input[p][i] * DeltaH[j] + alpha * DeltaWeightIH[i][j];
                    WeightIH[i][j] += DeltaWeightIH[i][j] ;
                }
            }
            for( k = 1 ; k <= NumOutput ; k ++ )
            {   
                DeltaWeightHO[0][k] =  eta* DeltaH[k] + alpha * DeltaWeightIH[0][k] ;
                Hidden[p][j] = eta* DeltaO[k] + alpha * DeltaWeightHO[0][k] ;
                WeightHO[0][k] += DeltaWeightHO[0][k] ;
                for( j = 1 ; j <= NumHidden ; j++ ) 
                {
                    DeltaWeightHO[j][k] =  eta*Hidden[p][j] * DeltaO[k] + alpha * DeltaWeightHO[j][k] ;
                    WeightHO[j][k] += DeltaWeightHO[j][k] ;
                }
            }
        }
        if(epoch%1000==0)
        	cout<<"Epoch = "<<epoch/1000<<" "<<"Error = "<<Error<<endl;
        if( Error < 0.0004 )
        { 
        	break ;  
        }
    }
    cout<<"Testing Starts!!\n";
    // fprintf(stdout, "\n\nNETWORK DATA - EPOCH %d\n\nPat\t", epoch) ;   /* print network outputs */
    // for( i = 1 ; i <= NumInput ; i++ ) {
    //     fprintf(stdout, "Input%-4d\t", i) ;
    // }
    // for( k = 1 ; k <= NumOutput ; k++ ) {
    //     fprintf(stdout, "Target%-4d\tOutput%-4d\t", k, k) ;
    // }
    // for( p = 1 ; p <= NumPattern ; p++ ) {        
    // fprintf(stdout, "\n%d\t", p) ;
    //     for( i = 1 ; i <= NumInput ; i++ ) {
    //         fprintf(stdout, "%f\t", Input[p][i]) ;
    //     }
    //     for( k = 1 ; k <= NumOutput ; k++ ) {
    //         fprintf(stdout, "%f\t%f\t", Target[p][k], Output[p][k]) ;
    //     }
    // }
    // fprintf(stdout, "\n\nGoodbye!\n\n") ;
double TEST[30][50]={
	{0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,7,7,0,7,7,7,0,0,7,7,7,0,0,7,7,7,7,0,7,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
	{0,7,7,7,0,7,7,0,7,7,7,7,0,7,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,0,7,7,0,7,7,7,0}, 
	{0,0,0,0,0,0,0,7,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,7,0,0,0,0,0,0,0},
	{0,0,0,0,0,7,0,0,0,0,0,7,0,0,0,0,7,7,0,0,0,7,7,0,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,7,0,0,0,0,7,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,7,0,0,0,7,7,0,0,7,7,0,0,0,7,7,0,0,7,7,0,0,0,7,7,0,0,7,7,0,0,0,7,0,0,0,0,0,0,0,0,0},  
	{0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0,0,7,0,7,7,7,0,0,7,7,0,0,7,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0}, 
	{0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,7,0,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,7,7,7,0,0,0,0,0,0,0,0,0,0},
	{7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7}, 
	{0,0,7,7,0,0,7,0,0,7,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,0,7,0,0,0,0,0,7,0,0,0,7,0,0,7,7,0,0,0,0,0,0,0}, 
	{7,7,7,7,7,0,0,0,7,0,0,0,7,0,0,0,7,7,0,0,0,0,0,7,0,0,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,0,0,0,0,7,0,0,7,7,0,0,0,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,7,0,0,7,0,0,7,0,0,7,0,7,0,0,7,0,0,7,7,0,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,7,0,7,7,7,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,7,0,0,7,0,7,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,7,7,7,7.7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0},
	{0,0,0,0,0,0,7,7,7,0,0,7,0,0,0,0,7,0,0,0,0,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
	{0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,7,7,7,0,0,0,0,0,7,0,0,0,0,7,7,7,7,7,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,0,0,0,0,7,0,7,7,7,7,7,0,0,7,0,7,7,7,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,7,7,7,7,7,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,7,7,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,7,7,7,7,7,0,0,7,7,0,0,0,7,0,7,7,7,0,0,0,0,0,0},
	{0,7,7,7,7,7,0,0,7,7,7,0,0,7,0,0,0,7,7,0,0,0,7,0,0,0,0,7,0,0,0,7,7,0,0,7,0,0,0,0,7,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,7,7,7,7,7,0,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,0,0,0,0,0,0,0},
	{0,0,7,7,0,0,7,0,0,0,7,0,0,0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0,0,7,0,7,0,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0},
	{0,0,0,0,0,0,7,7,0,0,7,0,0,0,0,7,0,0,0,7,7,0,0,7,0,7,7,7,0,0,0,7,7,0,0,7,0,0,7,0,7,0,0,0,7,0,7,7,7,0},
	{0,0,0,0,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,7,7,7,0,7,0,0,0,7,7,0,0,0,7,7,0,0,7,0,0,7,7,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,7,0,0,7,0,7,0,0,7,0,0,7,7,7,7,0,0,0,7,0,7,0,7,0,0,0,7,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,7,7,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,7,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,0,7,7,0,0},
	{0,0,7,7,0,0,7,0,0,7,7,0,0,0,7,7,0,0,0,7,0,7,0,7,0,0,0,7,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0}};
    // for(int i=1;i<=NUMIN;i++)
    // {
    // 	for(int j=1;j<=NUMHID;j++)
    // 	{
    // 		cout<<WeightIH[i][j]<<" ";
    //    	}
    //    	cout<<endl;
    // }
    // for(int j=1;j<=NUMHID;j++)
    // {
    // 	for(int k=1;k<=NUMOUT;k++)
    // 	{
    // 		cout<<WeightIH[j][k]<<" ";
    //    	}
    //    	cout<<endl;
    // }
	int TS=70;
    double x2[TS][NUMHID];
    for(int i=1;i<=TS;i++)
    {
        for(int j=1;j<=NUMHID;j++)
        {
            for(int k=1;k<=NUMIN;k++)
            {
                x2[i][j]+=(TEST[i][k]*WeightIH[k][j]);
            }
        }
    }
    double ans[TS][10];
    for(int p=1;p<=TS;p++)
    {
        for(int k=1;k<=10;k++)
        {
            ans[p][k]=0.0;
            for(int j=1;j<=NUMHID;j++)
            {
                ans[p][k]+=(x2[p][j] * WeightHO[j][k]);
            }
        }
    }
    cout<<"Testing Ends"<<endl;
    //Printing Ans Matrix
    // for(int i=1;i<=TS;i++)
    // {
    //     for(int j=1;j<=NUMOUT;j++)
    //     {
    //         cout<<ans[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    //  cout<<endl;
	int tmp[10];
    int mans[TS][10];
    int m=INT_MIN,pos;
    for(int i=1;i<=TS;i++)
    {
        m=INT_MIN,pos=0;
        for(int j=1;j<=10;j++)
        {
            if(ans[i][j]>m)
            {
                m=ans[i][j];
                pos=j;
            }
        }
        for(int g=1;g<=10;g++)
        {
            if(g==pos)
            {
                mans[i][g]=1;
            }
            else
            {
                mans[i][g]=0; 
            }
        }  

    }
    // Printing the Output Matrix
    // for(int i=1;i<=TS;i++)
    // {
    // 	for(int j=1;j<=10;j++)
    // 	{
    // 		cout<<mans[i][j]<<" ";
    // 	}
    // 	cout<<endl;
    // 	if(i%(TS/10)==0)
    // 		cout<<endl;
    // }	

    int cnt=0;
    for(int i=1,j=1;i<=TS;i++)
    {
    	if((mans[i][j]==1)||(mans[i+2][j]==1))
    	{
    		cnt++;
    	}
    	if(i%(TS/10)==0)
    		j++;
    }
    cout<<"Accuracy = "<<round(((double)cnt/TS)*100)<<" % "<<" and error is "<<Error<<endl;
    return 0;
}

