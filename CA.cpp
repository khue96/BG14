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


#define MAX 100005

//-------------------------------------------------------------------
int Swap(int x, int y)
{
	int tmp;
	tmp = x;
	x = y;
	y = tmp;
}

void MatPrint(Mat<ZZ_p>& tmp_mat)
{
	fo(i, 0, tmp_mat.NumRows())
	{
		fo(j, 0, tmp_mat.NumCols())
		{
			cout << tmp_mat[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

void FindInd(Mat<ZZ_p>& tmp_mat, int tmp_list[MAX])
{
	ZZ_p tmp;
	Vec<ZZ_p> tmp_vec;
	int num_tmp;

	tmp_vec.SetLength(N);

	fo(i, 0, N)
	{
		fo(j, i, tmp_mat.NumRows())
		{
			if(tmp_mat[j][i] != 0)
			{
				swap(tmp_mat[i], tmp_mat[j]);
				num_tmp = tmp_list[i];
				tmp_list[i] = tmp_list[j];
				tmp_list[j] = num_tmp;
				break;
			}
		}

		fo(j, i + 1, tmp_mat.NumRows())
		{
			if(tmp_mat[j][i] == 0) continue;
			tmp = tmp_mat[j][i]/tmp_mat[i][i];
			mul(tmp_vec, tmp_mat[i], tmp);
			sub(tmp_mat[j], tmp_mat[j], tmp_vec);
		}
	}
	return;
}

void GaussElim(Mat<ZZ_p>& tmp_mat, Vec<ZZ_p>& tmp_res)
{
	ZZ_p tmp;
	Vec<ZZ_p> tmp_vec;
	int num_tmp;

	long row = tmp_mat.NumRows();
	long col = tmp_mat.NumCols();

	fo(i, 0, col)
	{
		/*
		cout << "CHECK" << endl;
		MatPrint(tmp_mat);
		cout << tmp_res << endl;
		*/
		fo(j, i, row)
			if(tmp_mat[j][i] != 0){
				swap(tmp_mat[i], tmp_mat[j]);
				tmp = tmp_res[i];
				tmp_res[i] = tmp_res[j];
				tmp_res[j] = tmp;
				break;
			}

		fo(j, i + 1, row)
		{
			if(tmp_mat[j][i] == 0) continue;
			tmp = tmp_mat[j][i]/tmp_mat[i][i];
			mul(tmp_vec, tmp_mat[i], tmp);
			sub(tmp_mat[j], tmp_mat[j], tmp_vec);
			tmp_res[j] = tmp_res[j] - tmp_res[i] * tmp;
		}
	}
	return;
}

bool LinCheck(Mat<ZZ_p>& tmp_mat, int num_count, Vec<ZZ_p>& vec_res)
{
	ZZ_p tmp_num;

	vec_res.SetLength(num_count);

	Vec<ZZ_p> tmp_vec;
	tmp_vec.SetLength(N);

	long row = N;
	long col = num_count + 1;

	Mat<ZZ_p> mat_check;
	mat_check.SetDims(N, num_count);

	ZZ_p res;

	fo(i, 0, N)
	{
		fo(j, 0, num_count)
		{
			mat_check[i][j] = tmp_mat[i][j];
		}
	}

	Vec<ZZ_p> vec_check;
	vec_check.SetLength(N);

	fo(i, 0, N) vec_check[i] = tmp_mat[i][num_count];


	GaussElim(mat_check, vec_check);

	fo(i, col - 1, N)
	{
		if(vec_check[i] != 0) return false;
	}

	MatPrint(mat_check);
	//cout << col << endl;
	//cout << vec_check << endl;

	fod(i, num_count, 0){

		res = vec_check[i];

		fod(j, num_count, i + 1) res = res - mat_check[i][j] * vec_res[j];

		vec_res[i] = res / mat_check[i][i];
	}

	vec_res[num_count] = -1;

	//cout << vec_res << endl;

	mul(tmp_vec, mat_check, vec_res);

	//cout << tmp_vec << endl;


	return true;
}

//-------------------------------------------------------------------

int main()
{	

	freopen("signature.txt","r", stdin);
	ZZ_p::init(conv<ZZ>(_Q));

	Vec<ZZ_p> tmp_vec;
	tmp_vec.SetLength(N);

	Vec<ZZ_p> tmp_vec1;
	tmp_vec1.SetLength(N);

	Vec<ZZ_p> tmp_vec2;
	tmp_vec2.SetLength(N);

	Vec<ZZ_p> c[MAX];
	Vec<ZZ_p> y[MAX];
	Vec<ZZ_p> z[MAX];

	Mat<ZZ_p> C;
	C.SetDims(N*N, N);

	Mat<ZZ_p> Coor_Mat;
	Coor_Mat.SetDims(N, N);

	fo(i, 0, N*N)
	{
		cin >> z[i];
		cin >> y[i];
		cin >> c[i];
		C[i] = c[i];
	}

	//Finding the linear independent set
	int CList[MAX];
	fo(i, 0, N*N) CList[i] = i;

	FindInd(C, CList);
	cout << "after GE" << endl;

	//Building the Coordinate Matrix
	fo(i, 0, N)
		fo(j, 0, N)
			Coor_Mat[i][j] = c[CList[j]][i];
	//MatPrint(Coor_Mat);		



	//Finding representation of each c_i' and sampling vectors b
	ZZ_p tmp_d;

	Vec<ZZ_p> VecCoor[MAX];

	Vec<ZZ_p> VecCoor2;
	VecCoor2.SetLength(N + 1);

	Mat<ZZ_p> VecRes;
	VecRes.SetDims(N + 1, N);

	Mat<ZZ_p> CoorMatCheck;
	CoorMatCheck.SetDims(N, N);

	Vec<ZZ_p> vec_b;
	vec_b.SetLength(N);

	int ind_cnt;

	//Find the linear dependent set c_i'
	fo(k, 0, N + 1)
	{
		fo(j, 0, N)
			CoorMatCheck[j][k] = c[k + 50][j];

		if(k > 0)
		{
			if(!LinCheck(CoorMatCheck, k, VecCoor2)) continue;
			else{
				ind_cnt = k + 1;
				break;
			}
		}
	}

	cout << ind_cnt << endl;
	cout << "linear dep set" <<  VecCoor2 << endl;



	//FALSE sua so 20 vi trong rep set co phan tu > 20 
	fo(i, 0, ind_cnt)
	{
		mul(tmp_vec1, c[i + 50], VecCoor2[i]);
		add(tmp_vec, tmp_vec, tmp_vec1);
	}

	//cout << tmp_vec << endl;

	fo(k, 0, ind_cnt)
	{
		VecCoor[k].SetLength(N);
		solve(tmp_d, Coor_Mat, VecCoor[k], c[k + 50]);

		fo(i, 0, N)
		{
			mul(tmp_vec, z[CList[i]], VecCoor[k][i]);
			add(VecRes[k], VecRes[k], tmp_vec);
		}

		add(VecRes[k], VecRes[k], z[k + 50]);
		//cout << VecRes[k] << endl;
	}

	fo(i, 0, ind_cnt)
	{
		mul(tmp_vec1, VecRes[i], VecCoor2[i]);
		add(tmp_vec, tmp_vec, tmp_vec1);
	}

	cout << "u = " << tmp_vec << endl;

	fo(i, 0, ind_cnt)
	{
		//cout << "b = " << vec_b << endl;
		mul(tmp_vec1, VecCoor[i], VecCoor2[i]);
		add(vec_b, vec_b, tmp_vec1);
	}

	cout << "b = " << vec_b << endl;

	Vec<ZZ_p> tmp_y;
	tmp_y.SetLength(N);

	fo(i, 0, N)
	{
		mul(tmp_vec1, y[CList[i]], vec_b[i]);
		add(tmp_y, tmp_y, tmp_vec1);
	}

	cout << "y = " <<  tmp_y << endl;




	fclose(stdin);
	return 0;
}