#pragma once
#include "SingletonBase.h"

class CameraManager
	:public SingletonBase<CameraManager>
{
private:
	
};

//과제
/*
	기본숙제: 방향키 움직이면 고정시점, 마우스로 끝에서 밀면 자유시점
	추가숙제: 자유 시점에서 고정시점 돌아올때 보간을 이용해서 부드럽게 돌아오기.
*/