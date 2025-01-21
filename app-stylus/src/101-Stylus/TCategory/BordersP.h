#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

class BordersP : public BasePanel
{
public:
	BordersP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

	Wt::WCheckBox *m_main_toggler_;

	void setCustomTestValues();

private:
};