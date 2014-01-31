SKFCM-Algorithm
===============

Implementation of the SKFCM image segmentation algorithm

## Authors

This project was developped by Arriaza Maxime & Kevin Renella.

## Subject presentation

Image segmentation plays a crucial role in many areas of medical imaging. We have implemented a solution for segmenting image from the article [31] Dao-Qiang Zhang and Chen Song-Can, researchers from the Chinese Academy of Sciences (coupled to the computer department of the Chinese University of Aeronautics and astronautics). 

The image processing method presented in this article, Spatially constrained KFCM (SKFCM) allows an image segmentation fuzzy regions, inspired by the Fuzzy C-Means method (FCM), but using a distance induced by a kernel function (from vector machines support or SVM), and a consideration of the neighborhood by the introduction of spatial constraints in the objective function of FCM.

## Theory

It is first necessary to define what a fuzzy set.

A fuzzy set is a set whose edges are poorly defined. 
This results to a membership function values ​​in [0,1], as opposed to the conventional case where the membership function takes two values ​​0 or 1. This allows to define sets of a more flexible manner, tolerant inaccurate, incomplete and / or uncertain.

This property is exploited by image processing, and more precisely in classification where the classes, also known as regions are represented by fuzzy sets. This is useful when the regions can not be defined clearly and precisely. 
Their handling gradant the vagueness can handle imprecise data, uncertain and / or redundant in a more flexible manner.

Fuzzy clustering allows overlapping classes (also called regions). 
A non-fuzzy segmentation can be obtained by assigning each pixel to the class for which its membership degree is maximum.

The algorithm of the Fuzzy C-Means (FCM) is a fuzzy clustering algorithm based on optimization of a quadratic criterion of classification where each class is represented by its center of gravity. The algorithm requires knowing the number of classes in advance and generates classes itératiff process by minimizing an objective function. Thus, it provides a fuzzy partition of the image by giving each pixel a degree of membership in a given region.

## Results

Base image :
![Alt text](/images/brain_2.bmp "RMI brain")

Segmented image with exclusive solution :
![Alt text](/images/brain_2_exclusive.bmp "RMI brain exclusive segmented")


The SKFCM algorithm provides a segmented image noised and respecting the fuzzy regions of the original image.
Indeed, this aspect is very well represented by the picture of the fish. In the original image can be difficult to distinguish caudal fins of fish.
With SKFCM algorithm, fuzzy segmentation and reconstruction help highlight these fins on the processed image.

On MRI images taken in recent appear slightly noisy. It is for this reason that conventional segmentation methods as FCM does not allow a clear image segmentation. 
However, algortihme SKFCM provides a clear segmented image from an image with Gaussian noise characteristic of catches taken by magnetic resonance. That is why this method seems very appropriate for this kind of images, particularly useful for the detection of tumors in the brain.

## References

[1] Pham D.L, Xu C.Y, Prince J.L. A survey of current methods in medical image segmentation.
Annual Review of Biomedical Engineering, Annual Reviews, vol. 2, pp. 315-337, 2000.
[Technical report version, JHU/ECE 99-01, Johns Hopkins University]

            [2] Wells W.M, Grimson W.E.L, Kikinis R. and Arrdrige S.R. Adaptive segmentation of MRI data. IEEE Trans. Medical. Imaging., vol. 15, pp.429-442, 1996

            [3] Bezdek J.C, Hall L.O, and Clarke L.P. Review of MR image segmentation techniques using pattern recognition. Medical Physics, vol.20, pp.1033-1048, 1993

            [4] J.C. Bezdek. Pattern Recognition with Fuzzy Objective Function Algorithms. Plenum Press, New York, 1981

            [5] Dawant B.M, Zijidenbos, A.P., and Margolin, R.A. Correction of intensity variations in MR image for computer-aided tissue classification. IEEE Trans. on Medical Imaging, vol. 12, pp.770-781, 1993

            [6] Johnson B., Atkins M.S., Mackiewich B., and Andson M. Segmentation of multiple sclerosis lesions in intensity corrected multispectral MRI. IEEE Trans. on Medical Imaging, vol. 15, pp.154-169, 1996

            [7] Pham D.L and Prince J.L. An adaptive fuzzy C-means algorithm for image segmentation inthe presence of intensity inhomogeneities. Pattern Recognition Letters. vol. 20, no.1, pp.57-68, 1999

            [8] Tolias Y.A and Panas S.M. On applying spatial constraints in fuzzy image clustering using a fuzzy rule-based system. IEEE Signal Processing Letters, vol.5,no.10,pp.245-247, 1998

            [9] Tolias Y.A and Panas S.M. Image segmentation by a fuzzy clustering algorithm using adaptive spatially constrained membership fucntions. IEEE Trans. on Systems, Man, and Cybernetics-Part A,vol.28, no.3, pp.359-369, 1998

            [10] Liew A.W.C. Leung S.H. and Lau W.H. Fuzzy image clustering incorporating spatial continuity. IEE Proc.-Vis. Image Signal Process., vol. 147, no.2, pp. 185-192, 2000

            [11] Ahmed M.N, Yamany SM, Mohamed N, Farag AA, and Moriarty T. A modified fuzzy C-means algorithm for bias field estimation and segmentation of MRI data. IEEE Trans. on Medical Imaging, vol.21, no.3, pp.193-199, 2002

            <li>[12] Pham D.L. Fuzzy clustering with spatial constraints. In: Proceedings of the IEEE International Conference on Image Processing, New York, USA, August, 2002</li>

            [13] Muller K.R., Mika S., et al. An Introduction to Kernel-based Learning algorithms. IEEE Trans. Neural Networks, vol.12, no. 2, pp.181-202, 2001

            [14] Cristianini N, Taylor J S. An Introduction to SVMs and other kernel-based learning methods. Cambridge Univ. Press, 2000

            [15] Vapnik V.N. Statistical learning theory. Wiley, New York, 1998

            [16] Scholkopf B. Support vector learning. R. Oldenbourg Verlay, 1997

            [17] Roth V and Steinhage. Nonlinear discriminant analysis using kernel functions. In: Advances in Neural Information Processing Systems vol. 12, pp.568-574, 2000

            [18] Scholkopf B, Smola A J, Muller K R. Nonlinear component analysis as a kernel eigenvalue problem. Neural Computation, vol. 10, no. 5, pp.1299-1319, 1998

            [19] Cover T.M., Geometrical and statistical propertyes of systems of linear inequalityies in pattern recognition, IEEE Trans. Electron. Comput. Vol.14, pp.326-334, 1965.

            [20] Girolami M. Mercer kernel-based clustering in feature space. IEEE Trans. Neural Networks, vol. 13, no. 3, pp.780-784, 2002

            <li>[21] Zhang D.Q and Chen S.C. Fuzzy clustering using kernel methods. In: Procedings of the International Conference on Control and Automation, Xiamen, China, June, 2002

            [22] Wu K.L. and Yang M.S. Alternative c-means clustering algorithms, Pattern Recognition. vol. 35, pp. 2267-2278, 2002

            [23] Huber P J. Robust statistics. Wiley, New York, 1981

            [24] Chapelle O., Haffner P. and Vapnik V. Svms for histogram-based image classification. IEEE Trans. on Neural Networks, vol. 10, no. 5, pp.1055--1065, 1999

            [25] Kwan R.K.S., Evans A.C, Pike G.B. An Extensible MRI Simulator for Post-Processing Evaluation. Visualization in Biomedical Computing (VBC'96). Lecture Notes in Computer Science, vol. 1131, pp.135-140, Springer-Verlag, 1996.

            [26] Hur A.B, Horn D,Siegelmann H.T, Vapnik V. Support vector clustering. Journal of Machine Learning Research, vol.2, pp.125-137, 2001

            [27] Leski J. Towards a robust fuzzy clustering. Fuzzy Sets and Systems. In Press, Corrected Proof, Available online 8 February 2003

            [28] Lin C.T, Lee C.S.G. Real-time supervised structure/parameter learning for fuzzy neural network. In: Proc. of 1992 IEEE Int'l Conf. on Fuzzy Systems, San Diego, CA, pp. 1283-1290, 1992

            [29] Masulli F, Schenone A. A fuzzy clustering based segmentation system as support to diagnosis in medical imaging. Artificial Intelligence in Medicine, vol. 16, no.2, pp. 129-147, 1999

            [30] Dave R.N, Krishnapuram R. Robust clustering method: a unified view. IEEE Trans. Fuzzy Systems. vol.5,no.2, pp.270-293,1997

            [31] A novel kernelized fuzzy C-means algorithm with application in medical image segmentation, Dao-Qiang Zhang, and Song-Can Chen, 2004

## Licence
>The MIT License
>
>Copyright (c) 2012, Daniel Petisme
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in
> all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
> THE SOFTWARE.
