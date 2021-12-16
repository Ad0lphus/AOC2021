#include <bits/stdc++.h>

using namespace std;

int final_answer = 0;

vector<int> hex_to_bin(string &hex){
	vector<int> answer;
	for(auto i : hex){
		int value;
		if('0' <= i && i <= '9'){
			value = i - '0';
		}
		else{
			value = 10 + i - 'A';
		}

		vector<int> dummy;
		for(int i = 0; i < 4; i++){
			dummy.push_back(value % 2);
			value /= 2;
		}
		reverse(dummy.begin(), dummy.end());
		for(int i = 0; i < 4; i++){
			answer.push_back(dummy[i]);
		}
	}
	return answer;
}

int bin_to_dec(vector<int>& binary, int src, int end){
	int answer = 0;
	int counter = 1;
	for(int i = end; i >= src; i--){
		answer += binary[i] * counter;
		counter *= 2;
	}
	return answer;
}

int parse(vector<int>& binary, int src){
	int index = src;
	int packet_version = bin_to_dec(binary, index, index + 2);
	final_answer += packet_version;

	index += 3;
	int type_id = bin_to_dec(binary, index, index + 2);
	index = index + 3;

	if(type_id == 4){
		vector<int> dummy;
		while(index <= binary.size()){
			for(int i = 1; i <= 4; i++){
				dummy.push_back(binary[index + i]);
			}
			if(binary[index] == 1){
				index += 5;
			}
			else{
				index += 5;
				break;
			}
		}
	}
	else{
		int length_type = binary[index++];
		if(length_type == 0){
			int length = bin_to_dec(binary, index, index + 14);
			index += 15;
			int next = index;
			while(next < index + length){
				next = parse(binary, next);
			}
			index = next;
		}
		else{
			int length = bin_to_dec(binary, index, index + 10);
			index += 11;

			int next = index;
			for(int i = 0; i < length; i++){
				next = parse(binary, next);
			}
			index = next;
		}
	}
	return index;
}

int main(){
   	ios_base::sync_with_stdio(false);
    ifstream input_file("../Input/day16.txt");
	string input;
	input_file >> input;

	vector<int> binary = hex_to_bin(input);
	parse(binary, 0);

	cout << "Puzzle 1: " << final_answer << endl;
}