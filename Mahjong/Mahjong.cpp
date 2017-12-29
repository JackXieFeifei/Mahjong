// Mahjong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "AI/CMJ.h"
#include "AI/CMJManage.h"

#include <windows.h>
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	//�����������
	CMJ				t_OtherPlayer[3];
	//��
	CMJ				t_MyPlayer;
	//ϴ����
	CMJManage		t_MJManage;
	//����
	int				t_Score = 0;
GameStart:

	//��ʼ����ϴ��
	t_MJManage.InitPai();//��ʼ��
	t_MyPlayer.CleanUp();
	for (UINT i = 0; i < 3; i++)
	{
		t_OtherPlayer[i].CleanUp();
	}
	cout << "ϴ�����" << endl;
	cout << "����:========================================================" << endl;
	for (UINT i = 0; i < 13; i++)
	{

		stPAIEx t_Pai = t_MJManage.GetAPai();
		t_MyPlayer.AddPai(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);

		for (UINT j = 0; j < 3; j++)
		{
			stPAIEx t_Pai2 = t_MJManage.GetAPai();
			t_OtherPlayer[j].AddPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
		}
	}
	t_MyPlayer.Init();
	for (UINT j = 0; j < 3; j++)
	{
		t_OtherPlayer[j].Init();
	}
	//����ѭ��
	bool t_Finish = false;
	bool t_Ting = false;
	while (t_Finish == false)
	{

		t_MyPlayer.PrintAllPai();
		cout << endl;
		cout << "����:========================================================" << endl;
		stPAIEx t_Pai = t_MJManage.GetAPai();

		//ˢ���ҷ���ǽ
		t_MyPlayer.PrintPai(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);
		cout << endl;
		//���û����ͷ
		if (t_Ting == false)
		{
			cout << "Ҫ���Ǵ�Y/N";
			char t_Result;
			cin >> t_Result;
			if (t_Result == 'Y' || t_Result == 'y')
			{
				//����
				t_MyPlayer.AddPai(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);
				//���ƺ�����ж�
				t_Finish = t_MyPlayer.CheckAllPai(MJPAI_GETPAI);
				if (t_Finish)
				{
					printf("����!!!:%s-%d", t_MyPlayer.GetInfo()->m_GoodName, t_MyPlayer.GetInfo()->m_GoodValue);
					::Sleep(1000);
				}
				else
				{
					if (t_Pai.m_NewPai.m_Type == -1)//����������Ѵﵽ����
					{
						cout << endl;
						cout << "��ׯ�ˣ�������������������������" << endl;
						break;
					}

					t_MyPlayer.PrintAllPai();
					cout << endl;
				OUTPai:
					cout << "����ƣ���������ţ�";
					int PaiIndex;
					cin >> PaiIndex;
					if (t_MyPlayer.DelPai(PaiIndex) == false)
					{
						cout << "û�д���" << endl;
						goto OUTPai;
					}
					//==============================����ˢ��================================================
					cout << "����ˢ��============================" << endl;
					t_MyPlayer.PrintAllPai();
					cout << endl;
					//==============================================================================

					//======================����========================================================
					if (t_MyPlayer.CheckAllPai(MJPAI_PUTPAI))
					{

						char t_BTing;
						cout << "Ҫ������:(Y/N)";
						cin >> t_BTing;
						if (t_BTing == 'y' || t_BTing == 'Y')
						{
							t_Ting = true;
						}
					}
					//==============================================================================

				}
			}
			else
			{
				//======================����========================================================
				if (t_MyPlayer.CheckAllPai(MJPAI_PUTPAI))
				{

					char t_BTing;
					cout << "Ҫ������:(Y/N)";
					cin >> t_BTing;
					if (t_BTing == 'y' || t_BTing == 'Y')
					{
						t_Ting = true;
					}
				}
				//==============================================================================
			}
		}
		else
		{

			t_MyPlayer.AddPai(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);
			//����
			int iPaiIndex = t_MyPlayer.GetPaiIndex(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);
			if (iPaiIndex >= 0)
			{
				//���ƺ�����ж�
				t_Finish = t_MyPlayer.CheckAllPai(MJPAI_GETPAI);
				if (t_Finish)
				{
					cout << endl;
					printf("����!!!:%s-�ϼ�%d��", t_MyPlayer.GetInfo()->m_GoodName, t_MyPlayer.GetInfo()->m_GoodValue);
					t_Score += t_MyPlayer.GetInfo()->m_GoodValue;
					::Sleep(1000);
					break;
				}
				else
				{
					t_MyPlayer.DelPai(iPaiIndex);
					cout << "����";
					t_MyPlayer.PrintPai(t_Pai.m_NewPai.m_Type, t_Pai.m_NewPai.m_Value);
					cout << endl;
					::Sleep(1000);
				}
			}
			else
			{
				cout << "�������!" << endl;
			}

		}
		cout << endl;
		//����������Ƴ���
		for (UINT j = 0; j < 3; j++)
		{
			stPAIEx t_Pai2 = t_MJManage.GetAPai();
			if (j == 0)
			{
				cout << "�ϼ����Ƴ��ƣ�";
				t_MyPlayer.PrintPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				cout << endl;
				::Sleep(1000);
			}
			if (j == 1)
			{
				cout << "�������Ƴ��ƣ�";
				t_MyPlayer.PrintPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				cout << endl;
				::Sleep(1000);
			}
			if (j == 2)
			{
				cout << "�������Ƴ��ƣ�";
				t_MyPlayer.PrintPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				cout << endl;
				::Sleep(1000);
			}

			char t_Result;
			if (t_Ting == false)
			{
				if (t_Pai2.m_IsHZ)//����������Ѵﵽ����
				{
					cout << endl;
					cout << "��ׯ�ˣ�������������������������" << endl;
					t_Finish = true;
					break;
				}

				bool t_Check = false;
				//������
				if (t_MyPlayer.CheckChiPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value))
				{
					if (t_Check == false)
					{
						cout << "��ѡ��:";
					}
					cout << "(��)";
					t_Check = true;
				}
				//�������
				if (t_MyPlayer.CheckPengPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value))
				{
					if (t_Check == false)
					{
						cout << "��ѡ��:";
					}
					cout << "(��)";
					t_Check = true;
				}
				//������
				if (t_MyPlayer.CheckGangPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value))
				{
					if (t_Check == false)
					{
						cout << "��ѡ��:";
					}
					cout << "(��)";
					t_Check = true;
				}
				//����
				t_MyPlayer.AddPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				//���ƺ�����ж�
				if (t_MyPlayer.CheckAllPai(MJPAI_GETPAI))
				{
					if (t_Check == false)
					{
						cout << "��ѡ��:";
					}
					cout << "(��)";
					t_Check = true;
				}
				int iPaiIndex = t_MyPlayer.GetPaiIndex(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				t_MyPlayer.DelPai(iPaiIndex);
				//����鵽
				if (t_Check)
				{
					cout << endl;
					cin >> t_Result;
				}
				else
				{
					//����ѭ��
					continue;
				}
			}
			else
			{
				t_Result = '4';
			}
			//����
			if (t_Result == '1')
			{
				t_MyPlayer.PrintChiChosePai();

				int index = 0;
				//���������ϴ���
				if (t_MyPlayer.GetChiChoseNum() > 1)
				{
					cout << "��������Ϻ�:" << endl;
					cin >> index;
				}
				t_MyPlayer.DoChiPai(index, t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);

				//==============================================================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================

			OUTPai2:
				cout << "����ƣ���������ţ�";
				int PaiIndex;
				cin >> PaiIndex;
				if (t_MyPlayer.DelPai(PaiIndex) == false)
				{
					cout << "û�д���" << endl;
					goto OUTPai2;
				}

				//=================================����ˢ��=============================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================
				//======================����========================================================
				if (t_MyPlayer.CheckAllPai(MJPAI_PUTPAI))
				{

					char t_BTing;
					cout << "Ҫ������:(Y/N)";
					cin >> t_BTing;
					if (t_BTing == 'y' || t_BTing == 'Y')
					{
						t_Ting = true;
					}
				}
				//==============================================================================
				//�����¼�
				j = -1;

			}
			else if (t_Result == '2')//����
			{

				t_MyPlayer.PrintPengChosePai();
				t_MyPlayer.DoPengPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				//==============================================================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================
			OUTPai3:
				cout << "����ƣ���������ţ�";
				int PaiIndex;
				cin >> PaiIndex;
				if (t_MyPlayer.DelPai(PaiIndex) == false)
				{
					cout << "û�д���" << endl;
					goto OUTPai3;
				}
				//==========================����ˢ��====================================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================
				//======================����========================================================
				if (t_MyPlayer.CheckAllPai(MJPAI_PUTPAI))
				{

					char t_BTing;
					cout << "Ҫ������:(Y/N)";
					cin >> t_BTing;
					if (t_BTing == 'y' || t_BTing == 'Y')
					{
						t_Ting = true;
					}
				}
				//==============================================================================
				j = -1;

			}
			else if (t_Result == '3')//����
			{

				t_MyPlayer.PrintGangChosePai();
				t_MyPlayer.DoGangPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				cout << "��ܵ���" << endl;
				t_MyPlayer.AddPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				//==============================================================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================
				stPAIEx t_Pai2 = t_MJManage.GetAPai();

				//���ƺ�����ж�
				t_Finish = t_MyPlayer.CheckAllPai(MJPAI_GETPAI);
				if (t_Finish)
				{
					cout << "�ܵ׻���(Y/N)" << endl;
					char t_Result;
					cin >> t_Result;
					if (t_Result == 'Y' || t_Result == 'y')
					{
						cout << endl;
						printf("����!!!:%s-%d", t_MyPlayer.GetInfo()->m_GoodName, t_MyPlayer.GetInfo()->m_GoodValue);
						t_Score += t_MyPlayer.GetInfo()->m_GoodValue;
						::Sleep(1000);
						break;
					}
				}

				if (t_Pai2.m_IsHZ)//����������Ѵﵽ����
				{
					cout << "��ׯ�ˣ�������������������������" << endl;
					t_Finish = true;
					break;
				}

			OUTPai4:
				cout << "����ƣ���������ţ�";
				int PaiIndex;
				cin >> PaiIndex;
				if (t_MyPlayer.DelPai(PaiIndex) == false)
				{
					cout << "û�д���" << endl;
					goto OUTPai4;
				}
				//===========================����ˢ��===================================================
				cout << "����ˢ��============================" << endl;
				t_MyPlayer.PrintAllPai();
				cout << endl;
				//==============================================================================
				//======================����========================================================
				if (t_MyPlayer.CheckAllPai(MJPAI_PUTPAI))
				{

					char t_BTing;
					cout << "Ҫ������:(Y/N)";
					cin >> t_BTing;
					if (t_BTing == 'y' || t_BTing == 'Y')
					{
						t_Ting = true;
					}
				}
				//==============================================================================
				//�����¼�
				j = -1;

			}
			else if (t_Result == '4')//����
			{
				//����
				t_MyPlayer.AddPai(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
				//���ƺ�����ж�
				t_Finish = t_MyPlayer.CheckAllPai(MJPAI_GETPAI);
				if (t_Finish)
				{
					printf("����!!!:%s-�ϼ�%d��", t_MyPlayer.GetInfo()->m_GoodName, t_MyPlayer.GetInfo()->m_GoodValue);
					t_Score += t_MyPlayer.GetInfo()->m_GoodValue;
					::Sleep(1000);
					break;
				}
				else
				{
					if (t_Pai2.m_IsHZ)//����������Ѵﵽ����
					{
						cout << "��ׯ�ˣ�������������������������" << endl;
						t_Finish = true;
						break;
					}
					//����
					int iPaiIndex = t_MyPlayer.GetPaiIndex(t_Pai2.m_NewPai.m_Type, t_Pai2.m_NewPai.m_Value);
					cout << endl;
					t_MyPlayer.DelPai(iPaiIndex);
				}
			}

		}


	}
	cout << "�ҵķ�����" << t_Score << endl;
	::Sleep(3000);
	goto GameStart;//���¿�ʼһ��

	return 0;
}