import ij.*;
import ij.gui.GenericDialog;
import ij.gui.NewImage;
import ij.process.*;
import ij.plugin.filter.*;

public class Reduction implements PlugInFilter {
  public int setup(String args, ImagePlus im) {
    return DOES_RGB;
  }

  public void run(ImageProcessor ip) {
    int w = ip.getHeight();
    int h = ip.getWidth();
    GenericDialog gd = new GenericDialog("Facteur d�echelle", IJ.getInstance());
    //gd.addSlider("Facteur", 0.0, 10.0, 2.0);
    gd.addSlider("Height", 200, h * 2, h);
    gd.addSlider("Width", 200, w * 2, w);
    gd.showDialog();
    if (gd.wasCanceled()) {
      IJ.error("PlugIn cancelled");
      return;
    }
    //double ratio = (double) gd.getNextNumber();
    int ratioh = (int) gd.getNextNumber();
    int ratiow = (int) gd.getNextNumber();
/*
    int wR = (int) (ratio * w);
    int hR = (int) (ratio * h);

    ImagePlus imN = NewImage.createRGBImage("", wR, hR, 1, NewImage.FILL_BLACK);
    ImageProcessor ipN = imN.getProcessor();

    for (int i = 0; i < hR; i++) {
      for (int j = 0; j < wR; j++) {
        int value = ip.getPixel((int) (j / ratio), (int) (i / ratio));
        ipN.putPixel(j, i, value);
      }
    }
    imN.show();*/

    int wR = (int) ratiow;
    int hR = (int) ratioh;

    double ratioX = (double) wR / w;
    double ratioY = (double) hR / h;
    // putin de cast de merde !!!

    ImagePlus imNbis = NewImage.createRGBImage("", wR, hR, 1,
        NewImage.FILL_BLACK);
    ImageProcessor ipNBis = imNbis.getProcessor();
    System.out.println("ratioX: " + ratioX);
    for (int i = 0; i < hR; i++) {
      for (int j = 0; j < wR; j++) {
        int value = ip.getPixel((int) (j / ratioX), (int) (i / ratioY));
        ipNBis.putPixel(j, i, value);
      }
    }

    imNbis.show();

  }
}