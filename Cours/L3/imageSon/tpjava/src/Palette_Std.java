import ij.*;
import ij.gui.NewImage;
import ij.plugin.filter.PlugInFilter;
import ij.process.ImageProcessor;
import ij.process.LUT;

public class Palette_Std implements PlugInFilter{
  
  double distance(int r1, int g1, int b1, int r2, int g2, int b2) {
    double dist = Math.pow(r1-r2, 2) + Math.pow(g1-g2, 2) + Math.pow(b1-b2, 2);
    return dist;
  }
  
  int indice_Couleur(int c, LUT l){
    // decouper c en rgb
    int r1 = (c & 0xff0000) >> 16;
    int g1 = (c & 0x00ff00) >> 8;
    int b1 = (c & 0x0000ff);
    double dmin = 255+255+255;
    int imin = -1;
    
    for(int i = 0; i < 256; ++i){
      double d = distance(r1,g1,b1,l.getRed(i),l.getGreen(i),l.getBlue(i));
      if(d < dmin){
        dmin = d;
        imin = i;
      }
    }
    return imin;
  }
  
  public void run(ImageProcessor ip) {
    byte[] r = new byte[256];
    byte[] g = new byte[256];
    byte[] b = new byte[256];
    
    byte[] rVals = {(byte)0, (byte)36, (byte)12, (byte)108, (byte)144, (byte)180, (byte)212, (byte)255};
    byte[] gVals = {(byte)0, (byte)36, (byte)12, (byte)108, (byte)144, (byte)180, (byte)212, (byte)255};
    byte[] bVals = {(byte)0, (byte)85, (byte)170, (byte)255};
    
    int cpt = 1;
    
    for (int j = 0; j < 8; ++j)
      for (int i = 0; i < 8; ++i)
        for (int k = 0; k < 4; ++k){
          r[cpt] = rVals[j];
          g[cpt] = gVals[i];
          b[cpt] = bVals[k];
          cpt++;
        }
    LUT l = new LUT(r,g,b);
    
    int w = ip.getWidth(); int h = ip.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Image-Resultat", w, h, 1, NewImage.FILL_WHITE);
    ImageProcessor ipR = imR.getProcessor();
    for (int j = 0; j < h; ++j)
      for (int i = 0; i < w; ++i)
        ip.putPixel(i, j,indice_Couleur(ip.getPixel(i,j),l));
    ipR.setLut(l);
    imR.show();
    
  }
  public int setup(String arg, ImagePlus imp) {
    return DOES_RGB;
  }

}