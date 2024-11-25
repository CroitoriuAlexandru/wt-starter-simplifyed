#include "101-Stylus/TCategory/BasePanel.h"
#include "101-Stylus/Tailwind/TailwindConfig.h"

#include <Wt/WApplication.h>

BasePanel::BasePanel(TailwindConfig *tailwind_config, Wt::WContainerWidget *extra_widgets_wrapper, RIGHT_PANEL_MODE mode)
	: tailwind_config_(tailwind_config), extra_widgets_wrapper_(extra_widgets_wrapper), panel_mode_(mode)
{
	setStyleClass("z-10");

	headerWidget = addWidget(std::make_unique<Wt::WContainerWidget>());
	centralWidget = addWidget(std::make_unique<Wt::WContainerWidget>());
	title = headerWidget->addWidget(std::make_unique<Wt::WText>("Title"));
	extraButtonsWidget = headerWidget->addWidget(std::make_unique<Wt::WContainerWidget>());
	extraButtonsWidget->setStyleClass("flex items-center space-x-1");

	link_classes = "hover:text-blue-700 hover:underline text-blue-400 text-start";
	wrapper_classes = "flex whitespace-nowrap justify-between items-center";

	setStyleClass("h-fit !w-full border border-solid border-neutral-500 bg-neutral-100");
	title->setStyleClass("text-sm text-gray-500 grow italic font-bold pl-4 text-nowrap");
	// headerWidget->setStyleClass("flex items-center min-w-full w-full border-b border-solid border-neutral-300 bg-neutral-200 rounded-t-md");
	headerWidget->setStyleClass("flex items-center min-w-full w-full border-b border-solid border-gray-300 bg-gray-900");
	// centralWidget->setStyleClass("w-full min-w-full pl-1");
	centralWidget->setStyleClass("w-full min-w-full pl-1 bg-gray-800");
	// // popup widget
	// {
	// 	auto popupMenu = std::make_unique<Wt::WPopupMenu>();
	// 	std::string menuItemsStyles = "p-2 m-1 hover:bg-neutral-800 hover:text-neutral-200";
	// 	popupMenu->addItem("set test classes")->setStyleClass(menuItemsStyles);
	// 	popupMenu->addItem("reset styles")->setStyleClass(menuItemsStyles);
	// 	popupMenu->addSeparator()->setStyleClass("border border-solid border-neutral-900");
	// 	// popupMenu->setAutoHide(true);

	// 	popupMenu->setStyleClass("bg-neutral-700 text-neutral-200 border border-solid border-neutral-900 z-50");

	// 	popupMenu->triggered().connect(this, [=](Wt::WMenuItem *item) {
	// 		if(item->text().toUTF8().compare("set test classes") == 0){
	// 			setCustomTestValues();
	// 			styleChanged_.emit(getStyles());
	// 		}else if(item->text().toUTF8().compare("reset styles") == 0){
	// 			resetStyles();
	// 			styleChanged_.emit(getStyles());
	// 		}
	// 	});

	// 	auto popupBtn = titleBarWidget()->addWidget(std::make_unique<Wt::WPushButton>());
	// 	popupBtn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/hamburger.svg)] !ml-auto mr-2");
	// 	popupBtn->setMenu(std::move(popupMenu));
	// 	// prevent the click event from propagating to the parent because it is located in the title bar witch expands and collapse on click
	// 	popupBtn->clicked().preventPropagation();
	// 	popupBtn->clicked().connect(this, [=] {
	// 		popupBtn->menu()->popup(popupBtn, Wt::Orientation::Vertical);
	// 	});
	// }

	auto test_btn = headerWidget->addWidget(std::make_unique<Wt::WPushButton>(tr("stylus-svg-brush"), Wt::TextFormat::XHTML));
	// test_btn->setStyleClass("p-3 bg-cover bg-[url(resources/icons/pencil.svg)] !ml-auto");
	test_btn->setStyleClass("ml-auto");
	test_btn->clicked().connect(this, [=]
								{
		setCustomTestValues();
		styleChanged_.emit(getStyles()); });

	auto reset_btn = headerWidget->addWidget(std::make_unique<Wt::WPushButton>(tr("stylus-svg-refresh"), Wt::TextFormat::XHTML));
	reset_btn->clicked().preventPropagation();
	test_btn->clicked().preventPropagation();
	reset_btn->clicked().connect(this, [=]
								 {
		resetStyles();
		styleChanged_.emit(getStyles()); });
}
void BasePanel::setClasses(std::map<std::string, std::string> classes_data_map)
{
	for (const auto &[key, value] : classes_data_map)
	{
		setDisplayWidgets(key, value);
	}
	if (panel_mode_ == RIGHT_PANEL_MODE::NORMAL)
	{
		show();
		extra_widgets_wrapper_->hide();
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::EXTRA)
	{
		hide();
		extra_widgets_wrapper_->show();
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::BOTH)
	{
		show();
		extra_widgets_wrapper_->show();
	}
	if (getStyles().compare("") == 0)
	{
		extra_widgets_wrapper_->hide();
	}
}

std::unique_ptr<Wt::WAnchor> BasePanel::createAnchorToDocs(std::string link, std::string text)
{
	Wt::WLink link_ = Wt::WLink(Wt::LinkType::Url, link);
	link_.setTarget(Wt::LinkTarget::NewWindow);

	auto linkToDocs = std::make_unique<Wt::WAnchor>(link_, text);
	linkToDocs->setStyleClass(link_classes);

	linkToDocs->setCanReceiveFocus(false);
	linkToDocs->setTabIndex(-1);

	return linkToDocs;
}

void BasePanel::resetStyles()
{
	for (auto &[key, value] : classes_data_map_)
	{
		classes_data_map_[key] = "none";
	}
}

Wt::WCheckBox *BasePanel::addToggler(Wt::WWidget *widget, std::string label_text)
{
	auto return_checkbox = extraButtonsWidget->addWidget(std::make_unique<Wt::WCheckBox>());
	auto toggler_label = extraButtonsWidget->addWidget(std::make_unique<Wt::WLabel>(label_text));
	toggler_label->setBuddy(return_checkbox);
	return_checkbox->setStyleClass("peer/a" + return_checkbox->id() + "z hidden");
	toggler_label->setStyleClass("px-1.5 text-gray-200 rounded-lg peer-checked/a" + return_checkbox->id() + "z:bg-gray-700 ");

	return_checkbox->changed().connect(this, [=]()
									   {
		if(return_checkbox->checkState() == Wt::CheckState::Checked){
			widget->show();
			// widget->animateShow(Wt::WAnimation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::Linear, 250));
		}else{
			widget->hide();
			// widget->animateHide(Wt::WAnimation(Wt::AnimationEffect::SlideInFromTop, Wt::TimingFunction::Linear, 250));
		} });

	return return_checkbox;
}

std::string BasePanel::getStyles()
{
	std::string styles = "";

	for (const auto &[key, value] : classes_data_map_)
	{
		if (value.compare("none") != 0)
		{
			styles.append(value + " ");
		}
	}

	return styles;
}

void BasePanel::setPanelMode(RIGHT_PANEL_MODE mode)
{
	panel_mode_ = mode;
	if (panel_mode_ == RIGHT_PANEL_MODE::NORMAL)
	{
		show();
		extra_widgets_wrapper_->hide();
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::EXTRA)
	{
		hide();
		extra_widgets_wrapper_->show();
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::BOTH)
	{
		show();
		extra_widgets_wrapper_->show();
	}
	setClasses(classes_data_map_);
}

void BasePanel::setExtraWidgets(std::map<std::string, Propriety> classes_vec_map)
{
	for (auto &[key, value] : classes_vec_map)
	{
		std::vector<std::string> classes_vec = value.getClasses();
		if (value.getClasses().size() > 1)
		{
			std::reverse(classes_vec.begin() + 1, classes_vec.end());
		}
		auto wrapper = extra_widgets_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
		wrapper->setStyleClass("flex items-center w-fit");
		if (colors_map_[key])
		{
			extra_colors_map_[key] = wrapper->addWidget(std::make_unique<ColorsWidget>(value));
			extra_colors_map_[key]->setCustomValueString(value.class_name + "-");
			extra_colors_map_[key]->classChanged().connect(this, [=](std::string className)
														   {
				classes_data_map_[key] = className;
				styleChanged_.emit(getStyles()); });
			if (value.custom_value)
				extra_colors_map_[key]->setCustomValueString(value.class_name + "-");
			extra_colors_map_[key]->colors_group->button(0)->hide();
			wrapper->addStyleClass("w-full justify-center");
		}
		else
		{

			extra_combobox_map_[key] = wrapper->addWidget(std::make_unique<ComboBoxClassChanger>(std::vector<std::string>(classes_vec.begin() + 1, classes_vec.end())));
			extra_combobox_map_[key]->classChanged().connect(this, [=](std::string className)
															 {
				classes_data_map_[key] = className;
				styleChanged_.emit(getStyles()); });
			if (value.custom_value)
				extra_combobox_map_[key]->setCustomValueString(value.class_name + "-");
		}
	}
}

void BasePanel::setDisplayWidgets(std::string key, std::string value)
{
	classes_data_map_[key] = value;
	if (panel_mode_ == RIGHT_PANEL_MODE::NORMAL)
	{
		if (combobox_map_[key])
			combobox_map_[key]->setValue(value);
		else if (colors_map_[key])
			colors_map_[key]->setValue(value);
		else if (checkbox_map_[key])
			checkbox_map_[key]->setChecked(value.compare("none") != 0);
		else if (selectionbox_map_[key])
			selectionbox_map_[key]->setValue(value);
		else
			std::cout << "\n\n\n NORMAL something wrong is happening here key :" << key << " value :" << value << " \n\n\n\n";
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::EXTRA)
	{
		if (extra_combobox_map_[key])
			extra_combobox_map_[key]->setValue(value);
		else if (extra_colors_map_[key])
			extra_colors_map_[key]->setValue(value);
		else
			std::cout << "\n\n\n EXTRA something wrong is happening here key :" << key << " value :" << value << " \n\n\n\n";
	}
	else if (panel_mode_ == RIGHT_PANEL_MODE::BOTH)
	{
		if (combobox_map_[key])
			combobox_map_[key]->setValue(value);
		else if (colors_map_[key])
			colors_map_[key]->setValue(value);
		else if (checkbox_map_[key])
			checkbox_map_[key]->setChecked(value.compare("none") != 0);
		else if (selectionbox_map_[key])
			selectionbox_map_[key]->setValue(value);
		else
			std::cout << "\n\n\n BOTH something wrong is happening here key :" << key << " value :" << value << " \n\n\n\n";

		if (extra_combobox_map_[key])
			extra_combobox_map_[key]->setValue(value);
		else if (extra_colors_map_[key])
			extra_colors_map_[key]->setValue(value);
		else
			std::cout << "\n\n\n EXTRA something wrong is happening here key :" << key << " value :" << value << " \n\n\n\n";
	}

	if (value.compare("none") == 0)
	{
		if (extra_combobox_map_[key])
			extra_combobox_map_[key]->parent()->hide();
		else if (extra_colors_map_[key])
			extra_colors_map_[key]->parent()->hide();
	}
	else
	{
		if (extra_combobox_map_[key])
			extra_combobox_map_[key]->parent()->show();
		else if (extra_colors_map_[key])
			extra_colors_map_[key]->parent()->show();
	}
}
