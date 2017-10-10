#include "UI.h"
#include "stdafx.h"

void UI::setAddCallback()
{
	//대화창 콜백 함수 등록
	this->addCallback("conversation", [this](tagMessage msg)
	{
		this->setTokeWindow(msg.data, msg.conversation);
	});
}


void UI::setTokeWindow(int who, char txt)
{

}