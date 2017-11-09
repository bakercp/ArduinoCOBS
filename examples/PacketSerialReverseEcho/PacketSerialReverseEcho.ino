//
// Copyright (c) 2012 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include <PacketSerial.h>


// The PacketSerial object.
// It cleverly wraps one of the Serial objects.
// While it is still possible to use the Serial object
// directly, it is recommended that the user let the
// PacketSerial object manage all serial communication.
// Thus the user should not call Serial.write(), etc.
// Additionally the user should not use the serialEvent()
// callbacks.
PacketSerial serial;


void setup()
{
  // We must specify a packet handler method so that
  serial.setPacketHandler(&onPacket);
  serial.begin(115200);
}


void loop()
{
  // Do other things here.

  // The update() method attempts to read in
  // any incoming serial data and emits packets via
  // the user's onPacket(const uint8_t* buffer, size_t size)
  // method registered with the setPacketHandler() method.
  //
  // The update() method should be called at the end of the loop().
  serial.update();
}

// This is our packet callback.
// The buffer is delivered already decoded.
void onPacket(const uint8_t* buffer, size_t size)
{
  // Make a temporary buffer.
  uint8_t tmp[size];

  // Copy the packet into our temporary buffer.
  memcpy(tmp, buffer, size);

  // Reverse our temporaray buffer.
  reverse(tmp, size);

  // Send the reversed buffer back.
  // The send() method will encode the buffer
  // as a packet, set packet markers, etc.
  serial.send(tmp, size);
}

/// \brief A simple array reversal method.
void reverse(uint8_t* buffer, size_t size)
{
  uint8_t tmp;

  for (int i=0; i < size / 2; i++)
  {
    tmp = buffer[i];
    buffer[i] = buffer[size-i-1];
    buffer[size-i-1] = tmp;
  }
}

