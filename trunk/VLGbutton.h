
class VLGbutton : public VLGbase {
public:
	VLGbutton(const char* n);
	void onDestroyed();
	void onClicked();
	void moveTo(int x,int y);
	void setText(char *t);
	char* getText();
};
