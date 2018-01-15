package td_0;

public class TableauEntiers {
  
  public static void afficher(int[] t){
    for(int i=0;i<t.length;i++)
      System.out.println(t[i]);
    
  }
  public static int somme(int []t){
    int somme=0;
    for(int i=0;i<t.length;i++)
      somme+=t[i];
    return somme;
  }
  public static int minimum(int []t){
    int min=t[0];
    for(int i=0;i<t.length;i++){
      if(t[i]<min)
        min=t[i];
    }
  return min;
  }
  
  public static int indiceMaxi(int []t){
    int indice=0;int max=t[indice];
    for(int i=0;i<t.length;i++){
      if(max<t[i]){
        max=t[i];
        indice=i;
      }
    }
    return indice;
    
  }
  
  public static int[] oppose(int []t){
    int []to=new int[t.length];
    for(int i=0;i<t.length;i++)
      to[i]=-t[i];
    return to;

  }

  public static void tribulles(int []t) {
    for (int i = 0; i <= (t.length - 2); i++)
      for (int j = (t.length - 1); i < j; j--)
        if (t[j] < t[j - 1]) {
          int x = t[j - 1];
          t[j - 1] = t[j];
          t[j] = x;
        }
    
  }
  public static void echange(int []t , int a ,int b){
    int tmp=t[a]; 
    t[a]=t[b];
    t[b]=tmp;
}
  
  public static void inverser(int []t){
    int tmp;
    for(int i=0,j=t.length-1;i<j;i++,j--){
      tmp=t[i];
      t[i]=t[j];
      t[j]=tmp;
    }
    
  }
  
  public static boolean egalite(int []t1 , int []t2){
    for(int i=0;i<t1.length;i++)
      if(t1[i]!=t2[i])
        return false;
  
      return true;
      }
  
  public static void main(String[] args){
    int [] t= { 2 , 3 , 5 , 1 , 9 , 8 , 4 , 7 };
    int [] t1= { 2 , 3 , 5 , 1 , 9 , 8 , 4 , 7 };
    afficher(t);
    int som=somme(t);
    System.out.println("somme= "+som);
    int min=minimum(t);
    System.out.println("minimum= "+min);
    int indmax=indiceMaxi(t);
    System.out.println("indice max: "+indmax);
    afficher(oppose(t));
    //tribulles(t);
    //afficher(t);
    //inverser(t);
    //afficher(t);
    System.out.println(egalite(t, t1));
    
    }
    
    
  }

