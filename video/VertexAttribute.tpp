namespace lumina {

inline VLayoutChans::VLayoutChans(VAttr chan) {
  m_chans.set(static_cast<int>(chan));
}

inline VLayoutChans VLayoutChans::operator|(VAttr chan) {
  VLayoutChans out(*this);
  out.m_chans.set(static_cast<int>(chan));
  return out;
}

inline bool VLayoutChans::operator&(VAttr chan) {
  return m_chans.test(static_cast<int>(chan));
}


inline int VLayoutChans::count() const {
  return m_chans.count();
}

inline VLayoutChans operator|(VAttr a, VAttr b) {
  return VLayoutChans(a) | b;
}

}