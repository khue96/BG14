#include "params.h"
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/mat_ZZ_p.h>

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

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

void CRand(Vec<ZZ_p>& tmp_c)
{
	ZZ pos;
	int cnt = 0;
	int sgn_cnt = conv<int>(RandomBnd(omega + 1));


	tmp_c.SetLength(N);

	while(cnt < omega)
	{
		pos = RandomBnd(N);
		if(tmp_c[conv<int>(pos)]  != 0) continue;
		tmp_c[conv<int>(pos)] = 1;
		if(sgn_cnt > 0)
		{
			tmp_c[conv<int>(pos)] = -1;
			sgn_cnt--;
		}
		cnt++;
		if(cnt == omega) return;
	}
}

void YRand(Vec<ZZ_p>& tmp_y)
{
	tmp_y.SetLength(N);
	fo(i, 0, N) tmp_y[i] = random_ZZ_p();
	return;
}

void BGSign(Vec<ZZ_p>& tmp_z, Vec<ZZ_p>& tmp_c, Mat<ZZ_p>& tmp_S)
{
	Vec<ZZ_p> tmp_y;

	tmp_z.SetLength(N);

	CRand(tmp_c);
	YRand(tmp_y);

	mul(tmp_z, tmp_S, tmp_c);
	add(tmp_z, tmp_z, tmp_y);

	cout << tmp_z << endl;
	cout << tmp_c << endl;

	clear(tmp_z);
	clear(tmp_c);
	clear(tmp_y);
}
//-------------------------------------------------------------------

int main()
{
	ZZ_p::init(conv<ZZ>(_Q));

	FILE *fh;

	Mat<ZZ_p> S;
	Vec<ZZ_p> y;
	Vec<ZZ_p> c;
	Vec<ZZ_p> z;

	S.SetDims(N, N);

	fo(i, 0, N)
	{
		fo(j, 0, N)
		{
			S[i][j] = random_ZZ_p();
		}
	}

	fh = fopen("key.txt", "wb");
	MatPrint(S);
	fclose(fh);



	cout << "Sign" << endl;

	freopen("signature.txt", "w", stdout);

	fo(i, 0, N*N) BGSign(z, c, S);

	fclose(stdout);

	return 0;
}