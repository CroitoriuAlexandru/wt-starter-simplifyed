#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "101-Stylus/XMLBrain.h"
#include "003-TreePreview/PTree.h"

class LeftPanel : public BaseDialogPanel
{
public:
    LeftPanel(Stylus *stylus_brain);

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);

private:
    XMLBrain *xml_brain_;
};