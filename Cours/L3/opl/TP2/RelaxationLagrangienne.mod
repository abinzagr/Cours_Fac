/*********************************************
 * OPL 12.6.3.0 Model
 * Author: abbinzagr
 * Creation Date: 6 déc. 2017 at 11:17:57
 *********************************************/
int x1=...;
int x2=...;
int x3=...;
int x4=...;
int profit[1..4]=...;
int mult1=0; //apha
int mult2=0; //U
int cap1=10;
int cap2=10;
int cap3=10;
int w1[1..4]=...; //dimension 1
int w2[1..4]=...; //dimension 2
int w3[1..4]=...; //dimension 3

maximize
  	sum(i in 1..4)(profit[i]-mult1*w2[i]-mult2*w3[i]+mult1*cap2+mult2*cap3) ;
  	subject to{
  				6*x1+4*x2+5*x3+1*x4 <= 10; //contrainte dim1
  				//2*x1+3*x2+3*x3+3*x4 <= 10; contrainte dim2 relachée !
  				//1*x1+5*x2+5*x3+1*x4 <= 01; contrainte dim3 relachée !
  	}