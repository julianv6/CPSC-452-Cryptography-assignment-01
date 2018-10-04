#include <string>
#include <cstring>
#include "CipherInterface.h"
#include "RowTransposition.h"
#include "RailFence.h"
#include "Playfair.h"
#include "Vignere.h"
#include "Ceasar.h"
#include <iostream>
#include <fstream>

using namespace std;
void invalidArg(){
	cout << "INVALID ARGUMENTS\n\tCIPHER NAME: Is the name of the cipher. " 
		 	<< "Valid names are:\n\t\tPLF: Playfair\n\t\tRTS: Row Transpositio"
		 	<< "n\n\t\tRFC: Railfence\n\t\tVIG: Vigenre\n\t\tCES: Caesar"
			<< "\n\tKEY: the encryption key to use.\n\tENC/DEC: whether to "
			<< "encrypt or decrypt, respectively.\n\tINPUT FILE: the file from "
			<< "which to read the input.\n\tOUTPUT FILE: the file to which the "
			<< "output shall be written." << endl;
}
//./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>
int main(int argc, char** argv)
{
	if (argc !=6){
		invalidArg();
		return 0;
	}


	string text = "";
	ifstream inputfile(argv[4]);
    // Always check to see if file opening succeeded
    if (!inputfile.is_open()){
		cout<<"Could not open input file\n";
		return 0;
	}
    else {
		inputfile >> text;      
    }
	inputfile.close();

	ofstream outputfile(argv[5]);
	if (!outputfile.is_open()){
		cout<<"Could not open output file\n";
		return 0;
	}
	
	CipherInterface* cipher;	
	if(!strcmp(argv[1], "PLF")){	
		 cipher = new Playfair();		
	}
	else if(!strcmp(argv[1], "RTS")){
		cipher = new RowTransposition();
	}
	else if(!strcmp(argv[1], "RFC")){
		cipher = new RailFence();

	}
	else if(!strcmp(argv[1], "VIG")){
		cipher = new Vignere();

	}
	else if(!strcmp(argv[1], "CES")){
		cipher = new Ceasar();
	}
	else{
		invalidArg();
		return 0;
	}
	
	/* Error checks */
		if(!cipher)
		{
			fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
			__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
		}
	
		/* Set the encryption key */
		if(cipher->setKey(argv[2])){

		}
		if (!strcmp(argv[3], "ENC")){
			/* Perform encryption */
			outputfile << cipher->encrypt(text);
		}
		else if(!strcmp(argv[3], "DEC")){
			/* Perform decryption */
			outputfile << cipher->decrypt(text);
		}
		else{
			invalidArg();
			return 0;
		}
	
	outputfile.close();
	return 0;
}
