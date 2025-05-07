// Trie

// T.insert(s) - O(|s|*sigma)
// T.erase(s) - O(|s|)
// T.find(s) retorna a posicao, -1 se nao achar - O(|s|)
// T.count_pref(s) numero de strings que possuem s como prefixo - O(|s|)
// referencia: brunomaletta

struct Trie {
	vector<vector<int>> trie;
	vector<int> end, pref;
	
	Trie(){
		trie.push_back(vector<int>(26));
		end.push_back(0);
		pref.push_back(0);
	}

	void insert(string& str){
		int node = 0;

		for(char c : str){
			// cria um vertice com o char atual caso nao tenha
			if(!trie[node][c - 'a']){
				trie[node][c - 'a'] = trie.size();				
				trie.push_back(vector<int>(26));
				end.push_back(0), pref.push_back(0);
			}
			// continua o caminho na trie
			node = trie[node][c - 'a'], pref[node]++;
		}
		// aumenta o cont de palavras terminadas no vertice 'node'
		end[node]++, pref[0]++;
	}

	void erase(string& str){
		int at = 0;

		for(char c : str){
			int& node = trie[at][c - 'a'];

			at = node, pref[at]--;

			if(!pref[at]) node = 0;
		}
		end[at]--, pref[0]--;
	}

	int find(string& s){
		int node = 0;

		for(char c : s){
			node = trie[node][c - 'a'];

			if(!node) return -1;
		}
		
		return node;
	}

	int count_pref(string& s){
		int id = find(s);
		return id >= 0 ? pref[id] : 0;
	}
};
