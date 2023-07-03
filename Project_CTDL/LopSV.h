#pragma once
#include <iostream>
#include "CTDL.h"
using namespace std;
void Insert_Order(PTR_SV &First, PTR_SV &p)
{

	PTR_SV t, s ; // t la nut truoc, s la nut sau
	for (s = First; s != NULL && p->data.MALOP.compare(s->data.MALOP) == 1; t = s, s = s->pnext); // duyet toi vi tri dau cua lop
	string fullname_s, fullname_p;
	if (s != NULL)
		fullname_s = s->data.TEN + s->data.HO;
	fullname_p = p->data.TEN + p->data.HO;
	for (; s != NULL && fullname_p.compare(fullname_s) == 1 && p->data.MALOP.compare(s->data.MALOP) == 0 ; t = s, s = s->pnext)
	{
		fullname_s = s->data.TEN + s->data.HO;
	}
	if (s == First)
	{ // them nut vao dau danh sach lien ket
		p->pnext = First;
		First = p;
	}
	else // them nut p vao truoc nut s
	{
		p->pnext = s;
		t->pnext = p;
	}
}
void readfile(PTR_SV &First)
{
	ifstream dssv("data\\DSSV.txt", ios::in);
	string malop;
	if (!dssv)
	{
		cout << "khong mo dc";
		return;
	}
	while (!dssv.eof())
	{
		PTR_SV p = new nodeSV;
		getline(dssv, p->data.MASV, ',');
		getline(dssv, p->data.HO, ',');
		getline(dssv, p->data.TEN, ',');
		getline(dssv, p->data.PHAI, ',');
		getline(dssv, p->data.SDT, ',');
		getline(dssv, p->data.MALOP, ',');
		if (malop.compare(p->data.MALOP) != 0)
		{ // dem so luong lop hoc
			malop = p->data.MALOP;
			sl_lop++;
		}
		dssv >> p->data.namnhaphoc;
		string s;
		getline(dssv, s); // lay ki tu xuong dong;
		Insert_Order(First, p);
	}
	malop = "";
	dsl = new string[sl_lop];
	int i = 0;
	for (PTR_SV p = First; p != NULL; p = p->pnext)
	{
		if (malop.compare(p->data.MALOP) != 0)
		{ // gan ma lop hoc vao mang
			malop = p->data.MALOP;
			dsl[i++] = malop;
		}
	}
	dssv.close();
}
bool tim_kiem_lsv(string malop, string s)
{
	if (s.length() == 0 || malop.find(s)!=-1)
		return true;
	return false;
}
//------- Sinh Vien -------
void in_dsl(PTR_SV First_sv, int current)
{
	// content -- open --
	int y = y_hdsd;
	int x = frame_left + 40;
	string temp;
	string s1[] = {"STT", "Ten Lop", "So Sinh Vien Hien Tai", "Thao Tac", "Xem DSSV", "Xem Diem"};
	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x += 50;
	bar(x, y, x + 425, y + 30);
	rectangle(x, y, x + 425, y + 30);
	outtextxy(x + 212 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x += 425;
	bar(x, y, x + 390, y + 30);
	rectangle(x, y, x + 390, y + 30);
	outtextxy(x + 195 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x += 390;
	bar(x, y, x + 100, y + 30);
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[3].c_str()) / 2, y + 5, s1[3].c_str());
	y += 30;
	int count = 0;
	for (int i = 0; i < sl_lop; i++)
		if (tim_kiem_lsv(dsl[i], MaLop))
			count++;

	if (MaLop.length() == 0)
		count = sl_lop;

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
		{
			if (tim_kiem_lsv(dsl[i], MaLop))
				pos++;
		}
		for (; first_pos < last_pos; i++)
		{ // xuat tu lop[j] -> lop[line-1]
			if (tim_kiem_lsv(dsl[i], MaLop))
			{
				setfillstyle(1, cllightwhite);
				setbkcolor(cllightwhite);
				x = frame_left + 40;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(first_pos);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 425, y + 30);
				rectangle(x, y, x + 425, y + 30);
				outtextxy(x + 212 - textwidth(dsl[i].c_str()) / 2, y + 6, dsl[i].c_str());
				x += 425;
				bar(x, y, x + 390, y + 30);
				rectangle(x, y, x + 390, y + 30);
				int count_sv = 0;
				for (PTR_SV p = First_sv; p != NULL; p = p->pnext)
				{
					if(dsl[i].compare(p->data.MALOP) == -1)
						break;
					if (dsl[i].compare(p->data.MALOP) == 0)
						count_sv++;
				}
				temp = int_to_string(count_sv);
				outtextxy(x + 195 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 390;
				bar(x, y, x + 100, y + 30);
				rectangle(x, y, x + 100, y + 30);
				draw_rectangle(x + 5, y + 3, x + 95, y + 27, cllightgreen);
				rectangle(x + 5, y + 3, x + 95, y + 27);
				setbkcolor(cllightgreen);
				switch (type_lsv){
					case VIEW_DSSV:
						outtextxy(x + 50 - textwidth(s1[4].c_str()) / 2, y + 6, s1[4].c_str());
						break;
					case VIEW_DIEM:
						outtextxy(x + 50 - textwidth(s1[5].c_str()) / 2, y + 6, s1[5].c_str());
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
void SINH_VIEN(PTR_SV First_sv)
{
	cur_page = 1;
	view_dssv = false;
	opt[1] = true;
	NhapMaLop = MaLop = NhapMSSV = MSSV = "";
	int x, y;
	string s[] = {"DANH SACH LOP SINH VIEN", "TONG SO LOP: ", "Nhap Ten Lop Hoc:"};
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
	string temp;
	temp = int_to_string(sl_lop);
	s[1] += temp;
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());

	// SEARCH
	x = frame_right - 40;
	setcolor(clblack);
	setfillstyle(1, cllightgreen); // t�m kiem
	bar(x - 40, y_hdsd - 40, x, y_hdsd - 10);
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	x -= 50;
	setcolor(clblue);
	draw_rectangle(x - 210, y_hdsd - 40, x, y_hdsd - 10, cllightwhite);
	rectangle(x - 210, y_hdsd - 40, x, y_hdsd - 10);
	x -= 210;
	setbkcolor(cllightwhite);
	setcolor(clblack);
	outtextxy(x - textwidth(s[2].c_str()) - 3, y_hdsd - 35, s[2].c_str());
	// button -- close --
	in_dsl(First_sv, 1); // hien trang 1
	button_page();
	// content -- close --
}
