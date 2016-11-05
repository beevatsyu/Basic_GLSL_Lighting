* Tested on NVIDIA GeForce GTX 580/PCI/SSE2 and ATI Mobility Radeon HD 4500 on Ubuntu 12.04.
* Only single directional point light source is used for simple demonstration.
* Replace pfdsl.* files in light.c with pvdsl.* files for per vertex lighting.
* GLSL version 110 is used so that this program can be run on older GPUs (at least having OpenGL 2.0 specification) also.
* Make sure that GLEW(OpenGL Extension Wrangler Library) is installed in your system, otherwise code can't be compiled.
* For any kind of query, suggestion, appreciation or problem regarding these codes email me at mcs112580[At]cse[Dot]iitd[Dot]ac[Dot]in
* To compile: gcc light.c -lGL -lGLU -lGLEW -lglut
* To run: ./a.out
