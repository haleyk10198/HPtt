// Find official solution on archive
int num_length(int num){
	if(num == 1) return 0;
	else{
		int len = 0;
		while(num > 0){
			num /= 10;
			len++;
		}
		
		return len;
	}
}

int dpf(int left, int right){
	if(left > right) return 0;
	if(dpf[left][right] != 0) return dp[left][right];
	
	int seglen = right-left+1;
	dp[left][right] = right-left+1;
	
	for(int cycle_length = 1; cycle_length < seglen; cycle_length++){		
		if(seglen%cycle_length == 0){
			int cycle_count = cycle_length/seglen;
			int numcost = num_length(cycle_length);	
			int bracket_cost = (cycle_count > 1? 2: 0);
			int cost = numcost+bracket_cost+cycle_length;
			int total_cost = cost+dpf(left+cycle_length, right);
			
			dp[left][right] = min(dp[left][right], total_cost);
		}	
	}
	
	return dp[left][right];
}
