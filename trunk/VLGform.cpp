#include "VLG.h"

VLGform::VLGform(const char* n) {
	wcount++;
	widget=gtk_window_new (GTK_WINDOW_TOPLEVEL);
	sprintf(&name[0],"%s",n);

	g_signal_connect (G_OBJECT (widget), "destroy",G_CALLBACK(onDestroyedDispatcher), this);
// hmmm..... look into this later
//		g_signal_connect (G_OBJECT (widget), "destroy",G_CALLBACK(&VLGform::onDestroyed), this);
	fixed = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (widget), fixed);
	gtk_widget_set_events(GTK_WIDGET(widget), GDK_EXPOSURE_MASK
			| GDK_LEAVE_NOTIFY_MASK
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK
			| GDK_POINTER_MOTION_HINT_MASK); 
	gtk_widget_show (fixed);
	widgets.push_back(this);
	editing=false;
	setSize(256,256);

}


void VLGform::setSize(int nx,int ny) { 
	gtk_window_set_default_size (GTK_WINDOW(widget),(gint)nx,(gint)ny);
	width=nx;height=ny;
}

void VLGform::onDestroyed() {
	wcount--;
	if (wcount<1) gtk_main_quit();
}

void VLGform::onClicked() { } // unimplemented & dispatcher not connected

void VLGform::add(VLGbase *w) {
	w->parent=this;
	if (dynamic_cast<VLGlabel*>(w)) {
		gtk_fixed_put (GTK_FIXED (fixed), ((VLGlabel*)w)->eventBox, 0, 0);
	} else { 
		gtk_fixed_put (GTK_FIXED (fixed), w->widget, 0, 0);
	}
}

void VLGform::moveTo(int nx,int ny) {
	gtk_window_move((GtkWindow*)widget,(gint)nx,(gint)ny);
	x=nx;y=ny;
}

void VLGform::setText(const char* t) {
	sprintf(&text[0],"%s",t); 
	gtk_window_set_title((GtkWindow*)widget,(gchar*)t);
}

const char* VLGform::getText() { return "TODO implement VGLform::getText !!"; }

void VLGform::editMode(bool e) {
//	if (e==editing) return;
	editing=e;

/*
	if (editing) { 
		printf("%s editing mode ON\n",name);
	} else {
		printf("%s editing mode OFF\n",name);
	}
*/
	if (editing) {
		for (list<VLGbase*>::iterator it = widgets.begin(); it != widgets.end(); it++) {
			VLGbase *w=(*it);
			if (w->parent==this) {
				if (dynamic_cast<VLGlabel*>(w)) {
					w->editDownSignal=g_signal_connect (GTK_WIDGET(((VLGlabel*)w)->eventBox), "button_press_event",(GtkSignalFunc) button_press_edit_event, this);
					w->editMotionSignal=g_signal_connect (GTK_WIDGET(((VLGlabel*)w)->eventBox), "motion_notify_event",(GtkSignalFunc) motion_notify_edit_event, this);
				} else {
					w->editDownSignal=g_signal_connect (GTK_WIDGET(w->widget), "button_press_event",(GtkSignalFunc) button_press_edit_event, this);
					w->editMotionSignal=g_signal_connect (GTK_WIDGET(w->widget), "motion_notify_event",(GtkSignalFunc) motion_notify_edit_event, this);
				}
			}
		}
	} else {
		for (list<VLGbase*>::iterator it = widgets.begin(); it != widgets.end(); it++) {
			VLGbase *w=(*it);

			if (w->parent==this) {
				if (dynamic_cast<VLGlabel*>(w)) {
					g_signal_handler_disconnect(GTK_WIDGET(((VLGlabel*)w)->eventBox),w->editDownSignal);
					g_signal_handler_disconnect(GTK_WIDGET(((VLGlabel*)w)->eventBox),w->editMotionSignal);
				} else {
					g_signal_handler_disconnect(GTK_WIDGET (w->widget),w->editDownSignal);
					g_signal_handler_disconnect(GTK_WIDGET (w->widget),w->editMotionSignal);
				}
			}
		}
	}
}

