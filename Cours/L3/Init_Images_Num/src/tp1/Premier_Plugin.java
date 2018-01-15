package tp1;

import ij.*;
import ij.process.*;
import ij.plugin.filter.*;

public class Premier_Plugin implements PlugInFilter {
   public void run(ImageProcessor ip){
      ip.flipHorizontal();
   }
   public int setup(String arg, ImagePlus imp){
      return DOES_RGB;
   }
}