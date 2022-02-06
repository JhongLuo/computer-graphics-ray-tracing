#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>
Eigen::Vector3d blinn_phong_shading(
	const Ray& ray,
	const int& hit_id,
	const double& t,
	const Eigen::Vector3d& n,
	const std::vector< std::shared_ptr<Object> >& objects,
	const std::vector<std::shared_ptr<Light> >& lights)
{
	////////////////////////////////////////////////////////////////////////////
	std::shared_ptr<Material>& m = objects[hit_id]->material; // save time with reference

	Eigen::Vector3d pos = ray.origin + t * ray.direction; // out of loop for time saving
	Eigen::Vector3d rgb(0, 0, 0);

	// Ambient Shading 
	rgb += (m->ka.array() * (0.1 * Eigen::Vector3d(1, 1, 1)).array()).matrix();

	// for multiple lights
	for (int i = 0; i < lights.size(); ++i) {
		// get the l(has been normalized at direction function)
		Eigen::Vector3d l;
		double max_t;
		lights[i]->direction(pos, l, max_t);

		// figure out is the pos in shadow
		Ray to_light = { pos, l };
		int ignore_hit_id;
		double hit_distance;
		Eigen::Vector3d ignore_n;
		bool hitted = first_hit(to_light, 0.00001, objects, ignore_hit_id, hit_distance, ignore_n);

		if (hitted && (hit_distance < max_t)) {// when object between light and pos
			continue;
		}

		// Lambertian shading
		rgb += (m->kd.array() * lights[i]->I.array()).matrix() * std::max(0.0, l.dot(n.normalized()));

		// Blinn-Phong Shading
		Eigen::Vector3d h = (-ray.direction.normalized() + l).normalized();
		rgb += (m->ks.array() * lights[i]->I.array()).matrix() * std::pow(std::max(0.0, n.normalized().dot(h)), m->phong_exponent);
	}

	return rgb;
	////////////////////////////////////////////////////////////////////////////
}
