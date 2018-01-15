/*********************************************
 * OPL 12.6.3.0 Model
 * Author: abbinzagr
 * Creation Date: 8 nov. 2017 at 10:55:48
 *********************************************/
/*dvar float+ pate1;
dvar float+ pate2;
dvar float+ pate3;*/
dvar float+ pate[1..3];
int cst_ext=...;
int cst_int=...;
int demande[1..3]=...;
float cout[1..3][1..2]=...;/*chaque pate coutint|coutext*/
float farine[1..3]=...;
float oeuf[1..3]=...;

minimize  
	sum(i in 1..3)(sum (j in 1..2) (cout[i][j] * pate[i]));
	subject to{
		farine[1]*pate[1] + oeuf[1]*pate[2] ==demande[1];	
		farine[2]*pate[2] + oeuf[2]*pate[2] ==demande[2];	
		farine[3]*pate[3] + oeuf[3]*pate[3] ==demande[3];	
		sum(i in 1..3)(sum(j in 1..2)(cout[i][2] * pate[i])) <=200;
	}







