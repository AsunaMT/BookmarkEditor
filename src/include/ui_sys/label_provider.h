#ifndef LABEL_PROVIDER_H_
#define LABEL_PROVIDER_H_

#include <string>

template <class T>
class LabelProvider {
 public:
  virtual auto LableOf(const T& obj) -> std::string = 0;
};

#endif