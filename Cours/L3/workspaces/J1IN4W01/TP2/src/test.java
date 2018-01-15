
public class test {

  public static void main(String[] args) {

      Pt2DC pointbin=new Pt2DC(2,3);
      Pt2DC p1=new Pt2DC(1,2);
      System.out.println("on a creer notre point :"+pointbin.toString());
      System.out.println("son abscisse vaut :"+pointbin.getAbscisse()+" et son ordonnee vaut :"+pointbin.getOrdonnee());
      Pt2DC pointcopie=new Pt2DC();
      pointcopie=pointbin.clone();
      System.out.println("voici notre point copie:"+pointcopie.toString());
      if(pointbin!=pointcopie)
        System.out.println("les points n'ont pas la meme reference");
      if(pointbin.equals(pointcopie))
        System.out.println("les points ont les memes abscisse et les memes ordonnees");
      System.out.println("la distance entre p1 et pointbin vaut ="+Pt2DC.distance(p1, pointbin));
    }
  }


