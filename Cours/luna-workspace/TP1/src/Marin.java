
public class Marin extends Drones {
	private final double distMax =5000;
	private final int vitesse =2;
	public Marin() {
		super();
	}

	public Marin(position position, double autonomie, boolean mission,
			position sol) {
		super(position, autonomie, mission, sol);

	}
	boolean retourStation(){
		return(this.getAutonomie()>=((this.distance()*100))/distMax);
	}
	
	double tempsStation(){
		return(this.distance()/vitesse);
	}
}
