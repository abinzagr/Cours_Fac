
public class Point2D {
  private double x;
  private double y;
  
  public Point2D(double x,double y){
    this.x=x;
    this.y=y;
  }
  
  public double getX(){
    return this.x;
  }
  
  public double getY(){
    return this.y;
  }
  
  public void setX(double x){
    this.x=x;
  }
  
  public void setY(double y){
    this.y=y;
  }
  
  public String toString(){
    return("("+this.x+","+this.y+")");
  }
  
  public Point2D clone(){
    return new Point2D(this.x, this.y);
  }
  
 public boolean equals(Point2D p){
   return(this.x==p.x && this.y==p.y);
 } 
 
}
