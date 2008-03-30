#include "VLG.h"

VLGlabel::VLGlabel(const char* n) {
	widget = gtk_label_new ("Label");
	sprintf(&name[0],"%s",n);
	eventBox = gtk_event_box_new ();
    gtk_container_add ((GtkContainer*)eventBox, widget);
	gtk_widget_set_events(GTK_WIDGET(eventBox), GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	gtk_widget_show (widget);
	gtk_widget_show (eventBox);
	widgets.push_back(this);
	setMinSize(80,20);
	
	gtk_misc_set_alignment(GTK_MISC (widget),0,1);
}

void VLGlabel::onDestroyed() { }

void VLGlabel::onClicked() { }

void VLGlabel::moveTo(int nx,int ny) {
//	if (parent)	gtk_fixed_move (GTK_FIXED (((VLGform*)parent)->fixed), widget, x, y); 
	if (parent)	{
		gtk_fixed_move (GTK_FIXED (((VLGform*)parent)->fixed), eventBox, nx, ny);
		x=nx;y=ny;
	} 
}

void VLGlabel::setText(char *t) { 
	sprintf(&text[0],"%s",t); 
	gtk_label_set_label((GtkLabel*)widget,(gchar*)text);	
}


char* VLGlabel::getText() { }
