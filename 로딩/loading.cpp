#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}


HRESULT loadItem::initForSound(string keyName, const char* soundName, BOOL bgm, BOOL loop)
{
	_kind = LOAD_KIND_SOUND;

	memset(&_soundResorce, 0, sizeof(tagSoundResource));

	_soundResorce.keyName = keyName;
	_soundResorce.soundName = soundName;
	_soundResorce.bgm = bgm;
	_soundResorce.loop = loop;

	return S_OK;
}



loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage("로딩백그라운드", "디아블로.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//_loadingCat = IMAGEMANAGER->addFrameImage("로딩고양이", "cat.bmp", 0, 0, 234, 38, 4, 1, true, RGB(255, 0, 255));
	_loadingCat = new image;
	_loadingCat->init("cat.bmp", 234, 38, 4, 1, true, RGB(255, 0, 255));
	_loadingCat->setX(30);
	_loadingCat->setY(WINSIZEY - 50);
	_loadingCat->setFrameX(0);

	_count, _index = 0;
	_x = 30;
	_y = WINSIZEY -50;
	_rc = RectMakeCenter(_x, _y, _loadingCat->getFrameWidth(), _loadingCat->getFrameHeight());

	
	

	_loadingBar = new progressBar;
	_loadingBar->init("loadingBarTop", "loadingBarBottom", WINSIZEX/2, WINSIZEY - 20, WINSIZEX, 20);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	return S_OK;

}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	_loadingBar->update();

	_count++;
	//커밋테스트중
	if (_count % 10 == 0)
	{
		_index++;
		_loadingCat->setFrameX(_index);

		if (_index >= _loadingCat->getMaxFrameX()) _index = 0;
	}

	
	_rc = RectMakeCenter(_x, _y, _loadingCat->getFrameWidth(), _loadingCat->getFrameHeight());
	
}

void loading::render() 
{
	_background->render(getMemDC(), 0, 0);
	_loadingBar->render();
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_loadingCat->frameRender(getMemDC(), _loadingBar->getLine() - 50, _y);

}


void loading::loadImage(string keyName, int width, int height)																										
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)												
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)								
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName,x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)					
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, frameX, frameY, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, frameX, frameY, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char* soundName, BOOL bgm, BOOL loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, soundName, bgm, loop);

	_vLoadItem.push_back(item);

}


BOOL loading::loadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, 
				img.width, img.height, img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName,
				img.x, img.y,
				img.width, img.height, 
				img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName,
				img.width, img.height,
				img.frameX, img.frameY,
				img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName,
				img.x, img.y,
				img.width, img.height,
				img.frameX, img.frameY,
				img.trans, img.transColor);
		}
		break;
		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.soundName, sound.bgm, sound.loop);
		}
		break;
	}


	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	_currentGauge++;

	return FALSE;
}

