package tp1;

import ij.*;
import ij.process.*;
import ij.gui.*;
import ij.plugin.filter.*;

public class Canal_Rouge implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
      return DOES_RGB;
  }
  
  public void run(ImageProcessor ip) {
    int w = ip.getWidth();
    int h = ip.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Canal rouge", w, h, 1, NewImage.FILL_BLACK);
    ImageProcessor ipR = imR.getProcessor();
    
    System.out.println(ip.getPixel(0, 0)/(256*256));
    for(int i = 0 ; i < w ; i++) {
      for (int j = 0 ; j < h ; j++) {
        /* 
         * Version avec   void getPixel(int, int, int[])
         * 
         * int []tmp = new int[3] ;
        ip.getPixel(i, j, tmp);
        tmp[1] = 0 ;
        tmp[2] = 0 ;
        ipR.putPixel(i, j, tmp);*/
        
        /*
         * Version avec   int getPixel(int, int)
         */
        int tmp = ip.getPixel(i, j) ;
        tmp /= 256*256 ;
        tmp *= 256*256 ;
        ipR.putPixel(i, j, tmp);
      }
    }
  
  
    imR.show();
  }
}