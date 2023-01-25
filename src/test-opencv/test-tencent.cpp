#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

#include <opencv2/wechat_qrcode.hpp>
int main() 
{
	const std::string modelDir = "/root/computer-vision/opencv_3rdparty/";
	 
	// 构造（使用异常捕获构造函数是否正常）
	/*wechat_qrcode::WeChatQRCode detector{
        modelDir + "detect.prototxt", 
        modelDir + "detect.caffemodel",
        modelDir + "sr.prototxt",     
        modelDir + "sr.caffemodel"
    };*/

    
   Ptr<wechat_qrcode::WeChatQRCode> detector;
    

    detector = makePtr<wechat_qrcode::WeChatQRCode>(
        modelDir + "detect.prototxt", 
        modelDir + "detect.caffemodel",
        modelDir + "sr.prototxt",     
        modelDir + "sr.caffemodel"        
    );
    // 临时变量
    Mat img;
	vector<Mat> points;   // qrcode: Retangle, not RotatedBox
	
    //auto camIdx = 0; 
    auto camIdx = "/root/computer-vision/test-opencv/pictures/1.png";
   
    VideoCapture cap(camIdx);

    printf("here\n");
    while(cap.read(img)){
    	// 检测
       	auto res = detector->detectAndDecode(img, points); 
       	// 结果叠加
       	for(size_t idx = 0; idx < res.size(); idx ++){
			Point pt1 = points[idx].at<Point2f>(0);
			Point pt2 = points[idx].at<Point2f>(2);
	        Rect rect{pt1, pt2};
	        Point center = (pt1 + pt2) / 2;
			// 绘制矩形框
	        rectangle(img, rect, {0,0,255}, 2);
	        circle(img, center, rect.height / 15, {0,0,255}, -1);
			// 解码字符串
	        putText(img, res[idx], {pt1.x, pt2.y + 16}, 1, 1, {0,0,255});    
        }

        printf("here\n");
		imshow("image", img);
        waitKey(0);
    }
    return 0;
}
