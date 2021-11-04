#ifndef EMITFROMEVENTS_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define EMITFROMEVENTS_H_62B23520_7C8E_11DE_8A39_0800200C9A66

#if defined(_MSC_VER) ||                                            \
    (defined(__GNUC__) && (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || \
     (__GNUC__ >= 4))  // GCC supports "pragma once" correctly since 3.4
#pragma once
#endif

#include <stack>

#include "anchor.h"
#include "emitterstyle.h"
#include "eventhandler.h"

namespace YAML {
struct Mark;
}  // namespace YAML

namespace YAML {
class Emitter;

class EmitFromEvents : public EventHandler {
 public:
  EmitFromEvents(Emitter& emitter);

  void OnDocumentStart(const Mark& mark) override;
  void OnDocumentEnd() override;

  void OnNull(const Mark& mark, anchor_t anchor) override;
  void OnAlias(const Mark& mark, anchor_t anchor) override;
  void OnScalar(const Mark& mark, const std::string& tag,
                        anchor_t anchor, const std::string& value) override;

  void OnSequenceStart(const Mark& mark, const std::string& tag,
                               anchor_t anchor, EmitterStyle style) override;
  void OnSequenceEnd() override;

  void OnMapStart(const Mark& mark, const std::string& tag,
                          anchor_t anchor, EmitterStyle style) override;
  void OnMapEnd() override;

 private:
  void BeginNode();
  void EmitProps(const std::string& tag, anchor_t anchor);

 private:
  Emitter& m_emitter;

  enum class State {WaitingForSequenceEntry, WaitingForKey, WaitingForValue};
  std::stack<State> m_stateStack;
};
}

#endif  // EMITFROMEVENTS_H_62B23520_7C8E_11DE_8A39_0800200C9A66
