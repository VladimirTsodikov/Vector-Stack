#include <iostream>
#include "stack.h"
#include <string>

int main(int argc, char** argv)
{
	Stack<char> brc;
	bool flg = true;	//отвечает за корректность расставленных скобок
	for (int i = 1; i < argc && flg==true; i++)
	{
		cout << argv[i] << ' '<< strlen(argv[i]) << '\n';
		for (int j = 0;  flg == true && j < strlen(argv[i]); j++)
		{
			switch (*(argv[i] + j)) {
			case '[': brc.push('['); break;
			case '{': brc.push('{'); break;
			case '(': brc.push('('); break;
			
			case '}':
				//cout << brc.top() << '\n';
				if (brc.top() == '{') { brc.pop(); break; }
				else {
					flg = false;
					break;
				}

			case ']':
				//cout << brc.top() << '\n';
				if (brc.top() == '[') { brc.pop(); break; }
				else {
					flg = false;
					break;
				}

			case ')':
				//cout << brc.top() << '\n';
				if (brc.top() == '(') { brc.pop(); break; }
				else {
					flg = false;
					break;
				}

			default: break;
			}
		}
	}
	cout << brc << '\n';
	if (flg == true && brc.empty()) cout << "The introduced expression is correct";
	else cout << "The introduced expression is incorrect";

	Stack<> p(5);
	cin >> p;
	cout << p;
	return 0;
}