#pragma once
#include "101-Stylus/TCategory/BasePanel.h"

struct AccesibilityData
{
    std::string screen_readers = "none";
};

class AccesibilityP : public BasePanel
{
public:
    AccesibilityP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper);

    Wt::WCheckBox *m_main_toggler_;

    void setCustomTestValues();

private:
};