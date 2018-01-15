package tp2;

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;
import ij.gui.* ;

public class TailleResultat implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  public void run(ImageProcessor iI){
    GenericDialog gd = new GenericDialog( "Taille de l'image résultat",
        IJ.getInstance() );
    gd.addSlider( "largeur", 0.0, 1300.0, 400.0 );
    gd.addSlider( "hauteur", 0.0, 1000.0, 350.0 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    double wR = (double) gd.getNextNumber();
    double hR = (double) gd.getNextNumber();
    if (wR == 0 || hR == 0)
      return ;
    int w = iI.getWidth();
    int h = iI.getHeight();
    double sX = wR/w ;
    double sY = hR/h ;
    ImagePlus imR = NewImage.createRGBImage ("Agrandissement/Réduction", (int)wR, (int)hR, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    for(int yR = 0 ; yR < hR ; yR++)
      for(int xR = 0 ; xR < wR ; xR++)
        iR.putPixel(xR, yR, iI.getPixel((int)( (xR+(sX/2))/sX), (int) ( (yR+(sY/2)) /sY) )) ;
    imR.show();
  }
}