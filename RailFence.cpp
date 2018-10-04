#include "RailFence.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool RailFence::setKey(const string& key)
{ 
	stringstream keystream(key);
 
    int k = 0;
    keystream >> k;

	if(k <1){
		return false;
	}
	secretkey = k;
	return true;  
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string RailFence::encrypt(const string& plaintext)
{ 
	int p = plaintext.length();
	int maxCol = ceil(p/((double)secretkey));
	char matrix[secretkey][maxCol];
	string ciphertext ="";
	
	int i = 0;
	for(int c=0; c<maxCol; c++){
		for(int r=0; r<secretkey; r++){
			if(i<p){
				matrix[r][c]=plaintext[i];
				i++;
			}
			else
				matrix[r][c]='\0';
		}
	}
	
	for(int r = 0; r<secretkey; r++){
		for(int c = 0; c<maxCol; c++){
			ciphertext.push_back(matrix[r][c]);
		}
	}
	return ciphertext; 
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string RailFence::decrypt(const string& cipherText) 
{ 
	string plaintext = "";
	int clen = cipherText.length();
	int maxCol = ceil(clen/((double)secretkey));
	int i = 0;
	char matrix[secretkey][maxCol];
	for(int r = 0; r<secretkey; r++){
		for(int c = 0; c<maxCol; c++){
			if(i<clen){
				matrix[r][c]=cipherText[i];
				i++;
			}
			else
				matrix[r][c]='\0';
		}
	}
 	
	for(int c=0; c<maxCol; c++){
		for(int r=0; r<secretkey; r++){
			plaintext.push_back(matrix[r][c]);
		}
	}

	return plaintext; 
}

