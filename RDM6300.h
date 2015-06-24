/*
  RFID RDM6300 data decoder library
  (c) Stephane Driussi 20150623
  Not for commercial use

  Refer to rdm6300_decoder_wiring.jpg diagram for proper connection

*/

#ifndef RDM6300_H
#define RDM6300_H

#include <RDM6300.h>

class RDM6300 {
    public:
        bool decode(uint8_t input);
        RDM6300(uint8_t Data[]);
        uint8_t *_Payload; // used for read comparisons
    private:
        int _seq, _cnt;
        bool _new;
        uint8_t _temp, _checksum;
};

#endif

