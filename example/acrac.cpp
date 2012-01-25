/*
	ACRAC! After Changing, Run A Command
	by Evan Hahn

	1. Set up files to watch and their corresponding commands.
	2. Run it in the directory you want.
	3. ???
	4. Profit!

	See the readme for more information.

	This code is licensed under the Unlicense. For more information, refer to
	<unlicense.org> or see UNLICENSE.txt. You may do whatever you wish, though
	I'd appreciate if you gave me credit!
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h>
using namespace std;

// Wait
void wait(double secs) {
	clock_t end = clock() + (secs * CLOCKS_PER_SEC);
	while (clock() < end) {}
}

// Main
int main(int argc, char* argv[]) {

	// If there's no argument...
	if (argc <= 1) {
		cout << "Type 'acrac config.txt' to run ACRAC against config.txt." << endl;
		return -1;
	}

	// Open the file
	ifstream ins;
	ins.open(argv[1]);
	if (!ins.good()) {
		cout << "ACRAC cannot open the configuration file." << endl;
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
	cout << "ACRAC is now running. To halt, press ctrl + C." << endl;

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

						// Then update the modified time and execute the command
						modified[i] = age;
						const char* command = commands[i].c_str();
						system(command);

					}
				}

			}

		}

		wait(0.2);

	}

	// You should never get here, but...
	return -1;

}

