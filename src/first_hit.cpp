#include "first_hit.h"

bool first_hit(
	const Ray& ray,
	const double min_t,
	const std::vector< std::shared_ptr<Object> >& objects,
	int& hit_id,
	double& t,
	Eigen::Vector3d& n)
{
	////////////////////////////////////////////////////////////////////////////
	bool finded = false;
	for (int i = 0;i < objects.size();i++) {
		double tmp_t;
		Eigen::Vector3d tmp_n;
		bool hitted = objects[i]->intersect(ray, min_t, tmp_t, tmp_n);
		if (hitted && (!finded || tmp_t < t)) {
			hit_id = i;
			n = tmp_n;
			t = tmp_t;
			finded = true;
		}
	}
	return finded;
	////////////////////////////////////////////////////////////////////////////
}

