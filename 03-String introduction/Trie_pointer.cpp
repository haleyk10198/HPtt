struct Node{
	map<char, Node*> children;
	Node(){
	}
}

void dfs(Node *node){
	for(auto [character, child]: children){
		dfs(child);
	}
}

void insert(string str, Node *root){
	for(auto x: str){
		if(not root->children.count(x))
			root->children[x] = new Node();
		root = root->children[x];
	}
	
	//do something on root
}
