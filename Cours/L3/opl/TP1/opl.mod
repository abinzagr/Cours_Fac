/*********************************************
 * OPL 12.6.3.0 Model
 * Author: abbinzagr
 * Creation Date: 8 nov. 2017 at 10:21:22
 *********************************************/
dvar float+ Gas;
dvar float+ Chloride;

maximize
  40 * Gas + 50 * Chloride;
subject to {
	ctMaxtTotal :
		Gas + Chloride <= 50;
	ctMaxtTotal2 :
		3 * Gas + 4 * Chloride <= 180;
	ctMaxtChlhoride :
		Chloride <= 40 ;		
}