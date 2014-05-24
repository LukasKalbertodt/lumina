namespace lumina {

VLayoutChans::VLayoutChans(VChan chan) {
  m_chans.set(static_cast<int>(chan));
}

VLayoutChans VLayoutChans::operator|(VChan chan) {
  VLayoutChans out(*this);
  out.m_chans.set(static_cast<int>(chan));
  return out;
}

bool VLayoutChans::operator&(VChan chan) {
  return m_chans.test(static_cast<int>(chan));
}


int VLayoutChans::count() const {
  return m_chans.count();
}

VLayoutChans operator|(VChan a, VChan b) {
  return VLayoutChans(a) | b;
}

}