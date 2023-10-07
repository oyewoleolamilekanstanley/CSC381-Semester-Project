#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>
#include <ctime>

#include "transform.h"


#define WIDTH 750
#define HEIGHT 750

float rrand() {
    return (float) rand()/RAND_MAX;
}

void drawCube(Shape& shape);
void drawPolygon(Shape& shape);
void drawSphere(Shape& shape);

Shape *createPolygon(size_t points) {
    auto *polygon = new Shape(points);

    const float radius = 0.5f;

    for (int i = 0; i < points; i++) {
        float theta = 2.0f * (float)M_PI * float(i) / float(points); // Calculate angle for each vertex
        float x = radius * std::cos(theta);
        float y = radius * std::sin(theta);

        (*polygon)[i].x = x;
        (*polygon)[i].y = y;
    }

    polygon->setColor(rrand(), rrand(), rrand());
    polygon->setDrawHandler(drawPolygon);

    return polygon;
}

Shape *createCube() {
    auto *cube = new Shape(24);

    // Front face
    // Vertex Color (Red)
    cube->getPoint(0).color.setValues(1.0f, 0.0f, 0.0f);
    cube->getPoint(1).color.setValues(1.0f, 0.0f, 0.0f);
    cube->getPoint(2).color.setValues(1.0f, 0.0f, 0.0f);
    cube->getPoint(3).color.setValues(1.0f, 0.0f, 0.0f);

    cube->setPoint(0, -0.5f, -0.5f, 0.5f); // Bottom-left
    cube->setPoint(1, 0.5f, -0.5f, 0.5f);  // Bottom-right
    cube->setPoint(2, 0.5f, 0.5f, 0.5f);   // Top-right
    cube->setPoint(3, -0.5f, 0.5f, 0.5f);  // Top-left

    // Back face
    // Vertex Color (Blue)
    cube->getPoint(4).color.setValues(0.0f, 0.0f, 1.0f);
    cube->getPoint(5).color.setValues(0.0f, 0.0f, 1.0f);
    cube->getPoint(6).color.setValues(0.0f, 0.0f, 1.0f);
    cube->getPoint(7).color.setValues(0.0f, 0.0f, 1.0f);

    cube->setPoint(4, -0.5f, -0.5f, -0.5f); // Bottom-left
    cube->setPoint(5, 0.5f, -0.5f, -0.5f);  // Bottom-right
    cube->setPoint(6, 0.5f, 0.5f, -0.5f);   // Top-right
    cube->setPoint(7, -0.5f, 0.5f, -0.5f);  // Top-left

    // Left face
    // Vertex Color (Green)
    cube->getPoint(8).color.setValues(0.0f, 1.0f, 0.0f);
    cube->getPoint(9).color.setValues(0.0f, 1.0f, 0.0f);
    cube->getPoint(10).color.setValues(0.0f, 1.0f, 0.0f);
    cube->getPoint(11).color.setValues(0.0f, 1.0f, 0.0f);

    cube->setPoint(8, -0.5f, -0.5f, 0.5f);  // Bottom-front
    cube->setPoint(9, -0.5f, 0.5f, 0.5f);   // Top-front
    cube->setPoint(10, -0.5f, 0.5f, -0.5f);  // Top-back
    cube->setPoint(11, -0.5f, -0.5f, -0.5f); // Bottom-back

    // Right face
    // Vertex Color (Yellow)
    cube->getPoint(12).color.setValues(1.0f, 1.0f, 0.0f);
    cube->getPoint(13).color.setValues(1.0f, 1.0f, 0.0f);
    cube->getPoint(14).color.setValues(1.0f, 1.0f, 0.0f);
    cube->getPoint(15).color.setValues(1.0f, 1.0f, 0.0f);

    // Vertex Position
    cube->setPoint(12, 0.5f, -0.5f, 0.5f);  // Bottom-front
    cube->setPoint(13, 0.5f, 0.5f, 0.5f);   // Top-front
    cube->setPoint(14, 0.5f, 0.5f, -0.5f);  // Top-back
    cube->setPoint(15, 0.5f, -0.5f, -0.5f); // Bottom-back

    // Top face
    // Vertex Color (Magenta)
    cube->getPoint(16).color.setValues(1.0f, 0.0f, 1.0f);
    cube->getPoint(17).color.setValues(1.0f, 0.0f, 1.0f);
    cube->getPoint(18).color.setValues(1.0f, 0.0f, 1.0f);
    cube->getPoint(19).color.setValues(1.0f, 0.0f, 1.0f);

    cube->setPoint(16, -0.5f, 0.5f, 0.5f);  // Front-left
    cube->setPoint(17, 0.5f, 0.5f, 0.5f);   // Front-right
    cube->setPoint(18, 0.5f, 0.5f, -0.5f);  // Back-right
    cube->setPoint(19, -0.5f, 0.5f, -0.5f); // Back-left

    // Bottom face
    // Vertex Color (Cyan)
    cube->getPoint(20).color.setValues(0.0f, 1.0f, 1.0f);
    cube->getPoint(21).color.setValues(0.0f, 1.0f, 1.0f);
    cube->getPoint(22).color.setValues(0.0f, 1.0f, 1.0f);
    cube->getPoint(23).color.setValues(0.0f, 1.0f, 1.0f);

    cube->setPoint(20, -0.5f, -0.5f, 0.5f);  // Front-left
    cube->setPoint(21, 0.5f, -0.5f, 0.5f);   // Front-right
    cube->setPoint(22, 0.5f, -0.5f, -0.5f);  // Back-right
    cube->setPoint(23, -0.5f, -0.5f, -0.5f); // Back-left

    cube->setDrawHandler(drawCube);

    return cube;
}

Shape *createSphere() {

    const int stacks = 5;
    const int slices = 5;
    const float radius = 1.0f;

    size_t vertices = (stacks + 1) * (slices + 1);

    auto *sphere = new Shape(vertices);

    size_t shapeVertexIndex = 0;

    for (int stack = 0; stack < stacks; stack++) {
        double theta1 = static_cast<double>(stack) * M_PI / stacks;
        double theta2 = static_cast<double>(stack + 1) * M_PI / stacks;

        for (int slice = 0; slice <= slices; slice++) {
            float phi = slice * 2.0f * (float)M_PI / slices;

            float x1 = radius * sin(theta1) * cos(phi);
            float y1 = radius * sin(theta1) * sin(phi);
            float z1 = radius * cos(theta1);

            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * sin(theta2) * sin(phi);
            float z2 = radius * cos(theta2);

            sphere->setPoint(shapeVertexIndex++, x1, y1, z1);
            sphere->setPoint(shapeVertexIndex++, x2, y2, z2);
        }
    }
    sphere->setDrawHandler(drawSphere);
    return sphere;
}

void windowResize(GLFWwindow *window, int width, int height) {

    // 800*(x+4)/8, 600*(3-y)/6
    // width * (x + 4) / 8, heigth * (3 - y) / 6
    glViewport(0, 0, width, height);
}

void drawPolygon(Shape& shape)
{
    size_t points = shape.getNumberOfPoints();

    if (points < 1) {
        return;
    }

    const float *color = shape.getColor();

    glColor3f(color[0], color[1], color[2]);

    /* Draw a Polygon */
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < points; i++)
    {
        glVertex2f(shape[i].x, shape[i].y);
    }
    glEnd();
}

void drawCube(Shape& shape) {
    size_t points = shape.getNumberOfPoints();

    if (points < 3) {
        return;
    }

    const float *color = shape.getColor();

    /* Draw a Polygon */
    glBegin(GL_QUADS);
    for (size_t i = 0; i < points; i++)
    {
        glColor3f(shape[i].color.red, shape[i].color.green, shape[i].color.blue);
        glVertex3f(shape[i].x, shape[i].y, shape[i].z);
    }
    glEnd();
}

void drawSphere(Shape& shape) {
    size_t points = shape.getNumberOfPoints();

    if (points < 3) {
        return;
    }

    const float *color = shape.getColor();

    /* Draw a Sphere */
    glBegin(GL_TRIANGLE_STRIP);
    for (size_t i = 0; i < points; i++)
    {
//        glColor3f(shape[i].color.red, shape[i].color.green, shape[i].color.blue);
        glVertex3f(shape[i].x, shape[i].y, shape[i].z);
    }
    glEnd();
}

void drawShapes(const std::vector<Shape *>&shapes)
{
    if (shapes.empty())
        return;

    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
//        handler(**it);
        (**it).getDrawHandler()(**it);
    }


//    for (auto & shape : shapes)
//    {
//        handler(*shape);
//    }
}

void deleteShapes(const std::vector<Shape *>&shapes)
{
    for (auto & shape : shapes)
    {
        delete shape;
    }
}

int main() {
    std::cout << "Hello Opengl" << std::endl;

    GLFWwindow *window;

    if (!glfwInit()) {
        std::cerr << "Error Initializing GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    window = glfwCreateWindow(
            WIDTH,
            HEIGHT,
            "2D Transformation - CSC 381 Project",
            nullptr, nullptr
    );

    if (!window) {
        std::cerr << "Error Creating Window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, WIDTH, HEIGHT);

    srand( (unsigned)time( nullptr ) );

    Shape *cube = createCube();

    float rate = 0.0002;

    std::vector<Shape *> polygonsOnScreen;

    Shape *currentShape = cube;
    polygonsOnScreen.push_back(cube);
    size_t currentIndex = 0;


    float lastpress = 0;
    float frameCount = 0;


    std::unordered_map< int, int > polygonKeyMap;
    polygonKeyMap.insert({GLFW_KEY_3, 3});
    polygonKeyMap.insert({GLFW_KEY_4, 4});
    polygonKeyMap.insert({GLFW_KEY_5, 5});
    polygonKeyMap.insert({GLFW_KEY_6, 6});
    polygonKeyMap.insert({GLFW_KEY_7, 7});
    polygonKeyMap.insert({GLFW_KEY_8, 8});
    polygonKeyMap.insert({GLFW_KEY_9, 9});
    polygonKeyMap.insert({GLFW_KEY_0, 10});
    polygonKeyMap.insert({GLFW_KEY_C, 50});

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);



    while (!glfwWindowShouldClose(window)) {
        frameCount += 0.001;

        glfwSetFramebufferSizeCallback(window, windowResize);
        glClearColor(0.1f, 0.5f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawShapes(polygonsOnScreen);

        // Spawn Shapes
        for (const auto& pair : polygonKeyMap) {
            if (glfwGetKey(window, pair.first)) {
                if ((frameCount - lastpress) > 0.10)
                {
                    // Create Polygon
                    Shape * t = createPolygon(pair.second);
                    polygonsOnScreen.push_back(t);
                    lastpress = frameCount;
                    currentIndex = polygonsOnScreen.size() - 1;
                    currentShape = polygonsOnScreen.back();
                }
            }
        }

        // Delete currently selected shape
        if (glfwGetKey(window, GLFW_KEY_DELETE) && !polygonsOnScreen.empty()) {
            if ((frameCount - lastpress) > 0.10)
            {
                polygonsOnScreen.erase(polygonsOnScreen.begin() + (long)currentIndex);

                if (polygonsOnScreen.empty()) {
                    currentShape = nullptr;
                } else {
                    if (currentIndex >= polygonsOnScreen.size()) {
                        currentIndex = polygonsOnScreen.size() - 1;
                    }
                    currentShape = polygonsOnScreen[currentIndex];
                }

                lastpress = frameCount;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        {
            if ((frameCount - lastpress) > 0.10 && (currentIndex < polygonsOnScreen.size() - 1))
            {
                // Select next shape on screen
                currentIndex++;
                currentShape = polygonsOnScreen[currentIndex];
                lastpress = frameCount;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            if ((frameCount - lastpress) > 0.10 && (currentIndex > 0))
            {
                // Select previous shape on screen
                currentIndex--;
                currentShape = polygonsOnScreen[currentIndex];
                lastpress = frameCount;
            }
        }

        // Transformations
        if (currentShape != nullptr) {
            int moveUp = glfwGetKey(window, GLFW_KEY_W); // Moving Shape Up
            if (moveUp == GLFW_PRESS) {
                Point p = {0.0f, rate};
                translateShape(*currentShape, p);
            }

            int moveDown = glfwGetKey(window, GLFW_KEY_S);
            if (moveDown == GLFW_PRESS) {
                Point p = {0.0f, -rate};
                translateShape(*currentShape, p);
            }

            int moveLeft = glfwGetKey(window, GLFW_KEY_A);
            if (moveLeft == GLFW_PRESS) {
                Point p = {-rate, 0.0f};
                translateShape(*currentShape, p);
            }

            int moveRight = glfwGetKey(window, GLFW_KEY_D);
            if (moveRight == GLFW_PRESS) {
                Point p = {rate, 0.0f};
                translateShape(*currentShape, p);
            }

            int changeRate = glfwGetKey(window, GLFW_KEY_E);
            if (changeRate == GLFW_PRESS) {
                rate *= 1.05;
            }

            changeRate = glfwGetKey(window, GLFW_KEY_Q);
            if (changeRate == GLFW_PRESS) {
                rate /= 1.05;
            }

            int scaleUP = glfwGetKey(window, GLFW_KEY_UP);
            if (scaleUP == GLFW_PRESS) {
                verticallyShearShape(*currentShape, rate);
            }

            int scaleDOWN = glfwGetKey(window, GLFW_KEY_DOWN);
            if (scaleDOWN == GLFW_PRESS) {
                verticallyShearShape(*currentShape, -rate);
            }


            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                horizontallyShearShape(*currentShape, rate);
            }


            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                horizontallyShearShape(*currentShape, -rate);
            }


            if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
                scaleShape(*currentShape, 1 + rate);
            }


            if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
                scaleShape(*currentShape, 1 - rate);
            }

            if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
                rotateShape(*currentShape, rate);
            }

            if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
                rotateShape(*currentShape, -rate);
            }

            if (glfwGetKey(window, GLFW_KEY_X) && !glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
                rotateShapeX(*currentShape, rate);
            }

            if (glfwGetKey(window, GLFW_KEY_X) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
                rotateShapeX(*currentShape, -rate);
            }

            if (glfwGetKey(window, GLFW_KEY_Y) && !glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
                rotateShapeY(*currentShape, rate);
            }

            if (glfwGetKey(window, GLFW_KEY_Y) && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
                rotateShapeY(*currentShape, -rate);
            }

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
                if ((frameCount - lastpress) > 2) {
                    reflectShape(*currentShape);
                }
            }
        }


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    deleteShapes(polygonsOnScreen);


    glfwTerminate();

    return EXIT_SUCCESS;
}
