#pragma once
#include <Wt/WContainerWidget.h>

#include "101-Stylus/XMLBrain.h"

#include "003-Preview/TreeNode.h"
#include "003-Preview/ElemNode.h"

class Preview : public Wt::WContainerWidget
{
public:
    Preview(std::shared_ptr<Stylus> stylus);
    TreeNode *tree_node_;
    ElemNode *elem_node_;
    Wt::WContainerWidget *tree_wrapper_;
    Wt::WContainerWidget *elem_wrapper_;

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain);

private:
    std::shared_ptr<Stylus> stylus_;
    std::shared_ptr<XMLBrain> xml_brain_;
    void setTree(std::shared_ptr<XMLBrain> xml_brain);
    void setElem(std::shared_ptr<XMLBrain> xml_brain);
};