#include "options.hpp"

namespace fort {
namespace tags {

ApriltagOptions::ApriltagOptions()
	: Family(fort::tags::Family::Undefined)
	, QuadDecimate(1.0)
	, QuadSigma(0.0)
	, RefineEdges(false)
	, QuadMinClusterPixel(5)
	, QuadMaxNMaxima(10)
	, QuadCriticalRadian(0.174533)
	, QuadMaxLineMSE(10.0)
	, QuadMinBWDiff(40)
	, QuadDeglitch(false) {
}

void ApriltagOptions::SetUpDetector(apriltag_detector_t * d) {
	d->nthreads = 1;
	d->quad_decimate = QuadDecimate;
	d->quad_sigma = QuadSigma;
	d->refine_edges = RefineEdges ? 1 : 0;
	d->debug = false;
	d->qtp.min_cluster_pixels = QuadMinClusterPixel;
	d->qtp.max_nmaxima = QuadMaxNMaxima;
	d->qtp.critical_rad = QuadCriticalRadian;
	d->qtp.max_line_fit_mse = QuadMaxLineMSE;
	d->qtp.min_white_black_diff = QuadMinBWDiff;
	d->qtp.deglitch = QuadDeglitch ? 1 : 0;
}


} //namespace tags
} //namespace fort
