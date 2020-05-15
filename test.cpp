#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>

using namespace std;
using namespace NTL;

ZZ_p sum(ZZ_p tmp_a, ZZ_p tmp_b)
{
	return tmp_a + tmp_b;
}


int main()
{
   
   ZZ p;
   cin >> p;
   ZZ_p::init(p);

   ZZ_p a, b, c;

   cin >> c;
   a = random_ZZ_p();
   b = random_ZZ_p();
   c = sum(a,b);
   cout << a << " " << b << endl;
   cout << c << "\n";
}