#pragma once

#include "Function.h"
#include "Sinhvien.h"
#include "CTDL.h"
void free_DSDK(LIST_DSSVDK &dssvdk)
{
	delete[] dssvdk.list_svdk;
	dssvdk.list_svdk = NULL;
	dssvdk.sl_svdk = 0;
}
void free_DS_LTC(DS_LTC& dsltc) {
    for (int i = 0; i < dsltc.sl_ltc; i++) {
        free_DSDK(dsltc.ds_loptc[i]->dssvdk);
		delete dsltc.ds_loptc[i];
    }
    dsltc.sl_ltc = 0;
}
void add_SVDK(LIST_DSSVDK &dssvdk, DANGKY svdk, int svmax) {
	if(dssvdk.sl_svdk == svmax) {
		cout << "lop day";
		return;
	}
	// neu danh sach dang ky rong thi them sinh vien vao dau
    if(dssvdk.sl_svdk == 0) {
    	dssvdk.list_svdk[dssvdk.sl_svdk++] = svdk;
    	return;
	}
	
    int left = 0, right = dssvdk.sl_svdk - 1;
    int mid = 0;
    
    // tim vi tri de chen sinh vien
    while (left <= right) {
        mid = (left + right) / 2;
        if (dssvdk.list_svdk[mid].MASV.compare(svdk.MASV) == 0) {
            return;
        } else if (dssvdk.list_svdk[mid].MASV.compare(svdk.MASV) == 1) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    // chen sinh vien
    int pos = left;

    for (int i = dssvdk.sl_svdk; i > pos; i--) {
        dssvdk.list_svdk[i] = dssvdk.list_svdk[i - 1];
    }
    dssvdk.list_svdk[pos] = svdk;
    dssvdk.sl_svdk++;
}

int findPosSinhVien(LIST_DSSVDK dssvdk, string masv) {
	int left = 0, right = dssvdk.sl_svdk - 1;
	int mid = 0;
	while(left <= right) {
		mid = (left + right) / 2;
		if(dssvdk.list_svdk[mid].MASV == masv) {
			return mid;
		}else if(dssvdk.list_svdk[mid].MASV > masv) {
			right = mid - 1;
		}else {
			left = mid + 1;
		}
	}
	return -1;
}

void delete_SVDK(LIST_DSSVDK &dssvdk, string masv) {
	if(dssvdk.sl_svdk > 0) {
		int pos = findPosSinhVien(dssvdk, masv);
		if(pos != -1) { 
			for(int i = pos; i < dssvdk.sl_svdk - 1; i++) {
				dssvdk.list_svdk[i] = dssvdk.list_svdk[i + 1];
			}
			dssvdk.sl_svdk--;
		}else {
			cout << "khong tim thay sv";
		}
	}
}

float findDiem_SVDK(LIST_DSSVDK dssvdk, string masv) {
	int left = 0, right = dssvdk.sl_svdk - 1;
	int mid = 0;
	while(left <= right) {
		mid = (left + right) / 2;
		if(dssvdk.list_svdk[mid].MASV == masv) {
			return dssvdk.list_svdk[mid].diem;
		}else if(dssvdk.list_svdk[mid].MASV > masv) {
			right = mid - 1;
		}else {
			left = mid + 1;
		}
	}
	return -2;
}

void thongKeDSDK(PTR_SV &First_DSDK, PTR_SV First, LIST_DSSVDK &dssvdk) {
	
	for(int i = 0; i < dssvdk.sl_svdk; i++) {
		PTR_SV res = layInfoSV(First, dssvdk.list_svdk[i].MASV);
		if(res != NULL) {
			Insert_Order(First_DSDK, res);
		}else {
			cout << "\nKhong tim thay: " << dssvdk.list_svdk[i].MASV;
			delete_SVDK(dssvdk, dssvdk.list_svdk[i].MASV);
			i--;
		}
	}
}

void locDS_DK(LIST_DSSVDK dssvdk, string masv, LIST_DSSVDK &dssvdkFilter) {
	dssvdkFilter.sl_svdk = 0;
	for(int i = 0; i < dssvdk.sl_svdk; i++) {
		if(dssvdk.list_svdk[i].MASV.find(masv) != -1) {
			dssvdkFilter.list_svdk[dssvdkFilter.sl_svdk++] = dssvdk.list_svdk[i];
		}
	}
}

void freeDS_DK(LIST_DSSVDK &dssvdk) {
	delete[] dssvdk.list_svdk;
}

void in_dssvdk(LIST_DSSVDK &dssvdk, PTR_SV First, int current){
	// content -- open --
	PTR_SV First_DSDK = NULL;
	thongKeDSDK(First_DSDK, First, dssvdk);
	
    int y = y_hdsd;
    int x = frame_left + 40;
    string temp;
    string s1[]={"STT","Ma Sinh Vien","Ho","Ten","Phai","Lop"};
	setbkcolor(cllightwhite);
	setfillstyle(1,cllightwhite);
	rectangle(x, y, x+50, y+30);
	outtextxy(x+25-textwidth(s1[0].c_str())/2, y+5,s1[0].c_str());
	x+=50;
	rectangle(x,y,x+250, y+30);
	outtextxy(x+125-textwidth(s1[1].c_str())/2, y+5,s1[1].c_str());
	x+=250;
	rectangle(x,y,x+265,y+30);
	outtextxy(x+132-textwidth(s1[2].c_str())/2, y+5,s1[2].c_str());
	x+=265;
	rectangle(x,y,x+100, y+30);
	outtextxy(x+50-textwidth(s1[3].c_str())/2, y+5,s1[3].c_str());
	x+=100;
	rectangle(x,y,x+100, y+30);
	outtextxy(x+50-textwidth(s1[4].c_str())/2, y+5,s1[4].c_str());
	x+=100;
	rectangle(x,y, x+200, y+30);
	outtextxy(x+100-textwidth(s1[5].c_str())/2, y+5,s1[5].c_str());
	y+=30;
	
    int page = dssvdk.sl_svdk / 15;
    int du = dssvdk.sl_svdk % 15;
    int line = 0;
    if(du != 0)	page++;
    int j = 1;
    for(int i=1; i <= page; i++){
    	if(i==page && du!=0)	line+= du;
    	else line+=15;
    	if(current == i)	break;
    	j+=15;
    }
    PTR_SV p = First_DSDK;
    for(int i = 1; i < j && p != NULL; i++, p = p->pnext);
	for(; j <= line && p != NULL; j++, p = p->pnext){
		x = frame_left + 40;
				setbkcolor(cllightwhite);
				setfillstyle(1,cllightwhite);
				bar(x, y, x+50, y+30);
				rectangle(x, y, x+50, y+30);
				temp = int_to_string(j);
				outtextxy(x+25-textwidth(temp.c_str())/2,y+6,temp.c_str());
				x+=50;
				bar(x,y,x+250, y+30);
				rectangle(x,y,x+250, y+30);
				outtextxy(x+125-textwidth(p ->data.MASV.c_str())/2,y+6,p ->data.MASV.c_str());
				x+=250;
				bar(x,y,x+265,y+30);
				rectangle(x,y,x+265,y+30);
				outtextxy(x+10,y+6,p->data.HO.c_str());
				x+=265;
				bar(x,y,x+100, y+30);
				rectangle(x,y,x+100, y+30);
				outtextxy(x+10,y+6,p->data.TEN.c_str());
				x+=100;
				bar(x,y,x+100, y+30);
				rectangle(x,y,x+100, y+30);
				outtextxy(x+50-textwidth(p->data.PHAI.c_str())/2,y+6,p->data.PHAI.c_str());
				x+=100;
				bar(x,y, x+200, y+30);
				rectangle(x,y, x+200, y+30);
				outtextxy(x+100-textwidth(p->data.MALOP.c_str())/2,y+6,p->data.MALOP.c_str());
				y+=30;
	}
	y++;
	if(current == page) {
		draw_rectangle(frame_left+40,y,frame_left+980+30,685,cllightwhite);
	}
	string s ; s = int_to_string(page);
	s = '/' + s;
	string b; b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy( frame_left+(frame_right-frame_left)/2 - textwidth(s.c_str()),696,s.c_str());
	free_dssv(First_DSDK);
}

void DSSVDK_LTC(PTR_SV First, LIST_DSSVDK &dssvdk, int maltc, string tenmon, int soluong, bool tt, int nienkhoa, int hocky, int nhom) {
	refresh_content();
	string s[] = {"DANH SACH SINH VIEN 1 LOP TIN CHI", "Ma Lop:", "Ten Mon Hoc:", "So Luong:", "Trang Thai:", "Nien Khoa:", "Hoc Ky:", "Nhom:", "Nhap ma sinh vien:"};
	draw_rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10,cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10);
	outtextxy(frame_left+507-textwidth(s[0].c_str())/2,frame_top+dis_frame_main*5+1,s[0].c_str());
	setcolor(clblack);
	setbkcolor(cllightwhite);
	//in malop
	int x = frame_left;
	int y = frame_top;
	outtextxy(x+300-textwidth(s[1].c_str()),y+dis_frame_main*7,s[1].c_str());
	string temp = int_to_string(maltc);
	outtextxy(x+300+2,y+dis_frame_main*7,temp.c_str());
	x += 300 + 2 + 50;
	//in ten mon hoc
	outtextxy(x,y+dis_frame_main*7,s[2].c_str());
	x += textwidth(s[2].c_str());
	outtextxy(x+2,y+dis_frame_main*7,tenmon.c_str());
	x += (textwidth(tenmon.c_str()) + 50);
	// in so luong
	outtextxy(x,y+dis_frame_main*7,s[3].c_str());
	temp = int_to_string(soluong);
	x += textwidth(s[3].c_str());
	outtextxy(x+2,y+dis_frame_main*7,temp.c_str());
	x = frame_left;
	// in trangthai
	outtextxy(x+300+20-textwidth(s[4].c_str()),y+dis_frame_main*8,s[4].c_str());
	temp = tt == true ? "Dang Mo Lop" : "Da Dong";
	outtextxy(x+300+20+2,y+dis_frame_main*8,temp.c_str());
	x += 320+2+50+textwidth(temp.c_str());
	// in nien khoa
	outtextxy(x,y+dis_frame_main*8,s[5].c_str());
	temp = int_to_string(nienkhoa);
	x += textwidth(s[5].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());
	x += textwidth(temp.c_str()) + 50;
	// in hoc ky
	outtextxy(x,y+dis_frame_main*8,s[6].c_str());
	temp = int_to_string(hocky);
	x += textwidth(s[6].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());
	x += textwidth(temp.c_str()) + 50;
	// in nhom
	outtextxy(x,y+dis_frame_main*8,s[7].c_str());
	temp = int_to_string(nhom);
	x += textwidth(s[7].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());
	
	// Nhap ma sinh vien de tim kiem
	outtextxy(frame_right - 300 - textwidth(s[8].c_str()),y_hdsd-34,s[8].c_str());
	x = frame_right - 40;
	setcolor(clblack);
	setfillstyle(1,cllightgreen); 
	bar(x-40,y_hdsd-40,x,y_hdsd-10);
	rectangle(x-40,y_hdsd-40,x,y_hdsd-10);
	
	// icon tim kiem
	setbkcolor(cllightgreen);
	setusercharsize(5,5,1,2);
	outtextxy(x-27,y_hdsd-40+1+7,"\\");
	setusercharsize(3,5,1,2);
	outtextxy(x-31,y_hdsd-40+1,"O");
	setusercharsize(2,5,1,2);
	x-=50;
	setcolor(clblue);
	rectangle(x-210,y_hdsd-40,x,y_hdsd-10);
	setcolor(clblack);
	
	cur_page = 1;
	in_dssvdk(dssvdk, First, cur_page);
	button_page();
}

void in_dsdiemltc(LIST_DSSVDK &dssvdk, PTR_SV First, int current){
	// content -- open --
	PTR_SV First_DSDK = NULL;
	thongKeDSDK(First_DSDK, First, dssvdk);
	
    int y = y_hdsd;
    int x = frame_left + 40;
    string temp;
    string s1[]={"STT","Ma Sinh Vien","Ho","Ten","Lop","Diem"};
	setbkcolor(cllightwhite);
	setfillstyle(1,cllightwhite);
	rectangle(x, y, x+50, y+30);
	outtextxy(x+25-textwidth(s1[0].c_str())/2, y+5,s1[0].c_str());
	x+=50;
	rectangle(x,y,x+250, y+30);
	outtextxy(x+125-textwidth(s1[1].c_str())/2, y+5,s1[1].c_str());
	x+=250;
	rectangle(x,y,x+265,y+30);
	outtextxy(x+132-textwidth(s1[2].c_str())/2, y+5,s1[2].c_str());
	x+=265;
	rectangle(x,y,x+100, y+30);
	outtextxy(x+50-textwidth(s1[3].c_str())/2, y+5,s1[3].c_str());
	x+=100;
	rectangle(x,y,x+200, y+30);
	outtextxy(x+100-textwidth(s1[4].c_str())/2, y+5,s1[4].c_str());
	x+=200;
	rectangle(x,y, x+100, y+30);
	outtextxy(x+50-textwidth(s1[5].c_str())/2, y+5,s1[5].c_str());
	y+=30;
	
    int page = dssvdk.sl_svdk / 15;
    int du = dssvdk.sl_svdk % 15;
    int line = 0;
    if(du != 0)	page++;
    int j = 1;
    for(int i=1; i <= page; i++){
    	if(i==page && du!=0)	line+= du;
    	else line+=15;
    	if(current == i)	break;
    	j+=15;
    }
    PTR_SV p = First_DSDK;
    for(int i = 1; i < j && p != NULL; i++, p = p->pnext);
	for(; j <= line && p != NULL; j++, p = p->pnext){
		x = frame_left + 40;
				setbkcolor(cllightwhite);
				setfillstyle(1,cllightwhite);
				bar(x, y, x+50, y+30);
				rectangle(x, y, x+50, y+30);
				temp = int_to_string(j);
				outtextxy(x+25-textwidth(temp.c_str())/2,y+6,temp.c_str());
				x+=50;
				bar(x,y,x+250, y+30);
				rectangle(x,y,x+250, y+30);
				outtextxy(x+125-textwidth(p ->data.MASV.c_str())/2,y+6,p ->data.MASV.c_str());
				x+=250;
				bar(x,y,x+265,y+30);
				rectangle(x,y,x+265,y+30);
				outtextxy(x+10,y+6,p->data.HO.c_str());
				x+=265;
				bar(x,y,x+100, y+30);
				rectangle(x,y,x+100, y+30);
				outtextxy(x+10,y+6,p->data.TEN.c_str());
				x+=100;
				bar(x,y, x+200, y+30);
				rectangle(x,y, x+200, y+30);
				outtextxy(x+100-textwidth(p->data.MALOP.c_str())/2,y+6,p->data.MALOP.c_str());
				x+=200;
				
				// in diem cua sinh vien trong lop tc do
				float diem = findDiem_SVDK(dssvdk, p->data.MASV);
				temp = float_to_string(diem);
				if(temp == "-1") temp = "  ";
				bar(x,y, x+100, y+30);
				rectangle(x,y, x+100, y+30);
				outtextxy(x+50-textwidth(temp.c_str())/2,y+6,temp.c_str());
				y+=30;
	}
	y++;
	if(current == page) {
		draw_rectangle(frame_left+40,y,frame_left+980+30,686,cllightwhite);
	}
	string s ; s = int_to_string(page);
	s = '/' + s;
	string b; b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy( frame_left+(frame_right-frame_left)/2 - textwidth(s.c_str()),696,s.c_str());
	free_dssv(First_DSDK);
}

void in_dsRepairDiem(LIST_DSSVDK &dssvdk, PTR_SV First_DSDK, int current, string diem[]){
	// content -- open --
	
    int y = y_hdsd;
    int x = frame_left + 40;
    string temp;
    string s1[]={"STT","Ma Sinh Vien","Ho","Ten","Lop","Diem"};
	setbkcolor(cllightwhite);
	setfillstyle(1,cllightwhite);
	rectangle(x, y, x+50, y+30);
	outtextxy(x+25-textwidth(s1[0].c_str())/2, y+5,s1[0].c_str());
	x+=50;
	draw_rectangle(x, y, x + 250, y + 30, cllightwhite);
	rectangle(x,y,x+250, y+30);
	outtextxy(x+125-textwidth(s1[1].c_str())/2, y+5,s1[1].c_str());
	x+=250;
	draw_rectangle(x, y, x + 265, y + 30, cllightwhite);
	rectangle(x,y,x+265,y+30);
	outtextxy(x+132-textwidth(s1[2].c_str())/2, y+5,s1[2].c_str());
	x+=265;
	draw_rectangle(x, y, x + 100, y + 30, cllightwhite);
	rectangle(x,y,x+100, y+30);
	outtextxy(x+50-textwidth(s1[3].c_str())/2, y+5,s1[3].c_str());
	x+=100;
	draw_rectangle(x, y, x + 200, y + 30, cllightwhite);
	rectangle(x,y,x+200, y+30);
	outtextxy(x+100-textwidth(s1[4].c_str())/2, y+5,s1[4].c_str());
	x+=200;
	rectangle(x,y, x+100, y+30);
	outtextxy(x+50-textwidth(s1[5].c_str())/2, y+5,s1[5].c_str());
	y+=30;
	
    int page = dssvdk.sl_svdk / 15;
    int du = dssvdk.sl_svdk % 15;
    int line = 0;
    if(du != 0)	page++;
    int j = 1;
    for(int i=1; i <= page; i++){
    	if(i==page && du!=0)	line+= du;
    	else line+=15;
    	if(current == i)	break;
    	j+=15;
    }
    PTR_SV p = First_DSDK;
    for(int i = 1; i < j && p != NULL; i++, p = p->pnext);
	for(; j <= line && p != NULL; j++, p = p->pnext){
		x = frame_left + 40;
		setbkcolor(cllightwhite);
		setfillstyle(1,cllightwhite);
		bar(x, y, x+50, y+30);
		rectangle(x, y, x+50, y+30);
		temp = int_to_string(j);
		outtextxy(x+25-textwidth(temp.c_str())/2,y+6,temp.c_str());
		x+=50;
		bar(x,y,x+250, y+30);
		rectangle(x,y,x+250, y+30);
		outtextxy(x+125-textwidth(p ->data.MASV.c_str())/2,y+6,p ->data.MASV.c_str());
		x+=250;
		bar(x,y,x+265,y+30);
		rectangle(x,y,x+265,y+30);
		outtextxy(x+10,y+6,p->data.HO.c_str());
		x+=265;
		bar(x,y,x+100, y+30);
		rectangle(x,y,x+100, y+30);
		outtextxy(x+10,y+6,p->data.TEN.c_str());
		x+=100;
		bar(x,y, x+200, y+30);
		rectangle(x,y, x+200, y+30);
		outtextxy(x+100-textwidth(p->data.MALOP.c_str())/2,y+6,p->data.MALOP.c_str());
		x+=200;
			
		bar(x,y, x+100, y+30);
		rectangle(x,y, x+100, y+30);
		outtextxy(x+50-textwidth(diem[j - 1].c_str())/2,y+6,diem[j - 1].c_str());
		y+=30;
	}
	y++;
	if(current == page) {
		draw_rectangle(frame_left+40,y,frame_left+980+30,686,cllightwhite);
	}
	string s ; s = int_to_string(page);
	s = '/' + s;
	string b; b = int_to_string(current);
	s = b + s;
	setbkcolor(cllightwhite);
	outtextxy( frame_left+(frame_right-frame_left)/2 - textwidth(s.c_str()),696,s.c_str() );
}

void DSDIEM_LTC(PTR_SV First, LIST_DSSVDK &dssvdk, int maltc, string tenmon, int soluong, bool tt, int nienkhoa, int hocky, int nhom, Change_LTC type) {
	refresh_content();
	string s[] = {"DANH SACH SINH VIEN 1 LOP TIN CHI", "Ma Lop:", "Ten Mon Hoc:", "So Luong:", "Trang Thai:", "Nien Khoa:", "Hoc Ky:", "Nhom:", "Nhap ma sinh vien:", "Sua diem", "Luu diem", "Tim sinh vien", "Nhap diem"};
	draw_rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10,cllightgreen);
	setbkcolor(cllightgreen);
	setcolor(clred);
	rectangle(frame_left+507-200,frame_top+dis_frame_main*4+10,
		frame_left+507+200,frame_top+dis_frame_main*6+10);
	outtextxy(frame_left+507-textwidth(s[0].c_str())/2,frame_top+dis_frame_main*5+1,s[0].c_str());
	setcolor(clblack);
	setbkcolor(cllightwhite);
	//in malop
	int x = frame_left;
	int y = frame_top;
	outtextxy(x+300-textwidth(s[1].c_str()),y+dis_frame_main*7,s[1].c_str());
	string temp = int_to_string(maltc);
	outtextxy(x+300+2,y+dis_frame_main*7,temp.c_str());
	x += 300 + 2 + 50;
	//in ten mon hoc
	outtextxy(x,y+dis_frame_main*7,s[2].c_str());
	x += textwidth(s[2].c_str());
	outtextxy(x+2,y+dis_frame_main*7,tenmon.c_str());
	x += (textwidth(tenmon.c_str()) + 50);
	// in so luong
	outtextxy(x,y+dis_frame_main*7,s[3].c_str());
	temp = int_to_string(soluong);
	x += textwidth(s[3].c_str());
	outtextxy(x+2,y+dis_frame_main*7,temp.c_str());
	x = frame_left;
	// in trangthai
	outtextxy(x+300+20-textwidth(s[4].c_str()),y+dis_frame_main*8,s[4].c_str());
	temp = tt == true ? "Dang Mo Lop" : "Da Dong";
	outtextxy(x+300+20+2,y+dis_frame_main*8,temp.c_str());
	x += 320+2+50+textwidth(temp.c_str());
	// in nien khoa
	outtextxy(x,y+dis_frame_main*8,s[5].c_str());
	temp = int_to_string(nienkhoa);
	x += textwidth(s[5].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());
	x += textwidth(temp.c_str()) + 50;
	// in hoc ky
	outtextxy(x,y+dis_frame_main*8,s[6].c_str());
	temp = int_to_string(hocky);
	x += textwidth(s[6].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());
	x += textwidth(temp.c_str()) + 50;
	// int nhom
	outtextxy(x,y+dis_frame_main*8,s[7].c_str());
	temp = int_to_string(nhom);
	x += textwidth(s[7].c_str());
	outtextxy(x+2,y+dis_frame_main*8,temp.c_str());

	if(type == REPAIR_LTC) {
		// luu sua doi diem
		x = frame_left + 40;
		draw_rectangle(x,y_hdsd-40,x+100,y_hdsd-5,claqua);
		rectangle(x,y_hdsd-40,x+100,y_hdsd-5);
		setbkcolor(claqua);
		outtextxy(x+50-textwidth(s[10].c_str())/2,y_hdsd-32,s[10].c_str());
		x += 100 + 20;
		draw_rectangle(x,y_hdsd-40,x+100,y_hdsd-5,claqua);
		rectangle(x,y_hdsd-40,x+100,y_hdsd-5);
		setbkcolor(claqua);
		outtextxy(x+50-textwidth(s[11].c_str())/2,y_hdsd-32,s[11].c_str());
	}else {
		//int nhap ten sv
		outtextxy(frame_right - 300 - textwidth(s[8].c_str()),y_hdsd-34,s[8].c_str());
		x = frame_right - 40;
		setcolor(clblack);
		setfillstyle(1,cllightgreen); // t?m kiem
		bar(x-40,y_hdsd-40,x,y_hdsd-10);
		rectangle(x-40,y_hdsd-40,x,y_hdsd-10);
		
		// icon tim kiem
		setbkcolor(cllightgreen);
		setusercharsize(5,5,1,2);
		outtextxy(x-27,y_hdsd-40+1+7,"\\");
		setusercharsize(3,5,1,2);
		outtextxy(x-31,y_hdsd-40+1,"O");
		setusercharsize(2,5,1,2);
		x-=50;
		setcolor(clblue);
		rectangle(x-210,y_hdsd-40,x,y_hdsd-10);
		setcolor(clblack);
		
		bool check = true;
		for(int i = 0; i < dssvdk.sl_svdk; i++) {
			if(dssvdk.list_svdk[i].diem == -1) {
				check = false;
				break;
			}
		}
		//Button sua diem
		x = frame_left + 40;
		draw_rectangle(x,y_hdsd-40,x+100,y_hdsd-5,claqua);
		rectangle(x,y_hdsd-40,x+100,y_hdsd-5);
		setbkcolor(claqua);
		if(check) {
			outtextxy(x+50-textwidth(s[9].c_str())/2,y_hdsd-32,s[9].c_str());
		}else {
			outtextxy(x+50-textwidth(s[12].c_str())/2,y_hdsd-32,s[12].c_str());
		}
	}
	cur_page = 1;
	in_dsdiemltc(dssvdk, First, cur_page);
	button_page();
}

void table_suadiem(bool click_continue)
{
	string s[] = {"Tim Sinh Vien", "Nhap ma sinh vien:", "Diem:", "Tiep tuc", "Luu", "Quay lai"};
	
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 170 + w_subframe, cllightwhite);
	// thanh ngang
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200, y_hdsd + w_subframe, clred);
	draw_rectangle(x_hdsd - 100, y_hdsd + h_hdsd - 170, x_hdsd - 100 + w_table + 200, y_hdsd + h_hdsd - 170 + w_subframe, clred);
	// thanh doc
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_subframe, y_hdsd + h_hdsd - 170 + w_subframe, clred);
	draw_rectangle(x_hdsd - 100 + w_table + 200, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 170 + w_subframe, clred);
	button_x(x_btn_x_table + 100, y_btn_x_table);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());

	int y = y_hdsd + 40;
	setbkcolor(cllightwhite);
	outtextxy(x_hdsd - textwidth(s[1].c_str()) + 40, y + 6, s[1].c_str());
	if(!click_continue)	setcolor(clblue);
	rectangle(x_hdsd + 5 + 40, y, x_hdsd + 400, y + 30);
	setcolor(clblack);
	y += 50;
	if(click_continue) {
		outtextxy(x_hdsd - textwidth(s[2].c_str()) + 40, y + 6, s[2].c_str());
		setcolor(clblue);
		rectangle(x_hdsd + 5 + 40, y, x_hdsd + 400, y + 30);
		setcolor(clblack);
		y += 75;
		setbkcolor(clyellow);
		draw_rectangle(x_hdsd, y, x_hdsd + 100, y + 40, clyellow);
		rectangle(x_hdsd, y, x_hdsd + 100, y + 40);
		outtextxy(x_hdsd + 50 - textwidth(s[4].c_str()) / 2, y + 11, s[4].c_str());

		setbkcolor(cllightred);
		draw_rectangle(x_hdsd + 350, y, x_hdsd + 450, y + 40, cllightred);
		rectangle(x_hdsd + 350, y, x_hdsd + 450, y + 40);
		outtextxy(x_hdsd + 350 + 50 - textwidth(s[5].c_str()) / 2, y + 11, s[5].c_str());
	}else {
		y += 75;
		setbkcolor(clyellow);
		draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
		rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
		outtextxy(x_hdsd + w_table / 2 - textwidth(s[3].c_str()) / 2, y + 11, s[3].c_str());
	}
}

void SUA_DIEM(PTR_SV First_sv, LIST_DSSVDK &dssvdk, int maltc, string tenmon, int soluong, int nienkhoa, int hocky, int nhom) {
	Change_LTC type = REPAIR_LTC;
	DSDIEM_LTC(First_sv, dssvdk, maltc, tenmon, soluong, molop, nienkhoa, hocky, nhom, type);
	
	int page, so_du, first_pos_sv, last_pos_sv, mx, my, pos_diem = -1;
	float diem;
	Input type_input;
	string temp[soluong];
	string diem_cu;
	bool check = true;
	int x = frame_left+40+815, y; // toa do 
	enum Click {
		NHAPDIEM,
		SUADIEM
	};
	Click click = SUADIEM;
	PTR_SV First_DSDK = NULL;
	thongKeDSDK(First_DSDK, First_sv, dssvdk);
	
	PTR_SV p = First_DSDK;
	for(int i = 0; i < soluong && p != NULL; i++, p = p->pnext) {
		temp[i] = float_to_string(findDiem_SVDK(dssvdk, p->data.MASV));
		if(temp[i] == "-1") {
			temp[i] = "";
			click = NHAPDIEM;
		} 
	}
	setbkcolor(cllightwhite);
	string NhapMaSinhVien;
	while(1) {
		y = y_hdsd + 30;
		page = dssvdk.sl_svdk / 15;
		so_du = dssvdk.sl_svdk % 15;
		if(so_du != 0) page++;
		if(cur_page == page && so_du!=0 ){
			first_pos_sv = (cur_page-1) *15 + 1; // pos_sv la` vi tri' dung dau cua 1 trang
			last_pos_sv = first_pos_sv + so_du ;
		}else if(page!=0){
			first_pos_sv = (cur_page-1) *15 + 1;
			last_pos_sv = first_pos_sv + 15; 
		}
		if(pos_diem != -1) {
			for(int i = first_pos_sv; i < last_pos_sv; i++) {
				if(i == pos_diem + 1) {
					break;
				}
				y += 30;
			}
			type_input = DIEMSV;
			input(temp[pos_diem], x+10+50, y+6, type_input, 3);
			if(temp[pos_diem] == "" && click == SUADIEM) check = false;
			else check = true;
		}
		if(ismouseclick(WM_LBUTTONDOWN)) {
			y = y_hdsd + 30;
			for(int i = first_pos_sv; i < last_pos_sv; i++) {
				if(pos_diem == i - 1) {
					outtextxy(x + 10 + 50+ textwidth(temp[pos_diem].c_str()), y + 6, "  ");
					break;
				}
				y+=30;
			}
			mx = mousex();
			my = mousey();
			y = y_hdsd + 30;
			
			// Button Save
			if(mx > frame_left + 40 && my > y_hdsd - 40 && mx < frame_left + 40 + 100 && my < y_hdsd-5) {		
				if(check) {
					MessageBox(NULL,"Luu thanh cong!!!","Thong bao", MB_OK| MB_ICONWARNING);
					type = VIEW;
					view_dsdiem = true;
					p = First_DSDK;
					for(int i = 0; i < soluong && p != NULL; i++, p = p->pnext) {
						pos_diem = findPosSinhVien(dssvdk, p->data.MASV);
						if(temp[i] == "") temp[i] = "-1"; // click = nhap diem 
						dssvdk.list_svdk[pos_diem].diem = string_to_float(temp[i]);
					}
					molop = false;
					DSDIEM_LTC(First_sv, dssvdk, maltc, tenmon, soluong, molop, nienkhoa, hocky, nhom, type);
					break;
				}else {
					MessageBox(NULL,"Vui Long Nhap Du Thong Tin Truoc Khi Luu!!!","Thong bao", MB_OK| MB_ICONWARNING);
				}
			}
			
			// click button Tim sinh vien de sua diem
			if(mx > frame_left + 40 + 120 && my > y_hdsd - 40 && mx < frame_left + 40 + 220 && my < y_hdsd - 5) {
				bool click_continue = false;
				table_suadiem(click_continue);
				clearmouseclick(WM_LBUTTONDOWN);
				NhapMaSinhVien = "";
				while(1) {
					if(!click_continue) {
						type_input = NON_SPACE;
						input(NhapMaSinhVien, x_hdsd + 45 + 10, y_hdsd + 40 + 6, type_input, 15);
					}else {
						type_input = DIEMSV;
						input(temp[pos_diem], x_hdsd + 45 + 10, y_hdsd + 40 + 50 + 6, type_input, 3);
					}
					
					if(ismouseclick(WM_LBUTTONDOWN)) {
						
						mx = mousex();
						my = mousey();
						
						// button close tim sinh vien
						if (mx > x_btn_x_table + 100 && my > y_btn_x_table + w_subframe &&
						mx < x_btn_x_table + w_btn_x + 100 && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe){
							if(click_continue) {
								int yes = MessageBox(NULL,"Ban Co Muon Luu Khong!!!","Thong bao", MB_OKCANCEL| MB_ICONQUESTION);
								cur_page = 1;
								if(yes == 1) {
									if(click == SUADIEM && temp[pos_diem] == "") {
										MessageBox(NULL,"Vui Long Nhap Du Thong Tin!!!","Thong bao", MB_OK| MB_ICONWARNING);
									}else {
										in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
										pos_diem = -1;
										setbkcolor(cllightwhite);
										break;
									}
								}else {
									temp[pos_diem] = diem_cu;
									in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
									pos_diem = -1;
									setbkcolor(cllightwhite);
									break;
								}
							}else {
								in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
								pos_diem = -1;
								setbkcolor(cllightwhite);
								break;
							}
						}
						
						// click button tiep tuc
						if(mx > x_hdsd + 150 && my > y_hdsd + 40 + 50 + 75 && mx < x_hdsd + 250 && my < y_hdsd + 40 + 50 + 75 + 40) {
							if(NhapMaSinhVien == "") {
								MessageBox(NULL,"Vui Long Nhap Du Thong Tin!!!","Thong bao", MB_OK| MB_ICONWARNING);
							}else {
								diem = findDiem_SVDK(dssvdk, NhapMaSinhVien);
								p = First_DSDK;
								for(int i = 0; i < soluong; i++, p = p->pnext) {
									if(NhapMaSinhVien == p->data.MASV) {
										pos_diem = i;
										break;
									}
								}
								if(diem == -2) {
									MessageBox(NULL,"Khong Co Sinh Vien Nay!!!","Thong bao", MB_OK| MB_ICONWARNING);
								}else {
									click_continue = true;
									table_suadiem(click_continue);
									setbkcolor(cllightwhite);
									outtextxy(x_hdsd + 45 + 10, y_hdsd + 40 + 6, NhapMaSinhVien.c_str());
									outtextxy(x_hdsd + 45 + 10, y_hdsd + 40 + 50 + 6, temp[pos_diem].c_str());
									diem_cu = temp[pos_diem];
								}
							}
						}
						
						// click button luu
						if(mx > x_hdsd && my > y_hdsd + 40 + 50 + 75 && mx < x_hdsd + 100 && my < y_hdsd + 40 + 50 + 75 + 40 && click_continue) {
							if(temp[pos_diem] == "" && click == SUADIEM) {
								MessageBox(NULL,"Vui Long Nhap Du Thong Tin!!!","Thong bao", MB_OK| MB_ICONWARNING);
							}else {
								MessageBox(NULL,"Luu Thanh Cong!!!","Thong bao", MB_OK| MB_ICONWARNING);
								click_continue = false;
								cur_page = 1;
								in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
								pos_diem = -1;
								setbkcolor(cllightwhite);
								break;
							}
						}
						
						// click button quay lai
						if(mx > x_hdsd + 350 && my > y_hdsd + 40 + 50 + 75 && mx < x_hdsd + 450 && my < y_hdsd + 40 + 50 + 75 + 40 && click_continue) {
							click_continue = false;
							table_suadiem(click_continue);
							setbkcolor(cllightwhite);
							outtextxy(x_hdsd + 45 + 10, y_hdsd + 40 + 6, NhapMaSinhVien.c_str());
						}
						clearmouseclick(WM_LBUTTONDOWN);
					}
					delay(100);
				}
			}
			
			// vi tri diem de sua
			p = First_DSDK;
			for(int i = 1; i < first_pos_sv && p != NULL; i++, p = p->pnext);
			for(int i = first_pos_sv; i < last_pos_sv; i++, p = p->pnext) {
				if(mx > frame_left + 40 + 815 + 50 && my > y && mx < frame_left + 40 + 915 + 50 && my < y+30) {
					pos_diem = i - 1;
					outtextxy(x+100-textwidth(temp[pos_diem].c_str())/2, y+6, "   ");
					outtextxy(x+60, y + 6,temp[pos_diem].c_str());
					break;
				}
				y+=30;
			}
			
			// chuyen trang
			if(mx>frame_left+307 && my>690 && mx<frame_left+407 && my<715 && cur_page>1){ // back
				cur_page--;
				pos_diem = -1;
				in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
			}
			if(mx>frame_left+607 && my>690 && mx<frame_left+707 && my<715 && cur_page < page){ // next trang
				cur_page++;
				pos_diem = -1;
				if (cur_page == page) draw_rectangle(frame_left + 40,y_hdsd,frame_left+975+30+1,685+1,cllightwhite);
				in_dsRepairDiem(dssvdk, First_DSDK, cur_page, temp);
			}
			
			// Button close
			if(mx>frame_right-dis_frame_main-w_subframe*2-w_btn_x-1 && my> frame_top+dis_frame_main*4+ w_subframe 
			&& mx<frame_right-dis_frame_main-w_subframe*2-w_btn_x-1 + w_btn_x && my< frame_top+dis_frame_main*4+ w_subframe+ w_btn_x+w_subframe)
			{
				int yes = MessageBox(NULL,"Ban Co Muon Luu Khong!!!","Thong bao", MB_OKCANCEL| MB_ICONQUESTION);
				if(yes == 1) {
					if(check) {
						MessageBox(NULL,"Luu thanh cong!!!","Thong bao", MB_OK| MB_ICONWARNING);
						type = VIEW;
						view_dsdiem = true;
						molop = false;
						p = First_DSDK;
						for(int i = 0; i < soluong && p != NULL; i++, p = p->pnext) {
							pos_diem = findPosSinhVien(dssvdk, p->data.MASV);
							if(temp[i] == "") temp[i] = "-1";
							dssvdk.list_svdk[pos_diem].diem = string_to_float(temp[i]);
						}
						DSDIEM_LTC(First_sv, dssvdk, maltc, tenmon, soluong, molop, nienkhoa, hocky, nhom, type);
						break;
					}else {
						MessageBox(NULL,"Vui Long Nhap Du Thong Tin Truoc Khi Luu!!!","Thong bao", MB_OK| MB_ICONWARNING);
					}
				}
				else{
					type = VIEW;
					view_dsdiem = true;
					DSDIEM_LTC(First_sv, dssvdk, maltc, tenmon, soluong, molop, nienkhoa, hocky, nhom, type);
					break;
				}
			}
			clearmouseclick(WM_LBUTTONDOWN);	
		}	
		delay(100);
	}
	free_dssv(First_DSDK);
}


