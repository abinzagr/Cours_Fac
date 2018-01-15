import ij.*;
import ij.process.*;
import ij.plugin.filter.*;
import java.io.*;

public class Save_lut implements PlugInFilter{
  public void run(ImageProcessor ip) {
   LUT lutTmp = ip.getLut();
   byte[] tabByte = lutTmp.getBytes();
   
   try{
     FileWriter file = new FileWriter("lut.txt");
     int tmp_r,tmp_g,tmp_b;
     int len = tabByte.length;
     for(int i = 0; i < len/3;i++){   //
       tmp_r = Math.abs(tabByte[i]);
       tmp_g = Math.abs(tabByte[i+len/3]);
       tmp_b = Math.abs(tabByte[i+len-len/3]);
       file.write(tmp_r+" "+tmp_g+" "+tmp_b+"\n");
     }
     file.close();
   }catch(java.io.IOException e){
     System.err.println("erreur fichier");
   }
 }
 
 public int setup(String arg, ImagePlus imp) {
   return DOES_8C;
 }
}