#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
	const Ray& ray, const double min_t, double& t, Eigen::Vector3d& n) const
{
	////////////////////////////////////////////////////////////////////////////
	bool finded = false;
	for (int i = 0, size = this->triangles.size();i < size;i++) {
		double tmp_t;
		Eigen::Vector3d tmp_n;
		bool hit = this->triangles[i]->intersect(ray, min_t, tmp_t, tmp_n);
		if (hit && (!finded || tmp_t < t)) {
			t = tmp_t;
			n = tmp_n;
			finded = true;
		}
	}
	return finded;
	////////////////////////////////////////////////////////////////////////////
}



