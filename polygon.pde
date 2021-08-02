//this Polygon class extends the functionality of the built-in shape functions
//stroke is required to view the polygon
//be sure to set maxCorners to avoid syntax issues
//all operations involving angles are dealt with in degrees, not radians

//Guide:
//Function Name (a-z)        Line#

//addPoint()-----------------79
//avgX()---------------------297
//avgY()---------------------309
//contains()-----------------125
//createRegular()------------350
//drawPolygon()--------------43
//fillPolygon()--------------54
//getAngle()-----------------321
//intersectsPolygon()--------257
//reset()--------------------105
//resizePolygon()------------284
//rotatePolygon()------------207, 232
//rotateTo()-----------------341
//setAngle()-----------------330
//setMaxCorners()------------116
//translatePolygon()---------196
//translateTo()--------------249
//XPoints()------------------89
//YPoints()------------------97


import java.util.*;
class Polygon {

  public int maxCorners = 10;
  public float[] xcoords = new float[this.maxCorners];
  public float[] ycoords = new float[this.maxCorners];
  public int index = 0;
  public float angle = 0;

  //=====================================================================================

  //draws outline of a polygon

  void drawPolygon() {
    for (int i = 0; i < this.index-1; i++) {
      line(this.xcoords[i], this.ycoords[i], this.xcoords[i+1], this.ycoords[i+1]);
    }
    line(this.xcoords[0], this.ycoords[0], this.xcoords[this.index-1], this.ycoords[this.index-1]);
  }

  //===================================================================================== 

  //draws a filled in polygon

  void fillPolygon() {
    drawPolygon();
    float minX = this.xcoords[0];
    float maxX = this.xcoords[0];
    float minY = this.ycoords[0];
    float maxY = this.ycoords[0];
    for (int i = 0; i < this.xcoords.length; i++) {
      minX = Math.round(Math.min(minX, this.xcoords[i]));
      maxX = Math.round(Math.max(maxX, this.xcoords[i]));
      minY = Math.round(Math.min(minY, this.ycoords[i]));
      maxY = Math.round(Math.max(maxY, this.ycoords[i]));
    }
    for (int y = (int)minY; y < maxY; y++) {
      for (int x = (int)minX; x < maxX; x++) {
        if (this.contains(x, y)) {
          point(x, y);
        }
      }
    }
  }

  //=====================================================================================

  //adds a corner to the polygon

  void addPoint(float x, float y) {
    this.xcoords[this.index] = x;
    this.ycoords[this.index] = y;
    this.index += 1;
  }

  //===================================================================================== 

  //returns list of all x coordinates that have been added

  float[] XPoints() {
    return Arrays.copyOfRange(this.xcoords, 0, this.index);
  }

  //=====================================================================================

  //returns list of all y coordinates that have been added

  float[] YPoints() {
    return Arrays.copyOfRange(this.ycoords, 0, this.index);
  }

  //=====================================================================================

  //resets the lists of coordinates

  void reset() {
    this.xcoords = new float[this.maxCorners];
    this.ycoords = new float[this.maxCorners];
    this.index = 0;
  }

  //=====================================================================================

  //sets the maximum number of corners
  //note: setMaxCorners will reset the lists of coordinates

  void setMaxCorners(int num) {
    this.maxCorners = num;
    this.reset();
  }

  //=====================================================================================

  //if the given coordinate is inside the polygon, it returns true, otherwise it returns false

  boolean contains(float x, float y) {
    float slope = 0;
    float b = 0;
    int right = 0;
    int intersections = 0;
    int lastRight = 0;
    for (int i = 0; i < this.index-1; i++) {
      if (this.ycoords[i] >= y || this.ycoords[i+1] >= y) {
        if (((this.xcoords[i] <= x && this.xcoords[i+1] > x) || (this.xcoords[i] >= x && this.xcoords[i+1] < x) || (this.xcoords[i] < x && this.xcoords[i+1] >= x) || (this.xcoords[i] > x && this.xcoords[i+1] <= x)) && ((this.xcoords[i] >= x && this.xcoords[i+1] < x) || (this.xcoords[i] <= x && this.xcoords[i+1] > x)) || (this.xcoords[i] > x && this.xcoords[i+1] <= x) || (this.xcoords[i] < x && this.xcoords[i+1] >= x)) {
          slope = (this.ycoords[i+1]-this.ycoords[i])/(this.xcoords[i+1]-this.xcoords[i]);
          b = this.ycoords[i]-(slope*this.xcoords[i]);
          if ((x*slope)+b >= y) {
            if (this.xcoords[i] == x && this.xcoords[i] > x && this.xcoords[i+1] != x) {
              right = int(this.xcoords[i+1]-x/abs(this.xcoords[i+1]-x));
              if (lastRight != right && lastRight != 0) {
                intersections ++;
              } else {
                intersections += 2;
              }
              lastRight = right;
            } else if (this.xcoords[i+1] == x && this.xcoords[i+1] > x && this.xcoords[i] != x) {
              right = int(this.xcoords[i]-x/abs(this.xcoords[i]-x));
              if (lastRight != right && lastRight != 0) {
                intersections ++;
              } else {
                intersections += 2;
              }
              lastRight = right;
            } else {
              intersections ++;
            }
          }
        }
      }
    }
    if (this.ycoords[this.index-1] >= y || this.ycoords[0] >= y) {
      if (((this.xcoords[this.index-1] <= x && this.xcoords[0] > x) || (this.xcoords[this.index-1] >= x && this.xcoords[0] < x)) && ((this.xcoords[this.index-1] >= x && this.xcoords[0] < x) || (this.xcoords[this.index-1] <= x && this.xcoords[0] > x))) {
        slope = (this.ycoords[0]-this.ycoords[this.index-1])/(this.xcoords[0]-this.xcoords[this.index-1]);
        b = this.ycoords[this.index-1]-(slope*this.xcoords[this.index-1]);
        if ((x*slope)+b >= y) {
          if (this.xcoords[this.index-1] == x && this.xcoords[this.index-1] > x && this.xcoords[0] != x) {
            right = int(this.xcoords[0]-x/abs(this.xcoords[0]-x));
            if (lastRight != right && lastRight != 0) {
              intersections ++;
            } else {
              intersections += 2;
            }
          } else if (this.xcoords[0] == x && this.xcoords[0] > x && this.xcoords[this.index-1] != x) {
            right = int(this.xcoords[this.index-1]-x/abs(this.xcoords[this.index-1]-x));
            if (lastRight != right && lastRight != 0) {
              intersections ++;
            } else {
              intersections += 2;
            }
          } else {
            intersections ++;
          }
        }
      }
    }
    if (intersections%2 == 0) {
      return false;
    } else {
      return true;
    }
  }

  //=====================================================================================

  //translates the polygon by the given x and y

  void translatePolygon(float x, float y) {
    for (int i = 0; i < index; i++) {
      this.xcoords[i] = this.xcoords[i] + x;
      this.ycoords[i] = this.ycoords[i] + y;
    }
  }

  //=====================================================================================

  //rotates the polygon by the given angle around an average coordinate

  void rotatePolygon(float angle) {
    float x1 = 0;
    float y1 = 0;
    for (int i = 0; i < this.index; i++) {
      x1 += this.xcoords[i];
      y1 += this.ycoords[i];
    }
    x1 = x1/this.index;
    y1 = y1/this.index;
    this.translatePolygon(-x1, -y1);
    for (int i = 0; i < this.index; i++) {
      float y2 = this.ycoords[i];
      float x2 = this.xcoords[i];
      float x3 = x2*cos(radians(angle))+y2*sin(radians(angle));
      float y3 = y2*cos(radians(angle))-x2*sin(radians(angle));
      this.xcoords[i] = x3;
      this.ycoords[i] = y3;
    }
    this.translatePolygon(x1, y1);
  }

  //======================================================================================

  //rotates the polygon by the given angle around a given coordinate

  void rotatePolygon(float x, float y, float angle) {
    this.translatePolygon(-x, -y);
    for (int i = 0; i < this.index; i++) {
      float y2 = this.ycoords[i];
      float x2 = this.xcoords[i];
      float x3 = x2*cos(radians(angle))+y2*sin(radians(angle));
      float y3 = y2*cos(radians(angle))-x2*sin(radians(angle));
      this.xcoords[i] = x3;
      this.ycoords[i] = y3;
    }
    this.translatePolygon(x, y);
  }

  //======================================================================================

  //translates the polygon to the given coordinate

  void translateTo(float x, float y) {
    this.translatePolygon(x-this.avgX(), y-this.avgY());
  }

  //======================================================================================

  //returns true if the two polygons are intersecting, if not it returns false

  boolean intersectsPolygon(Polygon A) {
    float[] A_xcoords = A.XPoints();
    float[] A_ycoords = A.YPoints();
    float AXmax = A_xcoords[0];
    float AXmin = A_xcoords[0];
    float AYmax = A_ycoords[0];
    float AYmin = A_ycoords[0];
    for (int i = 0; i < A_xcoords.length; i++) {
      AXmax = round(max(AXmax, A_xcoords[i]));
      AXmin = round(min(AXmin, A_xcoords[i]));
      AYmax = round(max(AYmax, A_ycoords[i]));
      AYmin = round(min(AYmin, A_ycoords[i]));
    }
    for (int y = (int)AYmin; y < AYmax; y++) {
      for (int x = (int)AXmin; x < AXmax; x++) {
        if (A.contains(x, y) && this.contains(x, y)) {
          return true;
        }
      }
    }
    return false;
  }

  //======================================================================================

  //resizes the polygon to scl times its original size

  void resizePolygon(float scl) {
    float x1 = this.avgX();
    float y1 = this.avgY();
    for (int i = 0; i < this.index; i++) {
      this.xcoords[i] = x1 + ((this.xcoords[i] - x1)*scl);
      this.ycoords[i] = y1 + ((this.ycoords[i] - y1)*scl);
    }
  }

  //======================================================================================

  //returns an average x coordinate

  float avgX() {
    float avg = 0;
    for (int i = 0; i < this.index; i++) {
      avg += this.xcoords[i];
    }
    return avg/this.index;
  }

  //======================================================================================

  //returns an average y coordinate

  float avgY() {
    float avg = 0;
    for (int i = 0; i < this.index; i++) {
      avg += this.ycoords[i];
    }
    return avg/index;
  }

  //======================================================================================

  //returns the angle of the polygon in degrees

  float getAngle() {
    return this.angle;
  }

  //======================================================================================

  //changes the angle of the polygon to the given angle
  //note: if the angle of the polygon is not meant to begin at zero, set angle before setting the corners

  void setAngle(float a) {
    if (this.index != 0) {
      rotateTo(a);
    }
    this.angle = a;
  }

  //======================================================================================

  //rotates the polygon to the given angle around an average coordinate

  void rotateTo(float a) {
    rotatePolygon(a-this.angle);
  }

  //======================================================================================

  //creates a regular shape with an apothem of 1 with the given amount of sides
  //the number of sides has to be at least 3

  void createRegular(int sides) {
    if (sides >= 3) {
      setMaxCorners(sides);
      float a = 360/(2*sides);
      float r1 = sin(PI/sides);
      float r = pow(-1/((r1*r1)-1), 0.5);
      for (int i = 0; i < sides; i++) {
        float x = r*cos(PI*(90-a)/180);
        float y = r*sin(PI*(90-a)/180);
        addPoint(x, y);
        a += 360/sides;
      }
    }
  }

  //======================================================================================
}