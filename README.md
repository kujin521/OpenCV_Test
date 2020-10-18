> 信息科学与电气工程学院上机实验报告（电子版）

学号： 190863119 姓名： 库金 班级: 计升191

课程： 数字图像处理 指导教师: 李克锋 时间: 2020年 10 月 18 日

1.  实验名称

    实验四 图像增强

2.  实验目的

    实现图像的线性对比度展宽，非线性动态范围调整，直方图均衡，以及伪彩色增强中的密度分层法和灰度变换法。

3. 实验内容

   1. 线性对比度展宽

      ```c++
      void CDemo2Dlg::OnBnClickedLinear()
      {
      	// 线性对比度展宽
      	if (src.empty()) {
      		AfxMessageBox(_T("请先打开图像! "));
      	}
      
      	Mat g_src,dst;
      	cvtColor(src, g_src, CV_BGR2GRAY);
      	dst.create(src.size(), g_src.type());
      
      	UpdateData(TRUE);
      
      	if (m_a < 0 || m_b>255 || m_ga < 0 || m_gb>255) {
      		AfxMessageBox(_T("灰度范围有误! "));
      		return;
      	}
      
      	for (int i = 0;i < g_src.rows;i++) {
      		for (int j = 0;j < g_src.cols;j++) {
      			int tmp = g_src.at<uchar>(i, j);
      			if (tmp < m_a) {
      				dst.at<uchar>(i, j) = (tmp - m_a) * (m_gb - m_ga) / (m_b - m_a) + m_ga;
      			}
      			else if (tmp < m_b) {
      				dst.at<uchar>(i, j) = (tmp - m_a) * (m_gb - m_ga) / (m_b - m_a) + m_ga;
      			}
      			else {
      				dst.at<uchar>(i, j) = (tmp - m_gb) * (255 - m_gb) / (255 - m_b) + m_gb;
      			}
      		}
      	}
      
      	imshow("线性对比度展宽", dst);
      }
      ```

      

   2. 非线性动态范围调整

      ```c++
      void CDemo2Dlg::OnBnClickedNonlinear()
      {
      	// 非线性动态范围调整
      	if (src.empty()) {
      		AfxMessageBox(_T("请先打开图像! "));
      	}
      
      	Mat g_src, dst;
      
      	cvtColor(src, g_src, CV_BGR2GRAY);
      	dst.create(src.size(), g_src.type());
      
      	for (int i = 0;i < g_src.rows;i++) {
      		for (int j = 0;j < g_src.cols;j++) {
      			int tmp = g_src.at<uchar>(i, j);
      			dst.at<uchar>(i, j) = tmp * log10((float)(1 + tmp));
      		}
      	}
      
      	imshow("非线性动态范围调整", dst);
      
      }
      ```

   3. 直方图均衡

      ```c++
      void CDemo2Dlg::OnBnClickedHisteq()
      {
      	// 直方图均衡
      	if (src.empty()) {
      		AfxMessageBox(_T("请先打开图像! "));
      	}
      
      	Mat g_src, dst;
      
      	cvtColor(src, g_src, CV_BGR2GRAY);
      	dst.create(src.size(), g_src.type());
      
      	equalizeHist(g_src, dst);
      
      	imshow("直方图均衡", dst);
      }
      ```

   4.  伪彩色增强

       ```c++
   void CDemo2Dlg::OnBnClickedPseudo()
       {
   	// 伪彩色增强
       	if (src.empty()) {
   		AfxMessageBox(_T("请先打开图像! "));
       	}
       
       	Mat g_src, dst;
       
       	cvtColor(src, g_src, CV_BGR2GRAY);
       	dst.create(src.size(), CV_8UC3);
       
       	UpdateData(TRUE);
       
       	switch (m_pseudoMode) {
       	case 0://密度分层法
       		for (int i = 0;i < g_src.rows;i++) {
       			for (int j = 0;j < g_src.cols;j++) {
       				int tmp = g_src.at<uchar>(i, j);
       				if (tmp < 64) {
       					dst.at<Vec3b>(i, j)[0] = 255; //blue
       					dst.at<Vec3b>(i, j)[1] = 0; //green
       					dst.at<Vec3b>(i, j)[2] = 0; //red
       				}
       				else if (tmp < 192) {
       					dst.at<Vec3b>(i, j)[0] = 0; //blue
       					dst.at<Vec3b>(i, j)[1] = 255; //green
       					dst.at<Vec3b>(i, j)[2] = 0; //red
       				}
       				else {
       					dst.at<Vec3b>(i, j)[0] = 0; //blue
       					dst.at<Vec3b>(i, j)[1] = 0; //green
       					dst.at<Vec3b>(i, j)[2] = 255; //red
       				}
       			}
       		}
       		break;
       	case 1:
       		for (int i = 0;i < g_src.rows;i++) {
       			for (int j = 0;j < g_src.cols;j++) {
       				int tmp = g_src.at<uchar>(i, j);
       				if (tmp < 64) {
       					dst.at<Vec3b>(i, j)[0] = 255; //blue
       					dst.at<Vec3b>(i, j)[1] = tmp*255/64; //green
       					dst.at<Vec3b>(i, j)[2] = 0; //red
       				}else if (tmp < 128) {
       					dst.at<Vec3b>(i, j)[0] = (127-tmp)*4; //blue
       					dst.at<Vec3b>(i, j)[1] = 255; //green
       					dst.at<Vec3b>(i, j)[2] = 0; //red
       				}
       				else if (tmp < 192) {
       					dst.at<Vec3b>(i, j)[0] = 0; //blue
       					dst.at<Vec3b>(i, j)[1] = 255; //green
       					dst.at<Vec3b>(i, j)[2] = (tmp-127)*4; //red
       				}
       				else {
       					dst.at<Vec3b>(i, j)[0] = 0; //blue
       					dst.at<Vec3b>(i, j)[1] = tmp * 256 / 64; //green
       					dst.at<Vec3b>(i, j)[2] = 255; //red
       				}
       			}
       		}
       		break;
       	}
       
       	imshow("非线性动态范围调整", dst);
       }
       ```
       
       （过程或步骤、程序代码、运行结果、反映实验成果的截屏等，根据课程不同，以上内容可有所侧重或取舍）

4.  总结

    1.  对比度展宽:降低图像不重要的信息对比度 实现图片效果增强

    2.  非线性动态调整:利用人眼的视觉特性,将动态范围进行压缩,将感兴趣区的变化范围扩大,从而达到改善图像质量的目的

    3.  直方图均衡化:利用直方图对比度进行调整 在实际中经常使用归一化直方图

    4.  伪彩色增强:根据特定的准则对图像的灰度值赋予彩色处理

        1.  密度分层

        2.  灰度变换

            通过本次实验了解了数字图像处理 经过不同的算法对图像进行增强 达到人们想要的效果,

            注：上机实验指实验地点在信电学院计算中心的上机，留存电子版即可。

github地址: https://github.com/kujin521/OpenCV_Test/tree/%E5%AE%9E%E9%AA%8C4
