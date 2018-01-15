package tp4;

import ij.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;
import java.io.FileWriter;

public class Extraire_LUT implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_ALL;
  }

  @Override
  public void run(ImageProcessor ip) {
    LUT l = ip.getLut() ;
    try {
      FileWriter f = new FileWriter("lut.txt") ;
      byte[] tmp = l.getBytes() ;
      for(int i = 0 ; i < tmp.length ; i += 3) {
        f.write("case " + i/3 + " r:" + (tmp[i]&0xFF) + " g:" + (tmp[i+1]&0xFF) + " b:" + (tmp[i+2]&0xFF) + "\n");
      }
      f.close();
      
    } catch (java.io.IOException e) {
      System.out.println("Erreur à la création de fichier");
    }
  }
  
}
