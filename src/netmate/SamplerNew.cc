
/*! \file   SamplerNew.cc

    Copyright 2003-2004 Fraunhofer Institute for Open Communication Systems (FOKUS),
                        Berlin, Germany

    This file is part of Network Measurement and Accounting System (NETMATE).

    NETMATE is free software; you can redistribute it and/or modify 
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    NETMATE is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this software; if not, write to the Free Software 
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Description:
    samples *each and every* packet

    $Id: SamplerNew.cc 748 2009-09-10 02:54:03Z szander $

*/

#include "SamplerNew.h"

SamplerNew::SamplerNew()
{
    first_pkt = 0;
    last = 0;
    pkt_count = 0;
    drop_pkt_count = 0;
}

SamplerNew::~SamplerNew()
{

}

// samples *all* packets
int SamplerNew::sample(metaData_t* pkt)
{
  unsigned long long now = 0;
  unsigned long long delta = 0;
  unsigned long long sampling_rate = 100;
  pkt_count++;
  now = pkt->tv_sec*1000000ULL + pkt->tv_usec;
  if (first_pkt == 0) {
      if (last == 0)
          last = now;
  }
  delta = now - last;
  last = now;
//  printf("Timestamp_now:%llud\n", now);
//  printf("Timestamp_last:%llud\n", last);
  printf("Timestamp:%llud\n", delta);
  if (delta < sampling_rate && delta != 0) {
//      printf("Don't Sample\n");
      printf("Drop cnt:%d\n\n", ++drop_pkt_count);
//      return 0;
  } else {
//      printf("Sample\n");
      printf("Sampled cnt:%d\n\n", pkt_count - drop_pkt_count);
//      return 1;
  }
  return 1;
}
