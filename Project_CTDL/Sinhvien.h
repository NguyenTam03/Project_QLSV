#pragma once
#include "Const.h"
#include "LopSV.h"
/*
******* DSSV******
*/
void writeFile_SV(PTR_SV First)
{
	ofstream ofs("data\\DSSV.txt");
	if (ofs.is_open())
	{
		PTR_SV p = First;
		for (; p != NULL; p = p->pnext)
			ofs << p->data.MASV << "," << p->data.HO << "," << p->data.TEN << "," << p->data.PHAI << "," << p->data.SDT << "," << p->data.MALOP << "," << p->data.namnhaphoc << endl;
		// Di chuyen con tro ghi den vi tri' truoc ki' tu cuoi cu`ng trong file
		ofs.seekp(-1, std::ios::end);
		//  thay the ki' tu xuong dong
		ofs << " ";
		ofs.close();
	}
	else
	{
		cout << "Khong mo duoc file de ghi du lieu!\n";
	}
}

void free_dsl() {
	delete [] dsl;
}

void free_dssv(PTR_SV &First_sv)
{
	PTR_SV p;
	while (First_sv != NULL)
	{
		p = First_sv;
		First_sv = First_sv->pnext;
		delete p;
	}
}
bool tim_kiem_sv(PTR_SV p, string s)
{
	if (p->data.MALOP.compare(dsl[pos_lsv - 1]) != 0)
		return false; // kiem tra xem co thuoc lop ko da
	if (p->data.MASV.find(s) != -1 || s.length()==0)
		return true;
	return false;
}

PTR_SV layInfoSV(PTR_SV First, string masv)
{
	PTR_SV res = new nodeSV;
	PTR_SV p = First;
	for (; p != NULL; p = p->pnext)
	{
		if (p->data.MASV.compare(masv) == 0)
		{
			res->data = p->data;
			res->pnext = NULL;
			return res;
		}
	}
	return NULL;
}

void XOA_SV(PTR_SV &First, string masv, PTR_SV t)
{
	if (First == NULL)
		return;
	PTR_SV p, q;
	if (First->data.MASV == masv)
	{
		p = First;
		First = p->pnext;
		delete p;
		return;
	}
	else
	{
		q = t->pnext;
		t->pnext = q->pnext;
		delete q;
		return;
	}
}

void in_dssv(PTR_SV First_sv, int i, int current)
{
	// content -- open --
	string temp;
	string s2[] = {"DANH SACH LOP SINH VIEN", "Lop: ", "Tong So Sinh Vien: ", "Nhap MSSV: ", "THEM SV"};
	// Tieu de
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth(s2[0].c_str()) / 2, frame_top + dis_frame_main * 5 + 1, s2[0].c_str());
	setbkcolor(cllightwhite);
	setcolor(clblack);
	s2[1] = s2[1] + dsl[i - 1];
	outtextxy(frame_left + 507 - textwidth(s2[1].c_str()) / 2, frame_top + dis_frame_main * 7, s2[1].c_str());
	int count_sv = 0;
	for (PTR_SV p = First_sv; p != NULL; p = p->pnext)
	{
		if(dsl[i - 1].compare(p->data.MALOP) == -1)
			break;
		if (dsl[i - 1].compare(p->data.MALOP) == 0)
		{
			count_sv++;
		}
	}
	temp = int_to_string(count_sv);
	s2[2] = s2[2] + temp;
	outtextxy(frame_left + 507 - textwidth(s2[2].c_str()) / 2, frame_top + dis_frame_main * 9, s2[2].c_str());
	outtextxy(frame_right - 300 - textwidth(s2[3].c_str()), y_hdsd - 34, s2[3].c_str());
	// search
	int x = frame_right - 40;
	setcolor(clblack);
	setfillstyle(1, cllightgreen); // t�m kiem
	bar(x - 40, y_hdsd - 40, x, y_hdsd - 10);
	rectangle(x - 40, y_hdsd - 40, x, y_hdsd - 10);

	// icon tim kiem
	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(x - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(x - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);
	x -= 50;
	setcolor(clblue);
	rectangle(x - 210, y_hdsd - 40, x, y_hdsd - 10);
	setcolor(clblack);

	x = frame_left + 40; // Button
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s2[4].c_str()) / 2, y_hdsd - 32, s2[4].c_str());

	int y = y_hdsd;
	x = frame_left + 40;
	string s1[] = {"STT", "Ma Sinh Vien", "Ho", "Ten", "Phai", "SDT", "Nam NH", "Thao Tac"};
	setbkcolor(cllightwhite);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x += 50;
	rectangle(x, y, x + 230, y + 30);
	outtextxy(x + 115 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x += 230;
	rectangle(x, y, x + 265, y + 30);
	outtextxy(x + 132 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x += 265;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[3].c_str()) / 2, y + 5, s1[3].c_str());
	x += 100;
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[4].c_str()) / 2, y + 5, s1[4].c_str());
	x += 50;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[5].c_str()) / 2, y + 5, s1[5].c_str());
	x += 100;
	rectangle(x, y, x + 70, y + 30);
	outtextxy(x + 35 - textwidth(s1[6].c_str()) / 2, y + 5, s1[6].c_str());
	x += 70;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[7].c_str()) / 2, y + 5, s1[7].c_str());
	y += 30;
	int count = 0;
	if (MSSV.length() == 0)
		count = count_sv;
	else
	{
		for (PTR_SV p = First_sv; p != NULL; p = p->pnext)
		{
			if (tim_kiem_sv(p, MSSV))
				count++;
		}
	}

	int page = count / 15;
	int so_du = count % 15;

	int first_pos = 0; // vi tri dau cua trang hien h�nh
	int last_pos = 0;  // vi tri cuoi cua trang hien h�nh
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

		PTR_SV p = First_sv;

		for (int j = 1; j < first_pos; p = p->pnext)
		{
			if (tim_kiem_sv(p, MSSV))
			{
				j++;
			}
		}

		for (; first_pos < last_pos; p = p->pnext)
		{ // luc nao trung thi j moi tang len

			if (tim_kiem_sv(p, MSSV))
			{
				x = frame_left + 40;
				setbkcolor(cllightwhite);
				setfillstyle(1, cllightwhite);
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				temp = int_to_string(first_pos);
				outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 50;
				bar(x, y, x + 230, y + 30);
				rectangle(x, y, x + 230, y + 30);
				outtextxy(x + 115 - textwidth(p->data.MASV.c_str()) / 2, y + 6, p->data.MASV.c_str());
				x += 230;
				bar(x, y, x + 265, y + 30);
				rectangle(x, y, x + 265, y + 30);
				outtextxy(x + 10, y + 6, p->data.HO.c_str());
				x += 265;
				bar(x, y, x + 100, y + 30);
				rectangle(x, y, x + 100, y + 30);
				outtextxy(x + 10, y + 6, p->data.TEN.c_str());
				x += 100;
				bar(x, y, x + 50, y + 30);
				rectangle(x, y, x + 50, y + 30);
				outtextxy(x + 25 - textwidth(p->data.PHAI.c_str()) / 2, y + 6, p->data.PHAI.c_str());
				x += 50;
				bar(x, y, x + 100, y + 30);
				rectangle(x, y, x + 100, y + 30);
				outtextxy(x + 50 - textwidth(p->data.SDT.c_str()) / 2, y + 6, p->data.SDT.c_str());
				x += 100;
				bar(x, y, x + 70, y + 30);
				rectangle(x, y, x + 70, y + 30);
				temp = int_to_string(p->data.namnhaphoc);
				outtextxy(x + 35 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
				x += 70;
				// Thao Tac
				rectangle(x, y, x + 100, y + 30); // x = 1105
				draw_rectangle(x + 3, y + 3, x + 45, y + 27, clyellow);
				rectangle(x + 3, y + 3, x + 45, y + 27);
				setbkcolor(clyellow);
				outtextxy(x + 3 + 21 - textwidth("Sua") / 2, y + 5, "Sua");
				draw_rectangle(x + 55, y + 3, x + 97, y + 27, cllightred);

				rectangle(x + 55, y + 3, x + 97, y + 27);
				setbkcolor(cllightred);
				setcolor(cllightwhite);
				outtextxy(x + 55 + 21 - textwidth("Xoa") / 2, y + 5, "Xoa");
				setcolor(0);
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
	// content -- close --
	string s;
	s = int_to_string(page);
	s = '/' + s;
	string b;
	b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy(frame_left + (frame_right - frame_left) / 2 - textwidth(s.c_str()) / 2, 696, s.c_str());
}
void them_dong(int i)
{
	int y = y_hdsd + 30 * (i);
	int x = frame_left + 40;
	string temp;
	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	bar(x, y, x + 50, y + 30);
	rectangle(x, y, x + 50, y + 30);
	temp = int_to_string(i);
	outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
	x += 50;

	bar(x, y, x + 230, y + 30);
	rectangle(x, y, x + 230, y + 30);
	x += 230;

	bar(x, y, x + 265, y + 30);
	rectangle(x, y, x + 265, y + 30);
	x += 265;

	bar(x, y, x + 100, y + 30);
	rectangle(x, y, x + 100, y + 30);
	x += 100;

	bar(x, y, x + 150, y + 30);
	rectangle(x, y, x + 150, y + 30);
	rectangle(x + 10, y + 3, x + 60, y + 27);
	outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
	rectangle(x + 90, y + 3, x + 140, y + 27);
	outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
	x += 150;

	bar(x, y, x + 100, y + 30);
	rectangle(x, y, x + 100, y + 30);
	x += 100;

	bar(x, y, x + 70, y + 30);
	rectangle(x, y, x + 70, y + 30);
}
void condition_sua_sv(string Ho, string Ten, string Phai, string SDT, string NamNH, PTR_SV &p, bool &check)
{
	if (Ho.length() == 0 || Ten.length() == 0 || Phai.length() == 0 || SDT.length() == 0 || NamNH.length() == 0)
		MessageBox(NULL, "Phai Nhap Du Thong Tin!!!", "Thong bao", MB_OK | MB_ICONWARNING);
	else if (SDT.length() < 10 || SDT[0] != '0')
			MessageBox(NULL, "Vui Long Nhap Dung SDT!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		else if (NamNH.length() < 4)
			MessageBox(NULL, "Vui Long Nhap Dung Nam Nhap Hoc!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		else
		{
			if (Ho[Ho.length() - 1] == ' ')
				Ho.erase(Ho.length() - 1); // xoa ki tu khoang cach o cuoi
			p->data.HO = Ho;
			p->data.TEN = Ten;
			p->data.PHAI = Phai;
			p->data.SDT = SDT;
			p->data.namnhaphoc = string_to_int(NamNH);
			MessageBox(NULL, "Luu Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
			check = true;
		}
}
void remove_color_rectangle_suasv(int pre)
{ // pre laf xd vi tri' x, j la xd vi tri' y
	setcolor(clblack);
	int y = y_hdsd + 30;
	int x = frame_left + 90;
	x += 230;
	if (pre == 1)
		rectangle(x, y, x + 265, y + 30);
	x += 265;
	if (pre == 2)
		rectangle(x, y, x + 100, y + 30);
	x += 100;
	x += 150;
	if (pre == 4)
		rectangle(x, y, x + 100, y + 30);
	x += 100;
	if (pre == 5)
		rectangle(x, y, x + 70, y + 30);
}
void SUA_SV(PTR_SV First_sv, PTR_SV &p, int i)
{
	Input type;
	refresh_content();
	string temp;
	string s[] = {"SUA SINH VIEN", "Lop: ", "Luu"};
	// Tieu de
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth(s[0].c_str()) / 2, frame_top + dis_frame_main * 5 + 1, s[0].c_str());
	setbkcolor(cllightwhite);
	setcolor(clblack);

	s[1] = s[1] + dsl[i - 1];
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());

	// button Luu
	int x = frame_left + 40;
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s[2].c_str()) / 2, y_hdsd - 32, s[2].c_str());

	string s1[] = {"STT", "Ma Sinh Vien", "Ho", "Ten", "Phai", "SDT", "Nam NH"};
	int y = y_hdsd;
	x = frame_left + 40;

	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x += 50;
	rectangle(x, y, x + 230, y + 30);
	outtextxy(x + 115 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x += 230;
	rectangle(x, y, x + 265, y + 30);
	outtextxy(x + 132 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x += 265;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[3].c_str()) / 2, y + 5, s1[3].c_str());
	x += 100;
	rectangle(x, y, x + 150, y + 30);
	outtextxy(x + 75 - textwidth(s1[4].c_str()) / 2, y + 5, s1[4].c_str());
	x += 150;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[5].c_str()) / 2, y + 5, s1[5].c_str());
	x += 100;
	rectangle(x, y, x + 70, y + 30);
	outtextxy(x + 35 - textwidth(s1[6].c_str()) / 2, y + 5, s1[6].c_str());
	y += 30;
	them_dong(1);

	// ----------- thao tac' -----------
	int mx(0), my(0), pre(-1);
	string Mssv, Ho, Ten, Phai, SDT, NamNH;
	Mssv = p->data.MASV;
	Ho = p->data.HO;
	Ten = p->data.TEN;
	Phai = p->data.PHAI;
	SDT = p->data.SDT;
	NamNH = int_to_string(p->data.namnhaphoc);
	bool pos[6] = {false, true, false};

	// in truoc
	y = y_hdsd + 30;
	x = frame_left + 90;
	outtextxy(x + 10, y + 6, Mssv.c_str());
	x += 230;
	outtextxy(x + 10, y + 6, Ho.c_str());
	x += 265;
	outtextxy(x + 10, y + 6, Ten.c_str());
	x += 250;
	outtextxy(x + 10, y + 6, SDT.c_str());
	x += 100;
	outtextxy(x + 10, y + 6, NamNH.c_str());
	x -= 100;
	x -= 150;
	if (Phai == "Nam")
	{	// Phai nam
		draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, claqua); // to mau o nam
		setbkcolor(claqua);
		setcolor(clblack);
		outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
		Phai = "Nam";
		draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, cllightwhite); // xoa mau o Nu
		setbkcolor(cllightwhite);
		outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
	}
	if (Phai == "Nu")
	{ // Phai nu
		draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, claqua);
		setbkcolor(claqua);
		setcolor(clblack);
		outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
		Phai = "Nu";
		draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, cllightwhite);
		setbkcolor(cllightwhite);
		outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
	}

	while (1)
	{
		y = y_hdsd + 30;
		if (pre == -1)
		{ // Ho -1 la cho no hien dau tien
			setcolor(clblue);
			x = frame_left + 90;
			x += 230;
			rectangle(x, y, x + 265, y + 30);
			pre = 1;
		}
		x = frame_left + 90;
		x += 230;
		if (pos[1])
		{
			type = SURNAME;
			input(Ho, x + 10, y + 6, type, 20);
		}
		x += 265;
		if (pos[2])
		{
			type = NAME;
			input(Ten, x + 10, y + 6, type, 10);
		}
		x += 100;
		x += 150;
		if (pos[4])
		{
			type = NUMBER;
			input(SDT, x + 10, y + 6, type, 10);
		}
		x += 100;
		if (pos[5])
		{
			type = NUMBER;
			input(NamNH, x + 10, y + 6, type, 4);
		}
		y += 30;

		if (ismouseclick(WM_LBUTTONDOWN))
		{

			y = y_hdsd + 30;
			x = frame_left + 90;
			// xoa con nhay chuot o truoc
			x += 230;
			if (pre == 1)
				outtextxy(x + 10 + textwidth(Ho.c_str()), y + 3, "  ");
			x += 265;
			if (pre == 2)
				outtextxy(x + 10 + textwidth(Ten.c_str()), y + 3, "  ");
			x += 250;
			if (pre == 4)
				outtextxy(x + 10 + textwidth(SDT.c_str()), y + 3, "  ");
			x += 100;
			if (pre == 5)
				outtextxy(x + 10 + textwidth(NamNH.c_str()), y + 3, "  ");

			mx = mousex();
			my = mousey();
			x = frame_left + 90;
			x += 230;
			if (mx > x && my > y && mx < x + 265 && my < y + 30)
			{ // HO
				pos[1] = true;
				pos[2] = pos[4] = pos[5] = false;
				remove_color_rectangle_suasv(pre);
				setcolor(clblue);
				rectangle(x, y, x + 265, y + 30);
				pre = 1;
			}
			x += 265;
			if (mx > x && my > y && mx < x + 100 && my < y + 30)
			{ // Ten
				pos[2] = true;
				pos[1] = pos[4] = pos[5] = false;
				remove_color_rectangle_suasv(pre);
				setcolor(clblue);
				rectangle(x, y, x + 100, y + 30);
				pre = 2;
			}
			x += 100;
			if (mx > x + 10 && my > y + 3 && mx < x + 60 && my < y + 27 || Phai == "Nam")
			{																   // Phai nam
				draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, claqua); // to mau o nam
				setbkcolor(claqua);
				setcolor(clblack);
				outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
				Phai = "Nam";
				draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, cllightwhite); // xoa mau o Nu
				setbkcolor(cllightwhite);
				outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
			}
			if (mx > x + 90 && my > y + 3 && mx < x + 140 && my < y + 27 || Phai == "Nu")
			{ // Phai nu
				draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, claqua);
				setbkcolor(claqua);
				setcolor(clblack);
				outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
				Phai = "Nu";
				draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, cllightwhite);
				setbkcolor(cllightwhite);
				outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
			}
			x += 150;
			if (mx > x && my > y && mx < x + 100 && my < y + 30)
			{ // SDT
				pos[4] = true;
				pos[1] = pos[2] = pos[0] = pos[5] = false;
				remove_color_rectangle_suasv(pre);
				setcolor(clblue);
				rectangle(x, y, x + 100, y + 30);
				pre = 4;
			}
			x += 100;
			if (mx > x && my > y && mx < x + 70 && my < y + 30)
			{ // Nam Nhap Hoc
				pos[5] = true;
				pos[1] = pos[2] = pos[4] = false;
				remove_color_rectangle_suasv(pre);
				setcolor(clblue);
				rectangle(x, y, x + 70, y + 30);
				pre = 5;
			}
			y += 30;

			x = frame_left + 40;
			if (mx > x && my > y_hdsd - 40 && mx < x + 100 && my < y_hdsd - 5)
			{ // Button Luu
				bool check = false;
				condition_sua_sv(Ho, Ten, Phai, SDT, NamNH, p, check);
				if (check){
					writeFile_SV(First_sv);
					return;
				}
					
			}

			// xoa bang quay lai trang
			if (mx > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && my > frame_top + dis_frame_main * 4 + w_subframe && mx < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && my < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
			{
				int res = MessageBox(NULL, "Ban Co Muon Luu Khong!!!", "Thong bao", MB_OKCANCEL | MB_ICONWARNING);
				if (res == 1)
				{
					bool check = false;
					condition_sua_sv(Ho, Ten, Phai, SDT, NamNH, p, check);
					if (check){
						writeFile_SV(First_sv);
						return;
					}
				}
				else
					return;
			}

			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(100);
	}
}
// THEM SV
bool check_trung(string s[], int sl, PTR_SV First_sv)
{
	for (int i = 0; i < sl - 1; i++)
	{	
		if (s[i].compare(s[sl - 1]) == 0)
			return true;
	}
	for (int j = 0; j < sl; j++)
	{
		for (PTR_SV p = First_sv; p != NULL; p = p->pnext)
			if (s[j].compare(p->data.MASV) == 0)
				return true;
	}
	return false;
}
void them_sv(string Mssv[], string Ho[], string Ten[], string Phai[], string SDT[], string NamNH[], PTR_SV &First_sv, int sl, int pos)
{
	for (int i = 0; i < sl; i++)
	{
		PTR_SV p = new nodeSV;
		p->data.MASV = Mssv[i];
		if (Ho[i][Ho[i].length() - 1] == ' ')
			Ho[i].erase(Ho[i].length() - 1); // xoa ki tu khoang cach o cuoi
		p->data.HO = Ho[i];
		p->data.TEN = Ten[i];
		p->data.PHAI = Phai[i];
		p->data.SDT = SDT[i];
		int namnhaphoc = 0;
		namnhaphoc = string_to_int(NamNH[i]);
		p->data.namnhaphoc = namnhaphoc;
		p->data.MALOP = dsl[pos - 1];
		Insert_Order(First_sv, p);
	}
}
bool condition_them_sv(string Mssv[], string Ho[], string Ten[], string Phai[], string SDT[], string NamNH[], PTR_SV &First_sv, int sl, int pos_lsv)
{
	if (Mssv[sl - 1].length() == 0 || Ho[sl - 1].length() == 0 || Ten[sl - 1].length() == 0 || Phai[sl - 1].length() == 0 || SDT[sl - 1].length() == 0 || NamNH[sl - 1].length() == 0)
	{
		MessageBox(NULL, "Phai Nhap Du Thong Tin!!!", "Thong bao", MB_OK | MB_ICONWARNING);
	}
	else
	{
		if (SDT[sl - 1].length() < 10 || SDT[sl - 1][0] != '0')
			MessageBox(NULL, "Vui Long Nhap Dung SDT!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		else if (NamNH[sl - 1].length() < 4)
			MessageBox(NULL, "Vui Long Nhap Dung Nam Nhap Hoc!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		else if (!check_trung(Mssv, sl, First_sv))
		{
			them_sv(Mssv, Ho, Ten, Phai, SDT, NamNH, First_sv, sl, pos_lsv);
			MessageBox(NULL, "Luu Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
			writeFile_SV(First_sv); // Ghi file
			return true;
		}
		else
		{
			MessageBox(NULL, "Trung MSSV!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		}
	}
	return false;
}
void remove_color_rectangle_themsv(int pre, int j)
{ // pre laf xd vi tri' x, j la xd vi tri' y
	setcolor(clblack);
	int y = y_hdsd + 30 * (j + 1);
	int x = frame_left + 90;
	if (pre == 0)
		rectangle(x, y, x + 230, y + 30);
	x += 230;
	if (pre == 1)
		rectangle(x, y, x + 265, y + 30);
	x += 265;
	if (pre == 2)
		rectangle(x, y, x + 100, y + 30);
	x += 100;
	x += 150;
	if (pre == 4)
		rectangle(x, y, x + 100, y + 30);
	x += 100;
	if (pre == 5)
		rectangle(x, y, x + 70, y + 30);
}
void THEM_SV(PTR_SV &First_sv, int i)
{ // i la vi tri lop
	// Graphics
	refresh_content();
	string temp;
	string s[] = {"THEM SINH VIEN", "Lop: ", "Luu", "Them Dong"};
	// Tieu de
	draw_rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10, // o giua bang(507)
				   frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10, cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left + 507 - 200, frame_top + dis_frame_main * 4 + 10,
			  frame_left + 507 + 200, frame_top + dis_frame_main * 6 + 10);
	outtextxy(frame_left + 507 - textwidth(s[0].c_str()) / 2, frame_top + dis_frame_main * 5 + 1, s[0].c_str());
	setbkcolor(cllightwhite);
	setcolor(clblack);

	s[1] = s[1] + dsl[i - 1];
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());

	// button Luu
	int x = frame_left + 40;
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s[2].c_str()) / 2, y_hdsd - 32, s[2].c_str());
	// button Them dong
	x += 110;
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s[3].c_str()) / 2, y_hdsd - 32, s[3].c_str());

	string s1[] = {"STT", "Ma Sinh Vien", "Ho", "Ten", "Phai", "SDT", "Nam NH"};
	int y = y_hdsd;
	x = frame_left + 40;

	setbkcolor(cllightwhite);
	setfillstyle(1, cllightwhite);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x += 50;
	rectangle(x, y, x + 230, y + 30);
	outtextxy(x + 115 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x += 230;
	rectangle(x, y, x + 265, y + 30);
	outtextxy(x + 132 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x += 265;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[3].c_str()) / 2, y + 5, s1[3].c_str());
	x += 100;
	rectangle(x, y, x + 150, y + 30);
	outtextxy(x + 75 - textwidth(s1[4].c_str()) / 2, y + 5, s1[4].c_str());
	x += 150;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[5].c_str()) / 2, y + 5, s1[5].c_str());
	x += 100;
	rectangle(x, y, x + 70, y + 30);
	outtextxy(x + 35 - textwidth(s1[6].c_str()) / 2, y + 5, s1[6].c_str());
	y += 30;
	them_dong(1);

	// ----------- thao tac' -----------
	Input type;
	int mx(0), my(0), pre_y(-1), pre_x(0), sl(1); // sl la` so luong dong`
	string Mssv[15], Ho[15], Ten[15], Phai[15], SDT[15], NamNH[15];
	bool pos_y[6] = {true, false};
	bool pos_x[15] = {true, false}; // 15 dong max
	while (1)
	{
		y = y_hdsd + 30;
		if (pre_y == -1)
		{ // MSSV -1 la cho no hien dau tien
			setcolor(clblue);
			x = frame_left + 90;
			rectangle(x, y, x + 230, y + 30);
			pre_y = 0;
		}
		for (int j = 0; j < sl; j++)
		{
			x = frame_left + 90;
			if (pos_y[0] && pos_x[j])
			{
				type = NON_SPACE;
				input(Mssv[j], x + 10, y + 6, type, 10);
			}
			x += 230;
			if (pos_y[1] && pos_x[j])
			{
				type = SURNAME;
				input(Ho[j], x + 10, y + 6, type, 20);
			}
			x += 265;
			if (pos_y[2] && pos_x[j])
			{
				type = NAME;
				input(Ten[j], x + 10, y + 6, type, 10);
			}
			x += 100;
			x += 150;
			if (pos_y[4] && pos_x[j])
			{
				type = NUMBER;
				input(SDT[j], x + 10, y + 6, type, 10);
			}
			x += 100;
			if (pos_y[5] && pos_x[j])
			{
				type = NUMBER;
				input(NamNH[j], x + 10, y + 6, type, 4);
			}
			y += 30;
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{

			y = y_hdsd + 30;
			for (int j = 0; j < sl; j++)
			{
				x = frame_left + 90;
				// xoa con nhay chuot o truoc
				if (pre_y == 0 && pre_x == j)
					outtextxy(x + 10 + textwidth(Mssv[j].c_str()), y + 3, "  ");
				x += 230;
				if (pre_y == 1 && pre_x == j)
					outtextxy(x + 10 + textwidth(Ho[j].c_str()), y + 3, "  ");
				x += 265;
				if (pre_y == 2 && pre_x == j)
					outtextxy(x + 10 + textwidth(Ten[j].c_str()), y + 3, "  ");
				x += 250;
				if (pre_y == 4 && pre_x == j)
					outtextxy(x + 10 + textwidth(SDT[j].c_str()), y + 3, "  ");
				x += 100;
				if (pre_y == 5 && pre_x == j)
					outtextxy(x + 10 + textwidth(NamNH[j].c_str()), y + 3, "  ");
				y += 30;
			}

			y = y_hdsd + 30;
			for (int j = 0; j < sl; j++)
			{ // ta chi co 1 TH dung trong vong lap for nen khi dung ta thoat ra ( break )
				x = frame_left + 90;
				mx = mousex();
				my = mousey();
				x = frame_left + 90;
				if (mx > x && my > y && mx < x + 230 && my < y + 30)
				{ // MSSV -1 la cho no hien dau tien
					for (int k = 0; k < sl; k++)
						pos_x[k] = false;
					pos_y[0] = pos_x[j] = true;
					pos_y[1] = pos_y[2] = pos_y[4] = pos_y[5] = false;
					remove_color_rectangle_themsv(pre_y, pre_x);
					setcolor(clblue);
					rectangle(x, y, x + 230, y + 30);
					pre_y = 0;
					pre_x = j;
					break;
				}
				x += 230;
				if (mx > x && my > y && mx < x + 265 && my < y + 30)
				{ // HO
					for (int k = 0; k < sl; k++)
						pos_x[k] = false;
					pos_y[1] = pos_x[j] = true;
					pos_y[0] = pos_y[2] = pos_y[4] = pos_y[5] = false;
					remove_color_rectangle_themsv(pre_y, pre_x);
					setcolor(clblue);
					rectangle(x, y, x + 265, y + 30);
					pre_y = 1;
					pre_x = j;
					break;
				}
				x += 265;
				if (mx > x && my > y && mx < x + 100 && my < y + 30)
				{ // Ten
					for (int k = 0; k < sl; k++)
						pos_x[k] = false;
					pos_y[2] = pos_x[j] = true;
					pos_y[1] = pos_y[0] = pos_y[4] = pos_y[5] = false;
					remove_color_rectangle_themsv(pre_y, pre_x);
					setcolor(clblue);
					rectangle(x, y, x + 100, y + 30);
					pre_y = 2;
					pre_x = j;
					break;
				}
				x += 100;
				if (mx > x + 10 && my > y + 3 && mx < x + 60 && my < y + 27)
				{																   // Phai nam
					draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, claqua); // to mau o nam
					setbkcolor(claqua);
					setcolor(clblack);
					outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
					Phai[j] = "Nam";
					draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, cllightwhite); // xoa mau o Nu
					setbkcolor(cllightwhite);
					outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
				}
				if (mx > x + 90 && my > y + 3 && mx < x + 140 && my < y + 27)
				{ // Phai nu
					draw_rectangle(x + 90 + 1, y + 3 + 1, x + 140, y + 27, claqua);
					setbkcolor(claqua);
					setcolor(clblack);
					outtextxy(x + 115 - textwidth("Nu"), y + 6, "Nu");
					Phai[j] = "Nu";
					draw_rectangle(x + 10 + 1, y + 3 + 1, x + 60, y + 27, cllightwhite);
					setbkcolor(cllightwhite);
					outtextxy(x + 35 - textwidth("Nam"), y + 6, "Nam");
				}
				x += 150;
				if (mx > x && my > y && mx < x + 100 && my < y + 30)
				{ // SDT
					for (int k = 0; k < sl; k++)
						pos_x[k] = false;
					pos_y[4] = pos_x[j] = true;
					pos_y[1] = pos_y[2] = pos_y[0] = pos_y[5] = false;
					remove_color_rectangle_themsv(pre_y, pre_x);
					setcolor(clblue);
					rectangle(x, y, x + 100, y + 30);
					pre_y = 4;
					pre_x = j;
					break;
				}
				x += 100;
				if (mx > x && my > y && mx < x + 70 && my < y + 30)
				{ // Nam Nhap Hoc
					for (int k = 0; k < sl; k++)
						pos_x[k] = false;
					pos_y[5] = pos_x[j] = true;
					pos_y[1] = pos_y[2] = pos_y[4] = pos_y[0] = false;
					remove_color_rectangle_themsv(pre_y, pre_x);
					setcolor(clblue);
					rectangle(x, y, x + 70, y + 30);
					pre_y = 5;
					pre_x = j;
					break;
				}
				y += 30;
			}

			x = frame_left + 40;
			if (mx > x && my > y_hdsd - 40 && mx < x + 100 && my < y_hdsd - 5)
			{ // Button Luu
				if (condition_them_sv(Mssv, Ho, Ten, Phai, SDT, NamNH, First_sv, sl, i))
					return;
			}

			x += 110;
			if (mx > x && my > y_hdsd - 40 && mx < x + 100 && my < y_hdsd - 5 && sl < 15)
			{ // Button them dong
				if (Mssv[sl - 1].length() == 0 || Ho[sl - 1].length() == 0 || Ten[sl - 1].length() == 0 || Phai[sl - 1].length() == 0 || SDT[sl - 1].length() == 0 || NamNH[sl - 1].length() == 0)
				{
					MessageBox(NULL, "Phai Nhap Du Thong Tin!!!", "Thong bao", MB_OK | MB_ICONWARNING);
				}
				else
				{
					if (SDT[sl - 1].length() < 10 || SDT[sl - 1][0] != '0')
						MessageBox(NULL, "Vui Long Nhap Dung SDT!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					else if (NamNH[sl - 1].length() < 4)
						MessageBox(NULL, "Vui Long Nhap Dung Nam Nhap Hoc!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					else if (!check_trung(Mssv, sl, First_sv))
					{
						them_dong(++sl);
					}
					else
					{
						MessageBox(NULL, "Trung MSSV!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					}
				}
			}
			// xoa bang quay lai trang (Button X)
			if (mx > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && my > frame_top + dis_frame_main * 4 + w_subframe && mx < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && my < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
			{

				if (Mssv[sl - 1].length() == 0 && Ho[sl - 1].length() == 0 && Ten[sl - 1].length() == 0 && Phai[sl - 1].length() == 0 && SDT[sl - 1].length() == 0 && NamNH[sl - 1].length() == 0)
				{
					refresh_content();
					cur_page = 1;
					in_dssv(First_sv, i, 1);
					return;
				}

				int res = MessageBox(NULL, "Ban Co Muon Luu Khong!!!", "Thong bao", MB_OKCANCEL | MB_ICONWARNING);

				if (res == 1)
				{
					if (condition_them_sv(Mssv, Ho, Ten, Phai, SDT, NamNH, First_sv, sl, i))
						return;
				}
				else
				{
					return;
				}
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		delay(100);
	}
}
