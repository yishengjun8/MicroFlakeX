#include "pch.h"
#include "MfxLowPart.h"

std::wstring MicroFlakeX::MfxWords::Global_FontName = L"Consolas";
int MicroFlakeX::MfxWords::Global_FontSize = 14;
int MicroFlakeX::MfxWords::Global_LineSize = 6;

MicroFlakeX::MfxWords::MfxWords(Gdiplus::Graphics* myGraphics)
{
	myWords = L"<Sample Words>\n<__Ê¾ÀýÎÄ×Ö__>\n<Sample Words>";
	myFontName = Global_FontName;
	myFontSize = Global_FontSize;
	myRect = Gdiplus::Rect(0, 0, 160, 90);
	myFontOffset = Gdiplus::Point(Global_LineSize / 4, Global_LineSize / 2);
	myFormatXY = MFXWORDS_FORMATX_NEAR | MFXWORDS_FORMATY_NEAR;
	myLineSize = Global_LineSize;

	this->myGraphics = myGraphics;

	wordsFont = new Gdiplus::Font(myFontName.c_str(), myFontSize);
	wordsFormat.SetAlignment(Gdiplus::StringAlignmentNear);

	wordsColor = Gdiplus::Color::Black;//ÎÄ×ÖÑÕÉ«
	lineColor = Gdiplus::Color::Green;//±ß¿òÑÕÉ«
	backColor = Gdiplus::Color::Gray;//±³¾°ÑÕÉ«

	worldsBrush = new Gdiplus::SolidBrush(wordsColor);//ÎÄ×Ö»­Ë¢
	linePen = new Gdiplus::Pen(lineColor, myLineSize);//±ß¿ò»­±Ê
	backBrush = new Gdiplus::SolidBrush(backColor);//±³¾°»­Ë¢
}

MicroFlakeX::MfxWords::~MfxWords()
{
	delete wordsFont;

	delete worldsBrush;
	delete linePen;
	delete backBrush;
}

std::wstring MicroFlakeX::MfxWords::SetGlobalFont(std::wstring set)
{
	std::wstring retFontName = Global_FontName;
	Global_FontName = set;
	return retFontName;
}

std::wstring MicroFlakeX::MfxWords::GetGlobalFont()
{
	return Global_FontName;
}

int MicroFlakeX::MfxWords::SetGlobalFontSize(int set)
{
	int retSize = Global_FontSize;
	Global_FontSize = set;
	return retSize;
}

int MicroFlakeX::MfxWords::GetGlobalFontSize()
{
	return Global_FontSize;
}

int MicroFlakeX::MfxWords::SetGlobalLineSize(int set)
{
	int retSize = Global_LineSize;
	Global_LineSize = set;
	return retSize;
}

int MicroFlakeX::MfxWords::GetGlobalLineSize()
{
	return Global_LineSize;
}

std::wstring MicroFlakeX::MfxWords::SetWords(std::wstring set)
{
	std::wstring retWords = myWords;
	myWords = set;
	return retWords;
}

std::wstring MicroFlakeX::MfxWords::GetWords()
{
	return std::wstring();
}

std::wstring MicroFlakeX::MfxWords::SetFont(std::wstring set)
{
	Gdiplus::Font* tFont = nullptr;
	tFont = new Gdiplus::Font(set.c_str(), myFontSize);
	if (tFont == nullptr)
	{
		return std::wstring{L"Font Error"};
	}

	std::wstring retStr = myFontName;
	myFontName = set;
	delete wordsFont;
	wordsFont = tFont;
	return retStr;
}

std::wstring MicroFlakeX::MfxWords::GetFont()
{
	return myFontName;
}


int MicroFlakeX::MfxWords::SetFontSize(int set)
{
	if (set <= 0)
	{
		return -1;
	}
	Gdiplus::Font* tFont = nullptr;
	tFont = new Gdiplus::Font(myFontName.c_str(), myFontSize);
	if (tFont == nullptr)
	{
		return -1;
	}

	int retSize = myFontSize;
	myFontSize = set;
	delete wordsFont;
	wordsFont = tFont;
	return retSize;
}

int MicroFlakeX::MfxWords::GetFontSize()
{
	return myFontSize;
}

int MicroFlakeX::MfxWords::SetLineSize(int set)
{
	if (linePen->SetWidth(set) != Gdiplus::Ok)
	{
		return -1;
	}
	int retSize = myLineSize;
	myLineSize = set;

	return retSize;
}

int MicroFlakeX::MfxWords::GetLineSize()
{
	return myLineSize;
}

Gdiplus::Point MicroFlakeX::MfxWords::SetPoint(Gdiplus::Point set)
{
	Gdiplus::Point retPoint(myRect.X, myRect.Y);
	myRect.X = set.X;
	myRect.Y = set.Y;
	return retPoint;
}

Gdiplus::Point MicroFlakeX::MfxWords::GetPoint()
{
	Gdiplus::Point retPoint(myRect.X, myRect.Y);
	return retPoint;
}

Gdiplus::Size MicroFlakeX::MfxWords::SetSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width, myRect.Height);
	myRect.Width = set.Width;
	myRect.Height = set.Height;
	return retSize;
}

Gdiplus::Size MicroFlakeX::MfxWords::GetSize()
{
	Gdiplus::Size retSize(myRect.Width, myRect.Height);
	return retSize;
}

Gdiplus::Rect MicroFlakeX::MfxWords::SetRect(Gdiplus::Rect set)
{
	Gdiplus::Rect retRect = myRect;
	SetPoint(Gdiplus::Point(set.X, set.Y));
	SetSize(Gdiplus::Size(set.Width, set.Height));
	myRect = set;
	return retRect;
}

Gdiplus::Rect MicroFlakeX::MfxWords::GetRect()
{
	return myRect;
}

Gdiplus::Point MicroFlakeX::MfxWords::SetFontOffset(Gdiplus::Point set)
{
	Gdiplus::Point retOffset = myFontOffset;
	myFontOffset = set;
	return retOffset;
}

Gdiplus::Point MicroFlakeX::MfxWords::GetFontOffset()
{
	return myFontOffset;
}

MicroFlakeX::MFXWORDS_FORMAT MicroFlakeX::MfxWords::SetFormat(MFXWORDS_FORMAT set)
{
	myFormatXY = set;

	myFormatXY& MFXWORDS_FORMATX_NEAR ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentNear) : 0;
	myFormatXY& MFXWORDS_FORMATX_CENTER ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentCenter) : 0;
	myFormatXY& MFXWORDS_FORMATX_FAR ? wordsFormat.SetAlignment(Gdiplus::StringAlignmentFar) : 0;

	return myFormatXY;
}

MicroFlakeX::MFXWORDS_FORMAT MicroFlakeX::MfxWords::GetFormat()
{
	return myFormatXY;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetFontColor(Gdiplus::Color set)
{
	if (worldsBrush->SetColor(set) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(wordsColor);
	wordsColor = set;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetFontColor()
{
	return wordsColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetLineColor(Gdiplus::Color set)
{
	if (linePen->SetColor(set) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(lineColor);
	lineColor = set;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetLineColor()
{
	return lineColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::SetBackColor(Gdiplus::Color set)
{
	if (backBrush->SetColor(set) != Gdiplus::Ok)
	{
		return Gdiplus::Color(0, 0, 0, 0);
	}
	Gdiplus::Color retColor(backColor);
	backColor = set;
	return retColor;
}

Gdiplus::Color MicroFlakeX::MfxWords::GetBackColor()
{
	return backColor;
}

BOOL MicroFlakeX::MfxWords::Contains(Gdiplus::Point set)
{
	return myRect.Contains(set);
}

Gdiplus::Point MicroFlakeX::MfxWords::OffsetPoint(Gdiplus::Point set)
{
	return Gdiplus::Point();
}

Gdiplus::Size MicroFlakeX::MfxWords::OffsetSize(Gdiplus::Size set)
{
	Gdiplus::Size retSize(myRect.Width, myRect.Height);
	retSize = retSize + set;
	myRect.Width = retSize.Width;
	myRect.Height = retSize.Height;
	return retSize;
}

Gdiplus::Status MicroFlakeX::MfxWords::Draw(MFXWORDS_DRAWTYPE set)
{
	Gdiplus::Status retStatus(Gdiplus::Ok);
	if (set & MFXWORDS_DRAWTYPE_FILL)
	{
		retStatus = myGraphics->FillRectangle(backBrush, myRect);
	}

	if (retStatus != Gdiplus::Ok)
	{
		return retStatus;
	}

	retStatus = myGraphics->DrawString(
		myWords.c_str(), myWords.length(),
		wordsFont,
		Gdiplus::RectF(myRect.X, myRect.Y, myRect.Width, myRect.Height),
		&wordsFormat,
		worldsBrush);

	if (retStatus != Gdiplus::Ok)
	{
		return retStatus;
	}

	if (set & MFXWORDS_DRAWTYPE_LINE)
	{
		retStatus = myGraphics->DrawRectangle(linePen, myRect);
	}
	return retStatus;
}