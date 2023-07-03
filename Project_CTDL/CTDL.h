#pragma once
// MONHOC
struct MONHOC
{
	string MAMH;
	string TENMH;
	int STCLT;
	int STCTH;
	bool trangthai;
};

struct NODE
{
	MONHOC info;
	NODE *left;
	NODE *right;
};
typedef NODE *PTR_TREE;

struct TREE
{
	PTR_TREE root = NULL;
};
bool Tree_Empty(TREE tree)
{
	return tree.root == NULL;
}
// Danh sách DANGKY
struct DANGKY{
	string MASV;
	float diem; 
};
struct LIST_DSSVDK{
	DANGKY *list_svdk; // con tro tro toi doi tuong DANGKY
	int sl_svdk; 
};
//======LTC=====//
struct LOPTC
{
	int MALOPTC; // so nguyen tu dong tang
	string MAMH;
	int nienkhoa;
	int hocky;
	int nhom;
	int svmin;
	int svmax;
	bool huylop;
	// dssvdk
	LIST_DSSVDK dssvdk;
};
const int MAX_LTC = 10000;
struct DS_LTC
{
	int sl_ltc;
	LOPTC *ds_loptc[MAX_LTC]; // luu tru bang con tro
};
// SINH VIEN
struct SINHVIEN
{
	string MASV;
	string HO;
	string TEN;
	string PHAI;
	string SDT;
	string MALOP;
	int namnhaphoc;
};
struct nodeSV
{
	SINHVIEN data;
	nodeSV *pnext;
};
typedef nodeSV *PTR_SV;
