/*Ross Bearden	
CSCI 3130
OLA 1
1/28/2016
*/

#include <string.h>

void asm_function(const char* message, unsigned int count);

int main(){
	
	//String to be printed
	const char* message = "I want to sleep\nSwat the flies\nSoftly, please\nMasaoka Shiki\n\0";
	
	//Call assembly function
	asm_function(message, strlen(message));
		
	return 0;
}
