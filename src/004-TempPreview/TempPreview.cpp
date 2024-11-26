#include "004-TempPreview/TempPreview.h"
#include "101-Stylus/Stylus.h"
#include "004-TempPreview/PNode.h"
#include "002-Dbo/Tables.h"
#include "002-Dbo/Session.h"

TempPreview::TempPreview(std::shared_ptr<Stylus> stylus)
    : stylus_(stylus)
{
    // setOffsets(450, Wt::Side::Right);
    // setOffsets(380, Wt::Side::Left);
    setStyleClass("min-h-screen h-screen max-h-screen overflow-y-none overflow-x-none relative grow-[1] flex flex-col");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);

    preview_wrapper_ = addWidget(std::make_unique<Wt::WContainerWidget>());
    stylus_->node_selected().connect([=](std::shared_ptr<XMLBrain> xml_brain)
                                     { setXmlBrain(xml_brain); });
    preview_wrapper_->setStyleClass("h-full overflow-y-auto");

    // template selection bottom panel
    auto footer_bar_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
    footer_bar_wrapper->setStyleClass("bg-gray-800 p-2 flex justify-center sticky bottom-0 w-full space-x-2");

    folder_combo_box_ = footer_bar_wrapper->addWidget(std::make_unique<Wt::WComboBox>());
    file_combo_box_ = footer_bar_wrapper->addWidget(std::make_unique<Wt::WComboBox>());
    template_combo_box_ = footer_bar_wrapper->addWidget(std::make_unique<Wt::WComboBox>());

    folder_combo_box_->setStyleClass("line-edit-stylus-edditor");
    file_combo_box_->setStyleClass("line-edit-stylus-edditor");
    template_combo_box_->setStyleClass("line-edit-stylus-edditor");

    folder_combo_box_->activated().connect([=]
                                           { setFiles(folder_combo_box_->currentText().toUTF8()); });

    file_combo_box_->activated().connect([=]
                                         { setTemplates(file_combo_box_->currentText().toUTF8()); });

    template_combo_box_->activated().connect([=]
                                             {
                                                 auto t = Wt::Dbo::Transaction(stylus_->session_);
                                                 auto xml_temp = stylus_->session_.find<XmlTemplate>().where("temp_id = ?").bind(template_combo_box_->currentText().toUTF8()).resultValue();

                                                    if (xml_temp)
                                                    {
                                                        XmlDboRecord xml_temp_obj;
                                                        xml_temp_obj.dbo_folder_id = xml_temp->template_files->template_folder.id();
                                                        xml_temp_obj.dbo_file_id = xml_temp->template_files.id();
                                                        xml_temp_obj.dbo_temp_id = xml_temp.id();
                                                        xml_temp_obj.file_name = xml_temp->template_files->file_name;
                                                        xml_temp_obj.folder_name = xml_temp->template_files->template_folder->folder_name;
                                                        xml_temp_obj.temp_id = xml_temp->temp_id;
                                                        xml_temp_obj.xml_temp = xml_temp->xml_temp;
                                                        auto xml_brain = std::make_shared<XMLBrain>(stylus_->session_, xml_temp_obj, stylus_);
                                                        xml_brain->selected_node_ = xml_brain->message_node_;
                                                        stylus_->setXmlBrain(xml_brain);
                                                    }

                                                 t.commit(); });
    template_combo_box_->clicked().connect([=]
                                           { template_combo_box_->activated().emit(template_combo_box_->currentIndex()); });
    setFolders();
}

void TempPreview::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    preview_wrapper_->clear();
    if (xml_brain)
    {
        preview_wrapper_->addWidget(std::make_unique<PNode>(xml_brain, xml_brain->message_node_));
    }
}

void TempPreview::setFolders()
{
    folder_combo_box_->clear();
    auto t = Wt::Dbo::Transaction(stylus_->session_);
    auto folders = stylus_->session_.find<TemplateFolder>().resultList();
    for (auto &folder : folders)
    {
        folder_combo_box_->addItem(folder->folder_name);
    }
    t.commit();
    setFiles(folder_combo_box_->currentText().toUTF8());
}

void TempPreview::setFiles(std::string folder_name)
{
    file_combo_box_->clear();
    auto t = Wt::Dbo::Transaction(stylus_->session_);
    auto folder = stylus_->session_.find<TemplateFolder>().where("folder_name = ?").bind(folder_name).resultValue();
    if (folder)
    {
        auto files = folder->template_files;
        for (auto &file : files)
        {
            file_combo_box_->addItem(file->file_name);
        }
    }
    t.commit();

    setTemplates(file_combo_box_->currentText().toUTF8());
}

void TempPreview::setTemplates(std::string file_name)
{
    template_combo_box_->clear();
    auto t = Wt::Dbo::Transaction(stylus_->session_);
    auto file = stylus_->session_.find<TemplateFile>().where("file_name = ?").bind(file_name).resultValue();
    if (file)
    {
        auto templates = file->xml_templates;
        for (auto &temp : templates)
        {
            template_combo_box_->addItem(temp->temp_id);
        }
    }
    t.commit();
    template_combo_box_->activated().emit(template_combo_box_->currentIndex());
}
