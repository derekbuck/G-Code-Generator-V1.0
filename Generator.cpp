#include "Generator.h"

using namespace std;

ofstream fout;

vector <gen::Shape> gen::shapeObject;

int gen::counter = 0;
int gen::layer = 1;
int gen::speed;
bool gen::fillDirection = 0;

double gen::xMax;
double gen::yMax;
double gen::zMax;
double gen::headTemp;
double gen::bedTemp;
string gen::fileName;

double gen::lineWidth = .4;
double gen::layerHeight = .2;
double gen::infillPercent = .2;
double gen::retraction = 6;
int gen::wallLineCount = 3;
int gen::bottomLayers = 4;
int gen::topLayers = 4;
int gen::infillSpeed = 40;
int gen::innerWallSpeed = 40;
int gen::outerWallSpeed = 25;
int gen::solidFillSpeed = 40;
int gen::topSpeed = 25;

double gen::e = 0;
double gen::f = 0;
double gen::x = 0;
double gen::y = 0;
double gen::z = 0;
double gen::oldF = 0;
double gen::oldX = 0;
double gen::oldY = 0;
double gen::oldZ = 0;

void gen::printer(double printAreaX, double printAreaY, double printAreaZ, int setHeadTemp, int setBedTemp, string setFileName){


    xMax = printAreaX;
    yMax = printAreaY;
    zMax = printAreaZ;
    headTemp = setHeadTemp;
    bedTemp = setBedTemp;
    fileName = setFileName;

    fout.open(fileName + ".gcode");

}

void gen::setup(){

    fout << "; " << fileName << " GCode" << endl;
    fout << "; Objects To Be Printed: " << shapeObject.size() << endl;
    fout << "; Print Bed Dimensions: " << xMax << " x " << yMax << " x " << zMax << endl;
    fout << "; Extruder Temp: " << headTemp << " Degrees Celcius" << endl;
    fout << "; Bed Temp: " << bedTemp << " Degrees Celcius" << endl;
    fout << "; Layer Height = " << layerHeight << " mm" << endl;
    fout << "; Line Width = " << lineWidth << " mm" << endl;
    fout << "; Infill = " << infillPercent * 100 << "%" << endl;
    fout << "; Retraction Distance = " << retraction << " mm" << endl;
    fout << "; Wall Line Count = " << wallLineCount << endl;
    fout << "; Bottom Layers = " << bottomLayers << endl;
    fout << "; Top Layers = " << topLayers << endl;
    fout << "; Infill Print Speed = " << infillSpeed << " mm/s" << endl;
    fout << "; Inner Wall Print Speed = " << innerWallSpeed << " mm/s" << endl;
    fout << "; Outer Wall Print Speed = " << outerWallSpeed << " mm/s" << endl;
    fout << "; Solid Fill Print Speed = " << solidFillSpeed << " mm/s" << endl;
    fout << "; Top Layer Print Speed = " << topSpeed << " mm/s" << endl;

    fout << "; --------------------------------------" << endl;

    fout << "; " << shapeObject.size() << " Total Objects" << endl << endl;
    for (int i = 0; i < shapeObject.size(); i++){
        if (shapeObject[i].shape != emptyShape){
            if (shapeObject[i].shape == box){
                fout << "; Object " << i + 1 << ": Box" << endl;
                fout << "; Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width || shapeObject[i].topLength != shapeObject[i].length)
                    fout << "; Top Width: " << shapeObject[i].topWidth << "mm, Top Length: " << shapeObject[i].topLength << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    fout << "; X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                fout << endl;
            }
            if (shapeObject[i].shape == cylinder){
                fout << "; Object " << i + 1 << ": Cylinder" << endl;
                fout << "; Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width)
                    fout << "; Top Diameter: " << shapeObject[i].topWidth << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    fout << "; X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                fout << endl;
            }
            if (shapeObject[i].shape == polygon){
                if (shapeObject[i].sides == 3) fout << "; Object " << i + 1 << ": Triangle" << endl;
                else if (shapeObject[i].sides == 4) fout << "; Object " << i + 1 << ": Diamond" << endl;
                else if (shapeObject[i].sides == 5) fout << "; Object " << i + 1 << ": Pentagon" << endl;
                else if (shapeObject[i].sides == 6) fout << "; Object " << i + 1 << ": Hexagon" << endl;
                else if (shapeObject[i].sides == 7) fout << "; Object " << i + 1 << ": Heptagon" << endl;
                else if (shapeObject[i].sides == 8) fout << "; Object " << i + 1 << ": Octagon" << endl;
                else if (shapeObject[i].sides == 9) fout << "; Object " << i + 1 << ": Nonagon" << endl;
                else if (shapeObject[i].sides == 10) fout << "; Object " << i + 1 << ": Decagon" << endl;
                else if (shapeObject[i].sides == 11) fout << "; Object " << i + 1 << ": Hendecagon" << endl;
                else if (shapeObject[i].sides == 12) fout << "; Object " << i + 1 << ": Dodecagon" << endl;
                else if (shapeObject[i].sides > 12) fout << "; Object " << i + 1 << ": " << shapeObject[i].sides << " sided Polygon" << endl;
                fout << "; Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                fout << "; Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width)
                    fout << "; Top Diameter: " << shapeObject[i].topWidth << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    fout << "; X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                fout << endl;
            }
        }
    }

    fout << "; --------------------------------------" << endl;

    //GCODE setup commands
    fout << "; Setup Commands" << endl;
    fout << "M140 S" << bedTemp << endl;
    fout << "M105" << endl;
    fout << "M104 S" << headTemp << endl;
    fout << "M105" << endl;
    fout << "M109 S" << headTemp << endl;
    fout << "M82 ; absolute extrusion mode" << endl;
    fout << "G92 E0 ; Reset Extruder" << endl;
    fout << "G28 ; Home all axes" << endl;
    fout << "G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed" << endl;
    fout << "G1 X0.1 Y10 Z0.3 F5000.0 ; Move to start position" << endl;
    fout << "G1 X0.1 Y190.0 Z0.3 F1500.0 E15 ; Draw the first line" << endl;
    fout << "G1 X0.4 Y190.0 Z0.3 F5000.0 ; Move to side a little" << endl;
    fout << "G1 X0.4 Y10 Z0.3 F1500.0 E30 ; Draw the second line" << endl;
    fout << "G92 E0 ; Reset Extruder" << endl;
    fout << "G1 Z2.0 F3000 ; Move Z Axis up little to prevent scratching of Heat Bed" << endl;
    fout << "G1 X5 Y20 Z0.3 F5000.0; Move over to prevent blob squish" << endl;
    fout << "G0 F9000 Z2" << endl;
    fout << "M300 S800 P500" << endl;

}

void gen::finish(){

    fout << endl << ";-----------------------------------" << endl;
    fout << "; Finishing Commands" << endl;
    fout << "M300 S440 P200" << endl;
    fout << "M140 S0" << endl;
    fout << "M107" << endl;
    fout << "G91 ;Relative positioning" << endl;
    fout << "G1 E-2 F2700 ;Retract a bit" << endl;
    fout << "G1 E-2 Z0.2 F2400 ;Retract and raise Z" << endl;
    fout << "G1 X5 Y5 F3000 ;Wipe out" << endl;
    fout << "G1 Z50 ;Raise Z more" << endl;
    fout << "G90 ;Absolute positionning" << endl;
    fout << "G1 X0 Y220 ;Present print" << endl;
    fout << "M106 S0 ;Turn-off fan" << endl;
    fout << "M104 S0 ;Turn-off hotend" << endl;
    fout << "M140 S0 ;Turn-off bed" << endl;
    fout << "M84 X Y Z E ;Disable all steppers" << endl;
    fout << "M82 ;absolute extrusion mode" << endl;
    fout << "M104 S0" << endl;
    fout << "; " << e / 1000 << "m of filament used." << endl;

}

void gen::generateCode(){

    setup();

    double maxH = maxHeight();

    for (int i = 0; i < 100; i++) cout << " ";
    cout << (char)219;
    cout << "\r" ;

    while (1){

        //Loading Bar
        static int oldPercent = 0;
        int newPercent = (layer / (maxH / .2)) * 100;
        int percentToAdd = newPercent - oldPercent;
        for(int i = 0; i < percentToAdd; i++) cout << (char)219;
        oldPercent = newPercent;


        fout << endl << ";-------------------------------------------------" << endl;
        fout << "; Layer:" << layer << endl;
        z = layer * layerHeight;

        for (int i = 0; i < shapeObject.size(); i++){
            if (shapeObject[i].shape != emptyShape && layer <= shapeObject[i].totalLayers){

                fout << endl << "; Object " << i + 1 << ": ";

                if (shapeObject[i].shape == box) {
                    fout << "Box" << endl;
                    shapeObject[i].boxLayer();
                }
                else if (shapeObject[i].shape == cylinder) {
                    fout << "Cylinder" << endl;
                    shapeObject[i].cylinderLayer();
                }
                else if (shapeObject[i].shape == polygon) {
                    if (shapeObject[i].sides == 3) fout << "Triangle" << endl;
                    else if (shapeObject[i].sides == 4) fout << "Diamond" << endl;
                    else if (shapeObject[i].sides == 5) fout << "Pentagon" << endl;
                    else if (shapeObject[i].sides == 6) fout << "Hexagon" << endl;
                    else if (shapeObject[i].sides == 7) fout << "Heptagon" << endl;
                    else if (shapeObject[i].sides == 8) fout << "Octagon" << endl;
                    else if (shapeObject[i].sides == 9) fout << "Nonagon" << endl;
                    else if (shapeObject[i].sides == 10) fout << "Decagon" << endl;
                    else if (shapeObject[i].sides == 11) fout << "Hendecagon" << endl;
                    else if (shapeObject[i].sides == 12) fout << "Dodecagon" << endl;
                    else if (shapeObject[i].sides > 12) fout << shapeObject[i].sides << " Sided Polygon" << endl;
                    shapeObject[i].polygonLayer();
                }
            }
        }

        if (layer * layerHeight >= maxH) break;
        else if (layer * layerHeight >= zMax) break;
        else {
            layer += 1;
            fillDirection = !fillDirection;
        }
    }
    cout << endl;
    finish();
    bool i = isnan(gen::e) ? 1 : 0;
    if (i){
        cout << "ERROR: error code NAN" << endl;
        cout << "Your generated code is most likely faulty." << endl;
        cout << "Please contact Derek Boekelheide with Error code and specifics." << endl;
        cout << "Most likely, an algorithm tried finding the square root of a negative." << endl;
    }

}

void gen::coutObjects(){

    cout << shapeObject.size() << " Total Objects" << endl << endl;

    for (int i = 0; i < shapeObject.size(); i++){
        if (shapeObject[i].shape != emptyShape){
            if (shapeObject[i].shape == box){
                cout << "Object " << i + 1 << ": Box" << endl;
                cout << "Dimensions: " << shapeObject[i].width << "mm x " << shapeObject[i].length << "mm x " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width || shapeObject[i].topLength != shapeObject[i].length)
                    cout << "Top Width: " << shapeObject[i].topWidth << "mm, Top Length: " << shapeObject[i].topLength << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    cout << "X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                cout << endl;
            }
            if (shapeObject[i].shape == cylinder){
                cout << "Object " << i + 1 << ": Cylinder" << endl;
                cout << "Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width)
                    cout << "Top Diameter: " << shapeObject[i].topWidth << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    cout << "X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                cout << endl;
            }
            if (shapeObject[i].shape == polygon){
                if (shapeObject[i].sides == 3) cout << "Object " << i + 1 << ": Triangle" << endl;
                else if (shapeObject[i].sides == 4) cout << "Object " << i + 1 << ": Diamond" << endl;
                else if (shapeObject[i].sides == 5) cout << "Object " << i + 1 << ": Pentagon" << endl;
                else if (shapeObject[i].sides == 6) cout << "Object " << i + 1 << ": Hexagon" << endl;
                else if (shapeObject[i].sides == 7) cout << "Object " << i + 1 << ": Heptagon" << endl;
                else if (shapeObject[i].sides == 8) cout << "Object " << i + 1 << ": Octagon" << endl;
                else if (shapeObject[i].sides == 9) cout << "Object " << i + 1 << ": Nonagon" << endl;
                else if (shapeObject[i].sides == 10) cout << "Object " << i + 1 << ": Decagon" << endl;
                else if (shapeObject[i].sides == 11) cout << "Object " << i + 1 << ": Hendecagon" << endl;
                else if (shapeObject[i].sides == 12) cout << "Object " << i + 1 << ": Dodecagon" << endl;
                else if (shapeObject[i].sides > 12) cout << "Object " << i + 1 << ": " << shapeObject[i].sides << " sided Polygon" << endl;
                cout << "Diameter: " << shapeObject[i].width << "mm, Height: " << shapeObject[i].height << "mm" << endl;
                cout << "Location: (" << shapeObject[i].xLocation << ", " << shapeObject[i].yLocation << ")" << endl;
                if (shapeObject[i].topWidth != shapeObject[i].width)
                    cout << "Top Diameter: " << shapeObject[i].topWidth << "mm" << endl;
                if (shapeObject[i].yShiftDegrees || shapeObject[i].xShiftDegrees)
                    cout << "X Shift: " << shapeObject[i].xShiftDegrees << " Degrees, Y Shift: " << shapeObject[i].yShiftDegrees << " Degrees" << endl;
                cout << endl;
            }
        }
    }

}

void gen::shape(int shape, double width, double length, double height, int xLocation, int yLocation){
    shapeObject.resize(shapeObject.size() + 1);
    int newestObject = shapeObject.size() - 1;
    shapeObject[newestObject].shapeDims(shape, width, length, height, xLocation, yLocation);
}


void gen::deleteObject(int objectToDelete){
    int objectNumber = objectToDelete - 1;
    shapeObject.erase(shapeObject.begin() + objectNumber);
}

//G commands
void gen::G0(){

    f = 9000;

    fout << "G0";
    if (f != oldF) fout << " F" << f;
    fout << " X" << x;
    fout << " Y" << y;
    if (z != oldZ) fout << " Z" << z;
    fout << endl;
    oldF = f;
    oldX = x;
    oldY = y;
    oldZ = z;

}

void gen::G1(){

    if (x == oldX && y == oldY) return;

    f = speed * 60;
    e += sqrt(((x - oldX) * (x - oldX)) + ((y - oldY) * (y - oldY))) * ((lineWidth * layerHeight) / 2.3);

    fout << "G1";
    if (f != oldF) fout << " F" << f;
    fout << " X" << x;
    fout << " Y" << y;
    if (z != oldZ) fout << " Z" << z;
    fout << " E" << e;
    fout << endl;
    oldF = f;
    oldX = x;
    oldY = y;
    oldZ = z;

}

void gen::G0withRetraction(){

    f = 9000;
    e -= retraction;
    fout << "G1";
    if (f != oldF) fout << " F" << f;
    fout << " E" << e << endl;

    G0();

    e += retraction;
    fout << "G1 E" << e << endl;

    oldF = f;
}

void gen::G1circle(double radius, double xLocation, double yLocation){
    for (double theta = -1 * M_PI; theta <= M_PI; theta += (2 * M_PI / 60)){
        x = xLocation + (radius * cos(theta));
        y = yLocation + (radius * sin(theta));
        G1();
    }
}

double gen::maxHeight(){
    int counter = 0;
    for (int i = 0; i < shapeObject.size(); i ++){
        counter = (shapeObject[i].height > counter) ? shapeObject[i].height : counter;
    }
    return counter;
}

void gen::Shape::shapeDims(int setShape, double setWidth, double setLength, double setHeight, double setxLocation, double setyLocation){
    shape = setShape;
    width = setWidth;
    length = setLength;
    height = setHeight;
    xLocation = setxLocation;
    yLocation = setyLocation;
    topWidth = width;
    topLength = length;
    totalLayers = height / layerHeight;
    _xCorner = xLocation - (width / 2);
    _yCorner = yLocation - (length / 2);
}

void gen::Shape::shiftDims(double setxShiftDegrees, double setyShiftDegrees){
    xShiftDegrees = setxShiftDegrees;
    yShiftDegrees = setyShiftDegrees;
    _xShift = (((xShiftDegrees / 9) * 10) / 100) * lineWidth;
    _yShift = (((yShiftDegrees / 9) * 10) / 100) * lineWidth;
}

void gen::Shape::topLayerDims(double setTopWidth, double setTopLength){
    topWidth = setTopWidth;
    if (setTopLength != -1)
        topLength = setTopLength;
}

void gen::Shape::boxLayer(){

    _widthLayer = width - (((width - topWidth)/(totalLayers - 1)) * layer) + ((width - topWidth)/(totalLayers - 1));
    _lengthLayer = length - (((length - topLength)/(totalLayers - 1)) * layer) + ((length - topLength)/(totalLayers - 1));
    _xCornerLayer = xLocation - (_widthLayer / 2) + ((_xShift * layer) - _xShift);
    _yCornerLayer = yLocation - (_lengthLayer / 2) + ((_yShift * layer) - _yShift);

    wall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        solidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        if (!xShiftDegrees && !yShiftDegrees && topWidth == width && topLength == length)
            shiftedInfill();
        else cubicInfill();

}





void gen::Shape::cylinderLayer(){

    _widthLayer = width - (((width - topWidth)/(totalLayers - 1)) * layer) + ((width - topWidth)/(totalLayers - 1));
    _xLocationLayer = xLocation - ((_xShift * layer) - _xShift);
    _yLocationLayer = yLocation - ((_yShift * layer) - _yShift);

    circleWall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        circleSolidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        circleInfill();

}

void gen::Shape::polygonLayer(){

    _widthLayer = width - (((width - topWidth)/(totalLayers - 1)) * layer) + ((width - topWidth)/(totalLayers - 1));
    _xLocationLayer = xLocation - ((_xShift * layer) - _xShift);
    _yLocationLayer = yLocation - ((_yShift * layer) - _yShift);

    polygonWall();

    if (layer <= bottomLayers || layer > totalLayers - topLayers)
        polygonSolidFill();

    else if (layer > bottomLayers && layer <= totalLayers - topLayers)
        polygonInfill();

}


void gen::Shape::wall(){

    fout << endl << "; Wall" << endl;

    x = _xCornerLayer;
    y = _yCornerLayer;
    G0withRetraction();

    for (int i = 0; i < wallLineCount; i++){

        double wallShift = lineWidth * i;
        if (_widthLayer < ((i+1) * lineWidth) || _lengthLayer < ((i+1) * lineWidth)) break;

        x = _xCornerLayer + wallShift;
        y = _yCornerLayer + wallShift;
        G0();

        if (layer == totalLayers) speed = topSpeed;
        else if (!i) speed = outerWallSpeed;
        else if (i) speed = innerWallSpeed;

        x += (_widthLayer - (wallShift * 2));
        G1();
        y += (_lengthLayer - (wallShift * 2));
        G1();
        x -= (_widthLayer - (wallShift * 2));
        G1();
        y -= (_lengthLayer - (wallShift * 2));
        G1();

    }
}

void gen::Shape::solidFill(){

    x = _xCornerLayer + (lineWidth * wallLineCount);
    y = _yCornerLayer + (lineWidth * wallLineCount);
    G0withRetraction();

    if (layer == totalLayers) speed = topSpeed;
    else speed = solidFillSpeed;

    fout << endl << "; Solid Fill" << endl;
    if (!fillDirection){
        while(1){

            y += (_lengthLayer - (lineWidth * wallLineCount * 2));
            G1();
            if ((x + lineWidth) > (_xCornerLayer + _widthLayer - (lineWidth * wallLineCount))) break;
            x += lineWidth;
            G0();
            y -= _lengthLayer - (lineWidth * wallLineCount * 2);
            G1();
            if ((x + lineWidth) > (_xCornerLayer + _widthLayer - (lineWidth * wallLineCount))) break;
            x += lineWidth;
            G0();
        }
    }
    if (fillDirection){
        while(1){

            x += (_widthLayer - (lineWidth * wallLineCount * 2));
            G1();
            if ((y + lineWidth) > (_yCornerLayer + _lengthLayer - (lineWidth * wallLineCount))) break;
            y += lineWidth;
            G0();
            x -= _widthLayer - (lineWidth * wallLineCount * 2);
            G1();
            if ((y + lineWidth) > (_yCornerLayer + _lengthLayer - (lineWidth * wallLineCount))) break;
            y += lineWidth;
            G0();
        }
    }
}

void gen::Shape::cubicInfill(){

    if (infillPercent == 0) return;

    double xCornerInterior = _xCornerLayer + (lineWidth * wallLineCount);
    double yCornerInterior = _yCornerLayer + (lineWidth * wallLineCount);
    double widthInterior = _widthLayer - (wallLineCount * lineWidth * 2);
    double lengthInterior = _lengthLayer - (wallLineCount * lineWidth * 2);
    double infillSpacing = (1 / infillPercent) * lineWidth;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    //convert to int for remainder operator
    int xCorner1000 = _xCorner * 1000;
    int yCorner1000 = _yCorner * 1000;
    int width1000 = width * 1000;
    int length1000 = length * 1000;
    int infillSpacing1000 = infillSpacing * 1000;

    double xShift1000 = ((xCorner1000 + (width1000 / 2)) % infillSpacing1000);
    double yShift1000 = ((yCorner1000 + (length1000 / 2)) % infillSpacing1000);
    double xFirstPass = xShift1000 / 1000;
    double yFirstPass = yShift1000 / 1000;

    while (1){
        if (xFirstPass < xCornerInterior) xFirstPass += infillSpacing;
        else break;
    }
    while (1){
        if (yFirstPass < yCornerInterior) yFirstPass += infillSpacing;
        else break;
    }

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    if (width > infillSpacing){

        x = xFirstPass;
        y = yCornerInterior;
        G0withRetraction();
        while(1){
            y += lengthInterior;
            G1();
            if (x + infillSpacing > xCornerInterior + widthInterior) break;
            x += infillSpacing;
            G0();
            y -= lengthInterior;
            G1();
            if (x + infillSpacing > xCornerInterior + widthInterior) break;
            x += infillSpacing;
            G0();
        }
    }

    if (_lengthLayer > infillSpacing){

        x = xCornerInterior;
        y = yFirstPass;
        G0withRetraction();
        while(1){
            x += widthInterior;
            G1();
            if (y + infillSpacing > yCornerInterior + lengthInterior) break;
            y += infillSpacing;
            G0();
            x -= widthInterior;
            G1();
            if (y + infillSpacing > yCornerInterior + lengthInterior) break;
            y += infillSpacing;
            G0();
        }
    }
}

void gen::Shape::shiftedInfill(){

    if (infillPercent == 0) return;

    const double infillMultiplier = 1 / infillPercent;
    static double infillShift = 0;
    infillShift += (lineWidth / 4);
    if (infillShift >= lineWidth * infillMultiplier) infillShift = 0;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    x = _xCorner + (lineWidth * wallLineCount) + infillShift;
    y = _yCorner + (lineWidth * wallLineCount);
    G0withRetraction();

    while(1){
        y += length - (lineWidth * wallLineCount * 2);
        G1();
        if ((x + (lineWidth * infillMultiplier)) > (_xCorner + width - (lineWidth * wallLineCount))) break;
        x += (lineWidth * infillMultiplier);
        G0();
        y -= (length - (lineWidth * wallLineCount * 2));
        G1();
        if ((x + (lineWidth * infillMultiplier)) > (_xCorner + width - (lineWidth * wallLineCount))) break;
        x += (lineWidth * infillMultiplier);
        G0();
    }
    x = _xCorner + (lineWidth * wallLineCount);
    y = _yCorner + (lineWidth * wallLineCount) + infillShift;
    G0withRetraction();
    while(1){
        x += width - (lineWidth * wallLineCount * 2);
        G1();
        if ((y + (lineWidth * infillMultiplier)) > (_yCorner + length - (lineWidth * wallLineCount))) break;
        y += (lineWidth * infillMultiplier);
        G0();
        x -= (width - (lineWidth * wallLineCount * 2));
        G1();
        if ((y + (lineWidth * infillMultiplier)) > (_yCorner + length - (lineWidth * wallLineCount))) break;
        y += (lineWidth * infillMultiplier);
        G0();
    }

}

void gen::Shape::circleWall(){

    fout << endl << "; Wall" << endl;

    x = _xLocationLayer - (_widthLayer / 2);
    y = _yLocationLayer;
    G0withRetraction();

    for (int i = 0; i < wallLineCount; i++){

        if (_widthLayer < ((i+1) * lineWidth)) break;

        double lineRadius = (_widthLayer / 2) - (i * lineWidth);

        if (layer == totalLayers) speed = topSpeed;
        else if (!i) speed = outerWallSpeed;
        else if (i) speed = innerWallSpeed;

        G1circle(lineRadius, _xLocationLayer, _yLocationLayer);

    }
}

void gen::Shape::circleSolidFill(){

    fout << endl << "; Solid Fill" << endl;


    double interiorRadiusLayer = (_widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);


    if (layer == totalLayers) speed = topSpeed;
    else speed = solidFillSpeed;

    if (!fillDirection){

        x = _xLocationLayer - interiorRadiusLayer;
        y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            y = _yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G1();
            if (x + lineWidth > _xLocationLayer + interiorRadiusLayer) break;
            x += lineWidth;
            y = _yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G0();
            y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G1();
            if (x + lineWidth > _xLocationLayer + interiorRadiusLayer) break;
            x += lineWidth;
            y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G0();
        }
    }
    if (fillDirection){

        y = _yLocationLayer - interiorRadiusLayer;
        x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            x = _xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G1();
            if (y + lineWidth > _yLocationLayer + interiorRadiusLayer) break;
            y += lineWidth;
            x = _xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G0();
            x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G1();
            if (y + lineWidth > _yLocationLayer + interiorRadiusLayer) break;
            y += lineWidth;
            x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G0();
        }
    }

}

void gen::Shape::circleInfill(){

    if (infillPercent == 0) return;

    double interiorRadiusLayer = (_widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    double interiorDiameterLayer = interiorRadiusLayer * 2;
    double xLimitInteriorLayer = _xLocationLayer - interiorRadiusLayer;
    double yLimitInteriorLayer = _yLocationLayer - interiorRadiusLayer;
    double infillSpacing = (1 / infillPercent) * lineWidth;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    double interiorRadiusBase = (width / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    double interiorDiameterBase = interiorRadiusBase * 2;
    double xLimitInteriorBase = xLocation - interiorRadiusBase;
    double yLimitInteriorBase = yLocation - interiorRadiusBase;

    //convert to int for remainder operator
    int xLimitInteriorBase1000 = xLimitInteriorBase * 1000;
    int yLimitInteriorBase1000 = yLimitInteriorBase * 1000;
    int interiorRadiusBase1000 = interiorRadiusBase * 1000;
    int infillSpacing1000 = infillSpacing * 1000;

    double xShift1000 = (xLimitInteriorBase1000 + interiorRadiusBase1000 % infillSpacing1000);
    double yShift1000 = (yLimitInteriorBase1000 + interiorRadiusBase1000 % infillSpacing1000);
    double xFirstPass = xShift1000 / 1000;
    double yFirstPass = yShift1000 / 1000;

    while (1){
        if (xFirstPass < xLimitInteriorLayer) xFirstPass += infillSpacing;
        else break;
    }
    while (1){
        if (yFirstPass < yLimitInteriorLayer) yFirstPass += infillSpacing;
        else break;
    }

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    if (interiorDiameterLayer > infillSpacing){

        x = xFirstPass;
        y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
            y = _yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G1();
            if (x + infillSpacing > _xLocationLayer + interiorRadiusLayer) break;
            x += infillSpacing;
            y = _yLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G0();
            y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G1();
            if (x + infillSpacing > _xLocationLayer + interiorRadiusLayer) break;
            x += infillSpacing;
            y = _yLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((x - _xLocationLayer) * (x - _xLocationLayer))) + .0000001);
            G0();
        }

        y = yFirstPass;
        x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
        G0withRetraction();

        while(1){
        x = _xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G1();
            if (y + infillSpacing > _yLocationLayer + interiorRadiusLayer) break;
            y += infillSpacing;
        x = _xLocationLayer + sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G0();
        x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G1();
            if (y + infillSpacing > _yLocationLayer + interiorRadiusLayer) break;
            y += infillSpacing;
        x = _xLocationLayer - sqrt(((interiorRadiusLayer * interiorRadiusLayer) - ((y - _yLocationLayer) * (y - _yLocationLayer))) + .0000001);
            G0();
        }
    }
}

void gen::Shape::polygonWall(){

    fout << endl << "; Wall" << endl;

    x = _xLocationLayer - (_widthLayer / 2);
    y = _yLocationLayer;
    G0withRetraction();

    for (int i = 0; i < wallLineCount; i++){

        if (_widthLayer < ((i+1) * lineWidth)) break;

        double lineRadius = (_widthLayer / 2) - (i * lineWidth);

        if (layer == totalLayers) speed = topSpeed;
        else if (!i) speed = outerWallSpeed;
        else if (i) speed = innerWallSpeed;

        for (double theta = -1 * M_PI; theta <= M_PI; theta += (2 * M_PI / sides)){
            x = _xLocationLayer + (lineRadius * cos(theta));
            y = _yLocationLayer + (lineRadius * sin(theta));
            G1();
        }
    }
}

void gen::Shape::polygonSolidFill(){

    fout << endl << "; Solid Fill" << endl;

    if (layer == totalLayers) speed = topSpeed;
    else speed = solidFillSpeed;

    double interiorRadiusLayer = (_widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    if (interiorRadiusLayer < lineWidth) return;

    struct Coordinate{
        double x;
        double y;
    };

    vector <Coordinate> vertice;

    for (double theta = -1 * M_PI; theta < M_PI; theta += (2 * M_PI / sides)){
        if (vertice.size() >= sides) break;
        vertice.resize(vertice.size() + 1);
        vertice.back().x = _xLocationLayer + (interiorRadiusLayer * cos(theta));
        vertice.back().y = _yLocationLayer + (interiorRadiusLayer * sin(theta));
    }

    if (!fillDirection){

        //put coordinate vector in order based on x coordinate
        for (int i = 0; i < vertice.size() - 1; i++){
            for (int j = i + 1; j <= vertice.size() - 1; j++){
                if (vertice[i].x > vertice[j].x){
                    Coordinate storage = vertice[i];
                    vertice[i] = vertice[j];
                    vertice[j] = storage;
                }
            }
        }

        Coordinate oldTop = vertice[0];
        Coordinate oldBottom = vertice[0];
        x = oldTop.x - lineWidth;
        y = oldTop.y;
        G0withRetraction();
        for (int i = 1; i < vertice.size(); i += 2){
            Coordinate newTop;
            Coordinate newBottom;
            if (i + 1 >= vertice.size()){
                newTop = vertice[i];
                newBottom = vertice[i];
            }
            else{
                newTop = (vertice[i].y > vertice[i+1].y) ? vertice[i] : vertice[i+1];
                newBottom = (vertice[i].y > vertice[i+1].y) ? vertice[i+1] : vertice[i];
            }

            double topSlope = (newTop.y - oldTop.y) / (newTop.x - oldTop.x);
            double bottomSlope = (newBottom.y - oldBottom.y) / (newBottom.x - oldBottom.x);
            if (topSlope < .01 && topSlope > -.01) topSlope = 0;
            if (bottomSlope < .01 && bottomSlope > -.01) bottomSlope = 0;

            x += lineWidth;
            y = oldTop.y + ((x - oldBottom.x) * topSlope);
            G0();

            while(1){
                y = oldBottom.y + ((x - oldBottom.x) * bottomSlope);
                G1();
                if (x + lineWidth > newTop.x) break;
                x += lineWidth;
                y = oldBottom.y + ((x - oldBottom.x) * bottomSlope);
                G0();
                y = oldTop.y + ((x - oldTop.x) * topSlope);
                G1();
                if (x + lineWidth > newBottom.x) break;
                x += lineWidth;
                y = oldTop.y + ((x - oldTop.x) * topSlope);
                G0();
            }
            oldTop = newTop;
            oldBottom = newBottom;
        }
    }

    if (fillDirection){

        //put coordinate vector in order based on y coordinate
        for (int i = 0; i < vertice.size() - 1; i++){
            for (int j = i + 1; j <= vertice.size() - 1; j++){
                if (vertice[i].y > vertice[j].y){
                    Coordinate storage = vertice[i];
                    vertice[i] = vertice[j];
                    vertice[j] = storage;
                }
            }
        }

        Coordinate oldLeft;
        Coordinate oldRight;
        Coordinate newLeft;
        Coordinate newRight;

        int i;


        //if one bottom verticenewLeft.y - newRight.y > .001 || newLeft.y - newRight.y < -.001
        if (vertice[0].y - vertice[1].y > .001 || vertice[0].y - vertice[1].y < -.001){
            newLeft = vertice[0];
            newRight = vertice[0];
            i = 1;
        }

        //if two bottom vertices
        else {
            newLeft = (vertice[0].x < vertice[1].x) ? vertice[0] : vertice[1];
            newRight = (vertice[0].x < vertice[1].x) ? vertice[1] : vertice[0];
            i = 2;
        }


        y = newLeft.y - lineWidth;
        x = newLeft.x;

        for (;;){

            int nextI;
            if (i + 1 > (sides - 1)) nextI = i;
            else nextI = i + 1;
            Coordinate updateLeft = (vertice[i].x < vertice[nextI].x) ? vertice[i] : vertice [nextI];
            Coordinate updateRight = (vertice[i].x < vertice[nextI].x) ? vertice[nextI] : vertice [i];

            //if newLeft needs to be updated
            if (updateLeft.x != newLeft.x || updateLeft.y != newLeft.y){
                oldLeft = newLeft;
                newLeft = updateLeft;
            }
            //if newRight needs to be updated
            if (updateRight.x != newRight.x || updateRight.y != newRight.y){
                oldRight = newRight;
                newRight = updateRight;
            }

            double leftSlope = (newLeft.x - oldLeft.x) / (newLeft.y - oldLeft.y);
            double rightSlope = (newRight.x - oldRight.x) / (newRight.y - oldRight.y);
            if (leftSlope < .01 && leftSlope > -.01) leftSlope = 0;
            if (rightSlope < .01 && rightSlope > -.01) rightSlope = 0;


            y += lineWidth;
            x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
            G0();

            while(1){
                x = oldRight.x + ((y - oldRight.y) * rightSlope);
                G1();
                if (y + lineWidth > newLeft.y) break;
                y += lineWidth;
                x = oldRight.x + ((y - oldRight.y) * rightSlope);
                G0();
                x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
                G1();
                if (y + lineWidth > newRight.y) break;
                y += lineWidth;
                x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
                G0();
            }

            //if newLeft.y != newRight.y,,,, this accounts for slight differences in doubles
            if (abs(newLeft.y - newRight.y) > .0001) i += 1;
            //if newLeft.y == newRight.y
            else i += 2;

            if (i >= sides) break;
        }
    }
}

void gen::Shape::polygonInfill(){


    double interiorRadiusLayer = (_widthLayer / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);
    double interiorDiameterLayer = interiorRadiusLayer * 2;
    double infillSpacing = (1 / infillPercent) * lineWidth;
    if (interiorRadiusLayer < lineWidth) return;

    fout << endl << "; " << infillPercent * 100 << "% Infill" << endl;

    //double interiorRadiusBase = (width / 2) - (lineWidth * wallLineCount) + (lineWidth / 2);

    if (layer == totalLayers) speed = topSpeed;
    else speed = infillSpeed;

    if (interiorDiameterLayer > infillSpacing){

        struct Coordinate{
            double x;
            double y;
        };

        vector <Coordinate> vertice;

        for (double theta = -1 * M_PI; theta < M_PI; theta += (2 * M_PI / sides)){
            if (vertice.size() >= sides) break;
            vertice.resize(vertice.size() + 1);
            vertice.back().x = _xLocationLayer + (interiorRadiusLayer * cos(theta));
            vertice.back().y = _yLocationLayer + (interiorRadiusLayer * sin(theta));
        }

        //put coordinate vector in order based on x coordinate
        for (int i = 0; i < vertice.size() - 1; i++){
            for (int j = i + 1; j <= vertice.size() - 1; j++){
                if (vertice[i].x > vertice[j].x){
                    Coordinate storage = vertice[i];
                    vertice[i] = vertice[j];
                    vertice[j] = storage;
                }
            }
        }

        Coordinate oldTop = vertice[0];
        Coordinate oldBottom = vertice[0];

        double xFirstPassA = 0;
        double yFirstPassA = 0;
        while (1){
            if (xFirstPassA < oldBottom.x) xFirstPassA += infillSpacing;
            else break;
        }
        while (1){
            if (yFirstPassA < oldBottom.y) yFirstPassA += infillSpacing;
            else break;
        }

        x = xFirstPassA - infillSpacing;
        //y = oldTop.y;
        //G0withRetraction();
        fout << "; Vertical Infill" << endl;
        for (int i = 1; i < vertice.size(); i += 2){
            Coordinate newTop;
            Coordinate newBottom;
            if (i + 1 >= vertice.size()){
                newTop = vertice[i];
                newBottom = vertice[i];
            }
            else{
                newTop = (vertice[i].y > vertice[i+1].y) ? vertice[i] : vertice[i+1];
                newBottom = (vertice[i].y > vertice[i+1].y) ? vertice[i+1] : vertice[i];
            }

            double topSlope = (newTop.y - oldTop.y) / (newTop.x - oldTop.x);
            double bottomSlope = (newBottom.y - oldBottom.y) / (newBottom.x - oldBottom.x);
            if (topSlope < .01 && topSlope > -.01) topSlope = 0;
            if (bottomSlope < .01 && bottomSlope > -.01) bottomSlope = 0;

            x += infillSpacing;
            y = oldTop.y + ((x - oldBottom.x) * topSlope);
            G0();

            while(1){
                y = oldBottom.y + ((x - oldBottom.x) * bottomSlope);
                G1();
                if (x + infillSpacing > newTop.x) break;
                x += infillSpacing;
                y = oldBottom.y + ((x - oldBottom.x) * bottomSlope);
                G0();
                y = oldTop.y + ((x - oldTop.x) * topSlope);
                G1();
                if (x + infillSpacing > newBottom.x) break;
                x += infillSpacing;
                y = oldTop.y + ((x - oldTop.x) * topSlope);
                G0();
            }
            oldTop = newTop;
            oldBottom = newBottom;
        }

        //put coordinate vector in order based on y coordinate
        for (int i = 0; i < vertice.size() - 1; i++){
            for (int j = i + 1; j <= vertice.size() - 1; j++){
                if (vertice[i].y > vertice[j].y){
                    Coordinate storage = vertice[i];
                    vertice[i] = vertice[j];
                    vertice[j] = storage;
                }
            }
        }

        Coordinate oldLeft;
        Coordinate oldRight;
        Coordinate newLeft;
        Coordinate newRight;

        int i;

        //if one bottom verticenewLeft.y - newRight.y > .001 || newLeft.y - newRight.y < -.001
        if (vertice[0].y - vertice[1].y > .001 || vertice[0].y - vertice[1].y < -.001){
            newLeft = vertice[0];
            newRight = vertice[0];
            i = 1;
        }
        //if two bottom vertices
        else {
            newLeft = (vertice[0].x < vertice[1].x) ? vertice[0] : vertice[1];
            newRight = (vertice[0].x < vertice[1].x) ? vertice[1] : vertice[0];
            i = 2;
        }

        double xFirstPassB = 0;
        double yFirstPassB = 0;
        while (1){
            if (xFirstPassB < newLeft.x) xFirstPassB += infillSpacing;
            else break;
        }
        while (1){
            if (yFirstPassB < newLeft.y) yFirstPassB += infillSpacing;
            else break;
        }

        y = yFirstPassB - infillSpacing;

        fout << "; Horizontal Infill" << endl;
        for (;;){

            int nextI;
            if (i + 1 > (sides - 1)) nextI = i;
            else nextI = i + 1;
            Coordinate updateLeft = (vertice[i].x < vertice[nextI].x) ? vertice[i] : vertice [nextI];
            Coordinate updateRight = (vertice[i].x < vertice[nextI].x) ? vertice[nextI] : vertice [i];

            //if newLeft needs to be updated
            if (updateLeft.x != newLeft.x || updateLeft.y != newLeft.y){
                oldLeft = newLeft;
                newLeft = updateLeft;
            }
            //if newRight needs to be updated
            if (updateRight.x != newRight.x || updateRight.y != newRight.y){
                oldRight = newRight;
                newRight = updateRight;
            }

            double leftSlope = (newLeft.x - oldLeft.x) / (newLeft.y - oldLeft.y);
            double rightSlope = (newRight.x - oldRight.x) / (newRight.y - oldRight.y);
            if (leftSlope < .01 && leftSlope > -.01) leftSlope = 0;
            if (rightSlope < .01 && rightSlope > -.01) rightSlope = 0;

            y += infillSpacing;
            x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
            G0();

            while(1){
                x = oldRight.x + ((y - oldRight.y) * rightSlope);
                G1();
                if (y + infillSpacing > newRight.y || y + infillSpacing > newLeft.y) break;  //dont need both but dont feel like figuring out which one
                y += infillSpacing;
                x = oldRight.x + ((y - oldRight.y) * rightSlope);
                G0();
                x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
                G1();
                if (y + infillSpacing > newRight.y || y + infillSpacing > newLeft.y) break;
                y += infillSpacing;
                x = oldLeft.x + ((y - oldLeft.y) * leftSlope);
                G0();
            }

            //if newLeft.y != newRight.y,,,, this accounts for slight differences in doubles
            if (abs(newLeft.y - newRight.y) > .0001) {
                i += 1;
            }
            //if newLeft.y == newRight.y
            else{
                i += 2;
            }
            if (i >= sides) break;
        }
    }
}
