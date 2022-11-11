#ifndef LABEL_DECORATOR_H_
#define LABEL_DECORATOR_H_

#include <string>

#include "label_provider.h"

template <typename T>
class DirtyLabelProvider : public LabelProvider<T> {
 private:
  const LabelProvider<T>* provider_;

 public:
  DirtyLabelProvider(const LabelProvider<T>& provider_)
      : provider_(&provider_) {}

  auto LableOf(const T& obj) const -> std::string {
    return "*" + provider_->LableOf(obj);
  }
};

template <typename T>
class QuoteLabelProvider : public LabelProvider<T> {
 private:
  const LabelProvider<T>* provider_;

 public:
  QuoteLabelProvider(const LabelProvider<T>& provider_)
      : provider_(&provider_) {}

  auto LableOf(const T& obj) const -> std::string {
    return "\"" + provider_->LableOf(obj) + "\"";
  }
};

#endif