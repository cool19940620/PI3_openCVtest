//g++ simpletest_raspicam_cv.cpp -o simpletest_raspicam_cv -I/usr/local/include/ -lraspicam -lraspicam_cv -lopencv_core -lopencv_highgui
#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
using namespace std; 
using namespace cv;
int main ( int argc,char **argv ) 
{
  time_t timer_begin,timer_end;
  raspicam::RaspiCam_Cv Camera;
  cv::Mat image;
  int nCount=100;
  
  //set camera params
  Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
  Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640 );
  Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480 );
  
  
  //Open camera
  cout<<"Opening Camera..."<<endl;
  if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
  
  //Start capture
  cout<<"Capturing "<<nCount<<" frames ...."<<endl;
  time ( &timer_begin );
  for ( int i=0; i<nCount; i++ ) 
  {
    Camera.grab();
    Camera.retrieve ( image);
    
    cv::namedWindow("test", CV_WINDOW_AUTOSIZE);//CV_WINDOW_NORMAL
    cv::imshow("test", image);
    waitKey(1);
    
    if ( i%5==0 ) cout<<"\r captured "<<i<<" images"<<std::flush;
  }
  cout<<"Stop camera..."<<endl;
  Camera.release();
  
  //show time statistics
  time ( &timer_end ); /* get current time; same as: timer = time(NULL) */
  double secondsElapsed = difftime ( timer_end,timer_begin );
  cout<< secondsElapsed<<" seconds for "<< nCount<<" frames : FPS = "<< ( float ) ( ( float ) ( nCount ) /secondsElapsed ) <<endl;
  
  //save image 
  cv::imwrite("raspicam_cv_image.jpg",image);
  cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
  
  /*cv::namedWindow("test", CV_WINDOW_NORMAL);
  cv::imshow("test", image);
  waitKey(0);*/
}