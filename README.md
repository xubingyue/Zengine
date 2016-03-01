#Zengine


Eventually this will be a working engine. For now, it's more of an educational project for me, but I'm enjoying it a lot. Currently licensed under GNU PUBLIC LICENSE V3.


###Building with CMake and Ninja in Linux


This project is built with CMake and Ninja, and all build files are stored in /build. Create a /bin directory in your project root, and then in the build directory, run the commands:

`cmake -GNinja`

`ninja`

Make sure that Ninja is in your PATH.

A .sublime-build file is stored in /sublime for a build command specific to sublime.

