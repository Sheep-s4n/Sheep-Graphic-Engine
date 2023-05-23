#pragma once
#include "object.h"
#include "texture.h"
#include <string>
#include <iostream>
#include <type_traits>
#include <functional>
#include "program.h"
#define Comment(x) /* x */
#define Auto 0x0

extern float update_height;
extern float update_width;
extern int fps;
extern int frame_count;

bool windowSizeChanged(int update_width, int update_height);

struct Coordinates 
{
	int X;
	int Y;
};

struct Parallelogram_Coordinates 
{
	Coordinates top_left;
	Coordinates top_right;
	Coordinates bottom_right;
	Coordinates bottom_left;
}; 

struct Triangle_Coordinates 
{
	Coordinates top;
	Coordinates bottom_left;
	Coordinates bottom_right;
};

struct Character {
	unsigned int textureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};


// extern keyword = tell compiler that the var is defined somewhere else*/

class Square : public Object {
private :
	void updateVertexBuffer();
	int prev_Size;
public:
	void draw();
	void scale(double scaler);
	Square();
	int Size;
};

class Circle : public Object {
private:
	void updateVertexBuffer();
	void scaleUp();
	int prev_X_size;
	int prev_Y_size;
public:
	void draw();
	void setSizes(int X, int Y);
	void setSizes(int XY);
	void scale(double scaler);
	Circle();
	int X_size;
	int Y_size;
};

class Rectangle : public Object {
private:
	void updateVertexBuffer();
	int prev_X_size;
	int prev_Y_size;
public:
	void draw();
	void setSizes(int X, int Y);
	void setSizes(int XY);
	void scale(double scaler);
	Rectangle();
	int X_size;
	int Y_size;
};

class Triangle : public Object {
private:
	void updateVertexBuffer();
	int prev_Size;
	int shape_coordinate[6];
	Triangle_Coordinates prev_triangle_coordinates;
public:
	void draw();
	void scale(double scaler);
	Triangle();
	int Size;
	Triangle_Coordinates triangle_coordinates;
};

class Parallelogram : public Object {
private:
	void updateVertexBuffer();
	int prev_Size;
	int shape_coordinate[8];
	Parallelogram_Coordinates prev_triangle_coordinates;
public:
	Parallelogram();
	void draw();
	void scale(double scaler);
	int Size;
	Parallelogram_Coordinates parallelogram_Coordinates;
};

class Shape : public Object {
private:
	void updateVertexBuffer();
	bool shapeCoordinatesChanged();
	int prev_Size;
	int elm_count;
	std::vector<Coordinates> prev_shape_coordinates = { {0, 0} ,{0, 0} , { 0 ,0 } , {0 ,0} , {0 ,0} };
public:
	Shape();
	void draw();
	void scale(double scaler);
	int Size;
	std::vector<Coordinates> shape_Coordinates = { {0, 0} ,{0, 70} , { 50 ,100 } , {100 ,70} , {100 ,0} };
};

class Polytriangle : public Object {
private:
	void updateVertexBuffer();
	bool shapeCoordinatesChanged();
	int prev_Size;
	std::vector<Triangle_Coordinates> prev_shape_coordinates;
public:
	Polytriangle();
	void draw();
	void scale(double scaler);
	int Size;
	std::vector<Triangle_Coordinates> shape_Coordinates = { 
		{{0, 100} ,{0, 0} , { 100 ,0 }} , {{0 ,100} , {100 ,100} , {100 ,0}}
	};
};

class Text : public Object {
private:
	FT_Face face;
	FT_Library ft;
	Shader fs = Shader("F_text.shader", GL_FRAGMENT_SHADER);
	Shader vs = Shader("V_text.shader", GL_VERTEX_SHADER, fs.getProgram());
	std::map<char, Character> Characters;
	unsigned int VAO;
	unsigned int VBO;
	int font_texture_size;
	float Scale;
	int prev_Render_size;
	std::string prev_Font_file;
	std::string prev_Font_path;
	void loadChar();
public:
	void draw();
	void scale(double scaler);
	Text();
	Text(int render_size);
	~Text();
	int Font_size;
	int Render_size;
	std::string Value;
	std::string Font_file;
	std::string Font_path;
	int Texture_repeat;
};

void runEachS(double time_inteval, const std::function<void()>& func);
void runEachF(int frame_interval, const std::function<void()>& func);


Circle* copyShape(Circle* ptr);
Rectangle* copyShape(Rectangle* ptr);
Square* copyShape(Square* ptr);
Triangle* copyShape(Triangle* ptr);
Parallelogram* copyShape(Parallelogram* ptr);
Shape* copyShape(Shape* ptr);
Polytriangle* copyShape(Polytriangle* ptr);
Text* copyShape(Text* ptr);

template<class T1>
void PositionMiddle(T1* shape);

//std::void_t = templated metafunction or type trait = evaluated at compile time
// function = called with "()"
// metafunction = called by instantiating template class
template<typename type, typename = void>
struct has_Size : std::false_type {};
// make a new class called : has_X_size , that inherits from std::false_type {} = give has_X_size::vaue a value of false

// using Substitution failure is not an error (SFINAE) to check if class has a member X_size
template<typename type>
struct has_Size<type, std::void_t<decltype(type::Size)>> : std::true_type {};
// std::void_t<decltype(T2::X_size)> = if T2 has X_size member expression is valid and the struct value is true
// else the value returned is void an the first template is used to construct the return struct


Comment(std::cout << has_X_size<T2>::value << std::endl;)
/* use overload resolution to determine which version
of has_X_size to instantiate. If T2 has a static member
called X_size, then the compiler will select the second
template because it is a more specialized version of the primary
template. In that case, has_X_size<T2>::value will be true because
has_X_size<T2, std::void_t<decltype(T2::X_size)>> inherits
from std::true_type. If T2 does not have a static member
called X_size, then the compiler will select the primary
template, and has_X_size<T2>::value will be false because
has_X_size<T2> inherits from std::false_type.
 -- thanks chatGPT =)
*/



template<class T1, class T2>
void copyShapePropreties(T1* shape, T2* target_shape) {
	target_shape->R = shape->R;
	target_shape->G = shape->G;
	target_shape->B = shape->B;
	target_shape->A = shape->A;
	target_shape->X = shape->X;
	target_shape->Y = shape->Y;
	target_shape->X_rotate = shape->X_rotate;
	target_shape->Y_rotate = shape->Y_rotate;
	target_shape->Z_rotate = shape->Z_rotate;
	target_shape->Texture = shape->Texture;
	target_shape->Texture_colors = shape->Texture_colors;
	target_shape->Transform_from_middle = shape->Transform_from_middle;


	if constexpr (std::is_same<T1 , Text>::value || std::is_same<T2, Text>::value)
	{
		std::cout << "not implemented for text" << std::endl;
	}
	else 
	{
		// evaluate expression at compile-time using so it only keeps the correct piece of code
		if constexpr (has_Size<T1>::value && has_Size<T2>::value)
		{
			target_shape->Size = shape->Size;
		}
		else if constexpr (has_Size<T1>::value)
		{
			target_shape->X_size = shape->Size;
			target_shape->Y_size = shape->Size;
		}
		else if constexpr (has_Size<T2>::value)
		{
			target_shape->Size = shape->X_size;
		}
		else 
		{
			target_shape->X_size = shape->X_size;
			target_shape->Y_size = shape->Y_size;
		}
	}

}


template<class T1, class T2>
void copyShapeStyles(T1* shape, T2* target_shape) {
	target_shape->R = shape->R;
	target_shape->G = shape->G;
	target_shape->B = shape->B;
	target_shape->A = shape->A;
	target_shape->Texture = shape->Texture;
	target_shape->Texture_colors = shape->Texture_colors;
};

template<class T1, class T2>
void copyShapeTransformations(T1* shape, T2* target_shape) {
	target_shape->X = shape->X;
	target_shape->Y = shape->Y;
	target_shape->X_rotate = shape->X_rotate;
	target_shape->Y_rotate = shape->Y_rotate;
	target_shape->Z_rotate = shape->Z_rotate;
	target_shape->Transform_from_middle = shape->Transform_from_middle;

	if constexpr (std::is_same<T1, Text>::value || std::is_same<T2, Text>::value)
	{
		std::cout << "not implemented for text" << std::endl;
	}
	else
	{
		// evaluate expression at compile-time using so it only keeps the correct piece of code
		if constexpr (has_Size<T1>::value && has_Size<T2>::value)
		{
			target_shape->Size = shape->Size;
		}
		else if constexpr (has_Size<T1>::value)
		{
			target_shape->X_size = shape->Size;
			target_shape->Y_size = shape->Size;
		}
		else if constexpr (has_Size<T2>::value)
		{
			target_shape->Size = shape->X_size;
		}
		else
		{
			target_shape->X_size = shape->X_size;
			target_shape->Y_size = shape->Y_size;
		}
	}
};




// todo :
// text rotation
// text = reduce functions calls
// call updateBuffer for square , rectangle , circle when Transform_midlle changed