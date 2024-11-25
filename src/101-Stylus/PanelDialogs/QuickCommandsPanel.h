#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include <Wt/WLineEdit.h>

class Stylus;

class QuickCommandsPanel : public BaseDialogPanel
{
public:
    QuickCommandsPanel(Stylus *stylus);
    Wt::WLineEdit *line_eddit_;

private:
};