#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ucac4.h"

/* The following code is intended to separate all UCAC4 stars 
   by UCAC apparent magnitude by regions 9-12.9 12-14.9 13-15.9.
   As a result, 3 new files will be created each containing
   extracted stars data in ASCII format. */

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
  UCAC4_STAR *stars = (UCAC4_STAR *)calloc( buffsize, sizeof( UCAC4_STAR));
  //ifile = get_ucac4_zone_file(zone, path);
  if (ifile) {
    //char ibuff[50];
    printf("Everything is ok\n");
    printf("%d %d\n",zone,end_zone);
    //fseek(ifile, 0L, SEEK_END);
    //fread(&star, 1, sizeof( UCAC4_STAR), ifile);
    //fgets(ibuff, sizeof( ibuff), ifile); 
    //printf("%s\n", ibuff);
    //printf("%c\n", ibuff[0]);
    //printf("%9d %12.8lf %12.8lf\n", star.id_number,
    //	   (double) star.ra / 3600000.,
    //	   (double) star.spd / 3600000. - 90.);
    int keep_going = 1;
    int n_read = 0;
    int i;
    while ( zone <= end_zone && keep_going) {
      ifile = get_ucac4_zone_file(zone, path);
      while ( (n_read = fread(stars, sizeof(UCAC4_STAR), buffsize, ifile)) > 0 
	      && keep_going)
	for( i = 0; i < n_read && keep_going; i++) {
	  UCAC4_STAR star = stars[i];
	  
	  /* Picking stars */

	  /* Filter on # catalogs used for PM  */
	  if (star.cu1 < 3) continue;
	  
	  /* Filter on Proper motion */
	  int pmra = star.pm_ra;
	  int pmdec = star.pm_dec;
	  if ( sqrt(pmra * pmra + pmdec * pmdec) > 100 ) continue;
	}
      zone++;
    }
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

