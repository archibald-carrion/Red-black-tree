#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

class Llave {
  private:
     int k;

  public:
     Llave(int k){
       this->k = k;
     }
     int operator () (const Llave& otra) const {
         return this->k == otra.k;
     }   
};
/*

int main(){
   Llave valor(6);
     
   int v[6] = {2,1,6,4,0,3};

   vector<int> elVector(&v[0],&v[5]);
   
   vector<int>::iterator inicio = elVector.begin();
   vector<int>::iterator elFin = elVector.end();
 
   vector<int>::iterator i = find_if( inicio, elFin , valor);  
  
   cout << *i << endl;
   return 0;
}*/
