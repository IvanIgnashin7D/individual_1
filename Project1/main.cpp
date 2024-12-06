#include <iostream>
#include <iomanip>
#include <math.h>


double func_coshx(double x, long double accyracy, double max_numbers, long double result_computer);


const char* ERROR_LETTER = "ОШИБКА: введёно не число.";
const char* ERROR_NEGATIVE = "ОШИБКА: введёно не положительное число.";
const char* ERROR_RANGE = "ОШИБКА: допустимые значения аргумента функции должны находиться на интервале (-1; 1).";
const char* ERROR_RANGE_ORDER = "ОШИБКА: левая граница области определения аргумента должна быть меньше правой.";
const char* ERROR_NOT_REACHED = "Точность не достигнута";


int main() {
	setlocale(LC_ALL, "ru");

	long double accuracy = 0;
	double max_numbers = 0;
	double interval_left = 0;
	double interval_right = 0;
	double step = 0;

	try {
		std::cout << "Введите точность вычисления: ";
		std::cin >> accuracy;
		if (std::cin.fail())
			throw ERROR_LETTER;
		if (accuracy <= 0)
			throw ERROR_NEGATIVE;

		std::cout << "Введите максимальное количество слагаемых: ";
		std::cin >> max_numbers;
		if (std::cin.fail())
			throw ERROR_LETTER;
		if (max_numbers <= 0)
			throw ERROR_NEGATIVE;

		std::cout << "Введите левую границу интервала вычислений: ";
		std::cin >> interval_left;
		if (std::cin.fail())
			throw ERROR_LETTER;
		if (interval_left <= -1)
			throw ERROR_RANGE;

		std::cout << "Введите правую границу интеревала вычислений: ";
		std::cin >> interval_right;
		if (std::cin.fail())
			throw ERROR_LETTER;
		if (interval_left >= 1)
			throw ERROR_RANGE;
		if (interval_left >= interval_right)
			throw ERROR_RANGE_ORDER;

		std::cout << "Введите шаг интервала вычислений: ";
		std::cin >> step;
		if (std::cin.fail())
			throw ERROR_LETTER;
		if (step <= 0)
			throw ERROR_NEGATIVE;
	}
	catch (const char* a) {
		std::cout << a;
		return 1;
	}


	std::cout << std::setw(7) << "X" << std::setw(25) << "Result C++" << std::setw(30) << "Result Taylor`s row" << std::endl;
	std::cout << "-----------------------------------------------------------------" << "\n";
	for (; interval_left <= interval_right; interval_left += step) {
		long double result_computer = cosh(interval_left);
		try{
			long double result_row = func_coshx(interval_left, accuracy, max_numbers, result_computer);

			std::cout << std::fixed << std::setprecision(10);

			if (interval_left >= 0)
				std::cout << std::setw(13) << interval_left << std::setw(20) << result_computer << std::setw(25) << result_row << std::endl;
			else 
				std::cout << interval_left << std::setw(20) << result_computer << std::setw(25) << result_row << std::endl;
		}
		catch (const char* a) {
			if (interval_left >= 0)
				std::cout << std::setw(13) << interval_left << std::setw(20) << result_computer << std::setw(30) << a << std::endl;
			else
				std::cout << interval_left << std::setw(20) << result_computer << std::setw(30) << a << std::endl;

		}
	}
}


double func_coshx(double x, long double accuracy, double max_numbers, long double result_computer) {
	long double result = 1;
	long double detorminator = 2.0;
	double count_denominator = 3.0;
	long double numerator = x * x;
	for (int i = 1; i <= max_numbers; i++) {
		result += numerator / detorminator;
		numerator = numerator * x * x;
		detorminator = detorminator * count_denominator * (count_denominator + 1);
		count_denominator += 2;
		
		if (result <= (result_computer + accuracy) && result >= (result_computer - accuracy))
			return result;
	}
	throw ERROR_NOT_REACHED;
}	