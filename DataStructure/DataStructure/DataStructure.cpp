// DataStructure.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "stdafx.h"
#include "Hanoi.h"

enum class DS_Type
{
    SELECT,
    LINKED_LIST,
    STACK,
    QUEUE,
    CIRCULAR_QUEUE,
    LINKEDLIST_MEMORY_POOL_QUEUE,
    BINARY_TREE,
    HANOI,
    EXIT
};

enum class LL_Action
{
    LL_SELECT,
    LL_INSERT,
    LL_DELETE,
    LL_REVERSE,
    LL_PRINT
};

enum class S_Action
{
    S_SELECT,
    S_PUSH,
    S_POP,
    S_PEEK
};

enum class Q_Action
{
    Q_SELECT,
    Q_ENQUEUE,
    Q_DEQUEUE,
    Q_PEEK
};

enum class LLMP_Action
{
    LLMP_SELECT,
    LLMP_ENQUEUE,
    LLMP_DEQUEUE,
    LLMP_PEEK
};

#define ARRAY_INDEX 5
#define COUNT_TEST_FOR 1000000


int main()
{
    srand(time(NULL));

    bool isEnd = false;
    int nSelect = 0;
    int nActionSelect = 0;

    LinkedList<int>* list = new LinkedList<int>;
    Stack<int>* stack = new Stack<int>;
    Queue<int>* queue = new Queue<int>;
    Circular_Queue<int>* circular_queue = new Circular_Queue<int>(ARRAY_INDEX);
    LinkedList_MemoryPool_Queue<int>* LLMP_Queue = new LinkedList_MemoryPool_Queue<int>;
    BinaryTree<int>* BTree = new BinaryTree<int>;

    

    while (!isEnd)
    {
        switch ((DS_Type)nSelect)
        {
        case DS_Type::SELECT: default:
        {
            cout << "이용하실 자료구조 타입을 고르세요."<< endl << "(1.Linked-List 2.Stack 3.Queue 4.Circular_Queue 5.Linked-List Memory Pool 6.BinaryTree 7.Hanoi 8.Exit)" << endl;
            cout << "입력: ";
            cin >> nSelect;
            system("cls");
        }
        break;
        case DS_Type::LINKED_LIST:
        {
            if (nActionSelect == 0)
            {
                cout << "====================Linked_List====================" << endl;
                cout << "Linked-List에서 사용 할 기능을 고르세요.(1.Insert 2.Delete 3.Reverse 4.Print 5.Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "====================Linked_List====================" << endl;
                cout << "LINKED-LIST : INSERT" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                list->Insert(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "====================Linked_List====================" << endl;
                cout << "LINKED-LIST : DELETE" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                list->Delete(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "====================Linked_List====================" << endl;
                cout << "LINKED-LIST : REVERSE" << endl;
                cout << "List is Reversed!!" << endl;
                list->Reverse();
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                cout << "====================Linked_List====================" << endl;
                cout << "LINKED-LIST : PRINT" << endl;
                list->Print();
                while (!_kbhit())
                {
                    nActionSelect = 4;
                }
                system("cls");
                nActionSelect = 0;
            }
            else
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::STACK:
        {
            if (nActionSelect == 0)
            {
                cout << "====================Stack====================" << endl;
                cout << "Stack에서 사용 할 기능을 고르세요.(1.Push 2.Pop 3.Peek 4.Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "====================Stack====================" << endl;
                cout << "STACK : PUSH" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                stack->Push(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "====================Stack====================" << endl;
                cout << "STACK : POP" << endl;
                if (stack->IsEmpty())
                {
                    cout << "This STACK is Empty.." << endl;
                }
                else
                {
                    cout << "Pop form this STACK : " << stack->Pop() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "====================Stack====================" << endl;
                cout << "STACK : PEEK" << endl;
                if (stack->IsEmpty())
                {
                    cout << "This STACK is Empty.." << endl;
                }
                else
                {
                    cout << "Peek form this STACK : " << stack->Peek() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::QUEUE:
        {
            if (nActionSelect == 0)
            {
                cout << "====================Queue====================" << endl;
                cout << "Queue에서 사용 할 기능을 고르세요.(1.Enqueue 2.Dequeue 3.Peek 4.Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "====================Queue====================" << endl;
                cout << "QUEUE : ENQUEUE" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                queue->Enqueue(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "====================Queue====================" << endl;
                cout << "QUEUE : DEQUEUE" << endl;
                if (queue->IsEmpty())
                {
                    cout << "This QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Dequeue form this QUEUE : " << queue->DeQueue() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "====================Queue====================" << endl;
                cout << "QUEUE : PEEK" << endl;
                if (queue->IsEmpty())
                {
                    cout << "This QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Peek form this QUEUE : " << queue->Peek() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::CIRCULAR_QUEUE:
        {
            if (nActionSelect == 0)
            {
                cout << "===============Circular_Queue===============" << endl;
                cout << "Circular_Queue에서 사용 할 기능을 고르세요.(1.Enqueue 2.Dequeue 3.Peek 4.Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "===============Circular_Queue===============" << endl;
                cout << "CIRCULAR_QUEUE : ENQUEUE" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                circular_queue->EnQueue(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "===============Circular_Queue===============" << endl;
                cout << "CIRCULAR_QUEUE : DEQUEUE" << endl;
                if (circular_queue->IsEmpty())
                {
                    cout << "This CIRCULAR_QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Dequeue form this CIRCULAR_QUEUE : " << circular_queue->DeQueue() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "===============Circular_Queue===============" << endl;
                cout << "CIRCULAR_QUEUE : PEEK" << endl;
                if (circular_queue->IsEmpty())
                {
                    cout << "This CIRCULAR_QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Peek form this CIRCULAR_QUEUE : " << circular_queue->Peek() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::LINKEDLIST_MEMORY_POOL_QUEUE:
        {
            if (nActionSelect == 0)
            {
                cout << "===============Linked-List MemoryPool Queue===============" << endl;
                cout << "Linked-List MemoryPool Queue에서 사용 할 기능을 고르세요.(1.Enqueue 2.Dequeue 3.Peek 4.SpeedCheck 5.Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "===============Linked-List MemoryPool Queue===============" << endl;
                cout << "LINKED-LIST MEMORYPOOL QUEUE : ENQUEUE" << endl;
                cout << "입력: ";
                int value;
                cin >> value;
                LLMP_Queue->EnQueue(value);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "===============Linked-List MemoryPool Queue===============" << endl;
                cout << "LINKED-LIST MEMORYPOOL QUEUE : DEQUEUE" << endl;
                if (LLMP_Queue->IsQueueEmpty())
                {
                    cout << "This LINKED-LIST MEMORYPOOL QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Dequeue form this LINKED-LIST MEMORYPOOL QUEUE : " << LLMP_Queue->DeQueue() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "===============Linked-List MemoryPool Queue===============" << endl;
                cout << "LINKED-LIST MEMORYPOOL QUEUE : PEEK" << endl;
                if (LLMP_Queue->IsQueueEmpty())
                {
                    cout << "This CIRCULAR_QUEUE is Empty.." << endl;
                }
                else
                {
                    cout << "Peek form this LINKED-LIST MEMORYPOOL QUEUE : " << LLMP_Queue->Peek() << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                cout << "===============Linked-List MemoryPool Queue===============" << endl;
                cout << "LINKED-LIST MEMORYPOOL QUEUE : SPEED CHECK" << endl;
                cout << "몇번 반복 할까요? (x100만번) : ";
                int nCount = 0;
                cin >> nCount;
                nCount *= 1000000;

                DWORD dwStart, dwEnd, dwTime;

                dwStart = GetTickCount(); // 326070

                for (int i = 0; i < nCount; i++)
                    queue->Enqueue(20);
                
                for (int i = 0; i < nCount; i++)
                    queue->DeQueue();

                for (int i = 0; i < nCount; i++)
                    queue->Enqueue(20);

                for (int i = 0; i < nCount; i++)
                    queue->DeQueue();


                dwEnd = GetTickCount(); // 327070

                dwTime = dwEnd - dwStart;
                float fTime = dwTime / 1000.0f;

                cout << "일반 큐 : " << fTime << endl;

                dwStart = GetTickCount(); // 326070

                for (int i = 0; i < nCount; i++)
                    LLMP_Queue->EnQueue(20);

                for (int i = 0; i < nCount; i++)
                    LLMP_Queue->DeQueue();

                for (int i = 0; i < nCount; i++)
                    LLMP_Queue->EnQueue(20);

                for (int i = 0; i < nCount; i++)
                    LLMP_Queue->DeQueue();


                dwEnd = GetTickCount(); // 327070

                dwTime = dwEnd - dwStart;
                fTime = dwTime / 1000.0f;

                cout << "Linked-List MemoryPool 큐 : " << fTime << endl;
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 5)
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::BINARY_TREE:
        {
            if (nActionSelect == 0)
            {
                cout << "===============BinaryTree===============" << endl;
                cout << "BinaryTree에서 사용 할 기능을 고르세요.(1.Insert 2.Delete 3.Search 4.Print 5. Back)" << endl;
                cout << "입력: ";
                cin >> nActionSelect;
                system("cls");
            }
            else if (nActionSelect == 1)
            {
                cout << "===============BinaryTree===============" << endl;
                cout << "BINARY_TREE : INSERT" << endl;
                int key;
                int data;
                cout << "key값 입력: ";
                cin >> key;
                cout << "data값 입력: ";
                cin >> data;
             
                BTree->Insert(key, data);

                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 2)
            {
                cout << "===============BinaryTree===============" << endl;
                cout << "BINARY_TREE : DELETE" << endl;
                int key;
                cout << "key값 입력: ";
                cin >> key;
                BTree->Delete(key);
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 3)
            {
                cout << "===============BinaryTree===============" << endl;
                cout << "BINARY_TREE : SEARCH" << endl;
                int key;
                cout << "key값 입력: ";
                cin >> key;

                if (BTree->IsEmpty())
                {
                    cout << "This BINARY_TREE is Empty.." << endl;
                }
                else
                {
                    cout << "Search form this BINARY_TREE : " << BTree->Search(key) << endl;
                }
                Sleep(1000);
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 4)
            {
                cout << "===============BinaryTree===============" << endl;
                cout << "BINARY_TREE : PRINT" << endl;

                BTree->Print();
                while (!_kbhit())
                {
                    nActionSelect = 4;
                }
                system("cls");
                nActionSelect = 0;
            }
            else if (nActionSelect == 5)
            {
                nActionSelect = 0;
                nSelect = 0;
            }
        }
        break;
        case DS_Type::HANOI:
        {

            cout << "=================Hanoi=================" << endl;
            int num;
            cout << "하노이 탑 원판 갯수 입력 : ";
            cin >> num;

            if (num < 1)
            {
                nSelect = 0;
            }
            else
            {
                Hanoi* hanoi = new Hanoi(num);
                hanoi->Move(num, hanoi->m_stTower[0], hanoi->m_stTower[1], hanoi->m_stTower[2]);
                delete hanoi;
            }
        }
            break;
        case DS_Type::EXIT:
            return 0;
        break;
        }

    }
}

/*
    LinkedList Memory Pool Queue

    LinkedList 공간과 MemoryPool공간을 두개를 가지고 있고
    LinkedList에 New를 하기전에 MemoryPool공간에 Node가 있는지 확인하고 있으면 그대로 가져다가 LinkedList에 Insert를 함으로써 New로 생성하지 않도록 한다.
    LinkedList에서 delete를 할때 지우지 않고 LinkedList의 연결만 끊고 MemoryPool에 넣는다.
*/

/*
    Binary Tree 이진트리
    Node의 형태 : data, key, left, right
    기능: 삽입, 삭제, 검색, 출력(오름차순)
*/




//숙제 
//인간 찾기
//1번 주민은 무조건 인간이다
//처음 번호는 주민의 번호
//2번 번호는 해당 주민이 말하는 개수
//인간은 거짓말을 하지 않는다

//30명 치 만들고나서는 30명 정답 9명
//6만명 주민에서 찾는것 3초내에 찾을수 있게 만들기


/*
30                                                          
1 2     14 13                                              
2 8     1 7 19 15 4 5 10 12                                
3 2     1 2                                                
4 6     30 27 20 9 8 7                                     
5 10    11 12 13 14 15 16 17 18 19 20                      
6 5     5 4 3 2 1                                          
7 7     1 13 14 20 29 8 11                                 
8 5     11 29 17 14 20                                     
9 5     19 16 17 13 14                                     
10 4    29 20 19 17                                        
11 4    20 8 29 19                                         
12 10   1 2 3 4 5 6 7 8 9 10                               
13 5    1 14 17 29 19                                      
14 5    20 8 17 13 1                                       
15 13   1 3 5 7 9 11 30 29 28 25 24 23 10                  
16 8    1 9 7 3 21 28 22 25                                
17 4    14 13 8 29                                         
18 6    4 2 8 6 11 19                                      
19 3    13 11 29                                           
20 3    11 8 14                                            
21 8    1 2 3 4 5 6 7 8                                    
22 3    17 19 21                                           
23 12   2 4 6 8 12 13 18 16 24 26 28 29                    
24 6    4 14 24 6 16 26                                    
25 3    7 8 9                                              
26 8    25 29 27 24 21 19 12 4                             
27 5    1 9 5 22 24                                        
28 4    14 13 8 29                                         
29 5    13 19 17 8 11                                      
30 20   1 2 3 4 5 6 7 8 9 10 29 28 27 26 25 24 23 22 21 20 
*/