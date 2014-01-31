/**
  * A novel kernelized fuzzy C-means algorithm with application in medical image segmentation
  *
  * @author Maxime ARRIAZA
  * @author Kevin RENELLA
  * @date 01/2014
  *
  */
#include "CImg.h"
#include <math.h>
#include <ctime>
#include <iostream>
#include <vector>

using namespace cimg_library;

/**
 * @brief Gaussian Kernel function
 *
 * @param x : First vector
 * @param y : Second vector
 * @param sigma : Gaussian Kernel dispersion
 *
 * @return The kernel value
 */
double Kernel(double x, double y, double sigma)
{   
    return exp(-1 * (pow(x - y, 2)) / pow(sigma, 2));
}

 /** 
 * @brief Update classes vector
 *
 * @param img : Base image 
 * @param U : Distribution matrix
 * @param V : Classes vector
 * @param m : Weight
 * @param nClasses : Number of classes
 * @param sigma : Gaussian Kernel dispersion
 */
void updateV(CImg<> &img, CImg<> &U, std::vector<double> &V, int nClasses, int m, double sigma)
{
	double num, denum, tmp_val;
    
    cimg_forZ(U, z)
    {
		num = 0;
		denum = 0;
		cimg_forXY(U, x, y)
		{
			tmp_val = pow(U(x, y, z), m) * Kernel(img(x, y, 0), V[z], sigma);
			num += tmp_val * img(x, y, 0);
			denum += tmp_val;
		}
		V[z] = num / denum;
		
		// Debug
		//std::cout << "V[" << z << "] = " << V[z] << " (" << num << " / " << denum << ")" << std::endl;
	}
}


/** 
 * @brief Update distribution matrix
 *
 * @param img : Base image 
 * @param U : Distribution matrix
 * @param V : Classes vector
 * @param m : Weight
 * @param Nr : Neighbors number
 * @param alpha : Neighborhood weight
 * @param nClasses : Number of classes
 * @param sigma : Gaussian Kernel dispersion
 */
void updateU(CImg<> &img, CImg<> &U, std::vector<double> &V, int m, int Nr, int alpha, int nClasses, double sigma)
{
	//
	CImg<> sumClassU(img.width(), img.height(), 1, 1, 0);
	// Neighborhood
	CImg_3x3(I,float);
	double sum, num;
    
	cimg_forZ(U, z)
	{
		cimg_for3x3(U, x, y, z, 0, I, float)
		{
			sum = pow(1 - Ipp,m) + pow(1 - Icp,m) + pow(1 - Inp,m) + pow(1 - Ipc,m) + pow(1 - Inc,m) + pow(1 - Icn,m) + pow(1 - Ipn,m) + pow(1 - Inn,m);
			num = pow((1 - Kernel(img(x, y), V[z], sigma)) + (alpha / Nr) * sum ,-1 / (m - 1));
			U(x, y, z) = num;
		}
	}

	cimg_forXY(U, x, y)
	{
		cimg_forZ(U, z)
		{
			sumClassU(x, y) += U(x, y, z);
		}
		cimg_forZ(U, z)
		{
			U(x, y, z) = U(x, y ,z) / sumClassU(x, y);
		}
	}	
}

/**
 * @brief Reconstruction of segmented image
 * 
 * @param img : Base image 
 * @param U : Distribution matrix
 * @param V : Classes vector
 * @param nClasses : Number of classes
 * @param exclusive : true for an exclusive image reconstruction, false otherwise
 *
 * @return The segmented image
 */
CImg<> makeFinalImage(CImg<> &img, CImg<> &U, std::vector<double> &V, int nClasses, bool exclusive)
{
    CImg<> final_img(img.width(), img.height());
    int iClass;
    double iClassValue, greyValue;
    
    if(exclusive)
    {
    	// Exclusive reconstruction
		cimg_forXY(img, x, y)
		{
			iClass = 0;
			iClassValue = 0;
			cimg_forZ(U, z)
			{
				if (U(x, y, z) > iClassValue)
				{
					iClassValue = U(x, y, z);
					iClass = z;
				}
			}
			final_img(x, y) = V[iClass];
		}
	}
	else
	{
		// Shared reconstruction
		cimg_forXY(img, x, y)
		{
			greyValue = 0;
			cimg_forZ(U, z)
			{
				greyValue += V[z] * U(x, y, z);
			}
			final_img(x, y) = greyValue;
		}
	}
    
    return final_img;
}

/**
 * @brief Function to compute SKFCM
 * 
 * @param img : Base image 
 * @param exclusive : true for an exclusive image reconstruction, false otherwise
 * @param epsilon : Computer precision
 * @param tMax : Maximum number of iterations
 * @param alpha : Neighborhood weight
 * @param nClasses : Number of classes
 * @param sigma : Gaussian Kernel dispersion
 *
 * @return The segmented image
 */
CImg<> skfcm(CImg<> &img, double sigma, int nClasses, int m, double alpha, int tMax, double epsilon, bool exclusive)
{
    
    // Neighbors number
    int Nr = 8;
    // Iterations index
    int t = 0;
    
    // Debug section
    std::cout << std::endl << "Starts SKFCM algorithm with parameters : " << std::endl;
    std::cout << "> Number of classes : " << nClasses << std::endl;
    std::cout << "> Number of iterations : " <<  tMax << std::endl;
    std::cout << "> Epsilon : " <<  tMax << std::endl;
    std::cout << "> Result type : " << (exclusive ? "Exclusive" : "Shared") << std::endl;
    
    // Creation of distribution Matrix
    CImg<> U(img.width(), img.height(), nClasses, 1, 0);
    CImg<> oldU(img.width(), img.height(), nClasses, 1, 0);
    // Creation of classes vector
    std::vector<double> V(nClasses);
          
    // Distribution Matrix initialization (Uik)
    std::cout << "U init ... " << std::flush;
    //Set a one value for a class
    cimg_forXYZ(U, x, y, z)
	{
		int index = rand() % nClasses;
		U(x, y, z) = (z == index) ? 1 : 0;
	}
    std::cout << "DONE" << std::endl;
    
    // Classes vector initialization
    std::cout << "V init ... " << std::flush;
    for (int i = 0; i < nClasses; ++i)
    {
		V[i] = 255 / nClasses;
    }
    std::cout << "DONE" << std::endl;
    
    // Iteration
    double maxIk;
    do
	{
		std::cout << "Starts iteration " << t << std::endl;

		// Copy old U img
		oldU = U;

		// Vi iterations
		std::cout << "Manage V ... ";
		updateV(img, U, V, nClasses, m, sigma);
		std::cout << "DONE" << std::endl;

		// Manage Uik using oldV
		std::cout << "Manage U ... ";
		updateU(img, U, V, m, Nr, alpha, nClasses, sigma);
		std::cout << "DONE" << std::endl;

		// Stop test
		maxIk = (oldU - U).abs().max();
		std::cout << "Iteration ended with maxIk = " << maxIk << std::endl;

    } while(t++ < tMax && maxIk > epsilon);

    return makeFinalImage(img, U, V, nClasses, exclusive);
}

/// Main function
int main()
{
    // Sigma max
    double sigma = 100;
    // Number of classes
    int nClasses = 4;
    // Maximum of iterations
    int tMax = 250;
    // Epsilon
    double epsilon = 1e-7;
    // Weight
    int m = 2;
    // Neighborhood weight
    double alpha = 4;

    // Initialize seed for rand
    // The seed is fixed because the results must be reproducible
    // WARNING : Unix rand is a simple linear congruential random, that's bad for a scientific usage,
    // a better pseudo random generator should be used, as Mersenn Twister
    srand(4567890);

    // Base image
    CImg<> img = CImg<>("../images/test_1.bmp").channel(0);
    CImgDisplay dispImg(img, "Original image");

    // Exclusive result, a pixel belongs to only one class
    CImg<> exclusive = skfcm(img, sigma, nClasses, m, alpha, tMax, epsilon, true);
    CImgDisplay dispExclusive(exclusive, "Exclusive segmentation");
    exclusive.normalize(0, 255).save("exclusive.bmp");

    // Shared result, a pixel belongs to one class or more
    CImg<> shared = skfcm(img, sigma, nClasses, m, alpha, tMax, epsilon, false);
    CImgDisplay dispShared(shared, "Shared segmentation");
    shared.normalize(0, 255).save("shared.bmp");
    
    // Wait for the base image to be closed
    while (!dispImg.is_closed())
    {
        dispImg.wait();
    }

    return 0;
}
