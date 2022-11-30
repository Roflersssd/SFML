#include "Cube.h"

#include <cmath>
#include <iostream>
#include <vector>

Cube::Cube(float _size) {
  CDis = _size / 2;
  C3D = new Vector3D[8];
  distances = new float[9];

  move();
}

void Cube::draw(float x, float y, float z) {
  show.clear();
  updateDistances(Vector3D(x, y, z));
  for (int face = 0; face < 6; face++) {
    int index = 0;
    for (int corner = 0; corner < 4; corner++)
      index += faces[face][corner] - (distances[faces[face][corner]] - 1);
    if (index == 0)
      show.push_back(faces[face]);
  }
}

float Cube::distanceTo(float x, float y, float z) {
  return calcDistance(center, Vector3D(x, y, z));
}

void Cube::rotate(float alfaX, float alfaY, float alfaZ) {
  rotateX(alfaX);
  rotateY(alfaY);
  rotateZ(alfaZ);
}

void Cube::move(float x, float y, float z) {
  center = Vector3D(x, y, z);
  move();
}

void Cube::move() {
  for (int i = 0; i < 8; i++) {
    C3D[i] = center + vertex[i] * CDis;
  }
}

float Cube::calcDistance(Vector3D view, Vector3D obj) {
  float xcb = (view.x - obj.x) * (view.x - obj.x);
  float ycb = (view.y - obj.y) * (view.y - obj.y);
  float zcb = (view.z - obj.z) * (view.z - obj.z);
  return sqrtf(xcb + ycb + zcb);
}

void Cube::updateDistances(Vector3D view) {
  distances[8] = distances[0] = calcDistance(view, C3D[0]);

  for (int i = 1; i < 8; i++) {
    distances[i] = calcDistance(view, C3D[i]);
    Dist[i] = distances[i];
    if (distances[i] > distances[8])
      distances[8] = distances[i];
  }
  for (int i = 0; i < 8; i++) {
    if (distances[i] == distances[8])
      distances[i] = 0;
    else
      distances[i] = (i + 1);
  }
}

void Cube::rotateX(float angle) {
  float sinF = sin(angle);
  float cosF = cos(angle);
  for (int i = 0; i < 8; i++) {
    float y = vertex[i].y;
    float z = vertex[i].z;

    vertex[i].y = y * cosF - z * sinF;
    vertex[i].z = z * cosF + y * sinF;
  }
}

void Cube::rotateY(float angle) {
  float sinF = sin(angle);
  float cosF = cos(angle);
  for (int i = 0; i < 8; i++) {
    float x = vertex[i].x;
    float z = vertex[i].z;

    vertex[i].x = x * cosF + z * sinF;
    vertex[i].z = z * cosF - x * sinF;
  }
  move();
}

void Cube::rotateZ(float angle) {
  float sinF = sin(angle);
  float cosF = cos(angle);
  for (int i = 0; i < 8; i++) {
    float x = vertex[i].x;
    float y = vertex[i].y;

    vertex[i].x = x * cosF - y * sinF;
    vertex[i].y = y * cosF + x * sinF;
  }
  move();
}
