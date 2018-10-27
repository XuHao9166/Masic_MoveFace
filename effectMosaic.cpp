#include "effectMosaic.h"


#define MOSAIC_SIZE 18


// Konstruktor
EffectMosaic::EffectMosaic()
{
}

// Destruktor
EffectMosaic::~EffectMosaic() 
{
}

Mat EffectMosaic::Mosaic(Mat imgIn)
{	
	Mat imgOut = imgIn.clone();

	/*IplImage *imgOut = NULL;
	imgOut = cvCreateImage(cvGetSize(imgIn), imgIn->depth, imgIn->nChannels);*/

	

	for(int i=0; (i < imgIn.rows); i+=MOSAIC_SIZE)
	{
		for(int j=0; (j < imgIn.cols); j+=MOSAIC_SIZE)
		{			
			int r;
			int g;
			int b;

			AverageColor(imgIn, j, i, &r, &g, &b);
			SetColor(imgOut, j, i, r, g, b);
		}
	}


	//cvCopy( imgIn, imgOut, NULL );
	return imgOut;
};



/*
 Vypocet prumerne barvy v danem vyseku obrazu
 img - obrazek
 col - cislo sloupce
 row - cislo radku
 r,g,b - vysledna barva
*/
void EffectMosaic::AverageColor(Mat img, int col, int row, int *r, int *g, int *b)
{
	// vynulovani barev
	*r = 0;
	*g = 0;
	*b = 0;

	int counter = 0;

	// pruchod polem a pricitani hodnot barev
	for(int i=row; (i < img.rows)&&(i < row+MOSAIC_SIZE); i++)
	{
		for(int j=col; (j < img.cols)&&(j < col+MOSAIC_SIZE); j++)
		{
			*b += img.at<Vec3b>(i, j)[0]; // B
			*g += img.at<Vec3b>(i, j)[1]; // G
			*r += img.at<Vec3b>(i, j)[2]; // R
			counter++;
		}
	}

	// vypocet prumeru
	*r /= counter;
	*g /= counter;
	*b /= counter;

	return;
}



/*
 Obarveni vsech pixelu v danem vyseku stejnou barvou
 img - obrazek
 col - cislo sloupce
 row - cislo radku
 r,g,b - vysledna barva
*/
void EffectMosaic::SetColor(Mat img, int col, int row, int r, int g, int b)
{
	// pruchod polem a pricitani hodnot barev
	for (int i = row; (i < img.rows) && (i < row + MOSAIC_SIZE); i++)
	{
		for (int j = col; (j < img.cols) && (j < col + MOSAIC_SIZE); j++)
		{
			img.at<Vec3b>(i, j)[0] = b; // B
			img.at<Vec3b>(i, j)[1] = g; // G
			img.at<Vec3b>(i, j)[2] = r; // R
		}
	}

	return;
}
