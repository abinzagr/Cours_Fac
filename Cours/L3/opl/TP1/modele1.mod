/*********************************************
 * OPL 12.6.3.0 Model
 * Author: abbinzagr
 * Creation Date: 8 nov. 2017 at 10:29:49
 *********************************************/
int obj_gas=...;
int obj_chloride=...;
int cst_ct1=...;
int cst_ct2=...;
int cst_ct3=...;
dvar float+ Gas;
dvar float+ Chloride;
maximize
  	obj_gas * Gas + obj_chloride * Chloride;
  	subject to{
  		ctMaxTotal :
  			Gas + Chloride <= cst_ct1;
  		ctMaxTotal2 :
  			3 * Gas + 4 * Chloride <= cst_ct2;
  		ctMaxChloride :
  			Chloride <= cst_ct3;		
  	  	
  	}