#pragma once

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>
#include <QRadioButton>

class StockDialog : public QDialog {
public:
  StockDialog() {
    stock_length_label = new QLabel("Length:");
    stock_width_label = new QLabel("Width:");
    stock_height_label = new QLabel("Height:");

    stock_length = new QLineEdit;
    stock_width = new QLineEdit;
    stock_height = new QLineEdit;

    QHBoxLayout* stock_length_layout = new QHBoxLayout;
    stock_length_layout->addWidget(stock_length_label);
    stock_length_layout->addWidget(stock_length);

    QHBoxLayout* stock_width_layout = new QHBoxLayout;
    stock_width_layout->addWidget(stock_width_label);
    stock_width_layout->addWidget(stock_width);

    QHBoxLayout* stock_height_layout = new QHBoxLayout;
    stock_height_layout->addWidget(stock_height_label);
    stock_height_layout->addWidget(stock_height);
    
    done_button = new QPushButton("Done", this);

    material_group = new QGroupBox();

    aluminum_check = new QRadioButton(tr("&Aluminum"));
    brass_check = new QRadioButton(tr("&Brass"));
    acetal_check = new QRadioButton(tr("&Acetal"));

    aluminum_check->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(aluminum_check);
    vbox->addWidget(brass_check);
    vbox->addWidget(acetal_check);
    vbox->addStretch(1);
    material_group->setLayout(vbox);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(stock_length_layout);
    layout->addLayout(stock_width_layout);
    layout->addLayout(stock_height_layout);
    layout->addWidget(material_group);
    layout->addWidget(done_button);

    setLayout(layout);
  }

  gca::material read_material() const {
    if (aluminum_check->isChecked()) {
      return gca::ALUMINUM;
    }

    if (brass_check->isChecked()) {
      return gca::BRASS;
    }

    return gca::ACETAL;
  }

  gca::workpiece defined_stock() const {
    std::string lstr = stock_length->text().toUtf8().constData();
    double l = std::stof(lstr);

    std::string wstr = stock_width->text().toUtf8().constData();
    double w = std::stof(wstr);

    std::string hstr = stock_height->text().toUtf8().constData();
    double h = std::stof(hstr);

    gca::material m = read_material();
    return gca::workpiece(l, w, h, m);//gca::ALUMINUM);
  }

private slots:

private:
  QLabel* stock_length_label;
  QLabel* stock_width_label;
  QLabel* stock_height_label;

  QLineEdit* stock_length;
  QLineEdit* stock_width;
  QLineEdit* stock_height;

  QPushButton* done_button;

  QGroupBox* material_group;

  QRadioButton* aluminum_check;
  QRadioButton* brass_check;
  QRadioButton* acetal_check;
};

