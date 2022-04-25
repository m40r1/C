#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *save_file = NULL;
FILE *play_file = NULL;

static const int str_len = 80;

int lookup(char const *const name) {
  /*List of people in database*/
  static char *list[] = {"joao", "lucas", "maria", "leidiane"};
  for (int index = 0; list[index] != NULL; ++index) {
    if (strcmp(list[index], name) == 0)
      return (1);
  }
  return (0);
}

char *ext_fgts(char *line, int size, FILE *file) {

  char *result; /*result*/
  if (play_file != NULL) {
    result = fgets(line, size, play_file);
    fputs(line, stdout);
  } else {
    result = fgets(line,size,file);
  }
  /*saves the file*/
  if (save_file != NULL) {
    fputs(line, save_file);
  }  
  return(result);
}


int main(int argc, char *argv[]) {  

    char name[str_len]; /*a name to lookup*/
    char *save_file_name; /*for the file*/
    char *play_file_name; /*for the file*/

    for (; ((argc > 1) && (argv[1][0] == '-')); --argc && ++argv) {
        switch (argv[1][1]) {
          
            /*-S specify save file*/

        case 'S':
            save_file_name = &argv[1][2];
            save_file = fopen(save_file_name, "w");
            if (save_file == NULL) {
              fprintf(stderr, "Unable to open save file %s\n", save_file_name);
            }
            break;
        case 'P':
            play_file_name = &argv[1][2];
            play_file = fopen(play_file_name, "r");
            if (play_file == NULL) {
                fprintf(stderr, "unable to open %s\n", play_file_name);
                exit(8);
            }
            break;      
        default:      
            fprintf(stderr, "Bad options %s\n", argv[1]);
            exit(8);
        }
    }


    for (;;) {    
       
        fprintf(stdout, "Enter name:");
        ext_fgts(name, sizeof(name), stdin);
        /*checks blank name*/
        /*remebem 1 char for newline*/
        if (strlen(name) <= 1)
            break;

        name[strlen(name) - 1] = '\0';
    
        if (lookup(name)){
            fprintf(stdout, "%s is in the list\n", name);
            break;
        }    
        else
            fprintf(stdout, "%s is not in the list\n", name);
    }
    return 0;
}
