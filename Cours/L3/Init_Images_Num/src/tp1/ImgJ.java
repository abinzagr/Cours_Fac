package tp1;

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;

public class ImgJ implements PlugInFilter {
  public void run(ImageProcessor ip){
    int w = ip.getWidth();
    int h = ip.getHeight();
    for(int i = 0 ; i < w/2 ; i++) {
      for (int j = 0 ; j < h ; j++) {
        int tmp = ip.getPixel(i, j);
        ip.putPixel(i, j, ip.getPixel(w-i-1, j));
        ip.putPixel(w-i-1, j, tmp);
      }
    }
  }
  public int setup(String arg, ImagePlus imp){
    return DOES_RGB;
  }
}
