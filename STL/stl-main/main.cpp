#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main ()
{
  vector<int> myvector;
  for (int i=1; i<=5; i++) {
     myvector.push_back(i);
     myvector.push_back(i);
  }

  cout << "myvector contains:";

  for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it){
    cout << ' ' << *it;
  }

  cout << '\n';

  random_shuffle ( myvector.begin(), myvector.end() );
  cout << "myvector contains:";

  for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it){
    cout << ' ' << *it;
  }

  cout << '\n';

  sort(myvector.begin(), myvector.end());

  cout << "myvector contains:";
 
  for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it){
    cout << ' ' << *it;
  }
  cout << '\n';

  vector<int>::iterator ultimo = unique( myvector.begin(), myvector.end()); 


  cout << "myvector contains:";
 
  for (vector<int>::iterator it = myvector.begin() ; it != ultimo; ++it){
    cout << ' ' << *it;
  }
    cout << '\n';

  vector<int>::iterator pos = find (myvector.begin(), myvector.end(), 30);

  if(pos!=myvector.end()){
     cout << "Si lo encontramos al 30"<< endl;
  }
  
  pos = find (myvector.begin(), ultimo, 3);
  
  if(pos!=myvector.end()){
     cout << "Si lo encontramos al 3"<< endl;
  }  
  return 0;
}
