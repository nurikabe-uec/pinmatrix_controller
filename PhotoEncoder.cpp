#include "PhotoEncoder.h"

PhotoEncoder::PhotoEncoder(){
  PhotoEncoder(0);
}

PhotoEncoder::PhotoEncoder(unsigned long t){
  this -> value = 0;
  this -> state = NO_ROTATION;
  this -> countTime = t;
}

void PhotoEncoder::Count(unsigned long t) {
  if (state == FORWARD_ROTATION && (t - countTime) > 10) {
    value++;
    this -> countTime = t;
  } else if (state == REVERSE_ROTATION && (t - countTime) > 10) {
    value--;
    this -> countTime = t;
  }
  return;
}

void PhotoEncoder::SetState(State state) {
  this -> state = state;
  return;
}
