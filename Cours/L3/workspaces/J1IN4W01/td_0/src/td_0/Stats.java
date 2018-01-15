package td_0;

public class Stats {
  
  public static float moyenne(int []t){
    float moy=0f;float somme=0f;
    int nbelem=t.length;
    for(int i=0;i<t.length;i++)
      somme+=t[i];
    moy=somme/nbelem;
    return moy;
  } 
  
  public static float variance(int []t){
    float var=0f;float somme=0f;
    for(int i=0;i<t.length-1;i++)
      somme+=(t[i]-moyenne(t))*(t[i]-moyenne(t));
    var=somme/t.length;
    return var;
  }
  
}
