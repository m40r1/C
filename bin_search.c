#include <stdio.h>
#include <stdlib.h>

#define max_num 1000 /*max num in files*/
const char data_file[] = "num.dat"; /*file name*/

int data[max_num]; /*array of nums*/
int max_count; /*num of valid elements*/

int main() {
  
    FILE *in_file; /*input file*/
    int mid;       /*its the middle of the range*/
    int low, hi;   /*low and upper bounds*/
    int search;    /*we are looking for*/
    char line[80]; /*input line*/

    in_file = fopen(data_file, "r");
    if (in_file == NULL) {
        fprintf(stderr, "unable to open %s\n", data_file);
        exit(8);
    }
    max_count = 0;
    for (;;) {
        if (fgets(line, sizeof(line), in_file)== NULL)          
            break;
        sscanf(line, "%d",&data[max_count]);
        ++max_count;
    }
    for (;;) {
        fprintf(stdout, "enter num to seach or -1 to quit:");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &search);
        if (search == -1)
          break;
        low = 0;
        hi = max_count;
        for (;;) {
            mid = (low + hi) / 2;
            if(data[mid]==search){
              fprintf(stdout, "found at %d\n", mid);
              break;
            } else if (low == hi) {
              fprintf(stdout, "not found\n");
              break;
            }else if (data[mid] < search) {
                low = ++mid;
            } else {
                hi = --mid;
            }
        }
    }
    return 0;
}
