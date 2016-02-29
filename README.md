#Zengine


Eventually this will be a working engine. For now, it's more of an educational project for me, but I'm enjoying it a lot. Currently licensed under GNU PUBLIC LICENSE V3.


##Building with CMake and Ninja


This project is built with CMake, and all CMake files are stored in /build. In the build directory, run the command:

`cmake -GNinja`

To generate Ninja build files. To build and run, you can use the following command:

`ninja ; gnome-terminal -e ./../bin/ZengineServer & ./../bin/ZengineClient`

You may have to to create the bin directory inside the project root.

