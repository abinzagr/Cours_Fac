import ij.*;
import ij.process.*;
import ij.plugin.*;
import ij.plugin.filter.*;
import java.io.*;

public class Load_lut implements PlugInFilter{
  public void run(ImageProcessor ip) {
    LUT lut = LutLoader.openLut("lut.txt");
    ip.setLut(lut);
    
      
   try{
      
    FileReader fileRSize = new FileReader("lut.txt");
    int x = 0, size = 0;
    
    while((x = fileRSize.read()) != -1){
      if(x == 10) size++;
    }
  
    byte [] tabByteR = new byte [size];
    byte [] tabByteG = new byte [size];
    byte [] tabByteB = new byte [size];
    
    fileRSize.close();
    
    FileReader fileR = new FileReader("lut.txt");
    int i = 0;
    x = 0;
    int mod = 0;
    String tmp = "";
    
    while((x = fileR.read()) != -1){
      while(x >= 48 && x <= 57){
        tmp += (char)x;
        x = fileR.read();
      }
      mod %= 3;
      switch(mod){
        case(0):
          tabByteR[i] = (byte)Integer.parseInt(tmp);
          break;
        case(1):
          tabByteG[i] = (byte)Integer.parseInt(tmp);
          break;
        case(2):
          tabByteB[i] = (byte)Integer.parseInt(tmp);
          i++;
          break;
          default:
            System.out.println("erreur switch");
            break;
      }
      tmp = "";
      mod++;      
      
    }
    
    LUT lutTmp = new LUT(8,size,tabByteR,tabByteG,tabByteB);
    ip.setLut(lutTmp);
    
    fileR.close();
    }catch(java.io.IOException e){
      System.out.println("erreur fichier");
    }
  }
  public int setup(String arg, ImagePlus imp) {
    return DOES_8C;
  }
}