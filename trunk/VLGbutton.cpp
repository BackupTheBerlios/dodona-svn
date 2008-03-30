#include "VLG.h"

VLGbutton::VLGbutton(const char* n) {
	widget = gtk_button_new ();
	sprintf(&name[0],"%s",n);
	g_signal_connect (G_OBJECT(widget), "clicked", G_CALLBACK (onClickedDispatcher), this);
	gtk_widget_set_events(GTK_WIDGET(widget), GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	gtk_widget_show (widget);
	setMinSize(80,28);
	widgets.push_back(this);
}

void VLGbutton::onDestroyed() { }

void VLGbutton::onClicked() { 
	int e=luaL_dostring(LuaState, clickedScript);
    if (e==1) report_errors(LuaState,e);
}

void VLGbutton::moveTo(int nx,int ny) {
	if (parent)	{
		gtk_fixed_move (GTK_FIXED (((VLGform*)parent)->fixed), widget, nx, ny);
		x=nx;
		y=ny; 
	}
}

void VLGbutton::setText(char *t) { 
	sprintf(&text[0],"%s",t); 
	gtk_button_set_label((GtkButton*)widget,(gchar*)text);	
}

char* VLGbutton::getText() { }
