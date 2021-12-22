

#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <algorithm>
#include <queue>
#include <stack>

#include "Day18.h"

using namespace std;


class Day18
{
public:
	Day18()
	{
	}

	struct BTNode
	{
		BTNode* Left{ nullptr };
		BTNode* Right{ nullptr };
		BTNode* Parent{ nullptr };

		bool IsValueNode{ false };
		bool IsRegularNode{ false };

		int Depth{ 0 };
		int Value{ 0 };
	};

	void DeleteBTNode(BTNode* NodeToDelete)
	{
		if (NodeToDelete == nullptr)
		{
			return;
		}

		if (NodeToDelete->Left != nullptr)
		{
			DeleteBTNode(NodeToDelete->Left);
			delete NodeToDelete->Left;
			NodeToDelete->Left = nullptr;
		}

		if (NodeToDelete->Right != nullptr)
		{
			DeleteBTNode(NodeToDelete->Right);
			delete NodeToDelete->Right;
			NodeToDelete->Right = nullptr;
		}
	}

	void FixDepth(BTNode* Head, int currentDepth)
	{
		Head->Depth = currentDepth;

		if (Head->Left != nullptr)
		{
			bool IsLeftValueNode = Head->Left->IsValueNode;
			if (IsLeftValueNode)
			{
				FixDepth(Head->Left, currentDepth);
			}
			else
			{
				FixDepth(Head->Left, currentDepth + 1);
			}
		}

		if (Head->Right != nullptr)
		{
			bool IsRightValueNode = Head->Right->IsValueNode;
			if (IsRightValueNode)
			{
				FixDepth(Head->Right, currentDepth);
			}
			else
			{
				FixDepth(Head->Right, currentDepth + 1);
			}
		}

	}

	BTNode* AddTrees(BTNode* Left, BTNode* Right)
	{
		BTNode* NewHead = new BTNode;
		NewHead->Left = Left;
		NewHead->Right = Right;

		NewHead->IsValueNode = false;
		NewHead->Depth = 0;
		NewHead->Value = -1;

		NewHead->Parent = nullptr;
		Left->Parent = NewHead;
		Right->Parent = NewHead;

		if (Left->IsValueNode && Right->IsValueNode)
		{
			NewHead->IsRegularNode = true;
		}
		else
		{
			NewHead->IsRegularNode = false;
		}

		FixDepth(NewHead, 0);

		return NewHead;
	}

	BTNode* FindNodeToExplode(BTNode* Head)
	{
		if (Head->IsValueNode)
		{
			return nullptr;
		}

		if (Head->Depth == 4)
		{
			return Head;
		}
		else
		{
			BTNode* LeftToExplode = FindNodeToExplode(Head->Left);
			if (LeftToExplode != nullptr)
			{
				return LeftToExplode;
			}

			BTNode* RightToExplode = FindNodeToExplode(Head->Right);
			return RightToExplode;
		}
	}
		
	void ExplodeNode(BTNode* NodeToExplode, BTNode* Root)
	{
		vector<int*> OrderedList;

		vector<BTNode*> Queue;
		Queue.push_back(Root);

		if (!NodeToExplode->IsRegularNode)
		{
			cout << "wtf";
		}

 		while (Queue.size() > 0)
		{
			BTNode* Curr = Queue.back();
			Queue.pop_back();

			if (Curr->IsValueNode)
			{
				OrderedList.push_back(&(Curr->Value));
			}
			else
			{
				if (Curr->Right != nullptr)
				{
					//Queue.emplace(Queue.begin(), Curr->Right);
					Queue.push_back(Curr->Right);
				}

				if (Curr->Left != nullptr)
				{
					//Queue.emplace(Queue.begin(), Curr->Left);
					Queue.push_back(Curr->Left);
				}
			}
		}

		int* LeftValue = &(NodeToExplode->Left->Value);
		int* RightValue = &(NodeToExplode->Right->Value);

		for (int i = 0; i < OrderedList.size(); ++i)
		{
			if (LeftValue == OrderedList[i])
			{
				if (i > 0)
				{
					*(OrderedList[i - 1]) = *(OrderedList[i - 1]) + *LeftValue;

				}
			}

			if (RightValue == OrderedList[i])
			{
				if (i + 1 != OrderedList.size())
				{
					*(OrderedList[i + 1]) = *(OrderedList[i + 1]) + *RightValue;
				}
			}
		}

		DeleteBTNode(NodeToExplode->Left);
		DeleteBTNode(NodeToExplode->Right);

		NodeToExplode->Left = nullptr;
		NodeToExplode->Right = nullptr;

		NodeToExplode->Value = 0;
		NodeToExplode->Depth = NodeToExplode->Parent->Depth;
		NodeToExplode->IsRegularNode = false;
		NodeToExplode->IsValueNode = true;
		if (NodeToExplode->Parent->Right->IsValueNode && NodeToExplode->Parent->Left->IsValueNode)
		{
			NodeToExplode->Parent->IsRegularNode = true;
		}

	}

	BTNode* FindNodeToSplit(BTNode* Head)
	{
		if (Head->IsValueNode)
		{
			if (Head->Value > 9)
			{
				return Head;
			}

			return nullptr;
		}
		else
		{
			BTNode* LeftToSplit = FindNodeToSplit(Head->Left);
			if (LeftToSplit != nullptr)
			{
				return LeftToSplit;
			}

			BTNode* RightToSplit = FindNodeToSplit(Head->Right);
			return RightToSplit;
		}
	}

	void SplitNode(BTNode* Node)
	{
		if (!Node->IsValueNode)
		{
			cout << "wtf";
		}
		else
		{
			BTNode* NewLeft = new BTNode;
			BTNode* NewRight = new BTNode;

			NewLeft->Value = (Node->Value >> 1);
			NewRight->Value = (Node->Value >> 1) + (Node->Value % 2);

			Node->Depth += 1;

			NewLeft->Depth = Node->Depth;
			NewRight->Depth = Node->Depth;
			
			NewLeft->Parent = Node;
			NewRight->Parent = Node;

			NewLeft->IsValueNode = true;
			NewRight->IsValueNode = true;

			NewLeft->IsRegularNode = false;
			NewRight->IsRegularNode = false;

			NewLeft->Left = nullptr;
			NewLeft->Right = nullptr;
			NewRight->Left = nullptr;
			NewRight->Right = nullptr;

			Node->Left = NewLeft;
			Node->Right = NewRight;
			Node->Value = -1;
			Node->IsRegularNode = true;
			Node->IsValueNode = false;
		}
	}

	void ReduceTree(BTNode* Root, bool shouldPrint,  bool printDepth)
	{
		bool shouldBreak = false;
		while (!shouldBreak)
		{
			BTNode* NodeToExplodeOrSplit = FindNodeToExplode(Root);			
			if(NodeToExplodeOrSplit != nullptr)
			{
				ExplodeNode(NodeToExplodeOrSplit, Root);

				if (shouldPrint)
				{
					cout << "\n After Exploiding\n\n";

					print(Root, printDepth);
				}
				continue;
			}
			else
			{
				NodeToExplodeOrSplit = FindNodeToSplit(Root);
				if(NodeToExplodeOrSplit != nullptr)
				{
					SplitNode(NodeToExplodeOrSplit);
					if (shouldPrint)
					{
						cout << "\n After Splitting\n\n";

						print(Root, printDepth);
					}
					continue;
				}
			}

			shouldBreak = true;
		}
	}

	int GetMagnitude(BTNode* Node)
	{
		if (Node->IsValueNode)
		{
			return Node->Value;
		}
		else
		{
			int LeftMagnitude = GetMagnitude(Node->Left);
			int RightMagnitude = GetMagnitude(Node->Right);

			return (3 * LeftMagnitude) + (2 * RightMagnitude);
		}
	}

	BTNode* GetTreeFromString(string input, int currentDepth)
	{
		BTNode* NewHead = new BTNode;
		if (input.length() == 1)
		{
			if (input[0] >= '0' && input[0] <= '9')
			{
				NewHead->IsValueNode = true;
				NewHead->Value = input[0] - '0';
				NewHead->IsRegularNode = false;
				NewHead->Left = nullptr;
				NewHead->Right = nullptr;
			}
		}
		int NumOpen = 0;
		for (int i = 0; i < input.length(); ++i)
		{
			if (input[i] == ',')
			{
				if (NumOpen == 1)
				{
					string LeftString = input.substr(1, i-1);
					int count = input.length() - i - 1 - 1;
					string RightString = input.substr(i + 1, count);

					NewHead->Left = GetTreeFromString(LeftString, currentDepth + 1);
					NewHead->Right = GetTreeFromString(RightString, currentDepth + 1);

					NewHead->Left->Parent = NewHead;
					NewHead->Right->Parent = NewHead;

					NewHead->IsRegularNode = NewHead->Left->IsValueNode && NewHead->Right->IsValueNode;
					NewHead->IsValueNode = false;
					NewHead->Value = -1;
					NewHead->Left->Depth = NewHead->Left->IsValueNode ? currentDepth : currentDepth + 1;
					NewHead->Right->Depth = NewHead->Right->IsValueNode ? currentDepth : currentDepth + 1;
				}
			}
			else if (input[i] == '[')
			{
				NumOpen++;
			}
			else if (input[i] == ']')
			{
				NumOpen--;
			}
			else
			{
				continue;
			}
		}

		return NewHead;
	}

	void print(BTNode* Head, bool printDepth)
	{
		if (Head->IsValueNode)
		{
			cout << Head->Value;
			if (printDepth)
			{
				cout << "(" << Head->Depth << ")";
			}
			return;
		}

		cout << "[";
		print(Head->Left, printDepth);
		cout << ",";
		print(Head->Right, printDepth);
		cout << "]";
	}

	void Run()
	{

		ifstream infile("inputDay18.txt");

		string line;
		BTNode* CurrentHead = nullptr;

		bool printDepth = false;
		bool printReductions = false;

		vector<string> AllInputs;

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				AllInputs.push_back(line);
				cout << "\n\n NewLine - " << line << endl;
				BTNode* CurrentNode = GetTreeFromString(line, 0);
				if (CurrentHead != nullptr)
				{
					CurrentHead = AddTrees(CurrentHead, CurrentNode);
					
					cout << "Before Reducing \n";
					print(CurrentHead, printDepth);
					cout << endl;
					ReduceTree(CurrentHead, printReductions, printDepth);

					cout << "After Reducing \n";
					print(CurrentHead, printDepth);
					cout << endl;

				}
				else
				{
					CurrentHead = CurrentNode;
				}
			}

			int FinalMagnitude = GetMagnitude(CurrentHead);

			print(CurrentHead, printDepth);
			cout << endl;

			cout << FinalMagnitude<<endl;

			DeleteBTNode(CurrentHead);
			CurrentHead = nullptr;
		}

		int MaxMag = 0;

		for (int i = 0; i < AllInputs.size(); ++i)
		{
			for (int j = 0; j < AllInputs.size(); ++j)
			{
				if (i == j) continue;

				string first = AllInputs[i];
				string second = AllInputs[j];

				BTNode* NewHead = GetTreeFromString(first, 0);
				BTNode* ToAdd = GetTreeFromString(second, 0);
				NewHead = AddTrees(NewHead, ToAdd);

				ReduceTree(NewHead, printReductions, printDepth);

				ToAdd = nullptr;

				int Mag = GetMagnitude(NewHead);
				if (Mag > MaxMag)
				{
					MaxMag = Mag;
				}

				DeleteBTNode(NewHead);
				CurrentHead = nullptr;

			}
		}

		cout << "\n\nMAX =" << MaxMag;
	}

};

void RunDay18()
{
	Day18 Day18Obj;
	Day18Obj.Run();
}