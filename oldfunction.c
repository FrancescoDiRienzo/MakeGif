/*
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
   
    status=MagickAddImage(result,  clone);
    if (status == MagickFalse)
    	ThrowWandException(clone); 
	
    MagickSetImageDelay(result, 30);
    
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
*/
