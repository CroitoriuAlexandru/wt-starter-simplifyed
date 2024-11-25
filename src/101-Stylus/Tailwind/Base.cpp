#include "101-Stylus/Tailwind/Base.h"
#include <iostream>
#include "101-Stylus/Tailwind/TailwindConfig.h"

std::string ConfigFileData::getFileContent()
{
    std::string file_content = "";

    file_content += "tailwind.config = {\n";
    file_content += "\tdarkMode: " + darkMode + ",\n";
    file_content += "\ttheme: {\n";
    file_content += "\t\textend: {\n";

    // iterate over extend and place all the values in file_content
    for (const auto &extend_pair : extend)
    {
        file_content += extend_pair.second;
    }
    file_content += "\t\t},\n";
    file_content += "\t},\n";
    file_content += "};\n";

    return file_content;
}

void Propriety::readNode(tinyxml2::XMLElement *prop_node)
{
    if (!prop_node->Attribute("id"))
    {
        std::cout << "\n\n id attribute not found \n\n";
        return;
    }

    auto docs_node = prop_node->FirstChildElement("tailwind-docs");
    if (!docs_node || !docs_node->GetText())
    {
        std::cout << "\n\n docs_node or text not found " << prop_node->Attribute("id") << "\n\n";
        return;
    }

    auto reset_command_node = prop_node->FirstChildElement("reset-command");
    if (!reset_command_node || !reset_command_node->GetText())
    {
        std::cout << "\n\n reset_command_node or text not found \n\n";
        return;
    }

    auto classes_node = prop_node->FirstChildElement("classes");
    if (!classes_node || !classes_node->Attribute("className"))
    {
        std::cout << "\n\n classes_node or className attribute not found \n\n";
        return;
    }
    if (classes_node->Attribute("customValue"))
    {
        if (std::string(classes_node->Attribute("customValue")).compare("true") == 0)
        {
            custom_value = true;
        }
        else if (std::string(classes_node->Attribute("customValue")).compare("false") == 0)
        {
            custom_value = false;
        }
        else
        {
            std::cout << "\n\n customValue attribute not true or false but its present :( \n\n";
            return;
        }
    }

    class_name = classes_node->Attribute("className");

    config_name = prop_node->Attribute("id");
    docs_link = docs_node->GetText();
    reset_command = reset_command_node->GetText();
}

void Propriety::setPropriety(tinyxml2::XMLElement *prop_node)
{
    if (!prop_node)
    {
        std::cout << "\n\n prop_node not recived by Propriety is not valid !!! \n\n";
        return;
    }
    readNode(prop_node);

    auto classes_node = prop_node->FirstChildElement("classes");
    if (!classes_node || !classes_node->Attribute("className"))
    {
        std::cout << "\n\n classes_node or className attribute not found \n\n";
        return;
    }

    variant_value_pairs = tailwind_config_->getVariants(classes_node);
    tailwind_config_->variants_and_css[config_name] = variant_value_pairs;

    bool has_default = false;
    for (auto variant : variant_value_pairs)
    {
        std::string separator = "-";
        if (class_name.compare("") == 0)
        {
            separator = "";
        }
        std::string style_class;

        if (variant.first.compare("DEFAULT") == 0)
        {
            has_default = true;
            style_class = class_name;
        }
        else
        {
            style_class = class_name + separator + variant.first;
        }

        styleClasses.push_back(style_class);
    }

    // set regex
    std::string regex_string = "";

    if (variant_value_pairs.size() > 0 && class_name != "" && !has_default)
        regex_string += class_name + "-("; // class_name not empty and has many variants
    else if (class_name != "" && has_default)
        regex_string += class_name + "("; // class_name not empty and has default variant
    else if (variant_value_pairs.size() > 0)
        regex_string += "("; // no class_name but it has variants

    for (auto variant : variant_value_pairs)
    {
        // if the variant.first has a / in it then add a \ before the /
        std::string variant_first = variant.first;
        if (variant_first.find("/") != std::string::npos)
        {
            variant_first.insert(variant_first.find("/"), "\\");
        }
        if (variant.first.compare("DEFAULT") == 0)
            continue;
        if (has_default)
            regex_string += "-";
        regex_string += variant_first + "|";
    }
    if (custom_value)
    {
        if (has_default)
            regex_string += "-";
        regex_string += tailwind_config_->custom_value_regex; // add custom value regex
    }
    else
    {
        regex_string.pop_back(); // [p[ the last | character
    }
    if (variant_value_pairs.size() > 0)
        regex_string += ")"; // end the enumeration of variants
    if (has_default)
        regex_string += "?"; // make the default variant optional

    regex_string = tailwind_config_->no_start_characters + regex_string + tailwind_config_->no_end_characters;
    regex = boost::regex(regex_string);

    // std::cout << "\n\n---------------------------\n" << regex_string << "\n---------------------------\n\n";
    if (classes_node->Attribute("include"))
    {
        std::string includeAttribute = classes_node->Attribute("include");
        // std::cout << "\n\n include attribute found \n\n";
        if (includeAttribute.compare("colors") == 0)
        {
            // std::cout << "\n\n include colors found \n\n";
            includeColorVariants();
        }
        else if (includeAttribute.compare("spacing") == 0)
        {
            // std::cout << "\n\n include spacing found \n\n";
            includeSpacingVariants();
        }
        else if (includeAttribute.compare("screens/breakpoints") == 0)
        {
            // only for max width the included breakpoints need to be prefixed with 'screen' (max-w-screen-md)
            // std::cout << "\n\n include breakpoints found \n\n";
            includeScreenVariants();
        }
        else
        {
            includeVariants(includeAttribute);
        }
    }
}

void Propriety::includeVariants(std::string variantName)
{
    std::vector<std::pair<std::string, std::string>> variants;
    if (tailwind_config_->variants_and_css.find(variantName) != tailwind_config_->variants_and_css.end())
    {
        variants = tailwind_config_->variants_and_css[variantName];
    }
    else
    {
        std::cout << "\n\n variant not found " << variantName << " \n\n";
        return;
    }

    for (auto variant : variants)
    {
        std::string separator = "-";
        if (class_name.compare("") == 0)
        {
            separator = "";
        }
        std::string style_class;

        if (variant.first.compare("DEFAULT") == 0)
        {
            style_class = class_name;
        }
        else
        {
            style_class = class_name + separator + variant.first;
        }
        variant_value_pairs.push_back(std::make_pair(variant.first, variant.second));
        styleClasses.push_back(style_class);
    }

    // set regex
    std::string regex_string = "";
    if (class_name != "")
        regex_string += class_name + "("; // class_name not empty and has more then one variant
    else
        regex_string += "("; // no class_name but it has variants

    for (auto variant : variant_value_pairs)
    {
        // if the variant.first has a / in it then add a \ before the /
        std::string variant_first = variant.first;
        if (variant_first.find("/") != std::string::npos)
        {
            variant_first.insert(variant_first.find("/"), "\\");
        }
        if (variant.first.compare("DEFAULT") == 0)
            continue;
        regex_string += "-" + variant_first + "|";
    }
    regex_string.pop_back(); // [p[ the last | character
    regex_string += ")?";    // end the enumeration of variants
    regex_string = tailwind_config_->no_start_characters + regex_string + tailwind_config_->no_end_characters;
    regex = boost::regex(regex_string);
}

void Propriety::includeScreenVariants()
{
    for (auto screen_variant : tailwind_config_->variants_and_css["screen"])
    {
        std::string screen_variant_name = screen_variant.first;
        std::string screen_variant_value = screen_variant.second;
        std::string style_class = class_name + "-screen-" + screen_variant_name;
        styleClasses.push_back(style_class);
        variant_value_pairs.push_back(std::make_pair("screen-" + screen_variant_name, screen_variant_value));
    }

    std::string regex_string = class_name;
    if (variant_value_pairs.size() > 0)
        regex_string += "-(";

    std::string screens_regex;

    for (auto variant : variant_value_pairs)
    {
        // if the variant.first has a / in it then add a \ before the /
        screens_regex += variant.first + "|";
        std::string variant_first = variant.first;
        if (variant_first.find("/") != std::string::npos)
        {
            variant_first.insert(variant_first.find("/"), "\\");
        }

        regex_string += variant_first + "|";
    }

    // set regex
    regex_string += screens_regex + tailwind_config_->custom_value_regex; // add custom value regex
    regex_string += ")";                                                  // end the enumeration of variants
    regex_string = tailwind_config_->no_start_characters + regex_string + tailwind_config_->no_end_characters;
    // std::cout << "\n\n" << regex_string << "\n\n";
    regex = boost::regex(regex_string);
}

void Propriety::includeSpacingVariants()
{
    for (auto spacing_variant : tailwind_config_->variants_and_css["spacing"])
    {
        std::string spacing_variant_name = spacing_variant.first;
        std::string spacing_variant_value = spacing_variant.second;
        std::string style_class = class_name + "-" + spacing_variant_name;
        styleClasses.push_back(style_class);
        variant_value_pairs.push_back(std::make_pair(spacing_variant_name, spacing_variant_value));
    }

    std::string regex_string = class_name;
    if (variant_value_pairs.size() > 0)
        regex_string += "-(";

    for (auto variant : variant_value_pairs)
    {
        // if the variant.first has a / in it then add a \ before the /
        std::string variant_first = variant.first;
        if (variant_first.find("/") != std::string::npos)
        {
            variant_first.insert(variant_first.find("/"), "\\");
        }

        regex_string += variant_first + "|";
    }

    // set regex
    regex_string += tailwind_config_->spacing_regex; // add custom value regex
    regex_string += ")";                             // end the enumeration of variants
    regex_string = tailwind_config_->no_start_characters + regex_string + tailwind_config_->no_end_characters;
    // std::cout << "\n\n" << regex_string << "\n\n";
    regex = boost::regex(regex_string);
}

void Propriety::includeColorVariants()
{
    for (auto color : tailwind_config_->color_variants)
    {
        std::string color_name = color.first;
        for (auto color_variant : color.second)
        {
            std::string color_variant_name = color_variant.first;
            std::string color_variant_value = color_variant.second;
            std::string separator = "";
            if (color_name.compare("") != 0)
            {
                separator = "-";
            }
            std::string style_class = class_name + separator + color_name + "-" + color_variant_name;
            styleClasses.push_back(style_class);
        }
    }

    // set regex
    std::string regex_string = tailwind_config_->no_start_characters + class_name + "-(";
    for (auto variant : variant_value_pairs)
    {
        regex_string += variant.first + "|";
    }
    std::string colors_regex_new = tailwind_config_->colors_regex;
    // remove the first character of colors_regex_new
    colors_regex_new.erase(0, 1); // this was the starting ( character

    regex_string += colors_regex_new;
    // std::cout << "\n\n" << regex_string << "\n\n";
    regex = boost::regex(regex_string);

    //     std::cout << "\n\n";
    //     for(auto styleClass : styleClasses){
    //         std::cout << styleClass.first << " | ";
    //     }
    //     std::cout << "\n\n";
}

std::vector<std::string> Propriety::getClasses()
{
    std::vector<std::string> classes = {"none"};
    for (auto styleClass : styleClasses)
    {
        classes.push_back(styleClass);
    }
    return classes;
}
