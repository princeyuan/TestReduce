#include <algorithm>

#include "getNFromM.h"

namespace CPPTestor
{
	/************************************************
	*函数名称:	C
	*功能描述:	组合算子,计算从m个数中取n个数的组合数
	*输入参数:	m,n	从m个数中取n个数
	*输出参数:	无
	*返回值  :	计算结果
	*************************************************/
	int C(int m,int n)
	{
		if((m<n)||(m<=0)||(n<0))
		{
			return 1;
		}
		else if((m==n)||(n==0))
		{
			return 1;
		}

		int high=m;
		for(int i=1;i<=n-1;++i)
		{
			high=high*(m-i);
		}

		int low=n;
		for(int j=n-1;j>=2;--j)
		{
			low=low*j;
		}

		return high/low;
	}

	/************************************************
	*函数名称:	NFromM
	*功能描述:	返回从m个数中取n个数的所有组合
	*输入参数:	m,n	从m个数中取n个数
	*输出参数:	out	两维数组, 第一维长度为C(m, n), 第二维长度为n
	*返回值  :	无
	*************************************************/
	void GetNFromM::NFromM(int n, int m, 
		std::vector<std::vector<int> >& out)
	{
		n_ = n;
		m_ = m;
		len_ = C(m_, n_);

		for(int i=0; i<len_; ++i)
		{
			std::vector<int> comb(n+1);	// !! n+1 !! 
			getCombFromIndex(i, comb);

			std::vector<int> result(n);
			std::vector<int>::iterator begin = comb.begin();
			std::copy(++begin, comb.end(), result.begin());

			out.push_back(result);
		}
	}


	/************************************************
	*函数名称:	getCombFromIndex
	*功能描述:	根据n维参数组合在list中的索引Index,确定该组合具体由哪些参数组成
	*输入参数:	index	指定的组合的编号, 编排顺序为(2,4): 01, 02, 03, 12, 13, 23 
	*输出参数:	out		一维数组,长度为n+1,记录了组合的n个参数
	*返回值  :	无
	*************************************************/
	void GetNFromM::getCombFromIndex(int index, std::vector<int>& out)
	{
		out[0]=-1;
		for(int i=1; i<=n_; ++i)
		{
			getColNum(i, out[i], index, out[i-1]);
		}
	}

	/************************************************
	*函数名称:	getColNum
	*功能描述:	由getNWayFromIndex调用,确定组合中的某个参数
	*输入参数:	colOfN		指定n维组合中某一列
				prev		第colOfN-1列的取值
	*输出参数:	colVal		第colOfN列的取值
				index		根据colOfN列,修改index的值
	*返回值  :	无
	*************************************************/
	void GetNFromM::getColNum(int colOfN, int& colVal, int& index, int prev)
	{
		int count=0;
		for(int i=prev+1; ; ++i)
		{
			int j = i-(prev+1);
			int m = C(m_-j-prev-2, n_-colOfN);
			count += m;

			if(count > index)
			{
				colVal = i;
				index -= (count-m);
				break;
			}
		}
	}

}	//namespace CPPTestor

