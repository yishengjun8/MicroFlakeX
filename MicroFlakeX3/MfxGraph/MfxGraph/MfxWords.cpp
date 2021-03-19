#include "pch.h"
#include "MfxGraph.h"

MfxObject_Init_0(MfxWords)
MfxObject_Init_1(MfxWords)
MfxObject_Init_2(MfxWords, MfxGraph);

IDWriteTextFormat* MfxWords::gDefTextFormat = nullptr;

MicroFlakeX::MfxWords::MfxWords()
{

	myRect.Init(60, 60, 120, 120);
	myText = L"Welcome to MfxWords";
	myColor.Init(255, 255, 100, 100);
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

MicroFlakeX::MfxWords::MfxWords(MfxStrW str, MfxRect set)
{
	myRect = set;
	myText = str;
	myColor.Init(255, 255, 100, 100);
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

MicroFlakeX::MfxWords::MfxWords(MfxStrW str, MfxRect set, FLOAT size)
{
	myRect = set;
	myText = str;
	myColor.Init(255, 255, 100, 100);
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

MicroFlakeX::MfxWords::MfxWords(MfxStrW str, MfxRect set, FLOAT size, IDWriteTextFormat* format)
{
	myRect = set;
	myText = str;
	myColor.Init(255, 255, 100, 100);
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

MfxReturn MicroFlakeX::MfxWords::Clone(MfxBase** ret)
{
	return MfxReturn();
}

MfxReturn MicroFlakeX::MfxWords::Clone(MfxWords** ret)
{
	*ret = new MfxWords(myText, myRect, myTextLayout->GetFontSize(), myTextLayout);
	(*ret)->SetCanvas(myCanvas);
	(*ret)->SetTextColor(myColor);
	return RFine;
}

MfxBase& MicroFlakeX::MfxWords::operator=(MfxBase& rhs)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

BOOL MicroFlakeX::MfxWords::operator==(MfxBase& rhs)
{
	return 0;
}

MicroFlakeX::MfxReturn MicroFlakeX::MfxWords::Paint()
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
				myTextBrush);
		}
	}
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetCanvas(MfxCanvas* set)
{
	myCanvas = set; 
	if (!myCanvas)
	{
		return RFine;
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetCanvas(MfxCanvas** ret)
{
	*ret = myCanvas;
	return RFine;
}

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

MfxReturn MicroFlakeX::MfxWords::SetText(MfxStrW set)
{
	myText = set;
	ResetTextLayout();
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetText(MfxStrW* ret)
{
	*ret = myText;
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextSize(FLOAT set)
{
	myTextLayout->SetFontSize(set, DWRITE_TEXT_RANGE{ 0,myText.length() });
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextSize(FLOAT* ret)
{
	*ret = myTextLayout->GetFontSize();
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetFontName(MfxStrW set)
{
	myTextLayout->SetFontFamilyName(set.c_str(), DWRITE_TEXT_RANGE{ 0,myText.length() });
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetFontName(MfxStrW* ret)
{
	WCHAR* fontFamilyName = new WCHAR[myTextLayout->GetFontFamilyNameLength()]{ 0 };
	myTextLayout->GetFontFamilyName(fontFamilyName, myTextLayout->GetFontFamilyNameLength());

	*ret = fontFamilyName;
	SafeDeleteL(fontFamilyName);
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextFormat(IDWriteTextFormat* set)
{
	SafeRelease(myTextFormat);
	CopyTextFormat(&myTextFormat, set);
	return ResetTextLayout();
}

MfxReturn MicroFlakeX::MfxWords::GetTextFormat(IDWriteTextFormat** ret)
{
	return CopyTextFormat(ret, myTextLayout);
}

MfxReturn MicroFlakeX::MfxWords::SetTextColor(MfxColor set)
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
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextColor(MfxColor* set)
{
	*set = myColor;
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetRect(MfxRect set)
{
	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetSize(MfxSize set)
{
	myRect = set;
	myTextLayout->SetMaxWidth(myRect.myWidth);
	myTextLayout->SetMaxHeight(myRect.myHeight);
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentX(TextAlignmentX set)
{
	myTextLayout->SetTextAlignment(set);
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentX(TextAlignmentX* ret)
{
	*ret = myTextLayout->GetTextAlignment();
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::SetTextAlignmentY(TextAlignmentY set)
{
	myTextLayout->SetParagraphAlignment(set);
	return RFine;
}

MfxReturn MicroFlakeX::MfxWords::GetTextAlignmentY(TextAlignmentY* ret)
{
	*ret = myTextLayout->GetParagraphAlignment();
	return RFine;
}
