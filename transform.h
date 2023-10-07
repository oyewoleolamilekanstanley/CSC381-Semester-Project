
#ifndef CSC381_TRANSFORM_H
#define CSC381_TRANSFORM_H

#include <iostream>


class Point {
public:
    float x;
    float y;

    Point():x(0.0f), y(0.0f){

    }

    Point(float x_p, float y_p): x(x_p), y(y_p) {

    }
};

class Shape {
private:
    Point *points;
    float *color;
    size_t numberOfPoints;

public:
    explicit Shape(size_t numPoints);
    ~Shape();
    void setColor(float red, float green, float blue);
    void setPoint(size_t index, Point pointt);
    const float *getColor();

    Point& operator[](size_t index);
    size_t getNumberOfPoints();
};

void scaleShape(Shape& shape, float scale);
void translateShape(Shape& shape, Point& point);
void rotateShape(Shape& shape, float angle);
void reflectShape(Shape& shape);
void verticallyShearShape(Shape& shape, float scale);
void horizontallyShearShape(Shape& shape, float scale);


#endif //CSC381_TRANSFORM_H
