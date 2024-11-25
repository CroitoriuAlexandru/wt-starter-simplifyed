#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

class SvgP : public BasePanel
{
public:
    SvgP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

    Wt::WCheckBox *m_main_toggler_;

    void setCustomTestValues();

private:
};