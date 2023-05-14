#include "shapes.h"
#include <iostream>
#include <vector>
#include "settings.h"
#include <algorithm>
#include <GLFW/glfw3.h>
#include <cstring>
#define TF(x) (float)x / 100
#define Resolve(i , size) ()
#define MAX_ASCII 128




void runEachS(int s_time, const std::function<void()>& func)
{
    static double prev_time = glfwGetTime();
    if (glfwGetTime() > prev_time + s_time)
    {
        func();
        prev_time = glfwGetTime();
    }
};


void runEachF(int frame_interval, const std::function<void()>& func)
{
    static int frames = 0;
    if (frames >= frame_interval)
    {
        func();
        frames = 0;
    }
    frames++;
};


bool windowSizeChanged(int update_width, int update_height)
{
    static int prev_width = width;
    static int prev_height = height;
    if ((prev_width != update_width) || (prev_height != update_height))
    {
        prev_height = update_height;
        prev_width = update_width;
        return true;
    }
    return false;

}

template<class T>
T* copyBasicPropreties(T* shape, int arg = -1){
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

Shape* copyShape(Shape* ptr)
{
    Shape* new_shape = copyBasicPropreties<Shape>(ptr);
    new_shape->Size = ptr->Size;
    new_shape->shape_Coordinates = ptr->shape_Coordinates;
    return new_shape;
}

Polytriangle* copyShape(Polytriangle* ptr)
{
    Polytriangle* new_polytriangle = copyBasicPropreties<Polytriangle>(ptr);
    new_polytriangle->Size = ptr->Size;
    new_polytriangle->shape_Coordinates = ptr->shape_Coordinates;
    return new_polytriangle;
}

Text* copyShape(Text* ptr)
{
    Text* new_text = new Text(ptr->render_size);
    new_text->R = ptr->R;
    new_text->G = ptr->G;
    new_text->B = ptr->B;
    new_text->A = ptr->A;
    new_text->X = ptr->X;
    new_text->Y = ptr->Y;
    new_text->X_rotate = ptr->X_rotate;
    new_text->Y_rotate = ptr->Y_rotate;
    new_text->Z_rotate = ptr->Z_rotate;
    new_text->Texture = ptr->Texture;
    new_text->Texture_colors = ptr->Texture_colors;
    // custom propreties:
    new_text->Transform_from_middle = ptr->Transform_from_middle;
    new_text->font_size = ptr->font_size;
    new_text->font_path = ptr->font_path;
    new_text->font_file = ptr->font_size;
    new_text->value = ptr->value;
    return new_text;
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
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
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
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
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

    scaleUp();

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

void Circle::scaleUp()
{
    const int _X_size = X_size / 2;
    const int _Y_size = Y_size / 2;
    if (Transform_from_middle) {
        setUniform2f("pos", (X - _X_size) * (update_width / width), (Y - _Y_size) * (update_height / height));
    }
    else {
        setUniform2f("pos", X * (update_width / width), Y * (update_height / height));
    }
    setUniform2f("size", X_size * (update_width / width), Y_size * (update_height / height));

}

void Circle::draw()
{
    if (scale_render_on_window_resize && windowSizeChanged(update_width , update_height)) scaleUp();
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_X_size != X_size ||
        prev_Y_size != Y_size
        ) updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
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
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
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
    glm::mat4 mvp = proj;
    setUniformMatrix4fv("mvp", mvp);

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
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
    Object::draw();
}


Shape::Shape() : Size(100) {

    Program::sub_objects.push_back(this);
    float sqr_ver_buf[4020];


    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
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


void Shape::updateVertexBuffer()
{
    std::vector<Coordinates> coordinates;

    if (!Transform_from_middle)
    {
        for (Coordinates coord : shape_Coordinates)
        {
            Coordinates final_coord = {
                { coord.X * TF(Size) + X },
                { coord.Y * TF(Size) + Y }
            };
            coordinates.emplace_back(final_coord);
        }
    }
    else
    {
        for (Coordinates coord : shape_Coordinates)
        {
            Coordinates final_coord = {
                { (coord.X * TF(Size) + X) - Size / 2 },
                { (coord.Y * TF(Size) + Y) - Size / 2 }
            };
            coordinates.emplace_back(final_coord);
        }
    };


    int size = coordinates.size() * 4;
    float* sqr_ver_buf = new float[size];
    for (int i = 0 ;i < size; i+=4)
    {
        int vector_index = i / 4;
        sqr_ver_buf[i] =   (float)coordinates[vector_index].X; 
        sqr_ver_buf[i+1] = (float)coordinates[vector_index].Y;
        sqr_ver_buf[i+2] = TF(shape_Coordinates[vector_index].X);
        sqr_ver_buf[i+3] = TF(shape_Coordinates[vector_index].Y);
    }

    elm_count = (size / 4) + 1;
    unsigned int* sqr_ind_buf = new unsigned int[elm_count];
    sqr_ind_buf[0] = 0;
    for (int i = 1; i < elm_count - 1; i++)
    {
        sqr_ind_buf[i] = i;
    }
    sqr_ind_buf[elm_count - 1] = 1;

    setDynamicIndexBuffer(sqr_ind_buf, (size / 4 + 1) * sizeof(unsigned int));
    setDynamicVertexBuffer(sqr_ver_buf, size * sizeof(float));

    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_shape_coordinates = shape_Coordinates;
    delete[] sqr_ver_buf;
    delete[] sqr_ind_buf;
}

void Shape::scale(int scaler) {
    Size *= scaler;
}

bool Shape::shapeCoordinatesChanged()
{
    for (int i = 0; i < shape_Coordinates.size(); i++)
    {
        if (shape_Coordinates[i].X != prev_shape_coordinates[i].X) return true;
        if (shape_Coordinates[i].Y != prev_shape_coordinates[i].Y) return true;
    }
    return false;
}


void Shape::draw()
{
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size || 
        shapeCoordinatesChanged()
    )
    updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
    Object::draw(GL_TRIANGLE_FAN);
};


Polytriangle::Polytriangle() : Size(100) {

    Program::sub_objects.push_back(this);

    float sqr_ver_buf[4020];
    setDynamicVertexBuffer(sqr_ver_buf, sizeof(sqr_ver_buf));
    setVertexBufferLayout(0, 2, sizeof(float) * 4);
    setVertexBufferLayout(1, 2, sizeof(float) * 4, sizeof(float) * 2);
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


void Polytriangle::updateVertexBuffer()
{
    std::vector<Triangle_Coordinates> coordinates;

    if (!Transform_from_middle)
    {
        for (const Triangle_Coordinates& triangle : shape_Coordinates)
        {
            Triangle_Coordinates final_coord
                = {
                    {
                        { triangle.top.X * TF(Size) + X},
                        { triangle.top.Y * TF(Size) + Y}
                    },
                    {
                        { triangle.bottom_right.X * TF(Size) + X },
                        { triangle.bottom_right.Y * TF(Size) + Y }
                    },
                    {
                        { triangle.bottom_left.X * TF(Size) + X },
                        { triangle.bottom_left.Y * TF(Size) + Y }
                    }
            };
            coordinates.emplace_back(final_coord);
        }
    }
    else
    {
        for (const Triangle_Coordinates& triangle : shape_Coordinates)
        {
            Triangle_Coordinates final_coord
            = {
                {
                    { (triangle.top.X * TF(Size) + X) - Size / 2 },
                    { (triangle.top.Y * TF(Size) + Y) - Size / 2 }
                },
                {
                    { (triangle.bottom_right.X * TF(Size) + X) - Size / 2 },
                    { (triangle.bottom_right.Y * TF(Size) + Y) - Size / 2 }
                },
                {
                    { (triangle.bottom_left.X * TF(Size) + X) - Size / 2 },
                    { (triangle.bottom_left.Y * TF(Size) + Y) - Size / 2 }
                }
            };
            coordinates.emplace_back(final_coord);
        }
    };

    int int_count = 12;
    int size = coordinates.size() * int_count;
    float* sqr_ver_buf = new float[size];
    for (int i = 0; i < size; i += int_count)
    {
        int vector_index = i / int_count;

        sqr_ver_buf[i] = (float)coordinates[vector_index].top.X;
        sqr_ver_buf[i + 1] = (float)coordinates[vector_index].top.Y;
        sqr_ver_buf[i + 2] = TF(shape_Coordinates[vector_index].top.X);
        sqr_ver_buf[i + 3] = TF(shape_Coordinates[vector_index].top.Y);
        sqr_ver_buf[i + 4] = (float)coordinates[vector_index].bottom_right.X;
        sqr_ver_buf[i + 5] = (float)coordinates[vector_index].bottom_right.Y;
        sqr_ver_buf[i + 6] = TF(shape_Coordinates[vector_index].bottom_right.X);
        sqr_ver_buf[i + 7] = TF(shape_Coordinates[vector_index].bottom_right.Y);
        sqr_ver_buf[i + 8] = (float)coordinates[vector_index].bottom_left.X;
        sqr_ver_buf[i + 9] = (float)coordinates[vector_index].bottom_left.Y;
        sqr_ver_buf[i + 10] = TF(shape_Coordinates[vector_index].bottom_left.X);
        sqr_ver_buf[i + 11] = TF(shape_Coordinates[vector_index].bottom_left.Y);
    }

    setDynamicVertexBuffer(sqr_ver_buf, size * sizeof(int));
    prev_X = X;
    prev_Y = Y;
    prev_Size = Size;
    prev_shape_coordinates = shape_Coordinates;
    delete[] sqr_ver_buf;
}

void Polytriangle::scale(int scaler) {
    Size *= scaler;
}

bool Polytriangle::shapeCoordinatesChanged()
{
    for (int i = 0; i < shape_Coordinates.size(); i++)
    {
        if(shape_Coordinates[i].top.X != prev_shape_coordinates[i].top.X) return true;
        if(shape_Coordinates[i].top.Y != prev_shape_coordinates[i].top.Y) return true;
        if(shape_Coordinates[i].bottom_right.X!= prev_shape_coordinates[i].bottom_right.X) return true;
        if (shape_Coordinates[i].bottom_right.Y!= prev_shape_coordinates[i].bottom_right.Y)return true;
        if (shape_Coordinates[i].bottom_left.X != prev_shape_coordinates[i].bottom_left.X) return true;
        if (shape_Coordinates[i].bottom_left.Y != prev_shape_coordinates[i].bottom_left.Y) return true;

    }
    return false;
}


void Polytriangle::draw()
{
    if (
        prev_X != X ||
        prev_Y != Y ||
        prev_Size != Size ||
        shapeCoordinatesChanged()
    )
    updateVertexBuffer();
    if (prev_Texture != Texture) updateTexture();
    if (colorChanged()) updateColors();
    if (rotationChanged()) updateRotation();
    if (textureColorsChanged()) updateTextureColors();
    drawFromVBO(shape_Coordinates.size() * 3);
}




Text::Text(int _render_size) : render_size(_render_size), Scale(1), font_file("arial.ttf"), font_path("C:/Windows/Fonts"), value("Hello, World!"), font_size(48)
{
    program_id = fs.getProgram();
    Program::sub_objects.push_back(this);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
    ft = FT_Library();
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    face = FT_Face();
    if (FT_New_Face(ft, std::string(font_path +"/"+ font_file).c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    int divide = 10;
    font_texture_size = (height + width) / divide;
    if (render_size != -1) font_texture_size = render_size;
    FT_Set_Pixel_Sizes(face, 0, font_texture_size);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction


    for (unsigned char c = 0; c < MAX_ASCII; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 projection = proj;
    glUniformMatrix4fv(glGetUniformLocation(fs.getProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Text::Text() : Text(-1) {} //calling the other constructor !

void Text::draw() 
{
    fs.bindProgram(); //s.Use(); 

    //if (rotationChanged()) 
    //{
    //    glm::mat4 mvp =
    //        glm::rotate(glm::mat4(1.0f), glm::radians((float)Z_rotate), glm::vec3(0.0f, 0.0f, 1.0f))
    //        * glm::rotate(glm::mat4(1.0f), glm::radians((float)Y_rotate), glm::vec3(0.0f, 1.0f, 0.0f))
    //        * glm::rotate(glm::mat4(1.0f), glm::radians((float)X_rotate), glm::vec3(1.0f, 0.0f, 0.0f))
    //        * proj;
    //
    //    glProgramUniformMatrix4fv(
    //        fs.getProgram(),
    //        glGetUniformLocation(fs.getProgram(), "projection"),
    //        1, GL_FALSE,
    //        &mvp[0][0]
    //    );
    //
    //    prev_rotation[0] = X_rotate;
    //    prev_rotation[1] = Y_rotate;
    //    prev_rotation[2] = Z_rotate;
    //};
    if (prev_Texture != Texture) 
    {
        if (Texture == "")
        {
            setUniform1b("has_texture", false);
        }
        else
        {
            setUniform1b("has_texture", true);
            setTexture(Texture, "c_texture", true , 1);
        }
        prev_Texture = Texture;
    };
    if (textureColorsChanged()) updateTextureColors();


    int x = X;
    // activate corresponding render state	
    glUniform4f(glGetUniformLocation(fs.getProgram(), "textColor"), (float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
            // make 140px = 1px                 // adding font size
    Scale = (1.0f / (float)font_texture_size) + ((float)font_size / (float)font_texture_size);
    std::string::const_iterator c;
    
    int total_width = 0;
    int total_height = 0;
    for (c = value.begin(); c != value.end(); c++) {

        Character ch = Characters[*c];
        if ((ch.Size.y * Scale) > total_height)total_height = ch.Size.y * Scale;
        total_width += ((ch.Advance >> 6) * Scale);
    }
    float mid_w = total_width / 2;
    float mid_h = total_height / 2;


    for (c = value.begin(); c != value.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * Scale;
        float ypos = Y - (ch.Size.y - ch.Bearing.y) * Scale;

        float w = ch.Size.x * Scale;
        float h = ch.Size.y * Scale;
        // update VBO for each character


        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f }, // haut gauche
            { xpos,     ypos,       0.0f, 1.0f }, // bas gauche
            { xpos + w, ypos,       1.0f, 1.0f }, // bas droite

            { xpos,     ypos + h,   0.0f, 0.0f }, // haut gauche
            { xpos + w, ypos,       1.0f, 1.0f }, // bas droite
            { xpos + w, ypos + h,   1.0f, 0.0f } // 
        };



        if (Transform_from_middle) 
        {
            vertices[0][0] = xpos - mid_w;
            vertices[0][1] = (ypos + h) - mid_h;
            vertices[0][2] = 0.0f;
            vertices[0][3] = 0.0f;
        
            vertices[1][0] = xpos - mid_w;
            vertices[1][1] = ypos - mid_h;
            vertices[1][2] = 0.0f;
            vertices[1][3] = 1.0f;
        
            vertices[2][0] = (xpos + w) - mid_w;
            vertices[2][1] = ypos - mid_h;
            vertices[2][2] = 1.0f;
            vertices[2][3] = 1.0f;
        
            vertices[3][0] = xpos - mid_w;
            vertices[3][1] = (ypos + h) - mid_h;
            vertices[3][2] = 0.0f;
            vertices[3][3] = 0.0f;
        
            vertices[4][0] = (xpos + w) - mid_w;
            vertices[4][1] = (ypos) - mid_h;
            vertices[4][2] = 1.0f;
            vertices[4][3] = 1.0f;
        
            vertices[5][0] = (xpos + w) - mid_w;
            vertices[5][1] = (ypos + h) - mid_h;
            vertices[5][2] = 1.0f;
            vertices[5][3] = 0.0f;
        }
        // render glyph texture over quad
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        if (Texture != "")
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture.texture_id);
        }
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * Scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::scale(int scaler) {
    font_size *= scaler;
}


Text::~Text()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
};

