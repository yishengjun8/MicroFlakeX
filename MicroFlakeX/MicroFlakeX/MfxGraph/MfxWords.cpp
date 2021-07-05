#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init(MfxWords)
MfxObject_EndInit(MfxWords, MfxGraph, \
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
	myText = MfxText("Welcome to MfxWords");
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

MicroFlakeX::MfxWords::MfxWords(const MfxString str, const MfxRect* set)
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

MicroFlakeX::MfxWords::MfxWords(const MfxString str, const MfxRect* set, const FLOAT size)
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

MicroFlakeX::MfxWords::MfxWords(const MfxString str, const MfxRect* set, const FLOAT size, IDWriteTextFormat* format)
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


	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::Paint()
{
	Update_Canvas();
	myMemberLock.TryWaitLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	if (myRenderTarget && myTextBrush)
	{
		myRenderTarget->DrawTextLayout(
			myRect,
			myTextLayout,
			myTextBrush,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}

	myMemberLock.UnLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetCanvas(MfxCanvas* set)
{
	myMemberLock.WaitLock(&myCanvas);
	myCanvas = set; 
	myMemberLock.UnLock(&myCanvas);

	Update_Canvas();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetCanvas(MfxCanvas** ret)
{
	myMemberLock.WaitLock(&myCanvas);
	*ret = myCanvas;
	myMemberLock.UnLock(&myCanvas);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::GetText(MfxString* ret)
{
	myMemberLock.WaitLock(&myText);
	*ret = myText;
	myMemberLock.UnLock(&myText);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextSize(FLOAT* ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetFontSize();
	myMemberLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxString* ret)
{
	WCHAR* fontFamilyName = new WCHAR[myTextLayout->GetFontFamilyNameLength()]{ 0 };

	myMemberLock.WaitLock(&myTextLayout);
	myTextLayout->GetFontFamilyName(fontFamilyName, myTextLayout->GetFontFamilyNameLength());
	myMemberLock.UnLock(&myTextLayout);

	*ret = fontFamilyName;
	SafeDeleteL(fontFamilyName);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextColor(MfxColor* ret)
{
	myMemberLock.WaitLock(&myColor);
	myColor.GetColor(ret);
	myMemberLock.UnLock(&myColor);

	return Mfx_Return_Fine;
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentY(TextAlignmentY* ret)
{
	myMemberLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetParagraphAlignment();
	myMemberLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::SetRect(const MfxRect* set)
{
	myMemberLock.TryWaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMemberLock.UnLock(&myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetSize(const MfxSize* set)
{
	myMemberLock.TryWaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMemberLock.UnLock(&myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetText(const MfxString set)
{
	myMemberLock.WaitLock(&myText);
	myText = set;
	myMemberLock.UnLock(&myText);

	ResetTextLayout();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextSize(const FLOAT set)
{
	myMemberLock.TryWaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontSize(set, DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMemberLock.UnLock(&myTextLayout, &myText);

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxWords::SetFontName(const MfxString set)
{
	myMemberLock.TryWaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontFamilyName(set.c_str(), DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMemberLock.UnLock(&myTextLayout, &myText);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextColor(const MfxColor* set)
{
	myMemberLock.TryWaitLock(&myColor, &myTextBrushUpdateFlage);
	myColor.SetColor(set);
	myTextBrushUpdateFlage = true;
	myMemberLock.UnLock(&myColor, &myTextBrushUpdateFlage);

	return Mfx_Return_Fine;
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

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentY(TextAlignmentY set)
{
	myMemberLock.WaitLock(&myTextLayout);
	myTextLayout->SetParagraphAlignment(set);
	myMemberLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::ResetTextLayout()
{
	myMemberLock.TryWaitLock(&myText, &myRect, &myTextLayout, &myTextFormat);

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
		myMemberLock.TryWaitLock(&myRenderTarget, &myColor, &myTextBrush, &myTextBrushUpdateFlage);
		
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
		myMemberLock.TryWaitLock(&myRenderTarget, &myTextBrush);

		SafeRelease(myTextBrush);
		myRenderTarget = nullptr;

		myMemberLock.UnLock(&myRenderTarget, &myTextBrush);
	}
	return Mfx_Return_Fine;
}

