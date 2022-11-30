#pragma once

#include <cmath>
#include <iostream>
#include <vector>

struct Vector3D {
  float x, y, z;
  Vector3D() { x = 0, y = 0, z = 0; }
  Vector3D(float X, float Y, float Z) {
    x = X;
    y = Y;
    z = Z;
  }
  Vector3D operator+(Vector3D vec) {
    return Vector3D(vec.x + x, vec.y + y, vec.z + z);
  }
  Vector3D operator*(float a) { return Vector3D(x * a, y * a, z * a); }
};

class Cube {
 public:
  Vector3D* C3D;
  float Dist[8];
  std::vector<std::vector<int>> show;

  Cube(float _size);

  void draw(float x, float y, float z);

  float distanceTo(float x, float y, float z);

  void rotate(float alfaX, float alfaY, float alfaZ);

  void move(float x, float y, float z);

 private:
  void move();

  float calcDistance(Vector3D view, Vector3D obj);

  void updateDistances(Vector3D view);

  void rotateX(float angle);

  void rotateY(float angle);

  void rotateZ(float angle);

  float CDis = 0;

  std::vector<std::vector<int>> faces = {
      {0, 1, 5, 4}, {1, 2, 6, 5}, {2, 3, 7, 6}, {3, 0, 4, 7},
      {0, 1, 2, 3}, {4, 5, 6, 7}

  };

  Vector3D vertex[8] = {
      Vector3D(-1, -1, 1),  Vector3D(1, -1, 1), Vector3D(1, -1, -1),
      Vector3D(-1, -1, -1), Vector3D(-1, 1, 1), Vector3D(1, 1, 1),
      Vector3D(1, 1, -1),   Vector3D(-1, 1, -1)

  };

  Vector3D center = Vector3D(0, 0, 0);

  float* distances = nullptr;
};
