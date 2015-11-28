#include <iostream>
using namespace std;

int _01F(){
  int A=0, B=0, x=0, y=0;

  cin >> A >> B;
  //int Xl = (1-B*10000)/A;
  //int Xr = (1+B*10000)/A;
  for(x = -10000; x<10000; ++x){
    y=(int)((1-A*x)/B);
    if(x*A+y*B==1) {
        break;
      }
  }

  if(x*A+y*B!=1) { x=0; y=0;}
  cout << x <<" "<< y << endl;
  cout << x*A + y*B << endl;
}
