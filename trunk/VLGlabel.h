
class VLGlabel : public VLGbase {
public:
	GtkWidget *eventBox;
	VLGlabel(const char* n);
	void onDestroyed();
	void onClicked();
	void moveTo(int x,int y);
	void setText(const char *t);
	const char* getText();
};
