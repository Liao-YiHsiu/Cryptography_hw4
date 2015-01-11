#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/vec_ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/LLL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace NTL;

void readFile(char* fileName, ZZ &s, vec_ZZ &m);
void build(mat_ZZ &B, ZZ &s, vec_ZZ &m);
void print(mat_ZZ &M);
void print(ZZ &s, vec_ZZ &m);
bool check(mat_ZZ &B, ZZ &s, vec_ZZ &m, vector<int> &ans);

void Usage(char* progName){
   fprintf(stderr, "usage: %s knap.in\n", progName);
   exit(-1);
}

int main(int argc, char* argv[]){
   if(argc != 2)
      Usage(argv[0]);
   
   ZZ s, det2;
   vec_ZZ m;
   mat_ZZ B;
   vector<int> ans;

   readFile(argv[1], s, m);
   print(s, m);

   build(B, s, m);
   printf("\n\nBuild LLL matrix:\n");
   print(B);

   LLL(det2, B);
   printf("\n\nLLL results:\n");
   print(B);

   if(check(B, s, m, ans)){
      
      cout << endl << s << " = ";
      bool first = true;
      for(int i = 0; i < ans.size(); ++i)
         if(ans[i]){
            if(!first){
               cout << " + ";
            }
            cout << m[i];
            first = false;
         }
      cout << endl;
   }

   return 0;
}

void readFile(char* fileName, ZZ &s, vec_ZZ &m){
   ifstream fin(fileName);

   long long tmp;
   ZZ tmp_z;
   fin >> s;
   while(fin >> tmp){
      tmp_z = tmp;
      append(m, tmp_z);
   }
}

void build(mat_ZZ &B, ZZ &s, vec_ZZ &m){
   int N = m.length();
   B.SetDims(N + 1, N + 1);

   for(int i = 0; i < N; ++i)
      for(int j = 0; j < N; ++j){
         if(i == j)
            B[i][j] = 2;
         else
            B[i][j] = 0;
      }

   for(int i = 0; i < N; ++i)
      B[i][N] = m[i];

   for(int i = 0; i < N; ++i)
      B[N][i] = 1;

   B[N][N] = s;
}


void print(ZZ &s, vec_ZZ &m){
   cout << "S = " << s << endl 
      << "M = { "; 
   for(int i = 0; i < m.length(); ++i){
      if(i != 0)
         cout << ", ";
      cout << m[i];
   }
   cout << " }" << endl;
}

void print(mat_ZZ &M){
   int rows = M.NumRows();
   int cols = M.NumCols();
   for(int i = 0; i < rows; ++i){
      for(int j = 0; j < cols; ++j)
         cout << M[i][j] << "\t";
      cout << endl;
   }
}

bool check(mat_ZZ &B, ZZ &s, vec_ZZ &m, vector<int> &ans){
   int N = m.length();
   ZZ pos, neg;
   pos = 0; neg = 0;
   ans.clear();
   ans.resize(N, 0);

   if(B[0][N] != 0) return false;
   
   for(int i = 0; i < N; ++i){
      if(B[0][i] == 1)
         pos += m[i];
      else if(B[0][i] == -1)
         neg += m[i];
      else
         return false;
   }

   //cout << pos << " " << neg << " " << s << endl;
   if(pos == s){
      for(int i = 0; i < N; ++i)
         if(B[0][i] == 1)
            ans[i] = 1;
   }else if(neg == s){
      for(int i = 0; i < N; ++i)
         if(B[0][i] == -1)
            ans[i] = 1;
   }else
      return false;

   return true;
}
