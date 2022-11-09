#include "ui_sys/label_decorator.h"

template <class T>
auto DirtyLabelProvider<T>::LableOf(const T& obj) -> std::string {
  return "*" + provider_->LableOf(obj);
}