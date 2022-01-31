#include "viewing_ray.h"

void viewing_ray(
	const Camera& camera,
	const int i,
	const int j,
	const int width,
	const int height,
	Ray& ray)
{
	////////////////////////////////////////////////////////////////////////////

	double w_ratio = camera.width / width;
	double h_ratio = camera.height / height;
	ray.origin = camera.e;
	ray.direction = -camera.w * camera.d + (j - width / 2) * camera.u * w_ratio + (-i + height / 2 - 1) * camera.v * h_ratio;
	////////////////////////////////////////////////////////////////////////////
}

