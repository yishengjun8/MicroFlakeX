#include "pch.h"
#include "MfxGraph.h"

MFX_OBJ_REFLECTION_INIT(MfxWords)
MFX_OBJ_REFLECTION_ENDINIT(MfxWords, MfxGraph, \
	Paint, \
	\
	SetCanvas, \
	GetCanvas, \
	\
	GetText, \
	GetTextSize, \
	\
	GetFontName, \
	GetTextColor, \
	GetTextFormat, \
	GetTextAlignmentX, \
	GetTextAlignmentY, \
	\
	SetRect, \
	SetSize, \
	\
	SetText, \
	SetTextSize, \
	SetFontName, \
	SetTextColor, \
	SetTextFormat, \
	SetTextAlignmentX, \
	SetTextAlignmentY, \
	\
	Update_Canvas, \
	ResetTextLayout);

IDWriteTextFormat* MfxWords::gDefTextFormat = nullptr;

MicroFlakeX::MfxWords::MfxWords()
{
	myRect.Reset(0, 0, 100, 100);
	myText = MFX_TXT_W("Welcome to MfxWords");
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myTextBrushUpdateFlage = false;

	HRESULT hr = CopyTextFormat(&myTextFormat, gDefTextFormat);

	if (SUCCEEDED(hr))
	{
		hr = MfxGraph::myIDWriteFactory->CreateTextLayout(
			myText.c_str(),
			myText.length(),
			myTextFormat,
			myRect.myWidth,
			myRect.myHeight,
			&myTextLayout
		);
	}
}

MicroFlakeX::MfxWords::MfxWords(const MfxStringW str, const MfxRect* set)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myTextBrushUpdateFlage = false;

	HRESULT hr = CopyTextFormat(&myTextFormat, gDefTextFormat);

	if (SUCCEEDED(hr))
	{
		hr = MfxGraph::myIDWriteFactory->CreateTextLayout(
			myText.c_str(),
			myText.length(),
			myTextFormat,
			myRect.myWidth,
			myRect.myHeight,
			&myTextLayout
		);
	}
}

MicroFlakeX::MfxWords::MfxWords(const MfxStringW str, const MfxRect* set, const FLOAT size)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myTextBrushUpdateFlage = false;

	HRESULT hr = CopyTextFormat(&myTextFormat, gDefTextFormat);

	if (SUCCEEDED(hr))
	{
		hr = MfxGraph::myIDWriteFactory->CreateTextLayout(
			myText.c_str(),
			myText.length(),
			myTextFormat,
			myRect.myWidth,
			myRect.myHeight,
			&myTextLayout
		);

		SetTextSize(size);
	}
}

MicroFlakeX::MfxWords::MfxWords(const MfxStringW str, const MfxRect* set, const FLOAT size, IDWriteTextFormat* format)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;
	myTextBrushUpdateFlage = false;

	HRESULT hr = CopyTextFormat(&myTextFormat, format);

	if (SUCCEEDED(hr))
	{
		hr = MfxGraph::myIDWriteFactory->CreateTextLayout(
			myText.c_str(),
			myText.length(),
			myTextFormat,
			myRect.myWidth,
			myRect.myHeight,
			&myTextLayout
		);

		SetTextSize(size);
	}
}

MicroFlakeX::MfxWords::~MfxWords()
{
	SafeRelease(myTextBrush);
	SafeRelease(myTextFormat);
	SafeRelease(myTextLayout);
}

MfxReturn MicroFlakeX::MfxWords::Clone(MfxWords** ret)const
{
	*ret = new MfxWords(myText, &myRect, myTextLayout->GetFontSize(), myTextLayout);

	(*ret)->SetCanvas(myCanvas);
	(*ret)->SetTextColor(&myColor);


	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::Paint()
{
	Update_Canvas();
	myMemberLock.WaitLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	if (myRenderTarget && myTextBrush)
	{
		myRenderTarget->DrawTextLayout(
			myRect,
			myTextLayout,
			myTextBrush,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}

	myMemberLock.UnLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetCanvas(MfxCanvas* set)
{
	myMemberLock.WaitLock(&myCanvas);
	myCanvas = set; 
	myMemberLock.UnLock(&myCanvas);

	Update_Canvas();

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetCanvas(MfxCanvas** ret)
{
	myMemberLock.WaitLock(&myCanvas);
	*ret = myCanvas;
	myMemberLock.UnLock(&myCanvas);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::GetText(MfxStringW* ret)
{
	myMemberLock.WaitLock(&myText);
	*ret = myText;
	myMemberLock.UnLock(&myText);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetTextSize(FLOAT* ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetFontSize();
	myMemberLock.UnLock(&myTextLayout);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxStringW* ret)
{
	WCHAR* fontFamilyName = new WCHAR[myTextLayout->GetFontFamilyNameLength()]{ 0 };

	myMemberLock.WaitLock(&myTextLayout);
	myTextLayout->GetFontFamilyName(fontFamilyName, myTextLayout->GetFontFamilyNameLength());
	myMemberLock.UnLock(&myTextLayout);

	*ret = fontFamilyName;
	SafeDeleteList(fontFamilyName);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetTextColor(MfxColor* ret)
{
	myMemberLock.WaitLock(&myColor);
	myColor.GetColor(ret);
	myMemberLock.UnLock(&myColor);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetTextFormat(IDWriteTextFormat** ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	MfxReturn tRet = CopyTextFormat(ret, myTextLayout);
	myMemberLock.UnLock(&myTextLayout);

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentX(TextAlignmentX* ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetTextAlignment();
	myMemberLock.UnLock(&myTextLayout);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentY(TextAlignmentY* ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetParagraphAlignment();
	myMemberLock.UnLock(&myTextLayout);

	return MFX_RET_SECCESS;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::SetRect(const MfxRect* set)
{
	myMemberLock.WaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMemberLock.UnLock(&myTextLayout, &myRect);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetSize(const MfxSize* set)
{
	myMemberLock.WaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMemberLock.UnLock(&myTextLayout, &myRect);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetText(const MfxStringW set)
{
	myMemberLock.WaitLock(&myText);
	myText = set;
	myMemberLock.UnLock(&myText);

	ResetTextLayout();

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetTextSize(const FLOAT set)
{
	myMemberLock.WaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontSize(set, DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMemberLock.UnLock(&myTextLayout, &myText);

	return MFX_RET_SECCESS;
}


MfxReturn MicroFlakeX::MfxWords::SetFontName(const MfxStringW set)
{
	myMemberLock.WaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontFamilyName(set.c_str(), DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMemberLock.UnLock(&myTextLayout, &myText);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetTextColor(const MfxColor* set)
{
	myMemberLock.WaitLock(&myColor, &myTextBrushUpdateFlage);
	myColor.SetColor(set);
	myTextBrushUpdateFlage = true;
	myMemberLock.UnLock(&myColor, &myTextBrushUpdateFlage);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetTextFormat(IDWriteTextFormat* set)
{
	myMemberLock.WaitLock(&myTextFormat);

	SafeRelease(myTextFormat);
	CopyTextFormat(&myTextFormat, set);

	myMemberLock.UnLock(&myTextFormat);

	MfxReturn tRet = ResetTextLayout();

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentX(TextAlignmentX set)
{
	myMemberLock.WaitLock(&myTextLayout);
	myTextLayout->SetTextAlignment(set);
	myMemberLock.UnLock(&myTextLayout);

	return MFX_RET_SECCESS;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentY(TextAlignmentY set)
{
	myMemberLock.WaitLock(&myTextLayout);
	myTextLayout->SetParagraphAlignment(set);
	myMemberLock.UnLock(&myTextLayout);

	return MFX_RET_SECCESS;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::ResetTextLayout()
{
	myMemberLock.WaitLock(&myText, &myRect, &myTextLayout, &myTextFormat);

	SafeRelease(myTextFormat);
	CopyTextFormat(&myTextFormat, myTextLayout);
	SafeRelease(myTextLayout);

	MfxReturn tRet = MfxGraph::myIDWriteFactory->CreateTextLayout(
		myText.c_str(),
		myText.length(),
		myTextFormat,
		myRect.myWidth,
		myRect.myHeight,
		&myTextLayout
	);

	myMemberLock.UnLock(&myText, &myRect, &myTextLayout, &myTextFormat);

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::Update_Canvas()
{
	myMemberLock.WaitLock(&myCanvas);
	if (myCanvas)
	{
		ID2D1RenderTarget* tID2D1RenderTarget;
		myCanvas->GetRenderTarget(&tID2D1RenderTarget);

		myMemberLock.UnLock(&myCanvas);
		myMemberLock.WaitLock(&myRenderTarget, &myColor, &myTextBrush, &myTextBrushUpdateFlage);
		
		if (myTextBrushUpdateFlage || (myRenderTarget != tID2D1RenderTarget))
		{
			SafeRelease(myTextBrush);
			tID2D1RenderTarget ? (MfxReturn)tID2D1RenderTarget->CreateSolidColorBrush(myColor, &myTextBrush) : 0;
		}
		myRenderTarget = tID2D1RenderTarget;
		myTextBrushUpdateFlage = myTextBrush ? false : true;

		myMemberLock.UnLock(&myRenderTarget, &myColor, &myTextBrush, &myTextBrushUpdateFlage);
	}
	else
	{
		myMemberLock.UnLock(&myCanvas);
		myMemberLock.WaitLock(&myRenderTarget, &myTextBrush);

		SafeRelease(myTextBrush);
		myRenderTarget = nullptr;

		myMemberLock.UnLock(&myRenderTarget, &myTextBrush);
	}
	return MFX_RET_SECCESS;
}

