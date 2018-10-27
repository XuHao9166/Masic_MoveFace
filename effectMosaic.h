#ifndef __EFFECTMOSAIC_H__
#define __EFFECTMOSAIC_H__

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
class EffectMosaic 
{
	private:
		void SetColor(Mat img, int col, int row, int r, int g, int b);
		void AverageColor(Mat img, int col, int row, int *r, int *g, int *b);
	public:
		EffectMosaic();
		~EffectMosaic();
		Mat EffectMosaic::Mosaic(Mat imgIn);
};

#endif
