#include "101-Stylus/Tailwind/TailwindConfig.h"
#include "101-Stylus/Stylus.h"

#include <iostream>
#include <fstream>
// #include <jsoncpp/json/json.h>
#include "002-Dbo/Session.h"

TailwindConfig::TailwindConfig(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus),
      svg(this),
      sizing(this),
      typography(this),
      backgrounds(this),
      accesibility(this),
      flexboxAndGrid(this),
      filters(this),
      tables(this),
      transitionsAndAnimation(this),
      transforms(this),
      interactivity(this),
      layout(this),
      spacing(this),
      effects(this),
      borders(this),
      xml_brains_()
{
}

void TailwindConfig::readConfigurationXMLs()
{
    auto transaction = Dbo::Transaction(stylus_->session_);
    auto dbo_folder = stylus_->session_.find<TemplateFolder>().where("folder_name = ?").bind("stylus").resultValue();
    if (!dbo_folder)
    {
        std::cerr << "\n\n No folder found with the name: stylus \n\n";
        return;
    }
    auto dbo_files = dbo_folder->template_files.find().resultList();
    if (dbo_files.size() == 0)
    {
        std::cerr << "\n\n No files found in the folder: stylus \n\n";
        return;
    }
    for (auto dbo_file : dbo_files)
    {
        for (auto xml_template : dbo_file->xml_templates)
        {
            XmlDboRecord dbo_temp_data;
            dbo_temp_data.dbo_temp_id = xml_template.id();
            dbo_temp_data.dbo_file_id = dbo_file.id();
            dbo_temp_data.dbo_folder_id = dbo_folder.id();
            dbo_temp_data.file_name = dbo_file->file_name;
            dbo_temp_data.folder_name = dbo_folder->folder_name;
            dbo_temp_data.temp_id = xml_template->temp_id;
            dbo_temp_data.xml_temp = xml_template->xml_temp;
            auto xml_brain = std::make_shared<XMLBrain>(stylus_->session_, dbo_temp_data, stylus_);
            xml_brains_[xml_brain->dbo_temp_data_.temp_id.toUTF8()] = xml_brain;
        }
    }

    transaction.commit();

    auto colors_node = xml_brains_["colors"]->message_node_;
    if (!colors_node)
    {
        std::cout << "\n\n colors node not found \n\n";
        return;
    }

    auto spacing_node = xml_brains_["spacing"]->message_node_;
    if (!spacing_node)
    {
        std::cout << "\n\n spacings node not found \n\n";
        return;
    }

    auto opacity_node = xml_brains_["opacity"]->message_node_;
    if (!opacity_node)
    {
        std::cout << "\n\n opacity node not found \n\n";
        return;
    }

    auto screens_node = xml_brains_["screens"]->message_node_;
    if (!screens_node)
    {
        std::cout << "\n\n screens node not found \n\n";
        return;
    }

    // std::cout << "\n\n All good you can continue \n\n";
    getColorVariants(colors_node->ToElement());

    variants_and_css["spacing"] = getVariants(spacing_node->FirstChildElement("classes"));
    variants_and_css["opacity"] = getVariants(opacity_node->FirstChildElement("classes"));
    variants_and_css["screens"] = getVariants(screens_node->FirstChildElement("classes"));

    no_start_characters = R"((?<!\S)(!)?)";
    custom_value_regex = R"(\[[\.\S]*\])";
    no_end_characters = R"((?!\w|-))";

    if (variants_and_css["spacing"].size() == 0)
        spacing_regex = "";
    else
    {
        spacing_regex = "(";
        for (auto spacing_variant : variants_and_css["spacing"])
        {
            spacing_regex += spacing_variant.first + "|";
        }
        spacing_regex += custom_value_regex + ")";
    }

    if (variants_and_css["opacity"].size() == 0)
        opacity_regex = "";
    else
    {
        opacity_regex = "(";
        for (auto opacity_variant : variants_and_css["opacity"])
        {
            opacity_regex += opacity_variant.first + "|";
        }
        opacity_regex += custom_value_regex + ")";
    }

    color_custom_value_regex = R"(\[(#|rgb|rgba|hls|hlsa)(.*)\])";
    colors_regex = "";
    if (color_variants.size() == 0)
        colors_regex = "";
    else
    {
        colors_regex = "(";
        for (auto color : color_variants)
        {
            std::string separator = "";
            if (color.first.compare("") != 0)
            {
                separator = "-";
            }
            for (auto color_variant : color.second)
            {
                colors_regex += color.first + separator + color_variant.first + "|";
            }
        }
        colors_regex += color_custom_value_regex + ")";
    }
    colors_regex += "(\\/" + opacity_regex + ")?" + no_end_characters;

    readProprieties();

    // Svg
    {
        svg.fill.setPropriety(xml_brains_["fill"]->message_node_->ToElement());
        svg.stroke.setPropriety(xml_brains_["stroke"]->message_node_->ToElement());
        svg.strokeWidth.setPropriety(xml_brains_["strokeWidth"]->message_node_->ToElement());
    }

    // Sizing
    {
        sizing.width.setPropriety(xml_brains_["width"]->message_node_->ToElement());
        sizing.minWidth.setPropriety(xml_brains_["minWidth"]->message_node_->ToElement());
        sizing.maxWidth.setPropriety(xml_brains_["maxWidth"]->message_node_->ToElement());

        sizing.height.setPropriety(xml_brains_["height"]->message_node_->ToElement());
        sizing.minHeight.setPropriety(xml_brains_["minHeight"]->message_node_->ToElement());
        sizing.maxHeight.setPropriety(xml_brains_["maxHeight"]->message_node_->ToElement());
    }

    // Typography
    {
        typography.fontFamily.setPropriety(xml_brains_["fontFamily"]->message_node_->ToElement());
        typography.fontSize.setPropriety(xml_brains_["fontSize"]->message_node_->ToElement());
        typography.fontSmoothing.setPropriety(xml_brains_["fontSmoothing"]->message_node_->ToElement());
        typography.fontStyle.setPropriety(xml_brains_["fontStyle"]->message_node_->ToElement());
        typography.fontWeight.setPropriety(xml_brains_["fontWeight"]->message_node_->ToElement());
        typography.fontVariantNumeric.setPropriety(xml_brains_["fontVariantNumeric"]->message_node_->ToElement());
        typography.letterSpacing.setPropriety(xml_brains_["letterSpacing"]->message_node_->ToElement());
        typography.lineClamp.setPropriety(xml_brains_["lineClamp"]->message_node_->ToElement());
        typography.lineHeight.setPropriety(xml_brains_["lineHeight"]->message_node_->ToElement());
        typography.listStyleImage.setPropriety(xml_brains_["listStyleImage"]->message_node_->ToElement());
        typography.listStylePosition.setPropriety(xml_brains_["listStylePosition"]->message_node_->ToElement());
        typography.listStyleType.setPropriety(xml_brains_["listStyleType"]->message_node_->ToElement());
        typography.textAlign.setPropriety(xml_brains_["textAlign"]->message_node_->ToElement());
        typography.textColor.setPropriety(xml_brains_["textColor"]->message_node_->ToElement());
        typography.textDecoration.setPropriety(xml_brains_["textDecoration"]->message_node_->ToElement());
        typography.textDecorationColor.setPropriety(xml_brains_["textDecorationColor"]->message_node_->ToElement());
        typography.textDecorationStyle.setPropriety(xml_brains_["textDecorationStyle"]->message_node_->ToElement());
        typography.textDecorationThickness.setPropriety(xml_brains_["textDecorationThickness"]->message_node_->ToElement());
        typography.textUnderlineOffset.setPropriety(xml_brains_["textUnderlineOffset"]->message_node_->ToElement());
        typography.textTransform.setPropriety(xml_brains_["textTransform"]->message_node_->ToElement());
        typography.textOverflow.setPropriety(xml_brains_["textOverflow"]->message_node_->ToElement());
        typography.textWrap.setPropriety(xml_brains_["textWrap"]->message_node_->ToElement());
        typography.textIndent.setPropriety(xml_brains_["textIndent"]->message_node_->ToElement());
        typography.verticalAlign.setPropriety(xml_brains_["verticalAlign"]->message_node_->ToElement());
        typography.whitespace.setPropriety(xml_brains_["whitespace"]->message_node_->ToElement());
        typography.wordBreak.setPropriety(xml_brains_["wordBreak"]->message_node_->ToElement());
        typography.hyphens.setPropriety(xml_brains_["hyphens"]->message_node_->ToElement());
        typography.content.setPropriety(xml_brains_["content"]->message_node_->ToElement());
    }

    // Backgrounds
    {
        backgrounds.backgroundColor.setPropriety(xml_brains_["backgroundColor"]->message_node_->ToElement());
        backgrounds.backgroundImage.setPropriety(xml_brains_["backgroundImage"]->message_node_->ToElement());
        backgrounds.backgroundPosition.setPropriety(xml_brains_["backgroundPosition"]->message_node_->ToElement());
        backgrounds.backgroundSize.setPropriety(xml_brains_["backgroundSize"]->message_node_->ToElement());
        backgrounds.backgroundRepeat.setPropriety(xml_brains_["backgroundRepeat"]->message_node_->ToElement());
        backgrounds.backgroundAttachment.setPropriety(xml_brains_["backgroundAttachment"]->message_node_->ToElement());
        backgrounds.backgroundClip.setPropriety(xml_brains_["backgroundClip"]->message_node_->ToElement());
        backgrounds.backgroundOrigin.setPropriety(xml_brains_["backgroundOrigin"]->message_node_->ToElement());
        backgrounds.setGradientStepAndColorProprieties(xml_brains_["gradientColorStep"]->message_node_->ToElement());
    }

    // Accesibility
    accesibility.screenReaders.setPropriety(xml_brains_["screenReaders"]->message_node_->ToElement());

    // FlexboxAndGrid
    {
        flexboxAndGrid.flexBasis.setPropriety(xml_brains_["flexBasis"]->message_node_->ToElement());
        flexboxAndGrid.flexDirection.setPropriety(xml_brains_["flexDirection"]->message_node_->ToElement());
        flexboxAndGrid.flexWrap.setPropriety(xml_brains_["flexWrap"]->message_node_->ToElement());
        flexboxAndGrid.flex.setPropriety(xml_brains_["flex"]->message_node_->ToElement());
        flexboxAndGrid.flexGrow.setPropriety(xml_brains_["flexGrow"]->message_node_->ToElement());
        flexboxAndGrid.flexShrink.setPropriety(xml_brains_["flexShrink"]->message_node_->ToElement());
        flexboxAndGrid.order.setPropriety(xml_brains_["order"]->message_node_->ToElement());
        flexboxAndGrid.gridTemplateColumns.setPropriety(xml_brains_["gridTemplateColumns"]->message_node_->ToElement());
        flexboxAndGrid.gridColumn_span.setPropriety(xml_brains_["gridColumn"]->message_node_->ToElement());
        flexboxAndGrid.gridColumnStart.setPropriety(xml_brains_["gridColumnStart"]->message_node_->ToElement());
        flexboxAndGrid.gridColumnEnd.setPropriety(xml_brains_["gridColumnEnd"]->message_node_->ToElement());
        flexboxAndGrid.gridTemplateRows.setPropriety(xml_brains_["gridTemplateRows"]->message_node_->ToElement());
        flexboxAndGrid.gridRow_span.setPropriety(xml_brains_["gridRow"]->message_node_->ToElement());
        flexboxAndGrid.gridRowStart.setPropriety(xml_brains_["gridRowStart"]->message_node_->ToElement());
        flexboxAndGrid.gridRowEnd.setPropriety(xml_brains_["gridRowEnd"]->message_node_->ToElement());
        flexboxAndGrid.gridAutoFlow.setPropriety(xml_brains_["gridAutoFlow"]->message_node_->ToElement());
        flexboxAndGrid.gridAutoColumns.setPropriety(xml_brains_["gridAutoColumns"]->message_node_->ToElement());
        flexboxAndGrid.gridAutoRows.setPropriety(xml_brains_["gridAutoRows"]->message_node_->ToElement());
        flexboxAndGrid.justifyContent.setPropriety(xml_brains_["justifyContent"]->message_node_->ToElement());
        flexboxAndGrid.justifyItems.setPropriety(xml_brains_["justifyItems"]->message_node_->ToElement());
        flexboxAndGrid.justifySelf.setPropriety(xml_brains_["justifySelf"]->message_node_->ToElement());
        flexboxAndGrid.alignContent.setPropriety(xml_brains_["alignContent"]->message_node_->ToElement());
        flexboxAndGrid.alignItems.setPropriety(xml_brains_["alignItems"]->message_node_->ToElement());
        flexboxAndGrid.alignSelf.setPropriety(xml_brains_["alignSelf"]->message_node_->ToElement());
        flexboxAndGrid.placeContent.setPropriety(xml_brains_["placeContent"]->message_node_->ToElement());
        flexboxAndGrid.placeItems.setPropriety(xml_brains_["placeItems"]->message_node_->ToElement());
        flexboxAndGrid.placeSelf.setPropriety(xml_brains_["placeSelf"]->message_node_->ToElement());
        flexboxAndGrid.setGapProprieties(xml_brains_["gap"]->message_node_->ToElement());
    }

    // Filters
    {
        filters.blur.setPropriety(xml_brains_["blur"]->message_node_->ToElement());
        filters.brightness.setPropriety(xml_brains_["brightness"]->message_node_->ToElement());
        filters.contrast.setPropriety(xml_brains_["contrast"]->message_node_->ToElement());
        filters.dropShadow.setPropriety(xml_brains_["dropShadow"]->message_node_->ToElement());
        filters.grayscale.setPropriety(xml_brains_["grayscale"]->message_node_->ToElement());
        filters.hueRotate.setPropriety(xml_brains_["hueRotate"]->message_node_->ToElement());
        filters.invert.setPropriety(xml_brains_["invert"]->message_node_->ToElement());
        filters.saturate.setPropriety(xml_brains_["saturate"]->message_node_->ToElement());
        filters.sepia.setPropriety(xml_brains_["sepia"]->message_node_->ToElement());
        filters.backdropBlur.setPropriety(xml_brains_["backdropBlur"]->message_node_->ToElement());
        filters.backdropBrightness.setPropriety(xml_brains_["backdropBrightness"]->message_node_->ToElement());
        filters.backdropContrast.setPropriety(xml_brains_["backdropContrast"]->message_node_->ToElement());
        filters.backdropGrayscale.setPropriety(xml_brains_["backdropGrayscale"]->message_node_->ToElement());
        filters.backdropHueRotate.setPropriety(xml_brains_["backdropHueRotate"]->message_node_->ToElement());
        filters.backdropInvert.setPropriety(xml_brains_["backdropInvert"]->message_node_->ToElement());
        filters.backdropOpacity.setPropriety(xml_brains_["backdropOpacity"]->message_node_->ToElement());
        filters.backdropSaturate.setPropriety(xml_brains_["backdropSaturate"]->message_node_->ToElement());
        filters.backdropSepia.setPropriety(xml_brains_["backdropSepia"]->message_node_->ToElement());
    }

    // Tables
    {
        tables.borderCollapse.setPropriety(xml_brains_["borderCollapse"]->message_node_->ToElement());
        tables.tableLayout.setPropriety(xml_brains_["tableLayout"]->message_node_->ToElement());
        tables.setBorderSpacingProprieties(xml_brains_["borderSpacing"]->message_node_->ToElement());
        tables.captionSide.setPropriety(xml_brains_["captionSide"]->message_node_->ToElement());
    }

    // Transitions And Animation
    {
        transitionsAndAnimation.transitionProperty.setPropriety(xml_brains_["transitionProperty"]->message_node_->ToElement());
        transitionsAndAnimation.transitionDuration.setPropriety(xml_brains_["transitionDuration"]->message_node_->ToElement());
        transitionsAndAnimation.transitionTimingFunction.setPropriety(xml_brains_["transitionTimingFunction"]->message_node_->ToElement());
        transitionsAndAnimation.transitionDelay.setPropriety(xml_brains_["transitionDelay"]->message_node_->ToElement());
        transitionsAndAnimation.animation.setPropriety(xml_brains_["animation"]->message_node_->ToElement());
    }

    // Transforms
    {
        transforms.setScaleProprieties(xml_brains_["scale"]->message_node_->ToElement());
        transforms.rotate.setPropriety(xml_brains_["rotate"]->message_node_->ToElement());
        transforms.setTranslateProprieties(xml_brains_["translate"]->message_node_->ToElement());
        transforms.setSkewProprieties(xml_brains_["skew"]->message_node_->ToElement());
        transforms.transformOrigin.setPropriety(xml_brains_["transformOrigin"]->message_node_->ToElement());
    }
    // Interactivity
    {
        interactivity.accentColor.setPropriety(xml_brains_["accentColor"]->message_node_->ToElement());
        interactivity.appearance.setPropriety(xml_brains_["appearance"]->message_node_->ToElement());
        interactivity.cursor.setPropriety(xml_brains_["cursor"]->message_node_->ToElement());
        interactivity.caretColor.setPropriety(xml_brains_["caretColor"]->message_node_->ToElement());
        interactivity.pointerEvents.setPropriety(xml_brains_["pointerEvents"]->message_node_->ToElement());
        interactivity.resize.setPropriety(xml_brains_["resize"]->message_node_->ToElement());
        interactivity.scrollBehavior.setPropriety(xml_brains_["scrollBehavior"]->message_node_->ToElement());
        interactivity.setScrollMargin(xml_brains_["scrollMargin"]->message_node_->ToElement());
        interactivity.setScrollPadding(xml_brains_["scrollPadding"]->message_node_->ToElement());
        interactivity.scrollSnapAlign.setPropriety(xml_brains_["scrollSnapAlign"]->message_node_->ToElement());
        interactivity.scrollSnapStop.setPropriety(xml_brains_["scrollSnapStop"]->message_node_->ToElement());
        interactivity.scrollSnapType.setPropriety(xml_brains_["scrollSnapType"]->message_node_->ToElement());
        interactivity.scrollSnapStrictness.setPropriety(xml_brains_["scrollSnapStrictness"]->message_node_->ToElement());
        interactivity.touchAction.setPropriety(xml_brains_["touchAction"]->message_node_->ToElement());
        interactivity.userSelect.setPropriety(xml_brains_["userSelect"]->message_node_->ToElement());
        interactivity.willChange.setPropriety(xml_brains_["willChange"]->message_node_->ToElement());
    }

    // Layout
    {
        layout.aspectRatio.setPropriety(xml_brains_["aspectRatio"]->message_node_->ToElement());
        layout.container.setPropriety(xml_brains_["container"]->message_node_->ToElement());
        layout.columns.setPropriety(xml_brains_["columns"]->message_node_->ToElement());
        layout.breakAfter.setPropriety(xml_brains_["breakAfter"]->message_node_->ToElement());
        layout.breakBefore.setPropriety(xml_brains_["breakBefore"]->message_node_->ToElement());
        layout.breakInside.setPropriety(xml_brains_["breakInside"]->message_node_->ToElement());
        layout.boxDecorationBreak.setPropriety(xml_brains_["boxDecorationBreak"]->message_node_->ToElement());
        layout.boxSizing.setPropriety(xml_brains_["boxSizing"]->message_node_->ToElement());
        layout.display.setPropriety(xml_brains_["display"]->message_node_->ToElement());
        layout.floats.setPropriety(xml_brains_["floats"]->message_node_->ToElement());
        layout.clear.setPropriety(xml_brains_["clear"]->message_node_->ToElement());
        layout.isolation.setPropriety(xml_brains_["isolation"]->message_node_->ToElement());
        layout.objectFit.setPropriety(xml_brains_["objectFit"]->message_node_->ToElement());
        layout.objectPosition.setPropriety(xml_brains_["objectPosition"]->message_node_->ToElement());
        layout.setOverflowProprieties(xml_brains_["overflow"]->message_node_->ToElement());
        layout.setOverscrollBehaviorProprieties(xml_brains_["overscrollBehavior"]->message_node_->ToElement());
        layout.position.setPropriety(xml_brains_["position"]->message_node_->ToElement());
        layout.setInsetProprieties(xml_brains_["inset"]->message_node_->ToElement());
        layout.visibility.setPropriety(xml_brains_["visibility"]->message_node_->ToElement());
        layout.zIndex.setPropriety(xml_brains_["zIndex"]->message_node_->ToElement());
    }

    // Spacing
    {
        spacing.setPaddingProprieties(xml_brains_["padding"]->message_node_->ToElement());
        spacing.setMarginProprieties(xml_brains_["margin"]->message_node_->ToElement());
        spacing.setSpaceBetweenProprieties(xml_brains_["space"]->message_node_->ToElement());
        spacing.spaceXReverse.setPropriety(xml_brains_["spaceXReverse"]->message_node_->ToElement());
        spacing.spaceYReverse.setPropriety(xml_brains_["spaceYReverse"]->message_node_->ToElement());
    }

    // Effects
    {
        effects.boxShadow.setPropriety(xml_brains_["boxShadow"]->message_node_->ToElement());
        effects.boxShadow_inner.setPropriety(xml_brains_["boxShadowInner"]->message_node_->ToElement());
        effects.boxShadowColor.setPropriety(xml_brains_["boxShadowColor"]->message_node_->ToElement());
        effects.opacity.setPropriety(xml_brains_["opacity"]->message_node_->ToElement());
        effects.mixBlendMode.setPropriety(xml_brains_["mixBlendMode"]->message_node_->ToElement());
        effects.backgroundBlendMode.setPropriety(xml_brains_["backgroundBlendMode"]->message_node_->ToElement());
    }

    // Borders
    {
        borders.setBorderRadiusProprieties(xml_brains_["borderRadius"]->message_node_->ToElement());
        borders.setBorderWidthProprieties(xml_brains_["borderWidth"]->message_node_->ToElement());
        borders.borderColor.setPropriety(xml_brains_["borderColor"]->message_node_->ToElement());
        borders.borderStyle.setPropriety(xml_brains_["borderStyle"]->message_node_->ToElement());
        borders.setDivideWidthProprieties(xml_brains_["divideWidth"]->message_node_->ToElement());
        borders.divideXReverse.setPropriety(xml_brains_["divideXReverse"]->message_node_->ToElement());
        borders.divideYReverse.setPropriety(xml_brains_["divideYReverse"]->message_node_->ToElement());
        borders.divideColor.setPropriety(xml_brains_["divideColor"]->message_node_->ToElement());
        borders.divideStyle.setPropriety(xml_brains_["divideStyle"]->message_node_->ToElement());
        borders.outlineWidth.setPropriety(xml_brains_["outlineWidth"]->message_node_->ToElement());
        borders.outlineColor.setPropriety(xml_brains_["outlineColor"]->message_node_->ToElement());
        borders.outlineStyle.setPropriety(xml_brains_["outlineStyle"]->message_node_->ToElement());
        borders.outlineOffset.setPropriety(xml_brains_["outlineOffset"]->message_node_->ToElement());
        borders.ringWidth.setPropriety(xml_brains_["ringWidth"]->message_node_->ToElement());
        borders.ringInset.setPropriety(xml_brains_["ringInset"]->message_node_->ToElement());
        borders.ringColor.setPropriety(xml_brains_["ringColor"]->message_node_->ToElement());
        borders.ringOffsetWidth.setPropriety(xml_brains_["ringOffsetWidth"]->message_node_->ToElement());
        borders.ringOffsetColor.setPropriety(xml_brains_["ringOffsetColor"]->message_node_->ToElement());
    }
}

std::vector<std::string> TailwindConfig::getStyleClasses()
{
    std::vector<std::string> return_vector;
    // Svg
    {
        for (auto variant : svg.fill.styleClasses)
            return_vector.push_back("svg | " + variant);
        for (auto variant : svg.stroke.styleClasses)
            return_vector.push_back("svg | " + variant);
        for (auto variant : svg.strokeWidth.styleClasses)
            return_vector.push_back("svg | " + variant);
    }
    // Sizing
    {
        for (auto variant : sizing.width.styleClasses)
            return_vector.push_back("sizing | " + variant);
        for (auto variant : sizing.height.styleClasses)
            return_vector.push_back("sizing | " + variant);
        for (auto variant : sizing.minWidth.styleClasses)
            return_vector.push_back("sizing | " + variant);
        for (auto variant : sizing.maxWidth.styleClasses)
            return_vector.push_back("sizing | " + variant);
        for (auto variant : sizing.minHeight.styleClasses)
            return_vector.push_back("sizing | " + variant);
        for (auto variant : sizing.maxHeight.styleClasses)
            return_vector.push_back("sizing | " + variant);
    }
    // Typography
    {
        for (auto variant : typography.fontFamily.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.fontSize.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.fontSmoothing.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.fontStyle.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.fontWeight.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.fontVariantNumeric.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.letterSpacing.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.lineClamp.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.lineHeight.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.listStyleImage.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.listStylePosition.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.listStyleType.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textAlign.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textColor.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textDecoration.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textDecorationColor.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textDecorationStyle.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textDecorationThickness.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textUnderlineOffset.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textTransform.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textOverflow.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.textIndent.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.verticalAlign.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.whitespace.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.wordBreak.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.hyphens.styleClasses)
            return_vector.push_back("typography | " + variant);
        for (auto variant : typography.content.styleClasses)
            return_vector.push_back("typography | " + variant);
    }
    // Backgrounds
    {
        for (auto variant : backgrounds.backgroundColor.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundImage.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundColorFrom.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundColorVia.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundColorTo.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundPosition.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundSize.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundRepeat.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundAttachment.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundClip.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
        for (auto variant : backgrounds.backgroundOrigin.styleClasses)
            return_vector.push_back("backgrounds | " + variant);
    }
    // Accesibility
    {
        for (auto variant : accesibility.screenReaders.styleClasses)
            return_vector.push_back("accessibility | " + variant);
    }
    // Layout
    {
        for (auto variant : layout.aspectRatio.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.container.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.columns.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.breakAfter.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.breakBefore.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.breakInside.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.boxDecorationBreak.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.boxSizing.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.display.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.floats.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.clear.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.isolation.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.objectFit.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.objectPosition.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overflow.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overflow_x.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overflow_y.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overscrollBehavior.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overscrollBehavior_x.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.overscrollBehavior_y.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.position.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.inset.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.inset_x.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.inset_y.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.top.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.right.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.bottom.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.left.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.visibility.styleClasses)
            return_vector.push_back("layout | " + variant);
        for (auto variant : layout.zIndex.styleClasses)
            return_vector.push_back("layout | " + variant);
    }
    // FlexboxAndGrid
    {
        for (auto variant : flexboxAndGrid.flexDirection.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.flexWrap.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.flex.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.flexGrow.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.flexShrink.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.order.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.gridTemplateColumns.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridColumn_span.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridColumnStart.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridColumnEnd.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridTemplateRows.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridRow_span.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridRowStart.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridRowEnd.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridAutoFlow.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridAutoColumns.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gridAutoRows.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gap.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gap_x.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.gap_y.styleClasses)
            return_vector.push_back("grid | " + variant);
        for (auto variant : flexboxAndGrid.justifyContent.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.justifyItems.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.justifySelf.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.alignContent.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.alignItems.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.alignSelf.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.placeContent.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.placeItems.styleClasses)
            return_vector.push_back("flex | " + variant);
        for (auto variant : flexboxAndGrid.placeSelf.styleClasses)
            return_vector.push_back("flex | " + variant);
    }
    // Filters
    {
        for (auto variant : filters.blur.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.brightness.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.contrast.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.dropShadow.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.grayscale.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.hueRotate.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.invert.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.saturate.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.sepia.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropBlur.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropBrightness.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropContrast.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropGrayscale.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropHueRotate.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropInvert.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropOpacity.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropSaturate.styleClasses)
            return_vector.push_back("filters | " + variant);
        for (auto variant : filters.backdropSepia.styleClasses)
            return_vector.push_back("filters | " + variant);
    }
    // Tables
    {
        for (auto variant : tables.borderCollapse.styleClasses)
            return_vector.push_back("tables | " + variant);
        for (auto variant : tables.borderSpacing.styleClasses)
            return_vector.push_back("tables | " + variant);
        for (auto variant : tables.borderSpacing_x.styleClasses)
            return_vector.push_back("tables | " + variant);
        for (auto variant : tables.borderSpacing_y.styleClasses)
            return_vector.push_back("tables | " + variant);
        for (auto variant : tables.tableLayout.styleClasses)
            return_vector.push_back("tables | " + variant);
        for (auto variant : tables.captionSide.styleClasses)
            return_vector.push_back("tables | " + variant);
    }
    // TransitionsAndAnimation
    {
        for (auto variant : transitionsAndAnimation.transitionProperty.styleClasses)
            return_vector.push_back("trans-&-animation | " + variant);
        for (auto variant : transitionsAndAnimation.transitionDuration.styleClasses)
            return_vector.push_back("trans-&-animation | " + variant);
        for (auto variant : transitionsAndAnimation.transitionTimingFunction.styleClasses)
            return_vector.push_back("trans-&-animation | " + variant);
        for (auto variant : transitionsAndAnimation.transitionDelay.styleClasses)
            return_vector.push_back("trans-&-animation | " + variant);
        for (auto variant : transitionsAndAnimation.animation.styleClasses)
            return_vector.push_back("trans-&-animation | " + variant);
    }
    // Transforms
    {
        for (auto variant : transforms.scale.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.scale_x.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.scale_y.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.rotate.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.translate_x.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.translate_y.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.skew_x.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.skew_y.styleClasses)
            return_vector.push_back("transforms | " + variant);
        for (auto variant : transforms.transformOrigin.styleClasses)
            return_vector.push_back("transforms | " + variant);
    }
    // Interactivity
    {
        for (auto variant : interactivity.accentColor.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.appearance.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.cursor.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.caretColor.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.pointerEvents.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.resize.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollBehavior.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_x.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_y.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_s.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_e.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_t.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_b.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_r.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollMargin_l.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_x.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_y.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_s.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_e.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_t.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_b.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_r.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollPadding_l.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollSnapAlign.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollSnapStop.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollSnapType.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.scrollSnapStrictness.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.touchAction.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.userSelect.styleClasses)
            return_vector.push_back("interactivity | " + variant);
        for (auto variant : interactivity.willChange.styleClasses)
            return_vector.push_back("interactivity | " + variant);
    }
    // Spacing
    {
        for (auto variant : spacing.margin.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_x.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_y.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_s.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_e.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_t.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_b.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_r.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.margin_l.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_x.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_y.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_s.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_e.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_t.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_b.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_r.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.padding_l.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.spaceBetween_x.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.spaceBetween_y.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.spaceXReverse.styleClasses)
            return_vector.push_back("spacing | " + variant);
        for (auto variant : spacing.spaceYReverse.styleClasses)
            return_vector.push_back("spacing | " + variant);
    }
    // Effects
    {
        for (auto variant : effects.boxShadow.styleClasses)
            return_vector.push_back("effects | " + variant);
        for (auto variant : effects.boxShadow_inner.styleClasses)
            return_vector.push_back("effects | " + variant);
        for (auto variant : effects.boxShadowColor.styleClasses)
            return_vector.push_back("effects | " + variant);
        for (auto variant : effects.opacity.styleClasses)
            return_vector.push_back("effects | " + variant);
        for (auto variant : effects.mixBlendMode.styleClasses)
            return_vector.push_back("effects | " + variant);
        for (auto variant : effects.backgroundBlendMode.styleClasses)
            return_vector.push_back("effects | " + variant);
    }
    // Borders
    {
        for (auto variant : borders.borderRadius.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_s.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_e.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_t.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_r.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_b.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderRadius_l.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_x.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_y.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_s.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_e.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_t.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_r.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_b.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderWidth_l.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderColor.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.borderStyle.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideWidth_x.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideWidth_y.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideXReverse.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideYReverse.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideColor.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.divideStyle.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.outlineWidth.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.outlineColor.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.outlineStyle.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.outlineOffset.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.ringWidth.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.ringInset.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.ringColor.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.ringOffsetWidth.styleClasses)
            return_vector.push_back("borders | " + variant);
        for (auto variant : borders.ringOffsetColor.styleClasses)
            return_vector.push_back("borders | " + variant);
    }

    return return_vector;
}

ProprietyData TailwindConfig::readXmlProp(std::string propName)
{
    ProprietyData propriety_data;

    auto prop_node = xml_brains_[propName]->message_node_;
    if (!prop_node)
    {
        std::cout << "\n\n"
                  << propName << " node not found \n\n";
        return propriety_data;
    }
    auto docs_node = prop_node->FirstChildElement("tailwind-docs");
    if (!docs_node)
    {
        std::cout << "\n\n"
                  << propName << " docs node not found \n\n";
        return propriety_data;
    }
    auto reset_node = prop_node->FirstChildElement("reset-command");
    if (!reset_node)
    {
        std::cout << "\n\n"
                  << propName << " reset node not found \n\n";
        return propriety_data;
    }

    auto classes_node = prop_node->FirstChildElement("classes");
    if (!classes_node)
    {
        std::cout << "\n\n"
                  << propName << " classes node not found \n\n";
        return propriety_data;
    }
    if (classes_node->Attribute("id"))
        propriety_data.class_name = classes_node->Attribute("id");
    if (classes_node->Attribute("include"))
        propriety_data.includes = classes_node->Attribute("include");
    if (classes_node->Attribute("customValue") && std::string(classes_node->Attribute("customValue")).compare("true") == 0)
        propriety_data.config_name = true;
    if (classes_node->Attribute("canExtend") && std::string(classes_node->Attribute("canExtend")).compare("true") == 0)
        propriety_data.can_extend = true;

    propriety_data.prop_name = propName;
    propriety_data.docs_link = docs_node->GetText();
    propriety_data.reset_command = reset_node->GetText();

    return propriety_data;
}

void TailwindConfig::readProprieties()
{
    // Svg
    proprieties["stroke"] = readXmlProp("stroke");
    proprieties["fill"] = readXmlProp("fill");
    proprieties["strokeWidth"] = readXmlProp("strokeWidth");

    // Sizing
    proprieties["width"] = readXmlProp("width");
    proprieties["height"] = readXmlProp("height");
    proprieties["minWidth"] = readXmlProp("minWidth");
    proprieties["minHeight"] = readXmlProp("minHeight");
    proprieties["maxWidth"] = readXmlProp("maxWidth");
    proprieties["maxHeight"] = readXmlProp("maxHeight");

    // Typography
    proprieties["fontFamily"] = readXmlProp("fontFamily");
    proprieties["fontSize"] = readXmlProp("fontSize");
    proprieties["fontSmoothing"] = readXmlProp("fontSmoothing");
    proprieties["fontStyle"] = readXmlProp("fontStyle");
    proprieties["fontWeight"] = readXmlProp("fontWeight");
    proprieties["fontVariantNumeric"] = readXmlProp("fontVariantNumeric");
    proprieties["letterSpacing"] = readXmlProp("letterSpacing");
    proprieties["lineClamp"] = readXmlProp("lineClamp");
    proprieties["lineHeight"] = readXmlProp("lineHeight");
    proprieties["listStyleImage"] = readXmlProp("listStyleImage");
    proprieties["listStylePosition"] = readXmlProp("listStylePosition");
    proprieties["listStyleType"] = readXmlProp("listStyleType");
    proprieties["textAlign"] = readXmlProp("textAlign");
    proprieties["textColor"] = readXmlProp("textColor");
    proprieties["textDecoration"] = readXmlProp("textDecoration");
    proprieties["textDecorationColor"] = readXmlProp("textDecorationColor");
    proprieties["textDecorationStyle"] = readXmlProp("textDecorationStyle");
    proprieties["textDecorationThickness"] = readXmlProp("textDecorationThickness");
    proprieties["textUnderlineOffset"] = readXmlProp("textUnderlineOffset");
    proprieties["textTransform"] = readXmlProp("textTransform");
    proprieties["textOverflow"] = readXmlProp("textOverflow");
    proprieties["textWrap"] = readXmlProp("textWrap");
    proprieties["textIndent"] = readXmlProp("textIndent");
    proprieties["verticalAlign"] = readXmlProp("verticalAlign");
    proprieties["whitespace"] = readXmlProp("whitespace");
    proprieties["wordBreak"] = readXmlProp("wordBreak");
    proprieties["hyphens"] = readXmlProp("hyphens");
    proprieties["content"] = readXmlProp("content");

    // Backgrounds
    proprieties["backgroundAttachment"] = readXmlProp("backgroundAttachment");
    proprieties["backgroundClip"] = readXmlProp("backgroundClip");
    proprieties["backgroundColor"] = readXmlProp("backgroundColor");
    proprieties["backgroundOrigin"] = readXmlProp("backgroundOrigin");
    proprieties["backgroundPosition"] = readXmlProp("backgroundPosition");
    proprieties["backgroundRepeat"] = readXmlProp("backgroundRepeat");
    proprieties["backgroundSize"] = readXmlProp("backgroundSize");
    proprieties["backgroundImage"] = readXmlProp("backgroundImage");
    proprieties["gradientColorStep"] = readXmlProp("gradientColorStep");

    // Accesibility
    proprieties["screenReaders"] = readXmlProp("screenReaders");

    // FlexboxAndGrid
    proprieties["flexBasis"] = readXmlProp("flexBasis");
    proprieties["flexDirection"] = readXmlProp("flexDirection");
    proprieties["flexWrap"] = readXmlProp("flexWrap");
    proprieties["flex"] = readXmlProp("flex");
    proprieties["flexGrow"] = readXmlProp("flexGrow");
    proprieties["flexShrink"] = readXmlProp("flexShrink");
    proprieties["order"] = readXmlProp("order");
    proprieties["gridTemplateColumns"] = readXmlProp("gridTemplateColumns");
    proprieties["gridColumn"] = readXmlProp("gridColumn");
    proprieties["gridColumnStart"] = readXmlProp("gridColumnStart");
    proprieties["gridColumnEnd"] = readXmlProp("gridColumnEnd");
    proprieties["gridTemplateRows"] = readXmlProp("gridTemplateRows");
    proprieties["gridRow"] = readXmlProp("gridRow");
    proprieties["gridRowStart"] = readXmlProp("gridRowStart");
    proprieties["gridRowEnd"] = readXmlProp("gridRowEnd");
    proprieties["gridAutoFlow"] = readXmlProp("gridAutoFlow");
    proprieties["gridAutoColumns"] = readXmlProp("gridAutoColumns");
    proprieties["gridAutoRows"] = readXmlProp("gridAutoRows");
    proprieties["gap"] = readXmlProp("gap");
    proprieties["justifyContent"] = readXmlProp("justifyContent");
    proprieties["justifyItems"] = readXmlProp("justifyItems");
    proprieties["justifySelf"] = readXmlProp("justifySelf");
    proprieties["alignContent"] = readXmlProp("alignContent");
    proprieties["alignItems"] = readXmlProp("alignItems");
    proprieties["alignSelf"] = readXmlProp("alignSelf");
    proprieties["placeContent"] = readXmlProp("placeContent");
    proprieties["placeItems"] = readXmlProp("placeItems");
    proprieties["placeSelf"] = readXmlProp("placeSelf");

    // Filters
    proprieties["blur"] = readXmlProp("blur");
    proprieties["brightness"] = readXmlProp("brightness");
    proprieties["contrast"] = readXmlProp("contrast");
    proprieties["dropShadow"] = readXmlProp("dropShadow");
    proprieties["grayscale"] = readXmlProp("grayscale");
    proprieties["hueRotate"] = readXmlProp("hueRotate");
    proprieties["invert"] = readXmlProp("invert");
    proprieties["saturate"] = readXmlProp("saturate");
    proprieties["sepia"] = readXmlProp("sepia");
    proprieties["backdropBlur"] = readXmlProp("backdropBlur");
    proprieties["backdropBrightness"] = readXmlProp("backdropBrightness");
    proprieties["backdropContrast"] = readXmlProp("backdropContrast");
    proprieties["backdropGrayscale"] = readXmlProp("backdropGrayscale");
    proprieties["backdropHueRotate"] = readXmlProp("backdropHueRotate");
    proprieties["backdropInvert"] = readXmlProp("backdropInvert");
    proprieties["backdropOpacity"] = readXmlProp("backdropOpacity");
    proprieties["backdropSaturate"] = readXmlProp("backdropSaturate");
    proprieties["backdropSepia"] = readXmlProp("backdropSepia");
    proprieties["borderRadius"] = readXmlProp("borderRadius");
    proprieties["borderWidth"] = readXmlProp("borderWidth");
    proprieties["borderColor"] = readXmlProp("borderColor");
    proprieties["borderStyle"] = readXmlProp("borderStyle");

    // Tables
    proprieties["borderCollapse"] = readXmlProp("borderCollapse");
    proprieties["borderSpacing"] = readXmlProp("borderSpacing");
    proprieties["tableLayout"] = readXmlProp("tableLayout");
    proprieties["captionSide"] = readXmlProp("captionSide");

    // Transitions
    proprieties["transitionProperty"] = readXmlProp("transitionProperty");
    proprieties["transitionDuration"] = readXmlProp("transitionDuration");
    proprieties["transitionTimingFunction"] = readXmlProp("transitionTimingFunction");
    proprieties["transitionDelay"] = readXmlProp("transitionDelay");
    proprieties["animation"] = readXmlProp("animation");

    // Transforms
    proprieties["scale"] = readXmlProp("scale");
    proprieties["rotate"] = readXmlProp("rotate");
    proprieties["translate"] = readXmlProp("translate");
    proprieties["skew"] = readXmlProp("skew");
    proprieties["transformOrigin"] = readXmlProp("transformOrigin");

    // Interactivity

    proprieties["accentColor"] = readXmlProp("accentColor");
    proprieties["appearance"] = readXmlProp("appearance");
    proprieties["cursor"] = readXmlProp("cursor");
    proprieties["caretColor"] = readXmlProp("caretColor");
    proprieties["pointerEvents"] = readXmlProp("pointerEvents");
    proprieties["resize"] = readXmlProp("resize");
    proprieties["scrollBehavior"] = readXmlProp("scrollBehavior");
    proprieties["scrollMargin"] = readXmlProp("scrollMargin");
    proprieties["scrollPadding"] = readXmlProp("scrollPadding");
    proprieties["scrollSnapAlign"] = readXmlProp("scrollSnapAlign");
    proprieties["scrollSnapStop"] = readXmlProp("scrollSnapStop");
    proprieties["scrollSnapType"] = readXmlProp("scrollSnapType");
    proprieties["scrollSnapStrictness"] = readXmlProp("scrollSnapStrictness");
    proprieties["touchAction"] = readXmlProp("touchAction");
    proprieties["userSelect"] = readXmlProp("userSelect");
    proprieties["willChange"] = readXmlProp("willChange");

    // Layout
    proprieties["aspectRatio"] = readXmlProp("aspectRatio");
    proprieties["container"] = readXmlProp("container");
    proprieties["columns"] = readXmlProp("columns");
    proprieties["breakAfter"] = readXmlProp("breakAfter");
    proprieties["breakBefore"] = readXmlProp("breakBefore");
    proprieties["breakInside"] = readXmlProp("breakInside");
    proprieties["boxDecorationBreak"] = readXmlProp("boxDecorationBreak");
    proprieties["boxSizing"] = readXmlProp("boxSizing");
    proprieties["display"] = readXmlProp("display");
    proprieties["floats"] = readXmlProp("floats");
    proprieties["clear"] = readXmlProp("clear");
    proprieties["isolation"] = readXmlProp("isolation");
    proprieties["objectFit"] = readXmlProp("objectFit");
    proprieties["objectPosition"] = readXmlProp("objectPosition");
    proprieties["overflow"] = readXmlProp("overflow");
    proprieties["overscrollBehavior"] = readXmlProp("overscrollBehavior");
    proprieties["position"] = readXmlProp("position");
    proprieties["inset"] = readXmlProp("inset");
    proprieties["visibility"] = readXmlProp("visibility");
    proprieties["zIndex"] = readXmlProp("zIndex");

    // Spacing
    proprieties["padding"] = readXmlProp("padding");
    proprieties["margin"] = readXmlProp("margin");
    proprieties["space"] = readXmlProp("space");
    proprieties["spaceXReverse"] = readXmlProp("spaceXReverse");
    proprieties["spaceYReverse"] = readXmlProp("spaceYReverse");

    // Effects
    proprieties["boxShadow"] = readXmlProp("boxShadow");
    proprieties["boxShadowInner"] = readXmlProp("boxShadowInner");
    proprieties["boxShadowColor"] = readXmlProp("boxShadowColor");
    proprieties["opacity"] = readXmlProp("opacity");
    proprieties["mixBlendMode"] = readXmlProp("mixBlendMode");
    proprieties["backgroundBlendMode"] = readXmlProp("backgroundBlendMode");

    // Borders
    proprieties["divideWidth"] = readXmlProp("divideWidth");
    proprieties["divideXReverse"] = readXmlProp("divideXReverse");
    proprieties["divideYReverse"] = readXmlProp("divideYReverse");
    proprieties["divideColor"] = readXmlProp("divideColor");
    proprieties["divideStyle"] = readXmlProp("divideStyle");
    proprieties["outlineWidth"] = readXmlProp("outlineWidth");
    proprieties["outlineColor"] = readXmlProp("outlineColor");
    proprieties["outlineStyle"] = readXmlProp("outlineStyle");
    proprieties["outlineOffset"] = readXmlProp("outlineOffset");
    proprieties["ringWidth"] = readXmlProp("ringWidth");
    proprieties["ringInset"] = readXmlProp("ringInset");
    proprieties["ringColor"] = readXmlProp("ringColor");
    proprieties["ringOffsetWidth"] = readXmlProp("ringOffsetWidth");
    proprieties["ringOffsetColor"] = readXmlProp("ringOffsetColor");

    // Scale proprieties
    proprieties["screens"] = readXmlProp("screens");
    proprieties["colors"] = readXmlProp("colors");
    proprieties["spacing"] = readXmlProp("spacing");
}

std::vector<variant_and_value_pair> TailwindConfig::getVariants(tinyxml2::XMLElement *variants_node)
{

    std::vector<variant_and_value_pair> variants;
    std::string config_name;
    if (variants_node->Parent())
    {
        auto parent = variants_node->Parent();
        if (parent->ToElement())
        {
            auto parentElement = parent->ToElement();
            if (parentElement->Attribute("id"))
            {
                config_name = parentElement->Attribute("id");
            }
            else
            {
                std::cout << "\n\n no attribute id found on message node \n\n";
            }
        }
        else
            std::cout << "\n\n parent is not an element \n\n";
    }
    else
        std::cout << "\n\n parent not found \n\n";

    auto class_node = variants_node->FirstChildElement("class");
    std::vector<variant_and_value_pair> extend_variant_value_pairs;
    while (class_node)
    {
        auto class_name_node = class_node->FirstChildElement("name");
        auto class_value_node = class_node->FirstChildElement("value");

        if (!class_name_node && class_value_node && class_name_node->GetText() && class_value_node->GetText())
        {
            std::cout << "\n\n class name or value node not found \n\n";
            return variants;
        }
        std::string class_name = class_name_node->GetText();
        std::string class_value = class_value_node->GetText();

        variants.push_back(std::make_pair(class_name, class_value));
        if (class_node->Attribute("extends"))
        {
            extend_variant_value_pairs.push_back(std::make_pair(class_name, class_value));
        }

        class_node = class_node->NextSiblingElement("class");
    }

    if (extend_variant_value_pairs.size() > 0)
    {
        std::string prop = "\t\t\t" + config_name + ": {\n";
        for (auto extend_class_variant : extend_variant_value_pairs)
        {
            // std::cout << "\n\n extend_class_variant: " << extend_class_variant.first << " | " << extend_class_variant.second << "\n\n";
            prop += "\t\t\t\t '" + extend_class_variant.first + "': '" + extend_class_variant.second + "',\n";
        }
        prop += "\t\t\t},\n";
        // std::cout << "\n\n" << prop << "\n\n";
        configFileData.extend[config_name] = prop;
    }

    return variants;
}

void TailwindConfig::getColorVariants(tinyxml2::XMLElement *colors_node)
{
    std::vector<color_variants_css_pair> extend_color__intensities_and_css;

    auto classes_node = colors_node->FirstChildElement("classes");
    while (classes_node)
    {
        std::vector<std::pair<std::string, std::string>> extend_color_variants;
        std::string color_name;
        if (!classes_node->Attribute("className"))
        {
            std::cout << "\n\n className attribute representing a color not found  \n\n";
            return;
        }

        color_name = classes_node->Attribute("className");
        // std::cout << "\n\n color name: " << color_name << "\n\n";
        std::vector<std::pair<std::string, std::string>> this_color_variants;
        auto color_class_node = classes_node->FirstChildElement("class");
        while (color_class_node)
        {
            auto color_class_name_node = color_class_node->FirstChildElement("name");
            auto color_class_value_node = color_class_node->FirstChildElement("value");
            if (!color_class_name_node || !color_class_value_node ||
                !color_class_name_node->GetText() || !color_class_value_node->GetText())
            {
                std::cout << "\n\n color class name or value node not found \n\n";
                return;
            }
            if (color_class_node->Attribute("extends"))
            {
                // std::cout << "\n\n extends attribute found \n\n";
                extend_color_variants.push_back(std::make_pair(color_class_name_node->GetText(), color_class_value_node->GetText()));
            }

            std::string color_class_name = color_class_name_node->GetText();
            std::string color_class_value = color_class_value_node->GetText();

            this_color_variants.push_back(std::make_pair(color_class_name, color_class_value));
            color_class_node = color_class_node->NextSiblingElement("class");
        }
        color_variants.push_back(std::make_pair(color_name, this_color_variants));

        if (extend_color_variants.size() > 0)
        {
            extend_color__intensities_and_css.push_back(std::make_pair(color_name, this_color_variants));
        }

        classes_node = classes_node->NextSiblingElement("classes");
    }

    if (extend_color__intensities_and_css.size() > 0)
    {
        std::string prop = "\t\t\tcolors: {\n";
        for (auto extend_color__intensities_and_css : extend_color__intensities_and_css)
        {
            // std::cout << "\n\n extend_color__intensities_and_css: " << extend_color__intensities_and_css.first << "\n";
            prop += "\t\t\t\t " + extend_color__intensities_and_css.first + ": {\n";
            for (auto color_variant : extend_color__intensities_and_css.second)
            {
                prop += "\t\t\t\t\t " + color_variant.first + ": '" + color_variant.second + "',\n";
            }
            prop += "\t\t\t\t},\n";
        }
        prop += "\t\t\t},\n";
        // std::cout << "\n\n" << prop << "\n\n";
        configFileData.extend["colors"] = prop;
    }
}
