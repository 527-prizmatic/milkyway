#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "vect.h"
#include "SFML/Graphics.h"

sfVector2f vector2f(float _x, float _y) { return (sfVector2f) { _x, _y }; }

sfVector2f vectCreate(sfVector2f _a, sfVector2f _b) {
	return vector2f(_b.x - _a.x, _b.y - _a.y);
}

void vectorCopyFloat(sfVector2f _source, sfVector2f* _dest) {
	_dest->x = _source.x;
	_dest->y = _source.y;
}

sfVector2f vectAdd(sfVector2f _a, sfVector2f _b) {
	return vector2f(_b.x + _a.x, _b.y + _a.y);
}

sfVector2f vectSub(sfVector2f _a, sfVector2f _b) {
	return vector2f(_b.x - _a.x, _b.y - _a.y);
}

sfVector2f vectMultiply(sfVector2f _a, float _x) {
	return vector2f(_a.x * _x, _a.y * _x);
}

float vectDotProduct(sfVector2f _a, sfVector2f _b) {
	return _a.x * _b.x + _a.y * _b.y;
}

float vectMag(sfVector2f _a) {
	return sqrt((_a.x * _a.x) + (_a.y * _a.y));
}

float vectMag2(sfVector2f _a) {
	return (_a.x * _a.x) + (_a.y * _a.y);
}

sfVector2f vectNormalize(sfVector2f _a) {
	float n = vectMag(_a);
	if (n == 0) return _a;
	return vector2f(_a.x / n, _a.y / n);
}

sfBool vectEquals(sfVector2f _a, sfVector2f _b) {
	float e = 0.00001;
	if (abs(_a.x - _b.x) > e) return sfFalse;
	if (abs(_a.y - _b.y) > e) return sfFalse;
	return sfTrue;
}

sfVector2f vectRotate(sfVector2f _a, float _angle) {
	float mag = vectMag(_a);
	float angleOrig = vectAngle(_a, vector2f(1, 0));
	sfVector2f vectNew;
	vectNew.x = cos((DEG2RAD * _angle) - angleOrig) * mag;
	vectNew.y = sin((DEG2RAD * _angle) - angleOrig) * mag;
	return vectNew; // Returns Cartesian coords
}

float vectAngle(sfVector2f _a, sfVector2f _b) {
	return atan2(_b.y, _b.x) - atan2(_a.y, _a.x);
}

sfVector2f recToPol(sfVector2f _a) {
	sfVector2f v;
	v.x = sqrt((_a.x * _a.x) + (_a.y * _a.y));
	v.y = atan2(_a.y, _a.x);
	return v;
}

sfVector2f polToRec(sfVector2f _a) {
	sfVector2f v;
	v.x = _a.x * cosf(_a.y);
	v.y = _a.x * sinf(_a.y);
	return v;
}

float pixelateFloat(float _val, int _px) {
	return _px * truncf(_val / _px);
}

sfVector2f vectorSnap(sfVector2f _v, int _px) {
	sfVector2f vecPx;
	vecPx.x = pixelateFloat(_v.x + _px / 2, _px);
	vecPx.y = pixelateFloat(_v.y + _px / 2, _px);
	return vecPx;
}