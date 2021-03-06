// BTL_HMDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BTL_HM.h"
#include "BTL_HMDialog.h"


// CBTL_HMDialog dialog

IMPLEMENT_DYNAMIC(CBTL_HMDialog, CDialog)

CBTL_HMDialog::CBTL_HMDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBTL_HMDialog::IDD, pParent)
{
}

CBTL_HMDialog::~CBTL_HMDialog()
{
}

void CBTL_HMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, textFolderTrain);
	DDX_Control(pDX, IDC_EDIT2, textFolderTest);
	DDX_Control(pDX, IDC_BUTTON1, btTrain);
	DDX_Control(pDX, IDC_BUTTON2, btTest);
	DDX_Control(pDX, IDC_BUTTON3, btEvaluate);
}


BEGIN_MESSAGE_MAP(CBTL_HMDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CBTL_HMDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBTL_HMDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBTL_HMDialog::OnBnClickedButton3)
END_MESSAGE_MAP()


// CBTL_HMDialog message handlers

void CBTL_HMDialog::OnBnClickedButton1()//Bắt đầu huấn luyện
{
	// TODO: Add your control notification handler code here
	
	//Đọc danh sách thư từ tệp
	textFolderTrain.GetWindowText(m_sFolderTrain);
	GetMail(m_sFolderTrain + _T("\\") + SZ_NAME_FILE_NORMAL_TRAIN, 
		m_listMailTrainNormal);
	GetMail(m_sFolderTrain + _T("\\") + SZ_NAME_FILE_SPAM_TRAIN, 
		m_listMailTrainSpam);
// 
// 	//Tìm các từ khóa quan trọng
	GetFrequency(m_listMailTrainNormal, m_listTokenNormal);
	GetFrequency(m_listMailTrainSpam, m_listTokenSpam);
  	GetKey(m_listTokenNormal, m_listTokenSpam, m_listKey);
	m_nKeyNumber = m_listKey.GetCount();

// 
// 	Tính xác suất của mỗi từ khóa với mỗi nhãn lớp spam/normal
	CalculateProbability(m_listMailTrainNormal, m_listKey, m_listProbabilityKeyOnNormal);
 	CalculateProbability(m_listMailTrainSpam, m_listKey, m_listProbabilityKeyOnSpam);

	//Đã xong giai đoạn huấn luyện
}

void CBTL_HMDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	textFolderTest.GetWindowText(m_sFolderTest);
	GetMail(m_sFolderTest + _T("\\") + SZ_NAME_FILE_NORMAL_TEST, 
		m_listMailTestNormal);
	GetMail(m_sFolderTest + _T("\\") + SZ_NAME_FILE_SPAM_TEST, 
		m_listMailTestSpam);

}

void CBTL_HMDialog::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
}
void CBTL_HMDialog::GetMail(__in CString sPath, __out CStringList& sListMail)
{
	sListMail.RemoveAll();
	return;
}
void CBTL_HMDialog::GetFrequency(CStringList& listMail, __out TOKEN_LIST& listToken)
{
	listToken.RemoveAll();
	return;
}
BOOL operator == (TOKEN_INFO token1, TOKEN_INFO token2)
{
	return (token1.sTokenName.Compare(token2.sTokenName) == 0);
}
void CBTL_HMDialog::GetKey(TOKEN_LIST& listNormal, TOKEN_LIST& listSpam, __out CStringList& listKey)
{
	int nIndexSpam, nIndexNormal;
	POSITION posAppear;
	TOKEN_INFO infoTokenNormal, infoTokenSpam;
	
	listKey.RemoveAll();

	//Tìm các token chỉ xuất hiện trong tập thường
	for (nIndexNormal = 0; nIndexNormal < listNormal.GetCount(); nIndexNormal++)
	{
		infoTokenNormal = listNormal.GetAt(listNormal.FindIndex(nIndexNormal));
		posAppear = listSpam.Find(infoTokenNormal);
		if (posAppear == NULL)
			listKey.AddTail(infoTokenNormal.sTokenName);
	}

	//Tìm các token chỉ xuất hiện trong tập rác
	for (nIndexSpam = 0; nIndexSpam < listSpam.GetCount(); nIndexSpam++)
	{
		infoTokenSpam = listSpam.GetAt(listSpam.FindIndex(nIndexSpam));
		posAppear = listNormal.Find(infoTokenSpam);
		if (posAppear == NULL)
			listKey.AddTail(infoTokenSpam.sTokenName);
	}

	//Tìm các token xuất hiện trong cả 2 tập, so sánh
	for (nIndexNormal = 0; nIndexNormal < listNormal.GetCount(); nIndexNormal++)
	{
		infoTokenNormal = listNormal.GetAt(listNormal.FindIndex(nIndexNormal));
		posAppear = listSpam.Find(infoTokenNormal);
		if (posAppear != NULL)
		{
			infoTokenSpam = listSpam.GetAt(posAppear);
			double dPorportion;
			dPorportion = infoTokenNormal.dPercent / (infoTokenNormal.dPercent + infoTokenSpam.dPercent);
			if ((dPorportion < 0.2) || (dPorportion > 0.8))
				listKey.AddTail(infoTokenNormal.sTokenName);
		}
	}

	return;
}
void CBTL_HMDialog::GetAppearOneMail(CStringList& listKey, CString sMail, __out NUMBER_LIST& listFrequency)
{
	listFrequency.RemoveAll();
	return;
}
void CBTL_HMDialog::CalculateProbability(CStringList& listMail, CStringList& listKey, __out TOKEN_LIST& listProbability)
{
	listProbability.RemoveAll();
	return;
}

