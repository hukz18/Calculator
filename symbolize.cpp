#include "symbolize.h"

monomial::monomial(string &exp)
{
	string expression;
	int power, pos, length = exp.length();
	coefficient = stod(exp);
	for (int i = 0; i < length; i++)
	{
		if (isalpha(exp[i]))
		{
			power = 1;
			if (exp[i + 1] == '^')
				power = stoi(exp.substr(i + 2));
			if (expression.find(string(1, exp[i])) != string::npos)
			{
				cout << "you have input repeated letter " << exp[i] << "!" << endl;
				pos = expression.find(string(1, exp[i]));
				if (expression[pos + 1] == '^')
				{
					power += stoi(expression.substr(pos + 2));
					while (isdigit(expression[pos + 2]))
						expression.erase(pos + 2, 1);
				}
				else expression.insert(pos, 1, '^');
				expression.insert(pos + 2, to_string(power));
			}
			else
			{
				expression.append(1, exp[i]);
				if (power > 1)
				{
					expression.append(1, '^');
					expression.append(to_string(power));
				}
			}
		}
	}
	this->expression = expression;
}

monomial monomial::operator*(monomial const & m2) const
{
	monomial result;
	result.coefficient = coefficient * m2.coefficient;
	result.expression = expression;
	int power, pos;
	int length1 = expression.length();
	int length2 = m2.expression.length();
	for (int i = 0; i < length2; i++)
	{
		if (isalpha(m2.expression[i]))
		{
			power = 1;
			if (m2.expression[i + 1] == '^')
				power = stoi(m2.expression.substr(i + 2));
			if (result.expression.find(string(1, m2.expression[i])) != string::npos)
			{
				pos = result.expression.find(string(1, m2.expression[i]));
				if (result.expression[pos + 1] == '^')
				{
					power += stoi(result.expression.substr(pos + 2));
					while (isdigit(result.expression[pos + 2]))
						result.expression.erase(pos + 2, 1);
				}
				else
				{
					power += 1;
					result.expression.insert(pos, 1, '^');
				}
				result.expression.insert(pos + 2, to_string(power));
			}
			else
			{
				result.expression.append(1, m2.expression[i]);
				if (power > 1)
				{
					result.expression.append(1, '^');
					result.expression.append(to_string(power));
				}
			}
		}
	}
	return result;
}

ostream & operator<<(ostream & output,monomial const & m)
{
	output << m.coefficient << m.expression;
	return output;
}
