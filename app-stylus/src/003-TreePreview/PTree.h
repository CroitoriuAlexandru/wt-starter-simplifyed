#pragma once
#include <Wt/WContainerWidget.h>

#include "101-Stylus/XMLBrain.h"

class PTree : public Wt::WContainerWidget
{
public:
    PTree(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);

    Wt::WContainerWidget *titleBar_;
    Wt::WContainerWidget *content_;

    std::shared_ptr<XMLBrain> xml_brain_;
    tinyxml2::XMLNode *node_;

private:
};