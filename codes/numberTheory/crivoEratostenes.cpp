const int MAX = 1e6;

bool eh_primo[MAX];

//Crivo Basico para achar todos os primos
// Complexidade O(nlnln*sqrt(n) + o(n)) 
void crivo(){
        memset(eh_primo , true , sizeof eh_primo);

        eh_primo[0] = eh_primo[1] = false;

        for(int i = 2 ; i * i <= MAX ; i++){
                if(eh_primo[i]){
                        for(int j = i * i ; j <= MAX ; j += i)
                            eh_primo[j] = false;
                    }
            }
    }

//Versao de crivo para pegar todos os divisores primos
//Complexidade O(nloglogn)

int primo[MAX];

void crivo2(){
   memset(primo , -1 , sizeof primo);
   primo[0] = 0; 

   for(int i = 2 ; i <= MAX ; i++){
	if(primo[i] == -1){//Caso o num seja primo,marca
					//tds os nums divisiveis por ele
		for(int j = i ; j <= MAX ; j+=i)
			if(primo[j] == -1)
				primo[j] = i;
		}
   }
}

void fatorizacao(int num){
	//Guarda a menor fatorizacao para qualquer numero
	vector<int>fatores;
	while(num != 1){
		   fatores.push_back(primo[num]);
		   num = num / primo[num];
		}
   for(auto& nums : fatores) cout << nums << " ";
   cout << endl;
}
