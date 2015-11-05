
#include <iostream>
#include <fstream>
using namespace std;

void print_matrix(size_t **NM, size_t n){
  for(size_t i=0; i<n; ++i){
    for(size_t j=0; j<n; ++j)
      cout << NM[i][j] << " ";
    cout << endl;
  }
  //cout << endl;
}

size_t **transpose(size_t ** NM, size_t n){
  size_t **MN = new size_t*[n];
  for(size_t i = 0; i<n; ++i){
      MN[i] = new size_t[n];
      for(size_t j = 0; j<n; ++j)
        MN[i][j] = NM[j][i];
    }
  return MN;
}

int _01K(){
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);

  ifstream in("D:\\pgm\\Qt\\Tools\\QtCreator\\bin\\CSC1stContest\\input");

  size_t n=0, m=0;
  in >> n >>m;

  size_t **A = new size_t*[n];
  size_t **B = new size_t*[n];
  size_t **C = new size_t*[n];

  //A
  for(int i = 0; i<n; ++i){
      A[i] = new size_t[n];
      for(size_t j = 0; j<n; ++j)
        in >> A[i][j];
    }

  //B
  for(size_t i = 0; i<n; ++i){
      B[i] = new size_t[n];
      for(size_t j = 0; j<n; ++j)
        in >> B[i][j];
    }

  size_t **TB = transpose(B, n);
  size_t c = 0, m2 = m*m;
  size_t *Ai, *TBj;
  for(size_t i = 0; i<n; ++i){
      C[i] = new size_t[n];
      for(size_t j = 0; j<n; ++j){
          c=0;
          Ai = A[i];
          TBj = TB[j];
          for(size_t l = 0; l<n; l++){
              c+= Ai[l]*TBj[l];
              if(c>=m2) c-=m2;
          }
          C[i][j] = c%m;
        }
    }

  in.close();
  print_matrix(A, n);
  print_matrix(TB, n);
  print_matrix(C,n);

  return 0;
}
