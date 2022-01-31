#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	double tmp = ray.direction.dot(this->normal);
	if (tmp != 0) {
		t = (this->point - ray.origin).dot(this->normal) / tmp;
		if (t >= min_t) {
			n = this->normal;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

	////////////////////////////////////////////////////////////////////////////
}

