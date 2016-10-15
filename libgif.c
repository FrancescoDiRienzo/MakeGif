#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MagickWand/MagickWand.h>
#include "libgif.h"

void read_image(MagickWand** image ,char* name_image, MagickWand** background,char* name_background){ 
  
  //MagickBooleanType status;
  
  *(image)=NewMagickWand();  
  *(background)=NewMagickWand();  

  status=MagickReadImage( *(image),name_image);
  if (status == MagickFalse)
    ThrowWandException(*(image)); 

  status=MagickReadImage( *(background), name_background);
  if (status == MagickFalse)
    ThrowWandException(*(background)); 

}

void resize_image(MagickWand* dest, int x, int y){  

  MagickResetIterator(dest);

    
  while (MagickNextImage(dest) != MagickFalse)
    MagickResizeImage(dest,x,y,LanczosFilter);

}