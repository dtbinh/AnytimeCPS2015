Real-time reachability implementation
http://verivital.com/rtreach/

RELEASE HISTORY

Version 0.11
July 12, 2015
* Refactored dynamics to be used for analysis by makefile parameter

Version 0.1
June 22, 2015
* Initial release

License: http://verivital.uta.edu/rtreach/rtreach_license.pdf

Stanley Bak: http://stanleybak.com/
Taylor Johnson: http://www.taylortjohnson.com/
Marco Caccamo: http://pertsserver.cs.uiuc.edu/~mcaccamo/
Lui Sha: https://publish.illinois.edu/cpsintegrationlab/people/lui-sha/

Theory described in RTSS 2014 paper: http://www.taylortjohnson.com/research/bak2014rtss.pdf

Directory structure:
main.c: this is the main file

Example call:

The executable is typically called rtreach or rtreach_arm, although this varies some on the platform.

A basic call for the linearized inverted pendulum system is:

./rtreach 100 -0.1 0.0 0.0 1.1

which will use 100ms runtime and an initial state x_0 of [-0.1, 0.0, 0.0, 1.1]

In Matlab, this can be executed as:

rtreach(100.0, -0.1, 0.0, 0.0, 1.1)

NOTE: Matlab version cannot (due to how MEX accepts input arguments) be executed as: rtreach 100 -0.1 0.0 0.0 1.1

x86/x86-64 (Windows): from a Matlab console, execute:
1) make
2) the executable is called rtreach, an example call appears in the main file main.c, this can be executed via the Matlab MEX interface on Windows or Linux

x86/x86-64 (Linux): from the console, execute:
1) make
2) the executable is called rtreach, an example call appears in the main file main.c, this can be executed via a standard Linux executable as ./rtreach

ARM
1) make arm
2) the executable is called rtreach_arm

AVR
Need to use the Arduino Studio and the src.ino file, and can deploy to an AVR board via the Arduino studio.


qemu setup guide for OS on arm board:

http://fedoraproject.org/wiki/Architectures/ARM/HowToQemu