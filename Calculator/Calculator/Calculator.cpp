// Calculator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "stdafx.h"

enum TYPE {NUMBER, OPERATOR, BRACKET, MAX};

bool IsNumber(char txt);
bool IsOperator(char txt);
int GetPriority(char txt);
float Operate(float num1, char txt, float num2);



int main()
{
    char* _chInfix = new char[1024];
    memset(_chInfix, '\0', sizeof(_chInfix));

    FILE* pFile;
    fopen_s(&pFile, "../calc.txt", "r");

    fgets(_chInfix, 1024, pFile);

    Queue* tempQueue = new Queue;
    vector<TYPE> vecType;
    Queue* queue = new Queue;
    Stack* stack = new Stack;
    vector<float> vecValues;

    
        
        

    //읽어드릴 단위 구분해서 큐에 삽입해 놓기
    {
        char ch;
        int index = 0;
        ch = _chInfix[index];
        char* temp;
        int len;

        while (ch != '\0')
        {
            if (IsOperator(ch))
            {
                //연산자일경우
                if (ch == '-')
                {
                    if (index == 0)
                    {
                        temp = new char[1024];
                        memset(temp, '\0', sizeof(temp));
                        len = strlen(temp);
                        temp[len] = ch;
                        temp[len + 1] = '\0';
                        index++;
                        ch = _chInfix[index];

                        while (IsNumber(ch))
                        {
                            len = strlen(temp);
                            temp[len] = ch;
                            temp[len + 1] = '\0';
                            index++;
                            ch = _chInfix[index];
                        }
                        tempQueue->Enqueue(temp);
                        vecType.push_back(NUMBER);
                    }
                    else if (!IsNumber(_chInfix[index - 1]) && _chInfix[index - 1] != ')')
                    {
                        temp = new char[1024];
                        memset(temp, '\0', sizeof(temp));
                        len = strlen(temp);
                        temp[len] = ch;
                        temp[len + 1] = '\0';
                        index++;
                        ch = _chInfix[index];

                        while (IsNumber(ch))
                        {
                            len = strlen(temp);
                            temp[len] = ch;
                            temp[len + 1] = '\0';
                            index++;
                            ch = _chInfix[index];
                        }
                        tempQueue->Enqueue(temp);
                        vecType.push_back(NUMBER);
                    }
                    else
                    {
                        temp = new char[1024];
                        memset(temp, '\0', sizeof(temp));
                        len = strlen(temp);
                        temp[len] = ch;
                        temp[len + 1] = '\0';
                        tempQueue->Enqueue(temp);
                        vecType.push_back(OPERATOR);
                        index++;
                        ch = _chInfix[index];
                    }
                }
                else
                {
                    temp = new char[1024];
                    memset(temp, '\0', sizeof(temp));
                    len = strlen(temp);
                    temp[len] = ch;
                    temp[len + 1] = '\0';
                    tempQueue->Enqueue(temp);
                    vecType.push_back(OPERATOR);
                    index++;
                    ch = _chInfix[index];
                }
            }//연산자일경우
            else if (IsNumber(ch))
            {
                //숫자일경우
                temp = new char[1024];
                memset(temp, '\0', sizeof(temp));
                len = strlen(temp);
                temp[len] = ch;
                temp[len + 1] = '\0';
                index++;
                ch = _chInfix[index];

                while (IsNumber(ch))
                {
                    len = strlen(temp);
                    temp[len] = ch;
                    temp[len + 1] = '\0';
                    index++;
                    ch = _chInfix[index];
                }
                tempQueue->Enqueue(temp);
                vecType.push_back(NUMBER);
            }//숫자일경우
            else
            {
                //괄호일경우
                temp = new char[1024];
                memset(temp, '\0', sizeof(temp));
                len = strlen(temp);
                temp[len] = ch;
                temp[len + 1] = '\0';
                tempQueue->Enqueue(temp);
                vecType.push_back(BRACKET);
                index++;
                ch = _chInfix[index];
            }//괄호일경우
        }
    }
    //읽어드릴 단위 구분해서 큐에 삽입해 놓기
    
    //PostFix Rotation

    char* printTemp;
    cout << "Infix : ";
    while (!tempQueue->IsEmpty())
    {
        printTemp = tempQueue->Dequeue()->m_strData;
        cout << printTemp << " ";
        queue->Enqueue(printTemp);
    }
    cout << endl;

    while (!queue->IsEmpty())
    {
        tempQueue->Enqueue(queue->Dequeue()->m_strData);
    }


    while (!tempQueue->IsEmpty())
    {
        char* temp = NULL;
        temp = tempQueue->Dequeue()->m_strData;
        if (vecType[0] == NUMBER)
        {
            //숫자면 queue 에 삽입
            queue->Enqueue(temp);
            vecType.erase(vecType.begin());
        }
        else if (vecType[0] == OPERATOR)
        {
            //연산자면 stack의 top에 넣는 연산자보다 낮은 우선순위가 나올때까지 pop한뒤 push한다.
            if (stack->IsEmpty())
            {
                stack->Push(temp);
                vecType.erase(vecType.begin());
            }
            else
            {
                while (!stack->IsEmpty() && GetPriority(temp[0]) <= GetPriority(stack->m_pTop->m_strData[0]))
                {
                    queue->Enqueue(stack->Pop()->m_strData);
                }

                stack->Push(temp);
                vecType.erase(vecType.begin());
            }
        }
        else
        {
            
            if (temp[0] == '(')//여는 괄호라면
            {
                stack->Push(temp);
                vecType.erase(vecType.begin());
            }
            else//닫는 괄호라면
            {
                vecType.erase(vecType.begin());
                
                temp = stack->Pop()->m_strData;
                while (temp[0] != '(')
                {
                    queue->Enqueue(temp);
                    temp = stack->Pop()->m_strData;
                }
            }
        }   
    }
    
    while (!stack->IsEmpty())
    {
        queue->Enqueue(stack->Pop()->m_strData);
    }
    // 여기 까지가 Postfix Rotation 완료

    //while (!queue->IsEmpty())
    //{
    //    cout << queue->Dequeue()->m_strData << " ";
    //}

    //Postfix계산부

    cout << "Postfix : ";
    while (!queue->IsEmpty())
    {
        printTemp = queue->Dequeue()->m_strData;
        cout << printTemp << ", ";
        tempQueue->Enqueue(printTemp);
    }
    cout << endl;

    while (!tempQueue->IsEmpty())
    {
        queue->Enqueue(tempQueue->Dequeue()->m_strData);
    }


    while (!queue->IsEmpty())
    {

        //cout << queue->Dequeue()->m_strData << " ";

        char* temp = queue->Dequeue()->m_strData;
        
        if (IsOperator(temp[0]))
        {
            if (temp[1] == '\0')
            {
                float tempPop1 = vecValues[vecValues.size() - 1];
                vecValues.pop_back();
                float tempPop2 = vecValues[vecValues.size() - 1];
                vecValues.pop_back();
                float value = Operate(tempPop2, temp[0], tempPop1);
        
                vecValues.push_back(value);
            }
            else
            {
                vecValues.push_back(atof(temp));
            }
        }
        else
        {
            vecValues.push_back(atof(temp));
        }
    }
    
    cout << vecValues[0] << endl;
    
    delete tempQueue;
    delete queue;
    delete stack;

    fclose(pFile);

}

bool IsOperator(char txt)
{
    if (txt == '+' || txt == '-' || txt == '/' || txt == '*')
        return true;
    else
        return false;
}

bool IsNumber(char txt)
{
    if (IsOperator(txt) || txt == '(' || txt == ')' || txt == '\0')
        return false;
    else
        return true;
}


int GetPriority(char txt)
{
    if (txt == '(')
    {
        return 0;
    }
    else if (txt == '+' || txt == '-')
    {
        return 1;
    }
    else if (txt == '*' || txt == '/')
    {
        return 2;
    }
    else
    {
        cout << "Error!! : Operator Priority is Error !!" << endl;
        exit(-1);
    }
}

float Operate(float num1, char txt, float num2)
{
    if (txt == '+')
        return num1 + num2;
    else if (txt == '-')
        return num1 - num2;
    else if (txt == '*')
        return num1 * num2;
    else
        return num1 / num2;
}





/*
    PostFix계산하기
    피연산자는 포스트 픽스 큐에 담는다
    연산자는 연산자 우선순위 규칙을 통해서 스택에 담는다.

    Infix ->PostFix

    연산자를 스택에 담을때 기존에 들어가 있는 연산자 중에 자기 자신 보다 낮은 우선 순위를 만날때 까지 팝을 해서 큐에넣고 그 다음에 스택에 담는다.

    ( 는 우선 큐에 넣는다.

    2 + 6 - (3 - 1 x 5) - 6 / 2

    Queue : 2, 6, +, 3, 1, 5, x, -, -, 6, 2, /, -

    Stack : 

    PR Complete.

    Queue : 

    Stack : 10, 3, -  = 7


*/

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.


