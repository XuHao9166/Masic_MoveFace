#include <iostream>
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include  "effectMosaic.h"

using namespace cv;
//设定相机的内外参数
double K[9] = { 6.5308391993466671e+002, 0.0, 3.1950000000000000e+002, 0.0, 6.5308391993466671e+002, 2.3950000000000000e+002, 0.0, 0.0, 1.0 };
double D[5] = { 7.0834633684407095e-002, 6.9140193737175351e-002, 0.0, 0.0, -1.3073460323689292e+000 };

int main()
{

	cv::VideoCapture cap;
	Mat eysROI;
	int frameNum = 0;
	int eyeNum = 0;
	bool biaozhi = true;
	int x0 = 0, y0 = 0, w0 = 0, h0 = 0;
	float angle = 0;

	cap.open(0);
	//cap.open("驾驶行为.mp4");
	if (!cap.isOpened())
	{
		std::cout << "Unable to connect to camera" << std::endl;
		return EXIT_FAILURE;
	}
	//加载Dlib检测模型
	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
	dlib::shape_predictor predictor;
	dlib::deserialize("D:\\Dlib\\shape_predictor_68_face_landmarks.dat") >> predictor;


	//全部人脸特征点二维点容器
	std::vector<cv::Point2f> image_pts;
	

	////将创建马赛克句柄
	EffectMosaic *effectMosaic;
	effectMosaic = new EffectMosaic();


	while (1)
	{
		frameNum++;


		cv::Mat temp;
		cv::Mat src_Mosaic;

		cap >> temp;

		Mat tempclone = temp.clone();

		//resize(temp, temp,cv::Size(640, 480)); ////

		dlib::cv_image<dlib::bgr_pixel> cimg(temp);


		std::vector<dlib::rectangle> faces = detector(cimg);

		src_Mosaic = effectMosaic->Mosaic(temp);

		
		if (faces.size() > 0)
		{

			//跟踪特征
			dlib::full_object_detection shape = predictor(cimg, faces[0]);

			//绘制特征
			for (unsigned int i = 0; i < 68; ++i)
			{
				cv::circle(temp, cv::Point(shape.part(i).x(), shape.part(i).y()), 2, cv::Scalar(0, 0, 255), -1);
			}

				image_pts.clear();
				//人脸外围特征点的二维图像坐标
				for (int k = 0; k < 27; k++)
				{

					image_pts.push_back(cv::Point2d(shape.part(k).x(), shape.part(k).y()));
				}

				
					vector<int> hull;
					convexHull(Mat(image_pts), hull, CV_CLOCKWISE, 0);
					int  hullcount = (int)hull.size();
					cv::Point pt0;
					pt0 = image_pts[hull[hullcount - 1]];
					Mat mask(temp.size(), CV_8UC3, Scalar(0, 0, 0));
					Mat  mask_gray;
					for (int i = 0; i < hullcount; i++)
					{
						cv::Point pt = image_pts[hull[i]];

						cv::line(mask, pt0, pt, CV_RGB(255, 255, 255), 2, CV_AA);
						pt0 = pt;

					}

					cvtColor(mask, mask_gray, CV_BGR2GRAY);
					vector<vector<Point>> contours;
					vector<Vec4i>hierarcy;//定义拓扑结构
					findContours(mask_gray, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

					drawContours(mask, contours, -1, Scalar(255, 255, 255), -1, 8); 
					

					src_Mosaic.copyTo(temp, mask);
					cv::imshow("demo", temp);
			
		}


		//cv::imshow("矫正", tempclone);
		
		unsigned char key = cv::waitKey(1);
		if (key == 27)
		{
			break;
		}
	}

	return 0;
}
