#pragma once
#include "100-Utils/tinyxml2/tinyxml2.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/regex.hpp>

class TailwindConfig;

typedef std::pair<std::string, std::string> variant_and_value_pair;
// typedef std::vector<variant_and_value_pair> variant_css_vector;
typedef std::pair<std::string, std::vector<variant_and_value_pair>> color_variants_css_pair; // color -> variants
// typedef std::vector<many_variants_css_pair> color_variants_css_vector;

struct ConfigFileData
{
    std::string config_start = "module.exports = {\n";
    std::string darkMode = "'class'";
    std::string theme;
    std::unordered_map<std::string, std::string> extend;
    // std::vector<std::string> extend_proprieties;

    std::string spacing_scale;
    std::string colors_scale;
    std::string opacity_scale;

    std::string strokeWidth;

    std::string getFileContent();
};

struct ProprietyData
{
    std::string prop_name;
    std::string class_name;
    std::string docs_link;
    std::string reset_command;
    std::string config_name;
    bool custom_value;
    bool can_extend;
    std::vector<std::pair<std::string, std::string>> variant_value;
    std::string includes;
};

class Propriety
{
public:
    Propriety(TailwindConfig *tailwind_config) : tailwind_config_(tailwind_config), regex(boost::regex("")) {};
    Propriety() {};
    // pair of the class name variant and the value that it applies
    std::vector<variant_and_value_pair> variant_value_pairs;
    // pair of the class name and the css propriety that it applies
    std::vector<std::string> styleClasses;
    // name of the style class
    std::string class_name;
    // indicator if the propriety can have custom values
    bool custom_value;
    // link to tailwind docs
    std::string docs_link;
    // resset command for the propriety
    std::string reset_command;
    // config propriety name
    std::string config_name;
    void setPropriety(tinyxml2::XMLElement *prop_node);
    void includeVariants(std::string variantName);

    void includeColorVariants();
    void includeSpacingVariants();
    // at the moment only used by the max width
    void includeScreenVariants();

    boost::regex regex;

    TailwindConfig *tailwind_config_;

    std::vector<std::string> getClasses();
    void readNode(tinyxml2::XMLElement *prop_node);
};