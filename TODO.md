# TODO - Updated on 08/09/15

+ Locate shared pointes in the code and substitute regular pointers for shared_ptr<Type>
+ Add templates to logger class in order to expand upon the current functionalities in an ordely way
+ Next steps:
  * Renderer class
    - Camera
    - Mesh
    - Model
    - Data Structures: Octree
    - Texture
    - Shader
    - Light
    - Material (?)
    - Ray casting for picking
  * Input handling
    - Who to deal with system integration: classes should share the input and handle events individually, but there were some issues when dealing with many classes sharing this on the first version
    - Integrate mouse and picking further on
  * Text on screen
    - This can be used in conjuction with the logger class
    - FreeType is a start point
    - Should be done sooner than later, maybe after I can start rendering simple geometry
    - Debug, debug, debug
  * Rendering optimization
    - Look for ways to use the data structures in order to optimze rendering
    - Occlusion culling, visibility check, frustrum culling
    - Hidden surface removal
    - Batch rendering

## Some Concepts

* Should look into the uses of octrees and how that can help with geometry merging
* How to have as many few draw calls as possible?
* Look into voxel representation:
  - Voxel data structures
  - Compressing voxels for file system storage
  - Online compression and desconpression of voxels
  - Chunks
* Integration with bullet physics
  - Further down the road, when the primary graphics systems (listed above) are complete
  - How to make my code interface well with bullet physics library?
* Design considerations
  - When designing subsystems, what design pattern to use?
  - Identify classes that should be instanced only once and classes that would work well with factories, etc.
  - Modulartization: think ahead in order to prepare for code expansion

## Procedural Generation

* Read the procedural book (the one you printed)
* Read the Procedural Blog
* Finish the Automata course this week
* Start figuring the shape grammar

## AI

* Not important right now, should not be a concern for the close future
* Nevertheless, look into basic algorithms after the first primary systems are complete: A*, etc

## Other

* Sound might be a thing: OpenAL sounds interesting
* SDL seems to handle extra systems well, should look into it
* SMFL is another good platarform, but GLFW is good for now since the focus is graphics
* Create a code standart based on the (Google Style Guide)[https://google-styleguide.googlecode.com/svn/trunk/cppguide.html]
