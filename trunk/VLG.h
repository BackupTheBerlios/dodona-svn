#include <gtk/gtk.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <list>
using namespace std;

extern int wcount; // window count app exits when == 0 !


extern lua_State *LuaState;


gboolean onDestroyedDispatcher(GtkWidget *g, gpointer data);
gboolean onClickedDispatcher(GtkWidget *g, gpointer data);

bool initVLG( int argc, char *argv[] );
void startVLG();
void report_errors(lua_State *L, int status);

gboolean button_press_edit_event( GtkWidget *widget, GdkEventButton *event );
gboolean motion_notify_edit_event( GtkWidget *widget, GdkEventMotion *event , gpointer* parent);


class VLGbase {
public:

	char text[1024];
	char initialtext[1024];
	char name[256];
	char clickedScript[256];  // should only call a function with main code in the script
	int x,y;
	int width,height;

	GtkWidget *widget; // main gtk widget of a Visual Lua Gui widget
	VLGbase *parent; // everything except a form must have a parent
	gulong editDownSignal;
	gulong editMotionSignal;
	virtual void setText(const char *t)=0;
	virtual void setInitText(const char *t) { sprintf(&initialtext[0],"%s",t); }
	virtual const char* getText()=0;
	void setClickedScript(const char *t) { sprintf(&clickedScript[0],"%s",t); }
	virtual void onDestroyed()=0;
	virtual void onClicked()=0;
	virtual void moveTo(int nx,int ny)=0;
	void show() { gtk_widget_show (widget); }
	void hide() { gtk_widget_hide (widget); }
	void setSize(int nx,int ny) { 
		gtk_widget_set_size_request(widget,(gint)nx,(gint)ny);
		width=nx;height=ny;
		}
	int getWidth() { return width; }
	int getHeight() { return height; }
};

extern list<VLGbase*> widgets;
VLGbase* findWidget(char *findName);
void pEdit(VLGbase* w);

#include "VLGform.h"
#include "VLGbutton.h"
#include "VLGlabel.h"
#include "VLGedit.h"
