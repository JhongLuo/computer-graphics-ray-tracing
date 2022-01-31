#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	Eigen::Vector3d tmp = ray.origin - this->center;
	double a = ray.direction.dot(ray.direction);
	double b = 2 * ray.direction.dot(tmp);
	double c = tmp.dot(tmp) - this->radius * this->radius;
	double delta = b * b - 4 * a * c;
	if (delta >= 0) {
		double part1 = -b / (2 * a);
		double part2 = sqrt(delta) / (2 * a);
		double ans1 = part1 - part2;
		double ans2 = part1 + part2;
		if (ans1 < min_t) {
			if (ans2 < min_t) {
				return false;
			}
			else {
				t = ans2;
			}
		}
		else {
			t = ans1;
		}
		n = (t * ray.direction + tmp) / radius;
		return true;
	}
	else {
		return false;
	}
	////////////////////////////////////////////////////////////////////////////
}

