#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

unsigned char secret[400]; /*The letters*/
unsigned char key(void) {  /*generate small letters*/
  unsigned int c;
  unsigned char lil;
  srand(clock());
  for (c = 0; c < 2; ++c) {
    lil = (rand() % 26); /*pseudo-random*/
  }
  return (lil);
}

/* Vegenere cypher */
unsigned char encpt(unsigned char get, unsigned char secret) {
  unsigned char number;
  number = ((get + secret) % 26); /*frames it to asci*/
  return (number);
}

unsigned char decpt(unsigned char get,
                    unsigned char secret) { /*i dont think this is possible*/
  unsigned char number;
  number = ((get - secret + 26) % 26);
  return (number);
}

unsigned int parsed(unsigned char string) { /*puts asci insto my letters array*/
  unsigned int parsed;
  parsed = string - 97;
  return (parsed);
}

/* Vegenere cypher */

int main() {
  char get[400] =
      "a b c d e f g h i j k l m n o p q r s t u v w x y z"; /*the string to
                                                                encpt*/
  unsigned char enc[400]; /*the encripted string*/
  unsigned char
      y[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
               'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
               'u', 'v', 'w', 'x', 'y', 'z', ' '}; /*array for the alphabet*/
  for (int i = 0; i < strlen(get);
       ++i) { /*loops the string and apply func char by char*/

    secret[i] = key();
    enc[i] = encpt(parsed(get[i]), secret[i]);
    printf("%c", y[enc[i]]);
  }
  printf("\n");
  for (int i = 0; i < strlen(get); ++i) {
    if (get[i] == 32)
      printf(" ");
    else
      printf("%c", y[decpt(enc[i], secret[i])]);
  }
  printf("\n");
  return (0);
}


