/*

SnackWrap!
version 1.0
by Evan Hahn

<https://github.com/EvanHahn/SnackWrap>

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
using namespace std;

int main(int argc, char* argv[]) {

	// If there's no argument...
	if (argc <= 1) {
		cout << "Type 'snackwrap config.txt' to run SnackWrap against config.txt." << endl;
		return -1;
	}

	// Open the file
	ifstream ins;
	ins.open(argv[1]);
	if (!ins.good()) {
		cout << "SnackWrap cannot open the configuration file." << endl;
		return -1;
	}

	// How many lines does the file have? Count return characters to find out.
	int num = 0, temp, linelength = 0;
	while (!ins.eof()) {
		temp = ins.get();
		if ((temp == 10) && (linelength > 0)) {
			num ++;
			linelength = 0;
		} else
			linelength ++;
	}

	// Declare the files and their commands
	string files[num];
	string commands[num];
	time_t modified[num];

	// Restart file and read it in
	ins.clear();
	ins.seekg(0);
	for (int i = 0; i < num; i ++) {
		ins >> files[i];
		getline(ins, commands[i]);
		modified[num] = 0;
	}
	ins.close();

	// We're all good!
	cout << "SnackWrap is now running. To halt, press ctrl + Z." << endl;

	// Start the endless loop
	while (true) {

		// Go through each file
		for (int i = 0; i < num; i ++) {

			const char* thisFile = (files[i]).c_str();

			// If it's not a comment...
			if (thisFile[0] != '#') {

				// If it exists...
				ifstream input;
				input.open(thisFile);
				if (input.good()) {

					// And if it's newly modified...
					struct stat attributes;
					stat(thisFile, &attributes);
					time_t age = attributes.st_mtime;
					if (difftime(age, modified[i])) {

						// ...update the modified time and execute my command
						modified[i] = age;
						const char* command = commands[i].c_str();
						system(command);

					}
				}

			}

		}

		system("sleep 0.5");

	}

	// You should never get here, but...
	return -1;

}
