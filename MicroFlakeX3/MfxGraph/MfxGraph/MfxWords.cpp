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
	if (myCanvas)
	{
		ID2D1RenderTarget* tRenderTarget = nullptr;
		myCanvas->GetRenderTarget(&tRenderTarget);

		if (myRenderTarget != tRenderTarget)
		{
			myRenderTarget = tRenderTarget;
			SafeRelease(myTextBrush);
			D2D1_COLOR_F tColor{ 0 };
			myColor.GetD2D1ColorF(&tColor);
			myRenderTarget->CreateSolidColorBrush(tColor, (ID2D1SolidColorBrush**)&myTextBrush);
		}

		if (myTextBrush)
		{
			D2D1_POINT_2F tPoint{ 0 };
			myRect.GetD2D1PointF(&tPoint);
			myRenderTarget->DrawTextLayout(
				tPoint,
				myTextLayout,
				myTextBrush,
				D2D1_DRAW_TEXT_OPTIONS_CLIP);
		}
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetCanvas(MfxCanvas* set)
{
	myCanvas = set; 

	if (!myCanvas)
	{
		return Mfx_Return_Fine;
	}

	ID2D1RenderTarget* tRenderTarget = nullptr;
	myCanvas->GetRenderTarget(&tRenderTarget);

	if (myRenderTarget != tRenderTarget)
	{
		myRenderTarget = tRenderTarget;
		D2D1_COLOR_F tColor{ 0 };
		myColor.GetD2D1ColorF(&tColor);
		myRenderTarget->CreateSolidColorBrush(tColor, (ID2D1SolidColorBrush**)&myTextBrush);
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetCanvas(MfxCanvas** ret) const
{
	*ret = myCanvas;

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::GetText(MfxString* ret) const
{
	*ret = myText;

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextSize(FLOAT* ret) const
{
	*ret = myTextLayout->GetFontSize();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxString* ret) const
{
	WCHAR* fontFamilyName = new WCHAR[myTextLayout->GetFontFamilyNameLength()]{ 0 };
	myTextLayout->GetFontFamilyName(fontFamilyName, myTextLayout->GetFontFamilyNameLength());

	*ret = fontFamilyName;
	SafeDeleteL(fontFamilyName);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextColor(MfxColor* ret) const
{
	myColor.GetColor(ret);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextFormat(IDWriteTextFormat** ret) const
{
	return CopyTextFormat(ret, myTextLayout);
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentX(TextAlignmentX* ret) const
{
	*ret = myTextLayout->GetTextAlignment();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentY(TextAlignmentY* ret) const
{
	*ret = myTextLayout->GetParagraphAlignment();

	return Mfx_Return_Fine;
}




/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::SetRect(MfxRect* set)
{
	myRect = set;

	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetSize(MfxSize* set)
{
	myRect = set;

	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetText(MfxString set)
{
	myText = set;

	ResetTextLayout();

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextSize(FLOAT set)
{
	myTextLayout->SetFontSize(set, DWRITE_TEXT_RANGE{ 0,myText.length() });

	return Mfx_Return_Fine;
}


MfxReturn MicroFlakeX::MfxWords::SetFontName(MfxString set)
{
	myTextLayout->SetFontFamilyName(set.c_str(), DWRITE_TEXT_RANGE{ 0,myText.length() });

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextColor(MfxColor* set)
{
	myColor = set;

	if (myCanvas)
	{
		ID2D1RenderTarget* tRenderTarget = nullptr;
		myCanvas->GetRenderTarget(&tRenderTarget);
		if (myRenderTarget != tRenderTarget)
		{
			myRenderTarget = tRenderTarget;
			D2D1_COLOR_F tColor{ 0 };
			myColor.GetD2D1ColorF(&tColor);
			myRenderTarget->CreateSolidColorBrush(tColor, (ID2D1SolidColorBrush**)&myTextBrush);
		}
	}

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextFormat(IDWriteTextFormat* set)
{
	SafeRelease(myTextFormat);
	CopyTextFormat(&myTextFormat, set);

	return ResetTextLayout();
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentX(TextAlignmentX set)
{
	myTextLayout->SetTextAlignment(set);

	return Mfx_Return_Fine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentY(TextAlignmentY set)
{
	myTextLayout->SetParagraphAlignment(set);

	return Mfx_Return_Fine;
}


/**************************************************************
*
*
*
***************************************************************/
MfxReturn MicroFlakeX::MfxWords::ResetTextLayout()
{
	SafeRelease(myTextFormat);

	CopyTextFormat(&myTextFormat, myTextLayout);

	SafeRelease(myTextLayout);

	return MfxGraph::myIDWriteFactory->CreateTextLayout(
		myText.c_str(),
		myText.length(),
		myTextFormat,
		myRect.myWidth,
		myRect.myHeight,
		&myTextLayout
	);
}

