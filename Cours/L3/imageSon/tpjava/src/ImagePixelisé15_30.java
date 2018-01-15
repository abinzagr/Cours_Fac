import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.NewImage;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class ImagePixelisé15_30 implements PlugInFilter {
  
  public void run(ImageProcessor iI){
    GenericDialog gd = new GenericDialog( "Facteur d'agrandissement image",
        IJ.getInstance() );//facteur d'agrandissement
    gd.addSlider( "facteur", 0.0, 30.0, 2.0 );
    gd.showDialog() ;
    if ( gd.wasCanceled() ) {
      IJ.error( "PlugIn cancelled" );
      return;
    }
    double ratio = (double) gd.getNextNumber();//on recupere la valeur du facteur
    if (ratio == 0)
      return ;
    int w = iI.getWidth();
    int h = iI.getHeight();
    double wR = w*ratio ;
    double hR = h*ratio ;
    ImagePlus imR = NewImage.createRGBImage ("Agrandissement de l'image reduite", (int)wR, (int)hR, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    for(int y = 0 ; y < h ; y++) //parcours de boucle classique!!
      for(int x = 0 ; x < w ; x++) {
        int tmp = iI.getPixel(x, y) ;
        for (int i = 0 ; i < ratio ; i++) //Application de la pixelisation
          for (int j = 0 ; j < ratio ; j++)
            iR.putPixel(x*(int)ratio + i, y*(int)ratio + j, tmp) ;
      }
    imR.show();
  }

  
  
  
  
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }  
}
