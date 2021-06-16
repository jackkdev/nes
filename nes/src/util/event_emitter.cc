//
// Copyright (c) 2021 - jackk <jack@darkrp.sucks>, All rights reserved.
//

#include "event_emitter.h"

namespace nes {

void EventEmitter::Emit(const Event &event) const {
  auto type = event.Type();

  if (handlers_.find(type) == handlers_.end())
    return;

  auto &&handlers = handlers_.at(type);
  for (auto &&handler : handlers)
    handler(event);
}

void EventEmitter::On(EventEmitter::KeyType key, const EventEmitter::HandlerType &handler) {
  handlers_[key].push_back(handler);
}

}