/**
 * PERCOM Block tools
 *
 * pbset - Set PERCOM block
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
  print(" <#> <nt> <sr> <spt> <ns> <d> <ss> <ds> <rs1> <rs2> <rs3>\x9b\x9b");
  print("  <#>   DRIVE NUMBER\x9b");
  print("  <nt>  NUMBER OF TRACKS\x9b");
  print("  <sr>  STEP RATE\x9b");
  print("  <spt> SECTORS PER TRACK\x9b");
  print("  <ns>  NUMBER OF SIDES (1|2)\x9b");
  print("  <d>   DENSITY (0=FM|4=MFM)\x9b");
  print("  <ss>  SECTOR SIZE (128|256|512)\x9b");
  print("  <ds>  DRIVE SELECTED? (0|1)\x9b");
  print("  <rs1> RESERVED 1\x9b");
  print("  <rs2> RESERVED 2\x9b");
  print("  <rs3> RESERVED 3\x9b\x9b");
  print("ALL 11 PARAMETERS MUST BE PROVIDED.\x9b");
  print("USE - FOR PARAMETERS YOU DO NOT WISH\x9bTO CHANGE.\x9b");
}

int main(int argc, char* argv[])
{
  OS.lmargn=2;

  if (_is_cmdline_dos())
    {
      if (argc<12)
	{
	  args(argv);
	  return(1);
	}

      drive_num=atoi(argv[1]);
      
      if (percom_get(drive_num,&pb)!=1)
	{
	  print("COULD NOT RETRIEVE PERCOM BLOCK.");
	  return(1);
	}
      
      if (argv[2][0]!='-')
	{
	  pb.num_tracks=atoi(argv[2]);
	}

      if (argv[3][0]!='-')
	{
	  pb.step_rate=atoi(argv[3]);
	}

      if (argv[4][0]!='-')
	{
	  pb.sectors_per_track=atoi(argv[4]);
	}

      if (argv[5][0]!='-')
	{
	  pb.num_sides=atoi(argv[5]);
	}

      if (argv[6][0]!='-')
	{
	  pb.density=atoi(argv[6]);
	}
 
      if (argv[7][0]!='-')
	{
	  pb.sector_size=atoi(argv[7]);
	}

      if (argv[8][0]!='-')
	{
	  pb.drive_present=atoi(argv[8]);
	}

      if (argv[9][0]!='-')
	{
	  pb.reserved1=atoi(argv[9]);
	}

      if (argv[10][0]!='-')
	{
	  pb.reserved2=atoi(argv[10]);
	}

      if (argv[11][0]!='-')
	{
	  pb.reserved3=atoi(argv[11]);
	}
    }
  else
    {
      // DOS 2.0
      print("\x9b" "PRESS \xD2\xC5\xD4\xD5\xD2\xCE TO USE DEFAULT PARAMETER.\x9b");

      print("DRIVE NUMBER (");
      itoa(drive_num,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	drive_num=atoi(buf);

      if (percom_get(drive_num,&pb)!=1)
	{
	  print("COULD NOT RETRIEVE PERCOM BLOCK.");
	  return(1);
	}
      
      print("# OF TRACKS (");
      itoa(pb.num_tracks,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.num_tracks=atoi(buf);

      print("STEP RATE (");
      itoa(pb.step_rate,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.step_rate=atoi(buf);

      print("# OF SECTORS PER TRACK (");
      itoa(pb.sectors_per_track,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.sectors_per_track=atoi(buf);

      print("# OF SIDES - 1 (");
      itoa(pb.num_sides,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.num_sides=atoi(buf);

      print("DENSITY (");
      itoa(pb.density,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.density=atoi(buf);

      print("SECTOR SIZE (");
      itoa(pb.sector_size,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.sector_size=atoi(buf);

      print("DRIVE SELECTED (");
      itoa(pb.drive_present,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.drive_present=atoi(buf);

      print("RESERVED 1 (");
      itoa(pb.reserved1,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.reserved1=atoi(buf);

      print("RESERVED 2 (");
      itoa(pb.reserved2,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.reserved2=atoi(buf);

      print("RESERVED 3 (");
      itoa(pb.reserved3,buf,10);
      print(buf);
      print(")? ");
      get_line(buf,8);
      if (buf[0]!=0x9b)
	pb.reserved3=atoi(buf);
    }

  if (percom_set(drive_num,&pb)!=1)
    {
      print("COULD NOT SET PERCOM BLOCK.\x9b");
    }
  else
    {
      print("\x9b" "OK" "\x9b\x9b");
    }
  return(0);
}
