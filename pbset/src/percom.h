/**
 * Tiny Copy - a Sector Copy in 8K Cart form
 *
 * Author: Thomas Cherryhomes
 *  <thom.cherryhomes@gmail.com>
 *
 * Percom block functions
 */

#ifndef PERCOM_H
#define PERCOM_H

typedef struct _PercomBlock
{
  unsigned char num_tracks;
  unsigned char step_rate;
  unsigned short sectors_per_track;
  unsigned char num_sides;
  unsigned char density;
  unsigned short sector_size;
  unsigned char drive_present;
  unsigned char reserved1;
  unsigned char reserved2;
  unsigned char reserved3;
} PercomBlock;

/**
 * Get percom block
 * returns pointer to a percom block
 * d = Drive number.
 */
unsigned char percom_get(unsigned char d, PercomBlock* p);

/**
 * Set percom block
 * d = drive number
 * p = pointer to percom block struct
 */
unsigned char percom_set(unsigned char d, PercomBlock* p);

/**
 * Get default parameters
 * Returns a dummy percom block if drive does not
 * support the command, e.g. Atari 810/1050
 */
void percom_get_default_parameters(PercomBlock* pb);

#endif /* PERCOM_H */ 
