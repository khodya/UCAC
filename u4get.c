#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ucac4.h"

/* The following code is intended to separate all UCAC4 stars 
   by UCAC apparent magnitude by regions 9-12.9 12-14.9 13-15.9.
   As a result, 3 new files will be created each containing
   extracted stars data in ASCII format. */

int main(int argc, const char **argv) {
  const double start_dec = -10.;
  const double end_dec = 90.;
  const double zone_height = .2;
  int zone = (int)((start_dec + 90.) / zone_height) + 1;
  int end_zone = (int)((end_dec + 90.) / zone_height) + 1;
  const int buffsize = 400;
  FILE *index_file = NULL;
  UCAC4_STAR *stars = (UCAC4_STAR *)calloc(buffsize, sizeof(UCAC4_STAR));
  while (zone <= end_zone) {
    FILE *ifile = get_ucac4_zone_file(zone, path);
    int i, n_read, keep_going = 1;
    if (ifile) {
      while (n_read = fread(stars, sizeof(UCAC4_STARS), buffsize, ifile) > 0 
	     && keep_going) 
	for (i = 0; i< n_read && keep_going; i++)
	  {
	    UCAC4_STAR star = stars[i];

#ifdef __BYTE_ORDER
#if __BYTE_ORDER == __BIG_ENDIAN
	    flip_ucac4_star(&star);
#endif
#endif

	    char buff[UCAC4_ASCII_SIZE];
	    write_ucac4_star(zone, offset + 1, buff, &star, output_format);
	  }
    }
  }

}
