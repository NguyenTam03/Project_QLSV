#pragma once

#include "Const.h"
#include "CTDL.h"
// them mon hoc ket hop voi ca sua mon hoc
void add_MH(PTR_TREE &root, MONHOC mh)
{
	if (root == NULL)
	{
		root = new NODE;
		root->info = mh;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{
		if (root->info.MAMH.compare(mh.MAMH) > 0)
		{
			add_MH(root->left, mh);
		}
		else if (root->info.MAMH.compare(mh.MAMH) < 0)
		{
			add_MH(root->right, mh);
		}
	}
}

void repair_MH(PTR_TREE &root, MONHOC mh)
{
	PTR_TREE p = root;
	while (p != NULL)
	{
		if (p->info.MAMH.compare(mh.MAMH) > 0)
		{
			p = p->left;
		}
		else if (p->info.MAMH.compare(mh.MAMH) < 0)
		{
			p = p->right;
		}
		else
		{
			p->info.MAMH = mh.MAMH;
			p->info.STCLT = mh.STCLT;
			p->info.STCTH = mh.STCTH;
			p->info.TENMH = mh.TENMH;
			return;
		}
	}
}

void replace_trangThai(PTR_TREE &root, MONHOC monhoc)
{
	PTR_TREE p = root;
	while (p != NULL)
	{
		if (p->info.MAMH.compare(monhoc.MAMH) > 0)
		{
			p = p->left;
		}
		else if (p->info.MAMH.compare(monhoc.MAMH) < 0)
		{
			p = p->right;
		}
		else
		{
			p->info.trangthai = monhoc.trangthai;
			return;
		}
	}
}
bool checkTrung_MonHoc(PTR_TREE root, MONHOC mh)
{
	PTR_TREE p = root;
	while (p != NULL)
	{
		if (p->info.MAMH.compare(mh.MAMH) == 0)
		{
			return true;
		}
		else if (p->info.MAMH.compare(mh.MAMH) > 0)
		{
			p = p->left;
		}
		else if (p->info.MAMH.compare(mh.MAMH) < 0)
		{
			p = p->right;
		}
	}
	return false;
}

// bac cua cay
// int treeLevel(PTR_TREE root) {
//	if(root == NULL) return -1;
//	if(root->left == NULL && root->right == NULL) return 0;
//	return 1 + max(treeLevel(root->left), treeLevel(root->right));
//}
//
//// kiem tra cay da can bang chua
// bool checkAVl(PTR_TREE root) {
//	if(root == NULL) return true;
//	if(abs(treeLevel(root->left) - treeLevel(root->right)) > 1) return false;
//	return checkAVl(root->left) && checkAVl(root->right);
// }
//
PTR_TREE findMinNode(PTR_TREE root)
{
	PTR_TREE cur = root;
	while (cur->left != NULL)
	{
		cur = cur->left;
	}
	return cur;
}
//
// PTR_TREE turnRight(PTR_TREE a) {
//	PTR_TREE b = a->left;
//	PTR_TREE d = b->right;
//	a->left = d;
//	b->right = a;
//	return b;
//}
//
// PTR_TREE turnLeft(PTR_TREE a) {
//	PTR_TREE b = a->right;
//	PTR_TREE c = b->left;
//	a->right = c;
//	b->left = a;
//	return b;
//}

void locDSMonHoc(MONHOC *mh, int soluongmon, MONHOC *mhFilter, string tenmonhoc, int &n)
{
	string s;
	for (int i = 0; i < soluongmon; i++)
	{
		s = mh[i].TENMH;
		chuanHoaChuoi(s);
		if(s.find(tenmonhoc) != -1) {
			mhFilter[n++] = mh[i];
		}
	}
}

// cap nhat lai cay
// PTR_TREE updateTree(PTR_TREE root) {
//	if(abs(treeLevel(root->left) - treeLevel(root->right)) > 1) {
//		if(treeLevel(root->left) > treeLevel(root->right)) {
//			PTR_TREE temp = root->left;
//			if(treeLevel(temp->left) >= treeLevel(temp->right)) {
//				root = turnRight(root);
//			}else {
//				root->left = turnLeft(root->left);
//				root = turnRight(root);
//			}
//		}else {
//			PTR_TREE temp = root->right;
//			if(treeLevel(root->right) >= treeLevel(root->left)) {
//				root = turnLeft(root);
//			}else {
//				root->right = turnRight(root->right);
//				root = turnLeft(root);
//			}
//		}
//	}
//	if(root->left != NULL) root->left = updateTree(root->left);
//	if(root->right != NULL) root->right = updateTree(root->right);
//	return root;
//}

// Xoa mon hoc
PTR_TREE delete_MH(PTR_TREE root, MONHOC mh)
{
	if (root == NULL)
	{
		return root;
	}
	if (root->info.MAMH.compare(mh.MAMH) > 0)
	{
		root->left = delete_MH(root->left, mh);
	}
	else if (root->info.MAMH.compare(mh.MAMH) < 0)
	{
		root->right = delete_MH(root->right, mh);
	}
	else
	{
		if (root->left == NULL)
		{
			PTR_TREE temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			PTR_TREE temp = root->left;
			delete root;
			return temp;
		}
		PTR_TREE temp = findMinNode(root->right);
		root->info = temp->info;
		root->right = delete_MH(root->right, temp->info);
	}
	return root;
}

// Dem so node trong cay
int CountNodeInTree(PTR_TREE root)
{
	int count = 0;
	if (root == NULL)
	{
		return 0;
	}
	return 1 + CountNodeInTree(root->left) + CountNodeInTree(root->right);
}

void transferTreeToArr(PTR_TREE root, MONHOC *mh, int &n)
{
	if (root != NULL)
	{
		transferTreeToArr(root->left, mh, n);
		mh[n++] = root->info;
		transferTreeToArr(root->right, mh, n);
	}
}

void Swap(MONHOC &a, MONHOC &b)
{
	MONHOC temp = a;
	a = b;
	b = temp;
}

void quicksort(MONHOC *mh, int left, int right)
{
	int i = left, j = right;
	MONHOC pivot = mh[(left + right) / 2];
	while (i <= j)
	{
		while (mh[i].TENMH < pivot.TENMH)
		{
			i++;
		}
		while (mh[j].TENMH > pivot.TENMH)
		{
			j--;
		}
		if (i <= j)
		{
			Swap(mh[i], mh[j]);
			i++;
			j--;
		}
	}
	if (left < j)
	{
		quicksort(mh, left, j);
	}
	if (i < right)
	{
		quicksort(mh, i, right);
	}
}

void Sort_Name(MONHOC *mh, int n)
{
	quicksort(mh, 0, n - 1);
}

bool CheckTrungMaMH(TREE tree, string mamh)
{
	PTR_TREE p = tree.root;
	while (p != NULL)
	{
		if (p->info.MAMH.compare(mamh) > 0)
		{
			p = p->left;
		}
		else if (p->info.MAMH.compare(mamh) < 0)
		{
			p = p->right;
		}
		else
		{
			return true;
		}
	}
	return false;
}

void free_DSMH(PTR_TREE &root)
{
	if (root == NULL)
		return;
	free_DSMH(root->left);
	free_DSMH(root->right);
	delete root;
	root = NULL;
}

/*------------- doc ghi file ------------- */
void readFile_DSMH(TREE &tree)
{
	tree.root = NULL;
	ifstream filein;
	filein.open("data\\DSMH.txt", ios::in);
	if (filein.is_open())
	{
		char ch;
		string s;
		int temp;
		while (!filein.eof())
		{
			MONHOC mh;
			getline(filein, s, ',');
			if (s == "")
				break;
			mh.MAMH = s;
			getline(filein, s, ',');
			mh.TENMH = s;
			filein >> temp; // doc so
			mh.STCLT = temp;
			filein >> ch; // doc dau ,
			filein >> temp;
			mh.STCTH = temp;
			filein >> ch;
			filein >> temp;
			mh.trangthai = (bool)temp;

			filein.ignore(); // loai bo ky tu \n
			add_MH(tree.root, mh);
		}
	}
	else
	{
		cout << "\nKHONG TIM THAY FILE DU LIEU DS MON HOC";
	}
	filein.close();
}

void writeFile_MH(PTR_TREE root, ofstream &fileout)
{
	char ch = ',';
	if (root != NULL)
	{
		fileout << root->info.MAMH;
		fileout << ch;
		fileout << root->info.TENMH;
		fileout << ch;
		fileout << root->info.STCLT;
		fileout << ch;
		fileout << root->info.STCTH;
		fileout << ch;
		fileout << root->info.trangthai;
		fileout << '\n';
		writeFile_MH(root->left, fileout);
		writeFile_MH(root->right, fileout);
	}
}

void writeFile_DSMH(TREE tree)
{
	ofstream fileout;
	fileout.open("data\\DSMH.txt", ios::out);
	if (fileout.is_open())
	{
		writeFile_MH(tree.root, fileout);
	}
	fileout.close();
}

void in_dsmon(TREE &tree, int current, MONHOC *monhoc, int soluongmon, Change_MH type)
{
	// content -- open --
	int y = y_hdsd;
	int x = frame_left + 40;
	string temp;
	string s1[] = {"STT", "Ma Mon Hoc", "Ten Mon Hoc", "So TC Ly Thuyet", "So TC Thuc Hanh", "Thao Tac"};
	setbkcolor(cllightwhite);
	rectangle(x, y, x + 50, y + 30);
	outtextxy(x + 25 - textwidth(s1[0].c_str()) / 2, y + 5, s1[0].c_str());
	x += 50;
	draw_rectangle(x, y, x + 800, y + 30, cllightwhite); // xoa hinh anh truoc
	rectangle(x, y, x + 150, y + 30);
	outtextxy(x + 75 - textwidth(s1[1].c_str()) / 2, y + 5, s1[1].c_str());
	x += 150;
	rectangle(x, y, x + 425, y + 30);
	outtextxy(x + 212 - textwidth(s1[2].c_str()) / 2, y + 5, s1[2].c_str());
	x += 425;
	rectangle(x, y, x + 120, y + 30);
	outtextxy(x + 60 - textwidth(s1[3].c_str()) / 2, y + 5, s1[3].c_str());
	x += 120;
	rectangle(x, y, x + 120, y + 30);
	outtextxy(x + 60 - textwidth(s1[4].c_str()) / 2, y + 5, s1[4].c_str());
	x += 120;
	rectangle(x, y, x + 100, y + 30);
	outtextxy(x + 50 - textwidth(s1[5].c_str()) / 2, y + 5, s1[5].c_str());
	y += 30;

	int page = soluongmon / 15;
	int du = soluongmon % 15;
	int line = 0;
	if (du != 0)
		page++;
	int j = 1;
	for (int i = 1; i <= page; i++)
	{
		if (i == page && du != 0)
			line += du;
		else
			line += 15;
		if (current == i)
			break;
		j += 15;
	}
	for (; j <= line; j++)
	{
		setfillstyle(1, cllightwhite);
		setbkcolor(cllightwhite);
		x = frame_left + 40;
		bar(x, y, x + 50, y + 30);
		rectangle(x, y, x + 50, y + 30);
		temp = int_to_string(j);
		outtextxy(x + 25 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
		x += 50;
		bar(x, y, x + 150, y + 30);
		rectangle(x, y, x + 150, y + 30);
		outtextxy(x + 75 - textwidth(monhoc[j - 1].MAMH.c_str()) / 2, y + 6, monhoc[j - 1].MAMH.c_str());
		x += 150;
		bar(x, y, x + 425, y + 30);
		rectangle(x, y, x + 425, y + 30);
		outtextxy(x + 10, y + 6, monhoc[j - 1].TENMH.c_str());
		x += 425;
		bar(x, y, x + 120, y + 30);
		rectangle(x, y, x + 120, y + 30);
		temp = int_to_string(monhoc[j - 1].STCLT);
		outtextxy(x + 60 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
		x += 120;
		bar(x, y, x + 120, y + 30);
		rectangle(x, y, x + 120, y + 30);
		temp = int_to_string(monhoc[j - 1].STCTH);
		outtextxy(x + 60 - textwidth(temp.c_str()) / 2, y + 6, temp.c_str());
		x += 120;

		rectangle(x, y, x + 100, y + 30);
		switch (type)
		{
		case REPAIR_MH:
			draw_rectangle(x + 3, y + 3, x + 45, y + 27, clyellow);
			rectangle(x + 3, y + 3, x + 45, y + 27);
			setbkcolor(clyellow);
			outtextxy(x + 3 + 21 - textwidth("Sua") / 2, y + 5, "Sua");

			draw_rectangle(x + 55, y + 3, x + 97, y + 27, cllightred);
			rectangle(x + 55, y + 3, x + 97, y + 27);
			setbkcolor(cllightred);
			setcolor(cllightwhite);
			outtextxy(x + 55 + 21 - textwidth("Xoa") / 2, y + 5, "Xoa");
			break;
		case CHOSE:
			draw_rectangle(x + 25, y + 3, x + 75, y + 27, cllightgreen);
			rectangle(x + 25, y + 3, x + 75, y + 27);
			setbkcolor(cllightgreen);
			outtextxy(x + 50 - textwidth("Chon") / 2, y + 5, "Chon");
			break;
		}

		setcolor(clblack);
		y += 30;
	}
	y++;
	for (; j <= 15; j++)
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
	outtextxy(frame_left + (frame_right - frame_left) / 2 - textwidth(s.c_str())/2, 696, s.c_str());
}

void MON_HOC(TREE tree)
{
	cur_page = 1;
	//	refresh_content();
	NhapTenMon = "";
	int x, y;
	string s[] = {"DANH SACH MON HOC", "TONG SO MON HOC: ", "THEM MON HOC", "Nhap Ten Mon Hoc:"};
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
	
	int soluongmon = CountNodeInTree(tree.root);
	MONHOC *monhoc = new MONHOC[soluongmon];
	soluongmon = 0;
	transferTreeToArr(tree.root, monhoc, soluongmon);
	Sort_Name(monhoc, soluongmon);
	
	temp = int_to_string(soluongmon);
	s[1] += temp;
	outtextxy(frame_left + 507 - textwidth(s[1].c_str()) / 2, frame_top + dis_frame_main * 7, s[1].c_str());
	// button -- open --
	x = frame_left + 40;
	draw_rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5, claqua);
	rectangle(x, y_hdsd - 40, x + 100, y_hdsd - 5);
	setbkcolor(claqua);
	outtextxy(x + 50 - textwidth(s[2].c_str()) / 2, y_hdsd - 32, s[2].c_str());

	// SEARCH
	// search
	x = frame_right - 40;
	setcolor(clblack);
	setfillstyle(1, cllightgreen); // t?m kiem
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
	rectangle(x - 250, y_hdsd - 40, x, y_hdsd - 10);
	setcolor(clblack);
	setbkcolor(cllightwhite);
	outtextxy(x - textwidth(s[3].c_str()) - 250 - 3, y_hdsd - 35, s[3].c_str());

	// button -- close --
	// content -- open --

	//	while(!checkAVl(tree.root)) {
	//		tree.root = updateTree(tree.root);
	//	}
	Change_MH type = REPAIR_MH;
	in_dsmon(tree, 1, monhoc, soluongmon, type);
	button_page();
	delete [] monhoc;
	// content -- close --
}

void table_themmonhoc()
{
	string s[] = {"THEM MON HOC", "Ma Mon Hoc", "Ten Mon Hoc", "STCLT", "STCTH", "THEM"};
	//	table(x_hdsd-100,y_hdsd,w_table+200,h_hdsd-80);
	// Table
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, cllightwhite);
	// thanh ngang
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200, y_hdsd + w_subframe, clred);
	draw_rectangle(x_hdsd - 100, y_hdsd + h_hdsd - 80, x_hdsd - 100 + w_table + 200, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	// thanh doc
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	draw_rectangle(x_hdsd - 100 + w_table + 200, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	button_x(x_btn_x_table + 100, y_btn_x_table);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());

	int y = y_hdsd + 40;
	setbkcolor(cllightwhite);
	outtextxy(x_hdsd - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[2].c_str()), y + 6, s[2].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[3].c_str()), y + 6, s[3].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[4].c_str()), y + 6, s[4].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);

	y += 75;
	// button Them
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[5].c_str()) / 2, y + 11, s[5].c_str());
}

void remove_color_rectangle_themmh(int pre)
{
	setcolor(clblack);
	int y = y_hdsd + 40;
	if (pre == 0)
		rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	if (pre == 1)
		rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	if (pre == 2)
		rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	if (pre == 3)
		rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
}

void THEM_MON_HOC(TREE &tree)
{
	table_themmonhoc();
	string mamonhoc, tenmon, sltcth, sltclt;
	setbkcolor(cllightwhite); // nen chu trang
	setcolor(clblack);		  // chu den
	Input type;
	int mx, my, x, y, pre(-1); // mx , my : vi tri cua click , x , y vi tri xuat chu . prep(-1) : o click xuat hien dau tien
	bool pos[4] = {false};	   //
	// click
	while (1)
	{
		y = y_hdsd + 40;
		if (pos[0])
		{
			type = NON_SPACE;
			input(mamonhoc, x_hdsd + 10, y + 6, type, 10);
		}
		y += 50;
		if (pos[1])
		{
			type = TEXT;
			input(tenmon, x_hdsd + 10, y + 6, type, 50);
		}
		y += 50;
		if (pos[2])
		{
			type = NUMBER;
			input(sltclt, x_hdsd + 10, y + 6, type, 1);
		}
		y += 50;
		if (pos[3])
		{
			type = NUMBER;
			input(sltcth, x_hdsd + 10, y + 6, type, 1);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			y = y_hdsd + 40;
			if (pre == 0)
				outtextxy(x_hdsd + 10 + textwidth(mamonhoc.c_str()), y + 6, "  ");
			y += 50;
			if (pre == 1)
				outtextxy(x_hdsd + 10 + textwidth(tenmon.c_str()), y + 6, "  ");
			y += 50;
			if (pre == 2)
				outtextxy(x_hdsd + 10 + textwidth(sltclt.c_str()), y + 6, "  ");
			y += 50;
			if (pre == 3)
				outtextxy(x_hdsd + 10 + textwidth(sltcth.c_str()), y + 6, "  ");
			//
			mx = mousex();
			my = mousey();
			y = y_hdsd + 40;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30) || pre == -1)
			{ // Ma Mon Hoc  -1 la cho no hien dau tien
				pos[0] = true;
				pos[1] = pos[2] = pos[3] = false;
				remove_color_rectangle_themmh(pre); // xoa o mau xanh da click luc trc
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 0;
			}
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30))
			{
				pos[1] = true;
				pos[0] = pos[2] = pos[3] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 1;
			}
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30))
			{
				pos[2] = true;
				pos[0] = pos[1] = pos[3] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 2;
			}
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30))
			{
				pos[3] = true;
				pos[0] = pos[2] = pos[1] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 3;
			}
			y += 75;
			if (mx > x_hdsd + 150 && my > y && mx < x_hdsd + 250 && my < y + 40)
			{ // Button them
				if (mamonhoc == "" || tenmon == "" || sltclt == "" || sltcth == "")
				{
					MessageBox(NULL, "Thong Tin Con Trong!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
				}
				else
				{
					MONHOC mh;
					mh.MAMH = mamonhoc;
					mh.TENMH = tenmon;
					mh.STCLT = string_to_int(sltclt);
					mh.STCTH = string_to_int(sltcth);
					mh.trangthai = 0;
					if (CheckTrungMaMH(tree, mamonhoc))
					{
						MessageBox(NULL, "Mon Hoc Da Ton Tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					}
					else
					{
						if (mh.STCLT == 0 && mh.STCTH == 0)
						{
							MessageBox(NULL, "STCLT Va STCTH Khong Dong Thoi = 0!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						}
						else
						{
							add_MH(tree.root, mh);
							MessageBox(NULL, "Them Mon Hoc Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
							writeFile_DSMH(tree);
							MON_HOC(tree);
							break;
						}
					}
				}
			}

			// xoa bang quay lai trang LTC
			if (mx > x_btn_x_table + 100 && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x + 100 && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe)
			{
				MON_HOC(tree);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		delay(100);
	}
}

void table_suamonhoc()
{
	string s[] = {"SUA MON HOC", "Ma Mon Hoc", "Ten Mon Hoc", "STCLT", "STCTH", "SUA"};
	
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, cllightwhite);
	// thanh ngang
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_table + 200, y_hdsd + w_subframe, clred);
	draw_rectangle(x_hdsd - 100, y_hdsd + h_hdsd - 80, x_hdsd - 100 + w_table + 200, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	// thanh doc
	draw_rectangle(x_hdsd - 100, y_hdsd, x_hdsd - 100 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	draw_rectangle(x_hdsd - 100 + w_table + 200, y_hdsd, x_hdsd - 100 + w_table + 200 + w_subframe, y_hdsd + h_hdsd - 80 + w_subframe, clred);
	button_x(x_btn_x_table + 100, y_btn_x_table);
	// tieu de
	draw_rectangle(x_hdsd + w_table / 2 - 50, y_hdsd + 7, x_hdsd + w_table / 2 + 50, y_hdsd + 30, claqua);
	setbkcolor(claqua);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[0].c_str()) / 2, y_hdsd + 9, s[0].c_str());

	int y = y_hdsd + 40;
	setbkcolor(cllightwhite);
	outtextxy(x_hdsd - textwidth(s[1].c_str()), y + 6, s[1].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[2].c_str()), y + 6, s[2].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[3].c_str()), y + 6, s[3].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
	y += 50;
	outtextxy(x_hdsd - textwidth(s[4].c_str()), y + 6, s[4].c_str());
	rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);

	y += 75;
	// button Them
	setbkcolor(clyellow);
	draw_rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40, clyellow);
	rectangle(x_hdsd + 150, y, x_hdsd + 250, y + 40);
	outtextxy(x_hdsd + w_table / 2 - textwidth(s[5].c_str()) / 2, y + 11, s[5].c_str());
}

void SUA_MON_HOC(TREE &tree, MONHOC monhoc, MONHOC *mh, int soluong)
{
	Change_MH type_mh = REPAIR_MH;
	table_suamonhoc();
	string tenmon = monhoc.TENMH, stcth, stclt;
	stclt = int_to_string(monhoc.STCLT);
	stcth = int_to_string(monhoc.STCTH);
	setbkcolor(cllightwhite);
	setcolor(clblack);
	Input type;
	int mx, my, x, y, pre(-1);
	bool pos[3] = {false};
	y = y_hdsd + 40;
	outtextxy(x_hdsd + 10, y + 6, monhoc.MAMH.c_str());
	y += 50;
	outtextxy(x_hdsd + 10, y + 6, tenmon.c_str());
	y += 50;
	outtextxy(x_hdsd + 10, y + 6, stclt.c_str());
	y += 50;
	outtextxy(x_hdsd + 10, y + 6, stcth.c_str());
	while (1)
	{
		y = y_hdsd + 40;
		y += 50;
		if (pos[0])
		{
			type = TEXT;
			input(tenmon, x_hdsd + 10, y + 6, type, 50);
		}
		y += 50;
		if (pos[1])
		{
			type = NUMBER;
			input(stclt, x_hdsd + 10, y + 6, type, 1);
		}
		y += 50;
		if (pos[2])
		{
			type = NUMBER;
			input(stcth, x_hdsd + 10, y + 6, type, 1);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			y = y_hdsd + 40;
			y += 50;
			if (pre == 1)
				outtextxy(x_hdsd + 10 + textwidth(tenmon.c_str()), y + 6, "  ");
			y += 50;
			if (pre == 2)
				outtextxy(x_hdsd + 10 + textwidth(stclt.c_str()), y + 6, "  ");
			y += 50;
			if (pre == 3)
				outtextxy(x_hdsd + 10 + textwidth(stcth.c_str()), y + 6, "  ");
			//
			mx = mousex();
			my = mousey();
			y = y_hdsd + 40;
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30) || pre == -1)
			{
				pos[0] = true;
				pos[1] = pos[2] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 1;
			}
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30))
			{
				pos[1] = true;
				pos[0] = pos[2] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 2;
			}
			y += 50;
			if ((mx > x_hdsd + 5 && my > y && mx < x_hdsd + 400 && my < y + 30))
			{
				pos[2] = true;
				pos[0] = pos[1] = false;
				remove_color_rectangle_themmh(pre);
				setcolor(clblue);
				rectangle(x_hdsd + 5, y, x_hdsd + 400, y + 30);
				pre = 3;
			}
			y += 75;
			if (mx > x_hdsd + 150 && my > y && mx < x_hdsd + 250 && my < y + 40)
			{ // Button Dang Ky
				if (tenmon == "" || stclt == "" || stcth == "")
				{
					MessageBox(NULL, "Thong Tin Con Trong!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
				}
				else
				{
					monhoc.TENMH = tenmon;
					monhoc.STCLT = string_to_int(stclt);
					monhoc.STCTH = string_to_int(stcth);

					if (monhoc.STCLT == 0 && monhoc.STCTH == 0)
					{
						MessageBox(NULL, "STCLT Va STCTH Khong DongThoi = 0!!!", "Thong bao", MB_OK | MB_ICONQUESTION);
					}
					else
					{
						repair_MH(tree.root, monhoc);
						MessageBox(NULL, "Sua Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
						writeFile_DSMH(tree);
						refresh_content();
						isclicked_mh = false;
						MON_HOC(tree);
						break;
					}
				}
			}

			// xoa bang quay lai trang
			if (mx > x_btn_x_table + 100 && my > y_btn_x_table + w_subframe &&
				mx < x_btn_x_table + w_btn_x + 100 && my < y_btn_x_table + w_subframe + w_btn_x + w_subframe){
				in_dsmon(tree, cur_page, mh, soluong, type_mh);
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		delay(100);
	}
}

void XOA_MON_HOC(TREE &tree, MONHOC monhoc)
{
	if (monhoc.trangthai == false)
	{
		int x = MessageBox(NULL, "Ban Co Chac Muon Xoa Mon Hoc Nay!!!", "Thong bao", MB_OKCANCEL | MB_ICONQUESTION);
		if (x == 1)
		{
			tree.root = delete_MH(tree.root, monhoc);
			MessageBox(NULL, "Xoa Thanh Cong!!!", "Thong bao", MB_OK | MB_ICONWARNING);
			writeFile_DSMH(tree);
			refresh_content();
			isclicked_mh = false;
			MON_HOC(tree);
		}
	}
	else
	{
		MessageBox(NULL, "Mon hoc nay da duoc dang ky lop tin chi!!!", "Thong bao", MB_OK | MB_ICONWARNING);
		refresh_content();
		MON_HOC(tree);
	}
}
void Chose_MH(int x, int y, TREE &tree, Change_MH type_mh)
{
	int x1 = frame_left + 40;
	int y1 = y_hdsd + 30;
	int soluongmon = CountNodeInTree(tree.root);
	MONHOC *monhoc = new MONHOC[soluongmon];
	soluongmon = 0;
	transferTreeToArr(tree.root, monhoc, soluongmon);
	Sort_Name(monhoc, soluongmon);

	// them mon hoc
	if (x > x1 && y > y_hdsd - 40 && x < x1 + 100 && y < y_hdsd - 5 && type_mh == REPAIR_MH)
	{
		THEM_MON_HOC(tree);
		cur_page = 1;
	}
	if (soluongmon > 0)
	{
		int first_pos_mh = 0;
		int last_pos_mh = 0;
		int soluong = 0;
		MONHOC *mhFilter = new MONHOC[soluongmon];

		if (NhapTenMon != "")
		{
			string tenmonhoc = NhapTenMon;
			chuanHoaChuoi(tenmonhoc);
			if (x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10)
			{
				soluong = 0;
				cur_page = 1;
				isclicked_mh = true;
				locDSMonHoc(monhoc, soluongmon, mhFilter, tenmonhoc, soluong);
				if (soluong == 0)
				{
					MessageBox(NULL, "Mon Hoc Khong Ton Tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					isclicked_mh = false;
					in_dsmon(tree, cur_page, monhoc, soluongmon, type_mh);
					return;
				}
				else
				{
					in_dsmon(tree, cur_page, mhFilter, soluong, type_mh);
					return;
				}
			}
			else
			{
				if (isclicked_mh)
				{
					locDSMonHoc(monhoc, soluongmon, mhFilter, tenmonhoc, soluong);
				}
				else
				{
					soluong = soluongmon;
					for (int i = 0; i < soluongmon; i++)
					{
						mhFilter[i] = monhoc[i];
					}
				}
			}
		}
		else
		{
			soluong = soluongmon;
			for (int i = 0; i < soluongmon; i++)
			{
				mhFilter[i] = monhoc[i];
			}
		}

		int page = soluong / 15;
		int so_du = soluong % 15;

		if (so_du != 0)
			page++;
		if (cur_page == page && so_du != 0)
		{
			first_pos_mh = (cur_page - 1) * 15 + 1;
			last_pos_mh = first_pos_mh + so_du;
		}
		else if (page != 0)
		{
			first_pos_mh = (cur_page - 1) * 15 + 1;
			last_pos_mh = first_pos_mh + 15;
		}

		// Sua-Xoa

		for (int i = first_pos_mh; i < last_pos_mh; i++)
		{
			switch (type_mh)
			{
			case REPAIR_MH:
				if (x > x1 + 835 + 3 + 30 && y > y1 + 3 && x < x1 + 835 + 45 + 30 && y < y1 + 27)
				{
					SUA_MON_HOC(tree, mhFilter[i - 1], mhFilter, soluong);
					cur_page = 1;
				}
				else if (x > x1 + 835 + 55+ 30 && y > y1 + 3 && x < x1 + 835 + 97+ 30 && y < y1 + 27)
				{
					XOA_MON_HOC(tree, mhFilter[i - 1]);
					cur_page = 1;
				}
				break;
			case CHOSE:
				if (x > x1 + 835 + 25+ 30 && y > y1 + 3 && x < x1 + 835 + 75+ 30 && y < y1 + 27)
				{
					tempchose = mhFilter[i - 1].MAMH;
					ischose = true;
				}
				break;
			}

			y1 += 30;
		}

		// chuyen trang
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{
			cur_page--;
			in_dsmon(tree, cur_page, mhFilter, soluongmon, type_mh);
		}

		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1+30, 685 + 1, cllightwhite);
			in_dsmon(tree, cur_page, mhFilter, soluongmon, type_mh);
		}
		delete [] mhFilter;
	}
	delete [] monhoc;
	
}
void getMaMH(int x, int y, TREE &tree, Change_MH type_mh)
{ // muc dich su dung de tra ve mon hoc khi click vao`
	refresh_content();
	int soluongmon = CountNodeInTree(tree.root);
	MONHOC *monhoc = new MONHOC[soluongmon];
	int n = 0;
	transferTreeToArr(tree.root, monhoc, n);
	Sort_Name(monhoc, soluongmon);
	in_dsmon(tree, cur_page, monhoc, soluongmon, type_mh); // in ra trang dau tien
	// search
	setcolor(clblack);
	setfillstyle(1, cllightgreen); // t?m kiem
	bar(frame_right - 40 - 40, y_hdsd - 40, frame_right - 40, y_hdsd - 10);
	rectangle(frame_right - 40 - 40, y_hdsd - 40, frame_right - 40, y_hdsd - 10);

	// icon tim kiem
	setbkcolor(cllightgreen);
	setusercharsize(5, 5, 1, 2);
	outtextxy(frame_right - 40 - 27, y_hdsd - 40 + 1 + 7, "\\");
	setusercharsize(3, 5, 1, 2);
	outtextxy(frame_right - 40 - 31, y_hdsd - 40 + 1, "O");
	setusercharsize(2, 5, 1, 2);

	setcolor(clblue);
	rectangle(frame_right - 90 - 250, y_hdsd - 40, frame_right - 90, y_hdsd - 10);
	setcolor(clblack);
	setbkcolor(cllightwhite);
	outtextxy(frame_right - 90 - textwidth("Nhap Ten Mon Hoc: ") - 250 - 3, y_hdsd - 35, "Nhap Ten Mon Hoc: ");
	while (1)
	{	// chi duoc thao tac trong phan chon mon
		// search
		Input type = TEXT;
		input(NhapTenMon, frame_right - 330, y_hdsd - 34, type, 50);
		if (NhapTenMon == "" && isclicked_mh)
		{
			int soluongmon = CountNodeInTree(tree.root);
			MONHOC *monhoc = new MONHOC[soluongmon];
			soluongmon = 0;
			transferTreeToArr(tree.root, monhoc, soluongmon);
			Sort_Name(monhoc, soluongmon);
			NhapMSSV = "";
			cur_page = 1;
			in_dsmon(tree, cur_page, monhoc, soluongmon, type_mh);
			isclicked_mh = false;
			delete[] monhoc;
		}
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			int x = mousex();
			int y = mousey();
			Chose_MH(x, y, tree,type_mh);

			if ((x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe) || ischose)
			{
				ischose = false;
				refresh_content();
				cur_page = 1;
				break;
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}
		delay(100);
	}
}
