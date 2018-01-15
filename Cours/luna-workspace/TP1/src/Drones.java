
public class Drones {
	protected position position;
	protected double autonomie;
	protected boolean mission;
	protected position sol; 

	public Drones() {
		this.position = new position();
		this.autonomie = 0;
		this.mission = false;
		this.sol = new position();
	}

	public Drones(position position, double autonomie, boolean mission,
			position sol) {
		this.position = position;
		this.autonomie = autonomie;
		this.mission = mission;
		this.sol = sol;
	}

	double getAutonomie(){
		return this.autonomie;
	}

	boolean etatBatterie(){
		return(this.getAutonomie()==100);
	}
	
	double distance(){
		return Math.sqrt(Math.pow((position.x-sol.x),2)+Math.pow((position.y-sol.y),2)+Math.pow((position.z-sol.z),2));
		
	}
	
	
}
