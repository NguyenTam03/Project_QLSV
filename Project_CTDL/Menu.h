#pragma once
#include "LopTC.h"
#include "LopSV.h"
#include "Monhoc.h"
#include "Sinhvien.h"
#include "DSSVDK.h"
#include <iostream>

// ----- GRAPHICS ----- //
void background_option(int pos, PTR_SV First_sv, TREE tree, DS_LTC dsltc)
{
	int x, y;
	create_frame(); //  xoa mau o trc do
	setcolor(clblack);
	setfillstyle(1, cllightgreen);
	setbkcolor(cllightgreen);
	int length = textwidth(option[pos + 1].c_str()); // do chieu dai (toa do) cua word
	bar(frame_left + dis_frame_main + w_subframe + w_option * (pos + 1), frame_top + dis_frame_main + w_subframe,
		frame_left + dis_frame_main + w_option * (pos + 2), frame_top + dis_frame_main * 4);
	outtextxy(frame_left + dis_frame_main + w_option * (pos + 1) + w_option / 2 - length / 2, frame_top * 2 + h_word, option[pos + 1].c_str());
	if (pos == 0)
		LOP_TIN_CHI(dsltc, tree);
	if (pos == 1)
		SINH_VIEN(First_sv);
	if (pos == 2)
		MON_HOC(tree);
	if (pos == 3)
		DIEM(dsltc, tree);
}
// ----- CLOSE GRAPHICS ----- //

void animations(int x, int y, PTR_SV &First_sv, TREE &tree, DS_LTC &dsltc)
{
	if (x > frame_left + dis_frame_main + w_subframe && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 1 && y < frame_top + dis_frame_main * 4){
		draw_rectangle(frame_left + dis_frame_main + w_subframe,
						   frame_top + dis_frame_main * 4 + w_subframe,
						   frame_right - dis_frame_main - w_subframe,
						   frame_bottom - w_frame_main, cllightwhite);
		screen_logo();
		background_option(-1, First_sv, tree, dsltc);
		previous_page_index = -1;
		opt[0] = opt[1] = opt[2] = opt[3] = view_dssv = view_dsdiem = diemtb = click_diem_tk = false;	
	}
	if (opt[0] == true || opt[1] == true || opt[2] == true || opt[3] == true)
	{
		view_dsdk = false;
		view_diemtb = false;
		view_diemtk = false;
	}
	// lop tin chi
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (1) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 2 && y < frame_top + dis_frame_main * 4)
	{
		cur_page = 1;
		opt[0] = lf_ltc[0] = true;
		lf_ltc[1] = lf_ltc[2] = lf_ltc[3] = opt[1] = opt[2] = opt[3] = view_dssv = view_dsdiem = diemtb = click_diem_tk = false;
		pre_lf = -1;
		NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = NhapTenMon = "";
		hdsd = false;
		view_dssv = false; // fix loi khi nhan xem_dssv xong nhan qua lop tin chi
		refresh_content();
		background_option(0, First_sv, tree, dsltc);
		previous_page_index = 0;
	}
	// Sort // 

	// cho phep tao tac o trang LOP TIN CHI
	if (opt[0] == true)
	{ // opt[0] == true co' tac dung de danh' dau' minh dang o trang 0 va duoc thao tac tren do
		
		int x1 = frame_left + 40;
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 70 && y < y_hdsd - 5)
		{
			THEM_LTC(dsltc, tree);
			cur_page = 1;
		}
		x1 += 80;
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 70 && y < y_hdsd - 5)
		{
			NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
			if(dsltc.sl_ltc == 0){
				MessageBox(NULL, "Danh sach lop tin chi rong", "Thong bao", MB_OK | MB_ICONWARNING);
				return; 
			}
			else{
				HUY_LTC(dsltc, tree);
				cur_page = 1;
			}
			
		}
		x1 += 80;
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 100 && y < y_hdsd - 5)
		{
			NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
			if(dsltc.sl_ltc == 0){
				MessageBox(NULL, "Danh sach lop tin chi rong", "Thong bao", MB_OK | MB_ICONWARNING); 
				return; 
			}
			else{
				DANG_KY_LTC(dsltc, tree, First_sv);
				cur_page = 1;
			}
			
		}
		x1 += 110;
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 70 && y < y_hdsd - 5)
		{
			XEM_DSSV(dsltc, tree, First_sv);
			NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
			if (view_dsdk)
			{
				opt[0] = false;
				return;
			}
			cur_page = 1;
		}
		
		// button MH
		x1 = frame_right - 90;
		if (x > x1 - 75 && y > y_hdsd - 80 && x < x1 - 25 && y < y_hdsd - 50)
		{
			Change_MH type_mh = CHOSE;
			getMaMH(x, y, tree, type_mh);
			NhapMaMH = tempchose;
			LOP_TIN_CHI(dsltc, tree);
		}
		if (dsltc.sl_ltc > 0)
		{
			Change_LTC type = REPAIR_LTC;
			string temp, temp1, temp2, temp3;
			graphics_look_for(x, y); // tim kiem
			if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
			{ // Button tim` kie^m'
				isclicked_ltc = true;
				NienKhoa = NhapNienKhoa;
				HocKy = NhapHocKy;
				Nhom = NhapNhom;
				MaMH = NhapMaMH;
				count = 0;
				cur_page = 1;

				in_dsltc(dsltc, 1, tree, type);
				for (int i = 0; i < dsltc.sl_ltc; i++)
				{
					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
						count++;
				}
			}
			if (NienKhoa.length() == 0 && HocKy.length() == 0 && Nhom.length() == 0 && MaMH.length() == 0)
			{
				count = dsltc.sl_ltc;
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

				int i = dsltc.sl_ltc - 1;
				for (; pos < first_pos - 1; i--)
				{ //

					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
						pos++;
				}

				// XEM DSSV
				int y1 = y_hdsd + 30;
				for (; first_pos < last_pos; i--)
				{
					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
					{
						if (x > 1110 && y > y1 + 3 && x < 1152 && y < y1 + 27)
						{ // Sua sv;
							if(dsltc.ds_loptc[i]->nienkhoa < findMaxNienKhoa(dsltc) || (dsltc.ds_loptc[i]->nienkhoa == findMaxNienKhoa(dsltc) && dsltc.ds_loptc[i]->hocky < findMaxHocKy_Of_NienKhoa(dsltc))){
								MessageBox(NULL, "Lop tin chi da dong thi khong duoc sua", "Thong bao", MB_OK | MB_ICONWARNING);
							}
							else if (dsltc.ds_loptc[i]->huylop)
							{
								MessageBox(NULL, "Lop tin chi bi huy thi khong duoc sua", "Thong bao", MB_OK | MB_ICONWARNING);
							}
							else
							{
								SUA_LTC(dsltc, dsltc.ds_loptc[i], tree);
							}
						}
						if (x > 1162 && y > y1 + 3 && x < 1204 && y < y1 + 27)
						{ // XOA LTC
							if(dsltc.ds_loptc[i]->nienkhoa < findMaxNienKhoa(dsltc) || (dsltc.ds_loptc[i]->nienkhoa == findMaxNienKhoa(dsltc) && dsltc.ds_loptc[i]->hocky < findMaxHocKy_Of_NienKhoa(dsltc))){
								MessageBox(NULL, "Lop tin chi da dong thi khong duoc sua", "Thong bao", MB_OK | MB_ICONWARNING);
							}
							else if (dsltc.ds_loptc[i]->huylop)
							{
								MessageBox(NULL, "Lop tin chi bi huy thi khong duoc xoa", "Thong bao", MB_OK | MB_ICONWARNING);
							}
							else
							{
								if (dsltc.ds_loptc[i]->dssvdk.sl_svdk > 0)
								{
									MessageBox(NULL, "Lop tin chi da co sinh vien dang ky. Khong the xoa!!!", "Thong bao", MB_OK | MB_ICONWARNING);
								}
								else
								{
									int xoa_ltc = MessageBox(NULL, "Ban co chan chac muon xoa lop tin chi nay!!!", "Thong bao", MB_YESNO | MB_ICONQUESTION);
									if (xoa_ltc == 6)
									{ // 6 la Yes
										XoaLopTinChi(dsltc, i);
										bool coLop = checkLTC_SetTTMH(dsltc, dsltc.ds_loptc[i]->MAMH);
										if (coLop == false)
										{
											MONHOC monhoc;
											monhoc.MAMH = dsltc.ds_loptc[i]->MAMH;
											monhoc.trangthai = false;
											replace_trangThai(tree.root, monhoc);
										}
										MessageBox(NULL, "Da xoa thanh cong!!!", "Thong bao", MB_OK | MB_ICONINFORMATION);
										refresh_content();
										cur_page = 1;
										NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = "";
										LOP_TIN_CHI(dsltc, tree);
										writeDataDS_LTC(dsltc);
										return;
									}
									else
									{
										return;
									}
								}
							}
						}
						y1 += 30;
						first_pos++;
					}
				}
				// close XEM DSSV
			}

			// page
			if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
			{ // back
				cur_page--;
				in_dsltc(dsltc, cur_page, tree, type);
			}
			if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
			{ // next trang
				cur_page++;
				if (cur_page == page)
					draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 +30 + 1, 685 + 1, cllightwhite);
				in_dsltc(dsltc, cur_page, tree, type);
			}
			// close page
		}
	}

	if (view_dsdk)
	{
		int count;
		int first_pos_sv, last_pos_sv;
		LIST_DSSVDK dssvdkFilter;
		dssvdkFilter.list_svdk = new DANGKY[dsltc.ds_loptc[pos_ltc]->svmax];
		dssvdkFilter.sl_svdk = 0;
		if (NhapMSSV != "")
		{
			if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
			{ // Button tim` kie^m'
				isclicked_sv = true;
				cur_page = 1;
				locDS_DK(dsltc.ds_loptc[pos_ltc]->dssvdk, NhapMSSV, dssvdkFilter);
				if (dssvdkFilter.sl_svdk == 0)
				{
					MessageBox(NULL, "Ma Sinh Vien Khong Ton Tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					isclicked_sv = false;
					in_dssvdk(dsltc.ds_loptc[pos_ltc]->dssvdk, First_sv, cur_page);
					return;
				}
				else
				{
					in_dssvdk(dssvdkFilter, First_sv, cur_page);
					return;
				}
			}
			else
			{
				if (isclicked_sv == true)
				{
					locDS_DK(dsltc.ds_loptc[pos_ltc]->dssvdk, NhapMSSV, dssvdkFilter);
				}
				else
				{
					for (int i = 0; i < dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk; i++)
					{
						dssvdkFilter.list_svdk[dssvdkFilter.sl_svdk++] = dsltc.ds_loptc[pos_ltc]->dssvdk.list_svdk[i];
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk; i++)
			{
				dssvdkFilter.list_svdk[dssvdkFilter.sl_svdk++] = dsltc.ds_loptc[pos_ltc]->dssvdk.list_svdk[i];
			}
		}
		count = dssvdkFilter.sl_svdk;
		int page = count / 15;
		int so_du = count % 15;

		if (so_du != 0) page++;
		
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_dssvdk(dssvdkFilter, First_sv, cur_page);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1 + 30, 685 + 1, cllightwhite);
			in_dssvdk(dssvdkFilter, First_sv, cur_page);
		}
		// button close
		if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
		{
			refresh_content();
			cur_page = 1;
			background_option(0, First_sv, tree, dsltc);
			opt[0] = true;
			view_dsdk = false;
			freeDS_DK(dssvdkFilter);
			return;
		}
		freeDS_DK(dssvdkFilter);
	}
	//------ CLOSE LOP TIN CHI ------//
	// sinh vien
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (2) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 3 && y < frame_top + dis_frame_main * 4)
	{
		refresh_content();
		type_lsv = VIEW_DSSV;
		background_option(1, First_sv, tree, dsltc);
		previous_page_index = 1;
		opt[1] = true;
		opt[0] = opt[2] = opt[3] = view_dsdiem  = diemtb = click_diem_tk = view_diemtk = view_diemtb = false;
	}
	if (opt[1])	{ // opt[1] == true co' tac dung de danh' dau' minh dang o trang 1 va duoc thao tac tren do
		if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
		{ // Button tim` kie^m'
			isclicked_lsv = true;
			MaLop = NhapMaLop;
			count = 0;
			cur_page = 1;
			in_dsl(First_sv, 1);
			// count co tac dung dem so luong sinh vien can tim kiem
			for (int i = 0; i < sl_lop; i++)
			{
				if (tim_kiem_lsv(dsl[i], MaLop))
				{
					count++;
				}
			}
		}
		if (MaLop.length() == 0)
			count = sl_lop;
		int page = count / 15;
		int so_du = count % 15;
		int first_pos_lsv = 0; // vi tri dau cua trang lop
		int last_pos_lsv = 0;  // vi tri cuoi cua trang lop
		if (so_du != 0)
			page++; // dem xem co bn trang ( tat ca lop)
		if (page != 0)
		{
			if (cur_page == page && so_du != 0)
			{
				first_pos_lsv = (cur_page - 1) * 15 + 1;
				last_pos_lsv = first_pos_lsv + so_du;
			}
			else
			{
				first_pos_lsv = (cur_page - 1) * 15 + 1;
				last_pos_lsv = first_pos_lsv + 15;
			}
			pos_lsv = 1;
			for (int i = 1; i < first_pos_lsv; pos_lsv++)
			{
				if (tim_kiem_lsv(dsl[pos_lsv - 1], MaLop))
					i++;
			}
			// XEM DSSV
			int y1 = y_hdsd + 30;
			for (; first_pos_lsv < last_pos_lsv; pos_lsv++)
			{
				if (tim_kiem_lsv(dsl[pos_lsv - 1], MaLop))
				{
					if (x > 1110 && y > y1 + 3 && x < 1200 && y < y1 + 27)
					{ // 1110 toa do x bat dau xem --- dssv 1200 toa do x ket thuc dssv
						refresh_content();
						if(diemtb){
							int count_sv = 0;
							PTR_SV p = First_sv;
							for (; p != NULL && p->data.MALOP < dsl[pos_lsv - 1]; p = p->pnext);
							for(; p != NULL && p->data.MALOP == dsl[pos_lsv - 1]; p = p->pnext) {
								count_sv++;
							}
							refresh_content();
							DIEM_TB(dsltc, tree, First_sv, pos_lsv-1,count_sv);
							opt[1] = false;
							view_diemtb = true;
							return;
						}
						else if(click_diem_tk) 
						{
							int count_sv = 0;
							PTR_SV p = First_sv;
							for (; p != NULL && p->data.MALOP < dsl[pos_lsv - 1]; p = p->pnext);
							PTR_SV q = p;
							for(; p != NULL && p->data.MALOP == dsl[pos_lsv - 1]; p = p->pnext) {
								count_sv++;
							}
							refresh_content();
							DIEM_TK(dsltc, tree, q, pos_lsv-1,count_sv);
							opt[1] = false;
							view_diemtk = true;
							return;
						}
						else{
							in_dssv(First_sv, pos_lsv, 1);
							view_dssv = true; // view_dssv  = true d�? mo? thao tac duoc tren do
							opt[1] = false;	  // opt[1] = false de khoa thao tac opt[1]
							cur_page = 1;
//							x = y = -1;
							return; //  dung tai vi tri pos_lsv
						}
					}
					y1 += 30;
					first_pos_lsv++;
				}
			}
			// close XEM DSSV
		}

		// page
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_dsl(First_sv, cur_page);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1+30, 685 + 1, cllightwhite);
			in_dsl(First_sv, cur_page);
		}
		// close page
	}

	if (view_dssv) // in dssv cua lop do khi click vao`
	{
		if (x > frame_left + 40 && y > y_hdsd - 40 && x < frame_left + 140 && y < y_hdsd - 5)
		{ // THEM SV
			NhapMSSV = MSSV = "";
			clearmouseclick(WM_LBUTTONDOWN);
			THEM_SV(First_sv, pos_lsv);
			cur_page = 1;
			refresh_content();
			in_dssv(First_sv, pos_lsv, 1);
		}
		int first_pos_sv = 0;
		int last_pos_sv = 0; // vi tri cuoi cua trang hien hanh`

		int count_sv = 0; // so sinh vien cua lop do
		for (PTR_SV p = First_sv; p != NULL; p = p->pnext)
		{
			if(dsl[pos_lsv - 1].compare(p->data.MALOP) == -1)
				break;
			if (dsl[pos_lsv - 1].compare(p->data.MALOP) == 0)
				count_sv++;
		}
		PTR_SV p, t;
		if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
		{ // Button tim` kie^m'
			isclicked_sv = true;
			MSSV = NhapMSSV;
			count = 0;
			cur_page = 1;
			in_dssv(First_sv, pos_lsv, 1);
			// count co tac dung dem so luong sinh vien
			for (p = First_sv; p != NULL; p = p->pnext){
				if(dsl[pos_lsv - 1].compare(p->data.MALOP) == -1)
					break;
				if (tim_kiem_sv(p, MSSV))
					count++;
			}
		}
		if (MSSV.length() == 0)
			count = count_sv; 
		int page = count / 15;
		int so_du = count % 15;

		if (so_du != 0)
			page++; // dem xem co bn trang ( so sv cua 1 lop)

		if (cur_page == page && so_du != 0)
		{
			first_pos_sv = (cur_page - 1) * 15 + 1; // pos_sv la` vi tri' dung dau cua 1 trang
			last_pos_sv = first_pos_sv + so_du;
		}
		else if (page != 0)
		{
			first_pos_sv = (cur_page - 1) * 15 + 1;
			last_pos_sv = first_pos_sv + 15;
		}

		// Thao tac sua or xoa
		p = First_sv;
		for (int i = 1; i < first_pos_sv; p = p->pnext)
		{ // co' ta'c dung duyet toi sinh vien o dau trang (1,2,..)
			if (tim_kiem_sv(p, MSSV))
				i++; // neu trung thi moi tang i len
		}
		int y1 = y_hdsd + 30;
		for (; first_pos_sv < last_pos_sv; t = p, p = p->pnext)
		{ // duyet tu pos_dssv->line
			if (tim_kiem_sv(p, MSSV))
			{
				if (x > 1110 && y > y1 + 3 && x < 1152 && y < y1 + 27)
				{ // Sua sv
					clearmouseclick(WM_LBUTTONDOWN);
					SUA_SV(First_sv,p, pos_lsv); // p la sinh vien can sua
					NhapMSSV = MSSV = "";
					cur_page = 1;
					refresh_content();
					in_dssv(First_sv, pos_lsv, 1);
				}

				if (x > 1162 && y > y1 + 3 && x < 1204 && y < y1 + 27)
				{ // Xoa sv
					int x = MessageBox(NULL, "Ban co chac chan muon xoa sinh vien nay khong?", "Thong bao", MB_OKCANCEL | MB_ICONQUESTION);
					if (x == 1)
					{
						XOA_SV(First_sv, p->data.MASV, t);
						MessageBox(NULL, "Xoa Thanh Cong", "Thong bao", MB_OK | MB_ICONWARNING);
						NhapMSSV = MSSV = "";
						refresh_content();
						cur_page = 1;
						in_dssv(First_sv, pos_lsv, 1);
						writeFile_SV(First_sv); // Ghi File
					}
					return;
				}
				y1 += 30;
				first_pos_sv++;
			}
		}

		// page
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_dssv(First_sv, pos_lsv, cur_page);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1+30, 685 + 1, cllightwhite);
			in_dssv(First_sv, pos_lsv, cur_page);
		}

		// button close
		if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
		{
			refresh_content();
			cur_page = 1;
			background_option(1, First_sv, tree, dsltc);
			return;
		}
	}

	// mon hoc
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (3) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 4 && y < frame_top + dis_frame_main * 4)
	{
		refresh_content();
		background_option(2, First_sv, tree, dsltc);
		previous_page_index = 2;
		opt[2] = true;
		opt[0] = opt[1] = opt[3] = view_dssv = view_dsdiem = diemtb = click_diem_tk = false;
	}

	if (opt[2] == true)
	{
		Change_MH type_mh = REPAIR_MH;
		Chose_MH(x, y, tree, type_mh);
	}

	// diem
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (4) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 5 && y < frame_top + dis_frame_main * 4)
	{
		cur_page = 1;
		pre_lf = -1;
		NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = NhapTenMon = "";
		type_lsv = VIEW_DIEM;
		lf_ltc[0] = opt[3] = true;
		lf_ltc[1] = lf_ltc[2] = lf_ltc[3] = opt[0] = opt[1] = opt[2] = view_dssv = view_dsdiem = diemtb = click_diem_tk = false;
		refresh_content();
		background_option(3, First_sv, tree, dsltc);
		previous_page_index = 3;
	}
	if (opt[3])
	{
		// button MH
		int x1 = frame_right - 90;
		if (x > x1 - 75 && y > y_hdsd - 80 && x < x1 - 25 && y < y_hdsd - 50)
		{
			Change_MH type_mh = CHOSE;
			getMaMH(x, y, tree, type_mh);
			NhapMaMH = tempchose;
			DIEM(dsltc, tree);
		}
		x1 = frame_left + 40;
		// diem tb
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 70 && y < y_hdsd - 5)
		{
			refresh_content();
			SINH_VIEN(First_sv);
			diemtb = true;
			opt[3]=false;
			return;
		}
		x1 += 80;
		// diem tk
		if (x > x1 && y > y_hdsd - 40 && x < x1 + 70 && y < y_hdsd - 5)
		{
			refresh_content();
			click_diem_tk = true;
			SINH_VIEN(First_sv);
			opt[3] = false;
			return;
		}
		if (dsltc.sl_ltc > 0)
		{
			Change_LTC type = VIEW;
			string temp, temp1, temp2, temp3;

			graphics_look_for(x, y); // tim kiem
			if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
			{ // Button tim` kie^m'
				isclicked_ltc = true;
				NienKhoa = NhapNienKhoa;
				HocKy = NhapHocKy;
				Nhom = NhapNhom;
				MaMH = NhapMaMH;
				count = 0;
				cur_page = 1;

				in_dsltc(dsltc, 1, tree, type);
				for (int i = 0; i < dsltc.sl_ltc; i++)
				{
					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);
					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
						count++;
				}
			}

			if (NienKhoa.length() == 0 && HocKy.length() == 0 && Nhom.length() == 0 && MaMH.length() == 0)
			{
				count = dsltc.sl_ltc;
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

				int i = dsltc.sl_ltc - 1;
				for (; pos < first_pos - 1; i--)
				{ //

					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
						pos++;
				}

				// XEM Diem Lop TC
				int y1 = y_hdsd + 30;
				for (; first_pos < last_pos; i--)
				{
					temp1 = int_to_string(dsltc.ds_loptc[i]->nienkhoa);
					temp2 = int_to_string(dsltc.ds_loptc[i]->hocky);
					temp3 = int_to_string(dsltc.ds_loptc[i]->nhom);

					if (tim_kiem_ltc(temp1, NienKhoa, temp2, HocKy, temp3, Nhom, dsltc.ds_loptc[i]->MAMH, MaMH))
					{

						if (x > frame_left + 40 + 840 && y > y1 + 3 && x < frame_left + 40 + 835 + 95 && y < y1 + 27)
						{
							if(dsltc.ds_loptc[i]->dssvdk.sl_svdk == 0)	
							MessageBox(NULL, "Lop Khong Co Sinh Vien Dang Ky!!!", "Thong bao", MB_OK | MB_ICONWARNING);
							else{
								pos_ltc = i;
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
								type = VIEW;
								string tenmon = TimKiemTenMonHoc(tree, dsltc.ds_loptc[i]->MAMH);
								DSDIEM_LTC(First_sv, dsltc.ds_loptc[i]->dssvdk, dsltc.ds_loptc[i]->MALOPTC, tenmon, dsltc.ds_loptc[i]->dssvdk.sl_svdk, molop, dsltc.ds_loptc[i]->nienkhoa, dsltc.ds_loptc[i]->hocky, dsltc.ds_loptc[i]->nhom, type);
								view_dsdiem = true;
								opt[3] = false;
								NhapMSSV = "";
								return;
							}
						}
						y1 += 30;
						first_pos++;
					}
				}
				// close XEM DSSV
			}

			// page
			if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
			{ // back
				cur_page--;
				in_dsltc(dsltc, cur_page, tree, type);
			}
			if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
			{ // next trang
				cur_page++;
				if (cur_page == page)
					draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1+30, 685 + 1, cllightwhite);
				in_dsltc(dsltc, cur_page, tree, type);
			}
			// close page
		}
	}

	if (view_dsdiem)
	{
		int count(0);
		int first_pos_sv, last_pos_sv;
		LIST_DSSVDK dssvdkFilter;
		dssvdkFilter.list_svdk = new DANGKY[dsltc.ds_loptc[pos_ltc]->svmax];
		dssvdkFilter.sl_svdk = 0;
		
		if (NhapMSSV != "")
		{
			if ((x > frame_right - 80 && y > y_hdsd - 40 && x < frame_right - 40 && y < y_hdsd - 10))
			{ // Button tim` kie^m'
				isclicked_sv = true;
				cur_page = 1;
				locDS_DK(dsltc.ds_loptc[pos_ltc]->dssvdk, NhapMSSV, dssvdkFilter);
				if (dssvdkFilter.sl_svdk == 0)
				{
					MessageBox(NULL, "Ma Sinh Vien Khong Ton Tai!!!", "Thong bao", MB_OK | MB_ICONWARNING);
					isclicked_sv = false;
					in_dsdiemltc(dsltc.ds_loptc[pos_ltc]->dssvdk, First_sv, cur_page);
					return;
				}
				else
				{
					in_dsdiemltc(dssvdkFilter, First_sv, cur_page);
					return;
				}
			}	
			else
			{
				if (isclicked_sv == true)
				{
					locDS_DK(dsltc.ds_loptc[pos_ltc]->dssvdk, NhapMSSV, dssvdkFilter);
				}
				else
				{
					for (int i = 0; i < dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk; i++)
					{
						dssvdkFilter.list_svdk[dssvdkFilter.sl_svdk++] = dsltc.ds_loptc[pos_ltc]->dssvdk.list_svdk[i];
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk; i++)
			{
				dssvdkFilter.list_svdk[dssvdkFilter.sl_svdk++] = dsltc.ds_loptc[pos_ltc]->dssvdk.list_svdk[i];
			}
		}
		count = dssvdkFilter.sl_svdk;
		int page = count / 15;
		int so_du = count % 15;

		if (so_du != 0)	page++; 

		// Button Sua Diem
		if (x > frame_left + 40 && y > y_hdsd - 40 && x < frame_left + 140 && y < y_hdsd - 5)
		{
			if(!dsltc.ds_loptc[pos_ltc]->huylop) {
				clearmouseclick(WM_LBUTTONDOWN); // xoa vi tri chuot trong bo nho
				string tenmon = TimKiemTenMonHoc(tree, dsltc.ds_loptc[pos_ltc]->MAMH);
				SUA_DIEM(First_sv, dsltc.ds_loptc[pos_ltc]->dssvdk, dsltc.ds_loptc[pos_ltc]->MALOPTC, tenmon, dsltc.ds_loptc[pos_ltc]->dssvdk.sl_svdk, dsltc.ds_loptc[pos_ltc]->nienkhoa, dsltc.ds_loptc[pos_ltc]->hocky, dsltc.ds_loptc[pos_ltc]->nhom);
				writeFile_DSDK(dsltc);
			}else {
				MessageBox(NULL, "Lop Tin Chi Bi Huy Khong The Nhap Diem!!!", "Thong bao", MB_OK | MB_ICONWARNING);
			}
		}
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_dsdiemltc(dssvdkFilter, First_sv, cur_page);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 975 + 1+ 30 , 685 + 1, cllightwhite);
			in_dsdiemltc(dssvdkFilter, First_sv, cur_page);
		}
		// button close
		if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
		{
			refresh_content();
			background_option(3, First_sv, tree, dsltc);
			opt[3] = true;
			view_dsdiem = false;
			NhapMSSV = "";
			cur_page = 1;
			freeDS_DK(dssvdkFilter);
			return;
		}
		freeDS_DK(dssvdkFilter);
	}
	
	// xem diem trung binh
	if(view_diemtb) {
		int count_sv = 0;
		PTR_SV p = First_sv;
		for (; p != NULL && p->data.MALOP < dsl[pos_lsv - 1]; p = p->pnext);
		for(; p != NULL && p->data.MALOP == dsl[pos_lsv - 1]; p = p->pnext) {
			count_sv++;
		}
		
		int page = count_sv / 15;
		int so_du = count_sv % 15;
		if (so_du != 0) page++; 
		
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_dsDiemTB(dsltc, tree, First_sv, cur_page, pos_lsv - 1, count_sv);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 985+30, 685 + 1, cllightwhite);
			in_dsDiemTB(dsltc, tree, First_sv, cur_page, pos_lsv - 1, count_sv);
		}
		
		if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
		{
			view_diemtb = false;
			refresh_content();
			cur_page = 1;
			SINH_VIEN(First_sv);
			return;
		}
	}

	// xem diem tong ket
	if(view_diemtk) {
		int count_sv = 0;
		PTR_SV p = First_sv;
		for (; p != NULL && p->data.MALOP < dsl[pos_lsv - 1]; p = p->pnext);
		PTR_SV First = p;
		for(; p != NULL && p->data.MALOP == dsl[pos_lsv - 1]; p = p->pnext) {
			count_sv++;
		}
		
		int page = count_sv / 15;
		int so_du = count_sv % 15;
		if (so_du != 0) page++; 
		
		int soluongmon = somon;
		int page_mh = soluongmon / 6;
		int so_du_mh = soluongmon % 6;	    
	    if(so_du_mh != 0)	page_mh++;
		// chuyen trang Ma Mon Hoc
		if(x > frame_left + 565 && y > y_hdsd - 40 && x < frame_left + 665 &&  y < y_hdsd - 15 && cur_page_mamon > 1){
			in_DSMonHocTK(dsltc, tree, First, cur_page, --cur_page_mamon, pos_lsv - 1, count_sv);
		}
		if(x > frame_left + 865 && y > y_hdsd - 40 && x < frame_left + 965 &&  y < y_hdsd - 15 && cur_page_mamon < page_mh ){
			cur_page_mamon++;
			if (cur_page_mamon == page_mh)
				draw_rectangle(755, y_hdsd, frame_left + 985+30, 685 + 1, cllightwhite);		
			in_DSMonHocTK(dsltc, tree, First, cur_page, cur_page_mamon, pos_lsv - 1, count_sv);
		}
		// chuyen trang
		if (x > frame_left + 307 && y > 690 && x < frame_left + 407 && y < 715 && cur_page > 1)
		{ // back
			cur_page--;
			in_DSMonHocTK(dsltc, tree, First, cur_page, cur_page_mamon, pos_lsv - 1, count_sv);
		}
		if (x > frame_left + 607 && y > 690 && x < frame_left + 707 && y < 715 && cur_page < page)
		{ // next trang
			cur_page++;
			if (cur_page == page)
				draw_rectangle(frame_left + 40, y_hdsd, frame_left + 985+30, 685 + 1, cllightwhite);
			in_DSMonHocTK(dsltc, tree, First, cur_page, cur_page_mamon, pos_lsv - 1, count_sv);
		}
		
		// Button Xoa
		if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
		{
			view_diemtk = false;
			refresh_content();
			cur_page = 1;
			SINH_VIEN(First_sv);
			return;
		}
	}
	
	// hdsd
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (5) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 6 && y < frame_top + dis_frame_main * 4 && !view_dssv && !view_dsdiem && !diemtb && !click_diem_tk)
	{ // view_dssv == false = > opt[0] == true || opt[1]==true || opt[2]==true || opt[3]==true && tat ca = false
		hdsd = true;
		background_option(4, First_sv, tree, dsltc);
		table_hdsd();
	}
	// 	thoat
	if (x > frame_left + dis_frame_main + w_subframe + w_option * (6) && y > frame_top + dis_frame_main + w_subframe && x < frame_left + dis_frame_main + w_option * 7 && y < frame_top + dis_frame_main * 4)
	{
		int x = MessageBox(NULL, "Ban co muon thoat khong", "Thong bao", MB_OKCANCEL | MB_ICONWARNING);
		if (x == 1)
			thoat = true;
	}
	// remove table hdsd
	if (x > x_btn_x_table && y > y_btn_x_table + w_subframe && x < x_btn_x_table + w_btn_x && y < y_btn_x_table + w_btn_x + w_subframe && hdsd == true)
	{
		create_frame();
		hdsd = false;
		draw_rectangle(x_hdsd, y_hdsd, x_hdsd + w_table + w_subframe, y_hdsd + h_hdsd + w_subframe, cllightwhite);
		background_option(previous_page_index, First_sv, tree, dsltc);
		if (previous_page_index == -1)
			screen_logo();
	}
	// remove content -> screen_logo
	if (x > frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 && y > frame_top + dis_frame_main * 4 + w_subframe && x < frame_right - dis_frame_main - w_subframe * 2 - w_btn_x - 1 + w_btn_x && y < frame_top + dis_frame_main * 4 + w_subframe + w_btn_x + w_subframe)
	{
//		NhapNienKhoa = NienKhoa = NhapHocKy = HocKy = NhapNhom = Nhom = NhapMaMH = MaMH = NhapMaLop = MaLop = NhapMSSV = MSSV = "";
		if(diemtb==true || click_diem_tk == true){
			refresh_content();
			diemtb = opt[1] = click_diem_tk = false;
			opt[3]=true;
			DIEM(dsltc, tree);
		}
		else{
			opt[0] = opt[1] = opt[2] = opt[3] = false;
			lf_ltc[0] = lf_ltc[1] = lf_ltc[2] = lf_ltc[3] = false;
			create_frame();
			draw_rectangle(frame_left + dis_frame_main + w_subframe,
						   frame_top + dis_frame_main * 4 + w_subframe,
						   frame_right - dis_frame_main - w_subframe,
						   frame_bottom - w_frame_main, cllightwhite);
			// khong dung refresh_content() boi vi ham do co dau X
			screen_logo();
			previous_page_index = -1;
			background_option(-1, First_sv, tree, dsltc);
		}
	}
}
void click_main(PTR_SV &First_sv, TREE &tree, DS_LTC &dsltc)
{
	if (ismouseclick(WM_LBUTTONDOWN))
	{
		int x = mousex();
		int y = mousey();
		animations(x, y, First_sv, tree, dsltc);
		clearmouseclick(WM_LBUTTONDOWN);
	}

	if (opt[0])
	{
		Input type;
		if (lf_ltc[0])
		{
			type = NON_SPACE;
			input(NhapMaMH, frame_right - 190 + 10, y_hdsd - 34, type, 10);
		}
		if (lf_ltc[1])
		{
			type = NUMBER;
			input(NhapNhom, 1010 - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (lf_ltc[2])
		{
			type = NUMBER;
			input(NhapHocKy, 902 - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (lf_ltc[3])
		{
			type = NUMBER;
			input(NhapNienKhoa, 780 - 70 + 10, y_hdsd - 34, type, 4);
		}
		if (NhapMaMH.length() == 0 && NhapNhom.length() == 0 && NhapHocKy.length() == 0 && NhapNienKhoa.length() == 0 && isclicked_ltc)
		{
			isclicked_ltc = false;
			MaMH = Nhom = HocKy = NienKhoa = "";
			cur_page = 1;
			Change_LTC type1 = REPAIR_LTC;
			in_dsltc(dsltc, 1, tree, type1);
		}
	}
	if (view_dsdk)
	{
		Input type = NON_SPACE;
		input(NhapMSSV, frame_right - 290, y_hdsd - 34, type, 15);
		if (NhapMSSV == "" && isclicked_sv)
		{
			isclicked_sv = false;
			cur_page = 1;
			in_dssvdk(dsltc.ds_loptc[pos_ltc]->dssvdk, First_sv, cur_page);
		}
	}
	// ----- SINH VIEN -----//
	if (opt[1])
	{
		Input type = CLASS;
		input(NhapMaLop, frame_right - 290, y_hdsd - 34, type, 15);
		if (NhapMaLop.length() == 0 && isclicked_lsv)
		{
			isclicked_lsv = false;
			MaLop = "";
			cur_page = 1;
			in_dsl(First_sv, 1);
		}
	}
	if (view_dssv)
	{
		Input type = NON_SPACE;
		input(NhapMSSV, frame_right - 290, y_hdsd - 34, type, 15);
		if (NhapMSSV.length() == 0 && isclicked_sv)
		{
			isclicked_sv = false;
			MSSV = "";
			cur_page = 1;
			in_dssv(First_sv, pos_lsv, 1);
		}
	}
	// ----- close SINH VIEN -----//
	if (opt[2])
	{
		Input type = TEXT;
		Change_MH type1 = REPAIR_MH;
		setbkcolor(cllightwhite);
		outtextxy(frame_right - 330 + textwidth(NhapTenMon.c_str()), y_hdsd - 34, "  ");
		input(NhapTenMon, frame_right - 330, y_hdsd - 34, type, 50);
		if (NhapTenMon == "" && isclicked_mh)
		{
			int soluongmon = CountNodeInTree(tree.root);
			MONHOC *monhoc = new MONHOC[soluongmon];
			int n = 0;
			transferTreeToArr(tree.root, monhoc, n);
			Sort_Name(monhoc, soluongmon);
//			NhapMSSV = "";
			cur_page = 1;
			in_dsmon(tree, cur_page, monhoc, soluongmon, type1);
			isclicked_mh = false;
			delete[] monhoc;
		}
	}
	if (opt[3])
	{
		Input type;
		if (lf_ltc[0])
		{
			type = NON_SPACE;
			input(NhapMaMH, frame_right - 190 + 10, y_hdsd - 34, type, 10);
		}
		if (lf_ltc[1])
		{
			type = NUMBER;
			input(NhapNhom, 1010 - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (lf_ltc[2])
		{
			type = NUMBER;
			input(NhapHocKy, 902 - 70 + 10, y_hdsd - 34, type, 1);
		}
		if (lf_ltc[3])
		{
			type = NUMBER;
			input(NhapNienKhoa, 780 - 70 + 10, y_hdsd - 34, type, 4);
		}
		if (NhapMaMH.length() == 0 && NhapNhom.length() == 0 && NhapHocKy.length() == 0 && NhapNienKhoa.length() == 0 && isclicked_ltc)
		{
			isclicked_ltc = false;
			MaMH = Nhom = HocKy = NienKhoa = "";
			cur_page = 1;
			Change_LTC type1 = VIEW;
			in_dsltc(dsltc, 1, tree, type1);
		}
	}
	if (view_dsdiem)
	{
		Input type = NON_SPACE;
		input(NhapMSSV, frame_right - 290, y_hdsd - 34, type, 15);
		if (NhapMSSV.length() == 0 && isclicked_sv)
		{
			isclicked_sv = false;
			cur_page = 1;
			in_dsdiemltc(dsltc.ds_loptc[pos_ltc]->dssvdk, First_sv, cur_page);
		}
	}
}
