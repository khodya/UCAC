#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ucac4.h"

/* The following code is intended to separate all UCAC4 stars 
   by UCAC apparent magnitude by 3 regions.
   As a result, 3 new files will be created each containing
   extracted stars data in ASCII format. */

static const char *path_separator = "/", *read_only_permits = "r";
static const char *path = "data";
static FILE *get_ucac4_zone_file( const int zone_number, const char *path);
static const double eps = 1e-7;

int main(int arc, const char **argv) {
  const double start_dec = -10.;
  const double end_dec = 90.;
  const double zone_height = .2;
  //const int zone = (int)((start_dec + 90.) / zone_height) + 1;
  int zone = 400;
  long epoch_ra;
  long epoch_dec;
  const int end_zone = (int)((end_dec + 90.) / zone_height);
  FILE *ifile;
  UCAC4_STAR star;
  const int buffsize = 400;
  UCAC4_STAR *stars = (UCAC4_STAR *)calloc( buffsize, sizeof( UCAC4_STAR));
  //ifile = get_ucac4_zone_file(zone, path);
  //if (ifile) {
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
    FILE *file_a, *file_b, *file_c, *log;
    file_a = fopen("magA.dat", "w");
    file_b = fopen("magB.dat", "w");
    file_c = fopen("magC.dat", "w");
    log = fopen("u4get.log", "w");
    while ( zone <= end_zone && keep_going) {
      ifile = get_ucac4_zone_file(zone, path);
      if (ifile) 
      while ( (n_read = fread(stars, sizeof(UCAC4_STAR), buffsize, ifile)) > 0 
	      && keep_going)
	for( i = 0; i < n_read && keep_going; i++) {
	  UCAC4_STAR star = stars[i];
	  
	  /* Picking stars */
	  //printf("Picking stars\n");
	  /* Filter on # catalogs used for PM  */
	  if (star.n_cats_used < 3) {
	    fprintf(log, "%9d excluded: less number of catalogs used for PM: %2d\n",
		    star.id_number, 
		    (int) star.n_cats_used);
	    continue;
	  }
	  /* Filter on Proper motion */
	  if ( !star.pm_ra && !star.pm_dec ) {
	    fprintf(log, "%9d excluded: no PM given: %6d %6d\n",
		    star.id_number,
		    star.pm_ra,
		    star.pm_dec);
	    continue;
	  }
	  else {
	    double pmra = star.pm_ra / 10.;
	    double pmdec = star.pm_dec / 10.;
	    double pm = sqrt( pmra * pmra + pmdec * pmdec );
	    //printf("%6d %6d %12.8lf\n", star.pm_ra, star.pm_dec, pm);
	    if ( (pm - 100. ) > eps ) {
	      fprintf(log, "%9d excluded: total PM exceeds 100 mas/y: %12.8lf\n",
		      star.id_number,
		      pm);
	      continue;
	    }
	  }
	  
	  /* Separating by magnitude intervals */
	  
	  if ( star.mag2 >= 9000 && star.mag2 <= 12900 ) {
	    //FILE *file_a;
	    //file_a = fopen("magA.dat", "w");
	    epoch_ra = 190000 + star.epoch_ra;
	    epoch_dec = 190000 + star.epoch_dec;
	    fprintf(file_a, "%3d %3d %1d.%01d %1d.%01d %4d.%02d %4d.%02d\n",
		    star.ra_sigma + 128,
		    star.dec_sigma + 128,
		    //(double) (star.pm_ra_sigma + 128) / 10.,
		    (int) (star.pm_ra_sigma + 128) / 10,
		    (int) (star.pm_ra_sigma + 128) % 10, 
		    //(double) (star.pm_dec_sigma + 128) / 10.,
		    (int) (star.pm_dec_sigma + 128) / 10,
		    (int) (star.pm_dec_sigma + 128) % 10,
		    (int) epoch_ra / 100,
		    (int) epoch_ra % 100,
		    (int) epoch_dec / 100,
		    (int) epoch_dec % 100);
	    fprintf(log, "%9d included: I range %2d.%03d\n",
		    star.id_number,
		    star.mag2 / 1000,
		    abs(star.mag2 % 1000));
	    continue;
	  }

	  if ( star.mag2 > 11000 && star.mag2 < 14000 ) {
	    epoch_ra = 190000 + star.epoch_ra;
	    epoch_dec = 190000 + star.epoch_dec;
	    fprintf(file_b, "%3d %3d %3d.%01d %3d.%01d %4d.%02d %4d.%02d\n",
		    star.ra_sigma + 128,
		    star.dec_sigma + 128,
		    //(double) (star.pm_ra_sigma + 128) / 10.,
		    (int) (star.pm_ra_sigma + 128) / 10,
		    (int) (star.pm_ra_sigma + 128) % 10, 
		    //(double) (star.pm_dec_sigma + 128) / 10.,
		    (int) (star.pm_dec_sigma + 128) / 10,
		    (int) (star.pm_dec_sigma + 128) % 10,
		    (int) epoch_ra / 100,
		    (int) epoch_ra % 100,
		    (int) epoch_dec / 100,
		    (int) epoch_dec % 100);
	    fprintf(log, "%9d included: II range %2d.%03d\n",
		    star.id_number,
		    star.mag2 / 1000,
		    abs(star.mag2 % 1000));
	    continue;
	  }

	  if ( star.mag2 > 13000 && star.mag2 < 15900 ) {
	    epoch_ra = 190000 + star.epoch_ra;
	    epoch_dec = 190000 + star.epoch_dec;
	    fprintf(file_c, "%3d %3d %1d.%01d %1d.%01d %4d.%02d %4d.%02d\n",
		    star.ra_sigma + 128,
		    star.dec_sigma + 128,
		    //(double) (star.pm_ra_sigma + 128) / 10.,
		    (int) (star.pm_ra_sigma + 128) / 10,
		    (int) (star.pm_ra_sigma + 128) % 10, 
		    //(double) (star.pm_dec_sigma + 128) / 10.,
		    (int) (star.pm_dec_sigma + 128) / 10,
		    (int) (star.pm_dec_sigma + 128) % 10,
		    (int) epoch_ra / 100,
		    (int) epoch_ra % 100,
		    (int) epoch_dec / 100,
		    (int) epoch_dec % 100);
	    fprintf(log, "%9d included: III range %2d.%03d\n",
		    star.id_number,
		    star.mag2 / 1000,
		    abs(star.mag2 % 1000));
	    continue;
	  }
	  
	 fprintf(log, "%9d excluded: out of range %2d.%03d\n",
		    star.id_number,
		    star.mag2 / 1000,
		    abs(star.mag2 % 1000));
	}
      //if (!ifile) keep_going = 0;
      zone++;
      fclose(file_a);
      fclose(file_b);
      fclose(file_c);
      fclose(log);
    }
      //  } else {
      //    printf("File can\'t be opened.\n");
      //  }
      //fclose(file_a);
      //fclose(log);
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

