

#include "opencv/cv.h"
#include "opencv/highgui.h"

int g_slider_position = 0;
CvCapture* g_capture = NULL;

void onTrackbarSlide(int pos){
   cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES,pos);
}

int main( int argc, char** argv ) {
   cvNamedWindow( "Example4-in", CV_WINDOW_AUTOSIZE );
   cvNamedWindow( "Example4-out" );
   g_capture = cvCreateFileCapture( argv[1] );
   int frames= (int)cvGetCaptureProperty(g_capture,CV_CAP_PROP_FRAME_COUNT);
   
   if(frames!=0)
      cvCreateTrackbar("Position","Example3",&g_slider_position,frames,onTrackbarSlide);

   IplImage* frame;
   while(1) {
      frame = cvQueryFrame( g_capture );
      if( !frame ) break;
      cvShowImage( "Example4-in", frame );
      IplImage* out = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
      cvSmooth( frame, out, CV_GAUSSIAN, 3, 3 );
      cvShowImage( "Example4-out", out );
      char c = cvWaitKey(33);
      if( c == 27 ) break;
   }

   cvReleaseCapture( &g_capture );
   cvDestroyWindow( "Example4-in" );
   cvDestroyWindow( "Example4-out" );
}

