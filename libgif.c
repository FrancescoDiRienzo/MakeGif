#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <MagickWand/MagickWand.h>
#include "constant.h"
#include "libgif.h"


void print_error_image(MagickWand * image)
{ 
  char *description; 
 
  ExceptionType severity; 

  description=MagickGetException(image ,&severity); 
  (void) fprintf(stderr,"\n \nERROR: %s \n\n",description); 
  
  exit(-1); 
}

// read the background and foreground image 
void read_image(MagickWand** image ,char* name_image, MagickWand** background,char* name_background){ 
  
   MagickBooleanType status;
   *(image)=NewMagickWand();  
   *(background)=NewMagickWand();  

   status=MagickReadImage(*(image),name_image);
   if (status == MagickFalse)
      print_error_image(*(image)); 

   status=MagickReadImage( *(background), name_background);
   if (status == MagickFalse)
      print_error_image(*(background)); 
}


// resize the foreground image 
void resize_image(MagickWand* image, MagickWand* background){  
   float x ;
   float y ;
   size_t height_background, width_background , height_image, width_image;
   
   height_image=MagickGetImageHeight(image);
   width_image= MagickGetImageWidth(image);
   
   height_background=MagickGetImageHeight(background);
   width_background= MagickGetImageWidth(background);
   
   // for index of resize 
   if(width_image < width_background || height_image < height_background){            

      x = width_background / width_image;
      y = height_background / height_image;

   }
   else{

      x = width_image / width_background;
      y = height_image /height_background;

   }
   MagickResetIterator(image);                          //the iteration need in case more than one image must be resize (like file .gif)
  
   if(width_image > height_image){                      // horizontal image
   while (MagickNextImage(image) != MagickFalse) 
           MagickResizeImage(image,width_image/(SIZE_FACTOR*x),height_image/(SIZE_FACTOR*x),LanczosFilter);
  }
   else if(width_image < height_image) {                // vertical image
      
   while (MagickNextImage(image) != MagickFalse) 
           MagickResizeImage(image,height_image/(SIZE_FACTOR*y),width_image/(SIZE_FACTOR*y),LanczosFilter);
   }
   else {                                               //square image      
   while (MagickNextImage(image) != MagickFalse) 
           MagickResizeImage(image,height_image/(SIZE_FACTOR*x),width_image/(SIZE_FACTOR*x),LanczosFilter);
   }
   

}

//
void  make_gif(MagickWand* background, MagickWand* image,char* name_output, int type ){
   int i;
   MagickWand* clone=NewMagickWand();
   MagickWand* result=NewMagickWand();
   MagickBooleanType status;
   size_t height_background, width_background, height_image, width_image;
   size_t x, y;
   x = 0;
   y = 0;
   i = 0;

   height_background=MagickGetImageHeight(background);
   width_background= MagickGetImageWidth(background);
   height_image=MagickGetImageHeight(image);
   width_image= MagickGetImageWidth(image);

   status = MagickAddImage(clone, background);   // copy the backgroud 
   if (status == MagickFalse)
      print_error_image(clone); 

   while (i  < LOOPS ){

      MagickCompositeLayers(clone, background, OverCompositeOp, 0 , 0);   
      
      switch(type){ 
            //the image do a circular trajectory around center point of background
            case CIRCLE:
               // choise a shorter between width_background and height_background
               if(width_background > height_background){
                  x = (width_background/2) - (width_image/2) + ((height_background/4)*cos((float)(2* M_PI/LOOPS*i))); 
                  y = (height_background/2) - (height_image/2) - ((height_background/4)*sin((float)(2* M_PI/LOOPS*i)));
               }
               else{
                  x = (width_background/2) - (width_image/2)+((width_background/4)*cos((float)(2* M_PI/LOOPS*i))); 
                  y = (height_background/2) - (height_image/2) - ((width_background/4)*sin((float)(2* M_PI/LOOPS*i)));
               }
               break;
            //the image do a linear trajectory from left to right at the middle of height of background   
            case LINEAR:

               x = ((width_background/LOOPS)*i ); 
               y = (height_background/2) - (height_image/2);  

               break;
            //the image do a sinusoidal trajectory from left to right at the middle of height of background  
            case SIN:
               
               x = ((width_background/LOOPS)*i ); 
               y = (height_background/2) - (height_image/2) - ((height_background/6)*sin((float)2* M_PI/LOOPS*i));  
             
               break;
            //the image do a cosinusoidal trajectory from left to right at the middle of height of background 
            case COS:
               
               x = (width_background/2) - (width_image/2)+( (width_background/6)*cos((float)2* M_PI/LOOPS*i)); 
               y = - (width_image/2) + ((height_background/LOOPS)*i);  

               break;
            //the image do a diagonal trajectory from left to right from the top to the bottom of the background
            case DIAGONAL:

               x = ( (width_background/LOOPS)*i); 
               y = height_background -(width_image/2) - ((height_background/LOOPS)*i); 

               break;
            //default --> the image do a linear trajectory from left to right at the middle of height of background  
            default:      

               x = ((width_background/LOOPS)*i ); 
               y = (height_background/2) - (height_image/2);  

               break;
      }
      
      MagickCompositeLayers(clone, image, OverCompositeOp, x , y);
      status=MagickAddImage(result,  clone);

      if (status == MagickFalse)
         print_error_image(clone);            

      MagickSetImageDelay(result, DELAY);               
         i++;
   } 

   MagickWriteImages(result,name_output,MagickTrue); 

   // free space
   result=DestroyMagickWand(result);
   clone=DestroyMagickWand(clone);
}
