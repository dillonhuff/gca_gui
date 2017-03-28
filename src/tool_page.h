#pragma once

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>

#include "backend/tool.h"

class ToolWizard : public QDialog {
public:
  ToolWizard() {
    tool_cut_diameter_label = new QLabel("Cut diameter:");
    tool_cut_length_label = new QLabel;

    tool_shank_diameter_label = new QLabel;
    tool_shank_length_label = new QLabel;

    tool_holder_diameter_label = new QLabel;
    tool_holder_length_label = new QLabel;

    tool_cut_diameter = new QLineEdit;
    tool_cut_length = new QLineEdit;

    tool_shank_diameter = new QLineEdit;
    tool_shank_length = new QLineEdit;

    tool_holder_diameter = new QLineEdit;
    tool_holder_length = new QLineEdit;

    done_button = new QPushButton("Done", this);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    material_group = new QGroupBox();

    hss_check = new QRadioButton(tr("&HSS"));
    carbide_check = new QRadioButton(tr("&Carbide"));

    hss_check->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(hss_check);
    vbox->addWidget(carbide_check);
    vbox->addStretch(1);
    material_group->setLayout(vbox);
    
    tool_type_group = new QGroupBox();

    flat_check = new QRadioButton(tr("&Flat nosed"));    
    ball_check = new QRadioButton(tr("&Ball nosed"));

    flat_check->setChecked(true);

    QVBoxLayout *ttb = new QVBoxLayout;
    ttb->addWidget(flat_check);
    ttb->addWidget(ball_check);
    ttb->addStretch(1);
    tool_type_group->setLayout(ttb);
    
    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout* cut_diam_layout = new QHBoxLayout;
    cut_diam_layout->addWidget(tool_cut_diameter_label);
    cut_diam_layout->addWidget(tool_cut_diameter);

    layout->addLayout(cut_diam_layout);
    //layout->addWidget(tool_cut_diameter);
    layout->addWidget(tool_cut_length);

    layout->addWidget(tool_shank_diameter);
    layout->addWidget(tool_shank_length);

    layout->addWidget(tool_holder_diameter);
    layout->addWidget(tool_holder_length);

    layout->addWidget(tool_type_group);
    layout->addWidget(material_group);

    layout->addWidget(done_button);
    
    setLayout(layout);
  }

  gca::material read_material() const {
    if (hss_check->isChecked()) {
      return gca::HSS;
    }

    return gca::CARBIDE;
  }

  gca::tool_type read_tool_type() const {
    if (flat_check->isChecked()) {
      return gca::FLAT_NOSE;
    }

    return gca::BALL_NOSE;
  }
  
  gca::tool defined_tool() const {
    gca::tool t4{1.5, 3.94, 4, read_material(), read_tool_type()}; //gca::FLAT_NOSE};

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
  QLabel* tool_cut_diameter_label;
  QLabel* tool_cut_length_label;

  QLabel* tool_shank_diameter_label;
  QLabel* tool_shank_length_label;

  QLabel* tool_holder_diameter_label;
  QLabel* tool_holder_length_label;

  QLineEdit* tool_cut_diameter;
  QLineEdit* tool_cut_length;

  QLineEdit* tool_shank_diameter;
  QLineEdit* tool_shank_length;

  QLineEdit* tool_holder_diameter;
  QLineEdit* tool_holder_length;

  QPushButton* done_button;

  QGroupBox* material_group;

  QRadioButton* hss_check;
  QRadioButton* carbide_check;

  QGroupBox* tool_type_group;

  QRadioButton* flat_check;
  QRadioButton* ball_check;
  
};

