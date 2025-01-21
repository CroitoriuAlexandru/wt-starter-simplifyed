#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

class SpacingP : public BasePanel
{
public:
	SpacingP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

	Wt::WCheckBox *m_show_main_directions_toggler_;
	Wt::WCheckBox *m_show_sides_toggler_;
	Wt::WCheckBox *m_show_spacing_toggler_;

	void setCustomTestValues();

private:
};