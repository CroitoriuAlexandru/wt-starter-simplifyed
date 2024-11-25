#pragma once
#include "100-Utils/tinyxml2/tinyxml2.h"
#include "101-Stylus/Tailwind/Category.h"
#include "101-Stylus/Stylus.h"

#include "101-Stylus/Tailwind/Base.h"

#include <string>
#include <vector>
#include <unordered_map>

class TailwindConfig
{
public:
    TailwindConfig(std::shared_ptr<Stylus> stylus);
    std::shared_ptr<Stylus> stylus_;
    std::unordered_map<std::string, std::shared_ptr<XMLBrain>> xml_brains_;
    void readConfigurationXMLs();

    TSvg svg;
    TSizing sizing;
    TTypography typography;
    TBackgrounds backgrounds;
    TAccesibility accesibility;
    TFlexboxAndGrid flexboxAndGrid;
    TFilters filters;
    TTables tables;
    TTransitionsAndAnimation transitionsAndAnimation;
    TTransforms transforms;
    TInteractivity interactivity;
    TLayout layout;
    TSpacing spacing;
    TEffects effects;
    TBorders borders;

    std::vector<std::string> getStyleClasses();

    std::unordered_map<std::string, std::vector<variant_and_value_pair>> variants_and_css;
    std::vector<variant_and_value_pair> blur_variants;
    std::vector<variant_and_value_pair> brightness_variants;
    std::vector<color_variants_css_pair> color_variants;

    std::unordered_map<std::string, ProprietyData> proprieties;
    void readProprieties();
    ProprietyData readXmlProp(std::string propName);

    std::unordered_map<std::string, std::string> extend;
    std::string opacity_regex;
    std::string spacing_regex;

    std::string no_start_characters;
    std::string custom_value_regex;
    std::string colors_regex;
    std::string no_end_characters;

    std::string color_custom_value_regex;

    ConfigFileData configFileData;

    void getColorVariants(tinyxml2::XMLElement *colors_node);

    std::vector<variant_and_value_pair> getVariants(tinyxml2::XMLElement *variants_node);

private:
};