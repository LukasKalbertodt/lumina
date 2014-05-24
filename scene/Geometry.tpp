namespace lumina {

template <VChan C0, VChan... Chans> 
Mesh createBox(Vec3f size) {
  Mesh out;

  int bufsize = internal::VChansHelper<C0, Chans...>::size;
  out.create(bufsize);

  out.prime<typename internal::VChanHelper<C0>::type,
            typename internal::VChanHelper<Chans>::type...>([](
    HotMesh<typename internal::VChanHelper<C0>::type,
            typename internal::VChanHelper<Chans>::type...>& hot) {
    // fill vertex buffer with corner-points

    hot.applyVertexLayout();
  });

  return out;
}

}