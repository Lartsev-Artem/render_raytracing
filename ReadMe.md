# ray tracing
rendering images using sdl2, stl, stb and OpenCL libraries.

# control:
W,S,A,D,Z,X

error in converting spherical coordinates to Cartesian coordinates.
full rotation is possible only on one axis (WS or AD).

# Opportunities:

in the source code, you can change the computing core 
(processor (class render) or video card - (class render_cl))
as well as a mathematical model.

# warnigs:

no large-scale tests were conducted.
there may be problems with the cmake build.
(it is important that the *cl files are in the same directory as the exe file)
there are no checks for an incorrect command line.