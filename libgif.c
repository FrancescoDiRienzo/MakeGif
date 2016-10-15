/*
#include "libgif.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MagickWand/MagickWand.h>

void read_image(MagickWand** image ,char* name_image, MagickWand** background,char* name_background){ 
  
  MagickBooleanType status;

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

  printf(" 1 \n");	
  MagickResetIterator(dest);

  printf(" 2 \n");	
  while (MagickNextImage(dest) != MagickFalse)
    MagickResizeImage(dest,x,y,LanczosFilter);
	
  printf(" 3 \n");
}



void  make_linear_gif(MagickWand* background, MagickWand* image,char* name_background,char* name_output){ 
int i;
MagickWand* clone=NewMagickWand();
MagickWand* result=NewMagickWand();
MagickBooleanType status;
i = 0;
printf(" 1 \n");
status = MagickAddImage(clone, background);
if (status == MagickFalse)
    ThrowWandException(clone); 
printf(" 1 \n");

while (i < 20){
    printf(" %d \n",i);
    MagickCompositeLayers(clone, background, OverCompositeOp, 0 , 0);
    MagickCompositeLayers(clone, image, OverCompositeOp, 0+(10*i) , 335);
    
    //MagickCompositeLayers(result, clone, OverCompositeOp, 0 , 0);  
  
    status=MagickAddImage(result,  clone);
    if (status == MagickFalse)
    	ThrowWandException(clone); 
	
    MagickSetImageDelay(result, 30);
    //MagickWriteImages(temp,name_output,MagickTrue);
    //MagickReadImage(background,name_background);
    //MagickCompositeImage(result, clone, AddCompositeOp ,MagickTrue, 0 ,0);
    //clone=NewMagickWand();
    i++;
  } 
MagickWriteImages(result,name_output,MagickTrue); 
}

void  make_circle_gif(MagickWand* background, MagickWand* image,char* name_background,char* name_output ,int x ,int y , int r){ 
int i;
MagickWand* clone=NewMagickWand();
MagickWand* result=NewMagickWand();
MagickBooleanType status;
i = 30;
printf(" 1 \n");
status = MagickAddImage(clone, background);
if (status == MagickFalse)
    ThrowWandException(clone); 
printf(" 1 \n");

while (i > 0 ){
    printf(" %d \n",i);
    MagickCompositeLayers(clone, background, OverCompositeOp, 0 , 0);
    MagickCompositeLayers(clone, image, OverCompositeOp, x+(r*cos(i)) , y - (r*sin(i)));
    status=MagickAddImage(result,  clone);
    if (status == MagickFalse)
    	ThrowWandException(clone); 
	
    MagickSetImageDelay(result, 20);
    
    i--;
  } 
MagickWriteImages(result,name_output,MagickTrue); 
}


/*
