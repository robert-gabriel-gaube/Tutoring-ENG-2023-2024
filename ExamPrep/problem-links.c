/*
    Write a function that prints in increasing order of their URL length all links from an HTML file named on the
    command line. An HTML link is of the form <a href="google.com">Click</a> the URL portion is the one enclosed in
    quotes. URLs are at most 100 chars long, but arbitrarily many.
    I.e.: a possible input is <a href="www.upt.ro">Click1</a> <a href="acsa.upt.ro">Click2</a> which would print
    Click2 Click1

    I assumed that links can only be on a line and that they have no extra spaces like <   a   href =     "  "   >.
    I also assumed that the links are correctly started and ended.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#define URL_LENGTH 100
#define LABEL_LENGTH 100

typedef struct {
    char label[LABEL_LENGTH];
    char url[LABEL_LENGTH];
}LINK;

typedef struct {
    LINK *links;
    unsigned number_of_links;
}LINKS;

// start points to <a ... 
// end points to </a>
LINK string_to_link(char *start, char *end) {
    // start -> <a href="..." to position ourselves at the first char or URL we need to
    // jump over 9 characters. We need to jump over '"' because we'll use strchr to find 
    // the end quote.
    char *start_url = start + 9;
    char *end_quote = strchr(start_url, '\"');

    LINK link;
    // The length of the URL is the difference between the 2 addresses.
    unsigned url_length = end_quote - start_url; 
    // Copy url into link   
    strncpy(link.url, start_url, url_length);
    link.url[url_length] = '\0';

    // Kinda do the same thing for the label
    char *start_label = end_quote + 2; // Jump over '">'
    char *end_label = strchr(start_label, '<');

    unsigned label_length = end_label - start_label;
    strncpy(link.label, start_label, label_length);
    link.label[label_length] = '\0';
    
    return link;
}

LINKS make_space_for_next_line(LINKS links) {
    links.number_of_links++;
    LINK *aux = realloc(links.links, links.number_of_links * sizeof(LINK));

    if(aux == NULL) {
        fprintf(stderr, "Error with realloc links");
        exit(-1);
    } 
    links.links = aux;
    return links;
}

LINKS read_links(FILE *input) {
    LINKS links = {NULL, 0};

    char line[500];
    while(fgets(line, 500, input)) {
        char *link_start = NULL, *link_end = NULL, *line_pointer = line;

        // Go through all the links in line
        // link_start points to <a ...
        // link_end points to </a>
        while((link_start = strstr(line_pointer, "<a"))) {
            link_end = strstr(link_start, "</a>");
            LINK link = string_to_link(link_start, link_end);

            // Place link in array
            links = make_space_for_next_line(links);
            links.links[links.number_of_links - 1] = link;

            // Jump over the procesed link
            line_pointer = link_end;
        }    
    }
    return links;
}

int compare_links(const void *l1, const void *l2) {
    LINK *link1 = (LINK*)l1;
    LINK *link2 = (LINK*)l2;

    return strcmp(link1->url, link2->url);
}

void print_links_in_order(FILE *input) {
    LINKS links = read_links(input);
    qsort(links.links, links.number_of_links, sizeof(LINK), compare_links);

    for(unsigned i = 0; i < links.number_of_links; ++i) {
        printf("LINK #%d:\n", i);
        printf("\tURL: %s\n", links.links[i].url);
        printf("\tLabel: %s\n", links.links[i].label);
    }

    free(links.links);
}



int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage ./program <input_file_path>");
        return -1; 
    }

    FILE *input = fopen(argv[1], "r");
    if(input == NULL) {
        perror("");
        return -1;
    }

    print_links_in_order(input);

    fclose(input);
    return 0;
}