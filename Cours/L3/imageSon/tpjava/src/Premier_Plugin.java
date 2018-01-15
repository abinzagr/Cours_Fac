

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;

public class Premier_Plugin implements PlugInFilter {

  public void run(ImageProcessor ip){
    int width=ip.getWidth();
    int height=ip.getHeight();
    int tmp=0;
    for(int y=0;y<height;y++){
      for(int x=0;x<width/2;x++){
        tmp=ip.getPixel(x, y);
        ip.putPixel(x, y, ip.getPixel(width-x-1,y));
        ip.putPixel(width-x-1,y, tmp);
        
      }
    }
  }
  
  
  public int setup(String arg, ImagePlus imp){
    return DOES_RGB;
  }
  
}
