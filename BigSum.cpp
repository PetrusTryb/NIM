#include <iostream>
#include <string>
#include <vector>
using namespace std;
void moveDigits(vector<char> &a, vector<char> &b) {
	vector<char> first(a.begin(), a.end());
	vector<char> second(b.begin(), b.end());
	//Searching for comma
	unsigned int decimalPoint1 = distance(first.begin(), find(first.begin(), first.end(), ','));
	unsigned int decimalPoint2 = distance(second.begin(), find(second.begin(), second.end(), ','));
	//Checking sign of numbers
	bool firstMinus = first[0] == '-' ? true : false;
	bool secondMinus = second[0] == '-' ? true : false;
	//Moving number vectors until they both will have the same length and decimal point placement
	while (first.size() != second.size() || decimalPoint1 != decimalPoint2) {
		if (decimalPoint1 > decimalPoint2) {
			second.insert(second.begin() + secondMinus, '0');
			decimalPoint2++;
		}
		else if (decimalPoint1 < decimalPoint2) {
			first.insert(first.begin() + firstMinus, '0');
			decimalPoint1++;
		}
		else {
			if (first.size() > second.size()) {
				second.push_back('0');
			}
			else if (first.size() < second.size()) {
				first.push_back('0');
			}
		}
	}
	a = first;
	b = second;
}
int isMinus(char sign) {
	if (sign == '-')
		return -1;
	else
		return 1;
}
void calculate(vector<char> &a, vector<char> &b, vector<char> &final) {
	vector<char> first(a.begin(), a.end());
	vector<char> second(b.begin(), b.end());
	vector<char> result(final.begin(), final.end());
	for (int digit = first.size() - 1; digit >= 0; digit--) {
		if (first[digit] == ',')
			continue;
		int digitSum = isMinus(result[0])*(result[digit] - '0') + isMinus(second[0])*(second[digit] - '0');
		result[digit] = digitSum%10;
		if (digitSum / 10 > 0) {
			if (digit > 0) {
				if (result[digit - 1] == ',')
					result[digit - 2] += digitSum / 10;
				else
					result[digit - 1] += digitSum / 10;
			}
			else
				result.insert(result.begin(), digitSum / 10);
		}
		
	}
	final = result;
}
void print(vector<char> &table){
	vector<char> result(table.begin(), table.end());
	for (unsigned int index = 0; index < result.size(); index++) {
		if (result[index] != ',' && result[index] != '-')
			cout << (int)result[index];
		else
			cout << result[index];
	}
}
int main(){
	string temp1,temp2;
	cout << "Enter two numbers (use ',' as a decimal point)\n\a";
	cin >> temp1 >> temp2;
	vector<char> first(temp1.begin(), temp1.end());
	vector<char> second(temp2.begin(), temp2.end());
	vector<char> result(temp1.begin(), temp1.end());
	moveDigits(first, second);
	calculate(first, second, result);
	print(result);
	return 0;
}