#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
    cv::Mat frame;
    // 可从摄像头输入视频流或直接播放视频文件
    //cv::VideoCapture capture(0);
    cv::VideoCapture capture;

    //capture = cv::VideoCapture("rtsp://admin:a12345678@192.168.0.64/main/Channels/0");
    capture = cv::VideoCapture("rtsp://admin:a12345678@192.168.0.64/h264/ch1/sub/av_stream");
     
//capture = cv::VideoCapture(0);
//capture = cv::VideoCapture("rtsp://admin:a12345678@192.168.0.64/main/Channls/0");

///main/Channels/1

    double fps;
    char string[10];  // 用于存放帧率的字符串
    namedWindow("Camera FPS", cv::WINDOW_AUTOSIZE);
    double t = 0;
double tsum = 0;
int cfps = 0;
double cmp=1.0;

int stopped = -1;

    while (stopped == -1)
    {
        t = (double)cv::getTickCount();
        //if (cv::waitKey(50) == 30){ break; }
        if (capture.isOpened())
        {
            //capture >> frame;
	    bool result = capture.read(frame);
if(result == true){
cfps++;
}
            // getTickcount函数：返回从操作系统启动到当前所经过的毫秒数
            // getTickFrequency函数：返回每秒的计时周期数
            // t为该处代码执行所耗的时间,单位为秒,fps为其倒数
            t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
            fps = 1.0 / t;
	    tsum = tsum + t;
//printf("fps: %d \n",cfps);
	    if(tsum > cmp)
		{
		printf("fps: %d\n",cfps);
		cfps = 0;
		tsum = 0;
		}


            sprintf(string, "%.2f", fps);      // 帧率保留两位小数
            std::string fpsString("FPS:");
            fpsString += string;                    // 在"FPS:"后加入帧率数值字符串

        int new_width,new_height,width,height,channel;
        width=frame.cols;
        height=frame.rows;
        channel=frame.channels();
        //cout<<width<<"  "<<height<<"  "<<channel<<endl;
 
        //调整图像大小
        new_width=200;
      
        new_height=int(new_width*1.0/width*height);
        if (frame.empty() == true)
{
                 continue;
}
        cv::resize(frame, frame, cv::Size(new_width, new_height));


            // 将帧率信息写在输出帧上
            cv::putText(frame, // 图像矩阵
                    fpsString,                  // string型文字内容
                    cv::Point(5, 20),           // 文字坐标，以左下角为原点
                    cv::FONT_HERSHEY_SIMPLEX,   // 字体类型
                    0.5, // 字体大小
                    cv::Scalar(255, 255, 255));       // 字体颜色


            cv::imshow("Camera FPS", frame);

	    int keycode = cv::waitKey(1) & 0xff ; //ESC键退出
            if (keycode == 27) break ;
		//printf("%f\n",fps);

        }
        else
        {
            std::cout << "No Camera Input!" << std::endl;
            break;
        }
    }
return 0;
}
