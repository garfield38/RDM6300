/*
  RFID RDM6300 data decoder library
  (c) Stephane Driussi 20150623
  Not for commercial use

  Refer to rdm6300_decoder_wiring.png diagram for proper connection

*/

#include <Arduino.h>
#include "RDM6300.h"

RDM6300::RDM6300(uint8_t Data[]) {
  _Payload = Data;
}

bool RDM6300::decode(uint8_t input) {
  if(input == 2) { 
    _cnt=0;
    _checksum = 0; 
    _seq = 1;
    _temp = 0;
    _new = false;
  }
  else if(_seq == 1) { 
    _temp = input - 48;
    if (_temp > 9) _temp -= 7;
    _seq = 2;
  }          // store payload in buffer
  else if(_seq == 2) {
    input -= 48;
    if (input > 9) input -= 7;
    _temp = (_temp << 4) | input;
    if (_Payload[_cnt] != _temp) _new = true;
    _Payload[_cnt++] = _temp;
    if(_cnt > 5) _seq = 3; 
    else { 
      _seq=1; 
      _checksum ^= _temp;
    }  
  }          // store payload in buffer
  else if((_seq == 3) && (input == 0x03)) { 
    _seq = 4; 
  }
  else _seq = 0;
  if (_seq == 4) // all data in buffer
  {
    _seq = 0;
    _cnt = 0;
    if (_checksum == _Payload[5]) return _new;
  }
  return false;
}
