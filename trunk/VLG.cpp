#include "VLG.h"
#include <string.h>
using namespace std;

int wcount=0; // window count
list<VLGbase*> widgets;

lua_State *LuaState;
int setText(lua_State *L);
int setInitText(lua_State *L);
int getText(lua_State *L);
int editMode(lua_State *L);
int isEditing(lua_State *L);


// well it works for now!
gboolean onDestroyedDispatcher(GtkWidget *g, gpointer data) { ((VLGbase*)data)->onDestroyed(); }
gboolean onClickedDispatcher(GtkWidget *g, gpointer data) { ((VLGbase*)data)->onClicked(); }

bool initVLG( int argc, char *argv[] ) {
	gtk_init (&argc, &argv);

	if (argc==1) {
		printf("Please specify a script\n");
		return -1;
	}

	LuaState = lua_open();
    luaL_openlibs (LuaState);

    lua_register(LuaState, "setText", setText);
    lua_register(LuaState, "setInitText", setInitText);
    lua_register(LuaState, "getText", getText);
    lua_register(LuaState, "isEditing", isEditing);
    lua_register(LuaState, "editMode", editMode);


	int e=luaL_dofile(LuaState, argv[1]);
    if (e==1) { 
		report_errors(LuaState,e);
		return -1;
	}

	return 0;
}

void startVLG() {

	for (list<VLGbase*>::iterator it = widgets.begin(); it != widgets.end(); it++) {
		VLGbase *w=(*it);
		w->setText(w->initialtext);
	}

	gtk_main ();	
}

void report_errors(lua_State *L, int status) {
    if ( status!=0 ) {
        printf("-- %s \n",lua_tostring(L, -1));
        lua_pop(L, 1); // remove error message
    }
}

int setText(lua_State *L) {

  	int args = lua_gettop(L);
	if (args!=2) printf("ERROR!! setText takes TWO parameters\n");

	char name[256];
	char value[256];

	sprintf(&name[0],"%s",lua_tostring(L,1));
	sprintf(&value[0],"%s",lua_tostring(L,2));
	lua_pop(L, 2);
	VLGbase *w=findWidget(name);
	if (w) { 
		w->setText(value);
	}

	return 0; // number of return values
}

int setInitText(lua_State *L) {

  	int args = lua_gettop(L);
	if (args!=2) printf("ERROR!! setInitText takes TWO parameters\n");

	char name[256];
	char value[256];

	sprintf(&name[0],"%s",lua_tostring(L,1));
	sprintf(&value[0],"%s",lua_tostring(L,2));
	lua_pop(L, 2);
	VLGbase *w=findWidget(name);
	if (w) { 
		w->setInitText(value);
	}

	return 0; // number of return values
}

static char getValue[256];

int getText(lua_State *L) {

  	int args = lua_gettop(L);
	if (args!=1) printf("ERROR!! getText takes ONE parameter\n");

	char name[256];
	sprintf(&name[0],"%s",lua_tostring(L,1));

	VLGbase *w=findWidget(name);
	if (w) { 
		sprintf(&getValue[0],"%s",w->getText());
	}
	lua_pop(L, 1);
	lua_pushstring(L, &getValue[0]); // return value
	return 1; // number of return values
}

int editMode(lua_State *L) {
  	int args = lua_gettop(L);
	if (args!=2) printf("ERROR!! editMode takes TWO parameters\n");

	char name[256];
	int v;
	sprintf(&name[0],"%s",lua_tostring(L,1));
	v=(int)lua_tonumber(L,2);

	VLGform *w=(VLGform*)findWidget(name);
	if (w) {
		w->editMode(v);
	} else {
		printf("editMode couldn't find form %s\n",name);
	}
	lua_pop(L, 2);
	return 0; // number of return values

}

int isEditing(lua_State *L) {
  	int args = lua_gettop(L);
	if (args!=1) printf("ERROR!! isEditing takes ONE parameter\n");
	char name[256];
	int v;
	sprintf(&name[0],"%s",lua_tostring(L,1));
	VLGform *w=(VLGform*)findWidget(name);
	if (w) {
		v=w->editing;
	}
	lua_pop(L, 1);
	lua_pushnumber(L, v); // return value
	return 1;
}	

VLGbase* findWidget(char *findName) {

	for (list<VLGbase*>::iterator it = widgets.begin(); it != widgets.end(); it++) {
		VLGbase *w=(*it);
		if (strcmp(findName,&w->name[0])==0) return w;
	}
	return NULL;
}



VLGbase* findWidget(GtkWidget *widget) {
	for (list<VLGbase*>::iterator it = widgets.begin(); it != widgets.end(); it++) {
		VLGbase *w=(*it);

		if (dynamic_cast<VLGlabel*>(w)) {
			if ( ((VLGlabel*)w)->eventBox == widget) return w;
		}else{
			if ( w->widget == widget) return w;
		}

	}
	return NULL;
}


int editDownX,editDownY;
guint32 editDownTime;
bool editResize;

gboolean button_press_edit_event( GtkWidget *widget, GdkEventButton *event ) {

	if (event->button == 1 ) { 

		editDownX=(int)event->x;
		editDownY=(int)event->y;

		if (event->time-editDownTime<500) pEdit(findWidget(widget));

		editDownTime=event->time;
		editResize=false;
		VLGbase *w=findWidget(widget);
		if (editDownX>(w->getWidth()/2) && editDownY>(w->getHeight()/2)) {
			editResize=true;
		}
	}

	return TRUE;
}

gboolean motion_notify_edit_event( GtkWidget *widget, GdkEventMotion *event , gpointer* parent) {

	int nx, ny;
	GdkModifierType state;
	// the parent widget (a form) is made from a gtkWidget pass that *GDK* window to get the pointer
	gdk_window_get_pointer (((VLGform*)parent)->widget->window, &nx, &ny, &state);
	
	if (state & GDK_BUTTON1_MASK) {
		VLGbase *w=findWidget(widget);
		if (w) {
			if (editResize) {
				w->setSize(nx-w->x,ny-w->y);
			} else {
				w->moveTo(nx-editDownX,ny-editDownY);
			}
		} else {
			printf("gtk->VLG lookup failed\n");
		}
	}

	return TRUE;
}

