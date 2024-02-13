# 2D-Game-Engine
Custom 2D Game Engine written with C++/SDL/OpenGL.

The renderer is written in OpenGL and supports instanced rendering, batching, frustum culling, and simple point lights (no shadows).

Features a home-made implementation of the Entity-Component-System pattern for creating and managing game objects. Game objects can be created/destroyed and have components added or removed from them at runtime, allowing for very flexible behavior.

Compiles for Linux using Make. To compile, clone the repo, mkdir src/obj, then run make. Make sure to have OpenGL and SDL2 installed, however your repo may package them.

When you compile and run ./engine, you'll be greeted with a demo window. The arrow keys/WASD will move your character, the P key will spawn planets that exert gravitational influence and light, the M key will spawn a companion to follow you, and the Spacebar will fire projectiles that are influenced by gravity. 
