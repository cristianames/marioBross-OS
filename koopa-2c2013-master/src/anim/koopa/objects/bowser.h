#ifndef BOWSER_H_
#define BOWSER_H_

	#include "../../i_drawable.h"

	typedef struct {
		implements_i_drawable
	} t_bowser;

/*
             7   7
            7 7 7 7
           7 117  7
        7771177   7 77
       7117773   777  7
     771111733   711 7
    71117722733371 17
     77  7222777111  77
  7777   722222271111 17
 733377  72222227111111 7
 733333372277222227111 77
 733333337733722227 11  7
  7 3333333333722277 1 1 7
  7 7  3333333722777711717
   77  77  333777333777 7
     77777733773337723  777777
    73333777733723 222223    7
      77333377333727227727   7
       7777 7733723  2222223 7
            7733722223   22337
           73733722223   22227
           733733772223  2223 7
           7337333372223322223 7
     777   73337333772222222237
    7 3377777333733373  2222227
     733337 77337333723 23   27
     733337777333733772323  23 7
    7333337777333733722223  237
   7 33333777773373377222233227
    7733337 777777733377222227
     7 3377733733733333772227
      777      7  7      777

	first spaces => 0
	7 => 4
	middle spaces => 7
	\n => \\n
*/

	t_bowser* bowser_create(int x, int y, int maxHeight);
	void bowser_killLastLine(t_bowser* this);

#endif
