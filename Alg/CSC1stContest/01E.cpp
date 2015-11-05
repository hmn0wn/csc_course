#include <iostream>
#include <fstream>
using namespace std;

void print_matrix(size_t **NM, size_t n, size_t m){
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j)
      cout << NM[i][j] << " ";
    cout << endl;
  }
  //cout << endl;
}

size_t **transpose(size_t ** NM, size_t n, size_t m){
  size_t **MN = new size_t*[m];
  for(int i = 0; i<m; ++i){
      MN[i] = new size_t[n];
      for(int j = 0; j<n; ++j)
        MN[i][j] = NM[j][i];
    }
  return MN;
}

int _01E(){
  //ios_base::sync_with_stdio(0);
  //cin.tie(0);

  ifstream in("D:\\pgm\\Qt\\Tools\\QtCreator\\bin\\CSC1stContest\\input");

  size_t n=0, m=0, k=0;
  in >> n >> m >> k;

  size_t **A = new size_t*[n];
  size_t **B = new size_t*[m];
  size_t **C = new size_t*[n];

  //A
  for(int i = 0; i<n; ++i){
      A[i] = new size_t[m];
      for(int j = 0; j<m; ++j)
        in >> A[i][j];
    }

  //B
  for(int i = 0; i<m; ++i){
      B[i] = new size_t[k];
      for(int j = 0; j<k; ++j)
        in >> B[i][j];
    }

  size_t **TB = transpose(B, m, k);
  size_t c = 0;
  size_t *Ai, *TBj;
  for(int i = 0; i<n; ++i){
      C[i] = new size_t[k];
      for(int j = 0; j<k; ++j){
          c=0;
          Ai = A[i];
          TBj = TB[j];
          for(int l = 0; l<m; l++)
            c+= Ai[l]*TBj[l];
          C[i][j] = c;
        }
    }

  in.close();
  print_matrix(A, n, m);
  print_matrix(TB, k, m);
  print_matrix(C,n,k);

  return 0;
}
