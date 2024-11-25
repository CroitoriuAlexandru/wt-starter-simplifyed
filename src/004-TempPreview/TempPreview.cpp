#include "004-TempPreview/TempPreview.h"
#include "101-Stylus/Stylus.h"
#include "004-TempPreview/PNode.h"

TempPreview::TempPreview(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    setStyleClass("w-full h-screen relative");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);

    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setXmlBrain(xml_brain); });
}

void TempPreview::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    clear();
    if (xml_brain)
    {
        addWidget(std::make_unique<PNode>(xml_brain, xml_brain->message_node_));
    }
}
