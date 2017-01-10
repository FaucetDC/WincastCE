
#ifndef VGUI_LINEBORDER_H
#define VGUI_LINEBORDER_H

#include<VGUI.h>
#include<VGUI_Border.h>
#include<VGUI_Color.h>

namespace vgui
{

class Panel;

class VGUIAPI LineBorder : public Border
{
private:
	Color _color;
public:
	LineBorder();
	LineBorder(int thickness);
	LineBorder(Color color);
	LineBorder(int thickness,Color color);
private:
	virtual void init(int thickness,Color color);
protected:
	virtual void paint(Panel* panel);
};

}

#endif