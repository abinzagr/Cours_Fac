import ij.*;
import ij.process.*;
import ij.plugin.*;
import ij.plugin.filter.*;

import java.io.*;

public class ImageLoad implements PlugInFilter {
  public void run(ImageProcessor ip) {
    int size = 108;
    byte[] tabByteR = new byte[size];
    byte[] tabByteG = new byte[size];
    byte[] tabByteB = new byte[size];
    // 108 valeurs

    int[] rValeurs = { 244, 138, 255, 242, 176, 173, 255, 140, 246, 171, 216,
        255, 120, 255, 255, 255, 187, 207, 180, 208, 30, 250, 84, 27, 84, 0,
        127, 253, 88, 145, 175, 151, 249, 240, 115, 188, 103, 245, 214, 6, 86,
        38, 72, 183, 0, 156, 165, 222, 248, 238, 144, 249, 173, 239, 205, 112,
        117, 244, 137, 25, 0, 91, 112, 136, 114, 221, 0, 255, 252, 95, 236,
        150, 28, 14, 49, 138, 100, 200, 164, 70, 63, 157, 71, 135, 123, 142,
        86, 145, 211, 255, 241, 243, 250, 255, 119, 96, 68, 62, 255, 55, 170,
        70, 104, 211, 160, 205, 226, 119 };

    int[] gValeurs = { 244, 146, 214, 112, 160, 217, 133, 0, 169, 217, 109,
        128, 252, 242, 135, 148, 128, 138, 0, 80, 90, 200, 51, 42, 89, 133,
        196, 195, 171, 80, 190, 203, 183, 109, 150, 180, 31, 134, 121, 157, 71,
        70, 97, 212, 170, 214, 202, 234, 154, 84, 31, 167, 97, 88, 221, 129,
        101, 129, 125, 50, 69, 117, 142, 96, 0, 152, 158, 207, 172, 49, 68,
        150, 88, 62, 43, 18, 100, 200, 118, 138, 182, 195, 111, 43, 93, 85, 78,
        149, 53, 158, 120, 201, 169, 236, 201, 186, 26, 149, 201, 33, 125, 155,
        195, 242, 110, 164, 249, 119 };

    int[] bValeurs = { 244, 141, 127, 94, 111, 168, 0, 255, 187, 255, 44, 20,
        120, 48, 156, 148, 90, 71, 0, 152, 168, 10, 36, 52, 85, 43, 117, 131,
        65, 28, 214, 217, 165, 97, 200, 165, 129, 36, 35, 159, 47, 154, 172,
        37, 164, 204, 24, 146, 57, 52, 118, 119, 64, 40, 52, 154, 125, 71, 98,
        90, 26, 114, 124, 94, 18, 46, 206, 11, 0, 9, 29, 150, 167, 154, 135,
        168, 100, 200, 36, 95, 169, 247, 182, 23, 65, 151, 157, 202, 157, 205,
        128, 136, 100, 108, 216, 118, 145, 182, 149, 0, 85, 195, 226, 234, 185,
        222, 154, 78 };

    for (int i = 0; i < 108; i++) { //pour chaque tableaux on lui charge sa valeur la plus proche parmi les couleurs disponibles en lego!!!
      tabByteR[i] = (byte) (rValeurs[i]);

      tabByteG[i] = (byte) (gValeurs[i]);

      tabByteB[i] = (byte) (bValeurs[i]);
    }
    LUT lutTmp = new LUT(8,size,tabByteR,tabByteG,tabByteB);//on modifie la LUT de l'image traitée par les nouvelles valeurs chargées!!
    ip.setLut(lutTmp);
  }

  public int setup(String arg, ImagePlus imp) {
    return DOES_8C;
  }
}