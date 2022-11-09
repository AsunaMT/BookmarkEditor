#ifndef LABEL_DECORATOR_H_
#define LABEL_DECORATOR_H_

#include <string>

#include "label_provider.h"

template <class T>
class DirtyLabelProvider : public LabelProvider<T> {
 private:
  LabelProvider<T>* provider_;

 public:
  std::string LableOf(const T& obj);
};

#endif