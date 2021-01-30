# OpenGLRenderer

Hello and welcome to my OpenGL Renderer project.

To get started:

  1. Ensure that when you clone this project you use the following submodule command to clone all necessary dependencies
      1. `git clone --recurse-submodules https://github.com/nhoughto5/OpenGLRenderer.git`
  2. This project uses premake to auto-generate a visual studio solution file. There is a batch script `GenerateProjects.bat` in the root folder that will run the necessary process to build the solution
  3. Assets are stored in git in their original format. (ex .obj) The renderer uses its own binary format for optimized loading. The generated files are not checked in and must be made. There are two options:
     1. Open the `assetBuild` folder and run the OBJConverter.exe file.
     2. Open the VSStudio solution and set OBJConverter as the startup project (right click the project, hit "set as startup"). Then press play in visual studio
  4. Ensure the OpenGLRenderer project is the startup project and then press play. 
  
That should be it!
