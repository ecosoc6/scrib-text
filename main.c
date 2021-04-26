/*******************************************************************
 * 
 *   This program is to export the text from a Scribus .sla file. 
 *   It removes the XML tags, etc., thus making a document
 *   which is easier for humans to read.
 * 
 *   It does not produce a polished document, however,
 *   because it leaves line breaks in numerous places where
 *   the .sla style settings change, but where there would not be
 *   a line break in ordinary text.  Also, it reproduces text in the
 *   order in which it appears in the .sla file, which is the order,
 *   in time, in which it was entered into the Scribus editor.
 *   This is not necessarily the same as the spatial order in
 *   which Scribus or any other .sla editor or viewer would
 *   display it.  I find that the program is nevertheless quite
 *   useful for reviewing and spellchecking Scribus documents. 
 *
 *   The program is written in C.  It consists of only a single file,
 *   this one, and can be compiled easily with a C compiler.
 *   I used gcc-10, running on Linux (Lubuntu 20.04).
 *   Command-line syntax was:
 *      gcc-10 -o main.out main.c
 *   To run the output file, main.out:
 *      ./main.out
 *   The program expects to find a file called todump.sla in the
 *   same directory (folder) that the program is in. It reads this
 *   file and outputs a file called dumped.txt in the same
 *   directory.  So, take the .sla file you want to export,
 *   copy it to the directory this program is in, and rename it
 *   todump.sla. Then run the program and look at dumped.txt
 *   with the text editor or word processor of your choice.
 * 
 * 
 *   Program Structure
 *   --------------------------
 * 
 *   Textual content in .sla files occurs in XML elements that
 *   begin with: '<ITEXT '.  This program reads lines from
 *   'todump'; and subjects lines that begin with '<ITEXT'
 *    to further processing.  Other lines are ignored, except lines
 *    beginning with '<para', which are processed simply to
 *    put a line break in the output.
 * 
 *    '<ITEXT' lines are examined to find the construct 'CH',
 *    which  indicates that text (character) data of the kind we
 *    want are soon to follow. The function 'find_ct()' does this
 *    job. It then calls another function, 'pbq()' which prints
 *    the portion of subsequent material that occurs between
 *    quotation marks.
 * 
 * ***************************************************************/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define TAG  "<ITEXT"
#define PTAG "<para"
#define SL 1024
int find_ct();
int pbq();
int scop_pe();
FILE *fin, *fout;

int main () {
    char sc_result[SL] ;
    int sc_code ;
    char *q_pos_a;
    char *q_pos_b;
    fin = fopen("todump.sla", "r");
    if(fin ==  NULL) {puts("Couldn't find input file \"todump.sla\"\n"); exit(0);} 
    fout = fopen("dumped.txt", "w");
        
    do { 
        sc_code = fscanf(fin, "%s", sc_result);
        if (!(strcmp(sc_result, TAG))) {
          fgets(sc_result, SL, fin);
          find_ct(sc_result);       
       }
       if (!(strcmp(sc_result, PTAG))) { fputc('\n', fout); fputc('\n', fout); }
    } 
    while (sc_code == 1);
    fclose(fin);  fclose(fout);
    puts("\n Finished.  Look at \"dumped.txt\" for output.\n");
}


/* Find the construct that indicates text will begin   *
*  and call function to write from that point              */
int find_ct(char *sc_result) {
    char tail[SL];
    char *pos, *lqpos;
    pos = strstr(sc_result, "CH") + 2;
    scop_pe(sc_result, tail, pos);
    pos = strchr(tail, '"');
    lqpos = strrchr(tail, '"');
    pbq(tail, pos, lqpos);
}


/* Print the text occurring Between Quotes. */
int pbq(char *tail, char *q_pos1, char *q_pos2) {
    char c;
    char *pos;
    for (pos = q_pos1 + 1 ;   pos < q_pos2;  pos++) {
      c = * pos;
      fputc(c, fout);
    }
    fputc('\n', fout); fputc('\n', fout);
}



/* Copy the portion of string after pointer */
int scop_pe(char *whole, char *tail, char *p) {
    char *a;
    char *endp = whole + strlen(whole);
    int x = 0; 
    for (a= p; a <= endp; a++){
        tail[x] = *a;
        ++x;
    }
}
