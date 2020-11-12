#pragma once

#include "fort-tags.hpp"

namespace fort {
namespace tags {

class ApriltagOptions {
public:
	tags::Family Family;

	float        QuadDecimate;
	float        QuadSigma;
	bool         RefineEdges;
	int          QuadMinClusterPixel;
	int          QuadMaxNMaxima;
	float        QuadCriticalRadian;
	float        QuadMaxLineMSE;
	int          QuadMinBWDiff;
	bool         QuadDeglitch;


	ApriltagOptions();

	void SetUpDetector(apriltag_detector_t * detector) const;

};



} //namespace tags
} //namespace fort
