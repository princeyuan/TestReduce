#include <algorithm>

#include "getNFromM.h"

namespace CPPTestor
{
	/************************************************
	*��������:	C
	*��������:	�������,�����m������ȡn�����������
	*�������:	m,n	��m������ȡn����
	*�������:	��
	*����ֵ  :	������
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
	*��������:	NFromM
	*��������:	���ش�m������ȡn�������������
	*�������:	m,n	��m������ȡn����
	*�������:	out	��ά����, ��һά����ΪC(m, n), �ڶ�ά����Ϊn
	*����ֵ  :	��
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
	*��������:	getCombFromIndex
	*��������:	����nά���������list�е�����Index,ȷ������Ͼ�������Щ�������
	*�������:	index	ָ������ϵı��, ����˳��Ϊ(2,4): 01, 02, 03, 12, 13, 23 
	*�������:	out		һά����,����Ϊn+1,��¼����ϵ�n������
	*����ֵ  :	��
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
	*��������:	getColNum
	*��������:	��getNWayFromIndex����,ȷ������е�ĳ������
	*�������:	colOfN		ָ��nά�����ĳһ��
				prev		��colOfN-1�е�ȡֵ
	*�������:	colVal		��colOfN�е�ȡֵ
				index		����colOfN��,�޸�index��ֵ
	*����ֵ  :	��
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

