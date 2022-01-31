#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
	const std::string& filename,
	const std::vector<unsigned char>& data,
	const int width,
	const int height,
	const int num_channels)
{
	////////////////////////////////////////////////////////////////////////////
	// Replace with your code from computer-graphics-raster-images
	assert((num_channels == 3 || num_channels == 1));
	std::ofstream ppm_out(filename);
	if (!ppm_out.is_open()) {
		return false;
	}
	using namespace std;
	if (num_channels == 3) {
		ppm_out << "P3" << endl << width << " " << height << endl << 255 << endl;
	}
	else {
		ppm_out << "P2" << endl << width << " " << height << endl << 255 << endl;
	}

	unsigned long line_length = num_channels * width;
	for (int i = 0;i < width * height * num_channels;++i) {
		if (i % line_length) {
			ppm_out << (unsigned short)data[i] << " ";
		}
		else {
			ppm_out << (unsigned short)data[i] << endl;
		}
	}
	ppm_out.close();
	return true;
	////////////////////////////////////////////////////////////////////////////
}
