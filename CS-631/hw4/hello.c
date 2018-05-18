#include <greet.h>
#include <stdio.h>

int main(void) {
	greet();
	if (setgreeting("Howdy!") != 0) {
		fprintf(stderr, "Unable to set greeting!\n");
	}
	greet();
	hello("you there", getgreeting());
	return 0;
}
