#include "101-Stylus/XMLBrain.h"

#include "002-Dbo/Session.h"

XMLBrain::XMLBrain(Session &session, XmlDboRecord dbo_temp_data, Stylus *stylus)
    : session_(session),
      dbo_temp_data_(dbo_temp_data),
      stylus_(stylus)
{
    xml_doc_ = new tinyxml2::XMLDocument();
    message_node_ = xml_doc_->NewElement("message");
    message_node_->ToElement()->SetAttribute("dbo_id", dbo_temp_data_.dbo_temp_id);
    message_node_->ToElement()->SetAttribute("id", dbo_temp_data_.temp_id.toUTF8().c_str());
    xml_doc_->InsertFirstChild(message_node_);

    tinyxml2::XMLDocument temp_doc;
    temp_doc.Parse(dbo_temp_data_.xml_temp.toUTF8().c_str());
    auto child = temp_doc.FirstChild();
    if (child)
    {
        for (child; child; child = child->NextSibling())
        {
            auto new_child = child->DeepClone(xml_doc_);
            message_node_->InsertEndChild(new_child);
        }
    }
    else
    {
        // document dose not have any elements so we need to add the text content of the template to the message node
        auto text_node = xml_doc_->NewText(dbo_temp_data_.xml_temp.toUTF8().c_str());
        message_node_->InsertEndChild(text_node);
    }
}

void XMLBrain::saveXmlToDbo()
{
    std::cout << "\n\n saveXmlToDbo() \n\n";
    auto transaction = Dbo::Transaction(session_);
    dbo::ptr<XmlTemplate> xml_template = session_.find<XmlTemplate>().where("id = ?").bind(dbo_temp_data_.dbo_temp_id).resultValue();

    if (!xml_template)
    {
        std::cout << "\n\n no xml template found with the temp_id: " << dbo_temp_data_.dbo_temp_id << "\n\n";
    }
    else
    {
        Wt::WString value = "";
        for (auto node = message_node_->FirstChild(); node; node = node->NextSibling())
        {
            tinyxml2::XMLPrinter printer;
            node->Accept(&printer);
            value += printer.CStr();
        }

        dbo_temp_data_.xml_temp = value;

        xml_template.modify()->temp_id = dbo_temp_data_.temp_id;
        xml_template.modify()->xml_temp = dbo_temp_data_.xml_temp;
        std::cout << "\n\n xml_template->xml_temp: " << xml_template->xml_temp.toUTF8() << "\n\n";
    }

    transaction.commit();
}

TempVarData tempText(tinyxml2::XMLNode *node)
{
    TempVarData temp_var_data;
    // std::cout << "\n\n------------" << node_->ToText()->Value() << "------------\n\n";
    if (!node->ToText())
    {
        std::cout << "\n\n ERROR TCTemplate node is not text\n\n";
        return temp_var_data;
    }
    // boost::regex template_regex_ = boost::regex(R"(\$\{.*?\})");
    boost::regex template_regex_ = boost::regex(R"(\$\{[A-Za-z1-9-]*[ ]?(class=\"([^"]*)\")?[ ]?(implementation=\"[A-Za-z1-9 :\-|?]*\")?[ ]?\})");
    // boost::regex template_regex_ = boost::regex(R"(\$\{[A-Za-z1-9-]*[ ]?(class=\"([^"]*)\")?[ ]?(implementation=\"[A-Za-z-]*\")?[ ]?\})");
    // boost::regex template_regex_ = boost::regex(R"(\$\{[A-Za-z-]*[ ]\})");
    std::string node_text = node->ToText()->Value();
    if (boost::regex_match(node_text, template_regex_))
    {
        std::string temp_var = node->ToText()->Value();
        auto whitespace_pos = temp_var.find(" ");

        // set name_
        if (whitespace_pos == std::string::npos)
        {
            temp_var_data.name_ = temp_var.substr(2, temp_var.size() - 3);
        }
        else
        {
            temp_var_data.name_ = temp_var.substr(2, whitespace_pos - 2);
        }

        // set style_classes_
        auto class_pos = temp_var.find("class=\"");
        if (class_pos != std::string::npos)
        {
            auto class_end_pos = temp_var.find("\"", class_pos + 7);
            temp_var_data.style_classes_ = temp_var.substr(class_pos + 7, class_end_pos - class_pos - 7);
        }
        // set implementation_
        auto implementation_pos = temp_var.find("implementation=\"");
        if (implementation_pos != std::string::npos)
        {
            // std::cout << "implementation_pos <" << implementation_pos << ">";

            auto implementation_end_pos = temp_var.find("\"", implementation_pos + 16);
            temp_var_data.implementation_ = temp_var.substr(implementation_pos + 16, implementation_end_pos - implementation_pos - 16);
        }

        std::string implementation = temp_var_data.implementation_;
        auto column_pos = implementation.find(":");
        std::string widget_type = "";
        std::string widget_text = "";
        if (column_pos != std::string::npos)
        {
            widget_type = implementation.substr(0, column_pos);
            widget_text = implementation.substr(column_pos + 1);
        }
        else
            widget_type = implementation;

        temp_var_data.implementation_text_ = widget_text;
        if (widget_type == "text")
            temp_var_data.implementation_type_ = TempVarImplementationType::TEXT;
        else if (widget_type == "input")
            temp_var_data.implementation_type_ = TempVarImplementationType::INPUT;
        else if (widget_type == "textarea")
            temp_var_data.implementation_type_ = TempVarImplementationType::TEXTAREA;
        else if (widget_type == "button")
            temp_var_data.implementation_type_ = TempVarImplementationType::BUTTON;
        else if (widget_type == "checkbox")
            temp_var_data.implementation_type_ = TempVarImplementationType::CHECKBOX;
        else if (widget_type == "radio")
            temp_var_data.implementation_type_ = TempVarImplementationType::RADIO;
        else
            temp_var_data.implementation_type_ = TempVarImplementationType::TEXT;

        // std::cout << "var name <" << temp_var_data.name_ << "> ----- ";
        // std::cout << "implementation <" << temp_var_data.implementation_ << ">\n";
        return temp_var_data;
    }
    return temp_var_data;
}

std::vector<TempVarData> tempTexts(std::string text)
{
    std::vector<TempVarData> temp_var_datas;
    boost::regex template_regex_ = boost::regex(R"(\$\{[A-Za-z1-9-]*[ ]?(class=\"([^"]*)\")?[ ]?(implementation=\"[A-Za-z1-9 :\-]*\")?[ ]?\})");
    // boost::regex template_regex_ = boost::regex(R"(\$\{[A-Za-z1-9-]*[ ]?(class=\"([^"]*)\")?[ ]?(implementation=\"[A-Za-z-]*\")?[ ]?\})");
    boost::sregex_iterator it(text.begin(), text.end(), template_regex_);
    boost::sregex_iterator end;
    while (it != end)
    {
        boost::smatch match = *it;
        std::string temp_var = match.str();
        TempVarData temp_var_data;
        auto whitespace_pos = temp_var.find(" ");

        // set name_
        if (whitespace_pos == std::string::npos)
        {
            temp_var_data.name_ = temp_var.substr(2, temp_var.size() - 3);
        }
        else
        {
            temp_var_data.name_ = temp_var.substr(2, whitespace_pos - 2);
        }

        // set style_classes_
        auto class_pos = temp_var.find("class=\"");
        if (class_pos != std::string::npos)
        {
            auto class_end_pos = temp_var.find("\"", class_pos + 7);
            temp_var_data.style_classes_ = temp_var.substr(class_pos + 7, class_end_pos - class_pos - 7);
        }
        // set implementation_
        auto implementation_pos = temp_var.find("implementation=\"");
        if (implementation_pos != std::string::npos)
        {
            auto implementation_end_pos = temp_var.find("\"", implementation_pos + 16);
            temp_var_data.implementation_ = temp_var.substr(implementation_pos + 16, implementation_end_pos - implementation_pos - 16);
        }

        temp_var_datas.push_back(temp_var_data);
        ++it;
    }
    return temp_var_datas;
}