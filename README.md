# MakeGif
MakeGif is a free image processing system to create gif of two image. 


###Dependencies
1. [MagickWand](https://github.com/ImageMagick/ImageMagick/tree/master/MagickWand)


####Install Dependencies
In order to install the dependencies, there are two methods:

* Use a pkg manager like apt-get(Linux-like) or brew(Mac OS)
```
apt-get install ImageMagick
```
* Download,compile and install the library.
```
./configure
make
make install
```

###Execution:

```
./makeGif [-b name_image_background] [-i name_image_foreground] [-o name_image_output] [-a  animation_type] [-d delay_gif]
```
