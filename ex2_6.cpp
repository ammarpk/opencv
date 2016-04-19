#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.h"

#include "stdio.h"
#include "unistd.h"
using namespace cv;

using namespace std;

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos){
   cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES,pos);
}


IplImage* doCanny(IplImage* in,double lowThresh, double highThresh, double aperture) 
{
   if(in->nChannels != 1)
      return(0); //Canny only handles gray scale images
   IplImage* out = cvCreateImage(cvGetSize(in),IPL_DEPTH_8U,1);
   cvCanny( in, out, lowThresh, highThresh, aperture );
   return( out );
};

int main( int argc, char** argv ) {
   cvNamedWindow( "Example5", CV_WINDOW_AUTOSIZE );
   cvNamedWindow( "Example5-out", CV_WINDOW_AUTOSIZE );
   g_capture = cvCreateFileCapture( argv[1] );
   int frames= (int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
   
   if(frames!=0)
      cvCreateTrackbar("Position","Example5",&g_slider_position,frames,onTrackbarSlide);

   IplImage* frame;
   while(1) {
      frame = cvQueryFrame( g_capture );
      if( !frame ) break;
      cvShowImage( "Example5", frame );
      IplImage* gray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
      cvCvtColor(frame, gray, COLOR_BGR2GRAY);

      cvShowImage( "Example5-out", doCanny(gray,10,30,3) );
      char c = cvWaitKey(33);
      if( c == 27 ) break;
      sleep(2);
   }
   cvReleaseCapture( &g_capture );
   cvDestroyWindow( "Example5" );
}

