#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/Stylus.h"

LeftPanel::LeftPanel(std::shared_ptr<Stylus> stylus)
    : BaseDialogPanel(stylus)
{
    addStyleClass("w-[380px] relative");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);
    auto content_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contents()->addStyleClass("!bg-gray-800");

    // stylus->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
    //                                 { setXmlBrain(xml_brain); });
}

void LeftPanel::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    contents()->clear();
    if (xml_brain)
    {
        contents()->addWidget(std::make_unique<PTree>(xml_brain, xml_brain->message_node_));
    }
}
