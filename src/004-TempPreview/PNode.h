#pragma once
#include <Wt/WContainerWidget.h>

#include "101-Stylus/XMLBrain.h"

class PNode : public Wt::WContainerWidget
{
public:
    PNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);
    std::shared_ptr<XMLBrain> xml_brain_;
    tinyxml2::XMLNode *node_;

private:
};