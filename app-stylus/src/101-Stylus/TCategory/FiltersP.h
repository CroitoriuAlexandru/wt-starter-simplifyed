#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

class FiltersP : public BasePanel
{
public:
    FiltersP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

    void setCustomTestValues();

    Wt::WCheckBox *m_main_toggler_;

private:
};