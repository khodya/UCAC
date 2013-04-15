#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ucac4.h"

static const char *path_separator = "/", *read_only_permits = "r";
static const char *path = "data";
static FILE *get_ucac4_zone_file( const int zone_number, const char *path);

int main(int arc, const char **argv) {
  const double start_dec = -10.;
  const double end_dec = 90.;
  const double zone_height = .2;
  //const int zone = (int)((start_dec + 90.) / zone_height) + 1;
  int zone = 400;
  const int end_zone = (int)((end_dec + 90.) / zone_height) + 1;
  FILE *ifile;
  UCAC4_STAR star;
  const int buffsize = 400;
  //UCAC4_STAR *stars = (UCAC4_STAR *)calloc( buffsize, sizeof( UCAC4_STAR));
  ifile = get_ucac4_zone_file(zone, path);
  if (ifile) {
    //char ibuff[50];
    printf("Everything is ok\n");
    printf("%d %d\n",zone,end_zone);
    //fseek(ifile, 0L, SEEK_END);
    fread(&star, 1, sizeof( UCAC4_STAR), ifile);
    //fgets(ibuff, sizeof( ibuff), ifile); 
    //printf("%s\n", ibuff);
    //printf("%c\n", ibuff[0]);
    printf("%9d %12.8lf %12.8lf\n", star.id_number,
    	   (double) star.ra / 3600000.,
    	   (double) star.spd / 3600000. - 90.);
  } else {
    printf("File can\'t be opened.\n");
  }

  return 0;
}
    
static FILE *get_ucac4_zone_file( const int zone_number, const char *path)
{
   FILE *ifile;
   char filename[80];

   sprintf( filename, "u4%c%sz%03d", (zone_number >= 380 ? 'n' : 's'),
                     path_separator, zone_number);
            /* First,  look for file in current path: */
   ifile = fopen( filename + 4, read_only_permits);
   if( !ifile)
      ifile = fopen( filename, read_only_permits);
         /* If file isn't there,  use the 'path' passed in as an argument: */
   if( !ifile && *path)
      {
      char filename2[80], *endptr;
      int i;

      strcpy( filename2, path);
      endptr = filename2 + strlen( filename2);
      if( endptr[-1] != *path_separator)
         *endptr++ = *path_separator;
      for( i = 0; !ifile && i < 2; i++)
         {
         strcpy( endptr, filename + 4 * (1 - i));
         ifile = fopen( filename2, read_only_permits);
         }
      }
   return( ifile);
}
