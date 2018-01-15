
public class position {
	double x;
	double y;
	double z;
	
	public position() {
		this.x = 0;
		this.y = 0;
		this.z = 0;
	}
	
	
	public position(double x, double y, double z) {
		if(x<=1000 && x >= -1000)
		this.x = x;
		if(y<=1000 && y >= -1000)
		this.y = y;
		if(z<=1000 && z >= -1000)
		this.z = z;
	}
}
