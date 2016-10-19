# MakeGif
MakeGif is a free image processing system to create gif of two image.
Inserting the two images (background and foreground) you can choose which of the 5 possible trajectories for foreground:
```
1. -l --> realizes a linear trajectory
2. -d --> realizes a trajectory diagonal from the bottom-left corner to the upper-right
3. -c --> realizes a circular trajectory in the center of background
4. -s --> realizes a horizontal sinusoidal trajectory
5. -z --> realizes a vertical cosine trajectory
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
./makeGif [-b name_image_background] [-i name_image_foreground] [-o name_image_output] [-a  animation_type]
```
