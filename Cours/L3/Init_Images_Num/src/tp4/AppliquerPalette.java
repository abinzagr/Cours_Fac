package tp4;

import ij.*;
import ij.gui.*;
import ij.plugin.filter.PlugInFilter;
import ij.process.*;


public class AppliquerPalette implements PlugInFilter {
  public int setup(String arg, ImagePlus imp) {
    return DOES_ALL;
  }

  public static int min255(double n) {
	if (n > 255)
	  return 255 ;
	return (int)n ;
  }
	  
  public static int[][] paletteStandard() {
	int[][] tmp = new int[256][3]; //les 3 paramètres : R, G, B
	for(int i = 0 ; i < 256 ; i++) {
	  tmp[i][0] = (int) (i*5)%256 ;
	  tmp[i][1] = i ;
	  tmp[i][2] = (int) (i*25.5)%256 ;
	}
	return tmp ;
  }

  public static double niveauDeGris(int couleur) {
    double gris = 0.3*((couleur&0xFF0000) >> 16) + 0.59*((couleur&0x00FF00) >> 8) + 0.11*(couleur&0x0000FF) ;
    return gris ;
  }
  
  public static int casePalette(int[][] palette, int couleur) {
	int couleurPal = palette[0][0]*256*256 + palette[0][1]*256 + palette[0][2] ;
	int numCaseP = 0 ;
	double nuanceCaseP = Math.abs(niveauDeGris(couleurPal) - niveauDeGris(couleur)) ;
	for (int i = 1 ; i < 256 ; i++) {
	  couleurPal = palette[i][0]*256*256 + palette[i][1]*256 + palette[i][2] ;
	  double tmp = Math.abs(niveauDeGris(couleurPal) - niveauDeGris(couleur)) ;
	  if (tmp < nuanceCaseP) {
		numCaseP = i ;
		nuanceCaseP = tmp ;
	  }
	}
	return numCaseP ;
  }
  
  public void run(ImageProcessor ip) {
	int[][] palette = paletteStandard() ;
	int w = ip.getWidth();
    int h = ip.getHeight();
    ImagePlus imR = NewImage.createRGBImage ("Couleurs proches", w, h, 1, NewImage.FILL_BLACK);
    ImageProcessor iR = imR.getProcessor();
    
	for(int j = 0 ; j < h ; j++) {
	  for (int i = 0 ; i < w ; i++) {
		int pix = ip.getPixel(i, j) ;
		int numCP = casePalette(palette, pix) ;
		pix = palette[numCP][0]*256*256 + palette[numCP][1]*256 + palette[numCP][2] ;
		iR.putPixel(i, j, pix) ;
	  }
	}
	imR.show() ;
  }
}