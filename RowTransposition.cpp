#include "RowTransposition.h"


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool RowTransposition::setKey(const string& key)
{ 
	for(int i = 0; i< key.length(); i++){
		if(!isdigit(key[i]))
			return false;
	}
	secretkey = key;
	return true;  
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string RowTransposition::encrypt(const string& plaintext)
{ 
	string ciphertext = "";
	int maxCol = secretkey.length();
	int maxRow = ceil(plaintext.length()/(double)maxCol);
	int plaintextlength = plaintext.length();
	char matrix[maxRow][maxCol];
	int i = 0;

	//create matrix
	for(int r=0; r<maxRow; r++){
		for(int c=0; c<maxCol; c++){
			if(i < plaintextlength){
				matrix[r][c] = plaintext[i];
				i++;
			}
			else{
				matrix[r][c] = 'X';
			}
		}
	}

	//make ciphertext
	for (i=0; i<maxCol; i++){
		for (int r = 0; r<maxRow; r++){
			ciphertext.push_back(matrix[r][secretkey[i]-'1']);
		}
	}

	return ciphertext;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string RowTransposition::decrypt(const string& cipherText) 
{ 
	string plaintext = "";
	int maxCol = secretkey.length();
	int maxRow = cipherText.length()/maxCol;
	char matrix[maxRow][maxCol];
	int i = 0;

	//create matrix
	for(int c = 0; c < maxCol; c++){
		for(int r = 0; r< maxRow; r++){
			matrix[r][secretkey[c]-'1'] = cipherText[i];
			i++;
		}
	}
	
	//make plaintext
	for(int r=0; r<maxRow; r++){
		for(int c=0; c<maxCol; c++){
			plaintext.push_back(matrix[r][c]);
		}
	}
	return plaintext; 
	
}

