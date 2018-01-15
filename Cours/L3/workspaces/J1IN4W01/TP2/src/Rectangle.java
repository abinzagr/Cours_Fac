public class Rectangle {
  private Pt2DC cig;
  private Pt2DC csd;
  private double surface;
  public Rectangle(){
    this.cig=new Pt2DC();
    this.csd=new Pt2DC();
  }
  private boolean rectangleValide(){
    return((this.cig.getAbscisse()<this.csd.getAbscisse())&&(this.cig.getOrdonnee()<this.csd.getOrdonnee()));
  }
  
  public Rectangle(Pt2DC p1,Pt2DC p2){
      this.cig=p1.clone();
      this.csd=p2.clone();
      if(!this.rectangleValide())
        throw new RuntimeException("rectangle invalide");
      this.surface=this.calculSurface();
  }
  
  public Pt2DC getcig(){
    return this.cig.clone();
  }
  
  public Pt2DC getcsd(){
    return this.csd.clone();
  }
  
  public double getsurface(){
    return this.surface;
  }
  
  public void setCoinGauche(Pt2DC cig){
    this.cig=cig.clone();
    if(!this.rectangleValide())
      throw new RuntimeException("rectangle invalide");
    this.surface=this.calculSurface();
  }
  
  public void setCoinDroit(Pt2DC csd){
    this.csd=csd.clone();
    if(!this.rectangleValide())
      throw new RuntimeException("rectangle invalide");
    this.surface=this.calculSurface();
  }
  
  public boolean equals(Rectangle r){
    return(this.cig.equals(r.cig) && this.csd.equals(r.csd));
  }

  public Rectangle clone(){
    return new Rectangle(this.cig,this.csd);
  }
  
  public String toString(){
    return ("("+this.cig+","+this.csd+")");
  }
  
  public double calculSurface(){    
    return((Math.abs(csd.getAbscisse()-cig.getAbscisse()))*Math.abs((csd.getOrdonnee()-cig.getOrdonnee())));
  }
  
}
