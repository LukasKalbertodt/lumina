#pragma once

/******************************************************************************/

enum class LPipelineIOType {
  MeshData,
  PostVertexData,
  PreFragmentData,
  FragmentColor,
  FullTexture,
  None
};

/******************************************************************************/
template <int ID, typename T, typename... Ts>
struct LXVarCountHelper {
  using type = LXVarCountHelper<ID-1, T, Ts...>;
};
template <typename T, typename... Ts>
struct LXVarCountHelper<0, T, Ts...> {
  using type = T;
};

template <typename T, typename... Ts>
struct LXVarHelper {
  using first = T;
  using last = typename LXVarHelper<Ts...>::last;
  template <int ID>
  using at = LXVarCountHelper<ID, T, Ts...>;
};
template <typename T>
struct LXVarHelper<T> {
  using first = T;
  using last = T;
};



/******************************************************************************/
template <typename T, typename... Ts>
struct LXRenderPipelineImpl : public LXRenderPipelineImpl<Ts...> {
  LXRenderPipelineImpl(T& head, Ts&... tail)
    : LXRenderPipelineImpl<Ts...>(tail...), m_part(head) {}

  using base = LXRenderPipelineImpl<Ts...>;
  void activate() {
    m_part.activate();
    LXRenderPipelineImpl<Ts...>::activate();
  }

public:
  T& m_part;
};

template <typename T> struct LXRenderPipelineImpl<T> {
  LXRenderPipelineImpl(T& head) : m_part(head) {}

  void activate() { m_part.activate(); }
public:
  T& m_part;
};

template <int N, typename T, typename... Ts>
struct LXPipelineHelper {
  static auto getPartAt(LXRenderPipelineImpl<Ts...>& obj) 
    -> typename LXVarHelper<Ts...>::template at<N>::type {
    return LXPipelineHelper<N-1, Ts...>::
      getPartAt(static_cast<LXRenderPipelineImpl<Ts...>>(obj));
  }
};
template <typename T, typename... Ts>
struct LXPipelineHelper<0, T, Ts...> {
  static T& getPartAt(LXRenderPipelineImpl<T, Ts...>& obj) {
    return obj.m_part;
  }
};



/******************************************************************************/
template <typename... Ts>
class LRenderPipeline : public LXRenderPipelineImpl<Ts...> {
public:
  static constexpr LPipelineIOType pipelineInput
  = LXVarHelper<Ts...>::first::pipelineInput;
  static constexpr LPipelineIOType pipelineOutput
  = LXVarHelper<Ts...>::last::pipelineOutput;

  using LXRenderPipelineImpl<Ts...>::LXRenderPipelineImpl;
};