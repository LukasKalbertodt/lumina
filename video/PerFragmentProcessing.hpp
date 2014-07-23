#pragma once

#include "Program.fpp"
#include "../util/NotCloneable.hpp"

namespace lumina {

enum class DepthFunction {
  Never, Less, Equal, Lequal, Greater, NotEqual, Gequal, Always
};

class PerFragmentProcessing : public NotCopyable {
public:
  PerFragmentProcessing();

  void enableDepthTest(bool enable = true);
  void enableDepthWrite(bool enable = true);
  void setDepthFunction(DepthFunction func);


private:
  bool m_depthEnabled;
  bool m_depthWrite;
  DepthFunction m_depthFunc;


  void bindStage();
  void unbindStage();

  friend Program;
};

}

#include "PerFragmentProcessing.tpp"