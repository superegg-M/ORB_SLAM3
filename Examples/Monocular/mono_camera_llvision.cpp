//需要opencv库
#include <opencv2/opencv.hpp>

//ORB_SLAM的系统接口
#include <System.h>

#include <string>
//计算时间
#include <chrono>   
#include <iostream>

using namespace std;

//如果系统的路径不同，需要修改路径
string parameterFile = "./mono_camera_llvision.yaml";
string vocFile = "./../../Vocabulary/ORBvoc.txt";

//视频文件，该示例中视频文件存放在/Workspace/src/ORB_SLAM3/Examples/Monocular下
string videoFile = "./video.mp4";

int main(int argc, char **argv){
	//声明ORB_SLAM3系统
	ORB_SLAM3::System SLAM(vocFile, parameterFile, ORB_SLAM3::System::MONOCULAR, true);
	
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
		
		auto now = chrono::system_clock::now();
		auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
		SLAM.TrackMonocular(frame_resized, double(timestamp.count())/1000.0);
		cv::waitKey(1);
	}
	SLAM.Shutdown();
	return 0;
}
