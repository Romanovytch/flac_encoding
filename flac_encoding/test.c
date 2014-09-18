/*
** test.c for test in /home/romanovytch/rogervoice/timed_printer/flac_encoding
** 
** Made by Givernaud FLorian
** Login   <romanovytch@epitech.net>
** 
** Started on Thu Sep 18 18:20:49 2014 Givernaud FLorian
** Last update Thu Sep 18 18:20:54 2014 Givernaud FLorian
*/

#include "sfconfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sndfile.h>

#define BUFFER_LEN 4096

static void encode_file (const char *infilename, const char *outfilename, int filetype) ;

int main (int argc, char **argv)
{
  if (argc != 2)
    {
      printf("Usage : ./encode human_voice.wav\n");
      return (0);
    }
  encode_file(argv [1], "human_voice.flac", SF_FORMAT_FLAC | SF_FORMAT_PCM_16);
  return 0 ;
} /* main */


static void encode_file (const char *infilename, const char *outfilename, int filetype)
{ 
  static float buffer [BUFFER_LEN] ;
  SNDFILE *infile, *outfile ;
  SF_INFO sfinfo ;
  int k, readcount ;

  printf ("    %s -> %s ", infilename, outfilename) ;
  fflush (stdout) ;

  k = 16 - strlen (outfilename) ;

  if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
    {printf ("Error : could not open file : %s\n", infilename) ;
      puts (sf_strerror (NULL)) ;
      exit (1) ;
    }

  sfinfo.format = filetype ;

  if (! sf_format_check (&sfinfo))
    {sf_close (infile) ;
      printf ("Invalid encoding\n") ;
      return ;
    } ;

  if (! (outfile = sf_open (outfilename, SFM_WRITE, &sfinfo)))
    {printf ("Error : could not open file : %s\n", outfilename) ;
      puts (sf_strerror (NULL)) ;
      exit (1) ;
    } ;

  while ((readcount = sf_read_float (infile, buffer, BUFFER_LEN)) > 0)
    sf_write_float (outfile, buffer, readcount) ;

  sf_close (infile) ;
  sf_close (outfile) ;

  printf ("ok\n") ;

  return ;
} /* encode_file */
