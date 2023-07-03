// LOP TIN CHI
#pragma once
#include "DSSVDK.h"
#include "Function.h"
#include <iostream>
#include "Monhoc.h"
#include "CTDL.h"
using namespace std;

//===========================FUNCTION BACK - END===================//
void free_DSLTC(DS_LTC& dsltc) {
    for (int i = 0; i < dsltc.sl_ltc; i++) {
    	free_DSDK(dsltc.ds_loptc[i]->dssvdk);
        delete dsltc.ds_loptc[i];
    }
    dsltc.sl_ltc = 0;
}

void ReadDataDS_LTC(DS_LTC &dsltc)
{
	ifstream fileIn;
	fileIn.open("data\\DSLTC.txt", ios_base::in);
	if (!fileIn.is_open())
	{
		cout << "Khong mo dc file";
		return;
	}
	string line;
	int i = 0;
	while (getline(fileIn, line))
	{
		stringstream ss(line);
		string temp;
		dsltc.ds_loptc[i] = new LOPTC; // tao vung nho cho loptc de doc file
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->MALOPTC = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->MAMH = temp;
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->nienkhoa = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->hocky = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->nhom = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->svmax = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->svmin = stoi(temp);
		getline(ss, temp, ',');
		dsltc.ds_loptc[i]->huylop = (bool)stoi(temp);
		
		dsltc.ds_loptc[i]->dssvdk.list_svdk = new DANGKY[dsltc.ds_loptc[i]->svmax];
		dsltc.ds_loptc[i]->dssvdk.sl_svdk = 0;
		i++;
	}
	dsltc.sl_ltc = i;
	fileIn.close();
}
void writeData_LTC(LOPTC *LTC, ofstream &fileOut){
	
	char temp = ','; 
	fileOut << LTC->MALOPTC; 
	fileOut << temp; 
	fileOut << LTC->MAMH; 
	fileOut << temp; 
	fileOut << LTC->nienkhoa; 
	fileOut << temp; 
	fileOut << LTC->hocky; 
	fileOut << temp; 
	fileOut << LTC->nhom; 
	fileOut << temp; 
	fileOut << LTC->svmax;
	fileOut << temp; 
	fileOut << LTC->svmin;
	fileOut << temp;  
	fileOut << LTC->huylop; 
	fileOut << "\n"; 
}
void writeDataDS_LTC(DS_LTC ds_ltc){
	ofstream fileOut; 
	fileOut.open("data\\DSLTC.txt",ios_base::out); 
	for(int i = 0; i < ds_ltc.sl_ltc; i++){
		writeData_LTC(ds_ltc.ds_loptc[i],fileOut); 
	}
	fileOut.close(); 
}
int findLopTC(DS_LTC dsltc, int maloptc)
{
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		if (dsltc.ds_loptc[i]->MALOPTC == maloptc)
		{
			return i;
		}
	}
	return -1;
}

void readDataDS_DK(DS_LTC &dsltc)
{
	ifstream filein;
	filein.open("data\\DSDK.txt", ios::in);
	if (filein.is_open())
	{
		int mltc, pos, count = 1;
		char ch = ',';
		while (filein >> mltc)
		{
			if (mltc == 0)
				break;
			filein >> ch;
			pos = findLopTC(dsltc, mltc);
			if (pos != -1)
			{
				// doc ma sinh vien va diem
				DANGKY svdk;
				getline(filein, svdk.MASV, ',');
				filein >> svdk.diem;
				filein.ignore();
				add_SVDK(dsltc.ds_loptc[pos]->dssvdk, svdk, dsltc.ds_loptc[pos]->svmax);
			}
		}
	}
	else
	{
		cout << "\nKHONG TIM THAY FILE DSDK";
	}
}

void writeFile_DSDK(DS_LTC dsltc) {
	ofstream fileout;
	fileout.open("data\\DSDK.txt", ios::out);
	char ch = ',';
	if(!fileout.is_open()) {
		cout << "\nKhong mo duoc file DSDK";
	}else {
		for(int i = 0; i < dsltc.sl_ltc; i++) {
			for(int j = 0; j < dsltc.ds_loptc[i]->dssvdk.sl_svdk; j++) {
				fileout << dsltc.ds_loptc[i]->MALOPTC;
				fileout << ch;
				fileout << dsltc.ds_loptc[i]->dssvdk.list_svdk[j].MASV;
				fileout << ch;
				fileout << dsltc.ds_loptc[i]->dssvdk.list_svdk[j].diem;
				fileout << '\n';
			}
		}
	}
}
void KhoiTaoLopTinChi(LOPTC *lop)
{
	lop->MALOPTC = 0;
	lop->MAMH[0] = '\0';
	lop->nienkhoa = 0;
	lop->hocky = 0;
	lop->nhom = 0;
	lop->svmax = 0;
	lop->svmin = 0;
	lop->huylop = false;
	lop->dssvdk.list_svdk = NULL;
	lop->dssvdk.sl_svdk = 0;
}
bool checkTrung_LTC(DS_LTC ds, string MAMH, int nienkhoa, int hocky, int nhom, int &pos)
{
	for (int i = 0; i < ds.sl_ltc; i++)
	{
		if (ds.ds_loptc[i]->MAMH.compare(MAMH) == 0 && ds.ds_loptc[i]->nienkhoa == nienkhoa && ds.ds_loptc[i]->hocky == hocky && ds.ds_loptc[i]->nhom == nhom)
		{
			pos = i;
			return true;
		}
	}
	pos = -1;
	return false;
}

int TaoMaAuto_LTC(DS_LTC &ds)
{
	// Tao ma tu dong tang
	if (ds.sl_ltc == 0)
		return 1;
	else
		return ds.ds_loptc[ds.sl_ltc - 1]->MALOPTC + 1;
}

void ThemLopTinChi(DS_LTC &ds, LOPTC *ltc)
{
	// Tao ma lop tc tu dong
	ltc->MALOPTC = TaoMaAuto_LTC(ds);

	// Cap phat dong cho danh sach dang ky
	// int *a = new int[n] , mang duoi duoc quan ly bang con tro *list_svdk
	ltc->dssvdk.list_svdk = new DANGKY[ltc->svmax]; // dong thu nhat la gan dia chi cua mang vua cap phat vao con tro list_svdk
	ltc->dssvdk.sl_svdk = 0;						// chua co sv dk ( dang rong )
	ds.ds_loptc[ds.sl_ltc] = ltc;
	ds.sl_ltc++;
}
string TimKiemTenMonHoc(TREE dsmh, string maMH)
{
	PTR_TREE p = dsmh.root; // Staring from the root node of the Tree
	while (p != NULL)
	{
		if (maMH > p->info.MAMH)
		{
			p = p->right;
		}
		else if (maMH < p->info.MAMH)
		{
			p = p->left;
		}
		else
		{
			return p->info.TENMH; // Returns the subject name after finding and ending the Function
		}
	}

	return ""; // Returns an empty string if not found
}
// ----- GRAPHICS -----//
void remove_color_rectangle_lookfor(int pre)
{ // pre laf xd vi tri' x, j la xd vi tri' y
	setcolor(clblack);
	int y = y_hdsd - 40;
	int x = frame_right - 90;
	if (pre == 1)
		rectangle(x - 100, y, x, y + 30);

	if (pre == 2)
		rectangle(1010 - 70, y, 1010, y + 30);

	if (pre == 3)
		rectangle(902 - 70, y, 902, y + 30);

	if (pre == 4)
		rectangle(780 - 70, y, 780, y + 30);
}
void graphics_look_for(int mx, int my)
{
	int y = y_hdsd - 40;
	int x = frame_right - 90;
	if (pre_lf == -1)
	{ // cho Ma MH hien dau tien
		setcolor(clblue);
		rectangle(x - 100, y, x, y + 30);
		setcolor(clblack);
		pre_lf = 1;
	}
	setbkcolor(cllightwhite);
	y = y_hdsd - 40;
	x = frame_right - 190;
	// xoa con nhay chuot o truoc
	if (pre_lf == 1)
		outtextxy(x + 10 + textwidth(NhapMaMH.c_str()), y + 3, "  ");

	if (pre_lf == 2)
		outtextxy(1010 - 70 + 10 + textwidth(NhapNhom.c_str()), y + 3, "  ");

	if (pre_lf == 3)
		outtextxy(902 - 70 + 10 + textwidth(NhapHocKy.c_str()), y + 3, "  ");

	if (pre_lf == 4)
		outtextxy(780 - 70 + 10 + textwidth(NhapNienKhoa.c_str()), y + 3, "  ");

	x = frame_right - 90;

	if (mx > x - 75 && my > y_hdsd - 80 && mx < x - 25 && my < y_hdsd - 50)
	{ // Button Ma MH
	}
	if (mx > x - 100 && my > y_hdsd - 40 && mx < x && my < y_hdsd - 10)
	{ // Ma MH
		remove_color_rectangle_lookfor(pre_lf);
		lf_ltc[0] = true;
		lf_ltc[1] = lf_ltc[2] = lf_ltc[3] = false;
		setcolor(clblue);
		rectangle(x - 100, y, x, y + 30);
		setcolor(clblack);
		pre_lf = 1;
	}

	if (mx > 1010 - 70 && my > y_hdsd - 40 && mx < 1010 && my < y_hdsd - 10)
	{ // Nhom'
		remove_color_rectangle_lookfor(pre_lf);
		lf_ltc[1] = true;
		lf_ltc[0] = lf_ltc[2] = lf_ltc[3] = false;
		setcolor(clblue);
		rectangle(1010 - 70, y, 1010, y + 30);
		setcolor(clblack);
		pre_lf = 2;
	}
	if (mx > 902 - 70 && my > y_hdsd - 40 && mx < 902 && my < y_hdsd - 10)
	{ // Hoc Ky
		remove_color_rectangle_lookfor(pre_lf);
		lf_ltc[2] = true;
		lf_ltc[1] = lf_ltc[0] = lf_ltc[3] = false;
		setcolor(clblue);
		rectangle(902 - 70, y, 902, y + 30);
		setcolor(clblack);
		pre_lf = 3;
	}

	if (mx > 780 - 70 && my > y_hdsd - 40 && mx < 780 && my < y_hdsd - 10)
	{ // Nien Khoa
		remove_color_rectangle_lookfor(pre_lf);
		lf_ltc[3] = true;
		lf_ltc[1] = lf_ltc[2] = lf_ltc[0] = false;
		setcolor(clblue);
		rectangle(780 - 70, y, 780, y + 30);
		setcolor(clblack);
		pre_lf = 4;
	}
}

bool tim_kiem_ltc(string x1, string y1, string x2, string y2, string x3, string y3, string x4, string y4) // x la` dsltc.ds_loptc[i], y la Nhap
{
	if (y1.length() == 0 && y2.length() == 0 && y3.length() == 0 && y4.length() == 0)
		return true;
	if (x1.find(y1)==-1 || x2.find(y2)==-1 || x3.find(y3)==-1 || x4.find(y4)==-1)
		return false;
	return true;
}

void in_dsltc(DS_LTC &dsltc, int current, TREE dsmh, Change_LTC type)
{

	outtextxy(frame_right - 190 + 10, y_hdsd - 34, NhapMaMH.c_str());
	outtextxy(1010 - 70 + 10, y_hdsd - 34, NhapNhom.c_str());
	outtextxy(902 - 70 + 10, y_hdsd - 34, NhapHocKy.c_str());
	outtextxy(780 - 70 + 10, y_hdsd - 34, NhapNienKhoa.c_str());
	
	string s3[] = {"STT", "Ma Lop", "Ma MH", "Ten Mon Hoc", "Khoa", "HK", "Nhom", "Sl", "CL", "Min", "HUY", "Thao Tac"};
	int y = y_hdsd;
	setcolor(clblack);
	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	// in ten o? hang` 1
	int x = frame_left + 40;
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s3[0].c_str()) / 2, y + 6, s3[0].c_str());
	x += 50;
	bar(x, y, x + 60, y + 30);
	rectangle(x, y, x + 60, y + 30);
	outtextxy(x + 30 - textwidth(s3[1].c_str()) / 2, y + 6, s3[1].c_str());
	x += 60;
	bar(x, y, x + 90, y + 30);
	rectangle(x, y, x + 90, y + 30);
	outtextxy(x + 45 - textwidth(s3[2].c_str()) / 2, y + 6, s3[2].c_str());
	x += 90;
	bar(x, y, x + 375, y + 30);
	rectangle(x, y, x + 375, y + 30);
	outtextxy(x + 375 / 2 - textwidth(s3[3].c_str()) / 2, y + 6, s3[3].c_str());
	x += 375;
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 50 / 2 - textwidth(s3[4].c_str()) / 2, y + 6, s3[4].c_str());
	x += 50;
	bar(x, y, x + 30, y + 30);
	rectangle(x, y, x + 30, y + 30);
	outtextxy(x + 30 / 2 - textwidth(s3[5].c_str()) / 2, y + 6, s3[5].c_str());
	x += 30;
	for (int i = 6; i <= 9; i++)
	{
		bar(x, y, x + 40, y + 30);
		rectangle(x, y, x + 40, y + 30);
		outtextxy(x + 40 / 2 - textwidth(s3[i].c_str()) / 2, y + 6, s3[i].c_str());
		x += 40;
	}
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 50 / 2 - textwidth(s3[10].c_str()) / 2, y + 6, s3[10].c_str());
	x += 50;
	bar(x + 1, y + 1, x + 100 - 1, y + 30 - 1);
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 100 / 2 - textwidth(s3[11].c_str()) / 2, y + 6, s3[11].c_str());
	y += 30;

	int count = 0; // dem xem co bn so luong lop tin chi can tim
	string temp, temp1, temp2, temp3;
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
		temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
		temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
		if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
				count++;
		}
			
	}
	int page = count / 15;
	int so_du = count % 15;
	int first_pos = 0;
	int last_pos = 0;
	int pos = 0;
	if (so_du != 0)
		page++;
	if (page != 0)
	{
		if (current == page && so_du != 0)
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + so_du;
		}
		else
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + 15;
		}

		int i = dsltc.sl_ltc - 1;
		for (; pos < first_pos - 1; i--)
		{ //
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
					pos++;
			}		
		}	
		// ve table
		for (; first_pos < last_pos; i--)
		{
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
			{ // neu la luc dang ký thì chi in ra lop co huy lop la False
				setfillstyle(1, cllightwhite);
				x = frame_left + 40;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(first_pos);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());

				x += 50;
				bar(x, y, x + 60, y + 30);
				rectangle(x, y, x + 60, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->MALOPTC);
				outtextxy(x + 30 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 60;
				bar(x, y, x + 90, y + 30);
				rectangle(x, y, x + 90, y + 30);
				outtextxy(x + 45 - textwidth(dsltc.ds_loptc[i]->MAMH.c_str()) / 2, y + 6, dsltc.ds_loptc[i]->MAMH.c_str());
				x += 90;
				string tenMH = TimKiemTenMonHoc(dsmh, dsltc.ds_loptc[i]->MAMH);
				bar(x, y, x + 375, y + 30);
				rectangle(x, y, x + 375, y + 30);
				outtextxy(x + 10, y + 6, tenMH.c_str());
				x += 375;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 30, y + 30);
				rectangle(x, y, x + 30, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->hocky);
				outtextxy(x + 15 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 30;
				bar(x, y, x + 40, y + 30);
				rectangle(x, y, x + 40, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nhom);
				outtextxy(x + 20 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 40;
				bar(x, y, x + 40, y + 30);
				rectangle(x, y, x + 40, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax);
				outtextxy(x + 20 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 40;
				bar(x, y, x + 40, y + 30);
				rectangle(x, y, x + 40, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax -  dsltc.ds_loptc[i]->dssvdk.sl_svdk);
				outtextxy(x + 20 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str()); // con` lai
				x += 40;
				bar(x, y, x + 40, y + 30);
				rectangle(x, y, x + 40, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmin);
				outtextxy(x + 20 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 40;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				if (dsltc.ds_loptc[i]->huylop)
					temp = "TRUE";
				else
					temp = "FALSE";
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				rectangle(x, y, x + 100, y + 30);
				switch (type)
				{
				case REPAIR_LTC:
					draw_rectangle(x + 3, y + 3, x + 45, y + 27, clyellow);
					rectangle(x + 3, y + 3, x + 45, y + 27);
					setbkcolor(clyellow);
					outtextxy(x + 3 + 21 - textwidth("Sua") / 2, y + 5, "Sua");
					draw_rectangle(x + 55, y + 3, x + 97, y + 27, cllightred);

					rectangle(x + 55, y + 3, x + 97, y + 27);
					setbkcolor(cllightred);
					setcolor(cllightwhite);
					outtextxy(x + 55 + 21 - textwidth("Xoa") / 2, y + 5, "Xoa");
					setcolor(clblack);
					setbkcolor(cllightwhite);
					break;
				case VIEW:
					draw_rectangle(x + 5, y + 3, x + 95, y + 27, cllightgreen);
					rectangle(x + 5, y + 3, x + 95, y + 27);
					setbkcolor(cllightgreen);
					outtextxy(x + 50 - textwidth("Xem Diem") / 2, y + 6, "Xem Diem");
					setcolor(clblack);
					setbkcolor(cllightwhite);
					break;
				}

				y += 30;
				first_pos++;
			}
		}
	}
	else
		current = 0;
	y++;
	for (; first_pos <= 15; first_pos++)
	{
		draw_rectangle(frame_left + 40, y, frame_left + 980 + 30, y + 30, cllightwhite);
		y += 30;
	}
	button_page();
	string s;
	s = int_to_string(page);
	s = '/' + s;
	string b;
	b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy(frame_left + (frame_right - frame_left) / 2 - textwidth(s.c_str()) / 2, 696, s.c_str());
}
//------- Lop tin chi -------
void LOP_TIN_CHI(DS_LTC &dsltc, TREE dsmh)
{
	int x, y;
	string s[] = {"DANH SACH LOP TIN CHI", "TONG SO LOP: ", "THEM LTC", "HUY LTC", "DANG KY LTC", "XEM DSSV"};
	// Tieu de
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth(s[0].c_str()) / 2, frame_top + dis_frame_main * 5 + 1, s[0].c_str());

	setcolor(clblack);
	setbkcolor(cllightwhite);
	string temp = int_to_string(dsltc.sl_ltc);
	s[1] += temp;
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());

	// button -- open --
	x = frame_left + 40;
	draw_rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 35 - textwidth(s[2].c_str()) / 2, y_hdsd - 32, s[2].c_str());
	x += 80;
	draw_rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 35 - textwidth(s[3].c_str()) / 2, y_hdsd - 32, s[3].c_str());
	x += 80;

	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s[4].c_str()) / 2, y_hdsd - 32, s[4].c_str());
	x += 110;
	draw_rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 35 - textwidth(s[5].c_str()) / 2, y_hdsd - 32, s[5].c_str());

	x = frame_right - 40;
	string s1[] = {"Ma MH", "Nhom", "Hoc Ky", "Nien Khoa"};

	setcolor(clblack);
	draw_rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10, cllightgreen); // tï¿½m kiem
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	x -= 50;
	// Button MA MH
	draw_rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50);
	outtextxy(x - 50 - textwidth(s1[0].c_str()) / 2, y_hdsd - 74, s1[0].c_str());
	setbkcolor(cllightwhite);

	draw_rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10); // Ma MH
	x -= 100;

	outtextxy(x - textwidth(s1[0].c_str()) - 3, y_hdsd - 34, s1[0].c_str());
	x -= (textwidth(s1[0].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Nhï¿½m
	x -= 70;
	outtextxy(x - textwidth(s1[1].c_str()) - 3, y_hdsd - 34, s1[1].c_str());
	x -= (textwidth(s1[1].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Hoc Ky
	x -= 70;
	outtextxy(x - textwidth(s1[2].c_str()) - 3, y_hdsd - 34, s1[2].c_str());
	x -= (textwidth(s1[2].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Nien Khoa
	x -= 70;
	outtextxy(x - textwidth(s1[3].c_str()) - 3, y_hdsd - 34, s1[3].c_str());
	x -= (textwidth(s1[3].c_str()) + 10);
	// button -- close --
	Change_LTC type = REPAIR_LTC;
	in_dsltc(dsltc, 1, dsmh, type);
}
//-----------------------//
void table_themltc()
{
	string s[] = {"THEM LTC", "Ma Lop", "Ma Mon Hoc", "Ma MH", "Nien Khoa", "Hoc Ky", "Nhom", "SL Min", "SL Max", "THEM"};
	table(x_hdsd, y_hdsd, w_table, h_hdsd);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());
	setbkcolor(cllightwhite);

	int y = y_hdsd + 40;
	outtextxy(x_hdsd + 100 - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 355, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[2].c_str()), y + 6, s[2].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	// button
	draw_rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	outtextxy(x_hdsd + 320 - textwidth(s[3].c_str()) / 2, y + 6, s[3].c_str());
	setbkcolor(cllightwhite);

	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[4].c_str()), y + 6, s[4].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	outtextxy(x_hdsd + 280 - textwidth(s[5].c_str()), y + 6, s[5].c_str());
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[6].c_str()), y + 6, s[6].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[7].c_str()), y + 6, s[7].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	outtextxy(x_hdsd + 280 - textwidth(s[8].c_str()), y + 6, s[8].c_str());
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 75;
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[9].c_str()) / 2, y + 11, s[9].c_str());
	setbkcolor(cllightwhite);
}
//  ----------
// ----------------
//--------------

//--------------

// --- thao tac' LOP TIN CHI --- //
// ---- Them LTC ---- //

int show_Group_Number(DS_LTC &dsltc, string maMH, int nienkhoa, int hocky)
{
    int Group = 1;
    bool foundGroup = true;
    
        while (foundGroup)
        {
            foundGroup = false;

            for (int i = 0; i < dsltc.sl_ltc; i++)
            {
                if (dsltc.ds_loptc[i]->MAMH.compare(maMH) == 0 && dsltc.ds_loptc[i]->nienkhoa == nienkhoa && dsltc.ds_loptc[i]->hocky == hocky && dsltc.ds_loptc[i]->nhom == Group)
                {
                    foundGroup = true;
                    break;
                }
            }

            if (foundGroup)
            {
                Group++;
            }
        }

    return Group;
}

void remove_color_rectangle_themltc(int pre)
{
	setcolor(clblack);
	int y = y_hdsd + 90;
	if (pre == 0)
		rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	y += 50;
	if (pre == 1)
		rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	if (pre == 2)
		rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 50;
	//	if(pre == 3)	rectangle(x_hdsd+105,y,x_hdsd+235,y+30);
	y += 50;
	if (pre == 4)
		rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	if (pre == 5)
		rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
}
bool check_Status_LTC(DS_LTC dsltc, int nienkhoa, int hocky)
{
    for (int i = dsltc.sl_ltc -1  ; i >= 0   ; i--)
    {
        if (dsltc.ds_loptc[i]->nienkhoa == nienkhoa && dsltc.ds_loptc[i]->hocky == hocky)
        {
            LIST_DSSVDK dssvdk = dsltc.ds_loptc[i]->dssvdk;
            for (int j = 0; j < dssvdk.sl_svdk; j++)
            {
                if (dssvdk.list_svdk[j].diem != -1)
                {
                    return true; // L?p tín ch? dã dóng
                }
            }
        }
        else return false;
    }
    return false; // L?p tín ch? chua dóng
}
int findMaxNienKhoa(DS_LTC dsltc) {
	if(dsltc.sl_ltc == 0){
		return -1; 
	}
    return dsltc.ds_loptc[dsltc.sl_ltc - 1]->nienkhoa;
}
int findMaxHocKy_Of_NienKhoa(DS_LTC dsltc){
	if(dsltc.sl_ltc == 0){
		return 1;
	}
	return dsltc.ds_loptc[dsltc.sl_ltc - 1]->hocky; 
}
void THEM_LTC(DS_LTC &dsltc, TREE dsmh)
{
	Input type;
	table_themltc();
	setbkcolor(cllightwhite);
	setcolor(clblack);
	string autoMa_LTC = int_to_string(TaoMaAuto_LTC(dsltc));
	outtextxy(x_hdsd + 115, y_hdsd + 46, autoMa_LTC.c_str());
	string MaMonHoc, NienKhoa, HocKy, Nhom, SLMin, SLMax;
	int newNienKhoa, newHocKy; 
	int maxNienKhoa = findMaxNienKhoa(dsltc); 
	int maxHocKy = findMaxHocKy_Of_NienKhoa(dsltc);
	bool state = check_Status_LTC(dsltc,maxNienKhoa,maxHocKy); 
	if(state){ // da dong
		if(maxHocKy == 3){
			newNienKhoa = maxNienKhoa + 1 ;
			newHocKy = 1; 
		}
		else if((maxHocKy == 1)){
			newNienKhoa = maxNienKhoa; 
			newHocKy = maxHocKy + 1;
		}
		else if(maxHocKy == 2){
			newNienKhoa = maxNienKhoa; 
		}
	}
	else{ // chua dong
		newNienKhoa = maxNienKhoa; 
		newHocKy = maxHocKy; 
	}
	int mx, my, y, pre(-1);
	bool pos[6] = {false};
	// click
	while (1)
	{
		y = y_hdsd + 90;
		if (pos[0])
		{
			type = NON_SPACE;
			input(MaMonHoc, x_hdsd + 120, y + 6, type, 10);
		}
		y += 50;
		if (pos[1] && dsltc.sl_ltc == 0)
		{
			type = NUMBER;
			input(NienKhoa, x_hdsd + 120, y + 6, type, 4);
		}
		if(dsltc.sl_ltc != 0){
		setcolor(clblack);
		NienKhoa = int_to_string(newNienKhoa); 
		outtextxy(x_hdsd + 120, y + 6, NienKhoa.c_str());	
		}
		
		if (pos[2] && maxHocKy == 2 && state == true) // nien khoa max va hoc ky max da dong moi dc nhap
		{
			type = ADD_HOCKY;
			input(HocKy, x_hdsd + 300, y + 6, type, 1);
			 if (HocKy == "1")
   			{
        		newNienKhoa = maxNienKhoa + 1;
    		}
   			 else if (HocKy == "3")
    		{
        		newNienKhoa = maxNienKhoa;
    		}
		}
		if(maxHocKy != 2 || state == false){
			setcolor(clblack);
			HocKy = int_to_string(newHocKy); 
			outtextxy(x_hdsd + 300, y + 6, HocKy.c_str());
		}
	
		y += 50;
		setcolor(clblack);
		Nhom = int_to_string(show_Group_Number(dsltc, MaMonHoc, string_to_int(NienKhoa), string_to_int(HocKy)));
		outtextxy(x_hdsd + 120, y + 6, Nhom.c_str());
		y += 50;
		if (pos[4])
		{
			type = NUMBER;
			input(SLMin, x_hdsd + 120, y + 6, type, 3);
		}
		if (pos[5])
		{
			type = NUMBER;
			input(SLMax, x_hdsd + 300, y + 6, type, 3);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{

			// xoa con nhay chuot o truoc
			y = y_hdsd + 90;
			if (pre == 0)
				outtextxy(x_hdsd + 120 + textwidth(MaMonHoc.c_str()), y + 3, "  ");
			y += 50;
			if (pre == 1)
				outtextxy(x_hdsd + 120 + textwidth(NienKhoa.c_str()), y + 3, "  ");
			if (pre == 2)
				outtextxy(x_hdsd + 300 + textwidth(HocKy.c_str()), y + 3, "  ");
			y += 50;
			//            if(pre == 3)	outtextxy(x_hdsd+120+textwidth(Nhom.c_str()),y+3,"  ");
			y += 50;
			if (pre == 4)
				outtextxy(x_hdsd + 120 + textwidth(SLMin.c_str()), y + 3, "  ");
			if (pre == 5)
				outtextxy(x_hdsd + 300 + textwidth(SLMax.c_str()), y + 3, "  ");

			mx = mousex();
			my = mousey();
			y = y_hdsd + 90;
			if ((mx > x_hdsd + 105 && my > y && mx < x_hdsd + 235 && my < y + 30) || pre == -1)
			{ // Ma Mon Hoc  -1 la cho no hien dau tien
				pos[0] = true;
				pos[1] = pos[2] = pos[3] = pos[4] = pos[5] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
				pre = 0;
			}
			if (mx > x_hdsd + 285 && my > y && x_hdsd + 355 && my < y + 30)
			{						  // button Ma MH
				tempchose = MaMonHoc; // cï¿½ tï¿½c dung luu chuoi ky tu cu cua nguoi dung
				Change_MH type_mh = CHOSE;
				getMaMH(mx, my, dsmh, type_mh);
				MaMonHoc = tempchose;	  // khi chon mon hoc cap nhat chuoi ky tu moi
				LOP_TIN_CHI(dsltc, dsmh); // in lai bang ltc
				table_themltc();		  // in lai bang table them ltc
				outtextxy(x_hdsd + 115, y_hdsd + 46, autoMa_LTC.c_str());
				y = y_hdsd + 90;
				outtextxy(x_hdsd + 120, y + 6, MaMonHoc.c_str());
				y += 50;
				outtextxy(x_hdsd + 120, y + 6, NienKhoa.c_str());
				outtextxy(x_hdsd + 300, y + 6, HocKy.c_str());
				y += 100;
				outtextxy(x_hdsd + 120, y + 6, SLMin.c_str());
				outtextxy(x_hdsd + 300, y + 6, SLMax.c_str());
			}
			y += 50;
			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 185 && my < y + 30 && dsltc.sl_ltc == 0)
			{ // Nien Khoa
				pos[1] = true;
				pos[0] = pos[2] = pos[3] = pos[4] = pos[5] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
				pre = 1;
			}
			if (mx > x_hdsd + 285 && my > y && x_hdsd + 355 && my < y + 30 && maxHocKy == 2 && state == true)
			{ // Hoc Ky
				pos[2] = true;
				pos[1] = pos[0] = pos[3] = pos[4] = pos[5] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
				pre = 2;
			}
			y += 50;
			//            if( mx>x_hdsd+105 && my>y && mx<x_hdsd+235 && my<y+30 ){ // Nhom
			//                pos[3]= true;
			//                pos[1]= pos[2] = pos[0] = pos[4]= pos[5]= false;
			//                remove_color_rectangle_themltc(pre);
			//                setcolor(clblue);
			//                rectangle(x_hdsd+105,y,x_hdsd+235,y+30);
			//                pre = 3;
			//            }
			y += 50;
			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 185 && my < y + 30)
			{ // SL Min
				pos[4] = true;
				pos[1] = pos[2] = pos[3] = pos[0] = pos[5] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
				pre = 4;
			}
			if (mx > x_hdsd + 285 && my > y && mx < x_hdsd + 355 && my < y + 30)
			{ // SL Max
				pos[5] = true;
				pos[1] = pos[2] = pos[3] = pos[4] = pos[0] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
				pre = 5;
			}
			y += 75;
			
			if (mx > x_hdsd + 150 && my > y && mx < x_hdsd + 250 && my < y + 40)
			{ // Button Them
				if (MaMonHoc == "" || NienKhoa == "" || HocKy == "" || Nhom == "" || SLMin == "" || SLMax == "")
				{
					MessageBox(NULL, "Thong Tin Con Trong!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
				}
				else
				{
					if (dsltc.sl_ltc >= MAX_LTC)
					{
						MessageBox(NULL, "Danh sach lop tin chi day!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					}
					else
					{

						if (!CheckTrungMaMH(dsmh, MaMonHoc))
						{
							MessageBox(NULL, "Ma mon hoc khong ton tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else if ((string_to_int(NienKhoa) < 2000 || string_to_int(NienKhoa) > 3000))
						{
							MessageBox(NULL, "Nien Khoa Khong Hop Le. Nien khoa phai co du 4 chu so va phai nam trong doan [2000;3000]!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else if (string_to_int(SLMax) == 0)
						{
							MessageBox(NULL, "SL max phai lon hon 0!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else if (string_to_int(SLMin) > string_to_int(SLMax))
						{
							MessageBox(NULL, "SL max phai lon hon SL min!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}

						else
						{
							LOPTC *ltc = new LOPTC;
							MONHOC monhoc;
							monhoc.MAMH = MaMonHoc;
							monhoc.trangthai = true;
							KhoiTaoLopTinChi(ltc);
							ltc->MAMH = MaMonHoc;
							ltc->nienkhoa = string_to_int(NienKhoa);
							ltc->hocky = string_to_int(HocKy);
							ltc->nhom = string_to_int(Nhom);
							ltc->svmin = string_to_int(SLMin);
							ltc->svmax = string_to_int(SLMax);
							ThemLopTinChi(dsltc, ltc);
							MessageBox(NULL, "Them Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
							replace_trangThai(dsmh.root, monhoc);
							refresh_content();
							NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
							LOP_TIN_CHI(dsltc, dsmh);
							writeDataDS_LTC(dsltc);					
							break;
						}
					}
				}
			}
			// xoa bang quay lai trang LTC
			if (mx > x_btn_x_table && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe)
			{
				refresh_content();
				NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
				LOP_TIN_CHI(dsltc, dsmh);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		delay(100);
	}
}
// ---- close them LTC ---- //
// Dang Ky' LTC
void dangKyMH_LTC(DS_LTC &dsltc, int maLopTC, DANGKY svdk){
	for(int i = 0 ; i < dsltc.sl_ltc; i++){
		if(dsltc.ds_loptc[i]->MALOPTC == maLopTC){
			add_SVDK(dsltc.ds_loptc[i]->dssvdk,svdk, dsltc.ds_loptc[i]->svmax);
			return; 
		}
	}
}
bool checkSV_DK(LIST_DSSVDK dssvdk, string maSV){
	for(int i = 0; i < dssvdk.sl_svdk; i++){
		if(dssvdk.list_svdk[i].MASV.compare(maSV) == 0){
			return true; 
		}
	}
	return false;
}

bool checkSVDK_LTC(DS_LTC dsltc, int maLopTC, string maSV){
	for(int i = 0; i < dsltc.sl_ltc; i++){
		if(dsltc.ds_loptc[i]->MALOPTC == maLopTC){
			return checkSV_DK(dsltc.ds_loptc[i]->dssvdk, maSV); 
		}
	}
	return false;
}
void check_KhacNhom(DS_LTC dsltc, string maMH, int nienkhoa, int hocky, int nhom, int * &ChoseMH, int dk,int MaxNienKhoa, int MaxHocKy,int sldk){ // dk la` ChoseMH[i]
	for(int i = 0, pos = 0  ; pos < sldk && i < dsltc.sl_ltc ; i++){
		if(dsltc.ds_loptc[i]->MAMH.compare(maMH) == 0  && dsltc.ds_loptc[i]->nhom != nhom && !dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy){
			if(dk==1 || dk==3){// 1 la` khi click vao`  3 la da dk truoc' do'
				if(ChoseMH[pos]==-2)
					ChoseMH[pos] = -3;
				else
					ChoseMH[pos] = 2;
			}	
			else if(dk==0 || dk==-2){// -2 la cua cai da dk || khi huy dk thi cac o cac mo lai cho dk
					if(ChoseMH[pos]==-3)
						ChoseMH[pos] = -2;
					else
						ChoseMH[pos] = 0;
			}	
		}
		if(!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy)
			pos++;
	}		
}
void in_dsdkltc(DS_LTC &dsltc, int current, TREE dsmh,string MaSinhVien, int* ChoseMH,int MaxNienKhoa, int MaxHocKy)
{
	int x = frame_right - 90;
	outtextxy(x - 100 + 10, y_hdsd - 34, NhapNienKhoa.c_str());
	x = x - 100 - (textwidth("Nien Khoa") + 10);
	outtextxy(x - 70 + 10, y_hdsd - 34, NhapHocKy.c_str());
	
	string s3[] = {"STT", "Ma Lop", "Ma MH", "Ten Mon Hoc", "Khoa", "HK", "Nhom", "Sl", "CL", "Min", "HUY", "Thao Tac"};
	int y = y_hdsd;
	setcolor(clblack);
	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	// in ten o? hang` 1
	x = frame_left + 40;
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s3[0].c_str()) / 2, y + 6, s3[0].c_str());
	x += 50;
	bar(x, y, x + 60, y + 30);
	rectangle(x, y, x + 60, y + 30);
	outtextxy(x + 30 - textwidth(s3[1].c_str()) / 2, y + 6, s3[1].c_str());
	x += 60;
	bar(x, y, x + 90, y + 30);
	rectangle(x, y, x + 90, y + 30);
	outtextxy(x + 45 - textwidth(s3[2].c_str()) / 2, y + 6, s3[2].c_str());
	x += 90;
	bar(x, y, x + 305, y + 30);
	rectangle(x, y, x + 305, y + 30);
	outtextxy(x + 305 / 2 - textwidth(s3[3].c_str()) / 2, y + 6, s3[3].c_str());
	x += 305;
	for (int i = 4; i <= 9; i++)
	{
		bar(x, y, x + 50, y + 30);
		rectangle(x, y, x + 50, y + 30);
		outtextxy(x + 50 / 2 - textwidth(s3[i].c_str()) / 2, y + 6, s3[i].c_str());
		x += 50;
	}
	bar(x, y, x + 60, y + 30);
	rectangle(x, y, x + 60, y + 30);
	outtextxy(x + 60 / 2 - textwidth(s3[10].c_str()) / 2, y + 6, s3[10].c_str());
	x += 60;
	bar(x + 1, y + 1, x + 100 - 1, y + 30 - 1);
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 100 / 2 - textwidth(s3[11].c_str()) / 2, y + 6, s3[11].c_str());
	y += 30;

	int count = 0; // dem xem co bn so luong lop tin chi can tim
	string temp, temp1, temp2, temp3;
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
		temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
		temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
		if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
			if(!dsltc.ds_loptc[i]->huylop) count++;
		}
	}
	int page = count / 15;
	int so_du = count % 15;
	int first_pos = 0;
	int last_pos = 0;
	int pos = 0;
	if (so_du != 0)
		page++;
	if (page != 0)
	{
		if (current == page && so_du != 0)
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + so_du;
		}
		else
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + 15;
		}

		int i = 0;
		for (; pos < first_pos - 1; i++)
		{ //
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
				if(!dsltc.ds_loptc[i]->huylop) pos++;
			}
				
		}	
		// ve table
		for (int pos = 0; first_pos < last_pos; i++)
		{
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop)
			{ // neu la luc dang k? th? chi in ra lop co huy lop la False
				setfillstyle(1, cllightwhite);
				x = frame_left + 40;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(first_pos);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 60, y + 30);
				rectangle(x, y, x + 60, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->MALOPTC);
				outtextxy(x + 30 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 60;
				bar(x, y, x + 90, y + 30);
				rectangle(x, y, x + 90, y + 30);
				outtextxy(x + 45 - textwidth(dsltc.ds_loptc[i]->MAMH.c_str()) / 2, y + 6, dsltc.ds_loptc[i]->MAMH.c_str());
				x += 90;
				string tenMH = TimKiemTenMonHoc(dsmh, dsltc.ds_loptc[i]->MAMH);
				bar(x, y, x + 305, y + 30);
				rectangle(x, y, x + 305, y + 30);
				outtextxy(x + 10, y + 6, tenMH.c_str());
				x += 305;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->hocky);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nhom);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax -  dsltc.ds_loptc[i]->dssvdk.sl_svdk);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str()); // con` lai
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmin);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 60, y + 30);
				rectangle(x, y, x + 60, y + 30);
				if (dsltc.ds_loptc[i]->huylop)
					temp = "TRUE";
				else
					temp = "FALSE";
				outtextxy(x + 30 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 60;
				rectangle(x, y, x + 100, y + 30);

				if(dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy && !dsltc.ds_loptc[i]->huylop){
					if(ChoseMH[pos] == -1){
						draw_rectangle(x + 20, y + 3, x + 80, y + 27, cllightred);
						setbkcolor(cllightred);
						setcolor(cllightwhite);
						outtextxy(x + 50 - textwidth("Da Du") / 2, y + 5, "Da Du");
					}
					else if(ChoseMH[pos] == 3 ){
						draw_rectangle(x + 20, y + 3, x + 80, y + 27, cllightred);
						setbkcolor(cllightred);
						setcolor(cllightwhite);
						outtextxy(x + 50 - textwidth("Da DK") / 2, y + 5, "Da DK");
					}
					else{
						int temp = claqua;
						if(ChoseMH[pos] == 1){
							temp = cllightgreen;
						}	
						else if(ChoseMH[pos]==2 || ChoseMH[pos]== -3){
							temp = clgray;
						}	
						draw_rectangle(x + 20, y + 3, x + 80, y + 27, temp);
						setbkcolor(temp);
						setcolor(clblack);
						outtextxy(x + 50 - textwidth("Dang Ky") / 2, y + 5, "Dang Ky");
					}
					setcolor(clblack);
					rectangle(x + 20, y + 3, x + 80, y + 27);
					pos++;
				}
				else{
					draw_rectangle(x + 20, y + 3, x + 80, y + 27, clgray);
					setbkcolor(clgray);
					setcolor(clblack);
					outtextxy(x + 50 - textwidth("Dang Ky") / 2, y + 5, "Dang Ky");	
				}	
				setbkcolor(cllightwhite);
				y += 30;
				first_pos++;
			}
		}
	}
	else
		current = 0;
	y++;
	for (; first_pos <= 15; first_pos++)
	{
		draw_rectangle(frame_left + 40, y, frame_left + 980 + 30, y + 30, cllightwhite);
		y += 30;
	}
	button_page();
	string s;
	s = int_to_string(page);
	s = '/' + s;
	string b;
	b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy(frame_left + (frame_right - frame_left) / 2 - textwidth(s.c_str()) / 2, 696, s.c_str());
}

void dangkyltc(PTR_SV p) // phan dang ky mon cua user
{
	int x, y;
	refresh_content();
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth("DANG KY LOP TIN CHI") / 2, frame_top + dis_frame_main * 5 + 1, "DANG KY LOP TIN CHI");
	x = frame_left + 40;
	setcolor(clblack);
	setbkcolor(cllightwhite);
	string info;
	info = "MSSV: " + p->data.MASV + ", Ho Ten: " +  p->data.HO +" "+p->data.TEN+", Phai: "+ p->data.PHAI +", SDT: "+p->data.SDT+", NamNH: "+ int_to_string(p->data.namnhaphoc);
	outtextxy(frame_left + 507 - textwidth(info.c_str())/2, frame_top + dis_frame_main * 8, info.c_str());
	x = frame_left + 40; // Button
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth("Luu") / 2, y_hdsd - 32, "Luu");
	
	x = frame_right - 40;
	
	draw_rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10, cllightgreen); // tï¿½m kiem
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	x -= 50;
	string s1[] = {"Nien Khoa", "Hoc Ky"};

	rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10);
	x -= 100;
	setbkcolor(cllightwhite);
	outtextxy(x - textwidth(s1[0].c_str()) - 3, y_hdsd - 34, s1[0].c_str());
	x -= (textwidth(s1[0].c_str()) + 10);
	setcolor(clblue);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10);
	setcolor(clblack);
	x -= 70;
	outtextxy(x - textwidth(s1[1].c_str()) - 3, y_hdsd - 34, s1[1].c_str());
	x -= (textwidth(s1[1].c_str()) + 10);
	// button -- close --
}
void table_dangkyltc()
{
	string s[] = {"DANG KY LTC", "Ma Sinh Vien", "TIEP TUC"};
	table(x_hdsd, y_hdsd, w_table, h_hdsd / 2);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());

	int y = y_hdsd + 40;
	setbkcolor(cllightwhite);
	outtextxy(x_hdsd + 100 - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	setcolor(clblue);
	rectangle(x_hdsd + 105, y, x_hdsd + 350, y + 30);
	setcolor(clblack);
	y += 75;
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[2].c_str()) / 2, y + 11, s[2].c_str());
}
void remove_color_rectangle_dangkyltc(int pre)
{
	setcolor(clblack);
	int y = y_hdsd + 40;
	int x = frame_right - 90;
	if (pre == 1)
		rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10);
	y += 50;
	x = x - 100 - (textwidth("Nien Khoa") + 10);
	if (pre == 2)
		rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10);
}
PTR_SV check_sv(PTR_SV First_sv, string masv){
	for(PTR_SV p = First_sv; p!=NULL; p=p->pnext){
		if(masv.compare(p->data.MASV)==0)	return p;
	}
	return NULL;
}

void DANG_KY_LTC(DS_LTC &dsltc, TREE dsmh, PTR_SV &First_sv)
{
	// Trung` lop(HuyDK) = -3;  HuyDk = -2;  Chua DK = 0;  Full Sv = -1; ChonMH_DK = 1; Trung` lop = 2 (ChoseMH[i]); DaDK = 3
	Input type;
	table_dangkyltc();
	setbkcolor(cllightwhite);
	setcolor(clblack);
	int mx, my, x, y, pre(2); // HocKy(pre = 2)  Nien Khoa (pre = 1)
	int sldkltc=0;
	bool pos[3] = {true, false};
	bool ChonMon = false;
	int *ChoseMH; // danh dau user nhan click dang ky'(ChoseMH[i] = 1)
	string temp, temp1, temp2, temp3;
	string MaSinhVien;
	int MaxNienKhoa = findMaxNienKhoa(dsltc);
	int MaxHocKy = findMaxHocKy_Of_NienKhoa(dsltc);
	int sldk = 0;
	// click
	while (1)
	{
		y = y_hdsd + 40;
		x = frame_right - 90;
		if (pos[0]) // bang nhap MSSV
		{
			type = NON_SPACE;
			input(MaSinhVien, x_hdsd + 120, y + 6, type, 15);
		}
		if (pos[1]) // Nien Khoa va Hoc ky`
		{
			type = HOCKY;
			input(NhapNienKhoa, x - 100 + 10, y_hdsd - 34, type, 4);
		}
		x = x - 100 - (textwidth("Nien Khoa") + 10);
		if (pos[2])
		{
			type = NUMBER;
			input(NhapHocKy, x - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (NhapHocKy.length() == 0 && NhapNienKhoa.length() == 0 && isclicked_ltc && ChonMon) // phan sinh vien chon mon dang ky'
		{
			isclicked_ltc = false;
			MaMH = Nhom = HocKy = NienKhoa = "";
			cur_page = 1;
			in_dsdkltc(dsltc, 1, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			x = frame_right - 90;
			if (pre == 1)
				outtextxy(x - 100 + 10 + textwidth(NhapNienKhoa.c_str()), y_hdsd - 34, "  "); // Nien khoa
			x = x - 100 - (textwidth("Nien Khoa") + 10);
			if (pre == 2 && ChonMon)
				outtextxy(x - 70 + 10 + textwidth(NhapHocKy.c_str()), y_hdsd - 34, "  "); // Hoc Ky

			mx = mousex();
			my = mousey();
			y = y_hdsd + 40;
			if (!ChonMon)// Ma Sinh Vien
			{
				y += 75;
				// Khi click vao Dang K?' neu co sinh vien do thi in ra Bang Dang Ky mon hoc
				if (mx > x_hdsd + 150 && my > y && x_hdsd + 250 && my < y + 40)
				{ // Button Tiep Tuc
					cur_page = 1;
					PTR_SV p = check_sv(First_sv, MaSinhVien);
					if(p!=NULL){
						
						bool state = check_Status_LTC(dsltc,MaxNienKhoa,MaxHocKy);
						if(state){ // da dong
							if(MaxHocKy == 3){
								MaxNienKhoa++ ;
								MaxHocKy = 1; 
							}
							else if((MaxHocKy == 1) || MaxHocKy == 2){
								MaxHocKy++;
							}
						}
						else{
							for(int i=dsltc.sl_ltc-1 ;i >= 0; i--){
								if(dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy && !dsltc.ds_loptc[i]->huylop)
									sldk++;
								if(dsltc.ds_loptc[i]->nienkhoa != MaxNienKhoa || dsltc.ds_loptc[i]->hocky != MaxHocKy)
									break;
							}
							ChoseMH = new int [sldk];
							for(int i=0; i<sldk; i++){
								ChoseMH[i]=0;
							}
						}
						pos[0] = false;
						dangkyltc(p);
						pos[2] = ChonMon = true;
						for(int i=0,pos = 0;i<dsltc.sl_ltc;i++){
							if(!dsltc.ds_loptc[i]->huylop){
								if(dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy){
								 	if(checkSVDK_LTC(dsltc,dsltc.ds_loptc[i]->MALOPTC,MaSinhVien)){
										ChoseMH[pos]= 3;
										check_KhacNhom(dsltc,dsltc.ds_loptc[i]->MAMH,dsltc.ds_loptc[i]->nienkhoa,dsltc.ds_loptc[i]->hocky,dsltc.ds_loptc[i]->nhom,ChoseMH,ChoseMH[pos],MaxNienKhoa,MaxHocKy,sldk);
									}
									else if(dsltc.ds_loptc[i]->svmax - dsltc.ds_loptc[i]->dssvdk.sl_svdk == 0)
										ChoseMH[pos]= -1;
//									else if(ChoseMH[pos] != 2) ChoseMH[pos]= 0;
									pos++;
								}
								sldkltc++;
							}
						}
						NhapNienKhoa = NienKhoa = int_to_string(MaxNienKhoa);
						NhapHocKy = HocKy = int_to_string(MaxHocKy);
						count = 0;
						cur_page = 1;
						isclicked_ltc = true;
						for (int i = 0; i < dsltc.sl_ltc; i++)
						{
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop)
								count++;
						}
						in_dsdkltc(dsltc, 1, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
						if(state || sldk ==0)
							MessageBox(NULL, "Khong co mon hoc de dang ky", "Thong bao", MB_OK | MB_ICONWARNING);
					}
					else	MessageBox(NULL, "Khong tim thay sinh vien", "Thong bao", MB_OK | MB_ICONWARNING);
				}
			}
			// ChonMon == true thi bat cac` thao tac tren do
			else // Dang Ky'
			{
				if (dsltc.sl_ltc > 0)
				{
					if(mx>frame_left+40 && my > y_hdsd - 40 && mx < frame_left + 140 && my < y_hdsd - 10 ){ // Button Luu
						for(int i = dsltc.sl_ltc-1, pos_dk = sldk -1 ; pos_dk >= 0 && i >= 0; i--){
							if(ChoseMH[pos_dk] == 1){
								DANGKY svdk; 
								svdk.MASV = MaSinhVien; 
								svdk.diem = -1; 
								dangKyMH_LTC(dsltc,dsltc.ds_loptc[i]->MALOPTC,svdk);
							}
							else if(ChoseMH[pos_dk] == -2 || ChoseMH[pos_dk] == -3){
								delete_SVDK(dsltc.ds_loptc[i]->dssvdk,MaSinhVien);
							}
							if(!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy)
								pos_dk--;
							if(dsltc.ds_loptc[i]->nienkhoa != MaxNienKhoa || dsltc.ds_loptc[i]->hocky != MaxHocKy)
								break;
						}
						MessageBox(NULL, "Da luu thanh cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						ChonMon = pos[2] = false;
						refresh_content();
						cur_page = 1;
						NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
						LOP_TIN_CHI(dsltc, dsmh);
						delete [] ChoseMH;
						writeFile_DSDK(dsltc);
						return;
					}
					if (mx > frame_right - 80 && my > y_hdsd - 40 && mx < frame_right - 40 && my < y_hdsd - 10)	{ // Button tim` kie^m'
						isclicked_ltc = true;
						NienKhoa = NhapNienKhoa;
						HocKy = NhapHocKy;
						count = 0;
						cur_page = 1;
						in_dsdkltc(dsltc, 1, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
						for (int i = 0; i < dsltc.sl_ltc; i++)
						{
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop)
								count++;
						}
					}
					if (NienKhoa.length() == 0 && HocKy.length() == 0)
						count = sldkltc;
					int page = count / 15;
					int so_du = count % 15;
					int first_pos = 0;
					int last_pos = 0;
					int pos = 0;
					if (so_du != 0)
						page++;
					if (page != 0)
					{
						if (cur_page == page && so_du != 0)
						{
							first_pos = (cur_page - 1) * 15 + 1;
							last_pos = first_pos + so_du;
						}
						else
						{
							first_pos = (cur_page - 1) * 15 + 1;
							last_pos = first_pos + 15;
						}

						int i = 0;
						for (; pos < first_pos - 1; i++)
						{ //
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy)
								pos++;
						}
						int y1 = y_hdsd + 30;
						for (int pos = 0; first_pos < last_pos; i++)
						{
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop)
							{
								if(dsltc.ds_loptc[i]->nienkhoa == MaxNienKhoa && dsltc.ds_loptc[i]->hocky == MaxHocKy ){
									if (mx > 1110 + 17 - 1 && my > y1 + 3 && mx < 1204 - 15 && my < y1 + 27 && (ChoseMH[pos]==1 || ChoseMH[pos]==0 || ChoseMH[pos]==3 || ChoseMH[pos]==-2)){ // Dang Ky'
										if(ChoseMH[pos] == 1)	ChoseMH[pos] = 0;
										else if(ChoseMH[pos]==0)	ChoseMH[pos] = 1;
										else if(ChoseMH[pos]==3) ChoseMH[pos] = -2;
										else if(ChoseMH[pos]==-2) ChoseMH[pos] = 3;
										check_KhacNhom(dsltc,dsltc.ds_loptc[i]->MAMH,dsltc.ds_loptc[i]->nienkhoa,dsltc.ds_loptc[i]->hocky,dsltc.ds_loptc[i]->nhom,ChoseMH,ChoseMH[pos],MaxNienKhoa,MaxHocKy,sldk);
										in_dsdkltc(dsltc, cur_page, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
										break;
									}
									pos++;	
								}
								y1 += 30;
								first_pos++;
							}
						}
						// page
						if (mx > frame_left + 307 && my > 690 && mx < frame_left + 407 && my < 715 && cur_page > 1)
						{ // back
							cur_page--;
							in_dsdkltc(dsltc, cur_page, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
						}
						if (mx > frame_left + 607 && my > 690 && mx < frame_left + 707 && my < 715 && cur_page < page)
						{ // next trang
							cur_page++;
							if (cur_page == page)
								draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1 + 30, 685 + 1, cllightwhite);
							in_dsdkltc(dsltc, cur_page, dsmh,MaSinhVien,ChoseMH,MaxNienKhoa,MaxHocKy);
						}
						// close page
					}
				}

				x = frame_right - 90;
				if (mx > x - 100 && my > y_hdsd - 40 && mx < x && my < y_hdsd - 10)
				{ // Nien khoa
					pos[1] = true;
					pos[0] = pos[2] = false;
					remove_color_rectangle_dangkyltc(pre);
					setcolor(clblue);
					rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10);
					pre = 1;
				}
				x = x - 100 - (textwidth("Nien Khoa") + 10);
				if (mx > x - 70 && my > y_hdsd - 40 && mx < x && my < y_hdsd - 10)
				{ // Hoc Ky
					pos[2] = true;
					pos[0] = pos[1] = false;
					remove_color_rectangle_dangkyltc(pre);
					setcolor(clblue);
					rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10);
					pre = 2;
				}
				// ( button X )
				if (mx > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && my > frame_top + dis_frame_main * 4 + w_subframe && mx < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && my < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
				{
					int thoat_dkltc = MessageBox(NULL, "Cac thay doi cua ban se khong duoc luu!!!", "Thong bao", MB_YESNO | MB_ICONQUESTION);
					if(thoat_dkltc ==6){
						ChonMon = pos[2] = false;
						refresh_content();
						cur_page = 1;
						NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
						LOP_TIN_CHI(dsltc, dsmh);
						delete [] ChoseMH;
						return;
					}
				}
			}
			// xoa bang quay lai trang LTC ( button X)
			if (mx > x_btn_x_table && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe)
			{
				LOP_TIN_CHI(dsltc, dsmh);
				return;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(0.000);
	}
}
// ----	close dang ky LTC ---- //
// ---- XEM DSSV ---- //
void table_xemdssv()
{
	string s[] = {"XEM DSSV", "Ma Mon Hoc", "Ma MH", "Nien Khoa", "Hoc Ky", "Nhom", "XEM"};
	table(x_hdsd, y_hdsd, w_table, h_hdsd * 2 / 3);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());
	setbkcolor(cllightwhite);

	int y = y_hdsd + 40;
	outtextxy(x_hdsd + 100 - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	// button
	draw_rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	outtextxy(x_hdsd + 320 - textwidth(s[2].c_str()) / 2, y + 6, s[2].c_str());
	setbkcolor(cllightwhite);

	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[3].c_str()), y + 6, s[3].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	outtextxy(x_hdsd + 280 - textwidth(s[4].c_str()), y + 6, s[4].c_str());
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[5].c_str()), y + 6, s[5].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	y += 75;
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[6].c_str()) / 2, y + 11, s[6].c_str());
}

void remove_color_rectangle_xemdssv(int pre)
{
	setcolor(clblack);
	int y = y_hdsd + 40;
	if (pre == 0)
		rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	y += 50;
	if (pre == 1)
		rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	if (pre == 2)
		rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 50;
	if (pre == 3)
		rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
}
void XEM_DSSV(DS_LTC &dsltc, TREE dsmh, PTR_SV First_sv)
{
	Input type;
	table_xemdssv();
	string MaMonHoc, NienKhoa, HocKy, Nhom;
	setbkcolor(cllightwhite);
	setcolor(clblack);
	int mx, my, y, pre(-1);
	bool pos[4] = {false};
	// click
	while (1)
	{
		y = y_hdsd + 40;
		if (pos[0])
		{
			type = NON_SPACE;
			input(MaMonHoc, x_hdsd + 120, y + 6, type, 10);
		}
		y += 50;
		if (pos[1])
		{
			type = NUMBER;
			input(NienKhoa, x_hdsd + 120, y + 6, type, 4);
		}
		if (pos[2])
		{
			type = NUMBER;
			input(HocKy, x_hdsd + 300, y + 6, type, 1);
		}
		y += 50;
		if (pos[3])
		{
			type = NUMBER;
			input(Nhom, x_hdsd + 120, y + 6, type, 2);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{

			// xoa con nhay chuot o truoc
			y = y_hdsd + 40;
			if (pre == 0)
				outtextxy(x_hdsd + 120 + textwidth(MaMonHoc.c_str()), y + 3, "  ");
			y += 50;
			if (pre == 1)
				outtextxy(x_hdsd + 120 + textwidth(NienKhoa.c_str()), y + 3, "  ");
			if (pre == 2)
				outtextxy(x_hdsd + 300 + textwidth(HocKy.c_str()), y + 3, "  ");
			y += 50;
			if (pre == 3)
				outtextxy(x_hdsd + 120 + textwidth(Nhom.c_str()), y + 3, "  ");

			mx = mousex();
			my = mousey();
			y = y_hdsd + 40;
			if ((mx > x_hdsd + 105 && my > y && mx < x_hdsd + 235 && my < y + 30) || pre == -1)
			{ // Ma Mon Hoc  -1 la cho no hien dau tien
				pos[0] = true;
				pos[1] = pos[2] = pos[3] = false;
				remove_color_rectangle_xemdssv(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
				pre = 0;
			}
			if (mx > x_hdsd + 285 && my > y && x_hdsd + 355 && my < y + 30)
			{						  // button Ma MH
				tempchose = MaMonHoc; // cï¿½ tï¿½c dung luu chuoi ky tu cu cua nguoi dung
				Change_MH type_mh = CHOSE;
				getMaMH(mx, my, dsmh,type_mh);
				MaMonHoc = tempchose;	  // khi chon mon hoc cap nhat chuoi ky tu moi
				LOP_TIN_CHI(dsltc, dsmh); // in lai bang ltc
				table_xemdssv();		  // in lai bang table xem dssv
				setbkcolor(cllightwhite);
				y = y_hdsd + 40;
				outtextxy(x_hdsd + 120, y + 6, MaMonHoc.c_str());
				y += 50;
				outtextxy(x_hdsd + 120, y + 6, NienKhoa.c_str());
				outtextxy(x_hdsd + 300, y + 6, HocKy.c_str());
				y += 50;
				outtextxy(x_hdsd + 120, y + 6, Nhom.c_str());
			}
			y += 50;
			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 185 && my < y + 30)
			{ // Nien Khoa
				pos[1] = true;
				pos[0] = pos[2] = pos[3] = false;
				remove_color_rectangle_xemdssv(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
				pre = 1;
			}
			if (mx > x_hdsd + 285 && my > y && x_hdsd + 355 && my < y + 30)
			{ // Hoc Ky
				pos[2] = true;
				pos[1] = pos[0] = pos[3] = false;
				remove_color_rectangle_xemdssv(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
				pre = 2;
			}
			y += 50;
			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 235 && my < y + 30)
			{ // Nhom
				pos[3] = true;
				pos[1] = pos[2] = pos[0] = false;
				remove_color_rectangle_xemdssv(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
				pre = 3;
			}
			y += 75;
			if (mx > x_hdsd + 150 && my > y && x_hdsd + 250 && my < y + 40)
			{ // Button Xem
				if (MaMonHoc == "" || NienKhoa == "" || HocKy == "" || Nhom == "")
				{
					MessageBox(NULL, "Thong Tin Con Trong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
				}
				else
				{
					int nienkhoa = string_to_int(NienKhoa);
					int hocky = string_to_int(HocKy);
					int nhom = string_to_int(Nhom);
					if (checkTrung_LTC(dsltc, MaMonHoc, nienkhoa, hocky, nhom, pos_ltc))
					{
						if (dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk == 0)
						{
							MessageBox(NULL, "Lop Tin Chi Chua Co Sinh Vien Dang Ky!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else
						{
							molop = true;
							if(dsltc.ds_loptc[pos_ltc]->nienkhoa < dsltc.ds_loptc[dsltc.sl_ltc - 1]->nienkhoa) {
								molop = false;
							}else if(dsltc.ds_loptc[pos_ltc]->nienkhoa == dsltc.ds_loptc[dsltc.sl_ltc - 1]->nienkhoa) {
								if(dsltc.ds_loptc[pos_ltc]->hocky < dsltc.ds_loptc[dsltc.sl_ltc - 1]->hocky) {
									molop = false;
								}else if(dsltc.ds_loptc[pos_ltc]->hocky == dsltc.ds_loptc[dsltc.sl_ltc - 1]->hocky) {
									for(int i = 0; i < dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk; i++) {
										if(dsltc.ds_loptc[pos_ltc]->dssvdk.list_svdk[i].diem != -1) {
											molop = false;
											break;
										}
									}
								}
							}
							view_dsdk = true;
							string tenmon = TimKiemTenMonHoc(dsmh, MaMonHoc);
							DSSVDK_LTC(First_sv, dsltc.ds_loptc[pos_ltc]->dssvdk, dsltc.ds_loptc[pos_ltc]->MALOPTC, tenmon, dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk, molop, nienkhoa, hocky, nhom);

							return;
						}
					}
					else
					{
						MessageBox(NULL, "Lop Tin Chi Khong Ton Tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					}
				}
			}
			// xoa bang quay lai trang LTC
			if (mx > x_btn_x_table && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe)
			{
				LOP_TIN_CHI(dsltc, dsmh);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(100);
	}
}
// SUA LTC
void ChangeArraySize(DANGKY *&dssvdk, int n){
	DANGKY *tempArr;
    tempArr = new DANGKY [n]; // tao mang lop hon
    for (int i = 0; i < n; i++) {
    	if(dssvdk[i].MASV.length()==0)	break;
        tempArr[i] = dssvdk[i]; // sao chep sang mang moi
    }
    delete[] dssvdk; // giai phong mang cu
    dssvdk = tempArr; // tro con tro sang mang moi
}
void table_sualtc()
{
	string s[] = {"SUA LTC", "Ma Lop", "Ma Mon Hoc", "Ma MH", "Nien Khoa", "Hoc Ky", "Nhom", "SL Min", "SL Max", "SUA"};
	table(x_hdsd, y_hdsd, w_table, h_hdsd);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());
	setbkcolor(cllightwhite);

	int y = y_hdsd + 40;
	outtextxy(x_hdsd + 100 - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 355, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[2].c_str()), y + 6, s[2].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	// button
	draw_rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	outtextxy(x_hdsd + 320 - textwidth(s[3].c_str()) / 2, y + 6, s[3].c_str());
	setbkcolor(cllightwhite);

	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[4].c_str()), y + 6, s[4].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	outtextxy(x_hdsd + 280 - textwidth(s[5].c_str()), y + 6, s[5].c_str());
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[6].c_str()), y + 6, s[6].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
	y += 50;
	outtextxy(x_hdsd + 100 - textwidth(s[7].c_str()), y + 6, s[7].c_str());
	rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
	outtextxy(x_hdsd + 280 - textwidth(s[8].c_str()), y + 6, s[8].c_str());
	rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
	y += 75;
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[9].c_str()) / 2, y + 11, s[9].c_str());
	setbkcolor(cllightwhite);
}
void SUA_LTC(DS_LTC &dsltc, LOPTC *ltc, TREE dsmh)
{
	Input type;
	table_sualtc();
	setbkcolor(cllightwhite);
	setcolor(clblack);
	string autoMa_LTC = int_to_string(ltc->MALOPTC);
	outtextxy(x_hdsd + 115, y_hdsd + 46, autoMa_LTC.c_str());
	string MaMonHoc, NienKhoa, HocKy, Nhom, SLMin, SLMax;
	MaMonHoc = ltc->MAMH;
	NienKhoa = int_to_string(ltc->nienkhoa);
	HocKy = int_to_string(ltc->hocky);
	Nhom = int_to_string(ltc->nhom);
	SLMin = int_to_string(ltc->svmin);
	SLMax = int_to_string(ltc->svmax);
	int mx, my, y, pre(-1);
	bool pos[6] = {false};
	y = y_hdsd + 90;
	outtextxy(x_hdsd + 120, y + 6, MaMonHoc.c_str());
	y += 50;
	outtextxy(x_hdsd + 120, y + 6, NienKhoa.c_str());
	outtextxy(x_hdsd + 300, y + 6, HocKy.c_str());
	y += 50;
	outtextxy(x_hdsd + 120, y + 6, Nhom.c_str());
	y += 50;
	outtextxy(x_hdsd + 120, y + 6, SLMin.c_str());
	outtextxy(x_hdsd + 300, y + 6, SLMax.c_str());
	// click

	
	y = y_hdsd + 90;
	setfillstyle(8, clblack);
	bar(x_hdsd + 285 + 1, y + 1, x_hdsd + 355, y + 30);
	setfillstyle(1, clblack);
	
	while (1)
	{
		y = y_hdsd + 90;

//		if (pos[0] && ltc->dssvdk.sl_svdk == 0)
//		{
//			type = NON_SPACE;
//			input(MaMonHoc, x_hdsd + 120, y + 6, type, 10);
//		}
		y += 50;
//		if (pos[1] && ltc->dssvdk.sl_svdk == 0)
//		{
//			type = NUMBER;
//			input(NienKhoa, x_hdsd + 120, y + 6, type, 4);
//		}
//		if (pos[2] && ltc->dssvdk.sl_svdk == 0)
//		{
//			type = HOCKY;
//			input(HocKy, x_hdsd + 300, y + 6, type, 1);
//		}
		y += 50;
		//		if(pos[3]){
		//			type = NUMBER;
		//			input(Nhom,x_hdsd+120,y+6,type,2);
		//		}
		setcolor(clblack);
		outtextxy(x_hdsd + 120, y + 6, Nhom.c_str());
		y += 50;
		if (pos[4])
		{
			type = NUMBER;
			input(SLMin, x_hdsd + 120, y + 6, type, 3);
		}
		if (pos[5])
		{
			type = NUMBER;
			input(SLMax, x_hdsd + 300, y + 6, type, 3);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{

			// xoa con nhay chuot o truoc
			y = y_hdsd + 90;
//			if (pre == 0)
//				outtextxy(x_hdsd + 120 + textwidth(MaMonHoc.c_str()), y + 3, "  ");
			y += 50;
//			if (pre == 1)
//				outtextxy(x_hdsd + 120 + textwidth(NienKhoa.c_str()), y + 3, "  ");
//			if (pre == 2)
//				outtextxy(x_hdsd + 300 + textwidth(HocKy.c_str()), y + 3, "  ");
			y += 50;
			//            if(pre == 3)	outtextxy(x_hdsd+120+textwidth(Nhom.c_str()),y+3,"  ");
			y += 50;
			if (pre == 4)
				outtextxy(x_hdsd + 120 + textwidth(SLMin.c_str()), y + 3, "  ");
			if (pre == 5)
				outtextxy(x_hdsd + 300 + textwidth(SLMax.c_str()), y + 3, "  ");

			mx = mousex();
			my = mousey();
			y = y_hdsd + 90;
//			if ((mx > x_hdsd + 105 && my > y && mx < x_hdsd + 235 && my < y + 30 && ltc->dssvdk.sl_svdk == 0) || pre == -1 && ltc->dssvdk.sl_svdk == 0)
//			{ // Ma Mon Hoc  -1 la cho no hien dau tien
//				pos[0] = true;
//				pos[1] = pos[2] = pos[3] = pos[4] = pos[5] = false;
//				remove_color_rectangle_themltc(pre);
//				setcolor(clblue);
//				rectangle(x_hdsd + 105, y, x_hdsd + 235, y + 30);
//				pre = 0;
//			}
//			if (mx > x_hdsd + 285 && my > y && mx < x_hdsd + 355 && my < y + 30 && ltc->dssvdk.sl_svdk == 0)
//			{ // button Ma MH
//				tempchose = MaMonHoc;
//				Change_MH type_mh = CHOSE;
//				getMaMH(mx, my, dsmh,type_mh);
//				MaMonHoc = tempchose;
//				LOP_TIN_CHI(dsltc, dsmh);
//				table_sualtc();
//				outtextxy(x_hdsd + 115, y_hdsd + 46, autoMa_LTC.c_str());
//				y = y_hdsd + 90;
//				outtextxy(x_hdsd + 120, y + 6, MaMonHoc.c_str());
//				y += 50;
//				outtextxy(x_hdsd + 120, y + 6, NienKhoa.c_str());
//				outtextxy(x_hdsd + 300, y + 6, HocKy.c_str());
//				y += 100;
//				outtextxy(x_hdsd + 120, y + 6, SLMin.c_str());
//				outtextxy(x_hdsd + 300, y + 6, SLMax.c_str());
//				// Khi chon MH nhom moi bi thay doi
//				Nhom = int_to_string(show_Group_Number(dsltc, MaMonHoc, string_to_int(NienKhoa), string_to_int(HocKy)));
//			}
			y += 50;
//			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 185 && my < y + 30 && ltc->dssvdk.sl_svdk == 0)
//			{ // Nien Khoa
//				pos[1] = true;
//				pos[0] = pos[2] = pos[3] = pos[4] = pos[5] = false;
//				remove_color_rectangle_themltc(pre);
//				setcolor(clblue);
//				rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
//				pre = 1;
//			}
//			if (mx > x_hdsd + 285 && my > y && mx < x_hdsd + 355 && my < y + 30 && ltc->dssvdk.sl_svdk == 0)
//			{ // Hoc Ky
//				pos[2] = true;
//				pos[1] = pos[0] = pos[3] = pos[4] = pos[5] = false;
//				remove_color_rectangle_themltc(pre);
//				setcolor(clblue);
//				rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
//				pre = 2;
//			}
			y += 50;
			//            if( mx>x_hdsd+105 && my>y && mx<x_hdsd+235 && my<y+30 ){ // Nhom
			//                pos[3]= true;
			//                pos[1]= pos[2] = pos[0] = pos[4]= pos[5]= false;
			//                remove_color_rectangle_themltc(pre);
			//                setcolor(clblue);
			//                rectangle(x_hdsd+105,y,x_hdsd+235,y+30);
			//                pre = 3;
			//            }
			y += 50;
			if (mx > x_hdsd + 105 && my > y && mx < x_hdsd + 185 && my < y + 30 || pre == -1)
			{ // SL Min
				pos[4] = true;
				pos[1] = pos[2] = pos[3] = pos[0] = pos[5] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 105, y, x_hdsd + 185, y + 30);
				pre = 4;
			}
			if (mx > x_hdsd + 285 && my > y && mx < x_hdsd + 355 && my < y + 30)
			{ // SL Max
				pos[5] = true;
				pos[1] = pos[2] = pos[3] = pos[4] = pos[0] = false;
				remove_color_rectangle_themltc(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 285, y, x_hdsd + 355, y + 30);
				pre = 5;
			}
			y += 75;
			if (mx > x_hdsd + 150 && my > y && mx < x_hdsd + 250 && my < y + 40)
			{ // Button Them
						if (string_to_int(SLMax) == 0)
						{
							MessageBox(NULL, "SL max phai lon hon 0!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else if (string_to_int(SLMin) > string_to_int(SLMax))
						{
							MessageBox(NULL, "SL max phai lon hon SL min!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else if(string_to_int(SLMax) < ltc->dssvdk.sl_svdk)
						{
							MessageBox(NULL, "SL max phai khong be hon SLSV Da DK!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else
						{
							ltc->MAMH = MaMonHoc;
							ltc->nienkhoa = string_to_int(NienKhoa);
							ltc->hocky = string_to_int(HocKy);
							ltc->nhom = string_to_int(Nhom);
							ltc->svmin = string_to_int(SLMin);
							ltc->svmax = string_to_int(SLMax);
							ChangeArraySize(ltc->dssvdk.list_svdk,string_to_int(SLMax));
//							ltc->dssvdk.list_svdk = new DANGKY[ltc->svmax]; // dong thu nhat la gan dia chi cua mang vua cap phat vao con tro list_svdk
							MessageBox(NULL, "Sua Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
							cur_page = 1;
							LOP_TIN_CHI(dsltc, dsmh);
							writeDataDS_LTC(dsltc);
							break;
						}
					
				
			}
			// xoa bang quay lai trang LTC
			if (mx > x_btn_x_table && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe){
				cur_page = 1;
				LOP_TIN_CHI(dsltc, dsmh);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(100);
	}
}
//------- Diem -------
void DIEM(DS_LTC dsltc, TREE dsmh)
{
	int x, y;
	// button -- open --
	string s[] = {"DANH SACH LOP TIN CHI", "TONG SO LOP: ", "DIEM TB", "DIEM TK"};
	// tieu de
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth(s[0].c_str()) / 2, frame_top + dis_frame_main * 5 + 1, s[0].c_str());
	setcolor(clblack);
	setbkcolor(cllightwhite);
	string temp = int_to_string(dsltc.sl_ltc);
	s[1] += temp;
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());

	x = frame_left + 40;
	draw_rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 35 - textwidth(s[2].c_str()) / 2, y_hdsd - 32, s[2].c_str());
	x += 80;

	draw_rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 70, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 35 - textwidth(s[3].c_str()) / 2, y_hdsd - 32, s[3].c_str());

	// SEARCH
	x = frame_right - 40;
	string s1[] = {"Ma MH", "Nhom", "Hoc Ky", "Nien Khoa"};

	setcolor(clblack);
	draw_rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10, cllightgreen); // tï¿½m kiem
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	x -= 50;
	// Button MA MH
	draw_rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50);
	outtextxy(x - 50 - textwidth(s1[0].c_str()) / 2, y_hdsd - 74, s1[0].c_str());
	setbkcolor(cllightwhite);

	draw_rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10); // Ma MH
	x -= 100;

	outtextxy(x - textwidth(s1[0].c_str()) - 3, y_hdsd - 34, s1[0].c_str());
	x -= (textwidth(s1[0].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Nhï¿½m
	x -= 70;
	outtextxy(x - textwidth(s1[1].c_str()) - 3, y_hdsd - 34, s1[1].c_str());
	x -= (textwidth(s1[1].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Hoc Ky
	x -= 70;
	outtextxy(x - textwidth(s1[2].c_str()) - 3, y_hdsd - 34, s1[2].c_str());
	x -= (textwidth(s1[2].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Nien Khoa
	x -= 70;
	outtextxy(x - textwidth(s1[3].c_str()) - 3, y_hdsd - 34, s1[3].c_str());
	x -= (textwidth(s1[3].c_str()) + 10);
	// button -- close --
	Change_LTC type = VIEW;
	in_dsltc(dsltc, 1, dsmh, type);
}
// Xoa LTC
bool checkLTC_SetTTMH(DS_LTC dsltc, string maMH)
{
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		if (dsltc.ds_loptc[i]->MAMH.compare(maMH) == 0)
		{
			return true;
		}
	}
	return false;
}
void XoaLopTinChi(DS_LTC& dsltc, int viTri)
{
    free_DSDK(dsltc.ds_loptc[viTri]->dssvdk);
    delete dsltc.ds_loptc[viTri];

    // Di chuy?n các ph?n t? phía sau lên d? ghi dè l?p tín ch? b? xóa
    for (int i = viTri; i < dsltc.sl_ltc - 1; i++) {
        dsltc.ds_loptc[i] = dsltc.ds_loptc[i + 1];
    }

    dsltc.sl_ltc--;
}


// Huy LTC
void in_dshuyltc(DS_LTC &dsltc, int current, TREE dsmh,int *ChoseMH)
{	
	outtextxy(frame_right-190+10, y_hdsd-34, NhapMaMH.c_str());
	outtextxy(1010 - 70 + 10, y_hdsd-34,NhapNhom.c_str());
	string s3[] = {"STT", "Ma Lop", "Ma MH", "Ten Mon Hoc", "Khoa", "HK", "Nhom", "Sl", "CL", "Min", "HUY", "Thao Tac"};
	int maxNienKhoa = findMaxNienKhoa(dsltc); 
	int maxHocKy = findMaxHocKy_Of_NienKhoa(dsltc);
	int y = y_hdsd;
	setcolor(clblack);
	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	// in ten o? hang` 1
	int x = frame_left + 40;
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s3[0].c_str()) / 2, y + 6, s3[0].c_str());
	x += 50;
	bar(x, y, x + 60, y + 30);
	rectangle(x, y, x + 60, y + 30);
	outtextxy(x + 30 - textwidth(s3[1].c_str()) / 2, y + 6, s3[1].c_str());
	x += 60;
	bar(x, y, x + 90, y + 30);
	rectangle(x, y, x + 90, y + 30);
	outtextxy(x + 45 - textwidth(s3[2].c_str()) / 2, y + 6, s3[2].c_str());
	x += 90;
	bar(x, y, x + 305, y + 30);
	rectangle(x, y, x + 305, y + 30);
	outtextxy(x + 305 / 2 - textwidth(s3[3].c_str()) / 2, y + 6, s3[3].c_str());
	x += 305;
	for (int i = 4; i <= 9; i++)
	{
		bar(x, y, x + 50, y + 30);
		rectangle(x, y, x + 50, y + 30);
		outtextxy(x + 50 / 2 - textwidth(s3[i].c_str()) / 2, y + 6, s3[i].c_str());
		x += 50;
	}
	bar(x, y, x + 60, y + 30);
	rectangle(x, y, x + 60, y + 30);
	outtextxy(x + 60 / 2 - textwidth(s3[10].c_str()) / 2, y + 6, s3[10].c_str());
	x += 60;
	bar(x + 1, y + 1, x + 100 - 1, y + 30 - 1);
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 100 / 2 - textwidth(s3[11].c_str()) / 2, y + 6, s3[11].c_str());
	y += 30;

	int count = 0; // dem xem co bn so luong lop tin chi can tim
	string temp, temp1, temp2, temp3;
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
		temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
		temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
		if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
			if(!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
				count++;
		}
			
	}
	int page = count / 15;
	int so_du = count % 15;
	int first_pos = 0;
	int last_pos = 0;
	int pos = 0;
	if (so_du != 0)
		page++;
	if (page != 0)
	{
		if (current == page && so_du != 0)
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + so_du;
		}
		else
		{
			first_pos = (current - 1) * 15 + 1;
			last_pos = first_pos + 15;
		}

		int i = 0;
		for (; pos < first_pos - 1; i++)
		{ //
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH)){
				if(!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
					pos++;
			}
				
		}	
		// ve table
		for (int pos = 0; first_pos < last_pos; i++)
		{
			temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
			temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
			temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
			if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop 
				&& dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
			{ // neu la luc dang ký thì chi in ra lop co huy lop la False
				setfillstyle(1, cllightwhite);
				x = frame_left + 40;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(first_pos);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 60, y + 30);
				rectangle(x, y, x + 60, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->MALOPTC);
				outtextxy(x + 30 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 60;
				bar(x, y, x + 90, y + 30);
				rectangle(x, y, x + 90, y + 30);
				outtextxy(x + 45 - textwidth(dsltc.ds_loptc[i]->MAMH.c_str()) / 2, y + 6, dsltc.ds_loptc[i]->MAMH.c_str());
				x += 90;
				string tenMH = TimKiemTenMonHoc(dsmh, dsltc.ds_loptc[i]->MAMH);
				bar(x, y, x + 305, y + 30);
				rectangle(x, y, x + 305, y + 30);
				outtextxy(x + 10, y + 6, tenMH.c_str());
				x += 305;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->hocky);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->nhom);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmax -  dsltc.ds_loptc[i]->dssvdk.sl_svdk);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str()); // con` lai
				x += 50;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(dsltc.ds_loptc[i]->svmin);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 60, y + 30);
				rectangle(x, y, x + 60, y + 30);
				if (dsltc.ds_loptc[i]->huylop)
					temp = "TRUE";
				else
					temp = "FALSE";
				outtextxy(x + 30 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 60;
				rectangle(x, y, x + 100, y + 30);
				int temp = claqua;
				if(ChoseMH[pos] == 1){
					temp = cllightgreen; 
				}
				pos++;
				draw_rectangle(x + 20, y + 3, x + 80, y + 27, temp);
				setbkcolor(temp);
				
		
				setcolor(clblack);
				outtextxy(x + 50 - textwidth("Chon") / 2, y + 5, "Chon");
//						int temp = claqua;
//						if(ChoseMH[i] == 1){
//							temp = cllightgreen;
//						}	
//						else if(ChoseMH[i]==2){
//							temp = clgray;
//						}	
//						draw_rectangle(x + 20, y + 3, x + 80, y + 27, temp);
//						setbkcolor(temp);
//						setcolor(clblack);
//						outtextxy(x + 50 - textwidth("Dang Ky") / 2, y + 5, "Dang Ky");

					rectangle(x + 20, y + 3, x + 80, y + 27);
					setbkcolor(cllightwhite);
				y += 30;
				first_pos++;
			}
		}
	}
	else
		current = 0;
	y++;
	for (; first_pos <= 15; first_pos++)
	{
		draw_rectangle(frame_left + 40, y, frame_left + 980 + 30, y + 30, cllightwhite);
		y += 30;
	}
	button_page();
	string s;
	s = int_to_string(page);
	s = '/' + s;
	string b;
	b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy(frame_left + (frame_right - frame_left) / 2 - textwidth(s.c_str()) / 2, 696, s.c_str());
}
void huyltc() // phan dang ky mon cua user
{
	int x, y;
	refresh_content();
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth("HUY LOP TIN CHI") / 2, frame_top + dis_frame_main * 5 + 1, "HUY LOP TIN CHI");
	setcolor(clblack);
	x = frame_left + 40; // Button
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth("Luu") / 2, y_hdsd - 32, "Luu");
	
	x = frame_right - 40;
	string s1[] = {"Ma MH", "Nhom"};

	setcolor(clblack);
	draw_rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10, cllightgreen); // tï¿½m kiem
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	x -= 50;
	// Button MA MH
	draw_rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50, cllightgreen);
	setbkcolor(cllightgreen);
	rectangle(x - 75, y_hdsd - 80, x - 25, y_hdsd - 50);
	outtextxy(x - 50 - textwidth(s1[0].c_str()) / 2, y_hdsd - 74, s1[0].c_str());
	setbkcolor(cllightwhite);

	draw_rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 100, y_hdsd - 40, x, y_hdsd - 10); // Ma MH
	x -= 100;

	outtextxy(x - textwidth(s1[0].c_str()) - 3, y_hdsd - 34, s1[0].c_str());
	x -= (textwidth(s1[0].c_str()) + 10);

	draw_rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 70, y_hdsd - 40, x, y_hdsd - 10); // Nhï¿½m
	x -= 70;
	outtextxy(x - textwidth(s1[1].c_str()) - 3, y_hdsd - 34, s1[1].c_str());
}
void remove_color_rectangle_huyltc(int pre)
{
	setcolor(clblack);
	int y = y_hdsd + 40;
	if (pre == 0)
		rectangle(x_hdsd + 105, y, x_hdsd + 350, y + 30);
	y += 50;
	if (pre == 1)
		rectangle(x_hdsd + 105, y, x_hdsd + 350, y + 30);
}
void huyLopTC(LOPTC *ltc)
{
	if (ltc->dssvdk.sl_svdk < ltc->svmin && ltc->huylop == false)
	{
		ltc->huylop = true;
	}
}
void huyLopTCTheoKhoaVaHK_LTC(DS_LTC &dsltc, int nienkhoa, int hocky)
{
	for (int i = 0; i < dsltc.sl_ltc; i++)
	{
		if (dsltc.ds_loptc[i]->nienkhoa == nienkhoa && dsltc.ds_loptc[i]->hocky == hocky)
		{
			huyLopTC(dsltc.ds_loptc[i]);
		}
	}
}

void HUY_LTC(DS_LTC &dsltc, TREE dsmh)
{
	clearmouseclick(WM_LBUTTONDOWN); // xoa con tro chuot
	Input type;
	string NienKhoa, HocKy, preNienKhoa, preHocKy;
	int *ChoseMH;
	string temp1, temp2, temp3;
	int maxNienKhoa = findMaxNienKhoa(dsltc); 
	int maxHocKy = findMaxHocKy_Of_NienKhoa(dsltc);
	int slhuyltc = 0;
	setbkcolor(cllightwhite);
	setcolor(clblack);
	huyltc();
	int  x, y, pre(-1);
	bool pos[2] = {true,false};
	for (int i = dsltc.sl_ltc-1 ; i >=0; i--)
	{
		if (!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy &&  dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
			slhuyltc++;
		else if(dsltc.ds_loptc[i]->nienkhoa != maxNienKhoa && dsltc.ds_loptc[i]->hocky != maxHocKy) break;
	}
	ChoseMH = new int [slhuyltc];
	for (int i = 0; i< slhuyltc ; i++)
		ChoseMH[i]=0;	
	cur_page = 1;
	in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
	y = y_hdsd - 40;
	x = frame_right - 90;
	setcolor(clblue);
	rectangle(x - 100, y, x, y + 30);
	setcolor(clblack);
	while (1)
	{ 
		x = frame_right - 190;
		if (pos[1]) // click vao Nhom
			outtextxy(x + 10 + textwidth(NhapMaMH.c_str()), y + 3, "  ");
		if (pos[0]) // click vao MH
			outtextxy(1010 - 70 + 10 + textwidth(NhapNhom.c_str()), y + 3, "  ");
		if (pos[0])
		{
			type = NON_SPACE;
			input(NhapMaMH, frame_right - 190 + 10, y_hdsd - 34, type, 10);
		}
		if (pos[1])
		{
			type = NUMBER;
			input(NhapNhom, 1010 - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (NhapMaMH.length() == 0 && NhapNhom.length() == 0 && isclicked_ltc) // phan sinh vien chon mon dang ky'
		{
			isclicked_ltc = false;
			MaMH = Nhom = HocKy = NienKhoa = "";
			cur_page = 1;
			in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){
			int mx = mousex();
			int my = mousey();
				if (dsltc.sl_ltc > 0)
				{
					if(mx>frame_left+40 && my > y_hdsd - 40 && mx < frame_left + 140 && my < y_hdsd - 10 ){ // Button Luu
						int luu_huyltc = MessageBox(NULL, "Ban co chac muon huy cac lop tin chi nay!!!", "Thong bao", MB_YESNO | MB_ICONQUESTION);
						if(luu_huyltc == 6){
							for(int i = dsltc.sl_ltc - 1, pos = slhuyltc - 1; pos >=0 ; i--){
								if (!dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy &&  dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin){
									if(ChoseMH[pos] == 1){
										dsltc.ds_loptc[i]->huylop = true;
									}
									pos--;
								}	
							}
							MessageBox(NULL, "Da luu thanh cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
							refresh_content();
							cur_page = 1;
							NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
							LOP_TIN_CHI(dsltc, dsmh);
							writeDataDS_LTC(dsltc);
							delete [] ChoseMH;
							return;
						}
						
					}
					if (mx > frame_right - 80 && my > y_hdsd - 40 && mx < frame_right - 40 && my < y_hdsd - 10)	{ // Button tim` kie^m'
						isclicked_ltc = true;
						Nhom = NhapNhom;
						MaMH = NhapMaMH;
						count = 0;
						cur_page = 1;
						in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
						for (int i = 0; i < dsltc.sl_ltc; i++)
						{
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) 
								&& !dsltc.ds_loptc[i]->huylop && dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
								count++;
						}
					}
					if (Nhom.length() == 0 && MaMH.length() == 0)
						count = slhuyltc;
					int page = count / 15;
					int so_du = count % 15;
					int first_pos = 0;
					int last_pos = 0;
					int pos = 0;
					if (so_du != 0)
						page++;
					if (page != 0)
					{
						if (cur_page == page && so_du != 0)
						{
							first_pos = (cur_page - 1) * 15 + 1;
							last_pos = first_pos + so_du;
						}
						else
						{
							first_pos = (cur_page - 1) * 15 + 1;
							last_pos = first_pos + 15;
						}

						int i = 0;
						for (; pos < first_pos - 1; i++)
						{ //
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop
								&& dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
								pos++;
						}
						int y1 = y_hdsd + 30;
						for (int pos = 0; first_pos < last_pos; i++)
						{
							temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
							temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
							temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
							if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH) && !dsltc.ds_loptc[i]->huylop 
								&& dsltc.ds_loptc[i]->nienkhoa == maxNienKhoa && dsltc.ds_loptc[i]->hocky == maxHocKy && dsltc.ds_loptc[i]->dssvdk.sl_svdk < dsltc.ds_loptc[i]->svmin)
							{
								if (mx > 1110 + 17 - 1 && my > y1 + 3 && mx < 1204 - 15 && my < y1 + 27 && (ChoseMH[pos]==1 || ChoseMH[pos]==0)){ // Nut Chon 
									if(ChoseMH[pos] == 1)	ChoseMH[pos] = 0;
									else if(ChoseMH[pos]==0)	ChoseMH[pos] = 1;	
			
									in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
									
									break;
								}
								pos++;
								y1 += 30;
								first_pos++;
							}

						}
						// page
						if (mx > frame_left + 307 && my > 690 && mx < frame_left + 407 && my < 715 && cur_page > 1)
						{ // back
							cur_page--;
							in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
						}
						if (mx > frame_left + 607 && my > 690 && mx < frame_left + 707 && my < 715 && cur_page < page)
						{ // next trang
							cur_page++;
							if (cur_page == page)
								draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1 + 30, 685 + 1, cllightwhite);
							in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
						}
						// close page
					}
				}
				y = y_hdsd - 40;
				x = frame_right - 90;
						// button MH
				if (mx > x - 75 && my > y_hdsd - 80 && mx < x - 25 && my < y_hdsd - 50)
				{
					Change_MH type_mh = CHOSE;
					getMaMH(x, y, dsmh, type_mh);
					NhapMaMH = tempchose;
					huyltc();
					cur_page = 1;
					in_dshuyltc(dsltc, cur_page, dsmh,ChoseMH);
				}
				if (mx > x - 100 && my > y_hdsd - 40 && mx < x && my < y_hdsd - 10)
				{ // Ma MH
					remove_color_rectangle_lookfor(2);
					pos[0] = true;
					pos[1] = false;
					setcolor(clblue);
					rectangle(x - 100, y, x, y + 30);
					setcolor(clblack);
				}
				x = x - 100 - (textwidth("Nien Khoa") + 10);
				if (mx > 1010 - 70 && my > y_hdsd - 40 && mx < 1010 && my < y_hdsd - 10)
				{ // Nhom'
					remove_color_rectangle_lookfor(1);
					pos[1] = true;
					pos[0] = false;
					setcolor(clblue);
					rectangle(1010 - 70, y, 1010, y + 30);
					setcolor(clblack);
				}
				// ( button X )
				if (mx > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && my > frame_top + dis_frame_main * 4 + w_subframe && mx < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && my < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
				{
					int thoat_dkltc = MessageBox(NULL, "Cac thay doi cua ban se khong duoc luu!!!", "Thong bao", MB_YESNO | MB_ICONQUESTION);
					if(thoat_dkltc ==6){
						refresh_content();
						cur_page = 1;
						NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
						LOP_TIN_CHI(dsltc, dsmh);
						delete [] ChoseMH;
						return;
					}
				}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(100);
	}
}

void locCacLopDK_LTC(DS_LTC dsltc, MONHOC *monhoc, int soluongMH, string maSV, int pos) {
	// Khoi tao
	for(int j = 0; j < soluongMH; j++) {
		monhoc[j].TENMH = "-1";
	}
	int i = pos;
	for(; i < dsltc.sl_ltc; i++) {
		// kiem tra sv co trong loptc ko
		if(checkSV_DK(dsltc.ds_loptc[i]->dssvdk, maSV)) {
			// neu co duyet dsmh de danh dau cac loptc sv hoc
			for(int j = 0; j < soluongMH; j++) {
				if(monhoc[j].MAMH.compare(dsltc.ds_loptc[i]->MAMH) == 0) {
					if(monhoc[j].TENMH == "-1") {
						monhoc[j].TENMH = int_to_string(i); // danh dau vi tri sinh vien hoc
					}else { // neu ma mon hoc da dc danh dau thi kiem tra diem moi va diem cu
						float diemcu = findDiem_SVDK(dsltc.ds_loptc[string_to_int(monhoc[j].TENMH)]->dssvdk, maSV);
						float diemmoi = findDiem_SVDK(dsltc.ds_loptc[i]->dssvdk, maSV);
						if(diemmoi > diemcu) {
							monhoc[j].TENMH = int_to_string(i);
						}
					}
				}
			}
		}
	}
}

void thongKeDiemTB(DS_LTC dsltc, TREE dsmh, PTR_SV First, float *diemTB, int pos_lsv) {
	float tongdiem = 0, diem = 0;
	int tongSoTC = 0;
	int soTC = 0;
	
	int soluongmon = CountNodeInTree(dsmh.root);
	MONHOC *monhoc = new MONHOC[soluongmon];
	int n = 0;
	transferTreeToArr(dsmh.root, monhoc, n);
	int pos_sv = -1;
	int pos = 0;
	// vi tri lop tin chi dau tien
	for(; pos < dsltc.sl_ltc && dsltc.ds_loptc[pos]->nienkhoa < First->data.namnhaphoc; pos++);
	// duyet danh sach sinh vien
	for(PTR_SV p = First; p != NULL && p->data.MALOP == dsl[pos_lsv]; p = p->pnext) {
		tongdiem = 0;
		tongSoTC = 0;
		pos_sv++; // vi tri sinh vien
		
		locCacLopDK_LTC(dsltc, monhoc, soluongmon, p->data.MASV, pos);
		for(int i = 0; i < soluongmon; i++) {
			if(monhoc[i].TENMH != "-1") {
				soTC = monhoc[i].STCLT + monhoc[i].STCTH;
				tongSoTC += soTC;
				diem = findDiem_SVDK(dsltc.ds_loptc[string_to_int(monhoc[i].TENMH)]->dssvdk, p->data.MASV);
				if(diem == -1) {
					diem = 0;
				}
				tongdiem += diem * soTC;
			}
		}
		if(tongSoTC != 0) {
			diemTB[pos_sv] = tongdiem / tongSoTC;
			diemTB[pos_sv] = round(diemTB[pos_sv] * 10) / 10; // lam tron diem, lay 1 chu so thap phan
		}else {
			diemTB[pos_sv] = 0;
		}
	}
	delete[] monhoc;
}

void in_dsDiemTB(DS_LTC dsltc, TREE dsmh, PTR_SV First_sv, int current, int pos_lsv, int soluongsv){
	string temp;
	int y = y_hdsd;
	int x = frame_left + 40;
	PTR_SV p = First_sv;
	for(; p != NULL && p->data.MALOP < dsl[pos_lsv]; p = p->pnext);
	
	float *diemTB = new float[soluongsv];
	thongKeDiemTB(dsltc, dsmh, p, diemTB, pos_lsv);
	
	string s1[]={"STT","Ma Sinh Vien","Ho","Ten","DiemTB"};
	setbkcolor(cllightwhite);
//	setfillstyle(1,cllightwhite);
	rectangle(x, y, x+50, y+30);
	outtextxy(x+25-textwidth(s1[0].c_str())/2, y+5,s1[0].c_str());
	x+=50;
	rectangle(x,y,x+300, y+30);
	outtextxy(x+150-textwidth(s1[1].c_str())/2, y+5,s1[1].c_str());
	x+=300;
	rectangle(x,y,x+290,y+30);
	outtextxy(x+145-textwidth(s1[2].c_str())/2, y+5,s1[2].c_str());
	x+=290;
	rectangle(x,y,x+150, y+30);
	outtextxy(x+75-textwidth(s1[3].c_str())/2, y+5,s1[3].c_str());
	x+=150;
	rectangle(x,y,x+150, y+30);
	outtextxy(x+75-textwidth(s1[4].c_str())/2, y+5,s1[4].c_str());
	y+=30;

	int page = soluongsv / 15;
	int so_du = soluongsv % 15;
	
    int first_pos = 0; // vi tri dau cua trang hien hÃ nh
    int last_pos =0; // vi tri cuoi cua trang hien hÃ nh
    if(so_du != 0)	page++;

    if(page != 0) {      
        if(current == page && so_du!=0 ){
            first_pos = (current-1) *15 + 1;
            last_pos = first_pos + so_du ; 
        }
        else{
        	    first_pos = (current-1) *15 + 1;
            	last_pos = first_pos + 15;
        }
        
        p =	First_sv;
        for(; p != NULL && p->data.MALOP < dsl[pos_lsv]; p = p->pnext);
        
        for(int i = 1; i < first_pos && p != NULL; i++, p = p->pnext);
        
        for(; first_pos < last_pos; first_pos++, p=p->pnext){ 
				x = frame_left + 40;
				setbkcolor(cllightwhite);
				setfillstyle(1,cllightwhite);
				bar(x, y, x+50, y+30);
				rectangle(x, y, x+50, y+30);
				temp = int_to_string(first_pos);
				outtextxy(x+25-textwidth(temp.c_str())/2,y+6,temp.c_str());
				x+=50;
				bar(x,y,x+300, y+30);
				rectangle(x,y,x+300, y+30);
				outtextxy(x+150-textwidth(p ->data.MASV.c_str())/2,y+6,p ->data.MASV.c_str());
				x+=300;
				bar(x,y,x+290,y+30);
				rectangle(x,y,x+290,y+30);
				outtextxy(x+10,y+6,p->data.HO.c_str());
				x+=290;
				bar(x,y,x+150, y+30);
				rectangle(x,y,x+150, y+30);
				outtextxy(x+10,y+6,p->data.TEN.c_str());
				x+=150;
				// in diem trung binh
				temp = "0";
				if(diemTB[first_pos - 1] != -1) temp = float_to_string(diemTB[first_pos - 1]);
				bar(x,y,x+150, y+30);
				rectangle(x,y,x+150, y+30);
				outtextxy(x+10,y+6,temp.c_str());
				y+=30;
        }
	}
	else current = 0;
	y++;
//	for(;first_pos<=15;first_pos++){
//		draw_rectangle(frame_left+40,y,frame_left+980,y+30,cllightwhite);
//		y+=30;
//	}
	delete [] diemTB;
	button_page();
	// content -- close --  
	string s ; s = int_to_string(page);
	s = '/' + s;
	string b; b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy( frame_left+(frame_right-frame_left)/2 - textwidth(s.c_str())/2,696,s.c_str() );
}

void DIEM_TB(DS_LTC dsltc, TREE dsmh, PTR_SV First_sv, int pos_lsv, int soluongsv) {
	string s[] = {"BANG THONG KE DIEM TRUNG BINH KHOA HOC", "Lop:", "So sinh vien hien tai:"};
	draw_rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10,cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10);
	outtextxy(frame_left+507-textwidth(s[0].c_str())/2,frame_top+dis_frame_main*5+1,s[0].c_str());
	setcolor(clblack);
	setbkcolor(cllightwhite);
	int x = frame_left;
	int y = frame_top;
	string temp = s[1] + dsl[pos_lsv];
	outtextxy(x+500-textwidth(temp.c_str())/2,y+dis_frame_main*7,temp.c_str());
	
	temp = s[2] + int_to_string(soluongsv);
	outtextxy(x+500-textwidth(temp.c_str())/2,y+dis_frame_main*8,temp.c_str());
	
	cur_page = 1;
	in_dsDiemTB(dsltc, dsmh, First_sv, cur_page, pos_lsv, soluongsv);
	button_page();
}

// Diem Tong Ket

void locLopTC_TinhDiemTK(string *s, PTR_SV First, DS_LTC dsltc, int pos_lsv, float **diemTK, int &pos_mm) {
	int pos_sv = -1;
	bool check = true;
	float diemmoi = 0;
	int pos = 0;
	for(; pos < dsltc.sl_ltc && dsltc.ds_loptc[pos]->nienkhoa < First->data.namnhaphoc; pos++);
	int i = pos; // vi tri lop tin chi dau tien co nien khoa >= nam nhap hoc
	// duyet danh sach sinh vien
	for(PTR_SV p = First; p != NULL && p->data.MALOP == dsl[pos_lsv]; p = p->pnext) {
		pos_sv++;
		i = pos;
		// duyet danh sach lop tin chi
		for(; i < dsltc.sl_ltc; i++) {
			check = true;
			if(checkSV_DK(dsltc.ds_loptc[i]->dssvdk, p->data.MASV)) { // kiem tra sinh vien có trong lop tín chi
				for(int j = 0; j < pos_mm; j++) { // kiem tra lop tin chi co ma mon hoc trung
					if(s[j] == dsltc.ds_loptc[i]->MAMH) {
						check = false;
						if(diemTK[pos_sv][j] == -2) {
							diemTK[pos_sv][j] = findDiem_SVDK(dsltc.ds_loptc[i]->dssvdk, p->data.MASV);
						}else {
							diemmoi = findDiem_SVDK(dsltc.ds_loptc[i]->dssvdk, p->data.MASV);
							if(diemTK[pos_sv][j] < diemmoi) {
								diemTK[pos_sv][j] = diemmoi;
							}
						}
						break;
					}
				}
				if(check) {
					s[pos_mm] = dsltc.ds_loptc[i]->MAMH;
					diemTK[pos_sv][pos_mm] = findDiem_SVDK(dsltc.ds_loptc[i]->dssvdk, p->data.MASV);
					pos_mm++;
				}
			}
		}
	}
}

void in_DSMonHocTK(DS_LTC dsltc, TREE dsmh, PTR_SV First, int cur, int cur_page_mm, int pos_lsv, int soluongsv) {
	int x1 = frame_left + 40;
	int y = y_hdsd;
	int soluongmon = CountNodeInTree(dsmh.root);
	somon = 0;
	string temp;
	
	string s1[] = {"STT", "Ma Sinh Vien", "Ho Ten"};
	setbkcolor(cllightwhite);
	rectangle(x1, y, x1+ 50, y + 30);
	outtextxy(x1+ 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x1+= 50;
	rectangle(x1, y, x1+ 200, y + 30);
	outtextxy(x1+ 100 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x1+= 200;
	rectangle(x1, y, x1+ 265, y + 30);
	outtextxy(x1+ 132 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x1+= 265;
	
	string *str = new string[soluongmon];
	
	float *diemTK[soluongsv];
	for(int i = 0; i < soluongsv; i++) {
		diemTK[i] = new float[soluongmon];
		for(int j = 0; j < soluongmon; j++) {
			diemTK[i][j] = -2; // khoi tao = -2 
		}
	}
	
	PTR_SV p = First;
	somon = 0;
	locLopTC_TinhDiemTK(str, p, dsltc, pos_lsv, diemTK, somon);
	
	int page_mh = somon / 6;
	int so_du_mh = somon % 6;
	
    int first_pos_mh = 0; // vi tri dau cua trang hien hÃ nh
    int last_pos_mh = 0; // vi tri cuoi cua trang hien hÃ nh
    int first_pos_sv = 0, last_pos_sv = 0;
    
    if(so_du_mh != 0)	page_mh++;
    if(page_mh != 0) {      
        if(cur_page_mm == page_mh && so_du_mh != 0 ){
            first_pos_mh = (cur_page_mm-1) * 6 + 1;
            last_pos_mh = first_pos_mh + so_du_mh; 
        }
        else{
        	    first_pos_mh = (cur_page_mm-1) * 6 + 1;
            	last_pos_mh = first_pos_mh + 6;
        }
        x1 = frame_left + 40 + 50 + 200 + 265;
        
        for(int i = first_pos_mh; i < last_pos_mh; i++) {
        	draw_rectangle(x1, y, x1 + 70, y + 30,cllightwhite);
        	rectangle(x1, y, x1 + 70, y + 30);
			outtextxy(x1+35-textwidth(str[i - 1].c_str())/2, y+6, str[i - 1].c_str());
			x1 += 70;
		}
		if(cur_page_mm == page_mh && so_du_mh != 0) {
			for(int i = last_pos_mh; i <= 6 * cur_page_mm; i++) {
				draw_rectangle(x1, y, x1 + 70, y + 30,cllightwhite);
        		rectangle(x1, y, x1 + 70, y + 30);
        		x1 += 70;
			}
		}
		y += 30;
		
		
	}
	int page = soluongsv / 15;
	int so_du = soluongsv % 15;
	page = soluongsv / 15;
	so_du = soluongsv % 15;
	if(so_du != 0)	page++;
	if(page != 0) {      
        if(cur == page && so_du!=0 ){
            first_pos_sv = (cur-1) * 15 + 1;
            last_pos_sv = first_pos_sv + so_du ; 
        }
        else{
        	    first_pos_sv = (cur-1) * 15 + 1;
            	last_pos_sv = first_pos_sv + 15;
        }
        p =	First;
        for(int i = 1; i < first_pos_sv && p != NULL; i++, p = p->pnext);
        
        for(; first_pos_sv < last_pos_sv; first_pos_sv++, p=p->pnext) {
        	x1 = frame_left + 40;
				setbkcolor(cllightwhite);
				setfillstyle(1,cllightwhite);
				bar(x1, y, x1+50, y+30);
				rectangle(x1, y, x1+50, y+30);
				temp = int_to_string(first_pos_sv);
				outtextxy(x1+25-textwidth(temp.c_str())/2,y+6,temp.c_str());
				x1+=50;
				bar(x1,y,x1+200, y+30);
				rectangle(x1,y,x1+200, y+30);
				outtextxy(x1+100-textwidth(p->data.MASV.c_str())/2,y+6,p->data.MASV.c_str());
				x1+=200;
				bar(x1,y,x1+265,y+30);
				rectangle(x1,y,x1+265,y+30);
				temp = p->data.HO + " " + p->data.TEN;
				outtextxy(x1+10,y+6, temp.c_str());
				x1+=265;
        	for(int i = first_pos_mh; i < last_pos_mh; i++) {
        		rectangle(x1, y, x1 + 70, y + 30);
        		temp = "   ";
        		outtextxy(x1+35-textwidth(temp.c_str())/2, y+6, temp.c_str());
        		if(diemTK[first_pos_sv - 1][i - 1] != -1 && diemTK[first_pos_sv - 1][i - 1] != -2) {
        			temp = float_to_string(diemTK[first_pos_sv - 1][i - 1]);
				}
				outtextxy(x1+35-textwidth(temp.c_str())/2, y+6, temp.c_str());
        		x1 += 70;
			}
			if(cur_page_mm == page_mh && so_du_mh != 0) {
				for(int i = last_pos_mh; i <= 6 * cur_page_mm; i++) {
					draw_rectangle(x1, y, x1 + 70, y + 30,cllightwhite);
        			rectangle(x1, y, x1 + 70, y + 30);
        			x1 += 70;
				}
			}
			y += 30;
		}
    }
    for(int i = 0; i < soluongsv; i++) {
		delete [] diemTK[i];
	}
	delete [] str;
	button_page();
	// content -- close --  
	string s ; s = int_to_string(page);
	s = '/' + s;
	string b; b = int_to_string(cur);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy( frame_left+(frame_right-frame_left)/2 - textwidth(s.c_str())/2,696,s.c_str() );
}

void DIEM_TK(DS_LTC dsltc, TREE dsmh, PTR_SV First_sv, int pos_lsv, int soluongsv) {
	string s[] = {"BANG DIEM TONG KET", "Lop:", "So sinh vien hien tai:"};
	draw_rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10,cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10);
	outtextxy(frame_left+507-textwidth(s[0].c_str())/2,frame_top+dis_frame_main*5+1,s[0].c_str());
	setcolor(clblack);
	setbkcolor(cllightwhite);
	int x = frame_left;
	int y = frame_top;
	string temp = s[1] + dsl[pos_lsv];
	outtextxy(x+500-textwidth(temp.c_str())/2,y+dis_frame_main*7,temp.c_str());
	
	temp = s[2] + int_to_string(soluongsv);
	outtextxy(x+500-textwidth(temp.c_str())/2,y+dis_frame_main*8,temp.c_str());
	
	cur_page = 1;
	cur_page_mamon = 1;
	in_DSMonHocTK(dsltc, dsmh, First_sv, cur_page, cur_page_mamon, pos_lsv, soluongsv);
	button_page();
	button_MH();
}
