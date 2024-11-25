#include "101-Stylus/TCategory/TypographyP.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

TypographyP::TypographyP(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper)
    : BasePanel(tailwind_config, extra_widgets_wrapper)
{

    classes_data_map_ = {
        {"font_family", "none"},
        {"font_size", "none"},
        {"font_smoothing", "none"},
        {"font_style", "none"},
        {"font_weight", "none"},
        {"font_variant_numeric", "none"},
        {"letter_spacing", "none"},
        {"line_clamp", "none"},
        {"line_height", "none"},
        {"list_style_image", "none"},
        {"list_style_position", "none"},
        {"list_style_type", "none"},
        {"text_align", "none"},
        {"text_color", "none"},
        {"text_decoration", "none"},
        {"text_decoration_color", "none"},
        {"text_decoration_style", "none"},
        {"text_decoration_thickness", "none"},
        {"text_underline_offset", "none"},
        {"text_transform", "none"},
        {"text_overflow", "none"},
        {"text_wrap", "none"},
        {"text_indent", "none"},
        {"vertical_align", "none"},
        {"whitespace", "none"},
        {"word_break", "none"},
        {"hyphens", "none"},
        {"content", "none"}};

    std::map<std::string, Propriety> classes_vec_map = {
        {"font_family", tailwind_config->typography.fontFamily},
        {"font_size", tailwind_config->typography.fontSize},
        {"font_smoothing", tailwind_config->typography.fontSmoothing},
        {"font_style", tailwind_config->typography.fontStyle},
        {"font_weight", tailwind_config->typography.fontWeight},
        {"font_variant_numeric", tailwind_config->typography.fontVariantNumeric},
        {"letter_spacing", tailwind_config->typography.letterSpacing},
        {"line_clamp", tailwind_config->typography.lineClamp},
        {"line_height", tailwind_config->typography.lineHeight},
        {"list_style_image", tailwind_config->typography.listStyleImage},
        {"list_style_position", tailwind_config->typography.listStylePosition},
        {"list_style_type", tailwind_config->typography.listStyleType},
        {"text_align", tailwind_config->typography.textAlign},
        {"text_color", tailwind_config->typography.textColor},
        {"text_decoration", tailwind_config->typography.textDecoration},
        {"text_decoration_color", tailwind_config->typography.textDecorationColor},
        {"text_decoration_style", tailwind_config->typography.textDecorationStyle},
        {"text_decoration_thickness", tailwind_config->typography.textDecorationThickness},
        {"text_underline_offset", tailwind_config->typography.textUnderlineOffset},
        {"text_transform", tailwind_config->typography.textTransform},
        {"text_overflow", tailwind_config->typography.textOverflow},
        {"text_wrap", tailwind_config->typography.textWrap},
        {"text_indent", tailwind_config->typography.textIndent},
        {"vertical_align", tailwind_config->typography.verticalAlign},
        {"whitespace", tailwind_config->typography.whitespace},
        {"word_break", tailwind_config->typography.wordBreak},
        {"hyphens", tailwind_config->typography.hyphens},
        {"content", tailwind_config->typography.content}};

    title->setText("Typography");

    m_main_toggler_ = addToggler(centralWidget, "|");
    centralWidget->hide();

    auto font_family_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto font_size_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto font_smoothing_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto font_style_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto font_weight_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto font_variant_numeric_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto letter_spacing_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto line_clamp_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto line_height_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto list_style_image_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto list_style_position_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto list_style_type_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_align_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_decoration_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_decoration_color_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_decoration_style_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_opacity_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_decoration_thickness_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_underline_offset_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_transform_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_overflow_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_wrap_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto text_indent_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto vertical_align_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto whitespace_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto word_break_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto hyphens_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto content_wrapper = centralWidget->addWidget(std::make_unique<Wt::WContainerWidget>());

    // links to docs
    font_family_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_family"].docs_link, "Family")));
    font_size_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_size"].docs_link, "Size")));
    font_smoothing_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_smoothing"].docs_link, "Smoothing")));
    font_style_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_style"].docs_link, "Style")));
    font_weight_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_weight"].docs_link, "Weight")));
    font_variant_numeric_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["font_variant_numeric"].docs_link, "Variant Numeric")));
    letter_spacing_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["letter_spacing"].docs_link, "Letter Spacing")));
    line_clamp_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["line_clamp"].docs_link, "Line Clamp")));
    line_height_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["line_height"].docs_link, "Line Height")));
    list_style_image_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["list_style_image"].docs_link, "List Style Image")));
    list_style_position_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["list_style_position"].docs_link, "List Style Position")));
    list_style_type_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["list_style_type"].docs_link, "List Style Yype")));
    text_align_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_align"].docs_link, "Align")));
    text_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_color"].docs_link, "Color")));
    text_decoration_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_decoration"].docs_link, "Decor")));
    text_decoration_color_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_decoration_color"].docs_link, "Decor Color")));
    text_decoration_style_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_decoration_style"].docs_link, "Decor Style")));
    text_decoration_thickness_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_decoration_thickness"].docs_link, "Decor Thickness")));
    text_underline_offset_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_underline_offset"].docs_link, "Underline Offset")));
    text_transform_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_transform"].docs_link, "Transform")));
    text_overflow_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_overflow"].docs_link, "Overflow")));
    text_wrap_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_wrap"].docs_link, "Wrap")));
    text_indent_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["text_indent"].docs_link, "Indent")));
    vertical_align_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["vertical_align"].docs_link, "Vertical Align")));
    whitespace_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["whitespace"].docs_link, "Whitespace")));
    word_break_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["word_break"].docs_link, "Word Break")));
    hyphens_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["hyphens"].docs_link, "Hyphens")));
    content_wrapper->addWidget(std::move(createAnchorToDocs(classes_vec_map["content"].docs_link, "Content")));

    font_family_wrapper->setStyleClass(wrapper_classes);
    font_size_wrapper->setStyleClass(wrapper_classes);
    font_smoothing_wrapper->setStyleClass(wrapper_classes);
    font_style_wrapper->setStyleClass(wrapper_classes);
    font_weight_wrapper->setStyleClass(wrapper_classes);
    font_variant_numeric_wrapper->setStyleClass(wrapper_classes);
    letter_spacing_wrapper->setStyleClass(wrapper_classes);
    line_clamp_wrapper->setStyleClass(wrapper_classes);
    line_height_wrapper->setStyleClass(wrapper_classes);
    list_style_image_wrapper->setStyleClass(wrapper_classes);
    list_style_position_wrapper->setStyleClass(wrapper_classes);
    list_style_type_wrapper->setStyleClass(wrapper_classes);
    text_align_wrapper->setStyleClass(wrapper_classes);
    text_color_wrapper->setStyleClass(wrapper_classes);
    text_decoration_wrapper->setStyleClass(wrapper_classes);
    text_decoration_color_wrapper->setStyleClass(wrapper_classes);
    text_decoration_style_wrapper->setStyleClass(wrapper_classes);
    text_decoration_style_wrapper->setStyleClass(wrapper_classes);
    text_decoration_thickness_wrapper->setStyleClass(wrapper_classes);
    text_underline_offset_wrapper->setStyleClass(wrapper_classes);
    text_transform_wrapper->setStyleClass(wrapper_classes);
    text_overflow_wrapper->setStyleClass(wrapper_classes);
    text_wrap_wrapper->setStyleClass(wrapper_classes);
    text_indent_wrapper->setStyleClass(wrapper_classes);
    vertical_align_wrapper->setStyleClass(wrapper_classes);
    whitespace_wrapper->setStyleClass(wrapper_classes);
    word_break_wrapper->setStyleClass(wrapper_classes);
    hyphens_wrapper->setStyleClass(wrapper_classes);
    content_wrapper->setStyleClass(wrapper_classes);

    combobox_map_["font_family"] = font_family_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_family"].getClasses()));
    combobox_map_["font_size"] = font_size_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_size"].getClasses()));
    combobox_map_["font_smoothing"] = font_smoothing_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_smoothing"].getClasses()));
    combobox_map_["font_style"] = font_style_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_style"].getClasses()));
    combobox_map_["font_weight"] = font_weight_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_weight"].getClasses()));
    combobox_map_["font_variant_numeric"] = font_variant_numeric_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["font_variant_numeric"].getClasses()));
    combobox_map_["letter_spacing"] = letter_spacing_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["letter_spacing"].getClasses()));
    combobox_map_["line_clamp"] = line_clamp_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["line_clamp"].getClasses()));
    combobox_map_["line_height"] = line_height_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["line_height"].getClasses()));
    combobox_map_["list_style_image"] = list_style_image_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["list_style_image"].getClasses()));
    combobox_map_["list_style_position"] = list_style_position_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["list_style_position"].getClasses()));
    combobox_map_["list_style_type"] = list_style_type_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["list_style_type"].getClasses()));
    combobox_map_["text_align"] = text_align_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_align"].getClasses()));
    colors_map_["text_color"] = text_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["text_color"]));
    combobox_map_["text_decoration"] = text_decoration_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_decoration"].getClasses()));
    colors_map_["text_decoration_color"] = text_decoration_color_wrapper->addWidget(std::make_unique<ColorsWidget>(classes_vec_map["text_decoration_color"]));
    combobox_map_["text_decoration_style"] = text_decoration_style_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_decoration_style"].getClasses()));
    combobox_map_["text_decoration_thickness"] = text_decoration_thickness_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_decoration_thickness"].getClasses()));
    combobox_map_["text_underline_offset"] = text_underline_offset_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_underline_offset"].getClasses()));
    combobox_map_["text_transform"] = text_transform_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_transform"].getClasses()));
    combobox_map_["text_overflow"] = text_overflow_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_overflow"].getClasses()));
    combobox_map_["text_wrap"] = text_wrap_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_wrap"].getClasses()));
    combobox_map_["text_indent"] = text_indent_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["text_indent"].getClasses()));
    combobox_map_["vertical_align"] = vertical_align_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["vertical_align"].getClasses()));
    combobox_map_["whitespace"] = whitespace_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["whitespace"].getClasses()));
    combobox_map_["word_break"] = word_break_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["word_break"].getClasses()));
    combobox_map_["hyphens"] = hyphens_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["hyphens"].getClasses()));
    combobox_map_["content"] = content_wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(classes_vec_map["content"].getClasses()));

    if (tailwind_config_->typography.fontFamily.custom_value)
        combobox_map_["font_family"]->setCustomValueString(tailwind_config_->typography.fontFamily.class_name + "-");
    if (tailwind_config_->typography.fontSize.custom_value)
        combobox_map_["font_size"]->setCustomValueString(tailwind_config_->typography.fontSize.class_name + "-");
    if (tailwind_config_->typography.fontSmoothing.custom_value)
        combobox_map_["font_smoothing"]->setCustomValueString(tailwind_config_->typography.fontSmoothing.class_name + "-");
    if (tailwind_config_->typography.fontStyle.custom_value)
        combobox_map_["font_style"]->setCustomValueString(tailwind_config_->typography.fontStyle.class_name + "-");
    if (tailwind_config_->typography.fontWeight.custom_value)
        combobox_map_["font_weight"]->setCustomValueString(tailwind_config_->typography.fontWeight.class_name + "-");
    if (tailwind_config_->typography.fontVariantNumeric.custom_value)
        combobox_map_["font_variant_numeric"]->setCustomValueString(tailwind_config_->typography.fontVariantNumeric.class_name + "-");
    if (tailwind_config_->typography.letterSpacing.custom_value)
        combobox_map_["letter_spacing"]->setCustomValueString(tailwind_config_->typography.letterSpacing.class_name + "-");
    if (tailwind_config_->typography.lineClamp.custom_value)
        combobox_map_["line_clamp"]->setCustomValueString(tailwind_config_->typography.lineClamp.class_name + "-");
    if (tailwind_config_->typography.lineHeight.custom_value)
        combobox_map_["line_height"]->setCustomValueString(tailwind_config_->typography.lineHeight.class_name + "-");
    if (tailwind_config_->typography.listStyleImage.custom_value)
        combobox_map_["list_style_image"]->setCustomValueString(tailwind_config_->typography.listStyleImage.class_name + "-");
    if (tailwind_config_->typography.listStylePosition.custom_value)
        combobox_map_["list_style_position"]->setCustomValueString(tailwind_config_->typography.listStylePosition.class_name + "-");
    if (tailwind_config_->typography.listStyleType.custom_value)
        combobox_map_["list_style_type"]->setCustomValueString(tailwind_config_->typography.listStyleType.class_name + "-");
    if (tailwind_config_->typography.textAlign.custom_value)
        combobox_map_["text_align"]->setCustomValueString(tailwind_config_->typography.textAlign.class_name + "-");
    if (tailwind_config_->typography.textColor.custom_value)
        colors_map_["text_color"]->setCustomValueString(tailwind_config_->typography.textColor.class_name + "-");
    if (tailwind_config_->typography.textDecoration.custom_value)
        combobox_map_["text_decoration"]->setCustomValueString(tailwind_config_->typography.textDecoration.class_name + "-");
    if (tailwind_config_->typography.textDecorationColor.custom_value)
        colors_map_["text_decoration_color"]->setCustomValueString(tailwind_config_->typography.textDecorationColor.class_name + "-");
    if (tailwind_config_->typography.textDecorationStyle.custom_value)
        combobox_map_["text_decoration_style"]->setCustomValueString(tailwind_config_->typography.textDecorationStyle.class_name + "-");
    if (tailwind_config_->typography.textDecorationThickness.custom_value)
        combobox_map_["text_decoration_thickness"]->setCustomValueString(tailwind_config_->typography.textDecorationThickness.class_name + "-");
    if (tailwind_config_->typography.textUnderlineOffset.custom_value)
        combobox_map_["text_underline_offset"]->setCustomValueString(tailwind_config_->typography.textUnderlineOffset.class_name + "-");
    if (tailwind_config_->typography.textTransform.custom_value)
        combobox_map_["text_transform"]->setCustomValueString(tailwind_config_->typography.textTransform.class_name + "-");
    if (tailwind_config_->typography.textOverflow.custom_value)
        combobox_map_["text_overflow"]->setCustomValueString(tailwind_config_->typography.textOverflow.class_name + "-");
    if (tailwind_config_->typography.textWrap.custom_value)
        combobox_map_["text_wrap"]->setCustomValueString(tailwind_config_->typography.textWrap.class_name + "-");
    if (tailwind_config_->typography.textIndent.custom_value)
        combobox_map_["text_indent"]->setCustomValueString(tailwind_config_->typography.textIndent.class_name + "-");
    if (tailwind_config_->typography.verticalAlign.custom_value)
        combobox_map_["vertical_align"]->setCustomValueString(tailwind_config_->typography.verticalAlign.class_name + "-");
    if (tailwind_config_->typography.whitespace.custom_value)
        combobox_map_["whitespace"]->setCustomValueString(tailwind_config_->typography.whitespace.class_name + "-");
    if (tailwind_config_->typography.wordBreak.custom_value)
        combobox_map_["word_break"]->setCustomValueString(tailwind_config_->typography.wordBreak.class_name + "-");
    if (tailwind_config_->typography.hyphens.custom_value)
        combobox_map_["hyphens"]->setCustomValueString(tailwind_config_->typography.hyphens.class_name + "-");
    if (tailwind_config_->typography.content.custom_value)
        combobox_map_["content"]->setCustomValueString(tailwind_config_->typography.content.class_name + "-");

    for (auto &[key, combobox] : combobox_map_)
    {
        combobox->classChanged().connect(this, [=](std::string className)
                                         {classes_data_map_[key] = className; styleChanged_.emit(getStyles()); });
        if (classes_vec_map[key].custom_value)
            combobox->setCustomValueString(classes_vec_map[key].class_name + "-");
    }
    for (auto &color : colors_map_)
    {
        color.second->classChanged().connect(this, [=](std::string className)
                                             {classes_data_map_[color.first] = className; styleChanged_.emit(getStyles()); });
    }
    setExtraWidgets(classes_vec_map);
}

void TypographyP::setCustomTestValues()
{
    classes_data_map_["font_family"] = "font-sans";
    classes_data_map_["font_size"] = "text-xs";
    classes_data_map_["font_smoothing"] = "antialiased";
    classes_data_map_["font_style"] = "italic";
    classes_data_map_["font_weight"] = "font-bold";
    classes_data_map_["font_variant_numeric"] = "normal-nums";
    classes_data_map_["letter_spacing"] = "tracking-tight";
    classes_data_map_["line_clamp"] = "line-clamp-3";
    classes_data_map_["line_height"] = "leading-6";
    classes_data_map_["list_style_image"] = "list-image-none";
    classes_data_map_["list_style_position"] = "list-inside";
    classes_data_map_["list_style_type"] = "list-disc";
    classes_data_map_["text_align"] = "text-center";
    classes_data_map_["text_color"] = "text-red-500";
    classes_data_map_["text_decoration"] = "underline";
    classes_data_map_["text_decoration_color"] = "decoration-sky-500/70";
    classes_data_map_["text_decoration_style"] = "decoration-dotted";
    classes_data_map_["text_decoration_thickness"] = "decoration-4";
    classes_data_map_["text_underline_offset"] = "underline-offset-2";
    classes_data_map_["text_transform"] = "uppercase";
    classes_data_map_["text_overflow"] = "truncate";
    classes_data_map_["text_wrap"] = "text-nowrap";
    classes_data_map_["text_indent"] = "indent-4";
    classes_data_map_["vertical_align"] = "align-middle";
    classes_data_map_["whitespace"] = "whitespace-nowrap";
    classes_data_map_["word_break"] = "break-all";
    classes_data_map_["hyphens"] = "hyphens-auto";
    classes_data_map_["content"] = "content-none";
}
