#include "Ceasar.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Ceasar::setKey(const string& key)
{ 
	stringstream keystream(key);

    int k = 0;
    keystream >> k;

	if(k <1){
		return false;
	}
	secretkey = k%26;

	return true;  
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Ceasar::encrypt(const string& plaintext)
{ 
	string ciphertext = "";
	int plen = plaintext.length();
	for(int i = 0; i<plen; i++){
		ciphertext.push_back((char)(toupper((plaintext[i])+secretkey)%26 + 'A'));
	}
	return ciphertext; 
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Ceasar::decrypt(const string& cipherText) 
{ 
	string plaintext = "";
	int clen = cipherText.length();
	for(int i = 0; i<clen; i++){
		plaintext.push_back((char)((26 + (cipherText[i]-secretkey))%26+'A'));
	}
	return plaintext; 
	
}

