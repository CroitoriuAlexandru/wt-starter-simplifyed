#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class TemplateFolder;
class TemplateFile;
class XmlTemplate;

enum class PreviewPanel
{
  Main = 10,
  one = 11,
  two = 12,
  three = 13,
};

class PreviewDisplaySelected
{
public:
  PreviewPanel preview_panel;
  dbo::ptr<XmlTemplate> xml_template;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, preview_panel, "preview_panel");
    dbo::belongsTo(a, xml_template, "xml_template");
  }
};

class XmlTemplate
{
public:
  Wt::WString temp_id;
  Wt::WString xml_temp;
  dbo::ptr<TemplateFile> template_files;
  dbo::weak_ptr<PreviewDisplaySelected> preview_display_selected;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, temp_id, "temp_id");
    dbo::field(a, xml_temp, "xml_temp");
    dbo::belongsTo(a, template_files, "template_file"); // many-to-one relationship
    dbo::hasOne(a, preview_display_selected);
  }
};

class TemplateFile
{
public:
  Wt::WString file_name;
  dbo::collection<dbo::ptr<XmlTemplate>> xml_templates;
  dbo::ptr<TemplateFolder> template_folder;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, file_name, "file_name");
    dbo::hasMany(a, xml_templates, dbo::ManyToOne, "template_file"); // one-to-many relationship
    dbo::belongsTo(a, template_folder, "template_folder");
  }
};

class TemplateFolder
{
public:
  Wt::WString folder_name;
  dbo::collection<dbo::ptr<TemplateFile>> template_files;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, folder_name, "folder_name");
    dbo::hasMany(a, template_files, dbo::ManyToOne, "template_folder"); // one-to-many relationship
  }
};
