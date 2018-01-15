package tp3;

import ij.*;
import ij.gui.*;
import java.awt.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Selection_Couleur implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  int couleurVersNG(int couleur) {
    double gris = 0.3*((couleur&0xFF0000) >> 16) + 0.59*((couleur&0x00FF00) >> 8) + 0.11*(couleur&0x0000FF) ;
    return (int)gris*(1+256+256*256) ;
  }
  
  double distance(int couleur1, int couleur2) {
    double dist = Math.pow((((couleur1&0xFF0000) >> 16)-((couleur2&0xFF0000) >> 16)) ,  2) ; // Le carré de la distance des bleus,
    dist += Math.pow((((couleur1&0x00FF00) >> 8)-((couleur2&0x00FF00) >> 8)) ,  2) ; // des verts,
    dist += Math.pow( (couleur1&0x0000FF-couleur2&0x0000FF) ,  2) ; // et des rouges
    return Math.sqrt(dist) ;
  }
  
  
  public void run(ImageProcessor ip) {
    ColorChooser cc = new ColorChooser("Couleur de référence", Color.yellow, true);
    Color cRef = cc.getColor();
    if (cRef == null) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    int couleurRef = (cRef.getRed()<< 16) + (cRef.getGreen() << 8) + cRef.getBlue();
    
    //
    GenericDialog gd = new GenericDialog( "Distance à la couleur",
        IJ.getInstance() );
    gd.addSlider( "distance", 1.0, 100.0, 5.0 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    //
    
    int distanceMax = (int) gd.getNextNumber() ;
    
    int w = ip.getWidth();
    int h = ip.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Couleurs proches", w, h, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    
    for(int i = 0 ; i < w ; i++) {
      for (int j = 0 ; j < h ; j++) {
        int tmp = ip.getPixel(i, j);
        if (distanceMax < distance(tmp, couleurRef)) {
          int g = couleurVersNG(tmp) ;
          tmp /= 256*256*256 ;
          tmp *= 256*256*256 ;
          tmp += g ;
          iR.putPixel(i, j, tmp);
        } else
          iR.putPixel(i, j, tmp);
      }
    }
    imR.show();
  }

}