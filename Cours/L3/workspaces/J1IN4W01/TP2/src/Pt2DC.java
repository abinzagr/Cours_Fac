
public class Pt2DC {
  private double abscisse;
  private double ordonnee;
  
  public Pt2DC() {
    this.abscisse=0;
    this.ordonnee=0;
  }
  
  public Pt2DC(double x,double y) {
    this.abscisse=x;
    this.ordonnee=y;
  }
  
  public double getAbscisse(){
    return this.abscisse;
  }
  
  public double getOrdonnee(){
    return this.ordonnee;
  }
  
  public void setAbscisse(double x){
    this.abscisse=x;
  }
  
  public void setOrdonnee(double y){
    this.abscisse=y;
  }
  
  public String toString(){
    return ("("+this.abscisse+","+this.ordonnee+")");
  }
  
  public Pt2DC clone(){
    return new Pt2DC(this.abscisse,this.ordonnee);
  }
  
  public boolean equals(Pt2DC p){
    return(this.abscisse==p.abscisse&& this.ordonnee==p.ordonnee);
  }
  
  public void translation(double dx,double dy){
    this.abscisse+=dx;
    this.ordonnee+=dy;
  }
 
  public void rotation(double alpha){
  this.abscisse=(this.abscisse*Math.cos(alpha))-(this.ordonnee*Math.sin(alpha));  
  this.ordonnee=(this.abscisse*Math.sin(alpha))-(this.ordonnee*Math.cos(alpha));
  }
  
  public void homotetie(double k){
    this.abscisse*=k;
    this.ordonnee*=k;
  }
  
  public static double distance(Pt2DC p1,Pt2DC p2){
    return(Math.sqrt(((p2.abscisse-p1.abscisse)*(p2.abscisse-p1.abscisse))+((p2.ordonnee-p1.ordonnee)*(p2.ordonnee-p1.ordonnee))));
    
  }
  

  
}
 