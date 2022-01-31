#include "Triangle.h"
#include "Ray.h"

bool Triangle::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	Eigen::Vector3d corner0 = std::get<0>(this->corners);
	Eigen::Vector3d corner1 = std::get<1>(this->corners);
	Eigen::Vector3d corner2 = std::get<2>(this->corners);
	Eigen::Vector3d edge01 = corner0 - corner1;
	Eigen::Vector3d edge12 = corner1 - corner2;
	Eigen::Vector3d cross = edge01.cross(edge12);
	double tmp = ray.direction.dot(cross);
	if (tmp != 0) {
		Eigen::Vector3d edge20 = corner2 - corner0;
		t = (corner0 - ray.origin).dot(cross) / tmp;
		Eigen::Vector3d point = ray.direction * t + ray.origin;
		double area = cross.norm();
		double sum_area = 0;
		Eigen::Vector3d edge0p = corner0 - point;

		sum_area += (edge01.cross(edge0p)).norm();
		if ((sum_area - area) / area > 0.01)
			return false;
		Eigen::Vector3d edge1p = corner1 - point;
		sum_area += (edge12.cross(edge1p)).norm();
		if ((sum_area - area) / area > 0.01)
			return false;
		Eigen::Vector3d edge2p = corner2 - point;
		sum_area += (edge20.cross(edge2p)).norm();
		if ((sum_area - area) / area > 0.01 || (sum_area - area) / area < -0.01)
			return false;
		n = cross / cross.norm();
		return true;
	}
	else {
		return false;
	}
	////////////////////////////////////////////////////////////////////////////
}


