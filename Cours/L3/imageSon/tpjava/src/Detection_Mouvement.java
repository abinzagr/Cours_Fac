import java.awt.Color;
import java.io.File;

import javax.swing.JFileChooser;

import ij.IJ;
import ij.ImagePlus;
import ij.Prefs;
import ij.gui.NewImage;
import ij.io.OpenDialog;
import ij.io.Opener;
import ij.plugin.PlugIn;
import ij.process.ImageProcessor;

public class Detection_Mouvement implements PlugIn {

  public int max(int x, int y, int z) {
    int max = 0;
    if (x > y) {
      max = x;
      if (z > max)
        max = z;
    } else {
      max = y;
      if (z > max)
        max = z;
    }
    return max;
  }

  ImagePlus im1;
  ImagePlus im2;

  public void openFiles() {
    JFileChooser fc = new JFileChooser();
    fc.setMultiSelectionEnabled(true);

    File dir = null;
    String sdir = OpenDialog.getDefaultDirectory();
    if (sdir != null)
      dir = new File(sdir);
    if (dir != null)
      fc.setCurrentDirectory(dir);
    int returnVal = fc.showOpenDialog(IJ.getInstance());
    if (returnVal != JFileChooser.APPROVE_OPTION)
      return;

    File[] files = fc.getSelectedFiles();
    if (files.length != 2)
      return;
    String folderPath = fc.getCurrentDirectory().getPath()
        + Prefs.getFileSeparator();
    dir = fc.getCurrentDirectory();

    Opener opener = new Opener();
    im1 = opener.openImage(folderPath, files[0].getName());
    im2 = opener.openImage(folderPath, files[1].getName());
  }

  public void differenceInterImages(ImagePlus im1, ImagePlus im2,
      ImagePlus imR, ImagePlus imV, ImagePlus imB) {
    ImageProcessor ip1 = im1.getProcessor();
    ImageProcessor ip2 = im2.getProcessor();
    ImageProcessor ipR = imR.getProcessor();
    ImageProcessor ipV = imV.getProcessor();
    ImageProcessor ipB = imB.getProcessor();
    
    int width = ip1.getWidth();
    int height = ip1.getHeight();
    int couleur1 = 0;
    int couleur2 = 0;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {

        couleur1 = ip1.getPixel(x, y);
        int r1 = (couleur1 & 0xFF0000) >> 16;
        int g1 = (couleur1 & 0x00FF00) >> 8;
        int b1 = (couleur1 & 0x0000FF);

        couleur2 = ip2.getPixel(x, y);
        int r2 = (couleur2 & 0xFF0000) >> 16;
        int g2 = (couleur2 & 0x00FF00) >> 8;
        int b2 = (couleur2 & 0x0000FF);
        //System.out.println(r1+" "+r2);
        int r = Math.abs(r1 - r2);
        System.out.println(r);
        int v = Math.abs(g1 - g2);
        int b = Math.abs(b1 - b2);
        ipR.putPixel(x, y, r);
        ipV.putPixel(x, y, v);
        ipB.putPixel(x, y, b);
      }

    }
  }

  public void erodeEtDilateImage(ImagePlus im) {
    ImageProcessor ip1 = im.getProcessor();
    ip1.erode();
    ip1.dilate();

  }

  public void fusion(ImagePlus imR, ImagePlus imV, ImagePlus imB,
      ImagePlus imRes) {
    ImageProcessor ipR = imR.getProcessor();
    ImageProcessor ipV = imV.getProcessor();
    ImageProcessor ipB = imB.getProcessor();
    ImageProcessor ipRes = imRes.getProcessor();
    int width = ipR.getWidth();
    int height = ipR.getHeight();
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {

        couleur1 = ipR.getPixel(x, y);
        int r1 = (couleur1 & 0xFF0000) >> 16;
        int g1 = (couleur1 & 0x00FF00) >> 8;
        int b1 = (couleur1 & 0x0000FF);

        couleur2 = ipV.getPixel(x, y);
        int r2 = (couleur2 & 0xFF0000) >> 16;
        int g2 = (couleur2 & 0x00FF00) >> 8;
        int b2 = (couleur2 & 0x0000FF);

        couleur3 = ipB.getPixel(x, y);
        int r3 = (couleur3 & 0xFF0000) >> 16;
        int g3 = (couleur3 & 0x00FF00) >> 8;
        int b3 = (couleur3 & 0x0000FF);

        ipRes.putPixel(x, y, (max(r1, r2, r3) << 16) + (max(g1, g2, g3) << 8)
            + max(b1, b2, b3));
      }

    }

  }

  public void seuillage(ImagePlus im, int minValue) {
    ImageProcessor ip = im.getProcessor();
    ip.threshold(minValue);
  }

  // @Override
  public void run(String arg0) {
    openFiles();

    if (im1 == null || im2 == null)
      return;
    /*
     * ImageProcessor ip1=im1.getProcessor(); ImageProcessor
     * ip2=im1.getProcessor();
     */
    int width = im1.getWidth();
    int height = im1.getHeight();
    ImagePlus imR = NewImage.createByteImage("imageRouge", width, height, 1,
        NewImage.FILL_BLACK);
    ImagePlus imG = NewImage.createByteImage("imageVerte", width, height, 1,
        NewImage.FILL_BLACK);
    ImagePlus imB = NewImage.createByteImage("imageBleu", width, height, 1,
        NewImage.FILL_BLACK);
    ImagePlus imRes = NewImage.createByteImage("imageResultat", width, height, 1,
        NewImage.FILL_BLACK);
    differenceInterImages(im1, im2, imR, imG, imB);
    imR.show();
    imG.show();
    imB.show();
    fusion(imR, imG, imB, imRes);
    imRes.show();

  }
  /*
   * public int setup(String arg, ImagePlus imp) { return DOES_RGB;}
   */

}
