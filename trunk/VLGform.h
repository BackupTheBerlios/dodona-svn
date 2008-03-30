
class VLGform : public VLGbase {
	
public:
	GtkWidget *fixed;
	bool editing;	
	VLGform(const char* n);
	void onDestroyed();
	void onClicked();
	void add(VLGbase *w);
	void moveTo(int x,int y);
	void setText(char* t);
	char* getText();
	void editMode(bool e);
	void setSize(int nx,int ny);
};

