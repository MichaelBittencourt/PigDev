# PigDev

## Run on Linux without Code blocks

### Install dependencies

To execute this Library on Linux environment is necessary install some libraries on system.
To install these libraries execute commands bellow.

#### Install AV Libraries

```console
$ sudo apt-get update
$ sudo apt-get install libavcodec-dev libavformat-dev libavutil-dev libswresample-dev libavdevice-dev
```

#### Install SDL2
 
```console
$ sudo apt-get update
$ sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-net-dev libsdl2-gfx-dev libsdl2-doc
```

### Build and run code

Go to src folder and execute the make command to build

```console
$ cd src/
$ make
$ ./Projet.out
```
