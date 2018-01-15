package tp2;

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;
import ij.gui.* ;

public class Mosaiquage implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  public void run(ImageProcessor iI){
    GenericDialog gd = new GenericDialog( "Facteur de mosaïquage",
        IJ.getInstance() );
    gd.addSlider( "facteur", 0.0, 10.0, 2.0 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    double ratio = (double) gd.getNextNumber();
    if (ratio == 0)
      return ;
    int w = iI.getWidth();
    int h = iI.getHeight();
    double wR = w*ratio ;
    double hR = h*ratio ;
    ImagePlus imR = NewImage.createRGBImage ("Agrandissement/Réduction", (int)wR, (int)hR, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    for(int y = 0 ; y < h ; y++)
      for(int x = 0 ; x < w ; x++) {
        int tmp = iI.getPixel(x, y) ;
        for (int i = 0 ; i < ratio ; i++)
          for (int j = 0 ; j < ratio ; j++)
            iR.putPixel(x*(int)ratio + i, y*(int)ratio + j, tmp) ;
      }
    imR.show();
  }
}