
public class PolygonePt2DC {
  private Pt2DC[] points;
  
  public PolygonePt2DC(Pt2DC[] points){
    this.points=points.clone();
    for(int i=0;i<points.length;i++)
      this.points[i]=points[i].clone();
  }
  
  public Pt2DC[] getSommets(){
    Pt2DC[] tabp=new Pt2DC[this.points.length];
    for(int i=0;i<this.points.length;i++)
      tabp[i]=this.points[i].clone();
    return tabp;
  }
  
  public void setSommets(Pt2DC[] points){
    
  }
  
  public boolean equals(PolygonePt2DC poly){
    if(this.points.length!=poly.points.length)
      return false;
    for(int i=0;i<points.length;i++)
      if(!this.points[i].equals(poly.points[i]))
        return false;
    return true;
  }
  
  public PolygonePt2DC clone(){
   return new PolygonePt2DC(this.points);
  }
  
  public double perimetre(){
      double resultat= 0;
      for (int i=0; i<this.points.length-1; i++) {
        resultat += Pt2DC.distance(points[i],points[i+1]);
      }
      return (resultat+Pt2DC.distance(points[this.points.length-1],points[0]));
    }
    
  public String toString() {
    StringBuffer resultat = new StringBuffer();
    for (int i=0; i<this.points.length-1; i++) {
      resultat.append(points[i]+", ");
    }
    return new String(resultat);
  }
  
}
