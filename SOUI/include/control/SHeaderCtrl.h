#pragma once

namespace SOUI
{
#define SHDI_WIDTH               0x0001
#define SHDI_TEXT                0x0002
#define SHDI_SORTFLAG            0x0004
#define SHDI_LPARAM              0x0008
#define SHDI_ORDER               0x0010
#define SHDI_VISIBLE             0x0020

#define CX_HDITEM_MARGIN    6
	/**
	* @enum      _SHDSORTFLAG
	* @brief     �����־
	*
	* Describe   �����־
	*/
	enum SHDSORTFLAG {
		ST_NULL = 0,
		ST_UP,
		ST_DOWN,
	};

	/**
	* @struct    _SHDITEM
	* @brief     �б�ͷ��
	*
	* Describe   �б�ͷ��
	*/
	typedef struct SHDITEM {
		SHDITEM() :mask(0), cx(0), stFlag(ST_NULL), iOrder(0), bVisible(true) {
		}
		UINT    mask;
		int cx;
		SHDSORTFLAG stFlag;
		int     iOrder;
		bool    bVisible;
	}*LPSHDITEM;


	/**
	* @class     SHeaderCtrl
	* @brief     ��ͷ�ؼ�
	*
	* Describe   ��ͷ�ؼ�
	*/
	class SHeaderItem;
	class SOUI_EXP SHeaderCtrl : public SWindow
	{
		SOUI_CLASS_NAME(SHeaderCtrl, L"header")
		friend class SHeaderItem;
	public:
		/**
		* SHeaderCtrl::SHeaderCtrl
		* @brief    ���캯��
		*
		* Describe  ���캯��
		*/
		SHeaderCtrl(void);
		/**
		* SHeaderCtrl::~SHeaderCtrl
		* @brief    ��������
		*
		* Describe  ��������
		*/
		~SHeaderCtrl(void);

		/**
		* SHeaderCtrl::InsertItem
		* @brief    ��������
		* @param    int iItem --  ��������
		* @param    LPCTSTR pszText  --  �������
		* @param    int nWidth  -- ���
		* @param    SHDSORTFLAG stFlag -- �����־
		* @param    LPARAM lParam -- ���Ӳ���
		* @return   ����int
		*
		* Describe  ��������
		*/
		int InsertItem(int iItem, LPCTSTR pszText, int nWidth, SHDSORTFLAG stFlag, LPARAM lParam);
		int GetItemWidth(int iItem);
		/**
		* SHeaderCtrl::GetItem
		* @brief    �������
		* @param    int iItem  --  ����
		* @param    SHDITEM *pItem  -- �����б���ṹ
		* @return   ����BOOL
		*
		* Describe  �������
		*/
		BOOL GetItem(int iItem, SHDITEM *pItem);

		/**
		* SHeaderCtrl::GetItemCount
		* @brief    ��ȡ�б������
		* @return   ����int
		*
		* Describe  ��ȡ�б������
		*/
		size_t GetItemCount() const { return m_arrItems.GetCount(); }
		/**
		* SHeaderCtrl::GetTotalWidth
		* @brief    ������п��
		* @return   ����int
		*
		* Describe  ������п��
		*/
		int GetTotalWidth();

		/**
		* SHeaderCtrl::DeleteItem
		* @brief    ɾ��ָ����
		* @param    int iItem  --  ����
		* @return   ����BOOL
		*
		* Describe  ɾ��ָ����
		*/
		BOOL DeleteItem(int iItem);

		/**
		* SHeaderCtrl::DeleteAllItems
		* @brief    ɾ��������
		*
		* Describe  �������
		*/
		void DeleteAllItems();

		void SetItemSort(int iItem, SHDSORTFLAG stFlag);

		void SetItemVisible(int iItem, bool visible);

		bool IsItemVisible(int iItem) const;

		SOUI_ATTRS_BEGIN()
			ATTR_INT(L"fixWidth", m_bFixWidth, FALSE)
			ATTR_INT(L"itemSwapEnable", m_bItemSwapEnable, FALSE)
			ATTR_INT(L"sortHeader", m_bSortHeader, FALSE)
			ATTR_BOOL(L"ratable", m_bRatable,FALSE)
		SOUI_ATTRS_END()
	protected:
		int ChangeItemPos(SHeaderItem* pCurMove, CPoint ptCur);
		void ChangeItemSize(SHeaderItem*, CPoint ptCur);
		/**
		* SHeaderCtrl::CreateChildren
		* @brief    ��������
		* @param    pugi::xml_node xmlNode  -- xml�����ļ�
		*
		* Describe  ��������
		*/
		virtual BOOL CreateChildren(pugi::xml_node xmlNode);

		bool ClickHeader(EventArgs * pEvArg);

		bool IsLastItem(int iOrder);

		SHeaderItem *GetPrvItem(int iIdx);
		virtual void UpdateChildrenPosition()override;
		virtual CSize GetDesiredSize(LPCRECT pRcContainer);
		
		BOOL          m_bSortHeader;      /**< ��ͷ���Ե������ */
		BOOL          m_bFixWidth;        /**< �����ȹ̶����� */
		BOOL          m_bItemSwapEnable;  /**< �����϶�����λ�ÿ��� */
		SArray<SHeaderItem*> m_arrItems;
		BOOL m_bRatable;
	};
}