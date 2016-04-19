
#include "stdio.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"

using namespace std;

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos){
   cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES,pos);
}


IplImage* doPyrDown(IplImage* in,int filter = IPL_GAUSSIAN_5x5) {
   assert( in->width%2 == 0 && in->height%2 == 0 );
   IplImage* out = cvCreateImage(cvSize( in->width/2, in->height/2 ),in->depth,in->nChannels);
   cvPyrDown( in, out );
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
      cvShowImage( "Example5-out", doPyrDown(frame,IPL_GAUSSIAN_5x5) );
      char c = cvWaitKey(33);
      if( c == 27 ) break;
   }
   cvReleaseCapture( &g_capture );
   cvDestroyWindow( "Example5" );
}

