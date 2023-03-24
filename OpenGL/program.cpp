#include "program.h"
#include <algorithm>

bool compareObjectZ_index(Object* O1, Object* O2)
{
    return (O1->Z_index < O2->Z_index);
}


void Program::renderShapes()
{

    std::sort(Program::sub_objects.begin(), Program::sub_objects.end(), compareObjectZ_index);
    for (Object* obj : Program::sub_objects) {
        obj->draw(); // draw object
    }
}


void Program::clearObjects()
{
    for (Object* obj : Program::sub_objects) {
        delete obj;
    }
};







