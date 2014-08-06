#ifndef __LISTITEMCELL_H__
#define __LISTITEMCELL_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;

class ListItemCell : public CCTableViewCell
{
public:
	ListItemCell(void);
	~ListItemCell(void);
	bool init(void);
	static ListItemCell *create(const string name, const string target, const int amount);
	void updateLabels(const string name, const string target, const int amount);
	
	void onSelected() {m_bg->setOpacity(200);}
	void onDeselected(){m_bg->setOpacity(0);}
	bool isSelected() {return m_bg->getOpacity() > 0 ? true : false;}
private:
	CCLabelTTF *m_pItemName;
	CCLabelTTF *m_pTarget;
	CCLabelTTF *m_pAmount;
	CCNodeRGBA *m_bg;
};
#endif