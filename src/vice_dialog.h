#pragma once



#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWizardPage>
#include <QDialog>

#include "backend/tool.h"
#include "synthesis/vice.h"

namespace gca {

  class ViceDialog : public QDialog {
  public:
    ViceDialog() {

      done_button = new QPushButton("Done", this);

      connect(done_button, SIGNAL(clicked()), this, SLOT(accept()));

      vice_group = new QGroupBox();

      emco_2in = new QRadioButton(tr("&Emco 2in"));
      emco_6in = new QRadioButton(tr("&Emco 6in"));

      emco_2in->setChecked(true);

      QVBoxLayout *vbox = new QVBoxLayout;
      vbox->addWidget(emco_2in);
      vbox->addWidget(emco_6in);
      vbox->addStretch(1);
      vice_group->setLayout(vbox);

      QVBoxLayout* layout = new QVBoxLayout;
      layout->addWidget(vice_group);

      layout->addWidget(done_button);
      setLayout(layout);
    }

    gca::vice selected_vice() const {
      if (emco_2in->isChecked()) {
	vice test_v = current_setup();
	vice test_vice = top_jaw_origin_vice(test_v);
	return test_vice;
      }

      vice test_v = custom_jaw_vice(6.0, 1.5, 10.0, point(0.0, 0.0, 0.0));

      return top_jaw_origin_vice(test_v);
    }
  
  private slots:

  private:

    QPushButton* done_button;

    QGroupBox* vice_group;

    QRadioButton* emco_2in;
    QRadioButton* emco_6in;
  
  };
  
}
