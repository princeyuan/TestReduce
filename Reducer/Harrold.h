#ifndef HARROLD_H
#define HARROLD_H

#include "Reducer/Reducer.h"

namespace TestReduce
{
	class Harrold : public Reducer
    {
	public:
		void reduce(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests,
			std::list<TestCase*> &resultTests
			);

		char const * name() { return "Harrold"; }

	private:
		//typedef std::list<TestReq*> std::list<TestReq*>;
		//typedef std::list<TestCase*> std::list<TestCase*>;
		//typedef std::list<std::list<TestReq*> > std::list<std::list<TestReq*> >;

		//typedef std::list<TestReq*>::iterator std::list<TestReq*>::iterator;
		//typedef std::list<TestCase*>::iterator std::list<TestCase*>::iterator;
		//typedef std::list<std::list<TestReq*> >::iterator std::list<std::list<TestReq*> >::iterator;

		//typedef std::list<std::list<TestCase*>::iterator> std::list<std::list<TestCase*>::iterator>;

		void InitHarrold(
			const std::vector<TestReq*> &Reqs,
			const std::vector<TestCase*> &initTests
			);

		void PartitionReqs();

		void SatisfyMost_in_ReqSet(
			const std::list<std::list<TestReq*> >::iterator &,
			std::list<std::list<TestCase*>::iterator>&
			);

		std::list<TestCase*>::iterator SatisfyBest(const std::list<std::list<TestReq*> >::iterator &);

		void RefineReqs(const std::list<TestCase*>::iterator &);

		std::list<TestReq*> uncoveredReqs;
		std::list<TestCase*> leavedTests;

		std::list<std::list<TestReq*> > req_sets;
        
    };	//class Harrold
    
}	//namespace TestReduce

#endif
