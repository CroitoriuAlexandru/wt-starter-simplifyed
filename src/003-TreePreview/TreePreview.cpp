#include "003-TreePreview/TreePreview.h"
#include "003-TreePreview/PTree.h"
#include "101-Stylus/Stylus.h"

TreePreview::TreePreview(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    setStyleClass("bg-gray-800 !min-w-[380px] !max-w-[380px] h-screen relative");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);

    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setXmlBrain(xml_brain); });
}

void TreePreview::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    clear();
    if (xml_brain)
    {
        addWidget(std::make_unique<PTree>(xml_brain, xml_brain->message_node_));
    }
}
