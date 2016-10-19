#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <MagickWand/MagickWand.h>
#include "constant.h"
#include "libgif.h"

//It contains the informations obtained using la getopt() 
typedef struct datainput{
  int option;
  int type_animation;
  char* background_file;
  char* input_file;
  char* output_file;
} data_input;
//Initialization of the structure
void datainput_init(data_input* d){
  d->option=0;
  d->type_animation=0;
  d->background_file=NULL;
  d->input_file=NULL;
  d->output_file=NULL;
}

// function for the print of error
void print_error(int type) {
	printf("\nError:\n");
    switch (type)
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
		case ERROR_PARAMETERS :	
			printf("Choose the type of animation with the following options:\n");
			printf("\tlineal:  -l\n\tcircle:  -c\n\tsin:     -s\n\tcos:     -z\n\tdiagonal:-d\n");
		  break;
		case ERROR_MULTIPLE_PARAMETERS :	
			printf("Choose only one option for the type of animation\n");
		  break;
		default:	
			printf("default printf \n");
		  break;
	}
}

	
void check_command_line(int num_arg, char *arg_value[], data_input* d)
{
	while ((d->option = getopt(num_arg, arg_value,"clszdb:i:o:")) != -1) {
    switch (d->option) {
          case 'l' : 
              if(d->type_animation==0) d->type_animation = LINEAR;
              else d->type_animation = -1;
       		    break;
          case 'c' : 
              if(d->type_animation==0) d->type_animation = CIRCLE;
            	else d->type_animation = -1;
              break;
          case 's' : 
              if(d->type_animation==0) d->type_animation = SIN;
            	else d->type_animation = -1;
              break;
          case 'z' : 
              if(d->type_animation==0) d->type_animation = COS;
            	else d->type_animation = -1;
              break; 
          case 'd' : 
              if(d->type_animation==0) d->type_animation = DIAGONAL;
            	else d->type_animation = -1;   
            	break;	   	
          case 'b' : 
              d->background_file = optarg; 
              break;
          case 'i' : 
              d->input_file = optarg;
              break;
	     	  case 'o' : 
              d->output_file = optarg;
		 		      break;
          default: 
              break;
        }
    }
    //the user must select one and only one type of animation
    if (d->type_animation==0)  {
        print_error( ERROR_PARAMETERS );
        exit(EXIT_FAILURE);
    }

    if (d->type_animation==-1)  {
        print_error( ERROR_MULTIPLE_PARAMETERS );
        exit(EXIT_FAILURE);
    }

    if(d->background_file==NULL){
		    print_error( ERROR_BACKGROUND_FILE );
		    exit(EXIT_FAILURE);
	}

    if(d->input_file==NULL){
		    print_error( ERROR_INPUT_FILE );
		    exit(EXIT_FAILURE);
	}
		
    if(d->output_file==NULL){
		    print_error( ERROR_OUTPUT_FILE );
		    exit(EXIT_FAILURE);
	} 
	
	printf("\n\nStart Make ...\n" );
	
	
}


int main(int num_arg, char *arg_value[]) {
  data_input d;
	datainput_init(&d);

  MagickWand* image;
  MagickWand* background ;

  MagickWandGenesis();
	
	check_command_line(num_arg,arg_value,&d);

	read_image(&image, d.input_file,&background,d.background_file);
 	printf("... Read Images ...\n");	

  
  resize_image(image, background);
  printf("... Resize Images ...\n");	

  make_gif(background, image, d.output_file, d.type_animation);
  printf("... Gif is Ready! \n\n");	

  image=DestroyMagickWand(image);
  background=DestroyMagickWand(background);

  MagickWandTerminus();
	
  return 0;
}
