package tp2;

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;
import ij.gui.* ;

public class Ratio implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  public void run(ImageProcessor iI){
    GenericDialog gd = new GenericDialog( "Facteur d’echelle",
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
    for(int yR = 0 ; yR < hR ; yR++)
      for(int xR = 0 ; xR < wR ; xR++)
        iR.putPixel(xR, yR, iI.getPixel((int)((xR+(ratio/2))/ratio), (int) ( (yR+(ratio/2)) /ratio) )) ;
    imR.show();
  }
}