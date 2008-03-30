#include "VLG.h"

int main( int argc, char *argv[] ) {
	
	if (initVLG(argc, argv)!=0) return -1;
	
	VLGform *f1;
	f1=new VLGform("form1");
	f1->setInitText("Form 1");
	f1->setSize(10,10);
	
	VLGbutton *b1;
	b1=new VLGbutton("button1");
	f1->add(b1);
	
	b1->setClickedScript("onButton1Click()");
	b1->setInitText("button 1");
	b1->moveTo(60,50);
	
	VLGlabel *l;
	l=new VLGlabel("label1");
	f1->add(l);
	l->setInitText("A label!");
	l->moveTo(200,40);
	
	VLGedit *e;
	e=new VLGedit("edit1");
	f1->add(e);
	e->moveTo(10,10);
	
	
	VLGform *VLG_form;
	VLG_form=new VLGform("VLG_form");
	VLG_form->setInitText("Visual Lua Gui Editor");
	VLG_form->moveTo(500,40);
	
	VLGbutton *VLG_b2;
	VLG_b2=new VLGbutton("button2");
	VLG_form->add(VLG_b2);
	
	VLG_b2->setInitText("button 2");
	VLG_b2->moveTo(10,10);
	VLG_b2->setClickedScript("onButton2Click()");
	
	VLGbutton *VLG_b3;
	VLG_b3=new VLGbutton("VLG_EditButton");
	VLG_form->add(VLG_b3);
	
	VLG_b3->moveTo(10,40);
	VLG_b3->setInitText("Edit Mode");
	VLG_b3->setClickedScript("VLG_EditButtonClick()");	
	
		
	f1->show(); // by default all other VLG widets are shown on
	VLG_form->show(); // creation except VLGforms 
	
	startVLG();
		
	return 0;
}
