namespace lumina {

VLayoutChans::VLayoutChans(VLayoutChannel chan) {
  m_chans.set(static_cast<int>(chan));
}

VLayoutChans VLayoutChans::operator|(VLayoutChannel chan) {
  VLayoutChans out(*this);
  out.m_chans.set(static_cast<int>(chan));
  return out;
}

bool VLayoutChans::operator&(VLayoutChannel chan) {
  return m_chans.test(static_cast<int>(chan));
}


int VLayoutChans::count() const {
  return m_chans.count();
}

VLayoutChans operator|(VLayoutChannel a, VLayoutChannel b) {
  return VLayoutChans(a) | b;
}

}