/**
 * PERCOM Block Tools
 *
 * pbget - get and display PERCOM block
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Released under GPL 3.0
 * See COPYING for details.
 */

#include <atari.h>
#include <string.h>
#include <stdlib.h>
#include <peekpoke.h>
#include "sio.h"
#include "conio.h"
#include "err.h"
#include "percom.h"

PercomBlock pb;
unsigned char drive_num=1;
unsigned char buf[8];

void args(char* argv[])
{
  print(argv[0]);
  print(" <drive #>\x9b");
}

int main(int argc, char* argv[])
{  
  OS.lmargn=2;

  if (_is_cmdline_dos())
    {
      // CLI DOS detected.
      if (argc<2)
	{
	  // Too few args, show help.
	  args(argv);
	  return(1);
	}
      else
	{
	  // Get drive #
	  drive_num=atoi(argv[1]);
	}
    }
  else
    {
      // DOS 2.0
      print("GET PERCOM BLOCK FOR DRIVE #(1)? ");
      get_line(buf,8);

      // Default to drive 1
      if (buf[0]==0x9b)
	drive_num=1;
      else
	drive_num=atoi(buf);
    }

  if (!percom_get(drive_num,&pb))
    {
      print("\x9b" "COULD NOT GET PERCOM BLOCK.\x9b");
      return(1);
    }

  // Display PERCOM block

  // Header
  print("\x9bPERCOM BLOCK FOR DRIVE ");
  buf[0]=drive_num+0x30;
  printc(buf);
  print("\x9b\x9b");

  print(" NUMBER OF TRACKS: ");
  itoa(pb.num_tracks,buf,10);
  print(buf);
  print("\x9b");
  
  print("        STEP RATE: ");
  itoa(pb.step_rate,buf,10);
  print(buf);
  print("\x9b");

  print("SECTORS PER TRACK: ");
  itoa(pb.sectors_per_track,buf,10);
  print(buf);
  print("\x9b");
  
  print("  NUMBER OF SIDES: ");
  itoa(pb.num_sides,buf,10);
  print(buf);
  print("\x9b");

  print("          DENSITY: ");
  if (pb.density==0)
    print("FM");
  else
    print("MFM");
  print("\x9b");
  
  print("      SECTOR SIZE: ");
  itoa(pb.sector_size,buf,10);
  print(buf);
  print("\x9b");

  print("   DRIVE SELECTED: ");
  if (pb.drive_present==1)
    print("YES");
  else
    print("NO");
  print("\x9b");
  
  print("      RESERVED #1: ");
  itoa(pb.reserved1,buf,16);
  print("$");
  print(buf);
  print("\x9b");

  print("      RESERVED #2: ");
  itoa(pb.reserved2,buf,16);
  print("$");
  print(buf);
  print("\x9b");

  print("      RESERVED #3: ");
  itoa(pb.reserved3,buf,16);
  print("$");
  print(buf);
  print("\x9b");

  return(0);
}
