#include "101-Stylus/Tailwind/Category.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"
#include <iostream>

void TBackgrounds::setGradientStepAndColorProprieties(tinyxml2::XMLElement *prop_node)
{
    backgroundColorFrom.readNode(prop_node);
    backgroundColorVia = backgroundColorFrom;
    backgroundColorTo = backgroundColorFrom;

    backgroundColorFrom.class_name = "from";
    backgroundColorVia.class_name = "via";
    backgroundColorTo.class_name = "to";

    backgroundColorFromStep = backgroundColorFrom;
    backgroundColorViaStep = backgroundColorVia;
    backgroundColorToStep = backgroundColorTo;

    std::vector<variant_and_value_pair> gradient_steps = tailwind_config_->getVariants(prop_node->FirstChildElement("classes"));

    for (auto step : gradient_steps)
    {
        backgroundColorFromStep.styleClasses.push_back("from-" + step.first);
        backgroundColorViaStep.styleClasses.push_back("via-" + step.first);
        backgroundColorToStep.styleClasses.push_back("to-" + step.first);
    }

    for (auto color : tailwind_config_->color_variants)
    {
        std::string color_name = color.first;
        for (auto variant : color.second)
        {
            std::string variant_name = variant.first;
            std::string variant_value = variant.second;
            std::string separator = "";
            if (color_name.compare("") != 0)
            {
                separator = "-";
            }
            std::string style_class = color_name + separator + variant_name;

            backgroundColorFrom.styleClasses.push_back(style_class);
            backgroundColorVia.styleClasses.push_back(style_class);
            backgroundColorTo.styleClasses.push_back(style_class);

            backgroundColorFrom.variant_value_pairs.push_back(std::make_pair(color_name + separator + variant_name, variant_value));
            backgroundColorVia.variant_value_pairs.push_back(std::make_pair(color_name + separator + variant_name, variant_value));
            backgroundColorTo.variant_value_pairs.push_back(std::make_pair(color_name + separator + variant_name, variant_value));
        }
    }

    // regex
    std::string from_regex = tailwind_config_->no_start_characters + "from-" + tailwind_config_->colors_regex;
    std::string via_regex = tailwind_config_->no_start_characters + "via-" + tailwind_config_->colors_regex;
    std::string to_regex = tailwind_config_->no_start_characters + "to-" + tailwind_config_->colors_regex;

    backgroundColorFrom.regex = boost::regex(from_regex);
    backgroundColorVia.regex = boost::regex(via_regex);
    backgroundColorTo.regex = boost::regex(to_regex);

    // steps regex
    std::string steps_regex = "(";
    for (auto step : gradient_steps)
    {
        steps_regex += step.first + "|";
    }
    steps_regex += tailwind_config_->custom_value_regex;

    std::string step_from_regex = tailwind_config_->no_start_characters + "from-" + steps_regex + ")" + tailwind_config_->no_end_characters;
    std::string step_via_regex = tailwind_config_->no_start_characters + "via-" + steps_regex + ")" + tailwind_config_->no_end_characters;
    std::string step_to_regex = tailwind_config_->no_start_characters + "to-" + steps_regex + ")" + tailwind_config_->no_end_characters;

    // // std::cout << "\n\n step_from_regex: " << step_from_regex << "\n\n";
    backgroundColorFromStep.regex = boost::regex(step_from_regex);
    backgroundColorViaStep.regex = boost::regex(step_via_regex);
    backgroundColorToStep.regex = boost::regex(step_to_regex);
}

void TFlexboxAndGrid::setGapProprieties(tinyxml2::XMLElement *prop_node)
{
    gap.setPropriety(prop_node);
    gap_x = gap;
    gap_y = gap;

    gap_x.class_name = "gap-x";
    gap_y.class_name = "gap-y";

    gap_x.reset_command = "gap-x-res";
    gap_y.reset_command = "gap-y-res";

    gap_x.styleClasses.clear();
    gap_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : gap.variant_value_pairs)
    {
        gap_x.styleClasses.push_back("gap-x-" + variant.first);
        gap_y.styleClasses.push_back("gap-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string gap_x_regex = tailwind_config_->no_start_characters + "gap-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string gap_y_regex = tailwind_config_->no_start_characters + "gap-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    gap_x.regex = boost::regex(gap_x_regex);
    gap_y.regex = boost::regex(gap_y_regex);
}

void TTables::setBorderSpacingProprieties(tinyxml2::XMLElement *prop_node)
{
    borderSpacing.setPropriety(prop_node);
    borderSpacing_x = borderSpacing;
    borderSpacing_y = borderSpacing;

    borderSpacing_x.class_name = "border-spacing-x";
    borderSpacing_y.class_name = "border-spacing-y";

    borderSpacing_x.reset_command = "border-spacing-x-res";
    borderSpacing_y.reset_command = "border-spacing-y-res";

    std::string regex_values = "";
    for (auto variant : borderSpacing.variant_value_pairs)
    {
        borderSpacing_x.styleClasses.push_back("border-spacing-x-" + variant.first);
        borderSpacing_y.styleClasses.push_back("border-spacing-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string border_spacing_x_regex = tailwind_config_->no_start_characters + "border-spacing-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_spacing_y_regex = tailwind_config_->no_start_characters + "border-spacing-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    borderSpacing_x.regex = boost::regex(border_spacing_x_regex);
    borderSpacing_y.regex = boost::regex(border_spacing_y_regex);
}

void TTransforms::setScaleProprieties(tinyxml2::XMLElement *prop_node)
{
    scale.setPropriety(prop_node);
    scale_x = scale;
    scale_y = scale;

    scale_x.class_name = "scale-x";
    scale_y.class_name = "scale-y";

    scale_x.reset_command = "scale-x-res";
    scale_y.reset_command = "scale-y-res";

    scale_x.styleClasses.clear();
    scale_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : scale.variant_value_pairs)
    {
        scale_x.styleClasses.push_back("scale-x-" + variant.first);
        scale_y.styleClasses.push_back("scale-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string scale_x_regex = tailwind_config_->no_start_characters + "scale-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scale_y_regex = tailwind_config_->no_start_characters + "scale-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    scale_x.regex = boost::regex(scale_x_regex);
    scale_y.regex = boost::regex(scale_y_regex);
}

void TTransforms::setTranslateProprieties(tinyxml2::XMLElement *prop_node)
{
    translate_x.setPropriety(prop_node);
    translate_y = translate_x;

    translate_x.class_name = "translate-x";
    translate_y.class_name = "translate-y";

    translate_x.reset_command = "translate-x-res";
    translate_y.reset_command = "translate-y-res";

    translate_x.styleClasses.clear();
    translate_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : translate_x.variant_value_pairs)
    {
        translate_x.styleClasses.push_back("translate-x-" + variant.first);
        translate_y.styleClasses.push_back("translate-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string translate_x_regex = tailwind_config_->no_start_characters + "translate-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string translate_y_regex = tailwind_config_->no_start_characters + "translate-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    translate_x.regex = boost::regex(translate_x_regex);
    translate_y.regex = boost::regex(translate_y_regex);
}

void TTransforms::setSkewProprieties(tinyxml2::XMLElement *prop_node)
{
    skew_x.setPropriety(prop_node);
    skew_y = skew_x;

    skew_x.class_name = "skew-x";
    skew_y.class_name = "skew-y";

    skew_x.reset_command = "skew-x-res";
    skew_y.reset_command = "skew-y-res";

    skew_x.styleClasses.clear();
    skew_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : skew_x.variant_value_pairs)
    {
        skew_x.styleClasses.push_back("skew-x-" + variant.first);
        skew_y.styleClasses.push_back("skew-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string skew_x_regex = tailwind_config_->no_start_characters + "skew-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string skew_y_regex = tailwind_config_->no_start_characters + "skew-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    skew_x.regex = boost::regex(skew_x_regex);
    skew_y.regex = boost::regex(skew_y_regex);
}

void TInteractivity::setScrollMargin(tinyxml2::XMLElement *prop_node)
{
    scrollMargin.setPropriety(prop_node);
    scrollMargin_x = scrollMargin;
    scrollMargin_y = scrollMargin;
    scrollMargin_s = scrollMargin;
    scrollMargin_e = scrollMargin;
    scrollMargin_t = scrollMargin;
    scrollMargin_b = scrollMargin;
    scrollMargin_r = scrollMargin;
    scrollMargin_l = scrollMargin;

    scrollMargin_x.class_name = "scroll-mx";
    scrollMargin_y.class_name = "scroll-my";
    scrollMargin_s.class_name = "scroll-ms";
    scrollMargin_e.class_name = "scroll-me";
    scrollMargin_t.class_name = "scroll-mt";
    scrollMargin_b.class_name = "scroll-mb";
    scrollMargin_r.class_name = "scroll-mr";
    scrollMargin_l.class_name = "scroll-ml";

    scrollMargin_x.reset_command = "scroll-mx-res";
    scrollMargin_y.reset_command = "scroll-my-res";
    scrollMargin_s.reset_command = "scroll-ms-res";
    scrollMargin_e.reset_command = "scroll-me-res";
    scrollMargin_t.reset_command = "scroll-mt-res";
    scrollMargin_b.reset_command = "scroll-mb-res";
    scrollMargin_r.reset_command = "scroll-mr-res";
    scrollMargin_l.reset_command = "scroll-ml-res";

    scrollMargin_x.styleClasses.clear();
    scrollMargin_y.styleClasses.clear();
    scrollMargin_s.styleClasses.clear();
    scrollMargin_e.styleClasses.clear();
    scrollMargin_t.styleClasses.clear();
    scrollMargin_b.styleClasses.clear();
    scrollMargin_r.styleClasses.clear();
    scrollMargin_l.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : scrollMargin.variant_value_pairs)
    {
        scrollMargin_x.styleClasses.push_back("scroll-mx-" + variant.first);
        scrollMargin_y.styleClasses.push_back("scroll-my-" + variant.first);
        scrollMargin_s.styleClasses.push_back("scroll-ms-" + variant.first);
        scrollMargin_e.styleClasses.push_back("scroll-me-" + variant.first);
        scrollMargin_t.styleClasses.push_back("scroll-mt-" + variant.first);
        scrollMargin_b.styleClasses.push_back("scroll-mb-" + variant.first);
        scrollMargin_r.styleClasses.push_back("scroll-mr-" + variant.first);
        scrollMargin_l.styleClasses.push_back("scroll-ml-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string scroll_margin_x_regex = tailwind_config_->no_start_characters + "scroll-mx-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_y_regex = tailwind_config_->no_start_characters + "scroll-my-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_s_regex = tailwind_config_->no_start_characters + "scroll-ms-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_e_regex = tailwind_config_->no_start_characters + "scroll-me-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_t_regex = tailwind_config_->no_start_characters + "scroll-mt-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_b_regex = tailwind_config_->no_start_characters + "scroll-mb-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_r_regex = tailwind_config_->no_start_characters + "scroll-mr-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_margin_l_regex = tailwind_config_->no_start_characters + "scroll-ml-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    scrollMargin_x.regex = boost::regex(scroll_margin_x_regex);
    scrollMargin_y.regex = boost::regex(scroll_margin_y_regex);
    scrollMargin_s.regex = boost::regex(scroll_margin_s_regex);
    scrollMargin_e.regex = boost::regex(scroll_margin_e_regex);
    scrollMargin_t.regex = boost::regex(scroll_margin_t_regex);
    scrollMargin_b.regex = boost::regex(scroll_margin_b_regex);
    scrollMargin_r.regex = boost::regex(scroll_margin_r_regex);
    scrollMargin_l.regex = boost::regex(scroll_margin_l_regex);
}

void TInteractivity::setScrollPadding(tinyxml2::XMLElement *prop_node)
{
    scrollPadding.setPropriety(prop_node);
    scrollPadding_x = scrollPadding;
    scrollPadding_y = scrollPadding;
    scrollPadding_s = scrollPadding;
    scrollPadding_e = scrollPadding;
    scrollPadding_t = scrollPadding;
    scrollPadding_b = scrollPadding;
    scrollPadding_r = scrollPadding;
    scrollPadding_l = scrollPadding;

    scrollPadding_x.class_name = "scroll-px";
    scrollPadding_y.class_name = "scroll-py";
    scrollPadding_s.class_name = "scroll-ps";
    scrollPadding_e.class_name = "scroll-pe";
    scrollPadding_t.class_name = "scroll-pt";
    scrollPadding_b.class_name = "scroll-pb";
    scrollPadding_r.class_name = "scroll-pr";
    scrollPadding_l.class_name = "scroll-pl";

    scrollPadding_x.reset_command = "scroll-px-res";
    scrollPadding_y.reset_command = "scroll-py-res";
    scrollPadding_s.reset_command = "scroll-ps-res";
    scrollPadding_e.reset_command = "scroll-pe-res";
    scrollPadding_t.reset_command = "scroll-pt-res";
    scrollPadding_b.reset_command = "scroll-pb-res";
    scrollPadding_r.reset_command = "scroll-pr-res";
    scrollPadding_l.reset_command = "scroll-pl-res";

    scrollPadding_x.styleClasses.clear();
    scrollPadding_y.styleClasses.clear();
    scrollPadding_s.styleClasses.clear();
    scrollPadding_e.styleClasses.clear();
    scrollPadding_t.styleClasses.clear();
    scrollPadding_b.styleClasses.clear();
    scrollPadding_r.styleClasses.clear();
    scrollPadding_l.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : scrollPadding_x.variant_value_pairs)
    {
        scrollPadding_x.styleClasses.push_back("scroll-px-" + variant.first);
        scrollPadding_y.styleClasses.push_back("scroll-py-" + variant.first);
        scrollPadding_s.styleClasses.push_back("scroll-ps-" + variant.first);
        scrollPadding_e.styleClasses.push_back("scroll-pe-" + variant.first);
        scrollPadding_t.styleClasses.push_back("scroll-pt-" + variant.first);
        scrollPadding_b.styleClasses.push_back("scroll-pb-" + variant.first);
        scrollPadding_r.styleClasses.push_back("scroll-pr-" + variant.first);
        scrollPadding_l.styleClasses.push_back("scroll-pl-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string scroll_padding_x_regex = tailwind_config_->no_start_characters + "scroll-px-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_y_regex = tailwind_config_->no_start_characters + "scroll-py-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_s_regex = tailwind_config_->no_start_characters + "scroll-ps-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_e_regex = tailwind_config_->no_start_characters + "scroll-pe-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_t_regex = tailwind_config_->no_start_characters + "scroll-pt-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_b_regex = tailwind_config_->no_start_characters + "scroll-pb-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_r_regex = tailwind_config_->no_start_characters + "scroll-pr-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string scroll_padding_l_regex = tailwind_config_->no_start_characters + "scroll-pl-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    scrollPadding_x.regex = boost::regex(scroll_padding_x_regex);
    scrollPadding_y.regex = boost::regex(scroll_padding_y_regex);
    scrollPadding_s.regex = boost::regex(scroll_padding_s_regex);
    scrollPadding_e.regex = boost::regex(scroll_padding_e_regex);
    scrollPadding_t.regex = boost::regex(scroll_padding_t_regex);
    scrollPadding_b.regex = boost::regex(scroll_padding_b_regex);
    scrollPadding_r.regex = boost::regex(scroll_padding_r_regex);
    scrollPadding_l.regex = boost::regex(scroll_padding_l_regex);
}

void TLayout::setOverflowProprieties(tinyxml2::XMLElement *prop_node)
{
    overflow.setPropriety(prop_node);
    overflow_x = overflow;
    overflow_y = overflow;

    overflow_x.class_name = "overflow-x";
    overflow_y.class_name = "overflow-y";

    overflow_x.reset_command = "overflow-x-res";
    overflow_y.reset_command = "overflow-y-res";

    overflow_x.styleClasses.clear();
    overflow_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : overflow.variant_value_pairs)
    {
        overflow_x.styleClasses.push_back("overflow-x-" + variant.first);
        overflow_y.styleClasses.push_back("overflow-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string overflow_x_regex = tailwind_config_->no_start_characters + "overflow-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string overflow_y_regex = tailwind_config_->no_start_characters + "overflow-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    overflow_x.regex = boost::regex(overflow_x_regex);
    overflow_y.regex = boost::regex(overflow_y_regex);
}

void TLayout::setOverscrollBehaviorProprieties(tinyxml2::XMLElement *prop_node)
{
    overscrollBehavior.setPropriety(prop_node);
    overscrollBehavior_x = overscrollBehavior;
    overscrollBehavior_y = overscrollBehavior;

    overscrollBehavior_x.class_name = "overscroll-x";
    overscrollBehavior_y.class_name = "overscroll-y";

    overscrollBehavior_x.reset_command = "overscroll-x-res";
    overscrollBehavior_y.reset_command = "overscroll-y-res";

    overscrollBehavior_x.styleClasses.clear();
    overscrollBehavior_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : overscrollBehavior.variant_value_pairs)
    {
        overscrollBehavior_x.styleClasses.push_back("overscroll-x-" + variant.first);
        overscrollBehavior_y.styleClasses.push_back("overscroll-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string overscroll_behavior_x_regex = tailwind_config_->no_start_characters + "overscroll-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string overscroll_behavior_y_regex = tailwind_config_->no_start_characters + "overscroll-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    overscrollBehavior_x.regex = boost::regex(overscroll_behavior_x_regex);
    overscrollBehavior_y.regex = boost::regex(overscroll_behavior_y_regex);
}

void TLayout::setInsetProprieties(tinyxml2::XMLElement *prop_node)
{
    inset.setPropriety(prop_node);
    inset_x = inset;
    inset_y = inset;
    top = inset;
    bottom = inset;
    left = inset;
    right = inset;

    inset_x.class_name = "inset-x";
    inset_y.class_name = "inset-y";
    top.class_name = "top";
    bottom.class_name = "bottom";
    left.class_name = "left";
    right.class_name = "right";

    inset_x.reset_command = "inset-x-res";
    inset_y.reset_command = "inset-y-res";
    top.reset_command = "top-res";
    bottom.reset_command = "bottom-res";
    left.reset_command = "left-res";
    right.reset_command = "right-res";

    inset_x.styleClasses.clear();
    inset_y.styleClasses.clear();
    top.styleClasses.clear();
    bottom.styleClasses.clear();
    left.styleClasses.clear();
    right.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : inset.variant_value_pairs)
    {
        inset_x.styleClasses.push_back("inset-x-" + variant.first);
        inset_y.styleClasses.push_back("inset-y-" + variant.first);
        top.styleClasses.push_back("top-" + variant.first);
        bottom.styleClasses.push_back("bottom-" + variant.first);
        left.styleClasses.push_back("left-" + variant.first);
        right.styleClasses.push_back("right-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string inset_x_regex = tailwind_config_->no_start_characters + "inset-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string inset_y_regex = tailwind_config_->no_start_characters + "inset-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string top_regex = tailwind_config_->no_start_characters + "top-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string bottom_regex = tailwind_config_->no_start_characters + "bottom-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string left_regex = tailwind_config_->no_start_characters + "left-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string right_regex = tailwind_config_->no_start_characters + "right-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    inset_x.regex = boost::regex(inset_x_regex);
    inset_y.regex = boost::regex(inset_y_regex);
    top.regex = boost::regex(top_regex);
    bottom.regex = boost::regex(bottom_regex);
    left.regex = boost::regex(left_regex);
    right.regex = boost::regex(right_regex);
}

void TSpacing::setMarginProprieties(tinyxml2::XMLElement *prop_node)
{
    margin.setPropriety(prop_node);
    margin_x = margin;
    margin_y = margin;
    margin_s = margin;
    margin_e = margin;
    margin_t = margin;
    margin_b = margin;
    margin_r = margin;
    margin_l = margin;

    margin_x.class_name = "mx";
    margin_y.class_name = "my";
    margin_s.class_name = "ms";
    margin_e.class_name = "me";
    margin_t.class_name = "mt";
    margin_b.class_name = "mb";
    margin_r.class_name = "mr";
    margin_l.class_name = "ml";

    margin_x.reset_command = "mx-res";
    margin_y.reset_command = "my-res";
    margin_s.reset_command = "ms-res";
    margin_e.reset_command = "me-res";
    margin_t.reset_command = "mt-res";
    margin_b.reset_command = "mb-res";
    margin_r.reset_command = "mr-res";
    margin_l.reset_command = "ml-res";

    margin_x.styleClasses.clear();
    margin_y.styleClasses.clear();
    margin_s.styleClasses.clear();
    margin_e.styleClasses.clear();
    margin_t.styleClasses.clear();
    margin_b.styleClasses.clear();
    margin_r.styleClasses.clear();
    margin_l.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : margin.variant_value_pairs)
    {
        margin_x.styleClasses.push_back("mx-" + variant.first);
        margin_y.styleClasses.push_back("my-" + variant.first);
        margin_s.styleClasses.push_back("ms-" + variant.first);
        margin_e.styleClasses.push_back("me-" + variant.first);
        margin_t.styleClasses.push_back("mt-" + variant.first);
        margin_b.styleClasses.push_back("mb-" + variant.first);
        margin_r.styleClasses.push_back("mr-" + variant.first);
        margin_l.styleClasses.push_back("ml-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string margin_x_regex = tailwind_config_->no_start_characters + "mx-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_y_regex = tailwind_config_->no_start_characters + "my-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_s_regex = tailwind_config_->no_start_characters + "ms-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_e_regex = tailwind_config_->no_start_characters + "me-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_t_regex = tailwind_config_->no_start_characters + "mt-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_b_regex = tailwind_config_->no_start_characters + "mb-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_r_regex = tailwind_config_->no_start_characters + "mr-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string margin_l_regex = tailwind_config_->no_start_characters + "ml-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    margin_x.regex = boost::regex(margin_x_regex);
    margin_y.regex = boost::regex(margin_y_regex);
    margin_s.regex = boost::regex(margin_s_regex);
    margin_e.regex = boost::regex(margin_e_regex);
    margin_t.regex = boost::regex(margin_t_regex);
    margin_b.regex = boost::regex(margin_b_regex);
    margin_r.regex = boost::regex(margin_r_regex);
    margin_l.regex = boost::regex(margin_l_regex);
}

void TSpacing::setPaddingProprieties(tinyxml2::XMLElement *prop_node)
{
    padding.setPropriety(prop_node);
    padding_x = padding;
    padding_y = padding;
    padding_s = padding;
    padding_e = padding;
    padding_t = padding;
    padding_b = padding;
    padding_r = padding;
    padding_l = padding;

    padding_x.class_name = "px";
    padding_y.class_name = "py";
    padding_s.class_name = "ps";
    padding_e.class_name = "pe";
    padding_t.class_name = "pt";
    padding_b.class_name = "pb";
    padding_r.class_name = "pr";
    padding_l.class_name = "pl";

    padding_x.reset_command = "px-res";
    padding_y.reset_command = "py-res";
    padding_s.reset_command = "ps-res";
    padding_e.reset_command = "pe-res";
    padding_t.reset_command = "pt-res";
    padding_b.reset_command = "pb-res";
    padding_r.reset_command = "pr-res";
    padding_l.reset_command = "pl-res";

    padding_x.styleClasses.clear();
    padding_y.styleClasses.clear();
    padding_s.styleClasses.clear();
    padding_e.styleClasses.clear();
    padding_t.styleClasses.clear();
    padding_b.styleClasses.clear();
    padding_r.styleClasses.clear();
    padding_l.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : padding.variant_value_pairs)
    {
        padding_x.styleClasses.push_back("px-" + variant.first);
        padding_y.styleClasses.push_back("py-" + variant.first);
        padding_s.styleClasses.push_back("ps-" + variant.first);
        padding_e.styleClasses.push_back("pe-" + variant.first);
        padding_t.styleClasses.push_back("pt-" + variant.first);
        padding_b.styleClasses.push_back("pb-" + variant.first);
        padding_r.styleClasses.push_back("pr-" + variant.first);
        padding_l.styleClasses.push_back("pl-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string padding_x_regex = tailwind_config_->no_start_characters + "px-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_y_regex = tailwind_config_->no_start_characters + "py-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_s_regex = tailwind_config_->no_start_characters + "ps-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_e_regex = tailwind_config_->no_start_characters + "pe-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_t_regex = tailwind_config_->no_start_characters + "pt-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_b_regex = tailwind_config_->no_start_characters + "pb-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_r_regex = tailwind_config_->no_start_characters + "pr-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string padding_l_regex = tailwind_config_->no_start_characters + "pl-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    padding_x.regex = boost::regex(padding_x_regex);
    padding_y.regex = boost::regex(padding_y_regex);
    padding_s.regex = boost::regex(padding_s_regex);
    padding_e.regex = boost::regex(padding_e_regex);
    padding_t.regex = boost::regex(padding_t_regex);
    padding_b.regex = boost::regex(padding_b_regex);
    padding_r.regex = boost::regex(padding_r_regex);
    padding_l.regex = boost::regex(padding_l_regex);
}

void TSpacing::setSpaceBetweenProprieties(tinyxml2::XMLElement *prop_node)
{
    spaceBetween_x.setPropriety(prop_node);

    spaceBetween_x.class_name = "space-x";
    spaceBetween_y.class_name = "space-y";

    spaceBetween_x.reset_command = "space-x-res";
    spaceBetween_y.reset_command = "space-y-res";

    spaceBetween_x.styleClasses.clear();
    spaceBetween_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : spaceBetween_x.variant_value_pairs)
    {
        spaceBetween_x.styleClasses.push_back("space-x-" + variant.first);
        spaceBetween_y.styleClasses.push_back("space-y-" + variant.first);
        regex_values += variant.first + "|";
    }

    // regex
    std::string space_between_x_regex = tailwind_config_->no_start_characters + "space-x-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string space_between_y_regex = tailwind_config_->no_start_characters + "space-y-(" + regex_values + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    spaceBetween_x.regex = boost::regex(space_between_x_regex);
    spaceBetween_y.regex = boost::regex(space_between_y_regex);
}

void TBorders::setBorderRadiusProprieties(tinyxml2::XMLElement *prop_node)
{
    borderRadius.setPropriety(prop_node);
    borderRadius_s = borderRadius;
    borderRadius_e = borderRadius;
    borderRadius_t = borderRadius;
    borderRadius_b = borderRadius;
    borderRadius_r = borderRadius;
    borderRadius_l = borderRadius;
    borderRadius_ss = borderRadius;
    borderRadius_se = borderRadius;
    borderRadius_ee = borderRadius;
    borderRadius_es = borderRadius;
    borderRadius_tl = borderRadius;
    borderRadius_tr = borderRadius;
    borderRadius_br = borderRadius;
    borderRadius_bl = borderRadius;

    borderRadius_s.class_name = "rounded-s";
    borderRadius_e.class_name = "rounded-e";
    borderRadius_t.class_name = "rounded-t";
    borderRadius_b.class_name = "rounded-b";
    borderRadius_r.class_name = "rounded-r";
    borderRadius_l.class_name = "rounded-l";
    borderRadius_ss.class_name = "rounded-ss";
    borderRadius_se.class_name = "rounded-se";
    borderRadius_ee.class_name = "rounded-ee";
    borderRadius_es.class_name = "rounded-es";
    borderRadius_tl.class_name = "rounded-tl";
    borderRadius_tr.class_name = "rounded-tr";
    borderRadius_br.class_name = "rounded-br";
    borderRadius_bl.class_name = "rounded-bl";

    borderRadius_s.reset_command = "rounded-s-res";
    borderRadius_e.reset_command = "rounded-e-res";
    borderRadius_t.reset_command = "rounded-t-res";
    borderRadius_b.reset_command = "rounded-b-res";
    borderRadius_r.reset_command = "rounded-r-res";
    borderRadius_l.reset_command = "rounded-l-res";
    borderRadius_ss.reset_command = "rounded-ss-res";
    borderRadius_se.reset_command = "rounded-se-res";
    borderRadius_ee.reset_command = "rounded-ee-res";
    borderRadius_es.reset_command = "rounded-es-res";
    borderRadius_tl.reset_command = "rounded-tl-res";
    borderRadius_tr.reset_command = "rounded-tr-res";
    borderRadius_br.reset_command = "rounded-br-res";
    borderRadius_bl.reset_command = "rounded-bl-res";

    borderRadius_s.styleClasses.clear();
    borderRadius_e.styleClasses.clear();
    borderRadius_t.styleClasses.clear();
    borderRadius_b.styleClasses.clear();
    borderRadius_r.styleClasses.clear();
    borderRadius_l.styleClasses.clear();
    borderRadius_ss.styleClasses.clear();
    borderRadius_se.styleClasses.clear();
    borderRadius_ee.styleClasses.clear();
    borderRadius_es.styleClasses.clear();
    borderRadius_tl.styleClasses.clear();
    borderRadius_tr.styleClasses.clear();
    borderRadius_br.styleClasses.clear();
    borderRadius_bl.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : borderRadius.variant_value_pairs)
    {
        borderRadius_s.styleClasses.push_back("rounded-s-" + variant.first);
        borderRadius_e.styleClasses.push_back("rounded-e-" + variant.first);
        borderRadius_t.styleClasses.push_back("rounded-t-" + variant.first);
        borderRadius_b.styleClasses.push_back("rounded-b-" + variant.first);
        borderRadius_r.styleClasses.push_back("rounded-r-" + variant.first);
        borderRadius_l.styleClasses.push_back("rounded-l-" + variant.first);
        borderRadius_ss.styleClasses.push_back("rounded-ss-" + variant.first);
        borderRadius_se.styleClasses.push_back("rounded-se-" + variant.first);
        borderRadius_ee.styleClasses.push_back("rounded-ee-" + variant.first);
        borderRadius_es.styleClasses.push_back("rounded-es-" + variant.first);
        borderRadius_tl.styleClasses.push_back("rounded-tl-" + variant.first);
        borderRadius_tr.styleClasses.push_back("rounded-tr-" + variant.first);
        borderRadius_br.styleClasses.push_back("rounded-br-" + variant.first);
        borderRadius_bl.styleClasses.push_back("rounded-bl-" + variant.first);
        regex_values += "-" + variant.first + "|";
    }

    // regex
    std::string border_radius_s_regex = tailwind_config_->no_start_characters + "rounded-s(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_e_regex = tailwind_config_->no_start_characters + "rounded-e(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_t_regex = tailwind_config_->no_start_characters + "rounded-t(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_b_regex = tailwind_config_->no_start_characters + "rounded-b(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_r_regex = tailwind_config_->no_start_characters + "rounded-r(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_l_regex = tailwind_config_->no_start_characters + "rounded-l(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_ss_regex = tailwind_config_->no_start_characters + "rounded-ss(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_se_regex = tailwind_config_->no_start_characters + "rounded-se(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_ee_regex = tailwind_config_->no_start_characters + "rounded-ee(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_es_regex = tailwind_config_->no_start_characters + "rounded-es(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_tl_regex = tailwind_config_->no_start_characters + "rounded-tl(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_tr_regex = tailwind_config_->no_start_characters + "rounded-tr(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_br_regex = tailwind_config_->no_start_characters + "rounded-br(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_radius_bl_regex = tailwind_config_->no_start_characters + "rounded-bl(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    borderRadius_s.regex = boost::regex(border_radius_s_regex);
    borderRadius_e.regex = boost::regex(border_radius_e_regex);
    borderRadius_t.regex = boost::regex(border_radius_t_regex);
    borderRadius_b.regex = boost::regex(border_radius_b_regex);
    borderRadius_r.regex = boost::regex(border_radius_r_regex);
    borderRadius_l.regex = boost::regex(border_radius_l_regex);
    borderRadius_ss.regex = boost::regex(border_radius_ss_regex);
    borderRadius_se.regex = boost::regex(border_radius_se_regex);
    borderRadius_ee.regex = boost::regex(border_radius_ee_regex);
    borderRadius_es.regex = boost::regex(border_radius_es_regex);
    borderRadius_tl.regex = boost::regex(border_radius_tl_regex);
    borderRadius_tr.regex = boost::regex(border_radius_tr_regex);
    borderRadius_br.regex = boost::regex(border_radius_br_regex);
    borderRadius_bl.regex = boost::regex(border_radius_bl_regex);
}

void TBorders::setBorderWidthProprieties(tinyxml2::XMLElement *prop_node)
{
    borderWidth.setPropriety(prop_node);
    borderWidth_x = borderWidth;
    borderWidth_y = borderWidth;
    borderWidth_s = borderWidth;
    borderWidth_e = borderWidth;
    borderWidth_t = borderWidth;
    borderWidth_b = borderWidth;
    borderWidth_r = borderWidth;
    borderWidth_l = borderWidth;

    borderWidth_x.class_name = "border-x";
    borderWidth_y.class_name = "border-y";
    borderWidth_s.class_name = "border-s";
    borderWidth_e.class_name = "border-e";
    borderWidth_t.class_name = "border-t";
    borderWidth_b.class_name = "border-b";
    borderWidth_r.class_name = "border-r";
    borderWidth_l.class_name = "border-l";

    borderWidth_x.reset_command = "border-x-res";
    borderWidth_y.reset_command = "border-y-res";
    borderWidth_s.reset_command = "border-s-res";
    borderWidth_e.reset_command = "border-e-res";
    borderWidth_t.reset_command = "border-t-res";
    borderWidth_b.reset_command = "border-b-res";
    borderWidth_r.reset_command = "border-r-res";
    borderWidth_l.reset_command = "border-l-res";

    borderWidth_x.styleClasses.clear();
    borderWidth_y.styleClasses.clear();
    borderWidth_s.styleClasses.clear();
    borderWidth_e.styleClasses.clear();
    borderWidth_t.styleClasses.clear();
    borderWidth_b.styleClasses.clear();
    borderWidth_r.styleClasses.clear();
    borderWidth_l.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : borderWidth.variant_value_pairs)
    {
        borderWidth_x.styleClasses.push_back("border-x-" + variant.first);
        borderWidth_y.styleClasses.push_back("border-y-" + variant.first);
        borderWidth_s.styleClasses.push_back("border-s-" + variant.first);
        borderWidth_e.styleClasses.push_back("border-e-" + variant.first);
        borderWidth_t.styleClasses.push_back("border-t-" + variant.first);
        borderWidth_b.styleClasses.push_back("border-b-" + variant.first);
        borderWidth_r.styleClasses.push_back("border-r-" + variant.first);
        borderWidth_l.styleClasses.push_back("border-l-" + variant.first);
        regex_values += "-" + variant.first + "|";
    }

    // regex
    std::string border_width_x_regex = tailwind_config_->no_start_characters + "border-x(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_y_regex = tailwind_config_->no_start_characters + "border-y(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_s_regex = tailwind_config_->no_start_characters + "border-s(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_e_regex = tailwind_config_->no_start_characters + "border-e(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_t_regex = tailwind_config_->no_start_characters + "border-t(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_b_regex = tailwind_config_->no_start_characters + "border-b(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_r_regex = tailwind_config_->no_start_characters + "border-r(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string border_width_l_regex = tailwind_config_->no_start_characters + "border-l(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    borderWidth_x.regex = boost::regex(border_width_x_regex);
    borderWidth_y.regex = boost::regex(border_width_y_regex);
    borderWidth_s.regex = boost::regex(border_width_s_regex);
    borderWidth_e.regex = boost::regex(border_width_e_regex);
    borderWidth_t.regex = boost::regex(border_width_t_regex);
    borderWidth_b.regex = boost::regex(border_width_b_regex);
    borderWidth_r.regex = boost::regex(border_width_r_regex);
    borderWidth_l.regex = boost::regex(border_width_l_regex);
}

void TBorders::setDivideWidthProprieties(tinyxml2::XMLElement *prop_node)
{
    divideWidth_x.setPropriety(prop_node);
    divideWidth_y = divideWidth_x;

    divideWidth_x.class_name = "divide-x";
    divideWidth_y.class_name = "divide-y";

    divideWidth_x.reset_command = "divide-x-res";
    divideWidth_y.reset_command = "divide-y-res";

    divideWidth_x.styleClasses.clear();
    divideWidth_y.styleClasses.clear();

    std::string regex_values = "";
    for (auto variant : divideWidth_x.variant_value_pairs)
    {
        divideWidth_x.styleClasses.push_back("divide-x-" + variant.first);
        divideWidth_y.styleClasses.push_back("divide-y-" + variant.first);
        regex_values += "-" + variant.first + "|";
    }

    // regex
    std::string divide_width_x_regex = tailwind_config_->no_start_characters + "divide-x(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;
    std::string divide_width_y_regex = tailwind_config_->no_start_characters + "divide-y(" + regex_values + "-" + tailwind_config_->custom_value_regex + ")" + tailwind_config_->no_end_characters;

    divideWidth_x.regex = boost::regex(divide_width_x_regex);
    divideWidth_y.regex = boost::regex(divide_width_y_regex);
}
