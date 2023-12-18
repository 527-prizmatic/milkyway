#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "SFML/Graphics.h"

#define PI 3.1415926535
#define DEG2RAD PI / 180.f
#define RAD2DEG 180.f / PI

/// Quick sfVector2f constructor
sfVector2f vector2f(float _x, float _y);

/// Builds a vector by computing the difference between two vectors, in accordance with the triangle inequality principle.
sfVector2f vectCreate(sfVector2f _a, sfVector2f _b);

/// Copies values from a sfVector2f into another one.
/// \param _source - Source vector to copy data from
/// \param _dest - Pointer to a destination vector
void vectorCopyFloat(sfVector2f _source, sfVector2f* _dest);

/// Sums two vectors.
sfVector2f vectAdd(sfVector2f _a, sfVector2f _b);

/// Subtracts two vectors.
sfVector2f vectSub(sfVector2f _a, sfVector2f _b);

/// Multiplies a vector by a scalar.
sfVector2f vectMultiply(sfVector2f _a, float _x);

/// Computes the dot product of two vectors.
float vectDotProduct(sfVector2f _a, sfVector2f _b);

/// Computes a vector's magnitude.
float vectMag(sfVector2f _a);

/// Computes a vector's squared magnitude. Functionally similar to vectMag(sfVector2f _a), except that skipping the square root allows for slight optimizations.
float vectMag2(sfVector2f _a);

/// Normalizes a vector.
sfVector2f vectNormalize(sfVector2f _a);

/// Checks if two vectors are equal.
sfBool vectEquals(sfVector2f _a, sfVector2f _b);

/// Rotates a vector.
sfVector2f vectRotate(sfVector2f _a, float _angle);

float vectAngle(sfVector2f _a, sfVector2f _b);

sfVector2f recToPol(sfVector2f _a);

sfVector2f polToRec(sfVector2f _a);