# XVolatile

## Getting Started

`GLEW` : The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library. GLEW provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.
https://glew.sourceforge.net/

`GLFW` : an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
https://www.glfw.org/

To get started, a new c++ project was created in visual studio.
GLEW and GLFW were downloaded (pre-compiled binaries) and placed in the `ExternalLibs` directory.

These are the subsequent steps to take:

1. Open Solution Properties
2. Add the header files to include. In `C/C++ > General > Additional Include Directories` - added the following:
   - $(SolutionDir)/../ExternalLibs/glew-2.1.0/include
   - $(SolutionDir)/../ExternalLibs/glfw-3.3.8/include
3. Add the source files to include. In `Linker > General > Additional Library Directories` - added the following
   - $(SolutionDir)/../ExternalLibs/glew-2.1.0/lib/Release/x64
   - $(SolutionDir)/../ExternalLibs/glfw-3.3.8/lib-vc2022
4. Add the included libraries to the project dependencies, including the GLFW and GLEW library files, as well as the built in `opengl32` library. In `Linker > Input > Additional Dependencies` - added the following:
   - opengl32.lib;
   - glew32.lib;
   - glfw3.lib;
5. Copy the Dynamic Linking Library file `glew32.dll` from `ExternalLibs\glew-2.1.0\bin\Release\x64` to the root solution directory.

## Initializing the Window

The `XVolatile.cpp` file is the main entry point into the application, housing the `int main()` function, where the GLFW Window is created.
Initialization of the app and the window is a simple process, involving these following steps:

1. Setup GLFW window properties
   - Set OpenGL version to use (`GLFW_CONTEXT_VERSION_MAJOR` and `GLFW_CONTEXT_VERSION_MINOR`)
   - Disable older versions and prevent them from compiling `glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)`
   - Allow forward compatibility `glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);`
2. Create GLFW window
   - Create a `GLFWwindow` pointer using `glfwCreateWindow()`
   - Set Buffer Size information using `glfwGetFramebufferSize()`
   - Set up Context for GLEW to use, using `glfwMakeContextCurrent(mainWindow)`
   - Can also enable support of experimental features, via `glewExperimental = GLFW_TRUE;`
3. Create GLEW Context. Initialize context by verifying that `glewInit() == GLEW_OK`
4. Setup viewport Size, using `glViewport()`
5. Enter the main loop
   - Get and handle user events using `glfwPollEvents()`. This allows for automatically refreshing the window when it's resized, and collecting other event data
   - Clear the previous frame buffer using `glClear()`. This function accepts an argument, to be told specifically which resource to clear
   - Replace the previously drawn scene/frame, with the new and currently updated scene/frame - using `glfwSwapBuffers(mainWindow);`

## Rendering Pipeline Stages

Rendering is a multi-staged process in which a 3d scene (which is comprised of vector data, matrices, polygons and their coordinate data, shading, and more) has it's data sent to the GPU to be processed and rendered to the screen.
This process spans across 9 distinct stages, where 4 of these stages are reserved for Shading:

1. Vertex Specification
2. Vertex Shader (Programmable)
3. Tesselation Shader (Programmable)
4. Geometry Shader (Programmable)
5. Vertex Post-Processing
6. Primitive Assembly
7. Rasterization
8. Fragment(Pixel) Shader (Programmable)
9. Per-Sample Operations

Here is a more in-depth perspective at most of these stages:

1. Vertex Specification:
   - The process where vertex data is gathered
   - Uses `VAO`, `VBO`, and `Attribute Pointers`
     - `Vertex Array Objects` - Defines all the data values needed for each vertex (position, color, texture, normals, etc)
     - `Vertex Buffer Objects` - Defines the data itself
     - `Attribute Pointers` - Defines where and how shaders can access vertex data
2. Vertex Shader:
   - The process of applying position data FOR EACH vertex
   - Setup of this shader stage is mandatory. Even if you don't need anything from the vertex shader, it still needs to assign vertex data to `gl_Position`, as this data is necessary for later stages
   - Inputs to this shader consists of solely the Vertex Data itself
   - Outputs from this shader can be used in later shading stages
3. Tessellation Shader:
   - Sub-divides topology to allow greater detail, mostly coupled with a height-map
   - Can be used to dynamically add levels of detail based on distance from the camera
   - A relatively new addition to the OpenGL rendering pipeline (version 4.0)
4. Geometry Shader:
   - Handles group of vertices together
   - Can be used to create and manipulate primitive shapes
5. Vertex Post-Processing:
   - The process of committing to the vertex data and determining which vertices are redundant
   - `Transform Feedback` - The result of the Vertex and Geometry stages that were saved to buffers for later use. Mandatory only if the vertex Position data is updated each frame
   - `Clipping` - Conversion of units from `clip space` to `window space`. Additionally, any primitive that is not visible in the rendering space is being removed from rendering. as an optimization
6. Primitive Assembly:
   - Vertices are converted to a series of primitives
   - `Face Culling` - removes any backward-facing polygon from rendering (anti-normals)
7. Rasterization:
   - Converts primitives into "Fragments" - `Fragments` are the pieces of data for each pixel - obtained from the rasterization process
   - Fragment data is interpolated based on the relative position of each pixel
8. Pixel Shader:
   - The Fragment shader stage, is the process where each pixel is assigned an RGB value, according to the Fragment data
   - Is optional but it’s rare to not use it. Exceptions are cases where only depth or stencil data is required
   - Most important output is the color of the pixel that the fragment covers
9. Per-Sample Operations:
   - Series of tests run to see if the fragment should be drawn
   - Most important test: Depth test. Determines if something is in front of the point being drawn
   - `Color Blending` - can blend fragment color data with overlapping fragment color data (usually for transparency)
   - Fragment data written to currently bound FrameBuffer (usually the default buffer)
   - At this point usually a `Buffer Swap` is demanded - putting the newly drawn-to updated Frame-Buffer to the front
