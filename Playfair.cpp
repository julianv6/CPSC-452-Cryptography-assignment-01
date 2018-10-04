#include "Playfair.h"
#include <iostream> /*used for testing*/
#include <string>


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
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

	createMatrix();
	cout << "Secret key set\nMatrix created" << endl;
	return true;  
}




/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{  
	string text = plaintext;
	string ciphertext = "";
	int max = text.length();
	for (int i = 0; i<max; i+=2){
		if(isalpha(text[i])){
			/* check if pair or if last letter is single letter */
			if(i == max-1){
				text.push_back('X');
			}
			
			//check if letters are duplicates
			else if (text[i] == text[i+1]){
				text.insert(i+1,1,'X');
				max++;
			}
			
			//check if next letter is an alpha
			if (isalpha(text[i+1])){
				int x1,x2,y1,y2;
				x1 = getRow(text[i]);
				y1 = getCol(text[i]);
				x2 = getRow(text[i+1]);
				y2 = getCol(text[i+1]);

				if (x1==x2){
					ciphertext.push_back(getLetterAt(x1,++y1%5));
					ciphertext.push_back(getLetterAt(x2,++y2%5));
				}
				else if (y1==y2){
					ciphertext.push_back(getLetterAt(--x1%5,y1));
					ciphertext.push_back(getLetterAt(--x2%5,y2));
				}
				else {
					ciphertext.push_back(getLetterAt(x1,y2));
					ciphertext.push_back(getLetterAt(x2,y1));
				}
			}
			else{
				text.erase(i+1,1);
        		max--;
				i-=2;
			}

		}
		//ignore non alphas
		else{
			text.erase(i,1);
        	max--;
			i-=2;
		}
	}
	return ciphertext; 
}
int Playfair::getRow(char c){
	c = toupper(c);
	if(c == 'J')
		c = 'I';
	
	return (alphabet[(int)c - 65]/10)%10;
}
int Playfair::getCol(char c){
	c = toupper(c);
	if(c == 'J')
		c = 'I';
	
	return alphabet[(int)c - 65]%10;
}
char Playfair::getLetterAt(const int& x, const int& y){
	return matrix[x][y];
}
/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText) 
{ 
	string text = "";
	int max = cipherText.length();
	for(int i = 0; i< max; i+=2){
		int x1,x2,y1,y2;
		x1 = getRow(cipherText[i]);
		y1 = getCol(cipherText[i]);
		x2 = getRow(cipherText[i+1]);
		y2 = getCol(cipherText[i+1]);
		if (x1==x2){
			text.push_back(getLetterAt(x1,--y1%5));
			text.push_back(getLetterAt(x2,--y2%5));
		}
		else if (y1==y2){
			text.push_back(getLetterAt(++x1%5,y1));
			text.push_back(getLetterAt(++x2%5,y2));
		}
		else {
			text.push_back(getLetterAt(x1,y2));
			text.push_back(getLetterAt(x2,y1));
		}
	}
	return text;
}

void Playfair::printMatrix(FILE* fp){}

void Playfair::createMatrix(){
	for (int i = 0; i<26; i++){
		alphabet[i] = 0;
	}
	/* make the matrix
	 * loop through secretkey
	 *  if letter is used place in matrix[] otherwise move on
	 * loop through alphabet[]
	 *  if letter is not used place in matrix[] otherwise move on
	 */
	int row = 0;
	int col = 0;
	for (int i = 0; i< secretkey.length(); i++){
		if(alphabet[secretkey[i]-65] == 0){
			
			alphabet[secretkey[i]-65] = 100+row*10+col;
			matrix[row][col] = secretkey[i];
			
			if(++col == 5){
				col = 0;
				row++;
			}
			/* end of matrix check*/
			if (row == 5)
				break;
		}
	}

	for (int i = 0; i< 26; i++){
		if(i+65!=74 && alphabet[i] == 0){
			alphabet[i] = 100+row*10+col;
			matrix[row][col] = (char)(i+65);
			
			if(++col == 5){
				col = 0;
				row++;
			}
			/* end of matrix check*/
			if (row == 5)
				break;
		}
	}
	/* print resulting matrix*/
	for (int r = 0; r<5; r++){
		for(int c = 0; c<5; c++)
			cout << matrix[r][c];
		cout << endl;
	}
}
