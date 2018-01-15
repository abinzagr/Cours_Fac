
public class SousMarin extends Drones {
	private final int vitesse=2;
	private final double distMax =1500;
	public SousMarin() {
		super();
		// TODO Auto-generated constructor stub
	}

	public SousMarin(position position, double autonomie, boolean mission,
			position sol) {
		super(position, autonomie, mission, sol);
		// TODO Auto-generated constructor stub
	}
	boolean retourStation(){
		return(this.getAutonomie()>=((this.distance()*100))/distMax);
	}
	
	double tempsStation(){
		return(this.distance()/vitesse);
	}
}
