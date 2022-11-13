#ifndef LABEL_PROVIDER_H_
#define LABEL_PROVIDER_H_

#include <string>

template <typename T>
class LabelProvider {
 public:
  virtual auto LabelOf(const T& obj) const -> std::string = 0;
};

#endif