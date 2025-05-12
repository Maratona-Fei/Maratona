// Bitwise

// verifica se o bit k eh set
int check_kth_bit(int x, int k){
	return (x >> k) & 1;
}

// printa a posicao de todos os sets
void print_on_bits(int x){
	for(int k = 0; k < 32; k++){
		if(check_kth_bit(x, k)){
			cout<<k<<' ';
		}
	}
}

// seta o bit k
int set_kth_bit(int x, int k){
	return x | (1 << k);
}

// unseta o bit k
int unset_kth_bit(int x, int k){
	return x & (~(1 << k));
}

// toggle o o bit k
int toggle_kth_bit(int x, int k){
	return x ^ (1 << k);
}

bool check_power_of_2(int x){
	return __builtin_popcount(x) == 1;
}
