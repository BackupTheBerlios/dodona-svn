#include "VLG.h"

VLGedit::VLGedit(const char* n) {
	widget = gtk_entry_new ();
	sprintf(&name[0],"%s",n);

// on action? return pressed? on ANY key press? TODO decide on which event to implement
//	g_signal_connect (G_OBJECT(widget), "clicked", G_CALLBACK (onClickedDispatcher), this);

	gtk_widget_set_events(GTK_WIDGET(widget), GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	gtk_widget_show (widget);
	widgets.push_back(this);
	setMinSize(80,20);

}

void VLGedit::onDestroyed() { }

void VLGedit::onClicked() { }

void VLGedit::moveTo(int nx,int ny) {
	if (parent)	{
		gtk_fixed_move (GTK_FIXED (((VLGform*)parent)->fixed), widget, nx, ny); 
		x=nx;y=ny;
	}
}

void VLGedit::setText(char *t) { 
	sprintf(&text[0],"%s",t); 
	gtk_entry_set_text((GtkEntry*)widget,(gchar*)text);	
}

char* VLGedit::getText() { 
	(char*)gtk_entry_get_text((GtkEntry*)widget);	
}
