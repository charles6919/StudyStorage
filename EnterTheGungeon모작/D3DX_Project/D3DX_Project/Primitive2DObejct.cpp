#include "pch.h"
#include "Primitive2DObejct.h"

/*
버텍스 셋팅 -> 버텍스 벡터 -> 값을 채우고 -> 버텍스 버퍼 -> 셰이더 전달
 - 칼라 값을 설정해서 렌더 하는 경우 : 버텍스(포지션과 칼라)
 - 텍스쳐를 사용하는 경우 : 버텍스(포지션, UV좌표)

인덱스 셋팅 -> 인덱스 벡터 -> 값을 채우고 -> 인덱스 버퍼 -> 셰이더 전달

셋팅 된 값으로 셰이더에를 통해서 렌더

-----------------------------------------------------------------------------

기본적으로 위의 값에 대한 셋팅은 크기(지름)를 1로 (반지름 0.5)의 사이즈,
중점을 (0,0) 좌표로 셋팅해서 사용한다.

사이즈와 포지션을 설정하여 실제로 화면에 그려질 크기와 위치 설정
위에서 지정 된 설정값을 적용하기 위하여 트랜스폼 매트릭스를 만들어서 값을 계산한다.
*/