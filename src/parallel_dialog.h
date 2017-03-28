#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>

class ParallelDialog : public QDialog {
public:
  ParallelDialog() {
    parallel_height_label = new QLabel("Height:");
    parallel_height = new QLineEdit;

    done_button = new QPushButton("Done", this);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    QHBoxLayout* parallel_height_layout = new QHBoxLayout;
    parallel_height_layout->addWidget(parallel_height_label);
    parallel_height_layout->addWidget(parallel_height);
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(parallel_height_layout);

    layout->addWidget(done_button);
    
    setLayout(layout);
  }

  double defined_height() const {
    std::string fstr = parallel_height->text().toUtf8().constData();

    return std::stof(fstr);
  }

private slots:

private:
  QLabel* parallel_height_label;
  QLineEdit* parallel_height;

  QPushButton* done_button;
  
};

