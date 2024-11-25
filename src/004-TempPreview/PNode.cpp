#include "004-TempPreview/PNode.h"
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WCheckBox.h>
#include <Wt/WRadioButton.h>

#include "101-Stylus/Stylus.h"

PNode::PNode(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
    : xml_brain_(xml_brain),
      node_(node)
{
    clicked().preventPropagation();
    doubleClicked().preventPropagation();

    clicked().connect([=]
                      {
                        if(xml_brain_->stylus_->xml_brain_){
                            xml_brain_->stylus_->xml_brain_->selected_node_->node_selected().emit(false);
                        }
                        xml_brain_->selected_node_ = node;
                        xml_brain_->stylus_->setXmlBrain(xml_brain_); });
    // setStyleClass("p-4 bg-red-200");
    if (xml_brain_->selected_node_ == node)
    {
        setStyleClass("?");
    }
    mouseWentOver().preventPropagation();
    mouseWentOver().connect([=]
                            { toggleStyleClass("??", true); });
    mouseWentOut().preventPropagation();
    mouseWentOut().connect([=]
                           { toggleStyleClass("??", false); });

    node_->node_selected().connect([=](bool selected)
                                   { toggleStyleClass("?", selected); });
    node_->style_class_changed().connect([=](std::string style_class)
                                         { setStyleClass(style_class);
                                            toggleStyleClass("?", true); });

    if (node->ToElement() == xml_brain_->message_node_)
    {
        // std::cout << "\n\n message node found with id " << xml_brain_->dbo_temp_data_.temp_id << "\n";
        // setStyleClass("p-4 bg-green-200");
    }
    else
    {
        if (node->ToElement())
        {
            if (node->ToElement()->Attribute("class"))
            {
                addStyleClass(node->ToElement()->Attribute("class"));
            }
        }
        else if (node->ToText())
        {

            auto temp_var_data = tempText(node_);
            if (temp_var_data.name_ != "")
            {
                if (temp_var_data.implementation_type_ == TempVarImplementationType::TEMPLATE)
                {
                    // auto child_temp_xml_brain = xml_brain_->stylus_brain_->getXMLBrain(widget_text);
                    // if(child_temp_xml_brain != nullptr)
                    // {
                    // auto child_temp = addWidget(std::make_unique<PNode>(child_temp_xml_brain, child_temp_xml_brain->message_node_));
                    // }else addWidget(std::make_unique<Wt::WText>("Template not found"));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::TEXT)
                {
                    addWidget(std::make_unique<Wt::WText>(temp_var_data.implementation_text_));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::INPUT)
                {
                    addWidget(std::make_unique<Wt::WLineEdit>(temp_var_data.implementation_text_));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::BUTTON)
                {
                    addWidget(std::make_unique<Wt::WPushButton>(temp_var_data.implementation_text_));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::TEXTAREA)
                {
                    addWidget(std::make_unique<Wt::WTextArea>(temp_var_data.implementation_text_));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::CHECKBOX)
                {
                    addWidget(std::make_unique<Wt::WCheckBox>(temp_var_data.implementation_text_));
                }
                else if (temp_var_data.implementation_type_ == TempVarImplementationType::RADIO)
                {
                    addWidget(std::make_unique<Wt::WRadioButton>(temp_var_data.implementation_text_));
                }
                else
                    addWidget(std::make_unique<Wt::WText>("Widget type not found"));
            }
            else
            {

                auto text_value = node->ToText()->Value();

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
                                                    node->ToText()->SetValue(text_input->text().toUTF8().c_str());
                                                    xml_brain_->saveXmlToDbo(); });

                text_input->setMinimumSize(Wt::WLength(300, Wt::LengthUnit::Pixel), Wt::WLength::Auto);
                text_input->escapePressed().connect([=]
                                                    {
                                                    text_input->hide();
                                                    text->show(); });
            }
        }
    }

    if (node->FirstChild())
    {
        for (auto child = node->FirstChild(); child; child = child->NextSibling())
        {
            auto child_PNode = addWidget(std::make_unique<PNode>(xml_brain_, child));
        }
    }
}