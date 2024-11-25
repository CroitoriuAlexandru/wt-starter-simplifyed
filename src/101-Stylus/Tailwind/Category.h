#pragma once
#include "101-Stylus/Tailwind/Base.h"
#include <string>
#include <vector>
#include <boost/regex.hpp>

class TailwindConfig;

class TSvg
{
public:
    TSvg(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          fill(tailwind_config),
          stroke(tailwind_config),
          strokeWidth(tailwind_config) {};

    Propriety fill;
    Propriety stroke;
    Propriety strokeWidth;

    TailwindConfig *tailwind_config_;
};

class TSizing
{
public:
    TSizing(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          width(tailwind_config),
          height(tailwind_config),
          minWidth(tailwind_config),
          maxWidth(tailwind_config),
          minHeight(tailwind_config),
          maxHeight(tailwind_config) {};

    Propriety width;
    Propriety height;
    Propriety minWidth;
    Propriety maxWidth;
    Propriety minHeight;
    Propriety maxHeight;

    TailwindConfig *tailwind_config_;
};

class TTypography
{
public:
    TTypography(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          fontFamily(tailwind_config),
          fontSize(tailwind_config),
          fontSmoothing(tailwind_config),
          fontStyle(tailwind_config),
          fontWeight(tailwind_config),
          fontVariantNumeric(tailwind_config),
          letterSpacing(tailwind_config),
          lineClamp(tailwind_config),
          lineHeight(tailwind_config),
          listStyleImage(tailwind_config),
          listStylePosition(tailwind_config),
          listStyleType(tailwind_config),
          textAlign(tailwind_config),
          textColor(tailwind_config),
          textDecoration(tailwind_config),
          textDecorationColor(tailwind_config),
          textDecorationStyle(tailwind_config),
          textDecorationThickness(tailwind_config),
          textUnderlineOffset(tailwind_config),
          textTransform(tailwind_config),
          textOverflow(tailwind_config),
          textWrap(tailwind_config),
          textIndent(tailwind_config),
          verticalAlign(tailwind_config),
          whitespace(tailwind_config),
          wordBreak(tailwind_config),
          hyphens(tailwind_config),
          content(tailwind_config) {};

    Propriety fontFamily;
    Propriety fontSize;
    Propriety fontSmoothing;
    Propriety fontStyle;
    Propriety fontWeight;
    Propriety fontVariantNumeric;
    Propriety letterSpacing;
    Propriety lineClamp;
    Propriety lineHeight;
    Propriety listStyleImage;
    Propriety listStylePosition;
    Propriety listStyleType;
    Propriety textAlign;
    Propriety textColor;
    Propriety textDecoration;
    Propriety textDecorationColor;
    Propriety textDecorationStyle;
    Propriety textDecorationThickness;
    Propriety textUnderlineOffset;
    Propriety textTransform;
    Propriety textOverflow;
    Propriety textWrap;
    Propriety textIndent;
    Propriety verticalAlign;
    Propriety whitespace;
    Propriety wordBreak;
    Propriety hyphens;
    Propriety content;

    TailwindConfig *tailwind_config_;
};

class TAccesibility
{
public:
    TAccesibility(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          screenReaders(tailwind_config) {};

    Propriety screenReaders;

    TailwindConfig *tailwind_config_;
};

class TBackgrounds
{
public:
    TBackgrounds(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          backgroundColor(tailwind_config),
          backgroundImage(tailwind_config),
          backgroundColorFrom(tailwind_config),
          backgroundColorVia(tailwind_config),
          backgroundColorTo(tailwind_config),
          backgroundColorFromStep(tailwind_config),
          backgroundColorViaStep(tailwind_config),
          backgroundColorToStep(tailwind_config),
          backgroundPosition(tailwind_config),
          backgroundSize(tailwind_config),
          backgroundRepeat(tailwind_config),
          backgroundAttachment(tailwind_config),
          backgroundClip(tailwind_config),
          backgroundOrigin(tailwind_config) {};

    Propriety backgroundColor;
    Propriety backgroundImage;

    Propriety backgroundColorFrom;
    Propriety backgroundColorVia;
    Propriety backgroundColorTo;
    Propriety backgroundColorFromStep;
    Propriety backgroundColorViaStep;
    Propriety backgroundColorToStep;

    Propriety backgroundPosition;
    Propriety backgroundSize;
    Propriety backgroundRepeat;
    Propriety backgroundAttachment;
    Propriety backgroundClip;
    Propriety backgroundOrigin;

    void setGradientStepAndColorProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TFlexboxAndGrid
{
public:
    TFlexboxAndGrid(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          flexBasis(tailwind_config),
          flexDirection(tailwind_config),
          flexWrap(tailwind_config),
          flex(tailwind_config),
          flexGrow(tailwind_config),
          flexShrink(tailwind_config),
          order(tailwind_config),
          gridTemplateColumns(tailwind_config),
          gridColumn_span(tailwind_config),
          gridColumnStart(tailwind_config),
          gridColumnEnd(tailwind_config),
          gridTemplateRows(tailwind_config),
          gridRow_span(tailwind_config),
          gridRowStart(tailwind_config),
          gridRowEnd(tailwind_config),
          gridAutoFlow(tailwind_config),
          gridAutoColumns(tailwind_config),
          gridAutoRows(tailwind_config),
          gap(tailwind_config),
          gap_x(tailwind_config),
          gap_y(tailwind_config),
          justifyContent(tailwind_config),
          justifyItems(tailwind_config),
          justifySelf(tailwind_config),
          alignContent(tailwind_config),
          alignItems(tailwind_config),
          alignSelf(tailwind_config),
          placeContent(tailwind_config),
          placeItems(tailwind_config),
          placeSelf(tailwind_config) {};

    Propriety flexBasis;
    Propriety flexDirection;
    Propriety flexWrap;
    Propriety flex;
    Propriety flexGrow;
    Propriety flexShrink;
    Propriety order; //
    Propriety gridTemplateColumns;
    Propriety gridColumn_span;
    Propriety gridColumnStart;
    Propriety gridColumnEnd;
    Propriety gridTemplateRows;
    Propriety gridRow_span;
    Propriety gridRowStart;
    Propriety gridRowEnd;
    Propriety gridAutoFlow;
    Propriety gridAutoColumns;
    Propriety gridAutoRows;
    Propriety gap;
    Propriety gap_x;
    Propriety gap_y;
    Propriety justifyContent;
    Propriety justifyItems;
    Propriety justifySelf;
    Propriety alignContent;
    Propriety alignItems;
    Propriety alignSelf;
    Propriety placeContent;
    Propriety placeItems;
    Propriety placeSelf;

    void setGapProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TFilters
{
public:
    TFilters(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          blur(tailwind_config),
          brightness(tailwind_config),
          contrast(tailwind_config),
          dropShadow(tailwind_config),
          grayscale(tailwind_config),
          hueRotate(tailwind_config),
          invert(tailwind_config),
          saturate(tailwind_config),
          sepia(tailwind_config),
          backdropBlur(tailwind_config),
          backdropBrightness(tailwind_config),
          backdropContrast(tailwind_config),
          backdropGrayscale(tailwind_config),
          backdropHueRotate(tailwind_config),
          backdropInvert(tailwind_config),
          backdropOpacity(tailwind_config),
          backdropSaturate(tailwind_config),
          backdropSepia(tailwind_config) {};

    Propriety blur;
    Propriety brightness;
    Propriety contrast;
    Propriety dropShadow;
    Propriety grayscale;
    Propriety hueRotate;
    Propriety invert;
    Propriety saturate;
    Propriety sepia;
    Propriety backdropBlur;
    Propriety backdropBrightness;
    Propriety backdropContrast;
    Propriety backdropGrayscale;
    Propriety backdropHueRotate;
    Propriety backdropInvert;
    Propriety backdropOpacity;
    Propriety backdropSaturate;
    Propriety backdropSepia;

    TailwindConfig *tailwind_config_;
};

class TTables
{
public:
    TTables(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          borderCollapse(tailwind_config),
          borderSpacing(tailwind_config),
          borderSpacing_x(tailwind_config),
          borderSpacing_y(tailwind_config),
          tableLayout(tailwind_config),
          captionSide(tailwind_config) {};

    Propriety borderCollapse;
    Propriety borderSpacing;
    Propriety borderSpacing_x;
    Propriety borderSpacing_y;
    Propriety tableLayout;
    Propriety captionSide;

    void setBorderSpacingProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TTransitionsAndAnimation
{
public:
    TTransitionsAndAnimation(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          transitionProperty(tailwind_config),
          transitionDuration(tailwind_config),
          transitionTimingFunction(tailwind_config),
          transitionDelay(tailwind_config),
          animation(tailwind_config) {};

    Propriety transitionProperty;
    Propriety transitionDuration;
    Propriety transitionTimingFunction;
    Propriety transitionDelay;
    Propriety animation;

    TailwindConfig *tailwind_config_;
};

class TTransforms
{
public:
    TTransforms(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          scale(tailwind_config),
          scale_x(tailwind_config),
          scale_y(tailwind_config),
          rotate(tailwind_config),
          translate_x(tailwind_config),
          translate_y(tailwind_config),
          skew_x(tailwind_config),
          skew_y(tailwind_config),
          transformOrigin(tailwind_config) {};

    Propriety scale;
    Propriety scale_x;
    Propriety scale_y;
    Propriety rotate;
    Propriety translate_x;
    Propriety translate_y;
    Propriety skew_x;
    Propriety skew_y;
    Propriety transformOrigin;

    void setScaleProprieties(tinyxml2::XMLElement *prop_node);
    void setTranslateProprieties(tinyxml2::XMLElement *prop_node);
    void setSkewProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TInteractivity
{
public:
    TInteractivity(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          accentColor(tailwind_config),
          appearance(tailwind_config),
          cursor(tailwind_config),
          caretColor(tailwind_config),
          pointerEvents(tailwind_config),
          resize(tailwind_config),
          scrollBehavior(tailwind_config),
          scrollMargin(tailwind_config),
          scrollMargin_x(tailwind_config),
          scrollMargin_y(tailwind_config),
          scrollMargin_s(tailwind_config),
          scrollMargin_e(tailwind_config),
          scrollMargin_t(tailwind_config),
          scrollMargin_b(tailwind_config),
          scrollMargin_r(tailwind_config),
          scrollMargin_l(tailwind_config),
          scrollPadding(tailwind_config),
          scrollPadding_x(tailwind_config),
          scrollPadding_y(tailwind_config),
          scrollPadding_s(tailwind_config),
          scrollPadding_e(tailwind_config),
          scrollPadding_t(tailwind_config),
          scrollPadding_b(tailwind_config),
          scrollPadding_r(tailwind_config),
          scrollPadding_l(tailwind_config),
          scrollSnapAlign(tailwind_config),
          scrollSnapStop(tailwind_config),
          scrollSnapType(tailwind_config),
          scrollSnapStrictness(tailwind_config),
          touchAction(tailwind_config),
          userSelect(tailwind_config),
          willChange(tailwind_config) {};

    Propriety accentColor;
    Propriety appearance;
    Propriety cursor;
    Propriety caretColor;
    Propriety pointerEvents;
    Propriety resize;
    Propriety scrollBehavior;
    Propriety scrollMargin;
    Propriety scrollMargin_x;
    Propriety scrollMargin_y;
    Propriety scrollMargin_s;
    Propriety scrollMargin_e;
    Propriety scrollMargin_t;
    Propriety scrollMargin_b;
    Propriety scrollMargin_r;
    Propriety scrollMargin_l;
    Propriety scrollPadding;
    Propriety scrollPadding_x;
    Propriety scrollPadding_y;
    Propriety scrollPadding_s;
    Propriety scrollPadding_e;
    Propriety scrollPadding_t;
    Propriety scrollPadding_b;
    Propriety scrollPadding_r;
    Propriety scrollPadding_l;
    Propriety scrollSnapAlign;
    Propriety scrollSnapStop;
    Propriety scrollSnapType;
    Propriety scrollSnapStrictness;
    Propriety touchAction;
    Propriety userSelect;
    Propriety willChange;

    void setScrollMargin(tinyxml2::XMLElement *prop_node);
    void setScrollPadding(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TLayout
{
public:
    TLayout(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          aspectRatio(tailwind_config),
          container(tailwind_config),
          columns(tailwind_config),
          breakAfter(tailwind_config),
          breakBefore(tailwind_config),
          breakInside(tailwind_config),
          boxDecorationBreak(tailwind_config),
          boxSizing(tailwind_config),
          display(tailwind_config),
          floats(tailwind_config),
          clear(tailwind_config),
          isolation(tailwind_config),
          objectFit(tailwind_config),
          objectPosition(tailwind_config),
          overflow(tailwind_config),
          overflow_x(tailwind_config),
          overflow_y(tailwind_config),
          overscrollBehavior(tailwind_config),
          overscrollBehavior_x(tailwind_config),
          overscrollBehavior_y(tailwind_config),
          position(tailwind_config),
          inset(tailwind_config),
          inset_x(tailwind_config),
          inset_y(tailwind_config),
          top(tailwind_config),
          right(tailwind_config),
          bottom(tailwind_config),
          left(tailwind_config),
          visibility(tailwind_config),
          zIndex(tailwind_config) {};

    Propriety aspectRatio;
    Propriety container;
    Propriety columns;
    Propriety breakAfter;
    Propriety breakBefore;
    Propriety breakInside;
    Propriety boxDecorationBreak;
    Propriety boxSizing;
    Propriety display;
    Propriety floats;
    Propriety clear;
    Propriety isolation;
    Propriety objectFit;
    Propriety objectPosition;
    Propriety overflow;
    Propriety overflow_x;
    Propriety overflow_y;
    Propriety overscrollBehavior;
    Propriety overscrollBehavior_x;
    Propriety overscrollBehavior_y;
    Propriety position;
    Propriety inset;
    Propriety inset_x;
    Propriety inset_y;
    Propriety top;
    Propriety right;
    Propriety bottom;
    Propriety left;
    Propriety visibility;
    Propriety zIndex;

    void setOverflowProprieties(tinyxml2::XMLElement *prop_node);
    void setOverscrollBehaviorProprieties(tinyxml2::XMLElement *prop_node);
    void setInsetProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TSpacing
{
public:
    TSpacing(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          margin(tailwind_config),
          margin_x(tailwind_config),
          margin_y(tailwind_config),
          margin_s(tailwind_config),
          margin_e(tailwind_config),
          margin_t(tailwind_config),
          margin_b(tailwind_config),
          margin_r(tailwind_config),
          margin_l(tailwind_config),
          padding(tailwind_config),
          padding_x(tailwind_config),
          padding_y(tailwind_config),
          padding_s(tailwind_config),
          padding_e(tailwind_config),
          padding_t(tailwind_config),
          padding_b(tailwind_config),
          padding_r(tailwind_config),
          padding_l(tailwind_config),
          spaceBetween_x(tailwind_config),
          spaceBetween_y(tailwind_config),
          spaceXReverse(tailwind_config),
          spaceYReverse(tailwind_config) {};

    Propriety margin;
    Propriety margin_x;
    Propriety margin_y;
    Propriety margin_s;
    Propriety margin_e;
    Propriety margin_t;
    Propriety margin_b;
    Propriety margin_r;
    Propriety margin_l;
    Propriety padding;
    Propriety padding_x;
    Propriety padding_y;
    Propriety padding_s;
    Propriety padding_e;
    Propriety padding_t;
    Propriety padding_b;
    Propriety padding_r;
    Propriety padding_l;
    Propriety spaceBetween_x;
    Propriety spaceBetween_y;
    Propriety spaceXReverse;
    Propriety spaceYReverse;

    void setMarginProprieties(tinyxml2::XMLElement *prop_node);
    void setPaddingProprieties(tinyxml2::XMLElement *prop_node);
    void setSpaceBetweenProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};

class TEffects
{
public:
    TEffects(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          boxShadow(tailwind_config),
          boxShadow_inner(tailwind_config),
          boxShadowColor(tailwind_config),
          opacity(tailwind_config),
          mixBlendMode(tailwind_config),
          backgroundBlendMode(tailwind_config) {};

    Propriety boxShadow;
    Propriety boxShadow_inner;
    Propriety boxShadowColor;
    Propriety opacity;
    Propriety mixBlendMode;
    Propriety backgroundBlendMode;

    TailwindConfig *tailwind_config_;
};

class TBorders
{
public:
    TBorders(TailwindConfig *tailwind_config)
        : tailwind_config_(tailwind_config),
          borderRadius(tailwind_config),
          borderRadius_s(tailwind_config),
          borderRadius_e(tailwind_config),
          borderRadius_t(tailwind_config),
          borderRadius_r(tailwind_config),
          borderRadius_b(tailwind_config),
          borderRadius_l(tailwind_config),
          borderRadius_ss(tailwind_config),
          borderRadius_se(tailwind_config),
          borderRadius_ee(tailwind_config),
          borderRadius_es(tailwind_config),
          borderRadius_tl(tailwind_config),
          borderRadius_tr(tailwind_config),
          borderRadius_br(tailwind_config),
          borderRadius_bl(tailwind_config),
          borderWidth(tailwind_config),
          borderWidth_x(tailwind_config),
          borderWidth_y(tailwind_config),
          borderWidth_s(tailwind_config),
          borderWidth_e(tailwind_config),
          borderWidth_t(tailwind_config),
          borderWidth_r(tailwind_config),
          borderWidth_b(tailwind_config),
          borderWidth_l(tailwind_config),
          borderColor(tailwind_config),
          borderStyle(tailwind_config),
          divideWidth_x(tailwind_config),
          divideWidth_y(tailwind_config),
          divideXReverse(tailwind_config),
          divideYReverse(tailwind_config),
          divideColor(tailwind_config),
          divideStyle(tailwind_config),
          outlineWidth(tailwind_config),
          outlineColor(tailwind_config),
          outlineStyle(tailwind_config),
          outlineOffset(tailwind_config),
          ringWidth(tailwind_config),
          ringInset(tailwind_config),
          ringColor(tailwind_config),
          ringOffsetWidth(tailwind_config),
          ringOffsetColor(tailwind_config) {};

    Propriety borderRadius;
    Propriety borderRadius_s;
    Propriety borderRadius_e;
    Propriety borderRadius_t;
    Propriety borderRadius_r;
    Propriety borderRadius_b;
    Propriety borderRadius_l;
    Propriety borderRadius_ss;
    Propriety borderRadius_se;
    Propriety borderRadius_ee;
    Propriety borderRadius_es;
    Propriety borderRadius_tl;
    Propriety borderRadius_tr;
    Propriety borderRadius_br;
    Propriety borderRadius_bl;

    Propriety borderWidth;
    Propriety borderWidth_x;
    Propriety borderWidth_y;
    Propriety borderWidth_s;
    Propriety borderWidth_e;
    Propriety borderWidth_t;
    Propriety borderWidth_r;
    Propriety borderWidth_b;
    Propriety borderWidth_l;

    Propriety borderColor;
    Propriety borderStyle;

    Propriety divideWidth_x;
    Propriety divideWidth_y;

    Propriety divideXReverse;
    Propriety divideYReverse;
    Propriety divideColor;
    Propriety divideStyle;
    Propriety outlineWidth;
    Propriety outlineColor;
    Propriety outlineStyle;
    Propriety outlineOffset;
    Propriety ringWidth;
    Propriety ringInset;
    Propriety ringColor;
    Propriety ringOffsetWidth;
    Propriety ringOffsetColor;

    void setBorderRadiusProprieties(tinyxml2::XMLElement *prop_node);
    void setBorderWidthProprieties(tinyxml2::XMLElement *prop_node);
    void setDivideWidthProprieties(tinyxml2::XMLElement *prop_node);

    TailwindConfig *tailwind_config_;
};