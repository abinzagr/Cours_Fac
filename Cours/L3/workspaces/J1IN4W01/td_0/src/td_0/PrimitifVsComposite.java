package td_0;

class Point {
  public int x;
  public int y;
}

public class PrimitifVsComposite {

  public static void main(String[] args) {
    int x, y;
    x = 3;
    y = 3;
    if (x == y) {
      System.out.println("x :" + x + " y :" + y + "  x == y");
    } else {
        System.out.println("x :" + x + " y :" + y + "  x != y");
      }
    Point p1,p2;
    p1=new Point();
    p2= new Point();
    p1=p2;
    p1.x=0;
    p1.y=1;
    p2.x=0;
    p2.y=1;
    
    if(p1==p2){
      System.out.println("p1 :" + p1 + " p2: " + p2 + "  p1 == p2");
    } else {
      System.out.println("p1 :" + p1 + " p2: " + p2 + "  p1 != p2");
      }
  }

}
