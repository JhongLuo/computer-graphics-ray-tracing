#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d& in, const Eigen::Vector3d& n)
{
	////////////////////////////////////////////////////////////////////////////
	// have made sure in and n is normalized before calling the function, so don't waste time do the normalization
	return in + 2 * (-in.dot(n) * n);
	////////////////////////////////////////////////////////////////////////////
}
