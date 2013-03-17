Discordia Water Demo
=========================================

This is a work test that I did in the begining of 2005, with OpenGL pixel and vertex shaders. 

It is a scene that has a few textured boxes and a transparent water plane. When the user clicks and drags the mouse over the water plane there are waves created. The water plane is implemented by an approximation of Navier-Stockes equations. The code for the Navier-Stockes solver has not been written by me but by YannL, moderator at Gamedev in 2005. His code code be found at these links once upon a time, but they seem to be dead now:

* http://membres.lycos.fr/ylmb/source/solver.h
* http://membres.lycos.fr/ylmb/source/solver.cpp

Building and running
---------------------------------------------
I have compiled this with Visual Studio 2012. Since things has changed a bit with OpenGL  etc since 2005, I couldn't get the pixelbuffer code working. So there are no reflections over the water plane that I used to have in 2005. The pixlebuffer should be replaced by a OpenGL FrameBuffer anyway.

But it should just to be to open the solution file in Visual Studio 2012. But you will probably run into some problems with the paths because they are absolute at the moment. I'm going to make them relative, but it is late...