
#ifndef VGUI_IMAGEPANEL_H
#define VGUI_IMAGEPANEL_H

#include<VGUI.h>
#include<VGUI_Panel.h>

namespace vgui
{

class Image;

class VGUIAPI ImagePanel : public Panel
{
public:
	ImagePanel(Image* image);
public:
	virtual void setImage(Image* image);
protected:
	virtual void paintBackground();
protected:
	Image* _image;
};

}

#endif