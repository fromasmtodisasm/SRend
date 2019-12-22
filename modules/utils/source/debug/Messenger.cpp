#include "Messenger.hpp"
#include "MessengerCallbacks.hpp"

namespace utils::debug
{
  // Messenger --------------------------------------------------------------------------------------------------------

  Messenger::Messenger(MessengerCallback callback, MessageSeverityFlags severityFilter, MessageTypeFlags typeFilter)
      : severityFilter_(severityFilter), typeFilter_(typeFilter), callback_(std::move(callback))
  {
  }

  void Messenger::report(std::string const &message, MessageSeverityFlagBits severity, MessageTypeFlags types) const
  {
    if ((severity & severityFilter_) && (types &= typeFilter_))
    {
      callback_(message, severity, types);
    }
  }

  Messenger::Messenger(MessageSeverityFlags severityFilter, MessageTypeFlags typeFilter)
      : severityFilter_(severityFilter), typeFilter_(typeFilter), callback_(messengerCallbacks::consoleDefault)
  {
  }

}  // namespace utils::debug