#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#define ENDER_3_PRO 235, 235, 250

using namespace std;

namespace gen{


    void printer(double printAreaX, double printAreaY, double printAreaZ, int setHeadTemp, int setBedTemp, string fileName);

    double maxHeight();
    void coutObjects();

    void shape(int shape, double width, double length, double height, int xLocation, int yLocation);
    void deleteObject(int objectToDelete);

    void generateCode();

    extern int counter;
    extern int layer;
    extern int speed;
    extern bool fillDirection;

    extern double xMax;
    extern double yMax;
    extern double zMax;
    extern double headTemp;
    extern double bedTemp;
    extern string fileName;

    extern double lineWidth;
    extern double layerHeight;
    extern double infillPercent;
    extern double retraction;
    extern int wallLineCount;
    extern int bottomLayers;
    extern int topLayers;
    extern int infillSpeed;
    extern int innerWallSpeed;
    extern int outerWallSpeed;
    extern int solidFillSpeed;
    extern int topSpeed;

    extern double e;
    extern double f;
    extern double x;
    extern double y;
    extern double z;
    extern double oldF;
    extern double oldX;
    extern double oldY;
    extern double oldZ;

    void setup();
    void finish();
    void G0();
    void G1();
    void G0withRetraction();
    void G1circle(double radius, double xLocation, double yLocation);

    enum ShapeName : int8_t{
        emptyShape = -1, box, cylinder, polygon
    };

    class Shape{
        public:

            int objectNumber = 0;
            int shape = emptyShape;
            double width = 0;
            double length = 0;
            double height = 0;
            double xLocation = 0;
            double yLocation = 0;
            int totalLayers = 0;
            double xShiftDegrees = 0;
            double yShiftDegrees = 0;
            double topWidth;
            double topLength;
            int sides = 6; //default

            void shapeDims(int setShape, double setWidth, double setLength, double setHeight, double setxLocation, double setyLocation);
            void shiftDims(double setxShiftDegrees, double yShiftDegrees);
            void topLayerDims(double setTopWidth, double setTopLength = -1);

            void boxLayer();
            void cylinderLayer();
            void polygonLayer();

            void wall();
            void solidFill();
            void cubicInfill();
            void shiftedInfill();

            void circleWall();
            void circleSolidFill();
            void circleInfill();

            void polygonWall();
            void polygonSolidFill();
            void polygonInfill();

        private:
            double _xCorner;
            double _yCorner;
            double _widthLayer;
            double _lengthLayer;

            double _xLocationLayer;
            double _yLocationLayer;
            double _xCornerLayer;
            double _yCornerLayer;
            double _xShift = 0;
            double _yShift = 0;
    };

    extern vector<Shape> shapeObject;
};

#endif // GENERATOR_H

