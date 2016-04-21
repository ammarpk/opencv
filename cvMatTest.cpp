#include "opencv/highgui.h"
#include "iostream"

using namespace std;
int main( int argc, char** argv ) {
   int vals[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
   CvMat cvmat1;
   cvInitMatHeader(&cvmat1,4,4,CV_32SC1,vals);
   for (int i=0;i<4;i++){
      for (int j=0;j<4;j++){
         int val= CV_MAT_ELEM(cvmat1,unsigned int,i,j);
         cout << val << endl;
      }
   }

}
