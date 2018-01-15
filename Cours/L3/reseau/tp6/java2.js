window.addEventListener('load',main);

function add(){
	var r=document.getElementById("t2");
	r.setAttribute("hidden","hidden"); 
	}
	
function main(){
	var monst=document.getElementById("t1");
	monst.onclick=add;
	
	}	
