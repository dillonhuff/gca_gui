#pragma once

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

class GCodeDialog : public QDialog {

  string text;
public:
  GCodeDialog(const std::string& s) : text(s) {
    QVBoxLayout* layout = new QVBoxLayout;
    QTextEdit* text = new QTextEdit(s.c_str());
    layout->addWidget(text);
    setLayout(layout);
  }

};
