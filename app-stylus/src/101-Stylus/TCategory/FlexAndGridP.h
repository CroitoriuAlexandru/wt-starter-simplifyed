#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

class StyleEdditorWidget;

class FlexAndGridP : public BasePanel
{
public:
	FlexAndGridP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

	Wt::WCheckBox *m_flex_elem_toggler_;
	Wt::WCheckBox *m_flex_parent_toggler_;
	Wt::WCheckBox *m_grid_elem_toggler_;
	Wt::WCheckBox *m_grid_parent_toggler_;

	void setCustomTestValues();

private:
};