#include "UI.h"
#include "stdafx.h"

void UI::setAddCallback()
{
	//��ȭâ �ݹ� �Լ� ���
	this->addCallback("conversation", [this](tagMessage msg)
	{
		this->setTokeWindow(msg.data, msg.conversation);
	});
}


void UI::setTokeWindow(int who, char txt)
{

}