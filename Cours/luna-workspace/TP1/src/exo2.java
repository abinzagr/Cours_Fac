
public class exo2 {
	int[] tab;

	public exo2(int[] tab) {
		super();
		this.tab = tab;
	}

	public static void tritab(int tableau[]) {
		int longueur = tableau.length;
		int tampon = 0;
		boolean permut;
 
		do {
			// hypothèse : le tableau est trié
			permut = false;
			for (int i = 0; i < longueur - 1; i++) {
				// Teste si 2 éléments successifs sont dans le bon ordre ou non
				if (tableau[i] > tableau[i + 1]) {
					// s'ils ne le sont pas, on échange leurs positions
					tampon = tableau[i];
					tableau[i] = tableau[i + 1];
					tableau[i + 1] = tampon;
					permut = true;
				}
			}
		} while (permut);
	}
	
	public void affiche() {
		for (int i = 0; i < tab.length; i++) {
			System.out.println(tab[i]);
			}
		}
		
	
	public static void main(String[] args){
		int[] tab={4,1,5,8,9,3,7,5};
		System.out.println("tableau non trie");
		for (int i = 0; i < tab.length; i++) {
			System.out.println(tab[i]);
		}
		exo2 e=new exo2(tab);
		System.out.println("tableau trie");
		e.tritab(tab);
		e.affiche();
		

	}
}
