#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init(MfxWords)
MfxObject_EndInit(MfxWords, MfxGraph, \
	0, Paint, \
	\
	1, SetCanvas, \
	1, GetCanvas, \
	\
	1, GetText, \
	1, GetTextSize, \
	\
	1, GetFontName, \
	1, GetTextColor, \
	1, GetTextFormat, \
	1, GetTextAlignmentX, \
	1, GetTextAlignmentY, \
	\
	1, SetRect, \
	1, SetSize, \
	\
	1, SetText, \
	1, SetTextSize, \
	1, SetFontName, \
	1, SetTextColor, \
	1, SetTextFormat, \
	1, SetTextAlignmentX, \
	1, SetTextAlignmentY, \
	\
	0, ResetTextLayout);

IDWriteTextFormat* MfxWords::gDefTextFormat = nullptr;

MicroFlakeX::MfxWords::MfxWords()
{

	myRect.Reset(60, 60, 120, 120);
	myText = MfxText("Welcome to MfxWords");
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;

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

MicroFlakeX::MfxWords::MfxWords(MfxString str, MfxRect* set)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;

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

MicroFlakeX::MfxWords::MfxWords(MfxString str, MfxRect* set, FLOAT size)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;

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

MicroFlakeX::MfxWords::MfxWords(MfxString str, MfxRect* set, FLOAT size, IDWriteTextFormat* format)
{
	myRect = set;
	myText = str;
	myColor.Reset(255, 255, 100, 100);
	myTextBrush = nullptr;
	myTextFormat = nullptr;
	myTextLayout = nullptr;

	myCanvas = nullptr;
	myRenderTarget = nullptr;

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

MfxReturn MicroFlakeX::MfxWords::Clone(MfxWords** ret)
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
	myMutexLock.TryWaitLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	if (myRenderTarget && myTextBrush)
	{
		myRenderTarget->DrawTextLayout(
			myRect,
			myTextLayout,
			myTextBrush,
			D2D1_DRAW_TEXT_OPTIONS_CLIP);
	}

	myMutexLock.UnLock(&myRenderTarget, &myTextBrush, &myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetCanvas(MfxCanvas* set)
{
	myMutexLock.WaitLock(&myCanvas);
	myCanvas = set; 
	myMutexLock.UnLock(&myCanvas);

	Update_Canvas();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetCanvas(MfxCanvas** ret)
{
	myMutexLock.WaitLock(&myCanvas);
	*ret = myCanvas;
	myMutexLock.UnLock(&myCanvas);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::GetText(MfxString* ret)
{
	myMutexLock.WaitLock(&myText);
	*ret = myText;
	myMutexLock.UnLock(&myText);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextSize(FLOAT* ret)
{
	myMutexLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetFontSize();
	myMutexLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxString* ret)
{
	WCHAR* fontFamilyName = new WCHAR[myTextLayout->GetFontFamilyNameLength()]{ 0 };

	myMutexLock.WaitLock(&myTextLayout);
	myTextLayout->GetFontFamilyName(fontFamilyName, myTextLayout->GetFontFamilyNameLength());
	myMutexLock.UnLock(&myTextLayout);

	*ret = fontFamilyName;
	SafeDeleteL(fontFamilyName);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextColor(MfxColor* ret)
{
	myMutexLock.WaitLock(&myColor);
	myColor.GetColor(ret);
	myMutexLock.UnLock(&myColor);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextFormat(IDWriteTextFormat** ret)
{
	myMutexLock.WaitLock(&myTextLayout);
	MfxReturn tRet = CopyTextFormat(ret, myTextLayout);
	myMutexLock.UnLock(&myTextLayout);

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentX(TextAlignmentX* ret)
{
	myMutexLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetTextAlignment();
	myMutexLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentY(TextAlignmentY* ret)
{
	myMutexLock.WaitLock(&myTextLayout);
	*ret = myTextLayout->GetParagraphAlignment();
	myMutexLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::SetRect(MfxRect* set)
{
	myMutexLock.TryWaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMutexLock.UnLock(&myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetSize(MfxSize* set)
{
	myMutexLock.TryWaitLock(&myTextLayout, &myRect);

	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	myMutexLock.UnLock(&myTextLayout, &myRect);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetText(MfxString set)
{
	myMutexLock.WaitLock(&myText);
	myText = set;
	myMutexLock.UnLock(&myText);

	ResetTextLayout();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextSize(FLOAT set)
{
	myMutexLock.TryWaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontSize(set, DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMutexLock.UnLock(&myTextLayout, &myText);

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxWords::SetFontName(MfxString set)
{
	myMutexLock.TryWaitLock(&myTextLayout, &myText);
	myTextLayout->SetFontFamilyName(set.c_str(), DWRITE_TEXT_RANGE{ 0,myText.length() });
	myMutexLock.UnLock(&myTextLayout, &myText);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextColor(MfxColor* set)
{
	myMutexLock.WaitLock(&myColor);
	myColor.SetColor(set);
	myMutexLock.UnLock(&myColor);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextFormat(IDWriteTextFormat* set)
{
	myMutexLock.WaitLock(&myTextFormat);

	SafeRelease(myTextFormat);
	CopyTextFormat(&myTextFormat, set);

	myMutexLock.UnLock(&myTextFormat);

	MfxReturn tRet = ResetTextLayout();

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentX(TextAlignmentX set)
{
	myMutexLock.WaitLock(&myTextLayout);
	myTextLayout->SetTextAlignment(set);
	myMutexLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentY(TextAlignmentY set)
{
	myMutexLock.WaitLock(&myTextLayout);
	myTextLayout->SetParagraphAlignment(set);
	myMutexLock.UnLock(&myTextLayout);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::ResetTextLayout()
{
	myMutexLock.TryWaitLock(&myText, &myRect, &myTextLayout, &myTextFormat);

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

	myMutexLock.UnLock(&myText, &myRect, &myTextLayout, &myTextFormat);

	return tRet;
}

MfxReturn MicroFlakeX::MfxWords::Update_Canvas()
{
	myMutexLock.TryWaitLock(&myCanvas, &myRenderTarget, &myColor, &myTextBrush);
	if (myCanvas)
	{
		ID2D1RenderTarget* tID2D1RenderTarget;
		myCanvas->GetRenderTarget(&tID2D1RenderTarget);
		myRenderTarget = (myRenderTarget == tID2D1RenderTarget) ? myRenderTarget : tID2D1RenderTarget;

		SafeRelease(myTextBrush);
		myRenderTarget ? myRenderTarget->CreateSolidColorBrush(myColor, &myTextBrush) : 0;
	}
	else
	{
		SafeRelease(myTextBrush);
		myRenderTarget = nullptr;
	}
	myMutexLock.UnLock(&myCanvas, &myRenderTarget, &myColor, &myTextBrush);

	return Mfx_Return_Fine;
}

