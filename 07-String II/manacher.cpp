vi manacher(string input){
	string str;
	for(auto x: input){
		str += x+"$";
	}
	str.pop_back();
	
	int n = str.length();
	vi len(n, 1);

	for(int i = 1, rightmost = 0, pivot = 0; i < n; i++){
		if(rightmost > i){
			int j = pivot-(i-pivot);
			len[i] = min(len[j], rightmost-i);
		}
		
		for( ; i >= len[i] && i+len[i] < n && str[i-len[i]] == str[i+len[i]]; len[i]++);
		
		if(i+len[i] > rightmost){
			rightmost = i+len[i];
			pivot = i;
		}
	}
	
	return len;
}
