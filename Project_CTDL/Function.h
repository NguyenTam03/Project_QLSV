#pragma once
#include <winbgim.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include "Const.h"
#include "Logo.h"
void Nguyen_Tam()
{
	setbkcolor(clyellow);
	setcolor(0);
	setusercharsize(1.75,2,1,2);
	string s = "NGUYEN THANH TAM - NGUYEN TRUNG KHANH - LUONG HAI DANG";
	int length = textwidth(s.c_str());
	// screen logo
	outtextxy((frame_left + frame_right) / 2 - length / 2, frame_top * 8 + 30 * 15, s.c_str()); // 15 la` chieu cao(y) cua chu
		setusercharsize(2,5,1,2);
}
void screen_logo()
{
	setbkcolor(cllightwhite);
	setcolor(cllightred);
	int length = textwidth(logo[0].c_str());
	// screen logo
	for(int i=0; i<27; i++)
		outtextxy((frame_left + frame_right) / 2 - length / 2, frame_top * 8 + i * 15, logo[i].c_str()); // 15 la` chieu cao(y) cua chu
	Nguyen_Tam();
}

void draw_rectangle(int left, int top, int right, int bottom, int color)
{
	setfillstyle(1, color);
	bar(left, top, right, bottom);
}
void button_x(int x, int y)
{
	setcolor(clblack);
	rectangle(x, y + w_subframe, x + w_btn_x, y + w_btn_x + w_subframe);
	setbkcolor(cllightred);
	setfillstyle(1, cllightred);
	bar(x + 1, y + w_subframe + 1, x + w_btn_x, y + w_btn_x + w_subframe);
	string s = "X";
	int length = textwidth(s.c_str());
	outtextxy(x + w_btn_x / 2 - length / 2, y + w_subframe + w_btn_x / 2 - h_word + 1, s.c_str());
}
void refresh_content()
{
	draw_rectangle(frame_left + dis_frame_main + w_subframe,
				   frame_top + dis_frame_main * 4 + w_subframe,
				   frame_right - dis_frame_main - w_subframe,
				   frame_bottom - w_frame_main, cllightwhite);
	button_x(frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1, frame_top + dis_frame_main * 4 + w_subframe);
}
void table(int x, int y, int width, int height)
{
	draw_rectangle(x, y, x + width + w_subframe, y + height + w_subframe, cllightwhite);
	// thanh ngang
	draw_rectangle(x, y, x + width, y + w_subframe, clred);
	draw_rectangle(x, y + height, x + width, y + height + w_subframe, clred);
	// thanh doc
	draw_rectangle(x, y, x + w_subframe, y + height + w_subframe, clred);
	draw_rectangle(x + width, y, x + width + w_subframe, y + height + w_subframe, clred);
	// button X
	button_x(x_btn_x_table, y_btn_x_table);
}

// --------------------
void table_hdsd()
{
	table(x_hdsd, y_hdsd, w_table, h_hdsd);
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, cllightgreen);
	setcolor(cllightred);
	rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30);
	setcolor(clblack);
	setbkcolor(cllightgreen);
	outtextxy(x_hdsd + w_table / 2 - textwidth("HDSD") / 2, y_hdsd + 9, "HDSD");
	setbkcolor(cllightwhite);
	// content
	setbkcolor(cllightwhite);
//	setusercharsize(3,6,1,2);
	setusercharsize(1.7,2,1,2);
	outtextxy(x_hdsd + w_subframe * 2, y_hdsd + w_btn_x + w_subframe * 5, "- Dung chuot de thao tac");
	outtextxy(x_hdsd + w_subframe * 2, y_hdsd + w_btn_x + w_subframe * 5 + h_word * 3, "- Khi nhap khong the thao tac voi menu");
	outtextxy(x_hdsd + w_subframe * 2, y_hdsd + w_btn_x + w_subframe * 5 + h_word * 5, "  chinh");
//	outtextxy(x_hdsd + w_subframe * 2, y_hdsd + w_btn_x + w_subframe * 5 + h_word * 8, "- Khi tat bang HDSD se tu dong ve trang 1");
	setusercharsize(2,5,1,2);
}

void button_page()
{
	setbkcolor(clyellow);
	draw_rectangle(frame_left + 322, 690, frame_left + 422, 715, clyellow); //(1245-230)/2-200 = 307
	rectangle(frame_left + 322, 690, frame_left + 422, 715);
	outtextxy(frame_left + 322 + 50 - textwidth("<-") / 2, 693, "<-"); // 50 = 100/2

	draw_rectangle(frame_left + 622, 690, frame_left + 722, 715, clyellow); // (1245-230)/2+100 = 607
	rectangle(frame_left + 622, 690, frame_left + 722, 715);
	outtextxy(frame_left + 622 + 50 - textwidth("->") / 2, 693, "->");
}
void button_MH(){
	setbkcolor(cllightgreen);
	draw_rectangle(frame_left + 565, y_hdsd - 40, frame_left + 665, y_hdsd - 15, cllightgreen); //(1245-230)/2-200 = 307
	rectangle(frame_left + 565, y_hdsd - 40, frame_left + 665, y_hdsd - 15);
	outtextxy(frame_left + 565 + 50 - textwidth("<-") / 2, y_hdsd - 37, "<-"); // 50 = 100/2
	
	draw_rectangle(frame_left + 865, y_hdsd - 40, frame_left + 965, y_hdsd - 15, cllightgreen); // (1245-230)/2+100 = 607
	rectangle(frame_left + 865, y_hdsd - 40, frame_left + 965, y_hdsd - 15);
	outtextxy(frame_left + 865 + 50 - textwidth("->") / 2, y_hdsd - 37, "->");
	setbkcolor(cllightwhite);
	outtextxy(frame_left + 765 - textwidth("Xem Cac Mon Hoc Khac")/2 , y_hdsd - 35 , "Xem Cac Mon Hoc Khac");
}
string float_to_string(float a)
{
	string s;
	stringstream ss;
	ss << a;
	s = ss.str();
	return s;
}
string int_to_string(int a)
{
	string s;
	stringstream ss;
	ss << a;
	s = ss.str();
	return s;
}
int string_to_int(string s)
{
	int a;
	stringstream ss(s);
	ss >> a;
	return a;
}
float string_to_float(string s)
{
	float a;
	stringstream ss(s);
	ss >> a;
	return a;
}
int stoi(string s)
{
	int a;
	stringstream ss(s);
	ss >> a;
	return a;
}
//string reverse(string s){
//	stringstream ss(s);
//	string temp,res;
//	while(ss>>temp)
//	res = temp + res + ' ';
//	return res;
//}
void create_frame()
{
	// main frame
	// thanh ngang
	draw_rectangle(frame_left, frame_top, frame_right, frame_top + w_frame_main, clblue);
	draw_rectangle(frame_left, frame_bottom, frame_right, frame_bottom + w_frame_main, clblue);
	// thanh doc
	draw_rectangle(frame_left, frame_top, frame_left + w_frame_main, frame_bottom, clblue);
	draw_rectangle(frame_right - w_frame_main, frame_top, frame_right, frame_bottom, clblue);

	// subframe
	// thanh ngang
	draw_rectangle(frame_left + dis_frame_main, frame_top + dis_frame_main,
				   frame_right - dis_frame_main, frame_top + w_subframe + dis_frame_main, clred);
	draw_rectangle(frame_left + dis_frame_main, frame_bottom - w_subframe * 2,
				   frame_right - dis_frame_main, frame_bottom - w_subframe, clred);
	// thanh doc chinh
	draw_rectangle(frame_left + dis_frame_main, frame_top + dis_frame_main,
				   frame_left + frame_top, frame_bottom - w_subframe, clred);
	draw_rectangle(frame_right - dis_frame_main - w_subframe, frame_top + dis_frame_main,
				   frame_right - dis_frame_main, frame_bottom - w_subframe, clred);
	// thanh doc phu
	// do rong cua option la dis_frame_main*3
	draw_rectangle(frame_left + dis_frame_main, frame_top + dis_frame_main * 4,
				   frame_right - dis_frame_main, frame_top + dis_frame_main * 4 + w_subframe, clred);
	setcolor(clblack);
	int length = 0;
	for(int i=1; i<8; i++)
	{
		// thanh doc
		draw_rectangle(frame_left + dis_frame_main + w_option * i, frame_top + dis_frame_main,
					   frame_left + dis_frame_main + w_subframe + w_option * i, frame_top + dis_frame_main * 4, 4);
		setfillstyle(1, clyellow);
		setbkcolor(clyellow);
//		if (i == 1)
//		{
//			setfillstyle(1, cllightpurple);
//			setbkcolor(cllightpurple);
//		}
		length = textwidth(option[i - 1].c_str()); // do chieu dai (toa do) cua word
		bar(frame_left + dis_frame_main + w_subframe + w_option * (i - 1), frame_top + dis_frame_main + w_subframe,
			frame_left + dis_frame_main + w_option * (i), frame_top + dis_frame_main * 4);
		outtextxy(frame_left + dis_frame_main + w_option * (i - 1) + w_option / 2 - length / 2, frame_top * 2 + h_word, option[i - 1].c_str());
	}
}


void input(string &s, int x, int y, Input type, int length)
{
	setbkcolor(cllightwhite);
	setcolor(clblack);
	char ch;
	outtextxy(x + textwidth(s.c_str()), y - 1, "|");
	while (kbhit())
	{
		ch = getch();
		if (ch == 8)
		{ // Backspace key
			if (s.length() > 0)
			{ //  xoa' ky' tu.
				s.erase(s.length() - 1);
				outtextxy(x + textwidth(s.c_str()), y, "  ");
			}
			else
			{
				outtextxy(x, y, s.c_str());
			}
			continue;
		}
		if (ch == ' ' && s.size() == 0)
		{
			outtextxy(x, y, s.c_str());
			continue;
		}
		if (s.size() < length)
		{
			switch (type)
			{
			case TEXT:
				if ((ch <= '9' && ch >= '0') || (ch >= 'a' && ch <= 'z') || ch == ' ' || ch >= 'A' && ch <= 'Z' || ch =='+' || ch=='#')
				{
					if (ch == ' ')
					{
						if (s[s.size() - 1] != ' ')
						{
							s += ch;
							outtextxy(x, y, s.c_str());
						}
					}
					else
					{
						if (s.size() == 0)
							ch = toupper(ch);
						s += ch;
						outtextxy(x, y, s.c_str());
					}
				}
				break;
			case NON_SPACE:
				if (ch >= '0' && ch <= '9')
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				{
					ch = toupper(ch);
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case NUMBER:
				if (ch >= '0' && ch <= '9')
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case SURNAME:
				if (ch == ' ')
				{
					if (s[s.length() - 1] != ' ')
					{
						s += ch;
						outtextxy(x, y, s.c_str());
					}
				}
				else if ((ch > 96 && ch < 123) || (ch > 63 && ch < 91))
				{
					if (s.length() == 0 || s[s.length() - 1] == ' ')
					{
						if (ch > 96 && ch < 123)
							ch -= 32;
					}
					else if (ch > 64 && ch < 91)
						ch += 32;
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case NAME:
				if ((ch > 96 && ch < 123) || (ch > 63 && ch < 91))
				{
					if (s.length() == 0)
					{
						if (ch > 96 && ch < 123)
							ch -= 32;
					}
					else if (ch > 64 && ch < 91)
						ch += 32;

					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case CLASS:
				if ((ch > 47 && ch < 58) || (ch > 96 && ch < 123) || ch > 63 && ch < 91 || ch == '-')
				{
					if (ch > 96 && ch < 123)
						ch -= 32;
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case HOCKY:
				if (ch >= '1' || ch <= '3')
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case ADD_HOCKY:
				if (ch == '1' || ch == '3')
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				break;
			case DIEMSV:
				if (ch >= '0' && ch <= '9' && (s.length() == 0 || s[1] == '.'))
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				if (s[0] == '1' && ch == '0')
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
				if (ch == '.' && s.length() == 1)
				{
					s += ch;
					outtextxy(x, y, s.c_str());
				}
			}
		}
	}
}

void chuanHoaChuoi(string &s) {
	if(s[s.size() - 1] == ' ') {
		s.erase(s.size() - 1, 1);
	}
	for(int i = 0; i < s.size(); i++) {
		s[i] = tolower(s[i]);
		if(s[i] == ' ' && s[i + 1] != ' ') {
			s.erase(i, 1);
			i--;
		}
	}
}
void swap(string &a, string &b)
{
	string temp = a;
	a = b;
	b = temp;
}
