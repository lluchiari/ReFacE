# ReFacE
Reconhecimento Facial com visão Estéreo

ReFaCe is framework for Facial Recognition with Stereo Vision.

The project is hosted on github: 
https://github.com/lluchiari/ReFacE

The online version built in Doxygen is comming soon.

## What it does. ##
-------------

In a nutshell ReFacE is a framework that was proposed be used to create a 
modular face recognition system using Stereo Vision.

But  it's framework can be used for anything, you just need to folow the framework!

The framework consist in modules that inherite from a common root class called "Module". It forces all the modules
implement two basic functions: setup() and run();

Besides this every module requires a Setting file that dictates how the modules will run and with witch configuration files.

[Figure]

## Download Source ##
-------------
To retrieve the code:

 git clone https://github.com/lluchiari/ReFacE
    cd ReFacE


## Dependencies ##
-------------

ReFacE has the following dependencies:

* [OpenCV](https://opencv.org/) in version 3.4.1
* [Qt](https://www.qt.io) in version 5.10.1
* [TinnyXml2](https://github.com/leethomason/tinyxml2)
* [OpenFaceCpp](https://github.com/aybassiouny/OpenFaceCpp)