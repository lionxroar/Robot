#include "wireSphere.h"

void wireSphere::render(Matrix4 m)
{
	glColor3f(1, 0, 1);
	Vector3 center = Vector3(m.m[0][3], m.m[1][3], m.m[2][3]);
	m.transpose();
	extern int renderInt;
	extern int frustum;
	extern int bound;

	//Frustrum
	if (frustum == 1)
	{
		if (Globals::camera.sphereInFrustum(center, 100) != Globals::camera.OUTSIDE)
		{
			renderInt = 1;
			if (bound == 1)
			{
				glLoadMatrixd(m.getPointer());
				glutWireSphere(10, 20, 20);
			}
		}
	}

	//No Frustum
	else
	{
		if (bound == 1)
		{
			glLoadMatrixd(m.getPointer());
			glutWireSphere(10, 20, 20);
		}
	}
}