
#ifndef REDUCER_H
#define REDUCER_H

#include <list>
#include <vector>
#include "Tests/TestReq.h"
#include "Tests/TestCase.h"

namespace TestReduce
{
    class Reducer
    {
	public:
		virtual void reduce(
			const std::vector<TestReq*> &reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			) = 0 ;

		virtual char const * name() = 0;

		//virtual ~Reducer() {}

    };	//class Reducer
    
}	//namespace TestReduce

#endif
