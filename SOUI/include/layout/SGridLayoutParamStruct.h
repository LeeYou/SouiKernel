#pragma once

#include "SLayoutSize.h"

namespace SOUI
{

	enum GridGravity{
		gUndef=-1,	/**< δ���� */
		gLeft=0,	/**< ����� */
		gTop=0,		/**< �϶��� */
		gCenter=1,	/**< ���ж��� */
		gRight=2,	/**< �Ҷ��� */
		gBottom=2,	/**< �׶��� */
		gFill=3,	/**< ��չ���� */
	};

	/*
	* ���񲼾ֵ�Ԫ�����
	* remark: ���ͬһ���ж�����޸�ָ����rowWeight,ֻ��������һ����Ч����Ӧ��ͬһ����Ҳֻ������colWeight��Ч
	*/
	struct SGridLayoutParamStruct
	{
		int nColSpan;		/**< ����ռ���� */
		int nRowSpan;		/**< ����ռ���� */
		GridGravity layoutGravityX;/**< ����ˮƽ���뷽ʽ */
		GridGravity layoutGravityY;/**< ����ֱ���뷽ʽ */
		SLayoutSize  width;	/**< ������ */
		SLayoutSize  height;/**< ����߶� */
		float fColWeight;	/**< �����ȵļ�Ȩ */
		float fRowWeight;	/**< ����߶ȵļ�Ȩ */
	};

}