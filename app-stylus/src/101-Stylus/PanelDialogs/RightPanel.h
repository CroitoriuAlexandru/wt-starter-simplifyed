#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"

#include "101-Stylus/TCategory/AccesibilityP.h"
#include "101-Stylus/TCategory/BackgroundP.h"
#include "101-Stylus/TCategory/BordersP.h"
#include "101-Stylus/TCategory/FlexAndGridP.h"
#include "101-Stylus/TCategory/SpacingP.h"
#include "101-Stylus/TCategory/SizingP.h"
#include "101-Stylus/TCategory/LayoutP.h"
#include "101-Stylus/TCategory/TypographyP.h"
#include "101-Stylus/TCategory/FiltersP.h"
#include "101-Stylus/TCategory/EffectsP.h"
#include "101-Stylus/TCategory/TablesP.h"
#include "101-Stylus/TCategory/TransitionsAndAnimationP.h"
#include "101-Stylus/TCategory/TransformsP.h"
#include "101-Stylus/TCategory/SvgP.h"
#include "101-Stylus/TCategory/InteractivityP.h"

#include <Wt/WTextArea.h>

#include <boost/regex.hpp>

class RightPanel : public BaseDialogPanel
{
public:
    RightPanel(std::shared_ptr<Stylus> stylus);

    void setPanelsMode(RIGHT_PANEL_MODE mode);
    RIGHT_PANEL_MODE panels_mode_;
    boost::regex dark_mode_regex_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> category_classes_data_map_;

    std::shared_ptr<XMLBrain> xml_brain_;
    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);

    Wt::WContainerWidget *panelsWrapper;
    FlexAndGridP *flexAndGridWidget_;
    BackgroundP *backgroundWidget_;
    SpacingP *spacingWidget_;
    SizingP *sizingWidget_;
    LayoutP *layoutWidget_;
    TypographyP *typographyWidget_;
    BordersP *bordersWidget_;
    FiltersP *filtersWidget_;
    EffectsP *effectsWidget_;
    TablesP *tablesWidget_;
    TransitionsAndAnimationP *transitionsAndAnimationWidget_;
    TransformsP *transformsWidget_;
    SvgP *svgWidget_;
    AccesibilityP *accesibilityWidget_;
    InteractivityP *interactivityWidget_;

    std::string setFlexAndGridClasses(std::string classes, std::string prefix);
    std::string setBackgroundClasses(std::string classes, std::string prefix);
    std::string setSpacingClasses(std::string classes, std::string prefix);
    std::string setSizingClasses(std::string classes, std::string prefix);
    std::string setLayoutClasses(std::string classes, std::string prefix);
    std::string setTypographyClasses(std::string classes, std::string prefix);
    std::string setBordersClasses(std::string classes, std::string prefix);
    std::string setFiltersClasses(std::string classes, std::string prefix);
    std::string setEffectsClasses(std::string classes, std::string prefix);
    std::string setTablesClasses(std::string classes, std::string prefix);
    std::string setTransitionsAndAnimationClasses(std::string classes, std::string prefix);
    std::string setTransformsClasses(std::string classes, std::string prefix);
    std::string setSvgClasses(std::string classes, std::string prefix);
    std::string setAccesibilityClasses(std::string classes, std::string prefix);
    std::string setInteractivityClasses(std::string classes, std::string prefix);

    void setStyleClasses(std::string classes);
    std::string getStyles();

    Wt::Signal<std::string> &styleChanged() { return styleChanged_; }

private:
    Wt::Signal<std::string> styleChanged_;

    std::vector<std::string> findAndRemoveMatches(boost::regex regex, std::string &str);
    std::string findAndRemoveMatche(boost::regex regex, std::string &str);

    std::string current_prefix_ = "DEFAULT";
    std::string notFoundClasses = "";
    Wt::WTextArea *not_found_classes_widget_;
    std::unordered_map<std::string, Wt::WContainerWidget *> category_wrappers_;
};