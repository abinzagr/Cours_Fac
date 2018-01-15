


public class TestRectangle {

  public static void main(String[] args) {
  Pt2DC p1=new Pt2DC(1,1);
  Pt2DC p3=new Pt2DC(2,2);
  Pt2DC p2=new Pt2DC(5,5);
  Rectangle r1=new Rectangle(p1,p2);
  Rectangle r2=new Rectangle();
  System.out.println("r1 a pour point gauche et point droit :"+r1.toString());
  r2=r1.clone();
  System.out.println("r2 a pour point gauche et point droit :"+r2.toString());
  //p1.setAbscisse(6);
  System.out.println("les nouvels coordonnees de p1 sont :"+p1.toString());
  System.out.println("la surface vaut :"+r1.getsurface());
  r1.setCoinDroit(p3);
  System.out.println("r1 a pour nouveaux point gauche et point droit :"+r1.toString());
  System.out.println("la surface vaut :"+r1.getsurface());
  }

}
