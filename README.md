# MakeGif
MakeGif is a free image processing system to create gif of two image, one will be used for the backgound and the other
it will be moved to the background. The images will be resized automatically based on the ratio of their size
to get an appreciable gif without having to specify any configuration parameter.
You can choose which of the 5 possible trajectories for foreground:
```
1. -l --> realizes a linear trajectory from left to right at the middle of height of background
2. -d --> realizes a trajectory diagonal from the bottom-left corner to the upper-right of background
3. -c --> realizes a circular trajectory in the center of background with radius a shorter between width background and height background
4. -s --> realizes a horizontal sinusoidal trajectory from middle-left to the middle-right of background
5. -z --> realizes a vertical cosine trajectory from upper-middle to the bottom-middle of background
```

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
./makeGif [-b name_image_background] [-i name_image_foreground] [-o name_image_output] [-animation_type]
```

###Example:
```
./makeGif  -b background.jpeg -i mario.png -o mario_circle.gif -c 



Start Make ...
... Read Images ...
... Resize Images ...
... Gif is Ready! 

```
