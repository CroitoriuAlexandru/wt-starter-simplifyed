#include "005-ClassesEdditor/ClassesEdditor.h"
#include "101-Stylus/Stylus.h"
#include "101-Stylus/XMLBrain.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WApplication.h>

ClassesEdditor::ClassesEdditor(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    setStyleClass("h-screen max-h-screen overflow-y-auto overflow-x-none bg-gradient-dark !min-w-[450px] !max-w-[450px] relative");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);

    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setXmlBrain(xml_brain); });

    auto class_input_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
    auto class_input = class_input_wrapper->addWidget(std::make_unique<Wt::WLineEdit>());

    class_input_wrapper->setStyleClass("p-2");
    class_input->setStyleClass("line-edit-stylus-edditor");
    class_input->setPlaceholderText("Add class");

    class_input->keyWentDown().connect([=](Wt::WKeyEvent e)
                                       { Wt::WApplication::instance()->globalKeyWentDown().emit(e); });

    class_input->enterPressed().connect([=]
                                        {
                            if (class_input->text().empty())
                                return;
                            if (xml_brain_)
                            {
                                auto selected_node = xml_brain_->selected_node_;
                                if (!selected_node)
                                {
                                    std::cout << "\n selected node in classes edditor is null\n";
                                    return;
                                }
                                if (!selected_node->ToElement())
                                {
                                    std::cout << "\n selected node in classes edditor is not an element\n";
                                    return;
                                }
                                auto element = selected_node->ToElement();
                                if (!element->Attribute("class"))
                                {
                                    element->SetAttribute("class", class_input->text().toUTF8().c_str());
                                }
                                else
                                {
                                    std::string classes = element->Attribute("class");
                                    classes += class_input->text().toUTF8() + " ";
                                    element->SetAttribute("class", classes.c_str());
                                }
                                xml_brain_->saveXmlToDbo();
                                class_input->setText("");
                                stylus_->setXmlBrain(xml_brain_);
                            } });

    classes_inputs_wrapper_ = addWidget(std::make_unique<Wt::WContainerWidget>());
}

void ClassesEdditor::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    classes_inputs_.clear();
    classes_inputs_wrapper_->clear();
    std::vector<std::string> classes_vector;
    if (xml_brain)
    {
        xml_brain_ = xml_brain;
        auto selected_node = xml_brain_->selected_node_;
        if (!selected_node)
        {
            std::cout << "\n selected node in classes edditor is null\n";
            return;
        }

        if (selected_node->ToText())
        {
            auto temp_var_data = tempText(selected_node);
            if (temp_var_data.name_ != "")
            {
                auto classes = temp_var_data.style_classes_;
                std::istringstream iss(classes);
                classes_vector = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
            }
        }
        else if (selected_node->ToElement())
        {
            auto element = selected_node->ToElement();
            if (!element->Attribute("class"))
            {
                std::cout << "\n selected node in classes edditor has no class attribute\n";
                return;
            }
            std::string classes = element->Attribute("class");
            std::istringstream iss(classes);
            classes_vector = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        }
        else
        {
            std::cout << "\n selected node in classes edditor is not an element or text\n";
        }

        // iterate over the classes vector and add each class to the classes_inputs_wrapper_
        for (auto &class_name : classes_vector)
        {
            auto class_input_wrapper = classes_inputs_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
            auto class_input = class_input_wrapper->addWidget(std::make_unique<Wt::WLineEdit>());
            auto x_btn = class_input_wrapper->addWidget(std::make_unique<Wt::WText>("x"));
            class_input_wrapper->setStyleClass("p-2 flex");
            x_btn->setStyleClass("cursor-pointer px-2 bg-red-600 text-white rounded-md mx-2 my-1");
            class_input->setStyleClass("line-edit-stylus-edditor");
            class_input->setText(class_name);

            class_input->enterPressed().connect([=]
                                                {
                                                    std::string new_classes;
                                                    for (auto &class_input_map : classes_inputs_)
                                                    {
                                                        new_classes += class_input_map.begin()->second->text().toUTF8() + " ";
                                                    }
                                                    setSelectedClasses(new_classes); });

            x_btn->clicked().connect([=]
                                     {
                                            std::string new_classes;
                                            for (auto &class_input_map : classes_inputs_)
                                            {
                                                if (class_input_map.begin()->second != class_input)
                                                {
                                                    new_classes += class_input_map.begin()->second->text().toUTF8() + " ";
                                                }
                                            }
                                            setSelectedClasses(new_classes); });

            classes_inputs_.push_back({{class_name, class_input}});
        }
    }
}

void ClassesEdditor::setSelectedClasses(std::string new_classes)
{
    if (xml_brain_->selected_node_->ToElement())
    {
        auto element = xml_brain_->selected_node_->ToElement();
        element->SetAttribute("class", new_classes.c_str());
    }
    else if (xml_brain_->selected_node_->ToText())
    {
        auto temp_var_data = tempText(xml_brain_->selected_node_);
        if (temp_var_data.name_ != "")
        {
            temp_var_data.style_classes_ = new_classes;
            std::string temp_var = "${" + temp_var_data.name_ + " class=\"" + temp_var_data.style_classes_ + "\" widget=" + temp_var_data.widget_ + "(" + temp_var_data.widget_text_ + ")}";
            xml_brain_->selected_node_->ToText()->SetValue(temp_var.c_str());
        }
    }
    xml_brain_->saveXmlToDbo();
    stylus_->setXmlBrain(xml_brain_);
}
