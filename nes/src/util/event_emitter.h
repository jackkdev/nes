//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#ifndef NES_NES_SRC_UTIL_EVENT_EMITTER_H_
#define NES_NES_SRC_UTIL_EVENT_EMITTER_H_

#include <string>
#include <functional>
#include <vector>
#include <map>

namespace nes {

class Event {
 public:
  virtual ~Event() = default;

  using KeyType = const char *;
  [[nodiscard]] virtual KeyType Type() const = 0;
};

class EventEmitter {
 public:
  using KeyType = const char *;
  using HandlerType = std::function<void(const Event &event)>;

 public:
  EventEmitter() = default;
  ~EventEmitter() = default;

  void Emit(const Event &event) const;
  void On(KeyType key, const HandlerType &handler);

 private:
  std::map<KeyType, std::vector<HandlerType>> handlers_;
};

}

#endif //NES_NES_SRC_UTIL_EVENT_EMITTER_H_
