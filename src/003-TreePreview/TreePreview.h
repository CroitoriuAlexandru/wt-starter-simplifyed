#pragma once
#include <Wt/WContainerWidget.h>

class Stylus;
class XMLBrain;

class TreePreview : public Wt::WContainerWidget
{
public:
    TreePreview(std::shared_ptr<Stylus> stylus);

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain = nullptr);

private:
    std::shared_ptr<Stylus> stylus_;
};