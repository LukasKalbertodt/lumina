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

  void activate() {
    m_part.activate();
    LXRenderPipelineImpl<Ts...>::activate();
  }

  template <int N>
  auto getPart()
    -> typename LXVarHelper<T, Ts...>::template at<N>::type& {
    return LXRenderPipelineImpl<Ts...>::template getPart<N - 1>();
  }

public:
  T& m_part;
};



template <typename T> struct LXRenderPipelineImpl<T> {
  LXRenderPipelineImpl(T& head) : m_part(head) {}

  void activate() { m_part.activate(); }
  template <int N>
  T& getPart() {
    static_assert(N == 0, "something went wrong...");
    return m_part;
  }

public:
  T& m_part;
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