
public class exo1 {
	int entier;

	public exo1(int entier) {
		super();
		this.entier = entier;
	}

	public boolean parite(){
		if(this.entier%2==0)
			return true;
		return false;
	}
	public boolean signe(){
		if(this.entier>0)
			return true;
		return false;
	}

	public String toString() {
		if(this.signe() && this.parite())
			return "l'entier rentré est pair et positif";
		else if(this.signe()==false && this.parite())
			return "l'entier rentré est pair et negatif";
		else if(this.signe() && this.parite()==false)
			return "l'entier rentré est impair et positif";
		else
			return "l'entier rentré est impair et negatif";
	}

	public static void main(String[] args){
		int n=3;
		exo1 e=new exo1(-4);
		System.out.println(e.toString());

	}
}
