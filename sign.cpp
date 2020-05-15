#include "params.h"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>

using namespace std;
using namespace NTL;



//-------------------------------------------------------------------
void MatPrint(Mat<ZZ_p>& tmp_mat)
{
	fo(i, 0, tmp_mat.NumCols())
	{
		fo(j, 0, tmp_mat.NumRows())
		{
			cout << tmp_mat[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

//-------------------------------------------------------------------

int main()
{
	ZZ_p::init(conv<ZZ>(_Q));

	Mat<ZZ_p> S;
	Vec<ZZ_p> y;
	Vec<ZZ_p> c;
	Vec<ZZ_p> z;

	S.SetDims(N, N);
	y.SetLength(N);
	c.SetLength(N);
	z.SetLength(N);

	fo(i, 0, N)
	{
		fo(j, 0, N)
		{
			S[i][j] = 1;
		}
	}

	MatPrint(S);

	cout << "Sign" << endl;

	fo(i, 0, N) c[i] = 1;
	fo(i, 0, N) y[i] = 1;


	mul(z, S, c);
	cout << z << endl;
	add(z, z, y);

	cout << z << endl;

	return 0;
}