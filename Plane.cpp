#include "Plane.h"

void Plane::setPoints(Vector3 v1, Vector3 v2, Vector3 v3)
{
	Vector3 vector1 = v1 - v2;
	Vector3 vector2 = v3 - v2;

	normal = vector2.cross(vector1);
	normal.normalize();

	point = v2;

	d = -(normal.dot(normal,point));
}

float Plane::distance(Vector3 point)
{
	return (d + normal.dot(normal, point));
}