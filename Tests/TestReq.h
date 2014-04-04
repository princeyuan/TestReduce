#ifndef TEST_REQ_H
#define TEST_REQ_H

//SPECIAL USED FOR THE PROJECT BoolTest
#include <set>
#include <vector>
#include <algorithm>
//END SPECIAL USE 

#include "TestCase.h"

namespace TestReduce
{
    class TestReq
    {
	public:

		TestReq() {}
		//TestReq(int id) : id_(id) {}

		//int id() const { return id_; }

		//virtual bool satisfy(const TestCase *test) const = 0;
		//virtual bool isSubsetOf(const TestReq *req) const = 0;

		/*bool satisfy(const TestCase &t1, const TestCase &t2) const
		{ return satisfy(t1) && satisfy(t2); }*/

	private:

		//int id_;

	//SPECIAL USED FOR THE PROJECT BoolTest
	public:
		TestReq(const std::vector<int> &value)
			:m_all_kill_tests(value.begin(),value.end())
		{}
		bool satisfy(const TestCase *test) const
		{
			if(m_all_kill_tests.empty())return true;

			std::set<int>::const_iterator it=m_all_kill_tests.find(test->getValue());
			if(it!=m_all_kill_tests.end())
				return true;
			else
				return false;
		}
		bool isSubsetOf(const TestReq *req) const
		{
			return includes(req->m_all_kill_tests.begin(),req->m_all_kill_tests.end(),
				m_all_kill_tests.begin(),m_all_kill_tests.end());
		}
		const std::set<int> &getValue() const
		{
			return m_all_kill_tests;
		}
	private:
		std::set<int> m_all_kill_tests;
	//END SPECIAL USE 
        
    };	//class TestReq

	/*bool operator == (TestReq const& lhs, TestReq const& rhs);
	bool operator < (TestReq const& lhs, TestReq const& rhs);
	bool operator > (TestReq const& lhs, TestReq const& rhs);*/
    
}	//namespace TestReduce

#endif
