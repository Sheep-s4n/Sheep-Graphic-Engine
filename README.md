![sheep graphic engine logo](https://i.ibb.co/31QC4pj/sheep-graphic-engine.png)

## Usage:

All code needs to be in the **render.cpp** file.<br>
**render.cpp:**
```
#include "program.h"
#include "shapes.h"
#include "settings.h"

// initialize the shapes pointer here 
void Program::onStartup()
{
    // before render starts
}
void Program::onUpdate()
{
    // on rendering
}
void Program::onFinish()
{
    // after render
} 
```
1. First you have to initialize the shapes as a pointer outside the methods so that it can be accessed by all the methods afterwards.<br>
For example for a square : 
``` 
Square* my_sqr; 
```
2. Then you have to call the constructor of the shape in ``void Program::onStartup()`` and change the properties that will not be changed anymore.
```
my_sqr = new Square();
my_sqr->setColors(50); // or (*my_sqr).setColors(50);
```
3. Now you can change a property of a shape each rendered frame in ``void Program::onUpdate()``
``` 
my_sqr->X += 1; // the square will move forward 
```
4. Finally you can run code at the end of the rendering in `` void Program::onFinish() `` (you don't need to free the memory allocated in the heap by the ``new`` keyword, the graphic engine contains a garbage collector)
``` 
std::cout << "Successfully rendered a square !" << std::endl; 
```

Settings are located in **settings.h** file, they can be read from **render.cpp**.<br>
**settings.h:**
```
#pragma once
constexpr float height = 700.0f; // render height
constexpr float width = 700.0f; // render width
constexpr float swap_interval = 0; // rate at which the window's contents are updated and displayed on the screen 
constexpr bool scale_render_on_window_resize = true; // resize the rendering when the window is enlarged
```

## Graphic engine current features:

### Shapes:
* Polytriangle
* Circle
* Rectangle
* Square
* Triangle
* Parallelogram
* Shape
* Text
### Shapes main propreties:
* R (red channel color) --> int
* G (green channel color) --> int
* B (blue channel color) --> int
* A (transparency) --> int
* X (position in the X axis) --> int
* Y (position in the Y axis) --> int
* X_rotate (rotation of the X axis) --> int
* Y_rotate (rotation of the Y axis) --> int
* Z_rotate (rotation of the Z axis) --> int
* Z_index (order in the layers) --> int
* Transform_from_middle (transformation made from the shape's center) --> bool
* Texture (texture path relative to the executable) --> std::string
* Texture_colors (color of the texture) --> Texture_colors {int, int, int, int}
### Shapes main methods:
* void removeTexture();
* void setColors(int RGB);
* void setColors(int R, int G, int B);
* void setColors(int R, int G, int B, int A);
* void setColorsTexture(int RGB);
* void setColorsTexture(int R, int G, int B);
* void setColorsTexture(int R, int G, int B, int A);
* void setPositions(int XY);
* void setPositions(int X, int Y);
* void setPositions(int X, int Y, int Z);
* void setRotation(int Z);
* void setRotations(int X, int Y, int Z);
### Functions:
* void runEachS(int s_time, const std::function<void()>& func); (execute a callback function each *s_time* seconds)
* void runEachF(int frame_interval, const std::function<void()>& func); (execute a callback function each *frame_interval* frames)
* void PositionMiddle(Object* shape); (positions the shape in the render middle)
* Object* copyShape(Object* shape); (deep copy the give shape)
* void copyShapePropreties(Object* shape, Object* target_shape); (copy the properties of the first shape in the second one)
* void copyShapeStyles(T1* shape, T2* target_shape); (copy the style of the first shape in the second one)
* void copyShapeTransformations(T1* shape, T2* target_shape); (copy the transformations of the first shape in the second one)
### Extra class: 
* Animator (change the texture of any shape)
    * void linkShape(Object* shape); (selects the shape on which the animator will be used)
    * void nextFrameF(int switch_interval); (changes texture each *switch_interval* rendered frames)
    * void nextFrameS(float switch_interval); (changes texture each *switch_interval* seconds)
    * void addFrame(std::string image_path); (adds textures for animation)
    * void addFrames(int count, ...); (add more than one texture at a time)
    * void removeFrame(std::string image_path); (remove textures for animation)
    * void restoreFrame(int _sloat); (restore removed textures for animation)
	* void nextFrameReverseOrderF(int switch_interval);
    * void nextFrameReverseOrderS(float switch_interval);
    * void removeFrame(int _sloat); 
* Program (manage the rendering)
    * void onStartup(); (executed before the start of the rendering);
    * void onUpdate(); (executed at each frame of the rendering)
    * void onFinish(); (executed on program closure)
### Global variables:
* fps (number of frames per second processed by the graphic engine)
* frame_count (image count since the last second elapsed)
* update_width (width after window resizing)
* update_height (height after window resizing)

> ### Current version : 1.1

