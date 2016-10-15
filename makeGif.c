#include "libgif.h"

/*
{ 

}
*/

void read_image(MagickWand** image ,char* name_image, MagickWand** background,char* name_background){ 
  
  MagickBooleanType status;
  const char * string;

  
  *(image)=NewMagickWand();  
  *(background)=NewMagickWand();  

  status=MagickReadImage( *(image),name_image);
  if (status == MagickFalse)
    ThrowWandException(*(image)); 

  status=MagickReadImage( *(background), name_background);
  if (status == MagickFalse)
    ThrowWandException(*(background)); 
/*
  string = MagickIdentifyImage(*(image));
  printf("char %s \n",string);
*/
}

void resize_image(MagickWand* dest, int x, int y){  

  
  MagickResetIterator(dest);

  	
  while (MagickNextImage(dest) != MagickFalse)
    MagickResizeImage(dest,x,y,LanczosFilter);

}



void  make_gif(MagickWand* background, MagickWand* image,char* name_output, char* type , int delay){
int i;
MagickWand* clone=NewMagickWand();
MagickWand* result=NewMagickWand();
MagickBooleanType status;
size_t height_background;
size_t width_background;
size_t height_image;
size_t width_image;
size_t x;
size_t y;

height_background=MagickGetImageHeight(background);
printf("height--> %d \n",height_background);

width_background= MagickGetImageWidth(background);
printf("width--> %d \n",width_background);

height_image=MagickGetImageHeight(image);
printf("height--> %d \n",height_image);

width_image= MagickGetImageWidth(image);
printf("width--> %d \n",width_image);



status = MagickAddImage(clone, background);
if (status == MagickFalse)
    ThrowWandException(clone); 

i = 0;
    while (i  < 50 ){
        //printf(" %d \n",i);
        MagickCompositeLayers(clone, background, OverCompositeOp, 0 , 0);

          switch(*(type)){ 
            case 'c':
          		    x = (width_background/2) - (width_image/2)+( (width_image)*cos((float)i/4)); 
                  y = (height_background/2) - (height_image/2) - ((height_image)*sin((float)i/4));  
                  printf(" h %d  w %d \n",x,y); 

          break;
          	break;
          	case 'l':
                  x = ((width_image/2)*i ); 
                  y = (height_background/2);  
                  printf(" h %d  w %d \n",x,y); 

          	break;
            case 's':
                  x = ((width_image/2)*i); 
                  y = (height_background/2) - (height_image/2) - ((height_image/2)*sin((float)i/2));  
                  printf(" h %d  w %d \n",x,y); 
            break;
            case 'z':
                  x = (width_background/2) - (width_image/2)+( (width_image/2)*cos((float)i/2)); 
                  y = ((height_image/2)*i);  
                  printf(" h %d  w %d \n",x,y); 
            break;
          	case 'd':
                  x = ( (width_image/2)*i);   // modificarli 
                  y = height_background - (height_image/2) - ((width_image/4)*i);  // modificarli 
                  printf(" h %d  w %d \n",x,y); 
          	break;
          	default:
                  
                  printf(" null \n"); 
          	break;
          	}

        if(x > (width_background + width_image) ) 
         break;
         //if(x < (-width_image))
        //  break;
        if(y > (height_background + height_image) )
         break;
         //if(y < (-height_image))
          //break;
        if(i > 24 && *(type) == 'c' ) // 6 un giro --> 12 2 giri
                    break;


    MagickCompositeLayers(clone, image, OverCompositeOp, x , y);
   status=MagickAddImage(result,  clone);
    if (status == MagickFalse)
        ThrowWandException(clone);            
    MagickSetImageDelay(result, delay);               
         i++;

      
  } 

MagickWriteImages(result,name_output,MagickTrue); 

result=DestroyMagickWand(result);
clone=DestroyMagickWand(clone);
}



int main(int argc,char **argv)
{
  MagickWandGenesis();
  MagickBooleanType status;

  
  MagickWand* image;
  MagickWand* background ;


  if (argc != 5)
    {
      (void) fprintf(stdout,"Usage: %s image  background  output\n",argv[0]);
      exit(0);
    }
  
 

  read_image(&image, argv[1],&background,argv[2]);
  printf(" fine read \n");	
  

  resize_image(image,80,106);
  printf(" fine resize \n");	


  make_gif( background,image,argv[3],argv[4],15);
  printf(" fine gif \n");	


  image=DestroyMagickWand(image);
  background=DestroyMagickWand(background);

  MagickWandTerminus();
  return(0);
}
