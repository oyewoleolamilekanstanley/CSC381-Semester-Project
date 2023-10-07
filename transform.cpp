#include "transform.h"
#include <iostream>
#include <cmath>

Shape::Shape(size_t numPoints) {
    this->numberOfPoints = numPoints;
    this->points = new Point[numPoints];
    this->color = new float[3];
}
Shape::~Shape() {
    delete[] this->points;
    delete[] this->color;
}

Point& Shape::operator[](size_t index) {
    return this->points[index];
}

void Shape::setColor(float red, float green, float blue) {
    this->color[0] = red;
    this->color[1] = green;
    this->color[2] = blue;
}

void Shape::setPoint(size_t index, Point pointt) {
    (*(this))[index] = pointt;
}

size_t Shape::getNumberOfPoints(void) {
    return this->numberOfPoints;
}

const float *Shape::getColor() {
    return this->color;
}

void scaleShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();

    for (size_t i = 0; i < length; i++) {
        shape[i].x *= scale;
        shape[i].y *= scale;
    }
}

void translateShape(Shape& shape, Point& point) {
    size_t length = shape.getNumberOfPoints();

    for (size_t i = 0; i < length; i++) {
        shape[i].x += point.x;
        shape[i].y += point.y;
    }
}

void rotateShape(Shape& shape, float angle) {
    size_t length = shape.getNumberOfPoints();
    float x, y;

    for (size_t i = 0; i < length; i++) {
        x = shape[i].x;
        y = shape[i].y;

        shape[i].x = cos(angle) * x - sin(angle) * y;
        shape[i].y = sin(angle) * x + cos(angle) * y;
    }

}

void reflectShape(Shape& shape) {
    scaleShape(shape, -1.0f);
}

void horizontallyShearShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();

    // x1 = x + b * y

    for (size_t i = 0; i < length; i++) {
        shape[i].x = shape[i].x + scale * shape[i].y;
    }

}

void verticallyShearShape(Shape& shape, float scale) {
    size_t length = shape.getNumberOfPoints();
    // y1 = c * x + y

    for (size_t i = 0; i < length; i++) {
        shape[i].y = scale * shape[i].x + shape[i].y;
    }
}
