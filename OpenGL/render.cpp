#include "program.h"
#include "shapes.h"
#include "settings.h"

Square* testing;
Square* lightning;
Rectangle* help;
Rectangle* a_square;
Circle* circle2;
Triangle* tri_1;
Triangle* tri_2;
Triangle* tri_3;
Parallelogram* testing_this_sh__;
Animator<Rectangle>* deja_vu;
Shape* python_is_not_an_IDE;
Polytriangle* hell;


void Program::onStartup()
{

    testing = new Square();
    testing->setColors(50);
    testing->Z_index = -2;
    testing->Size = (height > width ? height : width);
    testing->setPositions(350);

    lightning = new Square();
    lightning->Size = 300;
    lightning->A = 0;
    lightning->setPositions(350);
    lightning->Texture = "Lightning.png";
    lightning->setColorsTexture(0, 200, 200, 255);
    lightning->Texture_colors.A = 255;

    a_square = new Rectangle();
    a_square->setPositions(0, 0);
    a_square->setSizes(0, 25);
    a_square->setColors(255, 255, 255, 100);
    a_square->Transform_from_middle = false;


    circle2 = new Circle();
    circle2->Z_index = -2;
    circle2->setSizes(300);
    circle2->setPositions(350, 350);
    circle2->setColors(0, 200, 200, 150);


    tri_1 = new Triangle();
    tri_1->setPositions(300 , 600);
    tri_1->setColors(236 , 179 , 1 ,255);
    tri_1->triangle_coordinates.top.Y = 70;
    tri_1->Transform_from_middle = false;

    tri_2 = copyShape(tri_1);
    tri_2->X -= 50;
    tri_2->Y -= 70;

    tri_3 = copyShape(tri_2);
    tri_3->X += 100;

    hell = new Polytriangle();
    hell->Size *= 2;
    hell->setPositions(350);
    hell->shape_Coordinates[0].bottom_left.X = 20;
    hell->shape_Coordinates.push_back(
        { {0, 50} ,{0, 0} , { 10 ,0 } }
    );
    hell->A = 200;
    hell->setColors(255, 0, 0);
    hell->Texture_colors.A = 0;

    help = new Rectangle();
    help->setPositions(350);
    help->A = 0;
    help->X_size = 700;
    help->Y_size = 300;
    
    deja_vu = new Animator<Rectangle>(help);
    deja_vu->addFrames(6, "anim1.png", "anim2.png", "anim3.png", "anim4.png" , "anim5.png" , "anim6.png");

    python_is_not_an_IDE = new Shape();
    python_is_not_an_IDE->Transform_from_middle = false;
}

void Program::onUpdate()
{
    lightning->setRotations(0, lightning->Y_rotate + 1, 0);
    help->Texture_colors.G -= 1;
    a_square->X_size += 3;
    if (a_square->X_size > width) a_square->X_size = 0;
    deja_vu->nextFrame(40); 
}

void Program::onFinish()
{
    std::cout << "ending..." << std::endl;
}