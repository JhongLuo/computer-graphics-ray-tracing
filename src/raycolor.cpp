#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "Material.h"
bool raycolor(
	const Ray& ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> >& objects,
	const std::vector< std::shared_ptr<Light> >& lights,
	const int num_recursive_calls,
	Eigen::Vector3d& rgb)
{
	////////////////////////////////////////////////////////////////////////////
	int hit_id;
	double t;
	Eigen::Vector3d n(1,1,1);
	if (first_hit(ray, min_t, objects, hit_id, t, n)) {
		rgb += blinn_phong_shading(ray, hit_id, t, n, objects, lights);
		Eigen::Vector3d& km = objects[hit_id]->material->km;//save time with reference
		if (km != Eigen::Vector3d(0, 0, 0) && num_recursive_calls < 10) {// is the mirror and the depth is not deep, for time saving
			Ray reflected_ray = { ray.origin + t * ray.direction, reflect(ray.direction.normalized(), n.normalized()) };
			Eigen::Vector3d reflected_rgb(0, 0, 0);
			if (raycolor(reflected_ray, 0.00001, objects, lights, num_recursive_calls + 1, reflected_rgb)) {
				rgb += (km.array() * reflected_rgb.array()).matrix();
			}
		}
		return true;
	}
	else {
		return false;
	}
	////////////////////////////////////////////////////////////////////////////
}
