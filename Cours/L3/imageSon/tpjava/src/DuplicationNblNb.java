
import ij.*;
import ij.process.*;
import ij.plugin.filter.*;
import ij.gui.* ;

public class DuplicationNblNb implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }
  
  public void run(ImageProcessor iI){
    GenericDialog gd = new GenericDialog( "Taille de l'image résultat",
        IJ.getInstance() );
    gd.addSlider( "dupliquation largeur", 0.0, 10.0, 2.0 );
    gd.addSlider( "duplication hauteur", 0.0, 10.0, 2.0 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    double nbl = (double) gd.getNextNumber();
    double nbh = (double) gd.getNextNumber();
    if (nbl == 0 || nbh == 0)
      return ;
    int w = iI.getWidth();
    int h = iI.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Agrandissement/Réduction", (int)(w*nbl), (int)(h*nbh), 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    for(int y = 0 ; y < h ; y++)
      for(int x = 0 ; x < w ; x++) {
        int tmp = iI.getPixel(x, y) ;
        for (int i = 0 ; i < nbl ; i++)
          for (int j = 0 ; j < nbh ; j++)
            iR.putPixel(x + w*i, (int)y + h*j, tmp) ;
      }
    imR.show();
  }
}