
public class Aerien extends Drones {
	private final int vitesse=10;
	private final double distMax =10000;
	public Aerien() {
		super();
	}

	public Aerien(position position, double autonomie, boolean mission,
			position sol) {
		super(position, autonomie, mission, sol);
	}
	boolean etatbatteri(){
		return(this.getAutonomie()==100);
	}
	
	boolean retourStation(){
		return(this.mission==true && this.getAutonomie()>=((this.distance()*100))/distMax);
	}
	
	double tempsStation(){
		return(this.distance()/vitesse);
	}
}
