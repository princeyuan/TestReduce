#ifndef TEST_CASE_H
#define TEST_CASE_H

namespace TestReduce
{
	class TestCase
	{
	public:

		TestCase() {}
		//TestCase(TestCase const& test) : id_(test.id_) {}

		//TestCase& operator = (const TestCase &rhs);

		//int id() const { return id_; }

		//virtual bool operator == (const TestCase &rhs) const = 0;

	private:

		//int id_;

	//SPECIAL USED FOR THE PROJECT BoolTest
	public:
		TestCase(int value)
			:m_value(value)
		{}
		int getValue() const
		{
			return m_value;
		}
	private:
		int m_value;
	//END SPECIAL USE 
	};

}//namespace TestReduce

#endif