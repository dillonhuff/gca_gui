#pragma once

#include <QPushButton>

class PostProcessButton : public QPushButton {

  Q_OBJECT
  
public:
  PostProcessButton(const std::string& name,
		    const unsigned step_num) :
    QPushButton(name.c_str()), num(step_num) {}

  unsigned num;
};
