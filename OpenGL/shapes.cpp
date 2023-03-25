#include "shapes.h"
#include <iostream>
#include <vector>
#include "settings.h"
#include <algorithm>
#include "program.h"
#define TF(x) (float)x / 100

template<class T>
T* copyBasicPropreties(T* shape){
    T* new_shape = new T();
    new_shape->R = shape->R;
    new_shape->G = shape->G;
    new_shape->B = shape->B;
    new_shape->A = shape->A;
    new_shape->X = shape->X;
    new_shape->Y = shape->Y;
    new_shape->X_rotate = shape->X_rotate;
    new_shape->Y_rotate = shape->Y_rotate;
    new_shape->Z_rotate = shape->Z_rotate;
    new_shape->Texture = shape->Texture;
    new_shape->Texture_colors = shape->Texture_colors;
    new_shape->Transform_from_middle = shape->Transform_from_middle;
    return new_shape;
};


Circle* copyShape(Circle* ptr)
{
    Circle* new_circle = copyBasicPropreties<Circle>(ptr);
    new_circle->X_size = ptr->X_size;
    new_circle->Y_size = ptr->Y_size;
    return new_circle;
}

Rectangle* copyShape(Rectangle* ptr)
{
    Rectangle* new_rectangle = copyBasicPropreties<Rectangle>(ptr);
    new_rectangle->X_size = ptr->X_size;
    new_rectangle->Y_size = ptr->Y_size;
    return new_rectangle;
}

Square* copyShape(Square* ptr)
{
    Square* new_square = copyBasicPropreties<Square>(ptr);
    new_square->Size = ptr->Size;
    return new_square;
}

Triangle* copyShape(Triangle* ptr)
{
    Triangle* new_triangle = copyBasicPropreties<Triangle>(ptr);
    new_triangle->Size = ptr->Size;
    new_triangle->triangle_coordinates = ptr->triangle_coordinates;
    return new_triangle;
}

Parallelogram* copyShape(Parallelogram* ptr)
{
    Parallelogram* new_parallelogram = copyBasicPropreties<Parallelogram>(ptr);
    new_parallelogram->Size = ptr->Size;
    new_parallelogram->parallelogram_Coordinates = ptr->parallelogram_Coordinates;
    return new_parallelogram;
}


Square::Square() :Size(100) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.9f, 1.0f, 0.0f,
      0.9f, 0.9f, 0.0f, 0.0f,
      0.9f, 1.0f, 0.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}



void Square::updateVertexBuffer()
{
    const int X_size = Size / 2;
    const int Y_size = Size / 2;
    float X_1 = X - X_size;
    float Y_1 = Y - Y_size;
    float X_2 = X + X_size;
    float Y_2 = Y + Y_size;

    if (!Transform_from_middle) {
        X_1 = X + Size;
        Y_1 = Y + Size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 1.0f, 1.0f,
      X_2, Y_1, 1.0f, 0.0f,
      X_1, Y_1 ,0.0f, 0.0f,
      X_1, Y_2, 0.0f, 1.0f,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
}

void Square::scale(int scaler) {
    Size *= scaler;
}


void Square::draw() 
{
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size
    ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture(); 

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}






Rectangle::Rectangle() : X_size(100) , Y_size(50) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.9f, 1.0f, 0.0f,
      0.9f, 0.9f, 0.0f, 0.0f,
      0.9f, 1.0f, 0.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}



void Rectangle::updateVertexBuffer()
{
    const int _X_size = X_size / 2;
    const int _Y_size = Y_size / 2;
    float X_1 = X - _X_size;
    float Y_1 = Y - _Y_size;
    float X_2 = X + _X_size;
    float Y_2 = Y + _Y_size;

    if (!Transform_from_middle) {
        X_1 = X + X_size;
        Y_1 = Y + Y_size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2, 1.0f, 1.0f,
      X_2, Y_1, 1.0f, 0.0f,
      X_1, Y_1 ,0.0f, 0.0f,
      X_1, Y_2, 0.0f, 1.0f
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
}


void Rectangle::scale(int scaler) {
    X_size *= scaler;
    Y_size *= scaler;
}

void Rectangle::draw()
{

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_X_size != X_size ||   
        prev_Y_size != Y_size
        ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}

void Rectangle::setSizes(int X, int Y)
{
    X_size = X;
    Y_size = Y;

}

void Rectangle::setSizes(int XY)
{
    X_size = XY;
    Y_size = XY;
}



Circle::Circle() : X_size(100) , Y_size(100) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.9f, 1.0f, 0.0f,
      0.9f, 0.9f, 0.0f, 0.0f,
      0.9f, 1.0f, 0.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_circle.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
}


void Circle::updateVertexBuffer()
{
    const int _X_size = X_size / 2;
    const int _Y_size = Y_size / 2;
    float X_1 = X - _X_size;
    float Y_1 = Y - _Y_size;
    float X_2 = X + _X_size;
    float Y_2 = Y + _Y_size;


    if (!Transform_from_middle) {
        X_1 = X + X_size;
        Y_1 = Y + Y_size;
        X_2 = X;
        Y_2 = Y;
    }

    float sqr_ver_buf[] =
    {
      X_2, Y_2,1.0f, 1.0f,
      X_2, Y_1,1.0f, 0.0f,
      X_1, Y_1,0.0f, 0.0f,
      X_1, Y_2,0.0f, 1.0f
    };

    if (Transform_from_middle) {
        setUniform2f("pos", X - _X_size, Y - _Y_size);
        setUniform2f("size", X_size, Y_size);
    }
    else {
        setUniform2f("pos", X, Y);
        setUniform2f("size", X_size, Y_size);
    }



    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_X_size = X_size;
    prev_Y_size = Y_size;
}

void Circle::scale(int scaler) {
    X_size *= scaler;
    Y_size *= scaler;
}


void Circle::draw()
{

    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_X_size != X_size ||
        prev_Y_size != Y_size
        ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}

void Circle::setSizes(int X, int Y)
{
    X_size = X;
    Y_size = Y;

}

void Circle::setSizes(int XY)
{
    X_size = XY;
    Y_size = XY;
}



Triangle::Triangle() : Size(100) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 3 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
    triangle_coordinates.top = { 50 ,100 };
    triangle_coordinates.bottom_left = { 0 ,0 };
    triangle_coordinates.bottom_right = { 100 , 0 };
}



void Triangle::updateVertexBuffer()
{
    int j = 0;
    for (const auto& member : { 
        triangle_coordinates.top.X,
        triangle_coordinates.top.Y,        
        triangle_coordinates.bottom_right.X,
        triangle_coordinates.bottom_right.Y,
        triangle_coordinates.bottom_left.X,
        triangle_coordinates.bottom_left.Y
        }) {
        shape_coordinate[j] = member;
        j++;
    };
    float coordinates[6];


    if (!Transform_from_middle) 
    {
        for (int i = 0; i < 6; i++) 
        {
            float coord = shape_coordinate[i] * TF(Size);
            (i % 2 ) ? coordinates[i] = coord + Y : coordinates[i] = coord + X;
        }
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            float coord = shape_coordinate[i] * TF(Size);
            (i % 2) ? coordinates[i] = (coord + Y) - Size / 2 : coordinates[i] = (coord + X) - Size / 2;
        }
    }

    float sqr_ver_buf[] =
    {
      coordinates[0], coordinates[1], TF(shape_coordinate[0]), TF(shape_coordinate[1]),
      coordinates[2], coordinates[3], TF(shape_coordinate[2]), TF(shape_coordinate[3]),
      coordinates[4], coordinates[5], TF(shape_coordinate[4]), TF(shape_coordinate[5])
    };


    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_triangle_coordinates = triangle_coordinates;
}

void Triangle::scale(int scaler) {
    Size *= scaler;
}


void Triangle::draw()
{
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size ||
        triangle_coordinates.top.X != prev_triangle_coordinates.top.X ||
        triangle_coordinates.top.Y != prev_triangle_coordinates.top.Y ||
        triangle_coordinates.bottom_right.X != prev_triangle_coordinates.bottom_right.X ||
        triangle_coordinates.bottom_right.Y != prev_triangle_coordinates.bottom_right.Y ||
        triangle_coordinates.bottom_left.X != prev_triangle_coordinates.bottom_left.X ||
        triangle_coordinates.bottom_left.Y != prev_triangle_coordinates.bottom_left.Y
    )updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}





Parallelogram::Parallelogram() : Size(100) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.9f, 1.0f, 0.0f,
      0.9f, 0.9f, 0.0f, 0.0f,
      0.9f, 1.0f, 0.0f, 1.0f,
    };


    unsigned int sqr_ind_buf[] = // has to be unsigned
    {
         0,1,2,
         2,3,0,
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
    setDynamicIndexBuffer(sqr_ind_buf, 6 * sizeof(unsigned int));
    setShader("F_square.shader", GL_FRAGMENT_SHADER);
    setShader("V_square.shader", GL_VERTEX_SHADER);


    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_Texture = Texture;
    Texture_colors = { 255 , 255 ,255 ,255 };
    parallelogram_Coordinates.top_left = { 0 ,100 };
    parallelogram_Coordinates.top_right = { 100 , 100 };
    parallelogram_Coordinates.bottom_right = { 100 , 0 };
    parallelogram_Coordinates.bottom_left = { 0 ,0 };

}


void Parallelogram::updateVertexBuffer()
{
    int j = 0;
    for (const auto& member : { parallelogram_Coordinates.top_left.X,parallelogram_Coordinates.top_left.Y,parallelogram_Coordinates.top_right.X,parallelogram_Coordinates.top_right.Y,parallelogram_Coordinates.bottom_right.X,parallelogram_Coordinates.bottom_right.Y,parallelogram_Coordinates.bottom_left.X , parallelogram_Coordinates.bottom_left.Y }) {
        shape_coordinate[j] = member;
        j++;
    };

    constexpr int coord_size = 8;
    float coordinates[coord_size];

    if (!Transform_from_middle)
    {
        for (int i = 0; i < coord_size; i++)
        {
            float coord = shape_coordinate[i] * TF(Size);
            (i % 2) ? coordinates[i] = coord + Y : coordinates[i] = coord + X;
        }
    }
    else
    {
        for (int i = 0; i < coord_size; i++)
        {
            float coord = shape_coordinate[i] * TF(Size);
            (i % 2) ? coordinates[i] = (coord + Y) - Size / 2 : coordinates[i] = (coord + X) - Size / 2;
        }
    }
    float sqr_ver_buf[] =
    {
      coordinates[0], coordinates[1], TF(shape_coordinate[0]), TF(shape_coordinate[1]),
      coordinates[2], coordinates[3], TF(shape_coordinate[2]), TF(shape_coordinate[3]),
      coordinates[4], coordinates[5], TF(shape_coordinate[4]), TF(shape_coordinate[5]),
      coordinates[6], coordinates[7], TF(shape_coordinate[6]), TF(shape_coordinate[7]),
    };

    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_triangle_coordinates = parallelogram_Coordinates;
}

void Parallelogram::scale(int scaler) {
    Size *= scaler;
}


void Parallelogram::draw()
{
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size ||
        parallelogram_Coordinates.top_left.X != prev_triangle_coordinates.top_left.X ||
        parallelogram_Coordinates.top_left.Y != prev_triangle_coordinates.top_left.Y ||
        parallelogram_Coordinates.top_right.X != prev_triangle_coordinates.top_right.X ||
        parallelogram_Coordinates.top_right.Y != prev_triangle_coordinates.top_right.Y ||
        parallelogram_Coordinates.bottom_right.X != prev_triangle_coordinates.bottom_right.X ||
        parallelogram_Coordinates.bottom_right.Y != prev_triangle_coordinates.bottom_right.Y ||
        parallelogram_Coordinates.bottom_left.X != prev_triangle_coordinates.bottom_left.X ||
        parallelogram_Coordinates.bottom_left.Y != prev_triangle_coordinates.bottom_left.Y
        )updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();

    updateColors();
    updateRotation();
    updateTextureColors();
    Object::draw();
}


/*
    float sqr_ver_buf[] =
    {
      1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.9f, 0.0f, 0.0f,
      0.9f, 0.9f, 1.0f, 0.0f,
      0.9f, 1.0f, 1.0f, 1.0f,
    };
*/