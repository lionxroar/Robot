#include "Geode.h"

void Geode::draw(Matrix4 C)
{
	//glLoadMatrixd(C.getPointer());
	render(C);
}