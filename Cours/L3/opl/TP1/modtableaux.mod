/*********************************************
 * OPL 12.6.3.0 Model
 * Author: abbinzagr
 * Creation Date: 8 nov. 2017 at 10:40:40
 *********************************************/
int n=...;
int ub=...;
int C=...;
int s[1..n]=...;
dvar int x[1..n][1..ub] in 0..1;
dvar int y[1..ub] in 0..1;
minimize
  sum(j in 1..ub) y[j];
  subject to{
  	forall(i in 1..n)
  	  sum(j in 1..ub) x[i][j] == 1;
  	forall(j in 1..ub)
  	  sum(i in 1..n) s[i] * x[i][j] - C * y[j] <=0;  
    
  }