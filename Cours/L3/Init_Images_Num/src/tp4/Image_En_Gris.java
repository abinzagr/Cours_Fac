package tp4;

import ij.*;
import ij.gui.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Image_En_Gris implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  int couleurVersNG(int couleur) {
    double gris = 0.3*((couleur&0xFF0000) >> 16) + 0.59*((couleur&0x00FF00) >> 8) + 0.11*(couleur&0x0000FF) ;
    return (int)gris*(1+256+256*256) ;
  }

  public void run(ImageProcessor ip) {
    int w = ip.getWidth();
    int h = ip.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Couleurs proches", w, h, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    
    for(int i = 0 ; i < w ; i++) {
      for (int j = 0 ; j < h ; j++) {
        int tmp = ip.getPixel(i, j);
        int g = couleurVersNG(tmp) ;
        tmp /= 256*256*256 ;
        tmp *= 256*256*256 ;
        tmp += g ;
        iR.putPixel(i, j, tmp);
      }
    }
    imR.show();
  }
}
