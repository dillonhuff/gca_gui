#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>

#include "backend/tool.h"

class ToolPage : public QWizardPage
{
    Q_OBJECT

public:
    ToolPage(QWidget *parent = 0)
      : QWizardPage(parent) {
      setTitle(tr("Toolduction"));

      tool_cut_diameter = new QLineEdit;
      QVBoxLayout *layout = new QVBoxLayout;
      layout->addWidget(tool_cut_diameter);
      setLayout(layout);
    }
  
private:
  QLineEdit* tool_cut_diameter;

};


class ToolWizard : public QDialog {
public:
  ToolWizard() {
    tool_cut_diameter = new QLineEdit;
    tool_cut_length = new QLineEdit;

    tool_shank_diameter = new QLineEdit;
    tool_shank_length = new QLineEdit;

    tool_holder_diameter = new QLineEdit;
    tool_holder_length = new QLineEdit;

    done_button = new QPushButton("Done", this);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tool_cut_diameter);
    layout->addWidget(tool_cut_length);

    layout->addWidget(tool_shank_diameter);
    layout->addWidget(tool_shank_length);

    layout->addWidget(tool_holder_diameter);
    layout->addWidget(tool_holder_length);

    layout->addWidget(done_button);
    
    setLayout(layout);
  }

  gca::tool defined_tool() const {
    gca::tool t4{1.5, 3.94, 4, gca::HSS, gca::FLAT_NOSE};

    std::string fstr = tool_cut_diameter->text().toUtf8().constData();
    t4.set_cut_diameter(std::stof(fstr));

    std::string cut_str = tool_cut_diameter->text().toUtf8().constData();
    t4.set_cut_length(std::stof(cut_str));

    t4.set_shank_diameter(0.5);
    t4.set_shank_length(0.05);

    t4.set_holder_diameter(2.5);
    t4.set_holder_length(3.5);

    return t4;
  }

private slots:

private:
  QLineEdit* tool_cut_diameter;
  QLineEdit* tool_cut_length;

  QLineEdit* tool_shank_diameter;
  QLineEdit* tool_shank_length;

  QLineEdit* tool_holder_diameter;
  QLineEdit* tool_holder_length;

  QPushButton* done_button;
  
};

