#include "003-TreePreview/PTree.h"
#include "101-Stylus/Stylus.h"

#include <Wt/WText.h>

PTree::PTree(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
    : xml_brain_(xml_brain),
      node_(node)
{
    clicked().preventPropagation();
    doubleClicked().preventPropagation();

    clicked().connect([=]
                      {
                        // if(xml_brain_->stylus_->xml_brain_){
                        //     xml_brain_->stylus_->xml_brain_->selected_node_->node_selected().emit(false);
                        // }
                        xml_brain_->selected_node_ = node;
                        xml_brain_->stylus_->setXmlBrain(xml_brain_); });

    titleBar_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    content_ = addWidget(std::make_unique<Wt::WContainerWidget>());

    std::string title_before_styles = "before:content-[''] before:absolute before:-left-2.5 before:top-1/2 before:-translate-y-1/2 before:w-3 before:border-b before:border-solid before:border-gray-400 ";
    std::string content_before_styles = "after:content-[''] after:absolute after:left-0 after:-top-2.5 after:bottom-2.5 after:border after:border-solid after:border-gray-400 ";

    titleBar_->setStyleClass("flex relative hover:bg-white/20 rounded-md text-nowrap space-x-2 cursor-pointer");
    content_->setStyleClass("flex relative flex-col pl-3");
    if (xml_brain_->selected_node_ == node)
    {
        titleBar_->addStyleClass("?");
    }
    mouseWentOver().preventPropagation();
    mouseWentOver().connect([=]
                            { titleBar_->toggleStyleClass("??", true); });
    mouseWentOut().preventPropagation();
    mouseWentOut().connect([=]
                           { titleBar_->toggleStyleClass("??", false); });

    // clicked().connect([=]
    //                   {
    //       xml_brain_->selected_node_ = node;
    //       xml_brain_->stylus_->setXmlBrain(xml_brain_); });

    auto title = titleBar_->addWidget(std::make_unique<Wt::WText>(""));
    title->setStyleClass("pl-1 font-bold");
    if (!node_)
    {
        title->setText("Node is null");
        title->addStyleClass("text-red-400");
        return;
    }
    else if (node_->ToElement())
    {
        if (node_->FirstChild() && node_->FirstChild()->ToElement())
        {
            content_->addStyleClass(content_before_styles);
        }
        if (node_ == xml_brain_->message_node_)
        {
            title->addStyleClass("text-purple-400");
            // title->setText(node_->ToElement()->Attribute("id"));
            // title->setText(node_->ToElement()->Name());
            title->setText(node_->ToElement()->Attribute("id"));
            addStyleClass("-ml-1");
        }
        else
        {
            title->addStyleClass("text-green-600 " + title_before_styles);
            title->setText(node_->ToElement()->Name());
        }
    }
    else if (node_->ToText())
    {
        auto temp_var_data = tempText(node_);
        if (temp_var_data.name_ != "")
        {
            title->setText("${" + temp_var_data.name_ + "}");
            title->addStyleClass("text-yellow-600");
            // titleBar_->doubleClicked().connect(this, [=]()
            //    {
            //    std::string temp_id = temp_var_data.implementation_;
            //    auto collon_pos = temp_id.find(":");
            //    if (collon_pos != std::string::npos)
            //    {
            //    temp_id = temp_id.substr(collon_pos + 1, temp_id.size());
            //    }
            //    std::cout << "\n\n double clicked " << temp_id << " \n\n";
            //    auto new_selected_xml_brain = xml_brain_->stylus_brain_->getXMLBrain(temp_id);
            //    new_selected_xml_brain->selected_node_ = new_selected_xml_brain->message_node_;
            // if(new_selected_xml_brain){
            //     xml_brain_->stylus_brain_->setSelectedNode(new_selected_xml_brain, new_selected_xml_brain->message_node_);
            // }else {
            //     std::cout << "\n\n xml brain not found \n\n";
            // }
            //    });
        }
        else
        {
            title->setText(node_->ToText()->Value());
            title->addStyleClass("text-blue-400");
        }
    }

    if (node->FirstChild())
    {
        for (auto child = node->FirstChild(); child; child = child->NextSibling())
        {
            if (child->ToElement())
            {
                content_->addWidget(std::make_unique<PTree>(xml_brain_, child));
            }
            else if (child->ToText())
            {
                titleBar_->addWidget(std::make_unique<PTree>(xml_brain_, child));
            }
        }
    }
}