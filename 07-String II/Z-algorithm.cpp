vi init(string str){
	int n = str.length();
	vi z(n, 0);
	// z[0] = 0;  special case
	for(int i = 1, rightmost = 0, pivot = 0; i < n; i++){
		if(rightmost > i){
			int j = i-pivot;
			z[i] = min(z[j], rightmost-i);
		}
		
		for( ; i+z[i] < n && str[z[i]] == str[i+z[i]]; z[i]++);
		
		if(i+z[i] > rightmost){
			pivot = i;
			rightmost = i+z[i];
		}
	}
	
	return z;
}

vi match(string pattern, string text){
	string str = pattern+"$"+text;
	vi z = init(str);
	vi match_position;
	for(int i = pattern.length()+1; i < str.length(); i++){
		if(z[i] == pattern.length()){
			match_position.push_back(i);
		}
	}
	
	return match_position;
}
