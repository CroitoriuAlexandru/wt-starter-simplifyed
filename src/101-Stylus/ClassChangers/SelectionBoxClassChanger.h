#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WRadioButton.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WCheckBox.h>

#include <vector>

class SelectionBoxClassChanger : public Wt::WContainerWidget
{
public:
  SelectionBoxClassChanger(std::vector<std::string> options_vec);
  void setValue(std::string className = "none");
  std::string getValue();

  Wt::Signal<std::string> &classChanged() { return classChanged_; }

private:
  Wt::WCheckBox *checkbox_important_;
  std::shared_ptr<Wt::WButtonGroup> m_widget_group_;

  Wt::Signal<std::string> classChanged_;
};