#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char *argv[]) {
    int page_size = atoi(argv[2]);
    int nu_phys_pages = atoi(argv[1]);
    char *filename = argv[3];
    
    FILE *file = fopen(filename, "r");
    char line[12];
    int page_numbers[100000]; // array of page numbers
    int a = 0; // page number
    int i = 0; // keeps track of where in our array should we put our page number(a).
    
    // Open the file and save every line into our array(page_numbers)
    while(fgets(line, 13, file)) {
        a = atoi(line)/(page_size);
        page_numbers[i] = a;
        i++;        
    }
    
    fclose(file);
    
    int frames = nu_phys_pages; 
    int pages = sizeof(page_numbers)/sizeof(page_numbers[0]);
    

    // Create a table 
    int temp[frames];
    for (int i = 0; i < frames; i++) {
        // pages cannot have negative number so it is ok to fill the table with -1s.
        temp[i] = -1;
    }

    int miss = 0; // number of page faults
    int index = 0; // Is only used when the table is not full. 

    // Go through every page
    for (int i = 0; i < pages; i++) {
        // helper helps us skip some parts if we get a hit
        // if helper is 1 it means that we get a hit!
        int helper = 0;
        for (int j = 0; j < frames; j++) {
            if (page_numbers[i] == temp[j]) {
                helper++;
                // We substract one from miss because even when we get a hit the program increaments miss by 1
                // to avoid this we simply subtract one so when the program increaments one nothing will change
                miss--;
            }
        }
        miss++;

        // If we get a hit (helper = 1), the we skip all these parts
        if (index == frames && helper == 0) {

            /* 
            Create  an array, same as temp.
            Then we go through our page table and check if we can find page x (temp[i]) in our page reference (page_nubers)
            If we find the page, then we calculate the distance between where we started and where the page is and add this value
            in our newly created array (temp_arr).
            But, if we cannot find page x in our page reference then we do nothing and the value for that page in our newly created
            array is -1.
            Ex. page table (temp):
                [ 3  , 2 , 1  ]
                and our newly created array (temp_arr):
                [ -1 , -1, -1 ]
                Then we go every element in our table and try to find it in our page reference (page_page numbers)
                 
                We are here:                 *
                page_numbers = [ 3, 2, 1, 3, 4, 1, 6, 2]

                3 is not found!
                [ -1, -1 , -1 ]
                2 is found! and the distance (from 4 to 2) is: 3
                [ -1, 3 , -1 ]
                1 is found! and the distance (from 4 to 1) is: 1
                [ -1,  3 , 1 ]
            */
            int temp_arr[frames];
            for (int j = 0; j < frames; j++) {
                temp_arr[j] = -1;
            }

            for (int j = 0; j < frames; j++) {
                for (int k = i; k < pages; k++) {
                    if (temp[j] == page_numbers[k]) {
                        temp_arr[j] = k;
                        // Same page may repeat itself multiple times. 
                        // Break when you find the nearest page. 
                        break;
                    }
                }
            }

            /*
            Now that we have all the distances, we start by cheking if we have a -1 in our temp_arr.
            Because -1 means that the page will never be used in the future. So we can just swap this page with the new page. 
            But if there are no -1s, then we look for the page which will be used furthest in the future (the page in our table 
            that has the largest distance value). Then we swap this page with the new page. 
            */
            int max = temp_arr[0];
            int max_index = 0;
            int value = 0;
            for (int j = 0; j < frames; j++) {
                if (temp_arr[j] == -1) {
                    temp[j] = page_numbers[i];
                    value = 1;
                    break;
                }
                if (max < temp_arr[j]) {
                    max = temp_arr[j];
                    max_index = j;
                }
            }
            if (value == 0) {
                temp[max_index] = page_numbers[i];
            }

        } else if (index < frames && helper == 0) {
            // skip if we get a hit
            temp[index] = page_numbers[i];
            index++;
        }
    }

    printf("Number of physical pages = %d, page size = %d\n", nu_phys_pages, page_size);
    printf("Reading memory trace from %s...  Read %d memory references\n", filename, pages);
    printf("Results:  %d page faults\n", miss);
    //printf("------------------------------------------------------------------------\n");
    //printf("%d\n", miss);

    return 0;
}



