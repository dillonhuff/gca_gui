#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>

class ParallelDialog : public QDialog {
public:
  ParallelDialog() {
    parallel_height = new QLineEdit;

    done_button = new QPushButton("Done", this);

    connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(parallel_height);

    layout->addWidget(done_button);
    
    setLayout(layout);
  }

  double defined_height() const {
    std::string fstr = parallel_height->text().toUtf8().constData();

    return std::stof(fstr);
  }

private slots:

private:
  QLineEdit* parallel_height;

  QPushButton* done_button;
  
};

