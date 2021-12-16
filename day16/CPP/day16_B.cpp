#include <bits/stdc++.h>

using namespace std;

vector<long long> hex_to_bin(string &hex){
	vector<long long> answer;
	for(auto i : hex){
		long long value;
		if('0' <= i && i <= '9'){
			value = i - '0';
		}
		else{
			value = 10 + i - 'A';
		}

		vector<long long> dummy;
		for(long long i = 0; i < 4; i++){
			dummy.push_back(value % 2);
			value /= 2;
		}
		reverse(dummy.begin(), dummy.end());
		for(long long i = 0; i < 4; i++){
			answer.push_back(dummy[i]);
		}
	}
	return answer;
}

long long bin_to_dec(vector<long long>& binary, long long src, long long end){
	long long answer = 0;
	long long counter = 1;
	for(long long i = end; i >= src; i--){
		answer += binary[i] * counter;
		counter *= 2;
	}
	return answer;
}

pair<long long, long long> parse(vector<long long>& binary, long long src){
	long long answer = 0;
	long long index = src;
	long long packet_version = bin_to_dec(binary, index, index + 2);

	index += 3;
	long long type_id = bin_to_dec(binary, index, index + 2);

	index = index + 3;


	if(type_id == 4){
		vector<long long> dummy;
		while(index <= binary.size()){
			for(long long i = 1; i <= 4; i++){
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
		answer = bin_to_dec(dummy, 0, dummy.size() - 1);
		return {index, answer};
	}
	else{
		vector<long long> test;
		long long length_type = binary[index++];
		if(length_type == 0){
			long long length = bin_to_dec(binary, index, index + 14);
			index += 15;
			pair<long long, long long> next = {index, -1};
			while(next.first < index + length){
				next = parse(binary, next.first);
				test.push_back(next.second);
			}
			index = next.first;
		}
		else{
			long long length = bin_to_dec(binary, index, index + 10);
			index += 11;

			pair<long long, long long> next = {index, -1};
			for(long long i = 0; i < length; i++){
				next = parse(binary, next.first);
				test.push_back(next.second);
			}
			index = next.first;
		}

		if(type_id == 0){
			for(auto i : test){
				answer += i;
			}
		}
		else if(type_id == 1){
			answer = 1;
			for(auto i : test){
				answer *= i;
			}
		}
		else if(type_id == 2){
			answer = *min_element(test.begin(), test.end());
		}
		else if(type_id == 3){
			answer = *max_element(test.begin(), test.end());
		}
		else if(type_id == 5){
			answer = test[0] > test[1];
		}
		else if(type_id == 6){
			answer = test[0] < test[1];
		}
		else{
			answer = test[0] == test[1];
		}
		return {index, answer};
	}
}

int main(){
   	ios_base::sync_with_stdio(false);
    ifstream input_file("../../Input/day16.txt");
	string input;
	input_file >> input;

	vector<long long> binary = hex_to_bin(input);

	pair<long long, long long> dummy = parse(binary, 0);
	cout << "Puzzle 2: " << dummy.second << endl;;
}