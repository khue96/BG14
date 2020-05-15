#include "params.h"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/vector.h>
#include <NTL/matrix.h>

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
	S.SetDims(N, N);

	fo(i, 0, N)
	{
		fo(j, 0, N)
		{
			S[i][j] = 1;
		}
	}

	MatPrint(S);
	return 0;
}