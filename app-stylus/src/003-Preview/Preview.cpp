#include "003-Preview/Preview.h"
#include "101-Stylus/Stylus.h"

Preview::Preview(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    tree_wrapper_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    elem_wrapper_ = addWidget(std::make_unique<Wt::WContainerWidget>());

    setStyleClass("min-h-screen h-screen max-h-screen relative w-[calc(100vw-450px)] flex");
    tree_wrapper_->setStyleClass("w-[380px] min-h-screen h-screen max-h-screen overflow-auto! bg-gradient-dark");
    elem_wrapper_->setStyleClass("w-full min-h-screen h-screen max-h-screen overflow-y-auto overflow-x-hidden");

    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setElem(xml_brain_);
                                        setTree(xml_brain); });
}

void Preview::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    if (!xml_brain)
        return;
    xml_brain_ = xml_brain;
    setElem(xml_brain);
    setTree(xml_brain);
}

void Preview::setTree(std::shared_ptr<XMLBrain> xml_brain)
{
    tree_wrapper_->clear();
    tree_node_ = tree_wrapper_->addWidget(std::make_unique<TreeNode>(xml_brain, xml_brain->xml_doc_->FirstChild()));
}

void Preview::setElem(std::shared_ptr<XMLBrain> xml_brain)
{
    elem_wrapper_->clear();
    elem_node_ = elem_wrapper_->addWidget(std::make_unique<ElemNode>(xml_brain, xml_brain->xml_doc_->FirstChild(), xml_brain));
}