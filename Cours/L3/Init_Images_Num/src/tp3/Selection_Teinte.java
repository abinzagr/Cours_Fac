package tp3;

import ij.*;
import ij.gui.*;
import java.awt.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;

public class Selection_Teinte implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  int couleurVersNG(int couleur) {
    double gris = 0.3*((couleur&0xFF0000) >> 16) + 0.59*((couleur&0x00FF00) >> 8) + 0.11*(couleur&0x0000FF) ;
    return (int)gris*(1+256+256*256) ;
  }
  
  double distance(int couleur1, int couleur2) {
    float[] hsbVals1 = new float[3] ; ;
    float[] hsbVals2 = new float[3] ; ;
    Color.RGBtoHSB(((couleur1&0xFF0000) >> 16), ((couleur1&0x00FF00) >> 8), couleur1&0x0000FF, hsbVals1) ;
    Color.RGBtoHSB(((couleur2&0xFF0000) >> 16), ((couleur2&0x00FF00) >> 8), couleur2&0x0000FF, hsbVals2) ;
    double dist = Math.abs(hsbVals1[0]-hsbVals2[0]);
    return dist ;
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
    GenericDialog gd = new GenericDialog( "Distance à la teinte",
        IJ.getInstance() );
    gd.addSlider( "distance", 0.0, 1.0, 0.10 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    //
    
    double distanceMax = gd.getNextNumber() ;
    
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
        } else {
          iR.putPixel(i, j, tmp);
        }
      }
    }
    imR.show();
  }

}