
#ifndef GET_N_FROM_M_H
#define GET_N_FROM_M_H

#include <vector>

namespace CPPTestor
{
    class GetNFromM
    {
	public:
		void NFromM(int n, int m, 
			std::vector<std::vector<int> >& out);

	private:
		int n_;
		int m_;
		int len_;	// len_= C(m_, n_)

		void getCombFromIndex(int index, std::vector<int>& out);
		void getColNum(int colOfN, int& colVal, int& index, int prev);

        
    };	//class getNFromM
    
}	//namespace CPPTestor

#endif
