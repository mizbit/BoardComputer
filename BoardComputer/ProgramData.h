/*
 * ProgramData.h
 *
 * Created: 2020-01-09 00:33:36
 *  Author: pszczelaszkov
 */ 
#ifndef PROGRAMDATA_H_
#define PROGRAMDATA_H_
#ifdef __AVR__
#include <avr/pgmspace.h>
#else
#define PROGMEM
uint16_t pgm_read_word(const int16_t* value)
{
    return *value;
}
#endif

const int16_t PROGRAMDATA_NTC_2200_INVERTED[] PROGMEM = {471,471,385,342,315,295,280,268,258,249,242,235,229,224,219,215,211,207,204,200,197,194,192,189,187,184,182,180,178,176,174,173,171,169,168,166,165,163,162,161,159,158,157,156,155,153,152,151,150,149,148,147,146,145,145,144,143,142,141,140,140,139,138,137,137,136,135,134,134,133,132,132,131,130,130,129,129,128,127,127,126,126,125,125,124,124,123,122,122,121,121,120,120,120,119,119,118,118,117,117,116,116,115,115,115,114,114,113,113,113,112,112,111,111,111,110,110,109,109,109,108,108,108,107,107,107,106,106,106,105,105,105,104,104,104,103,103,103,102,102,102,102,101,101,101,100,100,100,99,99,99,99,98,98,98,97,97,97,97,96,96,96,96,95,95,95,95,94,94,94,94,93,93,93,93,92,92,92,92,91,91,91,91,90,90,90,90,90,89,89,89,89,88,88,88,88,88,87,87,87,87,87,86,86,86,86,86,85,85,85,85,85,84,84,84,84,84,83,83,83,83,83,82,82,82,82,82,81,81,81,81,81,81,80,80,80,80,80,79,79,79,79,79,79,78,78,78,78,78,78,77,77,77,77,77,77,76,76,76,76,76,76,75,75,75,75,75,75,74,74,74,74,74,74,73,73,73,73,73,73,73,72,72,72,72,72,72,71,71,71,71,71,71,71,70,70,70,70,70,70,70,69,69,69,69,69,69,69,68,68,68,68,68,68,68,67,67,67,67,67,67,67,66,66,66,66,66,66,66,66,65,65,65,65,65,65,65,64,64,64,64,64,64,64,64,63,63,63,63,63,63,63,62,62,62,62,62,62,62,62,61,61,61,61,61,61,61,61,60,60,60,60,60,60,60,60,60,59,59,59,59,59,59,59,59,58,58,58,58,58,58,58,58,57,57,57,57,57,57,57,57,57,56,56,56,56,56,56,56,56,56,55,55,55,55,55,55,55,55,54,54,54,54,54,54,54,54,54,53,53,53,53,53,53,53,53,53,52,52,52,52,52,52,52,52,52,51,51,51,51,51,51,51,51,51,50,50,50,50,50,50,50,50,50,50,49,49,49,49,49,49,49,49,49,48,48,48,48,48,48,48,48,48,48,47,47,47,47,47,47,47,47,47,46,46,46,46,46,46,46,46,46,46,45,45,45,45,45,45,45,45,45,44,44,44,44,44,44,44,44,44,44,43,43,43,43,43,43,43,43,43,43,42,42,42,42,42,42,42,42,42,42,41,41,41,41,41,41,41,41,41,41,40,40,40,40,40,40,40,40,40,40,39,39,39,39,39,39,39,39,39,39,38,38,38,38,38,38,38,38,38,38,37,37,37,37,37,37,37,37,37,37,36,36,36,36,36,36,36,36,36,36,35,35,35,35,35,35,35,35,35,35,34,34,34,34,34,34,34,34,34,33,33,33,33,33,33,33,33,33,33,32,32,32,32,32,32,32,32,32,32,31,31,31,31,31,31,31,31,31,31,30,30,30,30,30,30,30,30,30,30,29,29,29,29,29,29,29,29,29,29,28,28,28,28,28,28,28,28,28,28,27,27,27,27,27,27,27,27,27,26,26,26,26,26,26,26,26,26,26,25,25,25,25,25,25,25,25,25,24,24,24,24,24,24,24,24,24,24,23,23,23,23,23,23,23,23,23,22,22,22,22,22,22,22,22,22,21,21,21,21,21,21,21,21,21,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,19,18,18,18,18,18,18,18,18,18,17,17,17,17,17,17,17,17,16,16,16,16,16,16,16,16,16,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,13,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,8,8,8,8,8,8,8,7,7,7,7,7,7,7,6,6,6,6,6,6,6,5,5,5,5,5,5,4,4,4,4,4,4,4,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-7,-7,-7,-7,-8,-8,-8,-8,-9,-9,-9,-9,-9,-10,-10,-10,-10,-11,-11,-11,-12,-12,-12,-12,-13,-13,-13,-13,-14,-14,-14,-15,-15,-15,-16,-16,-16,-17,-17,-17,-18,-18,-18,-19,-19,-19,-20,-20,-21,-21,-21,-22,-22,-23,-23,-23,-24,-24,-25,-25,-26,-26,-27,-28,-28,-29,-29,-30,-31,-31,-32,-33,-33,-34,-35,-36,-37,-38,-39,-40,-41,-42,-43,-45,-47,-48,-50,-53,-56,-59,-64,-71,};

#endif /* PROGRAMDATA_H_ */