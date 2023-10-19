//需要opencv库
#include <opencv2/opencv.hpp>

#include <string>

//计算时间
#include <chrono>  

using namespace std;


int main(int argc, char **argv){	
	//获取视频图像
	cv::VideoCapture cap("rtsp://192.168.50.46:8554"); //如果使用的是USB相机，将该参数修改成接口名称，如：0，1
	
	//记录系统时间
	auto start = chrono::system_clock::now();

	while(1){
		cv::Mat frame;
		cap >> frame;  //读取相机数据
		if(frame.data == nullptr)
			break;
		

		cv::Mat frame_resized;
		cv::resize(frame, frame_resized, cv::Size(960,540));//运行时显示的视频的尺寸

		cv::imshow("llvision",frame_resized);
		cv::waitKey(1);
	}

	return 0;
}
