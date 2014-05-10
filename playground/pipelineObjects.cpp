#include <iostream>
#include <type_traits>
using namespace std;

#include "LRenderPipeline.hpp"

class VertexShader {
public:
  static constexpr LPipelineIOType pipelineInput = LPipelineIOType::MeshData;
  static constexpr LPipelineIOType pipelineOutput
    = LPipelineIOType::PostVertexData;

  void activate() {
    cout << "A: VertexShader" << endl;
  }
};

class FragmentPreProcessing {
public:
  static constexpr LPipelineIOType pipelineInput
    = LPipelineIOType::PostVertexData;
  static constexpr LPipelineIOType pipelineOutput
    = LPipelineIOType::PreFragmentData;

  void activate() {
    cout << "A: FragmentPreProcessing" << endl;
  }
};

class FragmentShader {
public:
  static constexpr LPipelineIOType pipelineInput
    = LPipelineIOType::PreFragmentData;
  static constexpr LPipelineIOType pipelineOutput
    = LPipelineIOType::FragmentColor;

  void activate() {
    cout << "A: FragmentShader" << endl;
  }
};

class OutputMerger {
public:
  static constexpr LPipelineIOType pipelineInput
    = LPipelineIOType::FragmentColor;
  static constexpr LPipelineIOType pipelineOutput
    = LPipelineIOType::FullTexture;

  void activate() {
    cout << "A: OutputMerger" << endl;
  }
};

class TextureContainer {
public:
  static constexpr LPipelineIOType pipelineInput = LPipelineIOType::FullTexture;
  static constexpr LPipelineIOType pipelineOutput = LPipelineIOType::None;
};


/******************************************************************************/






template <typename Ta, typename Tb, typename... Ts>
struct checkPipeTypes : public checkPipeTypes<Tb, Ts...> {
  static_assert(Ta::pipelineOutput == Tb::pipelineInput,
    "Cannot tie pipeline: Input-Output missmatch!");
};

template <typename Ta, typename Tb>
struct checkPipeTypes<Ta, Tb> {
  static_assert(Ta::pipelineOutput == Tb::pipelineInput,
    "Cannot tie pipeline: Input-Output missmatch!");
  static constexpr bool valid = true;
};


template <typename T>
struct LXExtractPipeline {
  using type = LRenderPipeline<T>;
};
template <typename... Ts>
struct LXExtractPipeline<LRenderPipeline<Ts...>> {
  using type = LRenderPipeline<Ts...>;
};

template <typename Ta, typename Tb, typename... Ts>
struct LXMergePipelines;
template <typename... Tas, typename... Tbs, typename... Ts>
struct LXMergePipelines<LRenderPipeline<Tas...>, LRenderPipeline<Tbs...>, Ts...> {
  using type
    = typename LXMergePipelines<LRenderPipeline<Tas..., Tbs...>, Ts...>::type;
};
template <typename... Tas, typename... Tbs>
struct LXMergePipelines<LRenderPipeline<Tas...>, LRenderPipeline<Tbs...>> {
  using type = LRenderPipeline<Tas..., Tbs...>;
};

  
template <typename... Ts>
auto tiePipeline(Ts&... args)
  -> typename LXMergePipelines<typename LXExtractPipeline<Ts>::type...>::type {
  using Out
    = typename LXMergePipelines<typename LXExtractPipeline<Ts>::type...>::type;

  // checkPipeTypes<Ts...>;

   return Out(args...);
}

int main() {
  VertexShader vs;
  FragmentPreProcessing fpp;
  FragmentShader fs;
  OutputMerger om;
  TextureContainer tc;

  auto pipe = tiePipeline(vs, fpp, fs);
  LXPipelineHelper<1, VertexShader, FragmentPreProcessing, FragmentShader>::
    getPartAt(pipe).activate();
  // auto pipe2 = tiePipeline(pipe, om);
  // pipe.getPart<2>().activate();
  // pipe.getPart<1>().activate();
  // pipe.getPart<2>().activate();
  // pipe.activate();
  // cout << sizeof(pipe) << endl;
  // pipe2.activate();
  // cout << sizeof(pipe2) << endl;
}