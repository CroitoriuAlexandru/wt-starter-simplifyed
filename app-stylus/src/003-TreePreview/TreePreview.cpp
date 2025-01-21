#include "003-TreePreview/TreePreview.h"
#include "003-TreePreview/PTree.h"
#include "101-Stylus/XMLBrain.h"
#include "101-Stylus/Stylus.h"

#include <Wt/WApplication.h>

TreePreview::TreePreview(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    setStyleClass("h-screen max-h-screen bg-gray-800 !min-w-[380px] !max-w-[380px] h-screen relative flex flex-col");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);

    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setXmlBrain(xml_brain); });

    preview_wrapper_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    preview_wrapper_->setStyleClass("h-full overflow-auto");
    auto text_area_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
    text_area_ = text_area_wrapper->addWidget(std::make_unique<Wt::WTextArea>());
    text_area_wrapper->setStyleClass("w-full p-2");
    text_area_->setStyleClass("line-edit-stylus-edditor sticy bottom-0");

    text_area_->enterPressed().connect([=]()
                                       {
                                            // if selected_node is text
                                            // if selected_node is element and has text
                                            // if selected_node is element and has no children
                                           if (xml_brain_->selected_node_->ToText())
                                           {
                                                std::string text = text_area_->text().toUTF8();
                                                // remove whitespace and newlines
                                                text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
                                                if(text.empty())
                                                {
                                                    auto selected_node = xml_brain_->selected_node_;
                                                    auto parent = selected_node->Parent();
                                                    parent->DeleteChild(selected_node);
                                                    xml_brain_->selected_node_ = parent;
                                                }else {
                                                    xml_brain_->selected_node_->ToText()->SetValue(text_area_->text().toUTF8().c_str());
                                                }
                                                stylus_->setXmlBrain(xml_brain_);
                                                xml_brain_->saveXmlToDbo();
                                           }
                                           else if (xml_brain_->selected_node_->ToElement() && xml_brain_->selected_node_->ToElement()->FirstChild() && xml_brain_->selected_node_->ToElement()->FirstChild()->ToText())
                                           {
                                               xml_brain_->selected_node_->FirstChild()->ToText()->SetValue(text_area_->text().toUTF8().c_str());
                                               stylus_->setXmlBrain(xml_brain_);
                                               xml_brain_->saveXmlToDbo();
                                           }
                                           else if (!xml_brain_->selected_node_->ToElement()->FirstChild())
                                           {
                                               auto new_child = xml_brain_->xml_doc_->NewText(text_area_->text().toUTF8().c_str());
                                               xml_brain_->selected_node_->ToElement()->InsertEndChild(new_child);
                                               stylus_->setXmlBrain(xml_brain_);
                                               xml_brain_->saveXmlToDbo();
                                           } });
    text_area_->keyWentDown().connect([=](Wt::WKeyEvent e)
                                      { Wt::WApplication::instance()->globalKeyWentDown().emit(e); });
}

void TreePreview::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    preview_wrapper_->clear();
    xml_brain_ = xml_brain;
    if (xml_brain)
    {
        preview_wrapper_->addWidget(std::make_unique<PTree>(xml_brain, xml_brain->message_node_));

        if (xml_brain->selected_node_->ToText())
        {
            text_area_->setText(xml_brain->selected_node_->ToText()->Value());
            text_area_->setEnabled(true);
            text_area_->setHidden(false);
            text_area_->setFocus(true);
        }
        else if (xml_brain_->selected_node_->ToElement() && xml_brain_->selected_node_->ToElement()->FirstChild() && xml_brain_->selected_node_->ToElement()->FirstChild()->ToText())
        {
            text_area_->setText(xml_brain->selected_node_->FirstChild()->ToText()->Value());
            text_area_->setEnabled(true);
            text_area_->setHidden(false);
            text_area_->setFocus(true);
        }
        else if (!xml_brain_->selected_node_->FirstChild())
        {
            text_area_->setText("");
            text_area_->setEnabled(true);
            text_area_->setHidden(false);
            text_area_->setFocus(true);
        }
        else
        {
            text_area_->setText("");
            text_area_->setHidden(true);
        }
    }
}
// xml_brain_->selected_node_->ToElement() && xml_brain_->selected_node_->ToElement()->FirstChild() && xml_brain_->selected_node_->ToElement()->FirstChild()->ToText()