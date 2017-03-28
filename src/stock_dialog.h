#pragma once

#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>
#include <QRadioButton>

class StockDialog : public QDialog {
public:
  StockDialog() {
    stock_length = new QLineEdit;
    stock_width = new QLineEdit;
    stock_height = new QLineEdit;

    done_button = new QPushButton("Done", this);

    material_group = new QGroupBox();

    QRadioButton *radio1 = new QRadioButton(tr("&Aluminum"));
    QRadioButton *radio2 = new QRadioButton(tr("R&Brass"));
    QRadioButton *radio3 = new QRadioButton(tr("Ra&Acetal"));

    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    material_group->setLayout(vbox);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stock_length);
    layout->addWidget(stock_width);
    layout->addWidget(stock_height);
    layout->addWidget(done_button);
    layout->addWidget(material_group);
    
    setLayout(layout);
  }

  gca::workpiece defined_stock() const {
    std::string lstr = stock_length->text().toUtf8().constData();
    double l = std::stof(lstr);

    std::string wstr = stock_width->text().toUtf8().constData();
    double w = std::stof(wstr);

    std::string hstr = stock_height->text().toUtf8().constData();
    double h = std::stof(hstr);

    return gca::workpiece(l, w, h, gca::ALUMINUM);
  }

private slots:

private:
  QLineEdit* stock_length;
  QLineEdit* stock_width;
  QLineEdit* stock_height;

  QPushButton* done_button;

  QGroupBox* material_group;
  
};

