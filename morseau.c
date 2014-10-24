//r/dailyprogrammer
//Aug 28, 2014
//Challenge 176(intermediate)
//skeeto's solution, read and re-implemented

#include<stdio.h>
#include<arpa/inet.h>// for htonl()
#include<math.h>//for sin()
#include<limits.h> //for SCHAR_MAX
#include<string.h> //for strchr()
#include<ctype.h>//for toupper()

#define PI 3.14159
const char* LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
const char* CODES[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
			 "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
			 "..-", "...-", ".--", "-..-", "-.--", "--.", "-----", ".----", "..---",
			 "...--", "....-", ".....", "-....", "--...", "---..", "----."}; 

struct au{
  FILE* output; 
  int sample_rate; 
  double gain; 
};// Notes: Struct definition ends with semicolon. We club the stuff that is always used together; for example, to output anything to the stdout, you need sample_rate and gain of signal, hence the three (seemingly different) quantities are fields of a struct. 

void au_header(struct au* au){// Get header info from Au file format section of Wikipedia
  fwrite(".snd", 4, 1, au->output); //First byte is the magic number ".snd"
  uint32_t offset = htonl(24); //htonl() converts little-endian format (used by Intel processor in local machine) to network order (big endian format). 24 bytes of header (6 words of 4 bytes each) used.
  fwrite(&offset, 4, 1, au->output); //again, one word of 4 bytes each
  uint32_t data_size = 0xffffffff; 
  fwrite(&data_size, 4, 1, au->output);
  uint32_t encoding_type = htonl(2); 
  fwrite(&encoding_type, 4, 1, au->output);
  uint32_t sample_rate = htonl(8000); 
  fwrite(&sample_rate, 4, 1, au->output); 
  uint32_t num_channels = htonl(1); 
  fwrite(&num_channels, 4, 1, au->output);
}

void au_silence(struct au* au, double seconds){
  uint32_t sample_rate = au->sample_rate; 
  uint64_t num_samples = sample_rate*seconds;  
  for (int i = 0; i<num_samples; i++){
   putc(0, au->output);
  }
}

void au_beep(struct au* au, double seconds, double frequency){
  uint32_t sample_rate = au->sample_rate; 
  uint64_t num_samples = sample_rate*seconds; 
  for(int i = 0; i<num_samples; i++){
   double t = i/(double)sample_rate;
   double value = sin(2*PI*t*frequency);
   putc(value*SCHAR_MAX*au->gain, au->output);
  }
}

const char* morse_code(char c){
 const char* p = strchr(LETTERS, toupper(c));
 return p == NULL? NULL : CODES[p-LETTERS]; 
}

void morse_char(struct au* au, char c){
 const char* p = morse_code(c);
 if (p==NULL)
  au_silence(au, 0.7); 
 else{
  for(;*p; p++){
   au_beep(au, *p=='.'? 0.2 : 0.6, 500);
   au_silence(au, 0.2);
  }
 }
}

void morse_string(struct au* au, const char* message){
 for(;*message;message++){ // nice way to keep stepping along the message string
  morse_char(au, *message); 
  au_silence(au, 0.6);
 }
}

int main(int argc, char** argv){
  struct au au = {
    .output = stdout, 
    .sample_rate = 8000, 
    .gain = 0.4
  };

  au_header(&au); 
  morse_string(&au, argc==1? "Missing argument" : argv[1]);
  return 0;
}
