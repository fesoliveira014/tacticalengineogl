# TODO - Updated on 08/09/15

+ Locate shared pointes in the code and substitute regular pointers for shared_ptr<Type>
+ ~~Add templates to logger class in order to expand upon the current functionalities in an ordely way~~
  * Current logger satisfactory for the time being, but *stream* structure kinda annoying
  * *Refactor?*
+ Next steps:
  * Renderer class
    - ~~Camera~~
    - ~~Mesh~~
    - ~~Model~~
      + Partialy done, need to polish.
      + Might scap since changing paradigm to volume rendering.
    - ~~Data Structures: **Octree**~~
      + ~~Work in progress~~
      + Will not implement now. Further on will implement as a SVO.
    - ~~Texture~~
    - ~~Shader~~
    - Light
    - Material (?)
    - Ray casting for picking
  * Input handling
    - ~~Who to deal with system integration: classes should share the input and handle events individually, but there were some issues when dealing with many classes sharing this on the first version~~
    - Integrate mouse and picking further on
  * Text on screen
    - This can be used in conjuction with the logger class
    - FreeType is a start point
    - Should be done sooner than later, maybe after I can start rendering simple geometry
    - Debug, debug, debug
  * Rendering optimization
    - Look for ways to use the data structures in order to optimze rendering
    - Occlusion culling, visibility check, frustrum culling
      + Working on it now, is present on the Volume Mesh Builder.
    - Hidden surface removal
    - Batch rendering
  *  **Volume Rendering** (Work in progress)
    -  Ray casting
    -  Find different ways to represent volume
    -  Particle volume?

## Some Concepts
These are not *TODO*, but some stuff I think will be important down the road.

* ~~Should look into the uses of octrees and how that can help with geometry merging~~
  - Will only do this with SVO
* ~~How to have as many few draw calls as possible?~~
  - Solved on new volume rendering (only six vbos in use);
* Look into voxel representation:
  - ~~Voxel data structures~~
  - Compressing voxels for file system storage
  - Online compression and desconpression of voxels
  - ~~Chunks~~
* Integration with bullet physics
  - Further down the road, when the primary graphics systems (listed above) are complete
  - How to make my code interface well with bullet physics library?
* Design considerations
  - When designing subsystems, what design pattern to use?
  - Identify classes that should be instanced only once and classes that would work well with factories, etc.
  - Modulartization: think ahead in order to prepare for code expansion
  - Need to study about managers and how to better use them on the engine

## Procedural Generation

* Read the procedural book (the one you printed)
* Read the Procedural Blog
* Finish the Automata course this week
* Start figuring the shape grammar
* Volume procedural generation
## AI

* Not important right now, should not be a concern for the close future
* Nevertheless, look into basic algorithms after the first primary systems are complete: A*, etc

## Other

* Sound might be a thing: OpenAL sounds interesting
* SDL seems to handle extra systems well, should look into it
* SMFL is another good platarform, but GLFW is good for now since the focus is graphics
* Create a code standart based on the [Google Style Guide](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
