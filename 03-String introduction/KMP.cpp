#include <bits/stdc++.h>

using namespace std;

string str;
int fail[100];

int main(){	
	fail[0] = -1;
	for(int z = -1, y = 1; y < str.length(); y++){
		while(z != -1 && str[z+1] != str[y]){
			z = fail[z];
		}
		
		if(str[z+1] == str[y])
			z++;
			
		fail[y] = z;
	}
	
	string text;
	for(int str_position = -1, text_position = 0; text_position < text.length(); text_position++){
		while(str_position != -1 && str[str_position+1] != text[text_position]){
			str_position = fail[str_position];
		}
		
		if(str[str_position+1] == text[text_position]){
			str_position++;
			if(str_position == str.length()){
				cout << "match found at position " << text_position-str.length() << endl;
			}
		}
	}

	return 0;
}

