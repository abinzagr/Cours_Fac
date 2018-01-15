package tp5;
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
	
	ImagePlus im1;
	ImagePlus im2;

	public void openFiles()
	{
		JFileChooser fc = new JFileChooser();
		fc.setMultiSelectionEnabled(true);

		File dir = null;
		String sdir = OpenDialog.getDefaultDirectory();
		if (sdir!=null)	dir = new File(sdir);
		if (dir!=null) fc.setCurrentDirectory(dir);
		int returnVal = fc.showOpenDialog(IJ.getInstance());
		if (returnVal!=JFileChooser.APPROVE_OPTION)
			return;

		File[] files = fc.getSelectedFiles();
		if ( files.length != 2 ) return;
		String folderPath = fc.getCurrentDirectory().getPath()+Prefs.getFileSeparator();
		dir = fc.getCurrentDirectory();

		Opener opener = new Opener();
		im1 = opener.openImage(folderPath, files[0].getName());
		im2 = opener.openImage(folderPath, files[1].getName());
	}
	
	public void differenceInterImages( ImagePlus im1, ImagePlus im2, ImagePlus imR, ImagePlus imV, ImagePlus imB )
	{
	  // on initialise les processeurs des images en paramètre et on prend leur hauteur et leur largeur
    ImageProcessor ip1 = im1.getProcessor();
    ImageProcessor ip2 = im2.getProcessor();
    ImageProcessor ipR = imR.getProcessor();
    ImageProcessor ipV = imV.getProcessor();
    ImageProcessor ipB = imB.getProcessor();
    int w = ip1.getWidth();
    int h = ip1.getHeight();
    
    for (int j = 0 ; j < h ; j++) {
      for (int i = 0 ; i < w ; i++) {
        int coul1 = ip1.getPixel(i, j) ;
        int coul2 = ip2.getPixel(i, j) ;
        // on prend la différence de chaque couleur entre les 2 images, sur 255 à chaque fois
        int coulR = Math.abs( ((coul1 & 0xFF0000)>>16) - ((coul2 & 0xFF0000)>>16) );
        int coulV = Math.abs( ((coul1 & 0x00FF00)>>8 ) - ((coul2 & 0x00FF00)>>8 ) );
        int coulB = Math.abs(  (coul1 & 0x0000FF)      -  (coul2 & 0x0000FF)      );
        // et on la met chacune dans l'image de la couleur correspondante
        // sans re-décaler leur bytes, car les images sont au format ByteImage (couleurs de 0 à 255)
        ipR.putPixel(i, j, coulR);
        ipV.putPixel(i, j, coulV);
        ipB.putPixel(i, j, coulB);
      }
    }
	}
	
	public void erodeEtDilateImage( ImagePlus im )
	{
    ImageProcessor ip = im.getProcessor();
    // on erode l'image
    ip.erode();
    // puis on la dilate
    ip.dilate();
	}
	
	public void fusion( ImagePlus imR, ImagePlus imV, ImagePlus imB, ImagePlus imRes )
	{
	  // il faut que les pixels de imR soient au format XX0000 (X de 0 à F), imV en 00XX00, imB en 0000XX
	  
    // on initialise les processeurs des images en paramètre et on prend leur hauteur et leur largeur
    ImageProcessor ipR = imR.getProcessor();
    ImageProcessor ipV = imV.getProcessor();
    ImageProcessor ipB = imB.getProcessor();
    ImageProcessor ipRes = imRes.getProcessor();
    int w = ipRes.getWidth();
    int h = ipRes.getHeight();
    
    for (int j = 0 ; j < h ; j++) {
      for (int i = 0 ; i < w ; i++) {
        int coulR = ipR.getPixel(i, j) ;
        int coulV = ipV.getPixel(i, j) ;
        int coulB = ipB.getPixel(i, j) ;
        // on vérifie quelle couleur est la plus haute avant de la mettre dans l'image résultat
        // sans décaler leur bytes, car les images(couleurs) sont au format ByteImage (couleurs de 0 à 255)
        if (coulR > coulV) {
          if (coulR > coulB)
            ipRes.putPixel(i, j, coulR);
          else
            ipRes.putPixel(i, j, coulB);
        }
        else {
          if (coulV > coulB)
            ipRes.putPixel(i, j, coulV);
          else
            ipRes.putPixel(i, j, coulB);
        }
      }
    }
	}
	
	public void seuillage(ImagePlus im, int minValue)
	{
    ImageProcessor ip = im.getProcessor();
    //threshold place chaque pixel <minValue à 0, et chaque pixel >minValue à 255
    ip.threshold(minValue);
	}

	@Override
	public void run(String arg0) {
		openFiles();
		
		if ( im1 == null || im2 == null ) return;

    int w = im1.getProcessor().getWidth();
    int h = im1.getProcessor().getHeight();
    ImagePlus imR = NewImage.createByteImage ("Canal rouge", w, h, 1, NewImage.FILL_BLACK);
    ImagePlus imV = NewImage.createByteImage ("Canal vert" , w, h, 1, NewImage.FILL_BLACK);
    ImagePlus imB = NewImage.createByteImage ("Canal bleu" , w, h, 1, NewImage.FILL_BLACK);
    ImagePlus imRes = NewImage.createByteImage ("Image résultat" , w, h, 1, NewImage.FILL_BLACK);
    differenceInterImages(im1, im2, imR, imV, imB) ;
    erodeEtDilateImage(imR) ;
    erodeEtDilateImage(imV) ;
    erodeEtDilateImage(imB) ;
    fusion(imR, imV, imB, imRes) ;
    seuillage(imRes, 50) ;
    imRes.show();
		
	}

}