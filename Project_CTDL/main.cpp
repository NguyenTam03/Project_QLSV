#include"Menu.h"
int main(){
	initwindow(screen_width, screen_height);   
	setusercharsize(2,5,1,2);
	settextstyle(8,0,0);
	setbkcolor(cllightwhite);
	cleardevice();
	screen_logo();
	create_frame();
	PTR_SV First = NULL;
	TREE tree;
	DS_LTC dsltc; 
	readfile(First);
	readFile_DSMH(tree);
	ReadDataDS_LTC(dsltc);
	readDataDS_DK(dsltc);
	background_option(-1, First, tree, dsltc);
	while(1){
		click_main(First,tree,dsltc);
		if(thoat == true) break;
		delay(100);
	}	
	free_dssv(First);
	free_dsl();
	free_DSMH(tree.root);
	free_DSLTC(dsltc); 
	return 0;
}
