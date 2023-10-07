
#ifndef CSC381_TRANSFORM_H
#define CSC381_TRANSFORM_H

#include <iostream>

struct Color {
    float red, green, blue;

    void setValues(float red, float green, float blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

};

class Point {
public:
    float x;
    float y;
    float z;
    Color color;

    Point():x(0.0f), y(0.0f), z(0.0f), color{1.0f, 1.0f, 1.0f} {

    }

    Point(float x_p, float y_p): x(x_p), y(y_p), z(0.0f), color{1.0f, 1.0f, 1.0f} {

    }

    Point(float x_p, float y_p, float z_p): x(x_p), y(y_p), z(z_p), color{1.0f, 1.0f, 1.0f} {

    }

    Point(float x_p, float y_p, float z_p, float r, float g, float b): x(x_p), y(y_p), z(z_p), color{r, g, b} {

    }


};

class Shape {
private:
    Point *points;
    float *color;
    size_t numberOfPoints;
    void (*drawHandler)(Shape&);

public:
    explicit Shape(size_t numPoints);
    ~Shape();
    void setColor(float red, float green, float blue);
    Point& getPoint(size_t index);
    void setPoint(size_t index, Point pointt);
    void setPoint(size_t index, float x, float y, float z);
    const float *getColor();
    void setDrawHandler(void (*handler)(Shape&));
    void (*getDrawHandler()) (Shape&);

    Point& operator[](size_t index);
    size_t getNumberOfPoints() const;
};

void scaleShape(Shape& shape, float scale);
void translateShape(Shape& shape, Point& point);
void rotateShape(Shape& shape, float angle);
void rotateShapeX(Shape& shape, float angle);
void rotateShapeY(Shape& shape, float angle);
void reflectShape(Shape& shape);
void verticallyShearShape(Shape& shape, float scale);
void horizontallyShearShape(Shape& shape, float scale);


#endif //CSC381_TRANSFORM_H
