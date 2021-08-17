#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
using namespace std;

#define SAFE_DELETE(p)			{ if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { p->Release(); (p) = NULL; } }


#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "Circular_Queue.h"
#include "LinkedList_MemoryPool_Queue.h"
#include "BinaryTree.h"