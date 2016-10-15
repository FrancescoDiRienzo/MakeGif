#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <MagickWand/MagickWand.h>
#include "constant.h"
#include "libgif.h"

extern void  make_gif(MagickWand* , MagickWand* ,char* ,int , int);

int option = 0;
int type_animation = 0;
char* background_file = NULL;
char* input_file= NULL;
char* output_file= NULL;

// funzione complessiva per la stampa degli errori
void print_error(int tipo) {
	printf("\nError:\n");
    switch (tipo)
	{
		case ERROR_BACKGROUND_FILE :		
			printf("miss -b option\n");
		break;
		case ERROR_INPUT_FILE :		
			printf("miss -i option\n");
		break;
		case ERROR_OUTPUT_FILE :	
			printf("miss -o option\n");
		break;
		case ERROR_PARAMITERS :	
			printf("Choose the type of animation with the following options:\n");
			printf("\tlineal:  -l\n\tcircle:  -c\n\tsin:     -s\n\tcos:     -z\n\tdiagonal:-d\n");
		break;
		case ERROR_MULTIPLE_PARAMITERS :	
			printf("Choose only one option for the type of animation\n");
		break;
		default:	
			printf("default printf \n");
		break;
	}
}

	
void check_command_line(int num_arg, char *arg_value[])
{
	while ((option = getopt(num_arg, arg_value,"clszb:i:o:")) != -1) {
        switch (option) {
            case 'l' : if(type_animation==0) type_animation = LINEAR;
            		   else type_animation = -1;
       		    break;
            case 'c' : if(type_animation==0) type_animation = CIRCLE;
            		   else type_animation = -1;
                break;
            case 's' : if(type_animation==0) type_animation = SIN;
            		   else type_animation = -1;
                break;
            case 'z' : if(type_animation==0) type_animation = COS;
            		   else type_animation = -1;
                break; 
            case 'd' : if(type_animation==0) type_animation = DIAGONAL;
            		   else type_animation = -1;   
            	break;	   	
            case 'b' : background_file = optarg; 
                break;
            case 'i' : input_file = optarg;
                break;
	     	case 'o' : output_file = optarg;
		 		break;
            default: break;
        }
    }
    if (type_animation==0)  {
        print_error( ERROR_PARAMITERS );
        exit(EXIT_FAILURE);
    }

    if (type_animation==-1)  {
        print_error( ERROR_MULTIPLE_PARAMITERS );
        exit(EXIT_FAILURE);
    }

    if(background_file==NULL){
		print_error( ERROR_BACKGROUND_FILE );
		exit(EXIT_FAILURE);
	}

    if(input_file==NULL){
		print_error( ERROR_INPUT_FILE );
		exit(EXIT_FAILURE);
	}
		
    if(output_file==NULL){
		print_error( ERROR_OUTPUT_FILE );
		exit(EXIT_FAILURE);
	} 
	
	printf("\n\nStart Make..\n" );
	
	
}


int main(int num_arg, char *arg_value[]) {
	MagickWandGenesis();
  	MagickBooleanType status;
  
  	MagickWand* image;

  	MagickWand* background ;
	
	check_command_line(num_arg,arg_value);

	read_image(&image, input_file,&background,background_file);
 	printf(" fine read \n");	
  	MagickResizeImage(image,80,106,LanczosFilter);
  	//resize_image(image,80,106);
  	printf(" fine resize \n");	

  	//make_linear_gif(background,image,argv[2],argv[3]);
  	make_gif( background,image,output_file,type_animation,15);
  	printf(" fine gif \n");	


  	image=DestroyMagickWand(image);
  	background=DestroyMagickWand(background);

  	MagickWandTerminus();
	

    return 0;
}