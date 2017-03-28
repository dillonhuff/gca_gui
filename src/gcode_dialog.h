#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

#include "backend/gcode_generation.h"

class GCodeDialog : public QDialog {

  string text;
public:
  GCodeDialog(const gca::gcode_program& prog) {
    
    QVBoxLayout* layout = new QVBoxLayout;
    QTextEdit* text = new QTextEdit();
    for (auto& b : prog.blocks) {
      stringstream strs;
      strs << b << endl;
      text->append(strs.str().c_str());
    }
    //text->append("appended text"); //strs.str().c_str());
    layout->addWidget(text);
    setLayout(layout);
  }

};
