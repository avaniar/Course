#include "pch.h"
#include "CppUnitTest.h"
#include "../Course/Header.h"
#include "../Course/Header.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		infix* infi;
		TEST_METHOD_INITIALIZE(setUp)
		{
			infi = new infix;
		}
		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete infi;
		}
		TEST_METHOD(incorrect_symbol_transfer)
		{
			Assert::IsFalse(infi->transfer("(5+6l)"));
		}
		TEST_METHOD(no_operator_check1)
		{
			infi->transfer("5(5+6)");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(no_operator_check2)
		{
			infi->transfer("(5+6)5");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(no_operand_check1)
		{
			infi->transfer("5*/5");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(no_operand_check2)
		{
			infi->transfer("(5*/5)*()");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(no_operator_check3)
		{
			infi->transfer("(5*/5)(");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(Unequal_left_and_right_parentheses_check)
		{
			infi->transfer("(5*/5))");
			Assert::IsFalse(infi->check());
		}
		TEST_METHOD(div_0_check)
		{
			infix prefix;
			double answer;
			infi->transfer("5/0");
			infi->Translationprefix(prefix);
			Assert::IsFalse(prefix.count(answer));
		}
		TEST_METHOD(undefined_ln_check)
		{
			infix prefix;
			double answer;
			infi->transfer("ln(-1)");
			infi->Translationprefix(prefix);
			Assert::IsFalse(prefix.count(answer));
		}
		TEST_METHOD(undefined_log10_check)
		{
			infix prefix;
			double answer;
			infi->transfer("log(-1)");
			infi->Translationprefix(prefix);
			Assert::IsFalse(prefix.count(answer));
		}
		TEST_METHOD(undefined_sqrt_check)
		{
			infix prefix;
			double answer;
			infi->transfer("sqrt(-1)");
			infi->Translationprefix(prefix);
			Assert::IsFalse(prefix.count(answer));
		}
		TEST_METHOD(Correct_count)
		{
			infix prefix;
			double answer;
			double answer2;
			infi->transfer("(sqrt(25)^5)/(55*log(100)*5^cos(60))");
			infi->Translationprefix(prefix);
			answer2 = ((pow(sqrt(25),5)) /(55 * log10(100) * pow(5,cos(60*PI/180))));
			prefix.count(answer);
			Assert::AreEqual(answer,answer2);
		}
		TEST_METHOD(Correct_count2)
		{
			infix prefix;
			double answer;
			double answer2;
			infi->transfer("sqrt(log(259*cos(69))/ctg(-8*ln(sin(59))))");
			infi->Translationprefix(prefix);
			answer2 = sqrt(log10(259 * cos(69 * PI / 180)) / (1 / tan((-8 * log(sin(59 * PI / 180)) * PI / 180))));
			prefix.count(answer);
			Assert::AreEqual(answer, answer2);
		}
	};
}
