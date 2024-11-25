#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include <Wt/WLineEdit.h>

class QuickCommandsPanel : public BaseDialogPanel
{
public:
    QuickCommandsPanel(std::shared_ptr<Stylus> stylus);
    Wt::WLineEdit *line_eddit_;

private:
};