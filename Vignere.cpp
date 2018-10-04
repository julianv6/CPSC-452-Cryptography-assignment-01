#include "Vignere.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Vignere::setKey(const string& key)
{ 
	for (int i = 0; i < key.length(); i++){
		// ignore all non letters
		// this allows for more comlex 
		// keys such as book sentences
		if(isalpha(key[i]) || key[i] != ' '){
			/*Set all Js to I*/
			if(toupper(key[i]) == 'J'){
				secretkey.push_back('I');
			}
			else{
				secretkey.push_back((char)toupper(key[i]));
			}
		}
		
	}
	//check for invalid key
	if(secretkey.length() == 0)
		return false;
	return true;  
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Vignere::encrypt(const string& plaintext)
{ 
	string ciphertext;
	int klen = secretkey.length();
 	int plen = plaintext.length();
	cout << plaintext << endl;
	for (int i = 0; i < plen; i++){
		ciphertext.push_back(((toupper(plaintext[i]) + secretkey[i%klen]) %26) + 'A');
	}
	return ciphertext;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Vignere::decrypt(const string& cipherText) 
{ 
	string plaintext;
	int klen = secretkey.length();
	int clen = cipherText.length();
	for (int i = 0 ; i < clen; i++){
		plaintext.push_back(((cipherText[i] - secretkey[i%klen] + 26) %26) + 'A');
	}
	return plaintext;
	
}

