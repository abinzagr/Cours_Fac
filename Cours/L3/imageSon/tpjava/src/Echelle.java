import ij.IJ;
import ij.ImagePlus;
import ij.gui.GenericDialog;
import ij.gui.NewImage;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;

public class Echelle implements PlugInFilter {

  public void run(ImageProcessor ip) {
    int width = ip.getWidth();
    int height = ip.getHeight();
    int tmp = 0;
    GenericDialog gd = new GenericDialog("Facteur d'echelle");
    // gd.addSlider("facteur", 0.0, 10.0, 2.0);
    gd.addSlider("Largeur", 10.0, 1500.0, 672.0);
    gd.addSlider("hauteur", 10.0, 1500.0, 512.0);
    gd.showDialog();
    if (gd.wasCanceled()) {
      IJ.error("Plugin cancelled");
      return;
    }
    int wR = (int) gd.getNextNumber();
    int hR = (int) gd.getNextNumber();
    double ratioX = (double)wR / width;
    double ratioY = (double)hR / height;
    /*
     * int width = (int) gd.getNextNumber(); int height = (int)
     * gd.getNextNumber();
     */
    ImagePlus iR = NewImage.createRGBImage("canal Rouge", wR, hR, 1,
        NewImage.FILL_BLACK);
    ImageProcessor iI = iR.getProcessor(); // traduction copie de travail
System.out.println(ratioX+"-"+ratioY);
    for (int yR = 0; yR < hR; ++yR) {
      for (int xR = 0; xR < wR; ++xR) {
        tmp = ip.getPixel((int) (xR / ratioX), (int) (yR / ratioY));
        iI.putPixel(xR, yR, tmp); // on opere sur la copie
      }
    }
    iR.show();
  }

  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }

}