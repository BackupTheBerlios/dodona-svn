
class VLGedit : public VLGbase {
public:
	VLGedit(const char* n);
	void onDestroyed();
	void onClicked();
	void moveTo(int x,int y);
	void setText(const char *t);
	const char* getText();
};
