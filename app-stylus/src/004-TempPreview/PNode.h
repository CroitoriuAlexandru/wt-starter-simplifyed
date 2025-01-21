#pragma once
#include <Wt/WContainerWidget.h>
#include "100-Utils/tinyxml2/tinyxml2.h"

class Stylus;
class XMLBrain;

class PNode : public Wt::WContainerWidget
{
public:
    PNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node, std::shared_ptr<XMLBrain> top_parent_xml_template);
    std::shared_ptr<XMLBrain> top_parent_xml_template_;
    std::shared_ptr<XMLBrain> xml_brain_;
    tinyxml2::XMLNode *node_;

private:
    void createChildren();
};