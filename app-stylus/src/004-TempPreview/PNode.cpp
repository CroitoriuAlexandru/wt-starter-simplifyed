#include "004-TempPreview/PNode.h"
#include "101-Stylus/XMLBrain.h"
#include "101-Stylus/Stylus.h"

#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WRadioButton.h>
#include <Wt/WTemplate.h>

PNode::PNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node, std::shared_ptr<XMLBrain> top_parent_xml_template)
    : xml_brain_(xml_brain),
      top_parent_xml_template_(top_parent_xml_template),
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

    // setStyleClass("p-4 bg-red-200");
    if (xml_brain_->selected_node_ == node)
    {
        toggleStyleClass("?", true);
    }

    mouseWentOver().preventPropagation();
    mouseWentOver().connect([=]
                            { toggleStyleClass("??", true); });
    mouseWentOut().preventPropagation();
    mouseWentOut().connect([=]
                           { toggleStyleClass("??", false); });

    // node_->node_selected().connect([=](bool selected)
    //                                { toggleStyleClass("?", selected); });
    // node_->style_class_changed().connect([=](std::string style_class)
    //                                      { setStyleClass(style_class);
    //                                         toggleStyleClass("?", true); });
    createChildren();
}

void PNode::createChildren()
{

    if (node_->ToElement())
    {

        // setAttributeValue(attr->Name(), attr->Value());
        if (node_->ToElement()->Attribute("class"))
        {
            addStyleClass(node_->ToElement()->Attribute("class"));
        }
        if (std::strcmp(node_->ToElement()->Name(), "img") == 0)
        {
            setHtmlTagName("img");
            if (node_->ToElement()->Attribute("src"))
            {
                setAttributeValue("src", node_->ToElement()->Attribute("src"));
            }
        }
        else if (std::strcmp(node_->ToElement()->Name(), "svg") == 0)
        {
            Wt::WString value = "";
            tinyxml2::XMLPrinter printer;
            node_->ToElement()->Accept(&printer);
            value += printer.CStr();
            addWidget(std::make_unique<Wt::WTemplate>(value));
            return;
        }
    }
    else if (node_->ToText())
    {

        auto temp_var_data = tempText(node_);
        std::cout << "\n temp var data name: " << temp_var_data.name_ << "\n";

        if (temp_var_data.name_ != "")
        {
            if (temp_var_data.widget_type_ == TempVarWidgetType::TEMPLATE)
            {
                // addWidget(std::make_unique<Wt::WText>(temp_var_data.widget_));
                addStyleClass(temp_var_data.style_classes_);
                auto child_xml_brain = xml_brain_->stylus_->xml_brains_[temp_var_data.widget_text_];
                if (child_xml_brain != nullptr)
                {
                    addWidget(std::make_unique<PNode>(child_xml_brain, child_xml_brain->message_node_, top_parent_xml_template_));
                }
                // auto child_temp_xml_brain = xml_brain_->stylus_brain_->getXMLBrain(widget_text);
                // if(child_temp_xml_brain != nullptr)
                // {
                // auto child_temp = addWidget(std::make_unique<PNode>(child_temp_xml_brain, child_temp_xml_brain->message_node_));
                // }else addWidget(std::make_unique<Wt::WText>("Template not found"));
            }
            else if (temp_var_data.widget_type_ == TempVarWidgetType::TEXT)
            {
                addWidget(std::make_unique<Wt::WText>(temp_var_data.widget_text_));
            }
            else
                addWidget(std::make_unique<Wt::WText>("Widget type not found"));
        }
        else
        {

            auto text_value = node_->ToText()->Value();

            auto text_wid_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
            auto text = text_wid_wrapper->addWidget(std::make_unique<Wt::WText>(text_value));
            auto text_input = text_wid_wrapper->addWidget(std::make_unique<Wt::WTextArea>(text_value));

            text_input->hide();
            text->doubleClicked().connect([=]
                                          {
                                            text->hide();
                                            text_input->show(); 
                                            text_input->setFocus(); });

            text_input->enterPressed().connect([=]
                                               {
                                                text->setText(text_input->text());
                                                text_input->hide();
                                                text->show();
                                                node_->ToText()->SetValue(text_input->text().toUTF8().c_str());
                                                xml_brain_->saveXmlToDbo(); });

            text_input->setMinimumSize(Wt::WLength(300, Wt::LengthUnit::Pixel), Wt::WLength::Auto);
            text_input->escapePressed().connect([=]
                                                {
                                                text_input->hide();
                                                text->show(); });
        }
    }

    if (node_->FirstChild())
    {
        for (auto child = node_->FirstChild(); child; child = child->NextSibling())
        {
            auto child_PNode = addWidget(std::make_unique<PNode>(xml_brain_, child, top_parent_xml_template_));
        }
    }
}
